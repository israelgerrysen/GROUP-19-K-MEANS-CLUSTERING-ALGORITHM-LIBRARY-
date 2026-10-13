​1. What class did you create?
​I created a class named KMeansClusterManager.
​2. Why?
​In procedural programming, cluster management functions and raw data arrays often float around globally, making code difficult to maintain and scale. Creating the KMeansClusterManager class allows us to bundle cluster-specific utility operations—specifically the detection and recovery of empty clusters—into a single, cohesive blueprint. This follows standard object-oriented design principles, making the code reusable and easier to test.
​3. What data does it hold?
​The class manages parameters required to evaluate cluster distribution.
•  ​Data Members:
◦ ​int k: Stores the total number of clusters (K).
◦ ​int dimensions: Stores the dimensionality of the dataset features.

​4. What functions operate on that data?
​The class relies on both public interface functions and private helper functions to process the data:
•  ​Public Member Functions:
◦ ​void processEmptyClusters(const std::vector<std::vector<double>>& data, std::vector<std::vector<double>>& centroids, std::vector<int>& assignments); — The main entry point that checks for empty clusters and triggers reassignments.
•  ​Private Helper Functions:
◦ ​std::vector<int> countClusterPoints(const std::vector<int>& assignments) const; — Counts how many data points belong to each respective cluster.
◦ ​int findFarthestPoint(const std::vector<std::vector<double>>& data, const std::vector<std::vector<double>>& centroids, const std::vector<int>& assignments) const; — Scans the dataset to locate the point furthest from its assigned centroid.
​5. Why are some members private and others public? How is the class used by the rest of the program?
•  ​Access Control Strategy:
◦  ​Public members (processEmptyClusters) form the external interface. They are accessible to the rest of the program (such as main.cpp or your primary K-Means training loop) so the algorithm can easily request empty cluster checks without needing to know how the math is executed. 
◦  ​Private members (helper functions like countClusterPoints and findFarthestPoint) are hidden from the outside world. The rest of the program cannot call them directly. This enforces encapsulation, protecting internal helper logic from being misused or modified improperly elsewhere in the codebase. 
• ​How it is used in the program: During the iterative training loop of your K-Means algorithm (right after the cluster assignment step and before updating the centroid means), your main program instantiates the manager or calls its public method to safeguard against division-by-zero errors