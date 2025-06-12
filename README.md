# CS_410_ReverseEngineering

## InvestmentCompanyApp
This project involved reverse-engineering a compiled C++ object file for an investment company application to recreate its source code. The program manages client data, including names and service choices (Brokerage or Retirement), stored in a data structure. The reverse-engineering process required decompiling the object file, analyzing its functionality, and reconstructing the source code with improvements for efficiency, security, and maintainability.

Reverse-Engineering Process
To recreate the application, I followed these steps to decompile the object file and reconstruct the source code:
Decompilation: I used a decompiler tool to analyze the object file and extract its assembly code. This provided a low-level view of the program’s logic, including function calls, data structures, and control flow.

- Function Identification: By examining the assembly, I identified key functions such as user authentication (CheckUserPermissionAccess), client list display (DisplayInfo), and client service modification (ChangeCustomerChoice). I mapped assembly instructions to C++ equivalents, noting function signatures and variable usage.

- Logic Reconstruction: I translated the assembly logic into C++ functions, adding comments to document the purpose of each function and key operations. For example, I noted that the authentication function compared a user-entered password to a hardcoded value, and the display function iterated over a fixed set of clients.

- Commenting: I added detailed comments to the reconstructed functions to explain their purpose and logic, based on the decompiled code. For instance, I commented on the hardcoded password vulnerability and the lack of input validation in the original functions.

### Improvements Made
After reconstructing the original code, I identified several inefficiencies and security issues. I implemented the following improvements to create the current, enhanced version:

- Data Structure Upgrade: Replaced global variables (e.g., name1, num1) with a std::map to store client data as key-value pairs (ID mapped to name and service choice). This improved data access efficiency to O(1) for lookups and updates, compared to linear searches in the original.

- Input Validation: Added parseIntInput and parseStringInput functions to safely parse user inputs, handling stream failures, invalid types, and overly long inputs. For example, parseIntInput uses stoi with error handling to prevent crashes from non-integer inputs.

- Security Enhancements: Replaced the hardcoded plaintext password ("123") with a hashed password comparison using std::hash. This prevents reverse-engineering of the password from the binary. I also added a login attempt limit (3 attempts) to mitigate brute-force attacks.

- Error Handling: Improved error handling in the main loop and ChangeCustomerChoice function by validating input ranges (e.g., client IDs between 1 and 5, service choices between 1 and 2) and providing user feedback for invalid inputs.

- Code Modularity: Refactored the code to follow the single responsibility principle, creating reusable functions like parseIntInput and parseStringInput. This reduced code duplication and improved maintainability.

- Documentation: Enhanced code comments to explain function purposes, input validation, and key logic. For example, I added comments in CheckUserPermissionAccess to describe the hashing process and in DisplayInfo to clarify the use of the std::map.

### Challenges and Solutions
The reverse-engineering process presented challenges, such as identifying the original program’s intent. I used decompilation features and cross-referenced with C++ documentation to map assembly to high-level C++ constructs. For complex logic, I employed a debugger to step through the program’s execution and verify function behavior. Online resources like Stack Overflow helped resolve syntax issues, while experimenting with small test programs clarified the use of std::map and std::hash.

### Lessons Learned
This project deepened my understanding of software design and reverse-engineering. Analyzing the decompiled code highlighted the importance of secure coding practices, such as avoiding hardcoded passwords. I learned that choosing the right data structure, like std::map over arrays for key-based access, significantly improves performance. The project also reinforced the value of modular functions and robust input validation, as the original code’s lack of these led to vulnerabilities. Finally, adding detailed comments during reconstruction made the code easier to understand and maintain, a practice I now prioritize.
The source code for the improved application is available in the provided C++ file, which includes the enhanced main program, input parsing functions, and client management logic with detailed comments.

