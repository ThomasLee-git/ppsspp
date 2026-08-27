# Milestone Memory

Read this file before continuing Android release work. Verify current source
and live Actions state before relying on these notes.

## Main Goal

Maintain a PPSSPP Android branch based on release `v1.20.4` with the project
changes for OpenGL-by-default Android rendering and removable-memstick
permission validation, and produce a testable APK.

## Current Focus

Done: `android-v1.20.4-custom` is based on `v1.20.4`, contains the intended
Android changes, and has produced a successful `NormalOptimized` APK build.

## Active Workstreams

### Android release branch

Goal: Keep the release-based custom branch buildable and testable.

Current status: Done and clean. `android-v1.20.4-custom` matches
`origin/android-v1.20.4-custom` at `bc363258e6`.

Key files: `Core/Config.cpp`, `Core/Util/MemStick.cpp`,
`Core/Util/MemStick.h`, `UI/MemStickScreen.cpp`,
`android/src/org/ppsspp/ppsspp/DocumentResultProxyActivity.java`,
`android/src/org/ppsspp/ppsspp/PpssppActivity.java`,
`assets/lang/en_US.ini`.

Decisions:

- Android defaults to OpenGL in `DefaultGPUBackend()`; explicit Vulkan
  selection remains available.
- The original broad OpenGL commit was reverted because it mixed newer
  `Core/Config.cpp` changes with `v1.20.4` headers. A narrow compatible patch
  was applied instead.
- Removable memstick selection verifies folder existence, PSP directory
  creation, write/read/delete capability, and persisted Android URI access.

Risks/blockers: Device-level validation of USB/scoped-storage behavior remains
to be performed. APK artifact metadata was not retrieved because the GitHub API
rate limit was exhausted after the successful run.

### GitHub Android APK workflow

Current status: Done. The obsolete `gradle --quiet androidGitVersion` step was
removed from `.github/workflows/manual_generate_apk.yml`; the workflow now
runs `./gradlew assemble${{ github.event.inputs.buildVariant }} --stacktrace`.

## Timeline Journal

### 2026-08-27

Situation: A release-based Android branch was needed with prior project changes.

Task: Apply the changes and generate an APK through GitHub Actions.

Action: Based `android-v1.20.4-custom` on tag `v1.20.4`; applied the removable
memstick validation changes; repaired the workflow by removing the nonexistent
`androidGitVersion` task; reverted the incompatible broad `Core/Config.cpp`
change and replaced it with the Android-only OpenGL default; fixed the Java
callback typo from `data.getFlags()` to `result.getData().getFlags()`.

Result: Successful workflow run `33042627806` for commit `bc363258e6`, branch
`android-v1.20.4-custom`, variant `NormalOptimized`. Run URL:
https://github.com/ThomasLee-git/ppsspp/actions/runs/33042627806
The uploaded artifact is named `android-NormalOptimized build`; artifact ID
and size remain unverified due to GitHub API rate limiting.

## Open Next Steps

- Download `android-NormalOptimized build` from run `33042627806` and test it
  on the target Android TV/device.
- Verify default OpenGL startup and explicit Vulkan selection on device.
- Test removable USB/scoped-storage folder selection, including denial and
  write/read/delete failure paths.
