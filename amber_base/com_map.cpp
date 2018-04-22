#include "com_map.h"

// CONSTRUCTORS
cOM_Map::cOM_Map()
{
    // Load Default Map
    osuFileName      = ""                  ;
    audioFileName    = "audio.mp3"         ;
    specialStyle     = false               ;
    widescreen       = false               ;
    distanceSpacing  = 1.0                 ;
    beatDivisor      = 4                   ;
    gridSize         = 4                   ;
    timelineZoom     = 1.0                 ;
    title            = "unknownTitle"      ;
    unicodeTitle     = "unknownUTitle"     ;
    artist           = "unknownArtist"     ;
    unicodeArtist    = "unknownUArtist"    ;
    creator          = "unknownCreator"    ;
    difficultyName   = "unknownDifficulty" ;
    source           = ""                  ;
    tags             = QStringList("")     ;
    beatmapID        = 0                   ;
    beatmapSetID     = -1                  ;
    HP               = 5                   ;
    CS               = 5                   ;
    OD               = 5                   ;
    AR               = 5                   ;
    sliderMult       = 1.0                 ;
    sliderTick       = 1                   ;
    bgFileName       = "bg.jpg"            ;
    OM_HOList        = cOM_HOList()        ;
    OM_TPList        = cOM_TPList()        ;
}

// LOADERS
void cOM_Map::loadMap(QString newMapString)
{
    // Convert to StringList then pass to StringList Handler
    loadMap(newMapString.split("\n",QString::KeepEmptyParts));
}
void cOM_Map::loadMap(QFileInfo newMapPath)
{
    // Convert to StringList then pass to StringList Handler
    QStringList mapStringList;
    QFile newMapFile;

    newMapFile.setFileName(newMapPath.filePath());
    if (newMapFile.open(QFile::ReadOnly)) {
        QTextStream mapStream(&newMapFile);
        while (!mapStream.atEnd()) {
            mapStringList.append(mapStream.readLine());
        }
    } else {
        WR_DEBUG("Map cannot be opened. \n"          );
        WR_DEBUG("Map Path: " + newMapFile.fileName());
    }

    newMapFile.close();

    osuFileName = newMapPath.filePath();

    loadMap(mapStringList);
}
void cOM_Map::loadMap(QStringList newMapStringList)
{
    QList<int> indexMapStringList;
    indexMapStringList = findMapSettings(newMapStringList);

    // We use the default value if there is nothing in the QString from QStringList

    audioFileName    = "audio.mp3"         ;
    specialStyle     = false               ;
    widescreen       = false               ;
    distanceSpacing  = 1.0                 ;
    beatDivisor      = 4                   ;
    gridSize         = 4                   ;
    timelineZoom     = 1.0                 ;
    title            = "unknownTitle"      ;
    unicodeTitle     = "unknownUTitle"     ;
    artist           = "unknownArtist"     ;
    unicodeArtist    = "unknownUArtist"    ;
    creator          = "unknownCreator"    ;
    difficultyName   = "unknownDifficulty" ;
    source           = ""                  ;
    tags             = QStringList("")     ;
    beatmapID        = 0                   ;
    beatmapSetID     = -1                  ;
    HP               = 5                   ;
    CS               = 5                   ;
    OD               = 5                   ;
    AR               = 5                   ;
    sliderMult       = 1.0                 ;
    sliderTick       = 1                   ;
    bgFileName       = "bg.jpg"            ;
    OM_HOList        = cOM_HOList()        ;
    OM_TPList        = cOM_TPList()        ;


    if (indexMapStringList[0]  != -1) { audioFileName
                = newMapStringList[indexMapStringList[0]].split(":")[1].simplified(); }
    if (indexMapStringList[1]  != -1) { audioLeadIn
                = newMapStringList[indexMapStringList[0]].split(":")[1].simplified().toInt(); }
    if (indexMapStringList[2]  != -1) { previewTime
                = newMapStringList[indexMapStringList[0]].split(":")[1].simplified().toInt(); }
    if (indexMapStringList[3]  != -1) { countdown
                = bool (newMapStringList[indexMapStringList[0]].split(":")[1].simplified().toInt()); }
    if (indexMapStringList[4]  != -1) { // sampleSet

        QString temp;

        temp = newMapStringList[indexMapStringList[0]].split(":")[1].simplified().toInt();

        if (temp == "None")
        {
            sampleSet = cOM_Map::cSampleSet::AUTO;
        }
        else if (temp == "Soft")
        {
            sampleSet = cOM_Map::cSampleSet::SOFT;
        }
        else if (temp == "Normal")
        {
            sampleSet = cOM_Map::cSampleSet::NORMAL;
        }
        else if (temp == "Drum")
        {
            sampleSet = cOM_Map::cSampleSet::DRUM;
        }
        else
        {
            sampleSet = cOM_Map::cSampleSet::AUTO;
        }
    }
    if (indexMapStringList[5]  != -1) { stackLeniency
                = newMapStringList[indexMapStringList[0]].split(":")[1].simplified().toDouble(); }
    if (indexMapStringList[6]  != -1) { // gameMode
        switch (newMapStringList[indexMapStringList[0]].split(":")[1].simplified().toInt()) {
        case 0:
            gameMode = cGameMode::STANDARD;
            break;
        case 1:
            gameMode = cGameMode::TAIKO;
            break;
        case 2:
            gameMode = cGameMode::CTB;
            break;
        case 3:
            gameMode = cGameMode::MANIA;
            break;
        default:
            gameMode = cGameMode::STANDARD;
            break;
        }
       }
    if (indexMapStringList[7]  != -1) { letterbox
                = bool (newMapStringList[indexMapStringList[0]].split(":")[1].simplified().toInt()); }
    if (indexMapStringList[8]  != -1) { specialStyle
                = bool (newMapStringList[indexMapStringList[8]].split(":")[1].simplified().toInt()); }
    if (indexMapStringList[9]  != -1) { widescreen
                = bool (newMapStringList[indexMapStringList[9]].split(":")[1].simplified().toInt()); }
    if (indexMapStringList[10] != -1) { distanceSpacing
                = newMapStringList[indexMapStringList[10]].split(":")[1].simplified().toDouble(); }
    if (indexMapStringList[11] != -1) { beatDivisor
                = newMapStringList[indexMapStringList[11]].split(":")[1].simplified().toInt(); }
    if (indexMapStringList[12] != -1) { gridSize
                = newMapStringList[indexMapStringList[12]].split(":")[1].simplified().toInt(); }
    if (indexMapStringList[13] != -1) { timelineZoom
                = newMapStringList[indexMapStringList[13]].split(":")[1].simplified().toDouble(); }
    if (indexMapStringList[14] != -1) { title
                =newMapStringList[indexMapStringList[14]].right // We do .right() instead of split just in case parameter contains ':'
                (
                    newMapStringList[indexMapStringList[14]].length() -newMapStringList[indexMapStringList[14]].indexOf(":") - 1
                ).simplified();
    }
    if (indexMapStringList[15] != -1) { unicodeTitle
                =newMapStringList[indexMapStringList[15]].right
                (
                    newMapStringList[indexMapStringList[15]].length() -newMapStringList[indexMapStringList[15]].indexOf(":") - 1
                ).simplified();
    }
    if (indexMapStringList[16] != -1) { artist
                =newMapStringList[indexMapStringList[16]].right
                (
                    newMapStringList[indexMapStringList[16]].length() -newMapStringList[indexMapStringList[16]].indexOf(":") - 1
                ).simplified();
    }
    if (indexMapStringList[17] != -1) { unicodeArtist
                =newMapStringList[indexMapStringList[17]].right
                (
                    newMapStringList[indexMapStringList[17]].length() -newMapStringList[indexMapStringList[17]].indexOf(":") - 1
                ).simplified();
    }
    if (indexMapStringList[18] != -1) { creator
                = newMapStringList[indexMapStringList[18]].split(":")[1].simplified();  }
    if (indexMapStringList[19] != -1) { difficultyName
                = newMapStringList[indexMapStringList[19]].right
                  (
                     newMapStringList[indexMapStringList[19]].length() -newMapStringList[indexMapStringList[19]].indexOf(":") - 1
                  ).simplified();
    }
    if (indexMapStringList[20] != -1) { source
                = newMapStringList[indexMapStringList[20]].right
                  (
                     newMapStringList[indexMapStringList[20]].length() -newMapStringList[indexMapStringList[20]].indexOf(":") - 1
                  ).simplified();
    }
    if (indexMapStringList[21] != -1) { // tags
        QString trimTag;

        trimTag =newMapStringList[indexMapStringList[21]].right
                  (
                     newMapStringList[indexMapStringList[21]].length() -newMapStringList[indexMapStringList[21]].indexOf(":") - 1
                  ).simplified();

        trimTag.replace(",", " "); // Just in case tags are separated by ','
        tags             = trimTag.split(" ",QString::SkipEmptyParts);
    }
    if (indexMapStringList[22] != -1) { beatmapID
                = newMapStringList[indexMapStringList[22]].split(":")[1].simplified().toInt(); }
    if (indexMapStringList[23] != -1) { beatmapSetID
                = newMapStringList[indexMapStringList[23]].split(":")[1].simplified().toInt(); }
    if (indexMapStringList[24] != -1) { HP
                = newMapStringList[indexMapStringList[24]].split(":")[1].simplified().toDouble(); }
    if (indexMapStringList[25] != -1) { CS
                = newMapStringList[indexMapStringList[25]].split(":")[1].simplified().toDouble();
                }
    if (indexMapStringList[26] != -1) { OD
                = newMapStringList[indexMapStringList[26]].split(":")[1].simplified().toDouble(); }
    if (indexMapStringList[27] != -1) { AR
                = newMapStringList[indexMapStringList[27]].split(":")[1].simplified().toDouble(); }
    if (indexMapStringList[28] != -1) { sliderMult
                = newMapStringList[indexMapStringList[28]].split(":")[1].simplified().toDouble(); }
    if (indexMapStringList[29] != -1) { sliderTick
                = newMapStringList[indexMapStringList[29]].split(":")[1].simplified().toInt(); }
    if (indexMapStringList[30] != -1) { // bgFileName
        QString lineBGFileName,
                trimBGFileName;
        int firstQuoteIndex,
            secondQuoteIndex;

        lineBGFileName = newMapStringList[indexMapStringList[30] + 1].simplified();

        firstQuoteIndex = lineBGFileName.indexOf("\"");
        secondQuoteIndex = lineBGFileName.indexOf("\"", firstQuoteIndex + 1);

        trimBGFileName = lineBGFileName.mid(firstQuoteIndex + 1, secondQuoteIndex - firstQuoteIndex - 1);

        bgFileName = trimBGFileName;
                 }
    if (indexMapStringList[31] != -1) { // videoFileName
        QString lineVideoFileName;
        int firstQuoteIndex,
            secondQuoteIndex;

        lineVideoFileName = newMapStringList[indexMapStringList[31]].simplified();

        firstQuoteIndex  = lineVideoFileName.indexOf("\"");
        secondQuoteIndex = lineVideoFileName.indexOf("\"", firstQuoteIndex + 1);

        videoFileName = lineVideoFileName.mid(firstQuoteIndex + 1, secondQuoteIndex - firstQuoteIndex - 1);
                 }
    if (indexMapStringList[32] != -1) { // BreakP

        int startBreakPIndex,
            endBreakPIndex;

        startBreakPIndex = endBreakPIndex = indexMapStringList[32] + 1;

        for (int temp = 0;
             temp < 50; // We assume there are no maps with more than 50 breaks.
             temp ++)
        {
            if (newMapStringList[temp + startBreakPIndex].left(1) == "/"){
                endBreakPIndex = temp + startBreakPIndex - 1;
                break;
            }
        }

        for (int temp = startBreakPIndex; temp <= endBreakPIndex; temp ++)
        {
            if (newMapStringList[temp].simplified() != ""){
                breakPList.append(cOM_BreakP(newMapStringList[temp]));
            }
        }
                 }
    if (indexMapStringList[33] != -1) { // OM_TPList
        int startOM_TPIndex,
            endOM_TPIndex;

        startOM_TPIndex = indexMapStringList[33] + 1;
        endOM_TPIndex = indexMapStringList[34] - 1;

        INF_DEBUG("startOM_TPIndex: " + startOM_TPIndex);
        INF_DEBUG("endOM_TPIndex: "   + endOM_TPIndex  );

        for (int temp = startOM_TPIndex; temp <= endOM_TPIndex; temp ++)
        {
            if (newMapStringList[temp].simplified() != ""){
                OM_TPList.append(cOM_TP(newMapStringList[temp]));
            }
        }

    }
    if (indexMapStringList[34] != -1) { // OM_HOList
        int startOM_HOIndex,
            endOM_HOIndex;

        startOM_HOIndex = indexMapStringList[34] + 1;
        endOM_HOIndex = newMapStringList.length();

        INF_DEBUG("startOM_HOIndex: " + startOM_HOIndex);
        INF_DEBUG("endOM_HOIndex: "   + endOM_HOIndex  );

        for (int temp = startOM_HOIndex; temp < endOM_HOIndex; temp ++)
        {
            if (newMapStringList[temp].simplified() != ""){
                OM_HOList.append(cOM_HO(newMapStringList[temp], CS));
            }
        }
    }


}

// SETTERS

// GETTERS
void cOM_Map::getInfo() const
{
    QString sampleSetStr,
            gameModeStr;

    // CONVERT SAMPLESET TO STR
    switch (sampleSet) {
    case cOM_Map::cSampleSet::AUTO:
        sampleSetStr = "AUTO";
        break;
    case cOM_Map::cSampleSet::SOFT:
        sampleSetStr = "SOFT";
        break;
    case cOM_Map::cSampleSet::NORMAL:
        sampleSetStr = "NORMAL";
        break;
    case cOM_Map::cSampleSet::DRUM:
        sampleSetStr = "DRUM";
        break;
    default:
        break;
    }

    // CONVERT SAMPLESET TO STR
    switch (gameMode) {
    case cOM_Map::cGameMode::STANDARD:
        gameModeStr = "STANDARD";
        break;
    case cOM_Map::cGameMode::TAIKO:
        gameModeStr = "TAIKO";
        break;
    case cOM_Map::cGameMode::CTB:
        gameModeStr = "CTB";
        break;
    case cOM_Map::cGameMode::MANIA:
        gameModeStr = "MANIA";
        break;
    default:
        break;
    }

    INF_DEBUG("[---- Map Info ----]");
    INF_DEBUG("AUDIOFILENAME    : " + audioFileName                   );
    INF_DEBUG("AUDIOLEADIN      : " + QString::number(audioLeadIn    ));
    INF_DEBUG("PREVIEWTIME      : " + QString::number(previewTime    ));
    INF_DEBUG("COUNTDOWN        : " + countdown                       );
    INF_DEBUG("SAMPLESET        : " + sampleSetStr                    );
    INF_DEBUG("STACKLENIENCY    : " + QString::number(stackLeniency  ));
    INF_DEBUG("GAMEMODE         : " + gameModeStr                     );
    INF_DEBUG("LETTERBOX        : " + letterbox                       );
    INF_DEBUG("SPECIALSTYLE     : " + specialStyle                    );
    INF_DEBUG("WIDESCREEN       : " + widescreen                      );
    INF_DEBUG("DISTANCESPACING  : " + QString::number(distanceSpacing));
    INF_DEBUG("BEATDIVISOR      : " + QString::number(beatDivisor    ));
    INF_DEBUG("GRIDSIZE         : " + QString::number(gridSize       ));
    INF_DEBUG("TIMELINEZOOM     : " + QString::number(timelineZoom   ));
    INF_DEBUG("TITLE            : " + title                           );
    INF_DEBUG("UNICODETITLE     : " + unicodeTitle                    );
    INF_DEBUG("ARTIST           : " + artist                          );
    INF_DEBUG("UNICODEARTIST    : " + unicodeArtist                   );
    INF_DEBUG("CREATOR          : " + creator                         );
    INF_DEBUG("DIFFICULTYNAME   : " + difficultyName                  );
    INF_DEBUG("SOURCE           : " + source                          );
    INF_DEBUG("TAGS             : " + tags                            );
    INF_DEBUG("BEATMAPID        : " + QString::number(beatmapID      ));
    INF_DEBUG("BEATMAPSETID     : " + QString::number(beatmapSetID   ));
    INF_DEBUG("HP               : " + QString::number(HP             ));
    INF_DEBUG("CS               : " + QString::number(CS             ));
    INF_DEBUG("OD               : " + QString::number(OD             ));
    INF_DEBUG("AR               : " + QString::number(AR             ));
    INF_DEBUG("SLIDERMULT       : " + QString::number(sliderMult     ));
    INF_DEBUG("SLIDERTICK       : " + QString::number(sliderTick     ));
    INF_DEBUG("BGFILENAME       : " + bgFileName                      );
    INF_DEBUG("VIDEOFILENAME    : " + videoFileName                   );
    INF_DEBUG("BreakPList <SIZE>: " + breakPList.getSize()            );
    INF_DEBUG("OM_TPLIST  <SIZE>: " + OM_TPList.getSize()             );
    INF_DEBUG("OM_HOLIST  <SIZE>: " + OM_HOList.getSize()             );
}

void cOM_Map::copyAudioFileTo(QFileInfo copyLocation)
{
    QFile oldLocation(getAudioFileName());

    if (oldLocation.copy(copyLocation.filePath()))
    {
        ER_DEBUG("Copy Failed.");
    }
}
void cOM_Map::copyOsuFileTo(QFileInfo copyLocation)
{
    QFile oldLocation(getOsuFileName());

    if (oldLocation.copy(copyLocation.filePath()))
    {
        ER_DEBUG("Copy Failed.");
    }
}
void cOM_Map::copyBGFileTo(QFileInfo copyLocation)
{
    QFile oldLocation(getBGFileName());

    if (oldLocation.copy(copyLocation.filePath()))
    {
        ER_DEBUG("Copy Failed.");
    }
}
void cOM_Map::copyAllTo(QFileInfo copyLocation)
{
    copyAudioFileTo(copyLocation);
    copyOsuFileTo(copyLocation);
    copyBGFileTo(copyLocation);
}

// OPERS

// MISC
QList<int> cOM_Map::findMapSettings(QStringList &mapSList)
{
    QList<QRegExp> settingsRegList;
    QList<bool> flagRegList;
    QList<int> output({-1, -1, -1, -1, -1, // 35 elements
                       -1, -1, -1, -1, -1,
                       -1, -1, -1, -1, -1,
                       -1, -1, -1, -1, -1,
                       -1, -1, -1, -1, -1,
                       -1, -1, -1, -1, -1,
                       -1, -1, -1, -1, -1});
    QRegExp REG_audioFileName  ("AudioFilename:.*"),
            REG_audioLeadIn    ("AudioLeadIn:.*"),
            REG_previewTime    ("PreviewTime:.*"),
            REG_countdown      ("Countdown:.*"),
            REG_sampleSet      ("SampleSet:.*"),
            REG_stackLeniency  ("StackLeniency:.*"),
            REG_gameMode       ("Mode:.*"),
            REG_letterbox      ("LetterboxInBreaks:.*"),
            REG_specialStyle   ("SpecialStyle:.*"),
            REG_widescreen     ("WidescreenStoryboard:.*"),
            REG_distanceSpacing("DistanceSpacing:.*"),
            REG_beatDivisor    ("BeatDivisor:.*"),
            REG_gridSize       ("GridSize:.*"),
            REG_timelineZoom   ("TimelineZoom:.*"),
            REG_title          ("Title:.*"),
            REG_unicodeTitle   ("TitleUnicode:.*"),
            REG_artist         ("Artist:.*"),
            REG_unicodeArtist  ("ArtistUnicode:.*"),
            REG_creator        ("Creator:.*"),
            REG_difficultyName ("Version:.*"),
            REG_source         ("Source:.*"),
            REG_tags           ("Tags:.*"),
            REG_beatmapID      ("BeatmapID:.*"),
            REG_beatmapSetID   ("BeatmapSetID:.*"),
            REG_HP             ("HPDrainRate:.*"),
            REG_CS             ("CircleSize:.*"),
            REG_OD             ("OverallDifficulty:.*"),
            REG_AR             ("ApproachRate:.*"),
            REG_sliderMult     ("SliderMultiplier:.*"),
            REG_sliderTick     ("SliderTickRate:.*"),
            REG_bgFileName     ("//Background and Video events"),
            REG_videoFileName  ("Video,.*"),
            REG_breakPList     ("//Break Periods"),
            REG_OM_TPList      (".*TimingPoints.*"),
            REG_OM_HOList      (".*HitObjects.*");

    settingsRegList = {REG_audioFileName  ,
                       REG_audioLeadIn    ,
                       REG_previewTime    ,
                       REG_countdown      ,
                       REG_sampleSet      ,
                       REG_stackLeniency  ,
                       REG_gameMode       ,
                       REG_letterbox      ,
                       REG_specialStyle   ,
                       REG_widescreen     ,
                       REG_distanceSpacing,
                       REG_beatDivisor    ,
                       REG_gridSize       ,
                       REG_timelineZoom   ,
                       REG_title          ,
                       REG_unicodeTitle   ,
                       REG_artist         ,
                       REG_unicodeArtist  ,
                       REG_creator        ,
                       REG_difficultyName ,
                       REG_source         ,
                       REG_tags           ,
                       REG_beatmapID      ,
                       REG_beatmapSetID   ,
                       REG_HP             ,
                       REG_CS             ,
                       REG_OD             ,
                       REG_AR             ,
                       REG_sliderMult     ,
                       REG_sliderTick     ,
                       REG_bgFileName     ,
                       REG_videoFileName  ,
                       REG_breakPList     ,
                       REG_OM_TPList      ,
                       REG_OM_HOList      };

    bool    FLAG_audioFileName   = false,
            FLAG_audioLeadIn     = false,
            FLAG_previewTime     = false,
            FLAG_countdown       = false,
            FLAG_sampleSet       = false,
            FLAG_stackLeniency   = false,
            FLAG_gameMode        = false,
            FLAG_letterbox       = false,
            FLAG_specialStyle    = false,
            FLAG_widescreen      = false,
            FLAG_distanceSpacing = false,
            FLAG_beatDivisor     = false,
            FLAG_gridSize        = false,
            FLAG_timelineZoom    = false,
            FLAG_title           = false,
            FLAG_unicodeTitle    = false,
            FLAG_artist          = false,
            FLAG_unicodeArtist   = false,
            FLAG_creator         = false,
            FLAG_difficultyName  = false,
            FLAG_source          = false,
            FLAG_tags            = false,
            FLAG_beatmapID       = false,
            FLAG_beatmapSetID    = false,
            FLAG_HP              = false,
            FLAG_CS              = false,
            FLAG_OD              = false,
            FLAG_AR              = false,
            FLAG_sliderMult      = false,
            FLAG_sliderTick      = false,
            FLAG_bgFileName      = false,
            FLAG_videoFileName   = false,
            FLAG_breakPList      = false,
            FLAG_OM_TPList       = false,
            FLAG_OM_HOList       = false;

    flagRegList = {FLAG_audioFileName  ,
                   FLAG_audioLeadIn    ,
                   FLAG_previewTime    ,
                   FLAG_countdown      ,
                   FLAG_sampleSet      ,
                   FLAG_stackLeniency  ,
                   FLAG_gameMode       ,
                   FLAG_letterbox      ,
                   FLAG_specialStyle   ,
                   FLAG_widescreen     ,
                   FLAG_distanceSpacing,
                   FLAG_beatDivisor    ,
                   FLAG_gridSize       ,
                   FLAG_timelineZoom   ,
                   FLAG_title          ,
                   FLAG_unicodeTitle   ,
                   FLAG_artist         ,
                   FLAG_unicodeArtist  ,
                   FLAG_creator        ,
                   FLAG_difficultyName ,
                   FLAG_source         ,
                   FLAG_tags           ,
                   FLAG_beatmapID      ,
                   FLAG_beatmapSetID   ,
                   FLAG_HP             ,
                   FLAG_CS             ,
                   FLAG_OD             ,
                   FLAG_AR             ,
                   FLAG_sliderMult     ,
                   FLAG_sliderTick     ,
                   FLAG_bgFileName     ,
                   FLAG_videoFileName  ,
                   FLAG_breakPList     ,
                   FLAG_OM_TPList      ,
                   FLAG_OM_HOList      };

    INF_DEBUG("[---- RegEx Matching ----]");

    for (int tempS = 0; tempS < mapSList.length(); tempS ++)
    {
        for (int tempR = 0; tempR < settingsRegList.length(); tempR ++) {

            if (flagRegList[tempR] == true) // When it is true, that means the parameter has been found
            {
                continue;
            }

            else if (settingsRegList[tempR].exactMatch(mapSList[tempS])) {
                settingsRegList[tempR].setPatternSyntax(QRegExp::Wildcard);

                INF_DEBUG("Pattern : " << settingsRegList[tempR].pattern());
                INF_DEBUG("Match to: " << mapSList[tempS]                 );
                INF_DEBUG("Found at: " << QString::number(tempS)          );

                flagRegList[tempR] = true; // Set to true to skip this parameter next loop
                output[tempR] = tempS; // We return the line number where the parameter is located
            }
        }
    }

    return output;
}


