Bump iOS API 3
====

This is an all-new version of the Bump iOS API. 

Highlights
==========

* faster
* smaller
* multiple concurrent sessions: once two users have matched, they can continue to send data to each other and other users
* at the moment breaks compatibility with earlier versions of the API

Getting Started
=======

1. Get your Bump API key: http://bu.mp/apiagree
1. Add libBump.a and BumpClient.h to your Xcode project.
1. Ensure that your target is linked against libBump.a, CoreLocation.framework, and AudioToolbox.framework.
1. Configure your client:
    `[BumpClient configureWithAPIKey:@"your_api_key" andUserID:[[UIDevice currentDevice] name]];`

Congrats, that's it.  Your app is now bumpable!

Complete Example
================

	- (void) configureBump {
	    [BumpClient configureWithAPIKey:@"your_api_key" andUserID:[[UIDevice currentDevice] name]];

	    [[BumpClient sharedClient] setMatchOccurredBlock:^(BumpChannelID channel) { 
		NSLog(@"Matched with user: %@", [[BumpClient sharedClient] userIDForChannel:channel]); 
		
		[[BumpClient sharedClient] sendData:[[NSString stringWithFormat:@"Hello, world!"] dataUsingEncoding:NSUTF8StringEncoding]
					  toChannel:channel];
	    }];

	    [[BumpClient sharedClient] setDataReceivedBlock:^(BumpChannelID channel, NSData *data) {
		NSLog(@"Data received on channel %llu: %@", 
		      channel, 
		      [NSString stringWithCString:[data bytes] encoding:NSUTF8StringEncoding]);
	    }];

	    [[BumpClient sharedClient] setConnectionStateChangedBlock:^(BOOL connected) {
		if (connected) {
			    NSLog(@"Bump connected...");
		} else {
		    NSLog(@"Bump disconnected...");
		}
	    }];

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

Notes
=====

1. Use of this library is subject to both our SDK License agreement, http://bu.mp/licagr_internaluse, and Trademark Guidelines: http://bu.mp/apitrademark
1. Android builds coming soon.
1. Please submit comments and questions to tg@bu.mp
