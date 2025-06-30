# 🏦 Cash Flow Minimizer System

A C++ console application that minimizes the number of transactions among multiple banks in different corners of the world using different payment modes. The system uses a **World Bank** as an intermediary when banks don't share common payment methods.

## 📘 Description

This project implements a sophisticated cash flow optimization algorithm that:
- Calculates **net balances** for each bank from a transaction graph
- Applies a **greedy minimization algorithm** to reduce transaction count
- Handles **payment-mode constraints** using set intersection operations
- Uses **World Bank intermediary** for banks with incompatible payment modes


## 🧠 Algorithm & Data Structures

### Core Algorithm:
1. **Net Balance Calculation**: Computes each bank's net position (inflow - outflow)
2. **Greedy Settlement**: Iteratively pairs minimum debtor with maximum creditor
3. **Payment Mode Matching**: Uses `set_intersection` to find compatible payment methods
4. **World Bank Mediation**: Routes transactions through World Bank when no common payment modes exist

### Key Data Structures:
- **Bank Class**: Stores name, net amount, and supported payment types (set)
- **Adjacency Matrix**: Represents transaction graph
- **Hash Map**: Quick bank name to index mapping
- **STL Sets**: Efficient payment mode storage and intersection

---

## 🧩 Features & Highlights

- ✅ **Flexible Input System**: Read from file or manual input
- ✅ **Multi-Payment Mode Support**: Each bank supports different payment methods
- ✅ **World Bank Intermediary**: Handles incompatible payment mode scenarios  
- ✅ **Net Balance Optimization**: Reduces transaction complexity
- ✅ **Bilateral Transaction Elimination**: Removes redundant mutual payments
- ✅ **Error Handling**: Validates bank names and file operations
- ✅ **Sample Test Cases**: Includes predefined test scenarios

---

## ⚙️ Prerequisites

- C++ compiler (GCC, Clang) with C++11 support or higher
- Standard Template Library (STL) support

---

## 💻 Installation & Building

```bash
# Clone the repository
git clone https://github.com/yourusername/cash-flow-minimizer.git
cd cash-flow-minimizer

# Build using g++
g++ -std=c++11 -o cashflow main.cpp

# For better optimization
g++ -std=c++11 -O2 -o cashflow main.cpp
```

## 🚀 Usage

### Running the Application:
```bash
./cashflow
```

### Input Options:
1. **File Input**: Read from `sample_input.txt` or custom file
2. **Manual Input**: Enter data interactively
3. **Custom File**: Specify your own input file

### Sample Input Format:
```
4                                    // Number of banks
WorldBank 3 Paytm GooglePay AmazonPay // Bank_name num_modes mode1 mode2 mode3
SBI 2 Paytm GooglePay               // Bank_name num_modes mode1 mode2  
HDFC 2 GooglePay AmazonPay          // Bank_name num_modes mode1 mode2
ICICI 1 AmazonPay                   // Bank_name num_modes mode1
3                                    // Number of transactions
SBI HDFC 1000                       // Debtor_bank Creditor_bank Amount
HDFC ICICI 2000                     // Debtor_bank Creditor_bank Amount
ICICI SBI 500                       // Debtor_bank Creditor_bank Amount
```

---

## 📈 Example Walkthrough

**Input:**
```
Banks:
- WorldBank: Paytm, GooglePay, AmazonPay
- SBI: Paytm, GooglePay  
- HDFC: GooglePay, AmazonPay
- ICICI: AmazonPay

Transactions:
- SBI owes HDFC: 1000
- HDFC owes ICICI: 2000  
- ICICI owes SBI: 500
```

**Net Balances:**
- SBI: -500 (owes 500)
- HDFC: -1000 (owes 1000)
- ICICI: +1500 (has excess 1500)

**Optimized Output:**
```
HDFC pays Rs 1000 to ICICI via GooglePay
SBI pays Rs 500 to ICICI via GooglePay
```

**Result**: Reduced from 3 original transactions to 2 optimized transactions using common payment modes.

---



## 👤 Author

**Manvitha Bheemvarapu**
* GitHub: [Profile](https://github.com/Manvi1670)

---


