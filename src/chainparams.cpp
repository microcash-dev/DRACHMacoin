// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

//
// Main network
//

unsigned int pnSeed[] =
{
    0x12345678
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0xcf;
        pchMessageStart[1] = 0x05;
        pchMessageStart[2] = 0x67;
        pchMessageStart[3] = 0xea;
        vAlertPubKey = ParseHex("04a82e43bebee0af77bb6d4f830c5b2095b7479a480e91bbbf3547fb261c5e6d1be2c27e3c57503f501480f5027371ec62b2be1b6f00fc746e4b3777259e7f6a78");
        nDefaultPort = 11198;
        nRPCPort = 11199;
        bnProofOfWorkLimit[ALGO_SHA256D] = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_SCRYPT]  = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_GROESTL] = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_X11]     = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_BLAKE]   = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_X13]     = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_X15]     = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 524160; // ~ every 6 months (2880 blocks per day including all algorithms)
        nSubsidyHalvingIntervalNEW = 518400; // ~ every 18 months (960 blocks per day including all algorithms)

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
  
        const char* pszTimestamp = "2014-07-01 EST - An ancient Greek currency unit used during a period of ten centuries.";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 65 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04e941763c7750969e751bee1ffbe96a651a0feb131db046546c219ea40bff40b95077dc9ba1c05af991588772d8daabbda57386c068fb9bc7477c5e28702d5eb9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = BLOCK_VERSION_DEFAULT;
        genesis.nTime    = 1404350340;
        genesis.nBits    = 0x1e0fffff;
        genesis.nNonce   = 4986355;
        
        //// debug print let there be light
	/*
MAIN: 00000f6d06fd7b77751899a8e6ce95b8977545c8304fdf1c42e53a40809aec0d
7c30cc28468aa112a905d7fdef6267ffbb2c9d30b2a37a96aac99e0c65c60875
1e0fffff
CBlock(hash=00000f6d06fd7b77751899a8e6ce95b8977545c8304fdf1c42e53a40809aec0d, ver=2, pow_algo=0, pow_hash=00000f6d06fd7b77751899a8e6ce95b8977545c8304fdf1c42e53a40809aec0d, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=7c30cc28468aa112a905d7fdef6267ffbb2c9d30b2a37a96aac99e0c65c60875, nTime=1404350340, nBits=1e0fffff, nNonce=4986355, vtx=1)
  CTransaction(hash=7c30cc2846, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    CTxIn(COutPoint(0000000000, 4294967295), coinbase 04ffff001d01044c56323031342d30372d303120455354202d20416e20616e6369656e7420477265656b2063757272656e637920756e6974207573656420647572696e67206120706572696f64206f662074656e2063656e7475726965732e)
    CTxOut(nValue=65.00000000, scriptPubKey=04e941763c7750969e751bee1ffbe9)
  vMerkleTree: 7c30cc28468aa112a905d7fdef6267ffbb2c9d30b2a37a96aac99e0c65c60875
	*/
        hashGenesisBlock = genesis.GetHash();
	//uncomment these 4 lines to generate the Genesis Block	
	
	/*	
        while (hashGenesisBlock > bnProofOfWorkLimit[ALGO_SCRYPT].getuint256()){
            if (++genesis.nNonce==0) break;
            hashGenesisBlock = genesis.GetHash();
        }
	
        printf("MAIN: %s\n", hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("%x\n", bnProofOfWorkLimit[ALGO_SHA256D].GetCompact());
        genesis.print();
	*/
	
       
        assert(hashGenesisBlock == uint256("0x00000f6d06fd7b77751899a8e6ce95b8977545c8304fdf1c42e53a40809aec0d"));
        assert(genesis.hashMerkleRoot == uint256("0x7c30cc28468aa112a905d7fdef6267ffbb2c9d30b2a37a96aac99e0c65c60875"));

        vSeeds.push_back(CDNSSeedData("drachmacoin.com", "drachmacoin.com"));
        vSeeds.push_back(CDNSSeedData("192.168.1.6", "192.168.1.6"));


        base58Prefixes[PUBKEY_ADDRESS] = 30; //DRACHMacoin address starts with S
        base58Prefixes[SCRIPT_ADDRESS] = 5;
        base58Prefixes[SECRET_KEY] = 177;

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' 
            const int64 nTwoDays = 2 * 24 * 60 * 60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nTwoDays) - nTwoDays;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0x01;
        pchMessageStart[1] = 0xf5;
        pchMessageStart[2] = 0x55;
        pchMessageStart[3] = 0xa4;
        vAlertPubKey = ParseHex("044adf046e6bc86fb83ef92f261fa3feff9176bd029c5ad4afb5c52ac21f9851f2b2eb861cdbf2c09e0cb97dbf75c6ca5ff6c5df88cfb244c72dba1d44b5a47655");
        nDefaultPort = 29717;
        nRPCPort = 29716;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1392876393;
        genesis.nNonce = 416875379;
        
        //// debug print
        hashGenesisBlock = genesis.GetHash();
	/*
        while (hashGenesisBlock > bnProofOfWorkLimit[ALGO_SHA256D].getuint256()){
        	if (++genesis.nNonce==0) break;
        	hashGenesisBlock = genesis.GetHash();
        }
	*/
        //printf("TEST: %s\n", hashGenesisBlock.ToString().c_str());
        //printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        //genesis.print();
        
        //assert(hashGenesisBlock == uint256("0x"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("testseed1.drachmacoin.org", "testseed1.drachmacoin.org"));

        base58Prefixes[PUBKEY_ADDRESS] = 90;
        base58Prefixes[SCRIPT_ADDRESS] = 188;
        base58Prefixes[SECRET_KEY] = 239;

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0x0f;
        pchMessageStart[2] = 0xa5;
        pchMessageStart[3] = 0x5a;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit[ALGO_SHA256D] = CBigNum(~uint256(0) >> 1);
        bnProofOfWorkLimit[ALGO_SCRYPT]  = CBigNum(~uint256(0) >> 1);
        bnProofOfWorkLimit[ALGO_GROESTL] = CBigNum(~uint256(0) >> 1);
        bnProofOfWorkLimit[ALGO_X11]     = CBigNum(~uint256(0) >> 1);
        bnProofOfWorkLimit[ALGO_BLAKE]   = CBigNum(~uint256(0) >> 1);
        bnProofOfWorkLimit[ALGO_X13]     = CBigNum(~uint256(0) >> 1);
        bnProofOfWorkLimit[ALGO_X15]     = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 4;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        
        //// debug print
        hashGenesisBlock = genesis.GetHash();
        //while (hashGenesisBlock > bnProofOfWorkLimit[ALGO_SHA256D].getuint256()){
        //    if (++genesis.nNonce==0) break;
        //    hashGenesisBlock = genesis.GetHash();
        //}

        //printf("REG: %s\n", hashGenesisBlock.ToString().c_str());
        //printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        //genesis.print();

        //assert(hashGenesisBlock == uint256("0x"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.

        base58Prefixes[PUBKEY_ADDRESS] = 0;
        base58Prefixes[SCRIPT_ADDRESS] = 5;
        base58Prefixes[SECRET_KEY] = 128;
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
