# Release Checklist

Use this checklist before committing or publishing a ROM-affecting package.

## Build

- [ ] `sha1sum baserom.gba` matches `a2fc3574f0a65a4fcf7682fb274b9d7eebdef963`
- [ ] `make clean`
- [ ] `make -j2 fomt.gba`
- [ ] `make check-all`
- [ ] `stat -c '%s' fomt.gba` prints `8388608`

## Emulator Smoke Test

- [ ] `mgba-qt fomt.gba` opens normally
- [ ] title/game screen is not pure white or pure black
- [ ] no emulator load error appears in the terminal

## Package-Specific Test

- [ ] Script package: target script decompiles and expected statements are present
- [ ] Map package: player spawns at a valid coordinate and can move
- [ ] NPC package: test both new game and old save conditions when relevant
- [ ] Decompilation package: current function and next function addresses match the expected map layout

## Notes

- Do not mix content patches and risky decompilation migrations in one commit.
- If a ROM whitescreens, first revert the latest decompilation package and retest before changing content scripts.
- Keep `baserom.gba` unchanged. All changes must be applied to the generated `fomt.gba`.
- Push package branches or PR branches. Do not force-push `main` to solve a non-fast-forward rejection.
