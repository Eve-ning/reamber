#include "osumapset.h"

// CONSTRUCTORS
osuMapSet::osuMapSet()
{

}

// LOADERS

// SETTERS
void osuMapSet::setOsuFileNameList      (QStringList                newOsuFileNameList    )
{
    if (newOsuFileNameList.length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newOsuFileNameList    .length(); temp ++)
    {
        OM_MapList[temp].setOsuFileName        (newOsuFileNameList    [temp]);
    }
}
void osuMapSet::setAudioFileNameList    (QStringList                newAudioFileNameList  )
{
    if (newAudioFileNameList  .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newAudioFileNameList  .length(); temp ++)
    {
        OM_MapList[temp].setAudioFileName      (newAudioFileNameList  [temp]);
    }
}
void osuMapSet::setAudioLeadInList      (QList<int                > newAudioLeadInList    )
{
    if (newAudioLeadInList    .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newAudioLeadInList    .length(); temp ++)
    {
        OM_MapList[temp].setAudioLeadIn        (newAudioLeadInList    [temp]);
    }
}
void osuMapSet::setPreviewTimeList      (QList<int                > newPreviewTimeList    )
{
    if (newPreviewTimeList    .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newPreviewTimeList    .length(); temp ++)
    {
        OM_MapList[temp].setPreviewTime        (newPreviewTimeList    [temp]);
    }
}
void osuMapSet::setCountdownList        (QList<bool               > newCountdownList      )
{
    if (newCountdownList      .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newCountdownList      .length(); temp ++)
    {
        OM_MapList[temp].setCountdown          (newCountdownList      [temp]);
    }
}
void osuMapSet::setSampleSetList        (QList<osuMap::cSampleSet> newSampleSetList      )
{
    if (newSampleSetList      .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newSampleSetList      .length(); temp ++)
    {
        OM_MapList[temp].setSampleSet          (newSampleSetList      [temp]);
    }
}
void osuMapSet::setStackLeniencyList    (QList<double             > newStackLeniencyList  )
{
    if (newStackLeniencyList  .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newStackLeniencyList  .length(); temp ++)
    {
        OM_MapList[temp].setStackLeniency      (newStackLeniencyList  [temp]);
    }
}
void osuMapSet::setGameModeList         (QList<osuMap::cGameMode > newGameModeList       )
{
    if (newGameModeList       .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newGameModeList       .length(); temp ++)
    {
        OM_MapList[temp].setGameMode           (newGameModeList       [temp]);
    }
}
void osuMapSet::setLetterboxList        (QList<bool               > newLetterboxList      )
{
    if (newLetterboxList      .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newLetterboxList      .length(); temp ++)
    {
        OM_MapList[temp].setLetterbox          (newLetterboxList      [temp]);
    }
}
void osuMapSet::setSpecialStyleList     (QList<bool               > newSpecialStyleList   )
{
    if (newSpecialStyleList   .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newSpecialStyleList   .length(); temp ++)
    {
        OM_MapList[temp].setSpecialStyle       (newSpecialStyleList   [temp]);
    }
}
void osuMapSet::setWidescreenList       (QList<bool               > newWidescreenList     )
{
    if (newWidescreenList     .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newWidescreenList     .length(); temp ++)
    {
        OM_MapList[temp].setWidescreen         (newWidescreenList     [temp]);
    }
}
void osuMapSet::setDistanceSpacingList  (QList<double             > newDistanceSpacingList)
{
    if (newDistanceSpacingList.length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newDistanceSpacingList.length(); temp ++)
    {
        OM_MapList[temp].setDistanceSpacing    (newDistanceSpacingList[temp]);
    }
}
void osuMapSet::setBeatDivisorList      (QList<int                > newBeatDivisorList    )
{
    if (newBeatDivisorList    .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newBeatDivisorList    .length(); temp ++)
    {
        OM_MapList[temp].setBeatDivisor        (newBeatDivisorList    [temp]);
    }
}
void osuMapSet::setGridSizeList         (QList<int                > newGridSizeList       )
{
    if (newGridSizeList       .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newGridSizeList       .length(); temp ++)
    {
        OM_MapList[temp].setGridSize           (newGridSizeList       [temp]);
    }
}
void osuMapSet::setTimelineZoomList     (QList<double             > newTimelineZoomList   )
{
    if (newTimelineZoomList   .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newTimelineZoomList   .length(); temp ++)
    {
        OM_MapList[temp].setTimelineZoom       (newTimelineZoomList   [temp]);
    }
}
void osuMapSet::setTitleList            (QStringList                newTitleList          )
{
    if (newTitleList          .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newTitleList          .length(); temp ++)
    {
        OM_MapList[temp].setTitle              (newTitleList          [temp]);
    }
}
void osuMapSet::setUnicodeTitleList     (QStringList                newUnicodeTitleList   )
{
    if (newUnicodeTitleList   .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newUnicodeTitleList   .length(); temp ++)
    {
        OM_MapList[temp].setUnicodeTitle       (newUnicodeTitleList   [temp]);
    }
}
void osuMapSet::setArtistList           (QStringList                newArtistList         )
{
    if (newArtistList         .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newArtistList         .length(); temp ++)
    {
        OM_MapList[temp].setArtist             (newArtistList         [temp]);
    }
}
void osuMapSet::setUnicodeArtistList    (QStringList                newUnicodeArtistList  )
{
    if (newUnicodeArtistList  .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newUnicodeArtistList  .length(); temp ++)
    {
        OM_MapList[temp].setUnicodeArtist      (newUnicodeArtistList  [temp]);
    }
}
void osuMapSet::setCreatorList          (QStringList                newCreatorList        )
{
    if (newCreatorList        .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newCreatorList        .length(); temp ++)
    {
        OM_MapList[temp].setCreator            (newCreatorList        [temp]);
    }
}
void osuMapSet::setDifficultyNameList   (QStringList                newDifficultyNameList )
{
    if (newDifficultyNameList .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newDifficultyNameList .length(); temp ++)
    {
        OM_MapList[temp].setDifficultyName     (newDifficultyNameList [temp]);
    }
}
void osuMapSet::setSourceList           (QStringList                newSourceList         )
{
    if (newSourceList         .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newSourceList         .length(); temp ++)
    {
        OM_MapList[temp].setSource             (newSourceList         [temp]);
    }
}
void osuMapSet::setTagsList             (QList<QStringList        > newTagsList           )
{
    if (newTagsList           .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newTagsList           .length(); temp ++)
    {
        OM_MapList[temp].setTags               (newTagsList           [temp]);
    }
}
void osuMapSet::setBeatmapIDList        (QList<int                > newBeatmapIDList      )
{
    if (newBeatmapIDList      .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newBeatmapIDList      .length(); temp ++)
    {
        OM_MapList[temp].setBeatmapID          (newBeatmapIDList      [temp]);
    }
}
void osuMapSet::setBeatmapSetIDList     (QList<int                > newBeatmapSetIDList   )
{
    if (newBeatmapSetIDList   .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newBeatmapSetIDList   .length(); temp ++)
    {
        OM_MapList[temp].setBeatmapSetID       (newBeatmapSetIDList   [temp]);
    }
}
void osuMapSet::setHPList               (QList<double             > newHPList             )
{
    if (newHPList             .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newHPList             .length(); temp ++)
    {
        OM_MapList[temp].setHP                 (newHPList             [temp]);
    }
}
void osuMapSet::setCSList               (QList<double             > newCSList             )
{
    if (newCSList             .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newCSList             .length(); temp ++)
    {
        OM_MapList[temp].setCS                 (newCSList             [temp]);
    }
}
void osuMapSet::setODList               (QList<double             > newODList             )
{
    if (newODList             .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newODList             .length(); temp ++)
    {
        OM_MapList[temp].setOD                 (newODList             [temp]);
    }
}
void osuMapSet::setARList               (QList<double             > newARList             )
{
    if (newARList             .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newARList             .length(); temp ++)
    {
        OM_MapList[temp].setAR                 (newARList             [temp]);
    }
}
void osuMapSet::setSliderMultList       (QList<double             > newSliderMultList     )
{
    if (newSliderMultList     .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newSliderMultList     .length(); temp ++)
    {
        OM_MapList[temp].setSliderMult         (newSliderMultList     [temp]);
    }
}
void osuMapSet::setSliderTickList       (QList<double             > newSliderTickList     )
{
    if (newSliderTickList     .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newSliderTickList     .length(); temp ++)
    {
        OM_MapList[temp].setSliderTick         (newSliderTickList     [temp]);
    }
}
void osuMapSet::setBGFileNameList       (QStringList                newBGFileNameList     )
{
    if (newBGFileNameList     .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newBGFileNameList     .length(); temp ++)
    {
        OM_MapList[temp].setBGFileName         (newBGFileNameList     [temp]);
    }
}
void osuMapSet::setVideoFileNameList    (QStringList                newVideoFileNameList  )
{
    if (newVideoFileNameList  .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newVideoFileNameList  .length(); temp ++)
    {
        OM_MapList[temp].setVideoFileName      (newVideoFileNameList  [temp]);
    }
}
void osuMapSet::setBreakPListList       (QList<BreakPointList     > newBreakPListList     )
{
    if (newBreakPListList     .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newBreakPListList     .length(); temp ++)
    {
        OM_MapList[temp].setBreakPList             (newBreakPListList     [temp]);
    }
}
void osuMapSet::setOM_HOListList        (QList<HitObjectList         > newOM_HOListList      )
{
    if (newOM_HOListList      .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newOM_HOListList      .length(); temp ++)
    {
        OM_MapList[temp].setOM_HOList              (newOM_HOListList      [temp]);
    }
}
void osuMapSet::setOM_TPListList        (QList<TimingPointList         > newOM_TPListList      )
{
    if (newOM_TPListList      .length() != OM_MapList.length())
    {
        qDebug() << __FUNCTION__ << "Length Mismatch" ;
    }
    for (int temp = 0; temp < newOM_TPListList      .length(); temp ++)
    {
        OM_MapList[temp].setOM_TPList              (newOM_TPListList      [temp]);
    }
}

// GETTERS
QStringList               osuMapSet::getOsuFileNameList      () const
{
    osuMap temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getOsuFileName());
    }

    return output;
}
QStringList               osuMapSet::getAudioFileNameList    () const
{
    osuMap temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getAudioFileName());
    }

    return output;
}
QList<int                >osuMapSet::getAudioLeadInList      () const
{
    osuMap temp;
    QList<int> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getAudioLeadIn());
    }

    return output;
}
QList<int                >osuMapSet::getPreviewTimeList      () const
{
    osuMap temp;
    QList<int> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getPreviewTime());
    }

    return output;
}
QList<bool               >osuMapSet::getCountdownList        () const
{
    osuMap temp;
    QList<bool> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getCountdown());
    }

    return output;
}
QList<osuMap::cSampleSet>osuMapSet::getSampleSetList        () const
{
    osuMap temp;
    QList<osuMap::cSampleSet> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getSampleSet());
    }

    return output;
}
QList<double             >osuMapSet::getStackLeniencyList    () const
{
    osuMap temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getStackLeniency());
    }

    return output;
}
QList<osuMap::cGameMode >osuMapSet::getGameModeList         () const
{
    osuMap temp;
    QList<osuMap::cGameMode> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getGameMode());
    }

    return output;
}
QList<bool               >osuMapSet::getLetterboxList        () const
{
    osuMap temp;
    QList<bool> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getLetterbox());
    }

    return output;
}
QList<bool               >osuMapSet::getSpecialStyleList     () const
{
    osuMap temp;
    QList<bool> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getSpecialStyle());
    }

    return output;
}
QList<bool               >osuMapSet::getWidescreenList       () const
{
    osuMap temp;
    QList<bool> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getWidescreen());
    }

    return output;
}
QList<double             >osuMapSet::getDistanceSpacingList  () const
{
    osuMap temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getDistanceSpacing());
    }

    return output;
}
QList<int                >osuMapSet::getBeatDivisorList      () const
{
    osuMap temp;
    QList<int> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getBeatDivisor());
    }

    return output;
}
QList<int                >osuMapSet::getGridSizeList         () const
{
    osuMap temp;
    QList<int> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getGridSize());
    }

    return output;
}
QList<double             >osuMapSet::getTimelineZoomList     () const
{
    osuMap temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getTimelineZoom());
    }

    return output;
}
QStringList               osuMapSet::getTitleList            () const
{
    osuMap temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getTitle());
    }

    return output;
}
QStringList               osuMapSet::getUnicodeTitleList     () const
{
    osuMap temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getUnicodeTitle());
    }

    return output;
}
QStringList               osuMapSet::getArtistList           () const
{
    osuMap temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getArtist());
    }

    return output;
}
QStringList               osuMapSet::getUnicodeArtistList    () const
{
    osuMap temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getUnicodeArtist());
    }

    return output;
}
QStringList               osuMapSet::getCreatorList          () const
{
    osuMap temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getCreator());
    }

    return output;
}
QStringList               osuMapSet::getDifficultyNameList   () const
{
    osuMap temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getDifficultyName());
    }

    return output;
}
QStringList               osuMapSet::getSourceList           () const
{
    osuMap temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getSource());
    }

    return output;
}
QList<QStringList        >osuMapSet::getTagsList             () const
{
    osuMap temp;
    QList<QStringList> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getTags());
    }

    return output;
}
QList<int                >osuMapSet::getBeatmapIDList        () const
{
    osuMap temp;
    QList<int> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getBeatmapID());
    }

    return output;
}
QList<int                >osuMapSet::getBeatmapSetIDList     () const
{
    osuMap temp;
    QList<int> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getBeatmapSetID());
    }

    return output;
}
QList<double             >osuMapSet::getHPList               () const
{
    osuMap temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getHP());
    }

    return output;
}
QList<double             >osuMapSet::getCSList               () const
{
    osuMap temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getCS());
    }

    return output;
}
QList<double             >osuMapSet::getODList               () const
{
    osuMap temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getOD());
    }

    return output;
}
QList<double             >osuMapSet::getARList               () const
{
    osuMap temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getAR());
    }

    return output;
}
QList<double             >osuMapSet::getSliderMultList       () const
{
    osuMap temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getSliderMult());
    }

    return output;
}
QList<double             >osuMapSet::getSliderTickList       () const
{
    osuMap temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getSliderTick());
    }

    return output;
}
QStringList               osuMapSet::getBGFileNameList       () const
{
    osuMap temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getBGFileName());
    }

    return output;
}
QStringList               osuMapSet::getVideoFileNameList    () const
{
    osuMap temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getVideoFileName());
    }

    return output;
}
QList<BreakPointList     >osuMapSet::getBreakPListList       () const
{
    osuMap temp;
    QList<BreakPointList> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getBreakPList());
    }

    return output;
}
QList<HitObjectList         >osuMapSet::getOM_HOListList        () const
{
    osuMap temp;
    QList<HitObjectList> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getOM_HOList());
    }

    return output;
}
QList<TimingPointList         >osuMapSet::getOM_TPListList        () const
{
    osuMap temp;
    QList<TimingPointList> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getOM_TPList());
    }

    return output;
}


