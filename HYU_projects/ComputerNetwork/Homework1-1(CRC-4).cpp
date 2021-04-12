#include <iostream>
#include <bitset>   // header file for bit control
#include <string>   // header file for string control
#include <cstdlib>  // header file for random number generation
#include <ctime>    // header file for seed of random number
using namespace std;

#define GeneratorString "10011" // Generator Bit
#define GeneratorSize 5         // Generator Size is defined in order to use 'bitset'.
#define ErrorHappened false     // 'true' if Error happened while transmitting.

string CRCTransmitter(string DataString);   // Function for CRC Calculation in Transmitter.
string CRCReceiver(string ReceivingString); // Function for CRC Calculation in Receiver.
string ErrorTrigger(string TransmitString); // Function for Triggering Errors on Transmitting Data.

int main(){
    string DataBit;
    cout << "\nOriginal Data Bit is : \t";
    cin >> DataBit; // Input Data Bit Stream.
    cout << endl;

    // Send DataBit to Transmitter and go through CRC Calculation for transmission.
    string TransmittingBit = CRCTransmitter(DataBit); 

    // When transmitting data, Errors can be happened.
    cout << "----- Transmitting Data -----" <<endl << endl;
    if(ErrorHappened){  // If Error is to be happened, send Transmitting Data to Error Trigger.
        TransmittingBit = ErrorTrigger(TransmittingBit);
        cout << "----- Error is Happened -----" << endl << endl;
    }

    // Receiver receives the Transmitted Data and go through CRC Calculation for Original Data.
    string ReceivingBit = TransmittingBit;
    string ReceivedDataBit = CRCReceiver(ReceivingBit);
    cout << "Received Data Bit is : \t" << ReceivedDataBit << endl << endl;

    return 0;
}

// Function for CRC Calculation in Transmitter.
string CRCTransmitter(string DataString){   
    int DataSize = DataString.size();
    int CRCSize = GeneratorSize - 1; // CRC is (Size of Generator - 1) Bits.
    string TempString = DataString;
    for(int i = 0; i < CRCSize; ++i) TempString.push_back('0'); // Put zeros behind, as much as Size of CRC Bit.

    cout << "< Here is CRCTransmitter. >" << endl;
    cout << "Initial Bit is : \t" << TempString << endl;
    cout << "Generator Bit is : \t" << GeneratorString << endl;
    cout << "----- CRC Calculation Start -----" << endl; 
    // CRC Calculation
    string RemainderString = TempString.substr(0, GeneratorSize); // Initialize Remainder with first few bits of Initial Bit.
    int NextBitIndex = GeneratorSize;                             // Index of next bit for each XOR operation.
    while(NextBitIndex < TempString.size()){ // XOR Operation continues until Remainder have last bit of Initial Bit.
        if(RemainderString[0] == '1'){ // If first bit of Remainder is 1, XOR with Generator Bit. Else, skip this process.
            bitset<GeneratorSize> tmp = bitset<GeneratorSize>(RemainderString) ^ bitset<GeneratorSize>(GeneratorString);
            RemainderString = tmp.to_string(); // Update Remainder with the result of XOR Operation.
        }
        RemainderString.erase(0, 1); // Erase first bit of Remainder and get next bit from Initial Bit. (shift to right)
        RemainderString.push_back(TempString[NextBitIndex++]);
    }
    cout << "----- CRC Calculation Ended -----" << endl; 

    string CRCString = RemainderString.erase(0, 1); // CRC becomes the last Remainder Bits.
    string TransmitString = DataString + RemainderString; // Attach CRC Bits behind the Data.
    cout << "CRC Bit is : \t\t" << CRCString << endl;
    cout << "Transmitting Bit is : \t" << TransmitString << endl;
    cout << "CRCTransmitter ended. Return Transmitting Bit." << endl << endl;
    return TransmitString; // Return Bit string for transmission.
}

// Function for CRC Calculation in Receiver.
string CRCReceiver(string ReceivingString){
    cout << "< Here is CRCReceiver. >" << endl;
    cout << "Received Data Bit is : \t" << ReceivingString << endl;
    cout << "Generator Bit is : \t" << GeneratorString << endl; 
    cout << "----- CRC Calculation Start -----" << endl; 

    // CRC Calculation
    string RemainderString = ReceivingString;
    RemainderString = RemainderString.substr(0, GeneratorSize); // Initialize Remainder with first few bits of Initial Bit.
    int NextBitIndex = GeneratorSize;                           // Index of next bit for each XOR operation.
    while(NextBitIndex < ReceivingString.size()){ // XOR Operation continues until Remainder have last bit of Initial Bit.
        if(RemainderString[0] == '1'){ // If first bit of Remainder is 1, XOR with Generator Bit. Else, skip this process.
            bitset<GeneratorSize> tmp = bitset<GeneratorSize>(RemainderString) ^ bitset<GeneratorSize>(GeneratorString);
            RemainderString = tmp.to_string(); // Update Remainder with the result of XOR Operation.       
        }
        RemainderString.erase(0, 1); // Erase first bit of Remainder and get next bit from Initial Bit. (shift to right)
        RemainderString.push_back(ReceivingString[NextBitIndex++]);
    }
    cout << "----- CRC Calculation Ended -----" << endl; 

    string Remainder = RemainderString.erase(0, 1); // Result of Remainder Bits.
    cout << "Remainder Bit is : \t" << Remainder << endl;

    // Check if Remainder is not zero.
    if(bitset<GeneratorSize>(RemainderString).any()){
        cout << "Remainder Check is : \tFALSE" << endl;
        cout << "CRCReceiver ended. Return Received Data Bit." << endl << endl;
        return "(Error Code) Data is Destroied!"; // Return Error Code.
    }

    int DataSize = ReceivingString.size() - (GeneratorSize - 1); // Calculate the Size of Original Bit.
    string ReceivedString = ReceivingString.substr(0, DataSize); // Cut out CRC Bits.
    cout << "Remainder Check is : \tTRUE" << endl;
    cout << "CRCReceiver ended. Return Received Data Bit." << endl << endl;
    return ReceivedString; // Return Received Data.
}

// Function for Triggering Errors on Transmitting Data.
string ErrorTrigger(string TransmitString){
    srand((unsigned int)time(NULL)); // Seed for Random number generation.
    int TransmitDataSize = TransmitString.size();
    int NumberofErrors = (int)rand() % TransmitDataSize + 1; // Random number 1 ~ (Size of Data).
    int ErrorIndexArray[NumberofErrors];

    // Generate (NumberofErrors) number of different indexes.
    for(int i = 0; i < NumberofErrors; ++i){
        ErrorIndexArray[i] = (int)rand() % TransmitDataSize; // Random index of Data.
        for(int j = 0; j < i; ++j){
            if(ErrorIndexArray[j] == ErrorIndexArray[i]){
                --i;
                break;
            }
        }
    }

    // Trigger random number of Errors.
    for(int i = 0; i < NumberofErrors; ++i){ 
        string ErrorBit = bitset<1>(TransmitString[ErrorIndexArray[i]]).flip().to_string(); // Filp the original Bit.
        TransmitString.replace(ErrorIndexArray[i], 1, ErrorBit); // Replace a bit to the Filpped Bit.
    }
    return TransmitString; // Return Error Triggered Transmitting Data.
}