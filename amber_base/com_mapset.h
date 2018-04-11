#ifndef cMAPSET_H
#define cMAPSET_H

#include "com_map.h"

class  cOM_MapSet
{
public:
    cOM_MapSet();

    QStringList               getOsuFileNameList      () const;
    QStringList               getAudioFileNameList    () const;
    QList<int                >getAudioLeadInList      () const;
    QList<int                >getPreviewTimeList      () const;
    QList<bool               >getCountdownList        () const;
    QList<cOM_Map::cSampleSet>getSampleSetList        () const;
    QList<double             >getStackLeniencyList    () const;
    QList<int                >getGameModeList         () const;
    QList<bool               >getLetterboxList        () const;
    QList<bool               >getSpecialStyleList     () const;
    QList<bool               >getWidescreenList       () const;
    QList<double             >getDistanceSpacingList  () const;
    QList<int                >getBeatDivisorList      () const;
    QList<int                >getGridSizeList         () const;
    QList<double             >getTimelineZoomList     () const;
    QStringList               getTitleList            () const;
    QStringList               getUnicodeTitleList     () const;
    QStringList               getArtistList           () const;
    QStringList               getUnicodeArtistList    () const;
    QStringList               getCreatorList          () const;
    QStringList               getDifficultyNameList   () const;
    QStringList               getSourceList           () const;
    QList<QStringList        >getTagsList             () const;
    QList<int                >getBeatmapIDList        () const;
    QList<int                >getBeatmapSetIDList     () const;
    QList<double             >getHPList               () const;
    QList<double             >getCSList               () const;
    QList<double             >getODList               () const;
    QList<double             >getARList               () const;
    QList<double             >getSliderMultList       () const;
    QList<double             >getSliderTickList       () const;
    QStringList               getBGFileNameList       () const;
    QStringList               getVideoFileNameList    () const;
    QList<cOM_BreakPList     >getBreakPListList       () const;
    QList<cOM_HOList         >getOM_HOListList        () const;
    QList<cOM_TPList         >getOM_TPListList        () const;

    void getOsuFileNameList      (QStringList                newOsuFileNameList    );
    void getAudioFileNameList    (QStringList                newAudioFileNameList  );
    void getAudioLeadInList      (QList<int                > newAudioLeadInList    );
    void getPreviewTimeList      (QList<int                > newPreviewTimeList    );
    void getCountdownList        (QList<bool               > newCountdownList      );
    void getSampleSetList        (QList<cOM_Map::cSampleSet> newSampleSetList      );
    void getStackLeniencyList    (QList<double             > newStackLeniencyList  );
    void getGameModeList         (QList<int                > newGameModeList       );
    void getLetterboxList        (QList<bool               > newLetterboxList      );
    void getSpecialStyleList     (QList<bool               > newSpecialStyleList   );
    void getWidescreenList       (QList<bool               > newWidescreenList     );
    void getDistanceSpacingList  (QList<double             > newDistanceSpacingList);
    void getBeatDivisorList      (QList<int                > newBeatDivisorList    );
    void getGridSizeList         (QList<int                > newGridSizeList       );
    void getTimelineZoomList     (QList<double             > newTimelineZoomList   );
    void getTitleList            (QStringList                newTitleList          );
    void getUnicodeTitleList     (QStringList                newUnicodeTitleList   );
    void getArtistList           (QStringList                newArtistList         );
    void getUnicodeArtistList    (QStringList                newUnicodeArtistList  );
    void getCreatorList          (QStringList                newCreatorList        );
    void getDifficultyNameList   (QStringList                newDifficultyNameList );
    void getSourceList           (QStringList                newSourceList         );
    void getTagsList             (QList<QStringList        > newTagsList           );
    void getBeatmapIDList        (QList<int                > newBeatmapIDList      );
    void getBeatmapSetIDList     (QList<int                > newBeatmapSetIDList   );
    void getHPList               (QList<double             > newHPList             );
    void getCSList               (QList<double             > newCSList             );
    void getODList               (QList<double             > newODList             );
    void getARList               (QList<double             > newARList             );
    void getSliderMultList       (QList<double             > newSliderMultList     );
    void getSliderTickList       (QList<double             > newSliderTickList     );
    void getBGFileNameList       (QStringList                newBGFileNameList     );
    void getVideoFileNameList    (QStringList                newVideoFileNameList  );
    void getBreakPListList       (QList<cOM_BreakPList     > newBreakPListList     );
    void getOM_HOListList        (QList<cOM_HOList         > newOM_HOListList      );
    void getOM_TPListList        (QList<cOM_TPList         > newOM_TPListList      );

private:

    QList<cOM_Map> OM_MapList;


};

#endif // cMAPSET_H
