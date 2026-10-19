# Class Implementation Report: DataLoader

## 1. What class did I create?
I created the DataLoader class.

## 2. Why?
I created the DataLoader class to encapsulate the logic required for reading external CSV files, handling file input/output errors, parsing character-by-character data (such as managing quoted fields), and converting raw text data into structured numerical formats (`std::vector<std::vector<double>>`) required by downstream algorithms like K-Means clustering.

## 3. What data does it hold?
The DataLoader class itself is primarily a service class and does not maintain persistent state variables (no private member variables).
Instead, it processes and holds temporary data locally during execution:
- `dataset`: A 2D vector (`std::vector<std::vector<double>>`) holding rows of numerical values parsed from the CSV
- `row`: A 1D vector (`std::vector<double>`) representing a single data record.
- `cell`: A string accumulator for parsing individual values within a row.
- `inQuotes`: A boolean flag tracking whether the parser is currently inside quotation marks.

## 4. What functions operate on that data?
`loadCSV(const string& filename)`:
- It is a public member function.
- It opens the specified CSV file, skips the header row, iterates through each subsequent line character-by-character to correctly handle commas inside and outside quotes, safely converts string cells into doubles via `stod` (with fallback handling for invalid or out-of-range arguments using `nan`), and returns the complete 2D dataset.

## 5. Why are some members private and others public? How is the class used by the rest of the program?
- **Encapsulation & Design:** The public interface (`loadCSV`) exposes only what other modules need to interact with by passing a filename and receiving the parsed dataset. Although I did not declare explicit private member variables in this implementation snippet, the design naturally isolates local parsing variables (`cell`, `inQuotes`, `row`) inside the scope of the method, preventing outside access or unwanted state modification.
- **Usage in the Program:** The rest of the program invokes `DataLoader::loadCSV("filename.csv")` to bootstrap machine learning or data analysis pipelines, ensuring raw files are cleanly converted into numerical matrices while handling missing or malformed inputs robustly.