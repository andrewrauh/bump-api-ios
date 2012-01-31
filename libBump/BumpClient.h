//
//  BumpClient.h
//
//  Created by Thomas Greany on 10/21/11.
//  Copyright 2011 Bump Technologies, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/* an identifier for a Channel. */
typedef unsigned long long BumpChannelID;

typedef enum {
    BUMP_EVENT_BUMP = 0,
    BUMP_EVENT_NO_MATCH = 1,
} bump_event;

/* called after a Bump or No Match is detected. */
typedef void (^BumpEventBlock)(bump_event event);

/* called after a Match has occurred. */
typedef void (^BumpMatchBlock)(BumpChannelID proposedChannelID);

/* called after both parties to a Match have confirmed the proposed Channel */
typedef void (^BumpChannelConfirmedBlock)(BumpChannelID channelID);

/* called when data has been received from the other end of a Channel */
typedef void (^BumpDataReceivedBlock)(BumpChannelID channel, NSData *data);

/* called when the connection to Bump connects or disconnects. */
typedef void (^BumpConnectionStateChangedBlock)(BOOL connectedToBumpServer);

@interface BumpClient : NSObject {}

/* 
 required configuration prior to accessing the sharedClient
 after configuration, the client will attempt to connect to Bump.
 */
+ (void) configureWithAPIKey : (NSString *) key andUserID : (NSString *) userID;


+ (BumpClient *) sharedClient;

/* setters for callback blocks */
- (void) setBumpEventBlock : (BumpEventBlock) bumpEventBlock;
- (void) setMatchBlock : (BumpMatchBlock) matchBlock;
- (void) setChannelConfirmedBlock : (BumpChannelConfirmedBlock) confirmedBlock;
- (void) setDataReceivedBlock : (BumpDataReceivedBlock) dataReceivedBlock;
- (void) setConnectionStateChangedBlock : (BumpConnectionStateChangedBlock) connectionBlock;

/* channel methods */
- (void) confirmMatch : (BOOL) confirmed onChannel : (BumpChannelID) proposedChannelID;
- (void) sendData : (NSData *) data toChannel : (BumpChannelID) channelID;
- (NSString *) userIDForChannel : (BumpChannelID) channelID;

/* turn bumping on/off; defaults to YES. */
@property (nonatomic) BOOL bumpable;

/* bump simulation */
- (void) simulateBump;

/* specify dispatch queue that callback blocks should placed on. if unset, the main queue is used. */
- (void) setCallbackQueue : (dispatch_queue_t) callbackQueue;

@end
