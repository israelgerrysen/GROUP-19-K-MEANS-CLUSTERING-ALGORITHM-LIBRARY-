# WEEK 2 progress report
## COMPLETED
I created a class called KMeansClusterManager in order to detect and and recover empty clusters
The class contains

`int k` : this is the number of clusters that need to be formed

`int max iteretions~` : defines the upper limit of iterrations for the algorithm to converge

`std::vector<std::vector<double>>` : vector storing the cordinates of the cluster centers

## CHALLENGES

Choosing the initial centroids since Kmeans is sensitive to initial positions. This was resolved by picking the positions randomly.

Determining when the loop should stop. this was resolved by implementing a cap on the number of iterations. 

## IN PROGRESS

Rigorous testing and fine tuning the program in order to make sure it produces the desired output with a clear logical flow.

## AI USAGE
Tool: Gemini
Use: To make sure that the correct and logical flow of the programm is maintained in order to produce the desired output.


