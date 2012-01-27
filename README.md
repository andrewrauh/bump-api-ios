Bump API 3.0 - iOS Beta
=======================

This is an all-new version of the Bump iOS API. 

Highlights
==========

* faster, smaller. block/GCD based callbacks.
* multiple concurrent sessions: once two users have matched, they can continue to send data to each other and other users
* at the moment breaks compatibility with earlier versions of the API

Getting Started
=======

1. Agree to the API license agreement and get your API key: http://bu.mp/apiagree
1. Add libBump.a and BumpClient.h to your Xcode project.
1. Ensure that your target is linked against libBump.a, CFNetwork.framework, CoreLocation.framework, and AudioToolbox.framework.
1. Configure your client:
    `[BumpClient configureWithAPIKey:@"your_api_key" andUserID:[[UIDevice currentDevice] name]];`

Congrats, that's it.  Your app is now bumpable!

Notes
=====

1. Use of this library is subject to both our SDK License agreement, http://bu.mp/licagr_internaluse, and Trademark Guidelines: http://bu.mp/apitrademark
1. Android builds coming soon.
1. Please submit comments and questions to tg@bu.mp

Release Notes
=============

Beta 2
------
* callback structure changed: BumpClient calls its `matchBlock` when a match occurs.  In order to create a channel (and send data), both users most call `[[BumpClient sharedClient] confirmMatch:YES onChannel:channel];`. When both users confirm a channel, then `BumpClient` will callback its `channelConfirmedBlock`.
* See updated examples for this new structure
* API key status notification on stderr.

Complete Example
================

```Objective-C
- (void) configureBump {
    // userID is a string that you could use as the user's name, or an ID that is semantic within your environment
    [BumpClient configureWithAPIKey:@"your_api_key" andUserID:[[UIDevice currentDevice] name]];

    [[BumpClient sharedClient] setMatchBlock:^(BumpChannelID channel) { 
		NSLog(@"Matched with user: %@", [[BumpClient sharedClient] userIDForChannel:channel]); 
		[[BumpClient sharedClient] confirmMatch:YES onChannel:channel];
    }];
    
    [[BumpClient sharedClient] setChannelConfirmedBlock:^(BumpChannelID channel) {
		NSLog(@"Channel with %@ confirmed.", [[BumpClient sharedClient] userIDForChannel:channel]);
		[[BumpClient sharedClient] sendData:[[NSString stringWithFormat:@"Hello, world!"] dataUsingEncoding:NSUTF8StringEncoding]
                                  toChannel:channel];
    }];

    [[BumpClient sharedClient] setDataReceivedBlock:^(BumpChannelID channel, NSData *data) {
		NSLog(@"Data received from %@: %@", 
		[[BumpClient sharedClient] userIDForChannel:channel], 
		[NSString stringWithCString:[data bytes] encoding:NSUTF8StringEncoding]);
    }];


    // optional callback
    [[BumpClient sharedClient] setConnectionStateChangedBlock:^(BOOL connected) {
		if (connected) {
			NSLog(@"Bump connected...");
		} else {
			NSLog(@"Bump disconnected...");
		}
    }];

    // optional callback
    [[BumpClient sharedClient] setBumpEventBlock:^(bump_event event) {
		switch(event) {
		    case BUMP_EVENT_BUMP:
				NSLog(@"Bump detected.");
				break;
		    case BUMP_EVENT_NO_MATCH:
				NSLog(@"No match.");
				break;
		}
    }];
} 
```
