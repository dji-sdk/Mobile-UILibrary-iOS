//
//  DUXPreflightChecklistManager.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DUXObjectProtocol.h"

@class DUXPreflightChecklistItem;
@class DUXPreflightChecklistManager;


/**
 *  Defines the communication between the ChecklistManager and the listeners
 */
@protocol DUXPreflightChecklistManagerListener <NSObject>


/**
 *  Called when an item changes.
 *  
 *  @param item the preflight checklist item
 *  @param manager the preflicht checklist manager
 */
- (void)preflightChecklistManager:(nonnull DUXPreflightChecklistManager *)manager noticedChangesForItem:(nonnull DUXPreflightChecklistItem *)item;

@end


/**
 *  State that each item will report.
 */
typedef NS_ENUM(NSInteger, DUXPreflightChecklistState) {

    /**
     *  Safe.
     */
    DUXPreflightChecklistSafeState,

    /**
     *  Warning.
     */
    DUXPreflightChecklistWarningState,

    /**
     *  Error.
     */
    DUXPreflightChecklistErrorState,

    /**
     *  Pending.
     */
    DUXPreflightChecklistPendingState,
};


/**
 *  The preflight checklist manager class manages the life-cycle of preflight
 *  checklist items, triggers their monitoring activity, and collects their states
 *  in order to produce a decision on whether or not it is advisable to take off. It
 *  is not a UI object, but can be used to produce a preflight checklist UI.
 */
@interface DUXPreflightChecklistManager : NSObject <DUXObjectProtocol>


/**
 *  Preflight checklist is ready to fly.
 */
@property (nonatomic) BOOL isReadyToFly;


/**
 *  Aggregated state of all the items.
 */
@property (nonatomic, readonly) DUXPreflightChecklistState overallState;


/**
 *  Array of the items in the preflight checklist manager
 */
@property (nonatomic, readonly, nonnull) NSArray <DUXPreflightChecklistItem *> *preFlightChecklistItems;



/**
 *  This instance will be prepopulated with a default set of checklist items.
 *  
 *  @return The default configured instance.
 */
+ (nonnull instancetype)defaultManager;


/**
 *  If an item in preflight checklist manager can update it's preferredCameraIndex
 *  setting this  will update all items to this index. Default value is 0.
 */
@property (nonatomic, assign) NSInteger preferredCameraIndex;
/*********************************************************************************/
#pragma mark - Items Management
/*********************************************************************************/


/**
 *  Add a preflight checklist item to the manager.
 *  
 *  @param item The item being added to the checklist
 */
- (void)addChecklistItem:(nullable DUXPreflightChecklistItem *)item;


/**
 *  Add a preflight checklist item to the manager after another pre flight checklist
 *  item already in the list.
 *  
 *  @param itemToInsert The item being added to the checklist
 *  @param itemToInsertAfter The item in the checklist to insert after
 */
- (void)insertChecklistItem:(nullable DUXPreflightChecklistItem *)itemToInsert afterChecklistItem:(nullable DUXPreflightChecklistItem *)itemToInsertAfter;


/**
 *  Add a preflight checklist item to the manager before another pre flight
 *  checklist item already in the list.
 *  
 *  @param itemToInsert The item being added to the checklist
 *  @param itemToInsertBefore The item in the checklist to insert before
 */
- (void)insertCheckListItem:(nullable DUXPreflightChecklistItem *)itemToInsert beforeChecklistItem:(nullable DUXPreflightChecklistItem *)itemToInsertBefore;


/**
 *  Remove a preflight checklist item from the manager.
 *  
 *  @param item The item being removed from the checklist
 */
- (void)removeChecklistItem:(nullable DUXPreflightChecklistItem *)item;


/**
 *  Number of items in the preflight checklist.
 *  
 *  @return The number of items
 */
- (NSInteger)checkListItemCount;


/**
 *  Returns the preflight checklist item at an index.
 *  
 *  @param index Index of desired checklist item.
 *  
 *  @return the preflight checklist item at an index
 */
- (nullable DUXPreflightChecklistItem *)checklistItemAtIndex:(NSInteger)index;

/*********************************************************************************/
#pragma mark - Items Monitoring
/*********************************************************************************/


/**
 *  When you are ready to show the check list, call this method to start activating
 *  the logic of each checklist item.
 */
- (void)startCheckingList;


/**
 *  When you are done with the checklist don't forget to call stopCheckingList.
 */
- (void)stopCheckingList;

/*********************************************************************************/
#pragma mark - Item to Manager communication
/*********************************************************************************/


/**
 *  Method that responds to changes in an item.
 *  
 *  @param item The item that changed.
 *  @param didChangeState Whether the item state changed.
 *  @param didChangeDescription Whether the item description changed.
 */
- (void)item:(nonnull DUXPreflightChecklistItem *)item didChangeState:(BOOL)didChangeState didChangeDescription:(BOOL)didChangeDescription;

/*********************************************************************************/
#pragma mark - Listeners
/*********************************************************************************/


/**
 *  Adds a listener.
 *  
 *  @param listener The listener being added.
 */
- (void)addListener:(nullable id <DUXPreflightChecklistManagerListener>)listener;


/**
 *  Removes a listener.
 *  
 *  @param listener The listener being removed.
 */
- (void)removeListener:(nullable id <DUXPreflightChecklistManagerListener>)listener;

@end
