# Clean task.
import sys, os, shutil

# Function to delete folder.
def removeTree(treeName):
    if os.path.exists(treeName):
        shutil.rmtree(treeName)

# Determine solution path and change current directory.
solutionPath = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(solutionPath)

# Fast remove big intermediate folders.
#for entry in os.listdir(solutionPath):
#    path = os.path.join(solutionPath, entry)
#    if not entry.startswith(".") and os.path.isdir(path):
#        removeTree(os.path.join(path, "bin"))
#        removeTree(os.path.join(path, "obj"))

# Additional clean of repository.
os.system("git clean -xdf")

#print("Press any key to exit.")
#input()
sys.exit(0)
