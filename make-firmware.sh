#!/usr/bin/env bash
#
# make-firmware.sh — interactive Corne (and friends) firmware builder.
#
# Scans this directory for */*/keymap.c, offers a lettered menu, then:
#   1. copies the selected keymap into ~/qmk_firmware/keyboards/<kb>/keymaps/
#   2. runs `qmk compile -kb <kb>/<rev> -km <keymap>`
#   3. copies the resulting .hex back into the source keymap directory
#
# Override the QMK location with QMK_HOME=… if it isn't at ~/qmk_firmware.
#
# To add a new keyboard family, extend keyboard_id_for() below.

set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
QMK_HOME="${QMK_HOME:-$HOME/qmk_firmware}"

# Map a top-level directory name (the first path segment under ROOT)
# to its QMK -kb identifier.
keyboard_id_for() {
    case "$1" in
        corne) echo "crkbd/rev1" ;;
        *)     echo "" ;;
    esac
}

# ---------------------------------------------------------------------------
# Discover keymap directories: ROOT/<keyboard>/<keymap>/keymap.c
# ---------------------------------------------------------------------------
KEYMAPS=()
while IFS= read -r -d '' dir; do
    [[ -f "$dir/keymap.c" ]] && KEYMAPS+=("$dir")
done < <(find "$ROOT" -mindepth 2 -maxdepth 2 -type d -print0 | sort -z)

if [[ ${#KEYMAPS[@]} -eq 0 ]]; then
    echo "No keymaps found under $ROOT (looking for */*/keymap.c)." >&2
    exit 1
fi

if [[ ${#KEYMAPS[@]} -gt 26 ]]; then
    echo "Found ${#KEYMAPS[@]} keymaps — this script only supports up to 26 (a–z)." >&2
    exit 1
fi

# ---------------------------------------------------------------------------
# Display menu
# ---------------------------------------------------------------------------
echo "Available firmware to build:"
i=0
for kp in "${KEYMAPS[@]}"; do
    rel="${kp#$ROOT/}"
    # ASCII 97 = 'a'
    letter=$(printf "\\$(printf '%03o' $((97 + i)))")
    printf "  %s) %s\n" "$letter" "$rel"
    i=$((i + 1))
done
echo

read -r -p "Pick one (letter): " choice

# Normalize to lowercase, require single letter a–z within range.
choice="$(echo "$choice" | tr '[:upper:]' '[:lower:]')"
if [[ ! "$choice" =~ ^[a-z]$ ]]; then
    echo "Invalid choice: '$choice' — expected a single letter." >&2
    exit 1
fi
idx=$(( $(printf '%d' "'$choice") - 97 ))
if (( idx < 0 || idx >= ${#KEYMAPS[@]} )); then
    echo "Letter '$choice' is out of range." >&2
    exit 1
fi

# ---------------------------------------------------------------------------
# Resolve names + paths from selection
# ---------------------------------------------------------------------------
SRC="${KEYMAPS[$idx]}"
REL="${SRC#$ROOT/}"
TOP_DIR="${REL%%/*}"      # e.g. "corne"
KEYMAP_NAME="${REL##*/}"  # e.g. "colemak-dh-iso-qwerty1"

KB_ID="$(keyboard_id_for "$TOP_DIR")"
if [[ -z "$KB_ID" ]]; then
    echo "No QMK keyboard ID known for '$TOP_DIR'." >&2
    echo "Add a case to keyboard_id_for() in $0 and re-run." >&2
    exit 1
fi

KB_BASE="${KB_ID%%/*}"  # e.g. "crkbd" (strip the /revN suffix)
DEST="$QMK_HOME/keyboards/$KB_BASE/keymaps/$KEYMAP_NAME"
HEX_NAME="${KB_ID//\//_}_${KEYMAP_NAME}.hex"
HEX_PATH="$QMK_HOME/$HEX_NAME"

# Sanity check QMK install
if [[ ! -d "$QMK_HOME" ]]; then
    echo "QMK_HOME does not exist: $QMK_HOME" >&2
    echo "Run 'qmk setup' or set QMK_HOME=/path/to/qmk_firmware before re-running." >&2
    exit 1
fi

cat <<EOF

  Source:      $SRC
  QMK -kb:     $KB_ID
  Keymap name: $KEYMAP_NAME
  Destination: $DEST

EOF

# ---------------------------------------------------------------------------
# 1. Copy keymap source into the QMK tree (fresh — wipe any prior copy)
# ---------------------------------------------------------------------------
echo "→ Copying keymap into QMK tree…"
rm -rf "$DEST"
cp -R "$SRC" "$DEST"

# ---------------------------------------------------------------------------
# 2. Compile
# ---------------------------------------------------------------------------
echo "→ Running: qmk compile -kb $KB_ID -km $KEYMAP_NAME"
( cd "$QMK_HOME" && qmk compile -kb "$KB_ID" -km "$KEYMAP_NAME" )

# ---------------------------------------------------------------------------
# 3. Copy resulting .hex back into the source keymap directory
# ---------------------------------------------------------------------------
if [[ ! -f "$HEX_PATH" ]]; then
    echo "Expected firmware at $HEX_PATH but it's not there." >&2
    echo "The build likely failed — check the qmk compile output above." >&2
    exit 1
fi

echo "→ Copying $HEX_NAME back to $SRC/"
cp "$HEX_PATH" "$SRC/"

echo
echo "✓ Done. Firmware at: $SRC/$HEX_NAME"
