#pragma once

#include "Common/File/Path.h"

#include <mutex>
#include <string_view>

// Utility functions moved out from MemstickScreen.

class MoveProgressReporter {
public:
	void SetProgress(std::string_view value, size_t count = 0, size_t maxVal = 0) {
		std::lock_guard<std::mutex> guard(mutex_);
		progress_ = value;
		count_ = (int)count;
		max_ = (int)maxVal;
	}

	std::string Format();

private:
	std::string progress_;
	std::mutex mutex_;
	int count_;
	int max_;
};

struct MoveResult {
	bool success;  // Got through the whole move.
	std::string errorMessage;
	size_t failedFiles;
	size_t skippedFiles;
};

bool FolderSeemsToBeUsed(const Path &newMemstickFolder);
// Verifies that the folder is usable for PSP data, then switches the active memstick.
// On failure, error (when provided) contains a user-facing explanation.
bool SwitchMemstickFolderTo(Path newMemstickFolder, std::string *error = nullptr);
MoveResult *MoveDirectoryContentsSafe(Path moveSrc, Path moveDest, MoveProgressReporter &progressReporter);
