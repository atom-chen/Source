#include "Base.h"
#include "audio/include/AudioEngine.h"
#include "SoundManager.h"
#include "TabFileReader.h"

using namespace experimental;

static SoundManager* s_soundManager = nullptr;

SoundManager::~SoundManager()
{
    for (auto& iter : _npcSoundEffectDataMap)
    {
        CC_SAFE_DELETE(iter.second);
    }
    _npcSoundEffectDataMap.clear();
}

SoundManager* SoundManager::getInstance()
{
    if (s_soundManager == nullptr)
    {
        s_soundManager = new SoundManager();
        s_soundManager->init();
    }

    return s_soundManager;
}

bool SoundManager::init()
{
    AudioEngine::lazyInit();

    initBackgroundMusicData();
    initNpcSoundEffectData();
    initBuildingSoundEffectData();

    return true;
}

bool SoundManager::initBackgroundMusicData()
{
    TabFileReader tabFileReader;
    if (tabFileReader.open("BackgroundMusic.tab"))
    {
        for (int i = 0; i < tabFileReader.getRowCount(); i++)
        {
            auto backgroundMusicName = tabFileReader.getString(i, "BackgroundMusicName");
            _backgroundMusicNameList.push_back(backgroundMusicName);
        }
    }

    return true;
}

bool SoundManager::initNpcSoundEffectData()
{
    TabFileReader tabFileReader;
    if (tabFileReader.open("NpcSoundEffect.tab"))
    {
        for (int i = 0; i < tabFileReader.getRowCount(); i++)
        {
            auto npcSoundEffectData = new NpcSoundEffectData();
            npcSoundEffectData->attackName = tabFileReader.getString(i, "AttackEffectName");
            npcSoundEffectData->deathName = tabFileReader.getString(i, "DeathEffectName");

            auto templateName = tabFileReader.getString(i, "TemplateName");
            _npcSoundEffectDataMap[templateName] = npcSoundEffectData;
        }
    }

    return true;
}

bool SoundManager::initBuildingSoundEffectData()
{
    TabFileReader tabFileReader;
    if (tabFileReader.open("BuildingSoundEffect.tab"))
    {
        _buildingSoundEffectData.constructName = tabFileReader.getString(0, "ConstructEffectName");
        _buildingSoundEffectData.destroyedName = tabFileReader.getString(0, "DestroyEffectName");
    }

    return true;
}

void SoundManager::setVolume(float volume)
{
    _volume = std::max(0.0f, volume);
    _volume = std::min(1.0f, volume);
}

float SoundManager::getVolume()
{
    return _volume;
}

void SoundManager::playRandomBackgroundMusicOneByOne()
{
    if (_backgroundMusicNameList.empty())
    {
        return;
    }

    int randomIndex = rand() % (int)_backgroundMusicNameList.size();
    auto backgroundMusicName = _backgroundMusicNameList[randomIndex];

    int audioID = AudioEngine::play2d(backgroundMusicName, false, _volume);
    AudioEngine::setFinishCallback(audioID, CC_CALLBACK_0(SoundManager::playRandomBackgroundMusicOneByOne, this));
}

void SoundManager::playNpcEffect(const string& templateName, NpcSoundEffectType type)
{
    auto npcSoundEffectIter = _npcSoundEffectDataMap.find(templateName);
    if (npcSoundEffectIter != _npcSoundEffectDataMap.end())
    {
        auto npcSoundEffectData = npcSoundEffectIter->second;
        string soundEffectName;
        if (type == NpcSoundEffectType::Attack)
        {
            soundEffectName = npcSoundEffectData->attackName;
        }
        else
        {
            soundEffectName = npcSoundEffectData->deathName;
        }

        AudioEngine::play2d(soundEffectName, false, _volume);
    }
}

void SoundManager::playBuildingEffect(BuildingSoundEffectType type)
{
    if (type == BuildingSoundEffectType::Construct)
    {
        AudioEngine::play2d(_buildingSoundEffectData.constructName, false, _volume);
    }
    else
    {
        AudioEngine::play2d(_buildingSoundEffectData.destroyedName, false, _volume);
    }
}