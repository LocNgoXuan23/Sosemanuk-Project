#include "cryptlib.h"
#include "secblock.h"
#include "sosemanuk.h"
#include "osrng.h"
#include "files.h"
#include "hex.h"

#include <iostream>
#include <string>

#include "cryptlib.h"
#include "sosemanuk.h"

#include <iostream>
#include <array>
#include <cstdint>

#include <sstream>
#include <iomanip>
#include <cstring>
#include <vector>
using namespace std;

void showVector(vector<int> vect) {
    for (int i = 0; i < vect.size(); i++) {
        std::cout << vect[i];
        if (i != vect.size() - 1) std::cout << " ";
    }
    std::cout << endl;
}

void showVector(vector<string> vect) {
    for (int i = 0; i < vect.size(); i++) {
        std::cout << vect[i];
        if (i != vect.size() - 1) std::cout << " ";
    }
    std::cout << endl;
}

vector<int> initialVector(int n) {
    vector<int> result;
    for (int i = 0; i < n; i++) {
        result.push_back(i);
    }
    return result;
}

int main()
{
    using namespace CryptoPP;

    AutoSeededRandomPool prng;
    HexEncoder encoder(new FileSink(std::cout));
    string plain("Sosemanuk stream cipher test"), cipher, recover;

    //string strKey = "xuanloc";
    //string strIv = "123";

    //string strKey("hello world");
    //SecByteBlock key((const byte*)strKey.data(), strKey.size());

    //string strIV("hello world");
    //SecByteBlock iv((const byte*)strIV.data(), strIV.size());

    int keySize = 14;
    int ivSize = 16;
    vector<string> keyByteVector{ "³","¥","Ë","@","Å","\"","R", "w","·","","Ò","w","","ý" };
    vector<string> ivbytevector{ "ê","ö","®","c","c","«","ó","y","(","ô","¥","",">","t","2","d" };

    //showVector(keyByteVector);
    byte keyTmp[] = {'³','¥','Ë','@','Å','"','R','w','·','','Ò','w','','ý'};
    byte IVTmp[] = {'Ê','Ö','®','C','C','«','ó','Y','(','Ô','¥','','>','T','2','D'};
    byte a[14];
    byte k[16];

    for (int i = 0; i < keySize; i++) a[i] = keyTmp[i];
    for (int i = 0; i < ivSize; i++) k[i] = IVTmp[i];

    vector<int> keyIntVect = initialVector(keySize);
    vector<int> IVIntVect = initialVector(ivSize);
    //random_shuffle(keyIntVect.begin(), keyIntVect.end());
    //random_shuffle(IVIntVect.begin(), IVIntVect.end());
    //for (int i = 0; i < keyIntVect.size(); i++) a[i] = keyTmp[keyIntVect[i]];
    //for (int i = 0; i < IVIntVect.size(); i++) k[i] = IVTmp[IVIntVect[i]];

    //stringstream ssKey;
    //for (size_t i = 0; i < keySize; ++i)
    //    ssKey << hex << uppercase << setfill('0') << setw(2 * sizeof(byte)) << static_cast<unsigned>(a[i]);
    //string sKey = ssKey.str();
    //std::cout << sKey << endl;

    //stringstream ssIV;
    //for (size_t i = 0; i < ivSize; ++i)
    //    ssIV << hex << uppercase << setfill('0') << setw(2 * sizeof(byte)) << static_cast<unsigned>(k[i]);
    //string sIV = ssIV.str();
    //std::cout << sIV << endl;

    SecByteBlock key(a, sizeof(a));
    SecByteBlock iv(k, sizeof(k));

    //SecByteBlock key(16);
    //SecByteBlock iv(16);

    //prng.GenerateBlock(key, key.size());
    //prng.GenerateBlock(iv, iv.size());
    //'Ê','Ö','®','C','C','«','ó','Y','(','Ô','¥','','>','T','2','D'
    //'³','¥','Ë','@','Å',''','R','w','·','','Ò','w','','ý




    //std::cout << "Key: ";
    //encoder.Put((const byte*)key.data(), key.size());
    //encoder.MessageEnd();
    //std::cout << endl;

    //std::cout << "IV: ";
    //encoder.Put((const byte*)iv.data(), iv.size());
    //encoder.MessageEnd();
    //std::cout << endl;

    // Encryption object
    Sosemanuk::Encryption enc;
    enc.SetKeyWithIV(key, key.size(), iv, iv.size());

    // Perform the encryption
    cipher.resize(plain.size());
    enc.ProcessData((byte*)&cipher[0], (const byte*)plain.data(), plain.size());

    std::cout << "Cipher: ";
    encoder.Put((const byte*)cipher.data(), cipher.size());
    std::cout << endl;

    const char* tempBuf = (const char*)cipher.data();

    //std::cout << tempBuf[0] << endl;
    //std::cout << hex << int(tempBuf[0]) << endl;
    //std::cout << int(tempBuf[0]) << endl;

    int cipherSize = 28;
    for (int i = 0; i < cipherSize; i++) {
        //std::cout << hex << int(tempBuf[i]);
        int tmp = int(tempBuf[i]);

        ostringstream ss;
        ss << hex << tmp;
        string result = ss.str();

        if (result.length() == 8) result = result.substr(6, 2);
        else if (result.length() == 1) result = "0" + result;
        for (int j = 0; j < result.length(); j++) result[j] = toupper(result[j]);
        std::cout << result;     

        //if (i != 28 - 1) std::cout << "|";
    }
    std::cout << endl;


    //cout << "/////////////////////////////////////////////////////" << endl;
    ///// ///////////////////////////////////////////////////////////
    //string myText;
    //ofstream MyFile("my_ciphers.txt");
    //int numOfGen = 4500;
    //for (int n = 0; n < numOfGen; n++) {
    //    random_shuffle(keyIntVect.begin(), keyIntVect.end());
    //    random_shuffle(IVIntVect.begin(), IVIntVect.end());
    //    for (int i = 0; i < keyIntVect.size(); i++) a[i] = keyTmp[keyIntVect[i]];
    //    for (int i = 0; i < IVIntVect.size(); i++) k[i] = IVTmp[IVIntVect[i]];

    //    SecByteBlock key(a, sizeof(a));
    //    SecByteBlock iv(k, sizeof(k));

    //    Sosemanuk::Encryption enc;
    //    enc.SetKeyWithIV(key, key.size(), iv, iv.size());
    //    cipher.resize(plain.size());
    //    enc.ProcessData((byte*)&cipher[0], (const byte*)plain.data(), plain.size());

    //    std::cout << "Cipher " << n << " : ";
    //    const char* tempBuf = (const char*)cipher.data();
    //    int cipherSize = 28;
    //    string cipher = "";
    //    for (int i = 0; i < cipherSize; i++) {
    //        int tmp = int(tempBuf[i]);

    //        ostringstream ss;
    //        ss << hex << tmp;
    //        string result = ss.str();

    //        if (result.length() == 8) result = result.substr(6, 2);
    //        else if (result.length() == 1) result = "0" + result;
    //        for (int j = 0; j < result.length(); j++) result[j] = toupper(result[j]);
    //        std::cout << result;
    //        cipher.append(result);
    //    }
    //    std::cout << endl;
    //    cout << cipher << endl;
    //    MyFile << cipher;
    //    if (n != numOfGen - 1) MyFile << "\n";
    //}
    //MyFile.close();



    cout << "/////////////////////////////////////////////////////" << endl;
    /// ///////////////////////////////////////////////////////////
    string myText;
    ofstream MyFile("my_ciphers2.txt");
    int numOfGen = 4500;
    for (int n = 0; n < numOfGen; n++) {
        random_shuffle(keyIntVect.begin(), keyIntVect.end());
        random_shuffle(IVIntVect.begin(), IVIntVect.end());
        for (int i = 0; i < keyIntVect.size(); i++) a[i] = keyTmp[keyIntVect[i]];
        for (int i = 0; i < IVIntVect.size(); i++) k[i] = IVTmp[IVIntVect[i]];

        SecByteBlock key(a, sizeof(a));
        SecByteBlock iv(k, sizeof(k));

        Sosemanuk::Encryption enc;
        enc.SetKeyWithIV(key, key.size(), iv, iv.size());
        cipher.resize(plain.size());
        enc.ProcessData((byte*)&cipher[0], (const byte*)plain.data(), plain.size());

        std::cout << "Cipher " << n << " : ";
        const char* tempBuf = (const char*)cipher.data();
        int cipherSize = 28;
        string cipher = "";
        for (int i = 0; i < cipherSize; i++) {
            int tmp = int(tempBuf[i]);

            ostringstream ss;
            ss << hex << tmp;
            string result = ss.str();

            if (result.length() == 8) result = result.substr(6, 2);
            else if (result.length() == 1) result = "0" + result;
            for (int j = 0; j < result.length(); j++) result[j] = toupper(result[j]);
            std::cout << result;
            cipher.append(result);
        }
        std::cout << endl;
        cout << cipher << endl;
        MyFile << cipher;
    }
    MyFile.close();


    return 0;
}