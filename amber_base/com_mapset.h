#ifndef cMAPSET_H
#define cMAPSET_H

#include "com_map.h"

class  cOM_MapSet
{
public:
    // CONSTRUCTORS
    cOM_MapSet();

    // SETTERS
    QStringList               getOsuFileNameList      () const;
    QStringList               getAudioFileNameList    () const;
    QList<int                >getAudioLeadInList      () const;
    QList<int                >getPreviewTimeList      () const;
    QList<bool               >getCountdownList        () const;
    QList<cOM_Map::cSampleSet>getSampleSetList        () const;
    QList<double             >getStackLeniencyList    () const;
    QList<cOM_Map::cGameMode> getGameModeList         () const;
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

    void setOsuFileNameList      (QStringList                newOsuFileNameList    );
    void setAudioFileNameList    (QStringList                newAudioFileNameList  );
    void setAudioLeadInList      (QList<int                > newAudioLeadInList    );
    void setPreviewTimeList      (QList<int                > newPreviewTimeList    );
    void setCountdownList        (QList<bool               > newCountdownList      );
    void setSampleSetList        (QList<cOM_Map::cSampleSet> newSampleSetList      );
    void setStackLeniencyList    (QList<double             > newStackLeniencyList  );
    void setGameModeList         (QList<cOM_Map::cGameMode > newGameModeList       );
    void setLetterboxList        (QList<bool               > newLetterboxList      );
    void setSpecialStyleList     (QList<bool               > newSpecialStyleList   );
    void setWidescreenList       (QList<bool               > newWidescreenList     );
    void setDistanceSpacingList  (QList<double             > newDistanceSpacingList);
    void setBeatDivisorList      (QList<int                > newBeatDivisorList    );
    void setGridSizeList         (QList<int                > newGridSizeList       );
    void setTimelineZoomList     (QList<double             > newTimelineZoomList   );
    void setTitleList            (QStringList                newTitleList          );
    void setUnicodeTitleList     (QStringList                newUnicodeTitleList   );
    void setArtistList           (QStringList                newArtistList         );
    void setUnicodeArtistList    (QStringList                newUnicodeArtistList  );
    void setCreatorList          (QStringList                newCreatorList        );
    void setDifficultyNameList   (QStringList                newDifficultyNameList );
    void setSourceList           (QStringList                newSourceList         );
    void setTagsList             (QList<QStringList        > newTagsList           );
    void setBeatmapIDList        (QList<int                > newBeatmapIDList      );
    void setBeatmapSetIDList     (QList<int                > newBeatmapSetIDList   );
    void setHPList               (QList<double             > newHPList             );
    void setCSList               (QList<double             > newCSList             );
    void setODList               (QList<double             > newODList             );
    void setARList               (QList<double             > newARList             );
    void setSliderMultList       (QList<double             > newSliderMultList     );
    void setSliderTickList       (QList<double             > newSliderTickList     );
    void setBGFileNameList       (QStringList                newBGFileNameList     );
    void setVideoFileNameList    (QStringList                newVideoFileNameList  );
    void setBreakPListList       (QList<cOM_BreakPList     > newBreakPListList     );
    void setOM_HOListList        (QList<cOM_HOList         > newOM_HOListList      );
    void setOM_TPListList        (QList<cOM_TPList         > newOM_TPListList      );

    // MISC
    void append(cOM_Map);

private:

    QList<cOM_Map> OM_MapList;


};

#endif // cMAPSET_H
