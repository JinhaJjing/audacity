/**********************************************************************

 Audacity: A Digital Audio Editor

 SelectionState.h

 **********************************************************************/

#ifndef __AUDACITY_SELECTION_STATE__
#define __AUDACITY_SELECTION_STATE__

class Track;
class TrackList;
class MixerBoard;
class ViewInfo;
#include "MemoryX.h"
#include <vector>

// State relating to the set of selected tracks
class SelectionState
{
public:
   static void SelectTrackLength
      ( ViewInfo &viewInfo, Track &track, bool syncLocked );

   void SelectTrack
      ( Track &track,
        bool selected, bool updateLastPicked, MixerBoard *pMixerBoard );
   // Inclusive range of tracks, the limits specified in either order:
   void SelectRangeOfTracks
      ( TrackList &tracks, Track &sTrack, Track &eTrack,
        MixerBoard *pMixerBoard );
   void SelectNone( TrackList &tracks, MixerBoard *pMixerBoard );
   void ChangeSelectionOnShiftClick
      ( TrackList &tracks, Track &track, MixerBoard *pMixerBoard );
   void HandleListSelection
      ( TrackList &tracks, ViewInfo &viewInfo, Track &track,
        bool shift, bool ctrl, bool syncLocked, MixerBoard *pMixerBoard );

private:
   friend class SelectionStateChanger;

   std::weak_ptr<Track> mLastPickedTrack;
};

// For committing or rolling-back of changes in selectedness of tracks.
// When rolling back, it is assumed that no tracks have been added or removed.
class SelectionStateChanger
{
public:
   SelectionStateChanger( SelectionState &state, TrackList &tracks );
   SelectionStateChanger( const SelectionStateChanger& ) = delete;
   SelectionStateChanger &operator=( const SelectionStateChanger& ) = delete;

   ~SelectionStateChanger();
   void Commit();

private:
   SelectionState *mpState;
   TrackList &mTracks;
   std::weak_ptr<Track> mInitialLastPickedTrack;
   std::vector<bool> mInitialTrackSelection;
};

#endif
