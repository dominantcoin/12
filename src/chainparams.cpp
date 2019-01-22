// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX Developers
// Copyright (c) 2017-2018 The DMTC Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

bool CheckProofOfWorkGen(uint256 hash, unsigned int nBits)
{
    bool fNegative;
    bool fOverflow;
    uint256 bnTarget;

    //if (Params().SkipProofOfWorkCheck())
    //    return true;

    bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

    // Check range
    if (fNegative || bnTarget == 0 || fOverflow || bnTarget > (~uint256(0) >> 20))
        return false;

    // Check proof of work matches claimed amount
    if (hash > bnTarget)
        return false;

    return true;
}

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

void MineGenesis(CBlock genesis)
{
    printf("Searching for genesis block...\n");
    // This will figure out a valid hash and Nonce if you're
    // creating a different genesis block:
    uint256 hashTarget = ~uint256(0) >> 20;
    uint256 thash;
    while(true)
    {
        thash = genesis.GetHash();
        if (thash <= hashTarget)
            break;
        if ((genesis.nNonce & 0xFFF) == 0)
        {
            printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
        }
        ++genesis.nNonce;
        if (genesis.nNonce == 0)
        {
            printf("NONCE WRAPPED, incrementing time\n");
            ++genesis.nTime;
        }
    }
    printf("block.nTime = %u \n", genesis.nTime);
    printf("block.nNonce = %u \n", genesis.nNonce);
    printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
    printf("block.merkle = %s\n", genesis.hashMerkleRoot.ToString().c_str());
    std::fflush(stdout);
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (0, uint256("0x0000044bc75bdf9982fc32ec19a0a443ea006235ca7ceabb14bf4e2b4b3ca89f"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1545134400, // * UNIX timestamp of last checkpoint block
    0,    // * total number of transactions between genesis and last checkpoint
    //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of(0, uint256("0x000000f351b8525f459c879f1e249b5d3d421b378ac6b760ea8b8e0df2454f33"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1537971708,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of(0, uint256("0x79ba0d9d15d36edee8d07cc300379ec65ab7e12765acd883e870aa618dbcc1a8"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1518723178,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnHexModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
        * The message start string is designed to be unlikely to occur in normal data.
        * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        * a large 4-byte int at any alignment.
        */

        pchMessageStart[0] = 0xdf;
        pchMessageStart[1] = 0xa0;
        pchMessageStart[2] = 0x8d;
        pchMessageStart[3] = 0x8f;
        premineAmt = 2700000 * COIN;

        vAlertPubKey = ParseHex("04ed12e4d3f43dcf7840f551f2485453602ee23689ca0e5b6c3a5ff45a09b3961124cd1a576b6c135046b432477531c64ef19ba6cb471be82f8c99fd5645a124dd");
        nDefaultPort = 51472;
        bnProofOfWorkLimit = ~uint256(0) >> 20;			// DMTC starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 60 * 24 * 365;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 3 * 60;						// DMTC: 1 in 3 minutes
        nTargetSpacing = 3 * 60;						// DMTC: 500sec 
        nMaturity = 20;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 2888888888 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;

        

        nModifierUpdateBlock = 99999999;				// protocol version fix; irrelevant to Dmtc
        nLotteryBlockStartBlock = 99999999;
        nLotteryBlockCycle = 99999999;
        nTreasuryPaymentsStartBlock = 201;
        nTreasuryPaymentsCycle = 60 * 24 * 7;
        nZerocoinStartHeight = 99999999;				// this and following five are all Zerocoin and thus irrelevant to Dmtc
        nZerocoinStartTime = 9999999999;
        nBlockEnforceSerialRange = 99999999;
        nBlockRecalculateAccumulators = 99999999;
        nBlockFirstFraudulent = 99999999;
        nBlockLastGoodCheckpoint = 99999999;

        nBlockEnforceInvalidUTXO = 99999999;			// Start enforcing the invalid UTXO's; may be worth implementing in the future

        /**
        * Build the genesis block. Note that the output of the genesis coinbase cannot
        * be spent as it did not originally exist in the database.
        *
        * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
        *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
        *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
        *   vMerkleTree: e0028e
        */
        const char* pszTimestamp = "DMTC was created for gaming platform dominant chain";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("043360a496ec47307cc8ebc3d59b413626eb8b0cde57d1d9bbc6beda174474c9506fb666c9da4a4d9694bf4e6e422fa0347bb4f73192de3246c02d144db1e47c69") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1545134400;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 868485;
        genesis.payee = txNew.vout[0].scriptPubKey;

        nExtCoinType = 273;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000044bc75bdf9982fc32ec19a0a443ea006235ca7ceabb14bf4e2b4b3ca89f"));
        assert(genesis.hashMerkleRoot == uint256("0xe6bc22d7fda684b086330f78edb1d480dba772514a1ec15949e92c604bf1571d"));

        vSeeds.push_back(CDNSSeedData("104.248.9.25", "104.248.9.25"));
        vSeeds.push_back(CDNSSeedData("159.203.70.14", "159.203.70.14"));
        vSeeds.push_back(CDNSSeedData("68.183.52.73", "68.183.52.73"));
        vSeeds.push_back(CDNSSeedData("188.166.101.109", "188.166.101.109"));
        vSeeds.push_back(CDNSSeedData("68.183.52.141", "68.183.52.141"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 30);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 30 * 60; // fulfilled requests expire in 30 minutes
        strSporkKey = "0448017b7f5cacf585e43acdfdbfbf0087fcb2aa9113b8acdb8459396aaa489e261999dc198e367cfcc9857659f3091f482af1a7d394bd06faf91e213d055c9c8c";
        strObfuscationPoolDummyAddress = "D87q2gC9j6nNrnzCsg4aY6bHMLsT9nUhEw";
        nStartMasternodePayments = 1550102400; //Thursday, 14 February 2019 , 0:00:00

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                          "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                          "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                          "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                          "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                          "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 2;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 2; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

class CBetaParams : public CChainParams
{
public:
    CBetaParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
        * The message start string is designed to be unlikely to occur in normal data.
        * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        * a large 4-byte int at any alignment.
        */

        pchMessageStart[0] = 0xdf;
        pchMessageStart[1] = 0xa0;
        pchMessageStart[2] = 0x8d;
        pchMessageStart[3] = 0x8a;
        premineAmt = 2534320700;

        vAlertPubKey = ParseHex("04af0d2b506206d7205207b7cd7cb855d8061bcd1568b0d1b71ce079d65f0a3797862ec8a1112b722a9ac67966837c64e76669e3defe786b1a4751fa5b42900a1f");
        nDefaultPort = 51472;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // DMTC starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 1000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 3*60; // DMTC: 1 day
        nTargetSpacing = 1 * 3*60;  // DMTC: 1 minute
        nMaturity = 1; //byrdset from 100
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 2535000000 * COIN;

        nLotteryBlockStartBlock = 99999999;
        nLotteryBlockCycle = 60 * 24 * 7; // one week
        nTreasuryPaymentsStartBlock = 99999999;
        nTreasuryPaymentsCycle = 50;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 615800;
        nZerocoinStartHeight = 863787;
        nZerocoinStartTime = 1533945600; // October 17, 2017 4:30:00 AM
        nBlockEnforceSerialRange = 895400; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 891730; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 902850; //Start enforcing the invalid UTXO's

        /**
        * Build the genesis block. Note that the output of the genesis coinbase cannot
        * be spent as it did not originally exist in the database.
        *
        * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
        *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
        *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
        *   vMerkleTree: e0028e
        */
        const char* pszTimestamp = "March 2, 2018 - East And West, Both Coasts Brace For Major Winter Storms";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 8000250 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04bcc3ef3417ba00ab55e3de807a776ade43cbd634a7e2cff383fecc6920cf918b2ad427f6b0a3f8d38f5a41d5dcbf35b394521bd08fcb5f40749df5bfe7d42fe2") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1537971708;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 418873053;
        genesis.payee = txNew.vout[0].scriptPubKey;

        nExtCoinType = 1;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000050d77a86f7a3aa38dfac9c23821ed2c5d3002c2e02f9626c7521cd8ced5"));
        assert(genesis.hashMerkleRoot == uint256("0xb68f3b6cefa827045e8bac505203050c9d247c10d7fe2a951575924427a51052"));

        vSeeds.push_back(CDNSSeedData("104.248.9.25", "104.248.9.25"));
        vSeeds.push_back(CDNSSeedData("159.203.70.14", "159.203.70.14"));
        vSeeds.push_back(CDNSSeedData("68.183.52.73", "68.183.52.73"));
        vSeeds.push_back(CDNSSeedData("188.166.101.109", "188.166.101.109"));
        vSeeds.push_back(CDNSSeedData("68.183.52.141", "68.183.52.141"));
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 30);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
        vFixedSeeds.clear();

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60 * 60; // fulfilled requests expire in 1 hour
        strSporkKey = "";
        strObfuscationPoolDummyAddress = "";
        nStartMasternodePayments = 1550102400; //Thursday, 14 February 2019 , 0:00:00

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                          "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                          "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                          "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                          "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                          "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 2;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 2; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CBetaParams betaParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xdf;
        pchMessageStart[1] = 0xa0;
        pchMessageStart[2] = 0x8d;
        pchMessageStart[3] = 0x8b;
        vAlertPubKey = ParseHex("04af0d2b506206d7205207b7cd7cb855d8061bcd1568b0d1b71ce079d65f0a3797862ec8a1112b722a9ac67966837c64e76669e3defe786b1a4751fa5b42900a1f");
        nDefaultPort = 51476;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 3*60; // DMTC: 1 day
        nTargetSpacing = 1 * 3*60;  // DMTC: 1 minute
        nMaturity = 20;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 99999999;
        nMaxMoneyOut = 2534320700 * COIN;
        premineAmt = 617222416 * COIN;

        nZerocoinStartHeight = 99999999;				// this and following five are all Zerocoin and thus irrelevant to Dmtc
        nZerocoinStartTime = 9999999999;
        nBlockEnforceSerialRange = 99999999;
        nBlockRecalculateAccumulators = 99999999;
        nBlockFirstFraudulent = 99999999;
        nBlockLastGoodCheckpoint = 99999999;

        nBlockEnforceInvalidUTXO = 99999999;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;

        nLotteryBlockStartBlock = 99999999;
        nLotteryBlockCycle = 99999999; // one week
        nTreasuryPaymentsStartBlock = 99999999;
        nTreasuryPaymentsCycle = 99999999;

        nExtCoinType = 1;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1544529601;
        genesis.nNonce = 186087;
        
        pchMessageStart[0] = 0xdf;
        pchMessageStart[1] = 0xa0;
        pchMessageStart[2] = 0x8d;
        pchMessageStart[3] = 0x78;
        vAlertPubKey = ParseHex("04af0d2b506206d7205207b7cd7cb855d8061bcd1568b0d1b71ce079d65f0a3797862ec8a1112b722a9ac67966837c64e76669e3defe786b1a4751fa5b42900a1f");
        nDefaultPort = 51474;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // DMTC starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 1000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 3*60; // DMTC: 1 day
        nTargetSpacing = 1 * 3*60;  // DMTC: 1 minute
        nMaturity = 1; //byrdset from 100
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 2535000000 * COIN;

        nModifierUpdateBlock = 615800;
        nZerocoinStartHeight = 863787;
        nZerocoinStartTime = 1533945600; // October 17, 2017 4:30:00 AM
        nBlockEnforceSerialRange = 895400; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 891730; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 902850; //Start enforcing the invalid UTXO's

        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x00000a39ded6864ce85ef7979c49ce2163048bbfe76be515beb26433294649fd"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet dmtc addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet dmtc script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet dmtc BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet dmtc BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet dmtc BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04b527f93d3ddf83df1f21faec97ccc725b2e8b08efa063b8818e294e57f1ad7ba71a04c1e71485444bdff0b4b0250e3871962dea314e8dbe931ba8bc05a29ce00";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1550102400; //Thursday, 14 February 2019 , 0:00:00
        nBudget_Fee_Confirmations = 2; // Number of confirmations for the finalization fee. We have to make this very short
        // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nSubsidyHalvingInterval = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 1 * 3*60; // Dmtc: 1 day
        nTargetSpacing = 1 * 3*60;        // Dmtc: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1544529600;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 3;

        nLotteryBlockStartBlock = 100;
        nLotteryBlockCycle = 10; // one week
        nTreasuryPaymentsStartBlock = 100;
        nTreasuryPaymentsCycle = 50;

        nExtCoinType = 1;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 51476;
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes

       // assert(hashGenesisBlock == uint256("0x24a086529c39bb777da8b4369042b91ebbeb9b58091b46dc406d3f2a4224ea8f"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    case CBaseChainParams::BETATEST:
        return betaParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
