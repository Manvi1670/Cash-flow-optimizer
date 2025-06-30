#include <bits/stdc++.h>
using namespace std;

class bank{
    public:
    string name;
    int netAmount;
    set<string> types;
}; 

int getMinIndex(bank listOfNetAmounts[],int numBanks){
    int min=INT_MAX, minIndex=-1;
    for(int i=0;i<numBanks;i++){
        if(listOfNetAmounts[i].netAmount == 0) continue;
        
        if(listOfNetAmounts[i].netAmount < min){
            minIndex = i;
            min = listOfNetAmounts[i].netAmount;
        }
    }
    return minIndex;
}

int getSimpleMaxIndex(bank listOfNetAmounts[],int numBanks){
    int max=INT_MIN, maxIndex=-1;
    for(int i=0;i<numBanks;i++){
        if(listOfNetAmounts[i].netAmount == 0) continue;
        
        if(listOfNetAmounts[i].netAmount > max){
            maxIndex = i;
            max = listOfNetAmounts[i].netAmount;
        }
    }
    return maxIndex;
}

pair<int,string> getMaxIndex(bank listOfNetAmounts[],int numBanks,int minIndex,bank input[],int maxNumTypes){
    int max=INT_MIN;
    int maxIndex=-1;
    string matchingType;
    
    for(int i=0;i<numBanks;i++){
        if(listOfNetAmounts[i].netAmount == 0) continue;
        
        if(listOfNetAmounts[i].netAmount < 0) continue;
        
        vector<string> v(maxNumTypes);
        vector<string>::iterator ls=set_intersection(listOfNetAmounts[minIndex].types.begin(),listOfNetAmounts[minIndex].types.end(), listOfNetAmounts[i].types.begin(),listOfNetAmounts[i].types.end(), v.begin());
        
        if((ls-v.begin())!=0 && max<listOfNetAmounts[i].netAmount ){
            max=listOfNetAmounts[i].netAmount;
            maxIndex=i;
            matchingType = *(v.begin());
        } 
    }
    
    return make_pair(maxIndex,matchingType);
}

void printAns(vector<vector<pair<int,string>>> ansGraph, int numBanks,bank input[]){
    
    cout<<"\nThe transactions for minimum cash flow are as follows : \n\n";
    for(int i=0;i<numBanks;i++){
        for(int j=0;j<numBanks;j++){
            
            if(i==j) continue;
            
            if(ansGraph[i][j].first != 0 && ansGraph[j][i].first != 0){
                
                if(ansGraph[i][j].first == ansGraph[j][i].first){
                    ansGraph[i][j].first=0;
                    ansGraph[j][i].first=0;
                }
                else if(ansGraph[i][j].first > ansGraph[j][i].first){
                    ansGraph[i][j].first -= ansGraph[j][i].first; 
                    ansGraph[j][i].first =0;
                    
                    cout<<input[i].name<<" pays Rs " << ansGraph[i][j].first<< " to "<<input[j].name<<" via "<<ansGraph[i][j].second<<endl;
                }
                else{
                    ansGraph[j][i].first -= ansGraph[i][j].first;
                    ansGraph[i][j].first = 0;
                    
                    cout<<input[j].name<<" pays Rs "<< ansGraph[j][i].first<<" to "<<input[i].name<<" via "<<ansGraph[j][i].second<<endl;
                    
                }
            }
            else if(ansGraph[i][j].first != 0){
                cout<<input[i].name<<" pays Rs "<<ansGraph[i][j].first<<" to "<<input[j].name<<" via "<<ansGraph[i][j].second<<endl;
                
            }
            else if(ansGraph[j][i].first != 0){
                cout<<input[j].name<<" pays Rs "<<ansGraph[j][i].first<<" to "<<input[i].name<<" via "<<ansGraph[j][i].second<<endl;
                
            }
            
            ansGraph[i][j].first = 0;
            ansGraph[j][i].first = 0;
        }
    }
    cout<<"\n";
}

void minimizeCashFlow(int numBanks,bank input[],unordered_map<string,int>& indexOf,int numTransactions,vector<vector<int>>& graph,int maxNumTypes){
    
    bank listOfNetAmounts[numBanks];
    
    for(int b=0;b<numBanks;b++){
        listOfNetAmounts[b].name = input[b].name;
        listOfNetAmounts[b].types = input[b].types;
        
        int amount = 0;
        //incoming edges
        for(int i=0;i<numBanks;i++){
            amount += (graph[i][b]);
        }
        
        //outgoing edges
        for(int j=0;j<numBanks;j++){
            amount += ((-1) * graph[b][j]);
        }
        
        listOfNetAmounts[b].netAmount = amount;
    }
    
    vector<vector<pair<int,string>>> ansGraph(numBanks,vector<pair<int,string>>(numBanks,{0,""}));
    
    int numZeroNetAmounts=0;
    
    for(int i=0;i<numBanks;i++){
        if(listOfNetAmounts[i].netAmount == 0) numZeroNetAmounts++;
    }
    
    while(numZeroNetAmounts!=numBanks){
        
        int minIndex=getMinIndex(listOfNetAmounts, numBanks);
        pair<int,string> maxAns = getMaxIndex(listOfNetAmounts, numBanks, minIndex,input,maxNumTypes);
        
        int maxIndex = maxAns.first;
        
        if(maxIndex == -1){
            
            (ansGraph[minIndex][0].first) += abs(listOfNetAmounts[minIndex].netAmount);
            (ansGraph[minIndex][0].second) = *(input[minIndex].types.begin());
            
            int simpleMaxIndex = getSimpleMaxIndex(listOfNetAmounts, numBanks);
            (ansGraph[0][simpleMaxIndex].first) += abs(listOfNetAmounts[minIndex].netAmount);
            (ansGraph[0][simpleMaxIndex].second) = *(input[simpleMaxIndex].types.begin());
            
            listOfNetAmounts[simpleMaxIndex].netAmount += listOfNetAmounts[minIndex].netAmount;
            listOfNetAmounts[minIndex].netAmount = 0;
            
            if(listOfNetAmounts[minIndex].netAmount == 0) numZeroNetAmounts++;
            
            if(listOfNetAmounts[simpleMaxIndex].netAmount == 0) numZeroNetAmounts++;
            
        }
        else{
            int transactionAmount = min(abs(listOfNetAmounts[minIndex].netAmount), listOfNetAmounts[maxIndex].netAmount);
            
            (ansGraph[minIndex][maxIndex].first) += (transactionAmount);
            (ansGraph[minIndex][maxIndex].second) = maxAns.second;
            
            listOfNetAmounts[minIndex].netAmount += transactionAmount;
            listOfNetAmounts[maxIndex].netAmount -= transactionAmount;
            
            if(listOfNetAmounts[minIndex].netAmount == 0) numZeroNetAmounts++;
            
            if(listOfNetAmounts[maxIndex].netAmount == 0) numZeroNetAmounts++;
        }
        
    }
    
    printAns(ansGraph,numBanks,input);
}

bool readFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    cout<<"\n=== Reading input from file: " << filename << " ===\n";
    
    int numBanks;
    file >> numBanks;
    cout<<"Number of banks: " << numBanks << endl;
    
    bank input[numBanks];
    unordered_map<string,int> indexOf;
    
    int maxNumTypes = 0;
    
    cout<<"\nBank details:\n";
    for(int i=0; i<numBanks; i++){
        file >> input[i].name;
        indexOf[input[i].name] = i;
        
        int numTypes;
        file >> numTypes;
        
        if(i==0) maxNumTypes = numTypes;
        
        cout << input[i].name << " (" << numTypes << " payment modes): ";
        
        string type;
        for(int j=0; j<numTypes; j++){
            file >> type;
            input[i].types.insert(type);
            cout << type << " ";
        }
        cout << endl;
    }
    
    int numTransactions;
    file >> numTransactions;
    cout<<"\nNumber of transactions: " << numTransactions << endl;
    
    vector<vector<int>> graph(numBanks,vector<int>(numBanks,0));
    
    cout<<"\nTransactions:\n";
    for(int i=0; i<numTransactions; i++){
        string debtor, creditor;
        int amount;
        file >> debtor >> creditor >> amount;
        
        if(indexOf.find(debtor) == indexOf.end() || indexOf.find(creditor) == indexOf.end()) {
            cout << "Error: Bank name not found in transaction " << i+1 << endl;
            file.close();
            return false;
        }
        
        graph[indexOf[debtor]][indexOf[creditor]] = amount;
        cout << debtor << " owes " << creditor << ": " << amount << endl;
    }
    
    file.close();
    
    cout<<"\n" << string(50, '=') << endl;
    minimizeCashFlow(numBanks, input, indexOf, numTransactions, graph, maxNumTypes);
    
    return true;
}

void getUserInput() {
    cout<<"\n=== Manual Input Mode ===\n";
    cout<<"Enter the number of banks participating in the transactions.\n";
    int numBanks;
    cin >> numBanks;
    
    bank input[numBanks];
    unordered_map<string,int> indexOf;
    
    cout<<"Enter the details of the banks and transactions as stated:\n";
    cout<<"Bank name, number of payment modes it has and the payment modes.\n";
    cout<<"Bank name and payment modes should not contain spaces\n\n";
    
    int maxNumTypes;
    for(int i=0; i<numBanks; i++){
        if(i==0){
            cout<<"World Bank: ";
        }
        else{
            cout<<"Bank "<<i<<": ";
        }
        cin >> input[i].name;
        indexOf[input[i].name] = i;
        int numTypes;
        cin >> numTypes;
        
        if(i==0) maxNumTypes = numTypes;
        
        string type;
        for(int j=0; j<numTypes; j++){
            cin >> type;
            input[i].types.insert(type);
        }   
    }
    
    cout<<"Enter number of transactions.\n";
    int numTransactions;
    cin >> numTransactions;
    
    vector<vector<int>> graph(numBanks,vector<int>(numBanks,0));
    
    cout<<"Enter the details of each transaction as stated:\n";
    cout<<"Debtor Bank, Creditor Bank and amount\n";
    cout<<"The transactions can be in any order\n";
    for(int i=0; i<numTransactions; i++){
        cout<<(i+1)<<" transaction: ";
        string s1, s2;
        int amount;
        cin >> s1 >> s2 >> amount;
        
        if(indexOf.find(s1) == indexOf.end() || indexOf.find(s2) == indexOf.end()) {
            cout << "Error: Bank name not found. Please check spelling.\n";
            i--; // Retry this transaction
            continue;
        }
        
        graph[indexOf[s1]][indexOf[s2]] = amount;
    }
     
    cout<<"\n" << string(50, '=') << endl;
    minimizeCashFlow(numBanks, input, indexOf, numTransactions, graph, maxNumTypes);
}

int main() 
{ 
    cout<<"\n\t\t\t\t********************* Welcome to CASH FLOW MINIMIZER SYSTEM ***********************\n\n\n";
    cout<<"This system minimizes the number of transactions among multiple banks in different corners of the world that use different modes of payment.\n";
    cout<<"There is one world bank (with all payment modes) to act as an intermediary between banks that have no common mode of payment.\n\n";
    
    cout<<"Choose input method:\n";
    cout<<"1. Read from sample file (sample_input.txt)\n";
    cout<<"2. Enter input manually\n";
    cout<<"3. Try different sample file\n";
    cout<<"Enter your choice (1/2/3): ";
    
    int choice;
    cin >> choice;
    
    switch(choice) {
        case 1: {
            if(!readFromFile("sample_input.txt")) {
                cout<<"Error: Could not read from sample_input.txt\n";
                cout<<"Make sure the file exists in the same directory.\n\n";
                cout<<"Switching to manual input mode...\n";
                getUserInput();
            }
            break;
        }
        case 2: {
            getUserInput();
            break;
        }
        case 3: {
            cout<<"Enter filename: ";
            string filename;
            cin >> filename;
            if(!readFromFile(filename)) {
                cout<<"Error: Could not read from " << filename << endl;
                cout<<"Switching to manual input mode...\n";
                getUserInput();
            }
            break;
        }
        default: {
            cout<<"Invalid choice. Using manual input mode...\n";
            getUserInput();
            break;
        }
    }
    
    return 0; 
}
