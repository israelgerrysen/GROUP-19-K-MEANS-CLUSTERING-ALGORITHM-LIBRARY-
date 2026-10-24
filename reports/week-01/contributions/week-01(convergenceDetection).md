NANDYOWA PATIENCE VALERIA 25/U/0851
# Week 1 Progress Report

## Completed
- Went through the repo layout and read how it was arranged so I could follow the format
- Designed the public interface for the convergence detection component.
- Wrote the header file which declares the ConvergenceDetector class.
- Implemented the logic in ConvergenceDetector.cpp such as:
  - a centroid movement check (Euclidean distance compared against a tolerance)
  - an assignment check (have any labels changed since the last iteration?)
  - a combined stop condition that also stops once a maximum number of iterations is reached
- Wrote a small test program that covers the main pass and fail cases.
- Compiled the tests and ran them. All the checks printed PASS.

## In Progress
- Hooking the detector up to a full K-Means loop. This has to wait until the other modules are ready.
- Picking sensible default values for the tolerance and max iterations by trying them on some sample data.

## Challenges / Blockers
- I couldn't decide whether convergence should be judged by the centroids, the assignments, or both. In the end I gave the class separate methods for each, plus a combined one, so the caller can pick.

## Next Week
- Add the edge-case tests I haven't done yet (empty centroid list, mismatched dimensions and so on).
- Put together a short demo that shows the detector stopping a made-up K-Means run.

## AI Use
- Tool: claude
- Purpose: it helped in understanding convergence detection, what it does and why it is useful
- Reason: i needed to make research on the topic i had been assigned
