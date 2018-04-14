#include "com_mapset.h"

// CONSTRUCTORS
cOM_MapSet::cOM_MapSet()
{

}

// LOADERS

// SETTERS
void cOM_MapSet::setOsuFileNameList      (QStringList                newOsuFileNameList    )
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
void cOM_MapSet::setAudioFileNameList    (QStringList                newAudioFileNameList  )
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
void cOM_MapSet::setAudioLeadInList      (QList<int                > newAudioLeadInList    )
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
void cOM_MapSet::setPreviewTimeList      (QList<int                > newPreviewTimeList    )
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
void cOM_MapSet::setCountdownList        (QList<bool               > newCountdownList      )
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
void cOM_MapSet::setSampleSetList        (QList<cOM_Map::cSampleSet> newSampleSetList      )
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
void cOM_MapSet::setStackLeniencyList    (QList<double             > newStackLeniencyList  )
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
void cOM_MapSet::setGameModeList         (QList<cOM_Map::cGameMode > newGameModeList       )
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
void cOM_MapSet::setLetterboxList        (QList<bool               > newLetterboxList      )
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
void cOM_MapSet::setSpecialStyleList     (QList<bool               > newSpecialStyleList   )
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
void cOM_MapSet::setWidescreenList       (QList<bool               > newWidescreenList     )
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
void cOM_MapSet::setDistanceSpacingList  (QList<double             > newDistanceSpacingList)
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
void cOM_MapSet::setBeatDivisorList      (QList<int                > newBeatDivisorList    )
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
void cOM_MapSet::setGridSizeList         (QList<int                > newGridSizeList       )
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
void cOM_MapSet::setTimelineZoomList     (QList<double             > newTimelineZoomList   )
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
void cOM_MapSet::setTitleList            (QStringList                newTitleList          )
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
void cOM_MapSet::setUnicodeTitleList     (QStringList                newUnicodeTitleList   )
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
void cOM_MapSet::setArtistList           (QStringList                newArtistList         )
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
void cOM_MapSet::setUnicodeArtistList    (QStringList                newUnicodeArtistList  )
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
void cOM_MapSet::setCreatorList          (QStringList                newCreatorList        )
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
void cOM_MapSet::setDifficultyNameList   (QStringList                newDifficultyNameList )
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
void cOM_MapSet::setSourceList           (QStringList                newSourceList         )
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
void cOM_MapSet::setTagsList             (QList<QStringList        > newTagsList           )
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
void cOM_MapSet::setBeatmapIDList        (QList<int                > newBeatmapIDList      )
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
void cOM_MapSet::setBeatmapSetIDList     (QList<int                > newBeatmapSetIDList   )
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
void cOM_MapSet::setHPList               (QList<double             > newHPList             )
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
void cOM_MapSet::setCSList               (QList<double             > newCSList             )
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
void cOM_MapSet::setODList               (QList<double             > newODList             )
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
void cOM_MapSet::setARList               (QList<double             > newARList             )
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
void cOM_MapSet::setSliderMultList       (QList<double             > newSliderMultList     )
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
void cOM_MapSet::setSliderTickList       (QList<double             > newSliderTickList     )
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
void cOM_MapSet::setBGFileNameList       (QStringList                newBGFileNameList     )
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
void cOM_MapSet::setVideoFileNameList    (QStringList                newVideoFileNameList  )
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
void cOM_MapSet::setBreakPListList       (QList<cOM_BreakPList     > newBreakPListList     )
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
void cOM_MapSet::setOM_HOListList        (QList<cOM_HOList         > newOM_HOListList      )
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
void cOM_MapSet::setOM_TPListList        (QList<cOM_TPList         > newOM_TPListList      )
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
QStringList               cOM_MapSet::getOsuFileNameList      () const
{
    cOM_Map temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getOsuFileName());
    }

    return output;
}
QStringList               cOM_MapSet::getAudioFileNameList    () const
{
    cOM_Map temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getAudioFileName());
    }

    return output;
}
QList<int                >cOM_MapSet::getAudioLeadInList      () const
{
    cOM_Map temp;
    QList<int> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getAudioLeadIn());
    }

    return output;
}
QList<int                >cOM_MapSet::getPreviewTimeList      () const
{
    cOM_Map temp;
    QList<int> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getPreviewTime());
    }

    return output;
}
QList<bool               >cOM_MapSet::getCountdownList        () const
{
    cOM_Map temp;
    QList<bool> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getCountdown());
    }

    return output;
}
QList<cOM_Map::cSampleSet>cOM_MapSet::getSampleSetList        () const
{
    cOM_Map temp;
    QList<cOM_Map::cSampleSet> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getSampleSet());
    }

    return output;
}
QList<double             >cOM_MapSet::getStackLeniencyList    () const
{
    cOM_Map temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getStackLeniency());
    }

    return output;
}
QList<cOM_Map::cGameMode >cOM_MapSet::getGameModeList         () const
{
    cOM_Map temp;
    QList<cOM_Map::cGameMode> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getGameMode());
    }

    return output;
}
QList<bool               >cOM_MapSet::getLetterboxList        () const
{
    cOM_Map temp;
    QList<bool> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getLetterbox());
    }

    return output;
}
QList<bool               >cOM_MapSet::getSpecialStyleList     () const
{
    cOM_Map temp;
    QList<bool> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getSpecialStyle());
    }

    return output;
}
QList<bool               >cOM_MapSet::getWidescreenList       () const
{
    cOM_Map temp;
    QList<bool> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getWidescreen());
    }

    return output;
}
QList<double             >cOM_MapSet::getDistanceSpacingList  () const
{
    cOM_Map temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getDistanceSpacing());
    }

    return output;
}
QList<int                >cOM_MapSet::getBeatDivisorList      () const
{
    cOM_Map temp;
    QList<int> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getBeatDivisor());
    }

    return output;
}
QList<int                >cOM_MapSet::getGridSizeList         () const
{
    cOM_Map temp;
    QList<int> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getGridSize());
    }

    return output;
}
QList<double             >cOM_MapSet::getTimelineZoomList     () const
{
    cOM_Map temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getTimelineZoom());
    }

    return output;
}
QStringList               cOM_MapSet::getTitleList            () const
{
    cOM_Map temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getTitle());
    }

    return output;
}
QStringList               cOM_MapSet::getUnicodeTitleList     () const
{
    cOM_Map temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getUnicodeTitle());
    }

    return output;
}
QStringList               cOM_MapSet::getArtistList           () const
{
    cOM_Map temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getArtist());
    }

    return output;
}
QStringList               cOM_MapSet::getUnicodeArtistList    () const
{
    cOM_Map temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getUnicodeArtist());
    }

    return output;
}
QStringList               cOM_MapSet::getCreatorList          () const
{
    cOM_Map temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getCreator());
    }

    return output;
}
QStringList               cOM_MapSet::getDifficultyNameList   () const
{
    cOM_Map temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getDifficultyName());
    }

    return output;
}
QStringList               cOM_MapSet::getSourceList           () const
{
    cOM_Map temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getSource());
    }

    return output;
}
QList<QStringList        >cOM_MapSet::getTagsList             () const
{
    cOM_Map temp;
    QList<QStringList> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getTags());
    }

    return output;
}
QList<int                >cOM_MapSet::getBeatmapIDList        () const
{
    cOM_Map temp;
    QList<int> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getBeatmapID());
    }

    return output;
}
QList<int                >cOM_MapSet::getBeatmapSetIDList     () const
{
    cOM_Map temp;
    QList<int> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getBeatmapSetID());
    }

    return output;
}
QList<double             >cOM_MapSet::getHPList               () const
{
    cOM_Map temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getHP());
    }

    return output;
}
QList<double             >cOM_MapSet::getCSList               () const
{
    cOM_Map temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getCS());
    }

    return output;
}
QList<double             >cOM_MapSet::getODList               () const
{
    cOM_Map temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getOD());
    }

    return output;
}
QList<double             >cOM_MapSet::getARList               () const
{
    cOM_Map temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getAR());
    }

    return output;
}
QList<double             >cOM_MapSet::getSliderMultList       () const
{
    cOM_Map temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getSliderMult());
    }

    return output;
}
QList<double             >cOM_MapSet::getSliderTickList       () const
{
    cOM_Map temp;
    QList<double> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getSliderTick());
    }

    return output;
}
QStringList               cOM_MapSet::getBGFileNameList       () const
{
    cOM_Map temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getBGFileName());
    }

    return output;
}
QStringList               cOM_MapSet::getVideoFileNameList    () const
{
    cOM_Map temp;
    QStringList output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getVideoFileName());
    }

    return output;
}
QList<cOM_BreakPList     >cOM_MapSet::getBreakPListList       () const
{
    cOM_Map temp;
    QList<cOM_BreakPList> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getBreakPList());
    }

    return output;
}
QList<cOM_HOList         >cOM_MapSet::getOM_HOListList        () const
{
    cOM_Map temp;
    QList<cOM_HOList> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getOM_HOList());
    }

    return output;
}
QList<cOM_TPList         >cOM_MapSet::getOM_TPListList        () const
{
    cOM_Map temp;
    QList<cOM_TPList> output;
    foreach (temp, OM_MapList)
    {
        output.append(temp.getOM_TPList());
    }

    return output;
}


