# Task to obtain project version.
# Author: https://github.com/virtualmode
# Bad Python link on Linux? sudo ln -s /usr/bin/python3.10 /usr/bin/python
Version = "1.0.1"

# Default properties.
GitMinVersion = "2.5.0"
GitRemote = "origin"
GitDefaultCommit = "0000000"
GitDefaultVersion = "0.0.0.0" # General value for SemVer and assembly versions regex.
GitTagRegex = "*"
GitBaseVersionRegex = r"v?(?P<MAJOR>0|[1-9]\d*)\.(?P<MINOR>0|[1-9]\d*)(\.(?P<PATCH_BUILD>0|[1-9]\d*))?(\.(?P<REVISION>0|[1-9]\d*))?(?:-(?P<PRERELEASE>(?:0|[1-9]\d*|\d*[a-zA-Z-][0-9a-zA-Z-]*)(?:\.(?:0|[1-9]\d*|\d*[a-zA-Z-][0-9a-zA-Z-]*))*))?(?:\+(?P<BUILDMETADATA>[0-9a-zA-Z-]+(?:\.[0-9a-zA-Z-]+)*))?$"
GitShortShaFormat = "%h"
GitLongShaFormat = "%H"

# Import packages.
import argparse, os, re, subprocess, sys
from os import environ, chdir
from os.path import abspath, dirname, isdir, join
from re import search, sub, match
from subprocess import call, CalledProcessError, check_output

# Support Python 2.7 and higher.
try:
    from subprocess import DEVNULL
except ImportError:
    DEVNULL = open(os.devnull, 'wb')

# Read script arguments.
parser = argparse.ArgumentParser(prog = "Version " + Version + "\r\npython .ci/version.py", description = "Task to obtain project version.")
parser.add_argument("-d", "--debug", action="store_true", help = "show debug information")
parser.add_argument("-s", "--semver", action="store_true", help = "show project SemVer instead assembly version")
parser.add_argument("-l", "--long", action="store_true", help = "show project long version instead short")
parser.add_argument("-m", "--ignore-merges", action="store_true", help = "ignore merges")
parser.add_argument("-t", "--ignore-tag", action="store_true", help = "ignore tag version")
parser.add_argument("-n", "--not-ignore-branch", action="store_true", help = "don't ignore version in branch name")
parser.add_argument("-b", "--branch", nargs = "?", const = "main", help = "default repository branch name")
parser.add_argument("-f", "--file", nargs = "?", const = "", help = "file with version")
args = parser.parse_args()
if len(sys.argv) <= 1:
    parser.print_help()
    sys.exit(0)

# Calculate some properties from arguments.
GitCommits = None
GitVersionMatch = None
GitDefaultBranch = args.branch if args.branch else "main"
GitCommitsIgnoreMerges = "--no-merges" if args.ignore_merges else ""
GitVersionFile = args.file if args.file else ""
GitNotIgnoreBranchVersion = args.not_ignore_branch if args.not_ignore_branch else False
GitIgnoreTagVersion = args.ignore_tag if args.ignore_tag else False
GitCommit = GitDefaultCommit
GitBranch = GitDefaultBranch

# Function for debug purposes.
def log(message):
    if (args.debug):
        print(message)

# Run system command and get result.
def proc(command, errorValue = type(None), errorMessage = None):
    procResult = None
    try:
        procResult = check_output(command, shell = True).decode().strip() if args.debug else check_output(command, shell = True, stderr=DEVNULL).decode().strip()
        log("> " + command + " # " + str(procResult))
        return procResult
    except CalledProcessError:
        log("> " + command + " # " + str(procResult) + " -> " + str(errorValue))
        if errorMessage != None:
            log(errorMessage)
        if errorValue != type(None):
            return errorValue
        else:
            sys.exit(1)

# Calculate version from obtained properties.
def returnVersion():
    global GitCommits, GitVersionMatch
    # Match default regex version if required.
    if GitVersionMatch == None:
        GitVersionMatch = match(GitBaseVersionRegex, GitDefaultVersion)
    # Calculate properties.
    GitMajor = GitVersionMatch.group("MAJOR")
    GitMinor = GitVersionMatch.group("MINOR")
    GitPatchBuild = GitVersionMatch.group("PATCH_BUILD")
    GitRevision = GitVersionMatch.group("REVISION")
    GitPrerelease = GitVersionMatch.group("PRERELEASE")
    GitBuildMetadata = GitVersionMatch.group("BUILDMETADATA")
    GitMajor = int(GitMajor) if GitMajor else 0
    GitMinor = int(GitMinor) if GitMinor else 0
    GitPatchBuild = int(GitPatchBuild) if GitPatchBuild else 0
    GitRevision = int(GitRevision) if GitRevision else 0
    GitPrerelease = GitPrerelease if GitPrerelease else ""
    GitBuildMetadata = GitBuildMetadata if GitBuildMetadata else sub(r"[^0-9A-Za-z-]", "-", GitBranch)
    GitCommits = int(GitCommits) if GitCommits else 0
    # Create short version string.
    if args.semver:
        result = str(GitMajor) + "." + str(GitMinor) + "." + str(GitPatchBuild + GitCommits)
    else:
        result = str(GitMajor) + "." + str(GitMinor) + "." + str(GitPatchBuild) + "." + str(GitRevision + GitCommits)
    # Append long version string.
    if args.long:
        result += "-" + GitPrerelease if GitPrerelease != "" else GitPrerelease
        result += "+" + GitBuildMetadata + "." + GitCommit
    # Output result version.
    print(result)
    sys.exit(0)

# Check .git folder existence.
GitRoot = proc("git rev-parse --show-toplevel", "", "Cannot determine Git repository root.")
if GitRoot == "":
    returnVersion()

GitDir = join(GitRoot, ".git")
GitCurrentVersion = search(r"\d+\.\d+\.\d+", proc("git --version", GitMinVersion, "Could not determine git version from output. Required minimum git version is " + GitMinVersion + ".")).group(0)
IsGitWorkTree = proc("git rev-parse --is-inside-work-tree", False)
GitIsDirty = proc("git diff --quiet HEAD", 0)
GitRepositoryUrl = sub(r"://[^/]*@", "://", proc("git config --get remote." + GitRemote + ".url", "")) # Get origin address without user and password.

if IsGitWorkTree:
    GitCommonDir = proc("git rev-parse --git-common-dir")

# Get branch and commit information.
GitSha = proc("git -c log.showSignature=false log --format=format:" + GitLongShaFormat + " -n 1", GitDefaultCommit)
GitCommit = proc("git -c log.showSignature=false log --format=format:" + GitShortShaFormat + " -n 1", GitDefaultCommit)
GitCommitDate = proc("git -c log.showSignature=false show --format=%cI -s", "1987-12-24T11:00:00+07:00")
#GitDefaultBranch = proc('git remote show -n origin | sed -n "/HEAD branch/s/.*: /origin\//p"') # Slow way to use remote connection to obtain real default branch.
GitBranch = proc("git rev-parse --abbrev-ref HEAD", proc("git name-rev --name-only --refs=refs/heads/* --no-undefined --always HEAD", GitDefaultBranch))
GitBaseTag = proc("git describe --tags --match=" + GitTagRegex + " --abbrev=0", GitDefaultVersion)
GitBaseTagCommit = proc("git rev-list \"" + GitBaseTag + "\" -n 1", GitDefaultCommit)
GitTag = proc("git describe --match=" + GitTagRegex + " --tags", GitDefaultVersion)

# Calculate base version from branch name.
indexOfSlash = GitBranch.rfind("/")
GitBaseBranch = GitBranch if indexOfSlash < 0 else GitBranch[indexOfSlash + 1:]
GitForkPoint = proc("git merge-base --fork-point \"" + GitDefaultBranch + "\"",
    proc("git merge-base \"" + GitBranch + "\" \"origin/" + GitDefaultBranch + "\"", None))

# Check that the parent branch is selected correctly.
if GitForkPoint == None:
    log("Could not retrieve first commit where branch '" + GitBranch + "' forked from default '" + GitDefaultBranch + "' branch. Use script -b argument to setup default branch of your repository.")
    returnVersion()

# Check if the branch's parent is before the tag.
GitIsAncestor = False if GitForkPoint == GitSha else (True if proc("git merge-base --is-ancestor " + GitForkPoint + " " + GitBaseTag, False) == "" else False)

# Get commits from version file.
if GitVersionFile != "":
    try:
        with open(GitVersionFile) as versionFile:
            GitBaseFile = versionFile.read()
    except:
        GitBaseFile = GitDefaultVersion
    GitVersionMatch = match(GitBaseVersionRegex, GitBaseFile)
    GitLastBump = proc("git -c log.showSignature=false log -n 1 --format=format:" + GitShortShaFormat + " \"" + GitVersionFile + "\"", GitDefaultCommit, "Could not retrieve last commit for " + GitVersionFile + ". Defaulting to its declared version \"" + GitBaseFile + "\" and no additional commits.")
    GitCommits = proc("git rev-list --count --full-history " + GitCommitsIgnoreMerges + " \"" + GitLastBump + "\"..HEAD " + GitRoot, None) if GitLastBump != GitDefaultCommit else None

# Get commits from tag.
GitBranchMatch = match(GitBaseVersionRegex, GitBaseBranch)
if GitCommits == None and not GitIgnoreTagVersion:
    GitVersionMatch = match(GitBaseVersionRegex, GitBaseTag)
    GitCommits = proc("git rev-list --count " + GitCommitsIgnoreMerges + " \"" + GitBaseTagCommit + "\"..\"" + GitCommit + "\"", None) if GitIsAncestor or not GitNotIgnoreBranchVersion or GitBranchMatch == None else None

# Git commits from branch.
if GitCommits == None and GitNotIgnoreBranchVersion and GitBranchMatch:
    GitVersionMatch = GitBranchMatch
    GitCommits = proc("git rev-list --count " + GitCommitsIgnoreMerges + " \"" + GitForkPoint + "\"..HEAD", None)

# Get fallback commits from default version.
if GitCommits == None:
    GitVersionMatch = match(GitBaseVersionRegex, GitDefaultVersion)
    GitCommits = proc("git rev-list --count " + GitCommitsIgnoreMerges + " \"" + GitCommit + "\"", None)

# Write results with versions.
returnVersion()
