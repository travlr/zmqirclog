
| [Wednesday 01 December 2010] [00:40:43] <guido_g>	Nate75Sanders: no HWM means: queue all messages as long as memory permits.
| [Wednesday 01 December 2010] [00:41:34] <Nate75Sanders>	guido_g: Fair enough, but that means the documentation is wrong.
| [Wednesday 01 December 2010] [00:41:41] <guido_g>	Nate75Sanders: i think the "no downstream nodes" only applies when there _never_ were one
| [Wednesday 01 December 2010] [00:42:12] <guido_g>	because if there was a connection, then there is a queue and the hwm applies
| [Wednesday 01 December 2010] [00:42:28] <Nate75Sanders>	guido_g: strange....I definitely think the man page should describe this in more detail
| [Wednesday 01 December 2010] [00:42:54] <guido_g>	than attach a fix to the issue or post a patch to the ml
| [Wednesday 01 December 2010] [00:42:54] <Nate75Sanders>	guido_g: could you tell me where you gained this particular understanding of things? so i can read there instead?
| [Wednesday 01 December 2010] [00:43:30] <Nate75Sanders>	guido_g: I'd like to make _sure_ what you're saying is correct (it sounds like it is).
| [Wednesday 01 December 2010] [00:43:49] <guido_g>	Nate75Sanders: easy, hang around here for 3 to 4 month, read the things from the core devs that fly by and you'll know :)
| [Wednesday 01 December 2010] [00:44:10] <Nate75Sanders>	guido_g: understood :)
| [Wednesday 01 December 2010] [00:44:16] <guido_g>	Nate75Sanders: then write a test case and check what'S going on
| [Wednesday 01 December 2010] [00:44:34] <Nate75Sanders>	well, i'm halfway there -- based on my bug report
| [Wednesday 01 December 2010] [00:44:52] <Nate75Sanders>	just need a no-receiver at all case
| [Wednesday 01 December 2010] [00:45:06] <guido_g>	btw, writing a bug report w/o proof (aka test/show case) isn't worth much
| [Wednesday 01 December 2010] [00:45:16] <Nate75Sanders>	you know what? actually i think i tested that earlier
| [Wednesday 01 December 2010] [00:45:45] <Nate75Sanders>	yeah
| [Wednesday 01 December 2010] [00:45:45] <Nate75Sanders>	i did
| [Wednesday 01 December 2010] [00:45:48] <Nate75Sanders>	and i just did now, too
| [Wednesday 01 December 2010] [00:46:02] <Nate75Sanders>	there was never a downstream node
| [Wednesday 01 December 2010] [00:46:06] <Nate75Sanders>	and it still does NOT block
| [Wednesday 01 December 2010] [00:46:09] <guido_g>	then attach your test incl. program to the issue, so that it can be verified
| [Wednesday 01 December 2010] [00:46:17] <Nate75Sanders>	i did
| [Wednesday 01 December 2010] [00:46:21] <Nate75Sanders>	it's in the bug report
| [Wednesday 01 December 2010] [00:46:22] <Nate75Sanders>	2 scripts
| [Wednesday 01 December 2010] [00:46:35] <Nate75Sanders>	you can run the PUSHer without the PULLer and it refutes what you said earlier
| [Wednesday 01 December 2010] [00:47:45] <Nate75Sanders>	when you have a PUSHer, if there's no HWM present (whether or not there ever was) the behavior is that it will not block
| [Wednesday 01 December 2010] [00:47:58] <Nate75Sanders>	sorry, meant to say
| [Wednesday 01 December 2010] [00:48:21] <Nate75Sanders>	if there's no HWM and no receiver (whether or not there ever was a receiver) the behavior is that it will not block
| [Wednesday 01 December 2010] [00:48:51] <Nate75Sanders>	so, I'm not sure where you got your info, but it isn't correct
| [Wednesday 01 December 2010] [00:49:34] <Nate75Sanders>	you can run my code if you don't believe me
| [Wednesday 01 December 2010] [00:49:38] <Nate75Sanders>	maybe i'm crazy somehow
| [Wednesday 01 December 2010] [00:49:42] <Nate75Sanders>	but it's in the bug report
| [Wednesday 01 December 2010] [00:50:36] <Nate75Sanders>	wish sustrik was around....
| [Wednesday 01 December 2010] [00:51:00] <guido_g>	he will be in an hour or so
| [Wednesday 01 December 2010] [00:51:06] <guido_g>	he's an early bird
| [Wednesday 01 December 2010] [00:53:33] <guido_g>	hmm hmm mhmm
| [Wednesday 01 December 2010] [00:53:56] <guido_g>	if you use bind instead of connect on the push side, it works
| [Wednesday 01 December 2010] [00:54:16] <guido_g>	i just used "socket.bind("tcp://127.0.0.1:5555")"
| [Wednesday 01 December 2010] [00:54:23] <guido_g>	and it blocks, as described
| [Wednesday 01 December 2010] [00:55:10] <guido_g>	and with connect the hwm works too
| [Wednesday 01 December 2010] [00:56:14] <guido_g>	so it's more a documentation issue on bind vs connect, i'd say
| [Wednesday 01 December 2010] [00:58:25] <Nate75Sanders>	fair enough
| [Wednesday 01 December 2010] [00:58:27] <guido_g>	Nate75Sanders: just added that as a comment to your issue
| [Wednesday 01 December 2010] [00:58:30] <Nate75Sanders>	i had considered that, but not tested it
| [Wednesday 01 December 2010] [00:58:36] <guido_g>	tz tz tz
| [Wednesday 01 December 2010] [00:58:52] <Nate75Sanders>	i think in one part of the docks they make a big point to say that bind vs connect shouldn't affect socket semantics
| [Wednesday 01 December 2010] [00:59:04] <Nate75Sanders>	just the stable vs non-knowable parts of your architecture
| [Wednesday 01 December 2010] [00:59:11] <Nate75Sanders>	so i really do think that should be dealt with
| [Wednesday 01 December 2010] [00:59:24] <Nate75Sanders>	but good detective work
| [Wednesday 01 December 2010] [00:59:52] <guido_g>	before first coffee
| [Wednesday 01 December 2010] [01:00:02] <Nate75Sanders>	are you in europe?
| [Wednesday 01 December 2010] [01:00:06] <guido_g>	yes
| [Wednesday 01 December 2010] [01:00:19] <Nate75Sanders>	italy?
| [Wednesday 01 December 2010] [01:00:23] <guido_g>	no
| [Wednesday 01 December 2010] [01:00:25] <Nate75Sanders>	oh :)
| [Wednesday 01 December 2010] [01:00:26] <Nate75Sanders>	hehe
| [Wednesday 01 December 2010] [01:00:29] <Nate75Sanders>	I'm in Honolulu
| [Wednesday 01 December 2010] [01:00:34] <Nate75Sanders>	so it's 8PM here
| [Wednesday 01 December 2010] [01:00:37] <guido_g>	*sigh*
| [Wednesday 01 December 2010] [01:00:39] <Nate75Sanders>	"yesterday" :)
| [Wednesday 01 December 2010] [01:00:52] <Nate75Sanders>	moving soon
| [Wednesday 01 December 2010] [01:01:01] <Nate75Sanders>	this is a fun place to live, but not good for hackers
| [Wednesday 01 December 2010] [01:01:23] <Nate75Sanders>	i will miss the weather, though
| [Wednesday 01 December 2010] [01:01:27] <Nate75Sanders>	truly, truly amazing
| [Wednesday 01 December 2010] [01:01:34] <Nate75Sanders>	in the winter it's 75 and sunny
| [Wednesday 01 December 2010] [01:01:36] <guido_g>	given that outside are -7C i tend to be a bit jealous
| [Wednesday 01 December 2010] [01:01:38] <Nate75Sanders>	in the summer, it's 85 and sunny
| [Wednesday 01 December 2010] [01:02:50] <guido_g>	and i need to go to the office soon *shudder*
| [Wednesday 01 December 2010] [01:03:27] <Nate75Sanders>	What kind of place do you work?
| [Wednesday 01 December 2010] [01:03:58] <guido_g>	i'm a freelancer, at the moment i'm working at a local bank
| [Wednesday 01 December 2010] [01:04:04] <Nate75Sanders>	I decided to work for a place that doesn't really do as much code (half code, half sysadmin for an oceanographic science team)
| [Wednesday 01 December 2010] [01:04:06] <Nate75Sanders>	it's been great
| [Wednesday 01 December 2010] [01:04:17] <guido_g>	sounds good
| [Wednesday 01 December 2010] [01:04:18] <Nate75Sanders>	i help them immensely and everything i do is magic
| [Wednesday 01 December 2010] [01:04:21] <Nate75Sanders>	and i have plenty of free time
| [Wednesday 01 December 2010] [01:04:25] <Nate75Sanders>	didn't expect this
| [Wednesday 01 December 2010] [01:04:34] <Nate75Sanders>	i used to work more dev jobs....
| [Wednesday 01 December 2010] [01:04:35] <guido_g>	sounds even better :)
| [Wednesday 01 December 2010] [01:04:39] <Nate75Sanders>	they just left me feeling bad
| [Wednesday 01 December 2010] [01:04:50] <Nate75Sanders>	turning the thing i loved into terrible terrible work
| [Wednesday 01 December 2010] [01:05:03] <Nate75Sanders>	come home.....hardly interested in the computer....
| [Wednesday 01 December 2010] [01:05:12] <Nate75Sanders>	now? i'm happy to dive in and work on something
| [Wednesday 01 December 2010] [01:05:17] <Nate75Sanders>	not tired at the end of a day
| [Wednesday 01 December 2010] [01:05:19] <guido_g>	that's the price to pay, i know that
| [Wednesday 01 December 2010] [01:05:24] <Nate75Sanders>	yeah
| [Wednesday 01 December 2010] [01:07:16] <guido_g>	more coffee
| [Wednesday 01 December 2010] [01:07:28] <Nate75Sanders>	indeed :)
| [Wednesday 01 December 2010] [01:07:34] <Nate75Sanders>	don't work too hard today....
| [Wednesday 01 December 2010] [01:07:36] <Nate75Sanders>	pace yourself
| [Wednesday 01 December 2010] [01:07:48] <guido_g>	hey, it's a bank
| [Wednesday 01 December 2010] [01:07:51] <Nate75Sanders>	your 6 hours is easily worth someone else's 9
| [Wednesday 01 December 2010] [01:07:58] <Nate75Sanders>	deep breaths
| [Wednesday 01 December 2010] [01:07:59] <Nate75Sanders>	;)
| [Wednesday 01 December 2010] [01:08:05] <guido_g>	ahhh... 
| [Wednesday 01 December 2010] [01:08:11] <Nate75Sanders>	mindfulness
| [Wednesday 01 December 2010] [01:08:23] <guido_g>	i should have mentioned that today is my weekend
| [Wednesday 01 December 2010] [01:08:28] <Nate75Sanders>	oh, nice
| [Wednesday 01 December 2010] [01:08:32] <guido_g>	doing only 3 days a week
| [Wednesday 01 December 2010] [01:08:35] <Nate75Sanders>	sweet
| [Wednesday 01 December 2010] [01:08:40] <guido_g>	yeah
| [Wednesday 01 December 2010] [01:08:40] <Nate75Sanders>	hey you have it good, then
| [Wednesday 01 December 2010] [01:09:01] <Nate75Sanders>	i'm about to go half-time/half-salary myself
| [Wednesday 01 December 2010] [01:09:04] <Nate75Sanders>	and move
| [Wednesday 01 December 2010] [01:09:11] <guido_g>	i'm surprised that it worked
| [Wednesday 01 December 2010] [01:09:22] <Nate75Sanders>	which part?
| [Wednesday 01 December 2010] [01:09:25] <guido_g>	as i said, it's a bank
| [Wednesday 01 December 2010] [01:09:31] <guido_g>	the part time thingy
| [Wednesday 01 December 2010] [01:09:37] <Nate75Sanders>	yeah
| [Wednesday 01 December 2010] [01:09:41] <Nate75Sanders>	i am surprised too
| [Wednesday 01 December 2010] [01:09:48] <guido_g>	there not _that_ flexible usually
| [Wednesday 01 December 2010] [01:09:52] <Nate75Sanders>	yep
| [Wednesday 01 December 2010] [01:09:53] <Nate75Sanders>	agreed
| [Wednesday 01 December 2010] [01:09:55] <Nate75Sanders>	my dad runs a bank
| [Wednesday 01 December 2010] [01:10:23] <guido_g>	ahh so you know a little
| [Wednesday 01 December 2010] [01:11:29] <Nate75Sanders>	so what do you do with your spare time?
| [Wednesday 01 December 2010] [01:12:13] <guido_g>	reading funny irc channels on obscure software things, linke brokerless messaging and such
| [Wednesday 01 December 2010] [01:12:28] <guido_g>	noone will ever need this shit! :)
| [Wednesday 01 December 2010] [01:13:36] <Nate75Sanders>	haha
| [Wednesday 01 December 2010] [01:13:38] <Nate75Sanders>	nice
| [Wednesday 01 December 2010] [01:16:06] <guido_g>	i'd have a project using all this fun stuff -- if i would be better sales guy
| [Wednesday 01 December 2010] [04:21:15] <mikko>	good morning
| [Wednesday 01 December 2010] [04:27:55] <CIA-20>	zeromq2: 03Martin Lucina 07maint * r289b1f5 10/ src/kqueue.cpp : 
| [Wednesday 01 December 2010] [04:27:55] <CIA-20>	zeromq2: Remove unnecessary cast in kevent_delete
| [Wednesday 01 December 2010] [04:27:55] <CIA-20>	zeromq2: Fixes the build on NetBSD where the compiler complains about casting NULL
| [Wednesday 01 December 2010] [04:27:55] <CIA-20>	zeromq2: to (int).
| [Wednesday 01 December 2010] [04:27:55] <CIA-20>	zeromq2: Signed-off-by: Martin Lucina <mato@kotelna.sk> - http://bit.ly/esACki
| [Wednesday 01 December 2010] [04:27:56] <CIA-20>	zeromq2: 03Martin Lucina 07master * r289b1f5 10/ src/kqueue.cpp : 
| [Wednesday 01 December 2010] [04:27:56] <CIA-20>	zeromq2: Remove unnecessary cast in kevent_delete
| [Wednesday 01 December 2010] [04:27:57] <CIA-20>	zeromq2: Fixes the build on NetBSD where the compiler complains about casting NULL
| [Wednesday 01 December 2010] [04:27:57] <CIA-20>	zeromq2: to (int).
| [Wednesday 01 December 2010] [04:27:58] <CIA-20>	zeromq2: Signed-off-by: Martin Lucina <mato@kotelna.sk> - http://bit.ly/esACki
| [Wednesday 01 December 2010] [04:27:58] <CIA-20>	zeromq2: 03Martin Sustrik 07master * r17d7e6e 10/ src/kqueue.cpp : 
| [Wednesday 01 December 2010] [04:27:59] <CIA-20>	zeromq2: Merge branch 'maint'
| [Wednesday 01 December 2010] [04:28:53] <CIA-20>	zeromq2:  Remove unnecessary cast in kevent_delete
| [Wednesday 01 December 2010] [04:28:53] <CIA-20>	zeromq2: Conflicts:
| [Wednesday 01 December 2010] [04:28:53] <CIA-20>	zeromq2:  src/kqueue.cpp
| [Wednesday 01 December 2010] [04:28:53] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/gqsKEN
| [Wednesday 01 December 2010] [04:34:02] <CIA-20>	zeromq2: 03Mikko Koppanen 07master * r5bb0a33 10/ (5 files in 2 dirs): (log message trimmed)
| [Wednesday 01 December 2010] [04:34:02] <CIA-20>	zeromq2: Prefix variables with "ac_zmq_"
| [Wednesday 01 December 2010] [04:34:02] <CIA-20>	zeromq2:  - Added a macro for checking clang compiler
| [Wednesday 01 December 2010] [04:34:02] <CIA-20>	zeromq2:  - Moved basic compiler checks to a macro
| [Wednesday 01 December 2010] [04:34:02] <CIA-20>	zeromq2:  - Added a macro for checking if compiler supports a flag
| [Wednesday 01 December 2010] [04:34:02] <CIA-20>	zeromq2:  - Added --enable-debug flag
| [Wednesday 01 December 2010] [04:34:03] <CIA-20>	zeromq2:  - Added a macro for running normal autoconf check with compiler flags
| [Wednesday 01 December 2010] [04:47:39] <m_>	exit
| [Wednesday 01 December 2010] [04:58:17] <CIA-20>	zeromq2: 03Martin Lucina 07master * rb70d628 10/ (11 files): 
| [Wednesday 01 December 2010] [04:58:18] <CIA-20>	zeromq2: Documentation updates for 2.1
| [Wednesday 01 December 2010] [04:58:18] <CIA-20>	zeromq2: - Clarify ZMQ_LINGER, zmq_close (), zmq_term () relationship
| [Wednesday 01 December 2010] [04:58:18] <CIA-20>	zeromq2: - New socket options
| [Wednesday 01 December 2010] [04:58:18] <CIA-20>	zeromq2: - Clarify thread safety of sockets and migration between threads
| [Wednesday 01 December 2010] [04:58:18] <CIA-20>	zeromq2: - Other minor and spelling fixes
| [Wednesday 01 December 2010] [04:58:18] <CIA-20>	zeromq2: Signed-off-by: Martin Lucina <mato@kotelna.sk> - http://bit.ly/hV39nD
| [Wednesday 01 December 2010] [05:12:05] <CIA-20>	zeromq2: 03Martin Lucina 07master * r520d621 10/ configure.in : 
| [Wednesday 01 December 2010] [05:12:05] <CIA-20>	zeromq2: Bump ABI version to 1:0:0 for ZeroMQ 2.1.0 release
| [Wednesday 01 December 2010] [05:12:05] <CIA-20>	zeromq2: Signed-off-by: Martin Lucina <mato@kotelna.sk> - http://bit.ly/h94kRn
| [Wednesday 01 December 2010] [05:34:28] <vaadim>	Hello, all.
| [Wednesday 01 December 2010] [05:34:57] <vaadim>	Anybody can to help me?
| [Wednesday 01 December 2010] [05:35:26] <vaadim>	I have a critical error in object.cpp file.
| [Wednesday 01 December 2010] [05:35:41] <mikko>	vaadim: what is the error?
| [Wednesday 01 December 2010] [05:36:01] <vaadim>	Version 2.0.10 for windows.
| [Wednesday 01 December 2010] [05:37:11] <vaadim>	I write test project for client and server applications. Run zmq::queue() function.
| [Wednesday 01 December 2010] [05:37:57] <mikko>	what is the actual error?
| [Wednesday 01 December 2010] [05:38:15] <vaadim>	This function call zmq_poll->zmq::app_thread_t::process_commands->process_bind and
| [Wednesday 01 December 2010] [05:38:45] <vaadim>	in  case command_t::bind:  process_bind (cmd_.args.bind.in_pipe, cmd_.args.bind.out_pipe,             blob_t (cmd_.args.bind.peer_identity,             cmd_.args.bind.peer_identity_size));
| [Wednesday 01 December 2010] [05:39:20] <vaadim>	and cmd_.args.bind.peer_identity have a Bad Ptr == 0x0000000
| [Wednesday 01 December 2010] [05:39:26] <vaadim>	crash
| [Wednesday 01 December 2010] [05:40:22] <mikko>	does the same thing happen with github master?
| [Wednesday 01 December 2010] [05:40:27] <mikko>	can you test?
| [Wednesday 01 December 2010] [05:40:38] <mikko>	and is this easy to reproduce?
| [Wednesday 01 December 2010] [05:42:28] <vaadim>	I was try latest version in github, but this version have another problems, and i revert to version 2.0.10 back
| [Wednesday 01 December 2010] [05:42:45] <vaadim>	I can show my test project
| [Wednesday 01 December 2010] [05:42:59] <mikko>	what is the problem you had with the latest version?
| [Wednesday 01 December 2010] [05:44:34] <vaadim>	Current version in github is stable ? I need stable version for commercial project.
| [Wednesday 01 December 2010] [05:45:28] <mikko>	what i am intersted in what are the problems you are seeing so that they can be fixed
| [Wednesday 01 December 2010] [05:45:44] <mikko>	i would like you to test the github master to see if the issue with the null pointer has been fixed already
| [Wednesday 01 December 2010] [05:47:32] <vaadim>	OK. I will try master from github again. And I will come back with another bag's :)
| [Wednesday 01 December 2010] [05:47:52] <vaadim>	Thank you for help :)
| [Wednesday 01 December 2010] [05:52:53] <CIA-20>	zeromq2: 03Steven McCoy 07master * r4a3ed39 10/ (3 files in 2 dirs): 
| [Wednesday 01 December 2010] [05:52:53] <CIA-20>	zeromq2: Bump OpenPGM to 5.0.92.
| [Wednesday 01 December 2010] [05:52:53] <CIA-20>	zeromq2: Signed-off-by: Steven McCoy <steven.mccoy@miru.hk> - http://bit.ly/fLKN5H
| [Wednesday 01 December 2010] [05:57:05] <Steve-o>	thx Mato
| [Wednesday 01 December 2010] [05:57:31] <CIA-20>	zeromq2: 03Martin Lucina 07master * rabc8b5e 10/ NEWS : 
| [Wednesday 01 December 2010] [05:57:31] <CIA-20>	zeromq2: Update NEWS file for 2.1.0 release
| [Wednesday 01 December 2010] [05:57:31] <CIA-20>	zeromq2: Signed-off-by: Martin Lucina <mato@kotelna.sk> - http://bit.ly/hXdp5N
| [Wednesday 01 December 2010] [06:16:40] <rgl>	w00t 2.1 has hit the streets?
| [Wednesday 01 December 2010] [06:16:48] <mato>	almost
| [Wednesday 01 December 2010] [06:16:59] <mato>	due to DNS issues the announcement will go out this evening
| [Wednesday 01 December 2010] [06:17:06] <mato>	but it's in Git anyhow :-)
| [Wednesday 01 December 2010] [06:18:57] <mikko>	ill run daily builds now just to see that everything works
| [Wednesday 01 December 2010] [06:19:03] <rgl>	:)
| [Wednesday 01 December 2010] [06:19:28] <mikko>	building now
| [Wednesday 01 December 2010] [06:19:38] <rgl>	I just noticed Sockets may now be migrated between OS threads, as long as the
| [Wednesday 01 December 2010] [06:19:38] <rgl>	 application ensures that a full memory barrier is issued.  ... are there any examples how to do it?
| [Wednesday 01 December 2010] [06:21:02] <mikko>	is 2.1.0 going out as alpha or beta?
| [Wednesday 01 December 2010] [06:22:38] <rgl>	from the NEWS files its Beta
| [Wednesday 01 December 2010] [06:24:19] <sustrik>	rgl: when you migrate a thread you have no notify the other thread somehow
| [Wednesday 01 December 2010] [06:24:42] <sustrik>	the mechanism you use for the notfication will execute the barrier
| [Wednesday 01 December 2010] [06:24:53] <sustrik>	unless you are doing some black magic
| [Wednesday 01 December 2010] [06:26:08] <rgl>	I see. alright :D
| [Wednesday 01 December 2010] [06:33:07] <mikko>	success on all builds this far
| [Wednesday 01 December 2010] [06:33:33] <sustrik>	goodo
| [Wednesday 01 December 2010] [06:34:20] <mikko>	icc failed
| [Wednesday 01 December 2010] [06:34:22] <mikko>	let's see
| [Wednesday 01 December 2010] [06:34:37] <mikko>	it might be the shutdown stress test failing
| [Wednesday 01 December 2010] [06:34:55] <mikko>	Bad file descriptor
| [Wednesday 01 December 2010] [06:34:55] <mikko>	nbytes != -1 (tcp_socket.cpp:197)
| [Wednesday 01 December 2010] [06:34:56] <mikko>	yes
| [Wednesday 01 December 2010] [06:35:58] <sustrik>	yep, known issue
| [Wednesday 01 December 2010] [06:36:53] <rgl>	mikko, where is the build system? got url?
| [Wednesday 01 December 2010] [06:37:03] <mikko>	http://build.valokuva.org/
| [Wednesday 01 December 2010] [06:38:12] <mikko>	i got my eye on sunfire server on ebay
| [Wednesday 01 December 2010] [06:38:18] <mikko>	to add sparc into the build system
| [Wednesday 01 December 2010] [06:38:36] <Steve-o>	incredibly cheap these days, ~US$100
| [Wednesday 01 December 2010] [06:39:00] <Steve-o>	but also slow as lard, 100mb NICs often
| [Wednesday 01 December 2010] [06:39:20] <mikko>	this one is Dual 1.3Ghz Processors
| [Wednesday 01 December 2010] [06:39:29] <mikko>	i don't mind 100mb nic as it's just for building
| [Wednesday 01 December 2010] [06:39:32] <mikko>	not really for testing
| [Wednesday 01 December 2010] [06:40:17] <rgl>	mikko, no msvc build?
| [Wednesday 01 December 2010] [06:40:26] <Steve-o>	memory is the most important though, don't skimp on that
| [Wednesday 01 December 2010] [06:40:33] <mikko>	rgl: haven't got a windows running
| [Wednesday 01 December 2010] [06:40:41] <mikko>	Steve-o: it comes with 4GB
| [Wednesday 01 December 2010] [06:40:55] <vaadim>	Hello, I am here again.
| [Wednesday 01 December 2010] [06:41:07] <mikko>	the annoyance is that the build machines are running in finland
| [Wednesday 01 December 2010] [06:41:10] <mikko>	and i live in london
| [Wednesday 01 December 2010] [06:41:18] <mikko>	need to either host it here or ship it over
| [Wednesday 01 December 2010] [06:41:42] <sustrik>	does it make any difference?
| [Wednesday 01 December 2010] [06:41:43] <rgl>	mikko, http://build.valokuva.org/view/clrzmq/ is using mono then?
| [Wednesday 01 December 2010] [06:41:51] <mikko>	rgl: yes
| [Wednesday 01 December 2010] [06:41:51] <vaadim>	mikko: i try the current version from github in my test project
| [Wednesday 01 December 2010] [06:41:59] <mikko>	vaadim: ok
| [Wednesday 01 December 2010] [06:42:12] <mikko>	sustrik: i got free hosting in finland
| [Wednesday 01 December 2010] [06:42:16] <mikko>	that's the only difference
| [Wednesday 01 December 2010] [06:42:42] <sustrik>	i see
| [Wednesday 01 December 2010] [06:43:09] <rgl>	mikko, can you add clrmq2 into the clrmq tab too?
| [Wednesday 01 December 2010] [06:43:32] <mikko>	rgl: done
| [Wednesday 01 December 2010] [06:43:42] <mikko>	the regex for adding jobs there was outdated
| [Wednesday 01 December 2010] [06:43:45] <vaadim>	My server stoped with error while i try break zmq_device by call zmq_term() for kill context
| [Wednesday 01 December 2010] [06:43:46] <mikko>	clrzmq-.*
| [Wednesday 01 December 2010] [06:43:53] <rgl>	thanks :)
| [Wednesday 01 December 2010] [06:44:10] <mikko>	sustrik: what is the clean way to stop zmq device?
| [Wednesday 01 December 2010] [06:44:24] <mikko>	vaadim: i am not sure if that is the way to stop a device
| [Wednesday 01 December 2010] [06:46:21] <sustrik>	mikko: Ctrl+C?
| [Wednesday 01 December 2010] [06:46:33] <sustrik>	there's no remote management for devices yet
| [Wednesday 01 December 2010] [06:46:40] <vaadim>	I read this way in your mailing list archiew
| [Wednesday 01 December 2010] [06:47:00] <vaadim>	wait a moment...
| [Wednesday 01 December 2010] [06:47:51] <vaadim>	http://thread.gmane.org/gmane.network.zeromq.devel/2338/focus=2340
| [Wednesday 01 December 2010] [06:48:30] <sustrik>	vaadim: the devices are dumb pieces of code
| [Wednesday 01 December 2010] [06:48:43] <sustrik>	basically just a loop that reads from one socket and writes to another one
| [Wednesday 01 December 2010] [06:49:00] <sustrik>	if you want a better functionality, like a remote management
| [Wednesday 01 December 2010] [06:49:08] <sustrik>	you can add it there
| [Wednesday 01 December 2010] [06:51:42] <vaadim>	Sorry, i'm not understand, how to stop loop in device. I need to stop both sockets ?
| [Wednesday 01 December 2010] [06:52:51] <sustrik>	you just break out of the loop
| [Wednesday 01 December 2010] [06:53:01] <sustrik>	that's it
| [Wednesday 01 December 2010] [06:53:16] <vaadim>	How? Kill thread?
| [Wednesday 01 December 2010] [06:53:37] <sustrik>	while (true) {
| [Wednesday 01 December 2010] [06:53:39] <sustrik>	...
| [Wednesday 01 December 2010] [06:53:50] <sustrik>	    if (...)
| [Wednesday 01 December 2010] [06:53:52] <sustrik>	       break;
| [Wednesday 01 December 2010] [06:53:55] <sustrik>	...
| [Wednesday 01 December 2010] [06:53:55] <sustrik>	}
| [Wednesday 01 December 2010] [06:55:11] <vaadim>	But zmq_device(ZMQ_QUEUE, clients, workers); bon't return control, and i can't make loop myself.
| [Wednesday 01 December 2010] [06:55:26] <sustrik>	have a look at the source code
| [Wednesday 01 December 2010] [06:55:27] <mikko>	vaadim: have you looked at the device code?
| [Wednesday 01 December 2010] [06:55:47] <sustrik>	you just create your own device
| [Wednesday 01 December 2010] [06:55:55] <sustrik>	and modify it in any way you want
| [Wednesday 01 December 2010] [06:57:38] <vaadim>	Yeah, well, I'm gonna go build my own device, with blackjack and hookers. In fact, forget the device! :)
| [Wednesday 01 December 2010] [06:59:54] <vaadim>	Ok, i can append third parameter to my_zmq_device with stop socket.
| [Wednesday 01 December 2010] [07:00:25] <vaadim>	Thank's.
| [Wednesday 01 December 2010] [11:06:31] <Remoun>	hi
| [Wednesday 01 December 2010] [11:06:36] <Remoun>	I'm perusing the guide right now, but I thought I'd ask ahead: Can I overlay some sort of authentication mechanism for workers in a 0MQ-based system?
| [Wednesday 01 December 2010] [11:07:01] <mikko>	Remoun: i don't see why what would prevent you from doing that
| [Wednesday 01 December 2010] [11:07:29] <Remoun>	I don't see any reason, either; I just have no idea how yet
| [Wednesday 01 December 2010] [11:07:41] <Remoun>	But it should be doable (in a transparent manner), right?
| [Wednesday 01 December 2010] [11:07:52] <mikko>	what do you mean by transparent?
| [Wednesday 01 December 2010] [11:07:59] <mikko>	you would need to implement it in your code
| [Wednesday 01 December 2010] [11:08:06] <Remoun>	of course
| [Wednesday 01 December 2010] [11:08:43] <Remoun>	basically, layering the auth on top of the sockets
| [Wednesday 01 December 2010] [11:08:59] <Remoun>	So that I don't have to decorate every bit of code using 0MQ sockets with auth handling
| [Wednesday 01 December 2010] [11:09:32] <mikko>	there are plenty of ways to approach the problem
| [Wednesday 01 December 2010] [11:09:33] <Remoun>	... Does that make sense?
| [Wednesday 01 December 2010] [11:09:44] <mikko>	you could do a small device that handles the authentication
| [Wednesday 01 December 2010] [11:09:51] <mikko>	and forwards the messages using inproc
| [Wednesday 01 December 2010] [11:10:21] <mikko>	so your client code would communicate with inproc and the device decorates with authentication info and forwards the messages
| [Wednesday 01 December 2010] [11:13:51] <Remoun>	sounds good
| [Wednesday 01 December 2010] [11:13:54] <Remoun>	thanks mikko 
| [Wednesday 01 December 2010] [11:24:14] <shales>	hi, has anyone used eventlet with zmq? I'm wondering if or how eventlet works with zmq.REP sockets or do I have to switch to XREP sockets to avoid the state kept in the REP socket from messing up with multiple threads?
| [Wednesday 01 December 2010] [11:30:02] <mikko>	shales: sorry, no idea what eventlet is 
| [Wednesday 01 December 2010] [11:30:06] <mikko>	shales: is it ruby?
| [Wednesday 01 December 2010] [11:31:00] <mikko>	ah, python
| [Wednesday 01 December 2010] [11:31:03] <shales>	python
| [Wednesday 01 December 2010] [11:31:40] <shales>	it's ok, someone on #eventlet just gave me an easy workaround
| [Wednesday 01 December 2010] [11:31:58] <shales>	just give each greenthread its own REP socket
| [Wednesday 01 December 2010] [13:47:25] <jhawk28>	Hello. Congrats on the 2.1.0 beta!
| [Wednesday 01 December 2010] [14:58:58] <mikko>	mato: hmm, does 3.4.6 report that it supports dso visibility?
| [Wednesday 01 December 2010] [15:00:04] <mikko>	#   elif (defined __GNUC__ && __GNUC__ >= 4) || defined __INTEL_COMPILER
| [Wednesday 01 December 2010] [15:00:09] <mikko>	this error reported makes no sense
| [Wednesday 01 December 2010] [15:00:21] <mato>	mikko: it shouldn't, i'm just replying asking for more info
| [Wednesday 01 December 2010] [15:00:47] <mato>	unless RHAT borked it of course :-)
| [Wednesday 01 December 2010] [15:01:00] <mikko>	but in any case it should not pass __GNUC__ >= 4
| [Wednesday 01 December 2010] [15:01:13] <mato>	ISTR some problems related to OpenPGM use of __attribute__((visibility)) on old RHAT also
| [Wednesday 01 December 2010] [15:01:36] <mikko>	downloading centos4 now
| [Wednesday 01 December 2010] [15:01:42] <mato>	:-)
| [Wednesday 01 December 2010] [15:01:59] 	 * mato is not at the office, no VM-capable hardware here ...
| [Wednesday 01 December 2010] [15:02:38] <mikko>	http://cgi.ebay.co.uk/SUN-MICRO-SUNFIRE-V210-RACKMOUNT-SERVER-/230553957004?pt=UK_Computing_Networking_SM&hash=item35ae16328c
| [Wednesday 01 December 2010] [15:02:41] <mikko>	i got my eye on that
| [Wednesday 01 December 2010] [15:02:44] <mikko>	to add to build cluster
| [Wednesday 01 December 2010] [15:02:57] <mikko>	if the price doesn't go up much i'll try to snatch it
| [Wednesday 01 December 2010] [15:04:31] <prokos>	does ZMQ_SUBSCRIBE filter on the client side or the server side? 
| [Wednesday 01 December 2010] [15:04:49] <mikko>	prokos: client side
| [Wednesday 01 December 2010] [15:05:00] <mato>	heh, I got offered a Sun Fire 15k for free some time ago, declined on the grounds that I don't have an empty data center and free electricity to run it...
| [Wednesday 01 December 2010] [15:05:04] <mikko>	if by client you mean the subscriber
| [Wednesday 01 December 2010] [15:05:28] <mikko>	mato: i'm hoping to put this in the server room at work
| [Wednesday 01 December 2010] [15:05:36] <mikko>	and as a backup plan im gonna ship it to finland
| [Wednesday 01 December 2010] [15:06:02] <mato>	well, 50 GBP is damn cheap
| [Wednesday 01 December 2010] [15:06:33] <prokos>	yes i mean the subscriber.. Is there a reason to not filter on the publisher side?
| [Wednesday 01 December 2010] [15:07:00] <mikko>	prokos: it's very complicated to implement but i think it's on the list of things to do
| [Wednesday 01 December 2010] [15:11:13] <jhawk28>	has anyone seen this: http://sna-projects.com/kafka/
| [Wednesday 01 December 2010] [15:20:02] <mato>	mikko: I've forwarded you the outputs Chris Patti sent me just now
| [Wednesday 01 December 2010] [15:20:30] <mato>	mikko: It looks to me like his GCC claims to support -fvisibility=hidden but the results are completely bogus
| [Wednesday 01 December 2010] [15:20:54] <mato>	mikko: the symbol table in libzmq.so is missing anything which would normally be hidden
| [Wednesday 01 December 2010] [15:21:17] <mikko>	mato: yes
| [Wednesday 01 December 2010] [15:21:34] <mato>	mikko: looks like we need an autoconf check for "Checking to see if g++ -fvisibility=hidden actually works" :-)
| [Wednesday 01 December 2010] [15:21:36] <mikko>	i got centos4 running soon
| [Wednesday 01 December 2010] [15:22:23] <mato>	no point in fighting with getting it to work on buggy/old compilers, but it shouldn't break completely...
| [Wednesday 01 December 2010] [15:23:42] <mikko>	mato: does it support the pragma?
| [Wednesday 01 December 2010] [15:23:48] <mikko>	if it supports -fvisibility
| [Wednesday 01 December 2010] [15:24:11] <mato>	probably not
| [Wednesday 01 December 2010] [15:24:23] <mato>	or it's some bastardized RHAT version
| [Wednesday 01 December 2010] [15:26:06] <mikko>	got centos4 running now
| [Wednesday 01 December 2010] [15:27:36] <mikko>	yum is _slow_ on centos4
| [Wednesday 01 December 2010] [15:36:37] <mikko>	mato: gcc version 3.4.6 20060404 (Red Hat 3.4.6-11)
| [Wednesday 01 December 2010] [15:36:43] <mikko>	visibility works
| [Wednesday 01 December 2010] [15:36:52] <mikko>	no wait
| [Wednesday 01 December 2010] [15:36:58] <mikko>	it supports -fvisibility
| [Wednesday 01 December 2010] [15:37:04] <mikko>	but ignores the attribute
| [Wednesday 01 December 2010] [15:37:40] <mato>	geez
| [Wednesday 01 December 2010] [15:37:46] <mikko>	hmm
| [Wednesday 01 December 2010] [15:37:50] <mikko>	thats not completely true
| [Wednesday 01 December 2010] [15:38:00] <mikko>	https://gist.github.com/b2f2ef8f5bc92d2688b3
| [Wednesday 01 December 2010] [15:38:51] <mato>	well, in any case, we can't detect this case in zmq.h sanely
| [Wednesday 01 December 2010] [15:39:03] <mato>	so we need to account for it in the autoconf tests somehowe
| [Wednesday 01 December 2010] [15:40:06] <mato>	I reckon for now the easiest thing is to explicitly check the GCC version
| [Wednesday 01 December 2010] [15:40:23] <mato>	and not enable -fvisibility if it's < 4
| [Wednesday 01 December 2010] [15:40:28] <mikko>	yes, i was thinking the same
| [Wednesday 01 December 2010] [15:40:35] <mikko>	let me wrap a macro for that
| [Wednesday 01 December 2010] [15:55:12] <mikko>	brb
| [Wednesday 01 December 2010] [16:17:51] <prokos>	f
| [Wednesday 01 December 2010] [17:10:04] <mikko>	mato: take a look at http://valokuva.org/~mikko/visibility.patch when you got time
| [Wednesday 01 December 2010] [17:41:25] <jhawk28_>	hey sustrik
| [Wednesday 01 December 2010] [17:43:24] <sustrik>	hi
| [Wednesday 01 December 2010] [17:47:32] <Guthur>	is there tests for the new features?
| [Wednesday 01 December 2010] [17:47:38] <Guthur>	in 2.1.0
| [Wednesday 01 December 2010] [19:19:13] <erickt>	Hi #zeromq! congrats on 2.1.0. I was wondering, did sys://log make it into 2.1.0?
| [Wednesday 01 December 2010] [19:20:47] <erickt>	and if so, what is getting logged?
| [Wednesday 01 December 2010] [20:54:02] <Remoun>	How can I get the remote IP (of the sender) when receiving over TCP?
| [Wednesday 01 December 2010] [23:20:06] <DanielHolth>	any word on a ctypes zeromq binding?
| [Wednesday 01 December 2010] [23:20:11] <DanielHolth>	for Python?
| [Thursday 02 December 2010] [02:32:59] <delaney__>	has anyone had any luck getting pyzmq to build with 3.1?
| [Thursday 02 December 2010] [02:34:03] <delaney__>	trying with the 2.0.10
| [Thursday 02 December 2010] [02:53:58] <sustrik>	delaney: autobuilds: http://build.valokuva.org/
| [Thursday 02 December 2010] [02:54:33] <sustrik>	Remoun: you can't
| [Thursday 02 December 2010] [02:55:04] <sustrik>	erickt: it have made it in
| [Thursday 02 December 2010] [02:55:16] <sustrik>	you can subscribe to it
| [Thursday 02 December 2010] [02:55:23] <sustrik>	but nothing is logged yet :)
| [Thursday 02 December 2010] [02:59:16] <delaney__>	sustrik that looks cool but doesn't seem to have a link to the zmq package, or is that not available?  http://build.valokuva.org/view/pyzmq/job/pyzmq-master_ZeroMQ2-master_GCC/lastBuild/
| [Thursday 02 December 2010] [02:59:49] <sustrik>	nope, it doesn't create packages
| [Thursday 02 December 2010] [03:00:05] <sustrik>	but it shows that the pyzmq can be built with master
| [Thursday 02 December 2010] [03:03:33] <delaney__>	oh i don't doubt it
| [Thursday 02 December 2010] [03:03:50] <delaney__>	actually just got it working with 32bit visual studio 2008
| [Thursday 02 December 2010] [03:04:07] <delaney__>	but can't seem to with 64bit visual studio 2010
| [Thursday 02 December 2010] [03:09:09] <sustrik>	report the problem on the mailing list then...
| [Thursday 02 December 2010] [03:09:34] <sustrik>	i cannot really help myself is a don't have win64
| [Thursday 02 December 2010] [03:14:27] <Steve-o>	sustrik, hope you like the bug I found on MSVC :-)
| [Thursday 02 December 2010] [03:23:34] <sustrik>	Steve-o: haven't read all emails yet
| [Thursday 02 December 2010] [03:23:39] <sustrik>	which one is that?
| [Thursday 02 December 2010] [03:24:13] <Steve-o>	ok, end of "encoder hanging in remote_thr tests" thread.  
| [Thursday 02 December 2010] [03:24:29] <Steve-o>	compiler over-optimisation
| [Thursday 02 December 2010] [03:25:01] <sustrik>	uh, you've sent a patch
| [Thursday 02 December 2010] [03:25:16] <Steve-o>	it's a workaround, not a real patch
| [Thursday 02 December 2010] [03:25:31] <sustrik>	anyway, mark the emails containing patches with [PATCH]
| [Thursday 02 December 2010] [03:25:31] <Steve-o>	I have no idea what is a good solution, leave that up to you
| [Thursday 02 December 2010] [03:25:44] <sustrik>	otherwise it's pretty easy to forget about it
| [Thursday 02 December 2010] [03:26:01] <Steve-o>	I've dumped a Win32 API call in there, it's not useful to commit it
| [Thursday 02 December 2010] [03:26:10] <sustrik>	ok, i see
| [Thursday 02 December 2010] [03:26:52] <Steve-o>	still working on why linger isn't working
| [Thursday 02 December 2010] [03:27:06] <Steve-o>	is it supposed to on pub sockets?
| [Thursday 02 December 2010] [03:27:25] <sustrik>	Steve-o: i would say the problem is that OpenPGM doesn't have linger
| [Thursday 02 December 2010] [03:27:32] <sustrik>	so the LINGER is set on 0MQ level
| [Thursday 02 December 2010] [03:27:42] <sustrik>	when 0MQ pushes all data to OpenPGM
| [Thursday 02 December 2010] [03:27:53] <sustrik>	it considers the work done
| [Thursday 02 December 2010] [03:27:56] <sustrik>	and exits
| [Thursday 02 December 2010] [03:28:01] <sustrik>	which closes the process
| [Thursday 02 December 2010] [03:28:07] <Steve-o>	the problem here is 0MQ isn't sending anything to PGM
| [Thursday 02 December 2010] [03:28:10] <sustrik>	thus dropping the PGM tx buffers
| [Thursday 02 December 2010] [03:28:14] <sustrik>	ah
| [Thursday 02 December 2010] [03:28:27] <Steve-o>	it only init's the pgm_socket object
| [Thursday 02 December 2010] [03:28:31] <Steve-o>	the destroys it
| [Thursday 02 December 2010] [03:28:41] <Steve-o>	core bug
| [Thursday 02 December 2010] [03:28:50] <sustrik>	ok, i'll give it a look
| [Thursday 02 December 2010] [03:28:51] <Steve-o>	or "feature"
| [Thursday 02 December 2010] [03:29:08] <Steve-o>	check your mails and get back to me on the list later
| [Thursday 02 December 2010] [03:29:15] <sustrik>	sure, will do
| [Thursday 02 December 2010] [05:01:25] <PiotrSikora>	guys, are there any complete examples/guides about integrating zeromq with existing event poll using ZMQ_FD & ZMQ_EVENTS?
| [Thursday 02 December 2010] [05:20:41] <sustrik_>	PiotrSikora: have a look at src/zmq.cpp
| [Thursday 02 December 2010] [05:20:51] <sustrik_>	there's implementation of zmq_poll
| [Thursday 02 December 2010] [05:21:00] <sustrik_>	which uses ZMQ_FD and ZMQ_EVENTS underneath
| [Thursday 02 December 2010] [05:21:33] <sustrik_>	combined with either select(2) or poll(2)
| [Thursday 02 December 2010] [05:25:47] <PiotrSikora>	sustrik_: yeah, i looked at it... let me clarify...
| [Thursday 02 December 2010] [05:27:34] <PiotrSikora>	sustrik_: it is my understanding that in order to hook ZMQ into existing event look (kevent, epoll, etc) i need to get existing fd via getsockopt(ZMQ_FD), then when system will notice my about event on that fd, I need to verify that there is complete ZMQ message available via getsockopt(ZMQ_EVENTS)
| [Thursday 02 December 2010] [05:27:54] <PiotrSikora>	however i'm lost at how can i retrieve this message without blocking?
| [Thursday 02 December 2010] [05:28:02] <PiotrSikora>	zmq_poll? doesn't look like
| [Thursday 02 December 2010] [05:29:11] <PiotrSikora>	or would zmq_recv() be ok?
| [Thursday 02 December 2010] [05:29:35] <sustrik_>	zmq_recv()
| [Thursday 02 December 2010] [05:29:40] <sustrik_>	you know it's there
| [Thursday 02 December 2010] [05:29:50] <sustrik_>	so you just call zmq_recv() and you'll get it
| [Thursday 02 December 2010] [05:30:40] <PiotrSikora>	ok, thx :)
| [Thursday 02 December 2010] [05:31:07] <PiotrSikora>	seems like those new features make it extremely easy to integrate now
| [Thursday 02 December 2010] [05:31:30] <PiotrSikora>	i remember i looked into this (integrating with existing event loop) a while ago and it seemd rather impossible to do
| [Thursday 02 December 2010] [06:09:21] <mikko>	this is odd
| [Thursday 02 December 2010] [06:09:31] <mikko>	out of the box gcc 3.4.6 does not support -fvisibility=hidden flag
| [Thursday 02 December 2010] [06:09:44] <mikko>	but redhat "fixed" version does support it but messes up visibility
| [Thursday 02 December 2010] [06:55:18] <sustrik_>	Steve-o: hi
| [Thursday 02 December 2010] [06:55:26] <Steve-o>	hi
| [Thursday 02 December 2010] [06:55:40] <sustrik_>	aren't there 2 different problems there?
| [Thursday 02 December 2010] [06:55:49] <sustrik_>	one of them is solved by sleep()
| [Thursday 02 December 2010] [06:56:11] <Steve-o>	at least 2 possibly more
| [Thursday 02 December 2010] [06:56:26] <sustrik_>	yep
| [Thursday 02 December 2010] [06:56:35] <sustrik_>	so let's solve these seaprately
| [Thursday 02 December 2010] [06:56:49] <Steve-o>	the memory barrier / fence is the most odd
| [Thursday 02 December 2010] [06:57:08] <sustrik_>	mikko: mato says you are right
| [Thursday 02 December 2010] [06:57:15] <sustrik_>	and it's RH bug
| [Thursday 02 December 2010] [06:57:29] <sustrik_>	Steve-o: yes
| [Thursday 02 December 2010] [06:57:42] <sustrik_>	anyway, one problem that's pretty obvious is that 0MQ doesn't wait for OpenPGM when terminating
| [Thursday 02 December 2010] [06:58:09] <sustrik_>	can we solve that one somehow?
| [Thursday 02 December 2010] [06:58:22] <Steve-o>	isn't something broken in the linger implementation?
| [Thursday 02 December 2010] [06:58:37] <sustrik_>	maybe, but that's not the point
| [Thursday 02 December 2010] [06:58:52] <sustrik_>	the point is that 0mq doesn't know when openpgm have sent all the data
| [Thursday 02 December 2010] [06:59:06] <Steve-o>	ok three problems
| [Thursday 02 December 2010] [06:59:26] <sustrik_>	ok
| [Thursday 02 December 2010] [06:59:34] <Steve-o>	#1 0mq does not flush complete batch of messages, instead it only sends first message
| [Thursday 02 December 2010] [06:59:50] <Steve-o>	#2 a MSVC 2010 compiler optimisation bug causes encoder.get_data to hang
| [Thursday 02 December 2010] [07:00:13] <Steve-o>	#3 short PUB runs followed by zmq_term do not plug the underlying transport
| [Thursday 02 December 2010] [07:00:38] <mikko>	sustrik_: i think i got a feasible patch
| [Thursday 02 December 2010] [07:01:20] <mikko>	ill talk with mato when he is back
| [Thursday 02 December 2010] [07:01:25] <sustrik_>	sure
| [Thursday 02 December 2010] [07:02:15] <Steve-o>	note #1 & #3 may also be MSVC bugs, no idea
| [Thursday 02 December 2010] [07:03:00] <sustrik_>	Steve-o: ok, can it be reproduced on a single box?
| [Thursday 02 December 2010] [07:03:31] <Steve-o>	#3 is really easy, just run remote_thr with size=100 and count=1 ... 2000
| [Thursday 02 December 2010] [07:03:55] <Steve-o>	i added printf statements to every call in pgm_sender.cpp to see what if ever is called
| [Thursday 02 December 2010] [07:04:37] <Steve-o>	#2 randomly occurs when data is actually sent
| [Thursday 02 December 2010] [07:04:48] <Steve-o>	#1 not so important as the others
| [Thursday 02 December 2010] [07:06:01] <Steve-o>	of course it will be more annoying if it is hardware dependent
| [Thursday 02 December 2010] [07:06:50] <sustrik_>	so let's start with #3
| [Thursday 02 December 2010] [07:07:00] <sustrik_>	pgm?
| [Thursday 02 December 2010] [07:07:02] <sustrik_>	epgm?
| [Thursday 02 December 2010] [07:07:04] <sustrik_>	loopback?
| [Thursday 02 December 2010] [07:07:07] <Steve-o>	epgm,
| [Thursday 02 December 2010] [07:07:44] <sustrik_>	does it happen on linux as well?
| [Thursday 02 December 2010] [07:07:53] <Steve-o>	haven't checked yet
| [Thursday 02 December 2010] [07:08:26] <sustrik_>	let me try
| [Thursday 02 December 2010] [07:08:30] <Steve-o>	i only saw #1 on linux so far
| [Thursday 02 December 2010] [07:13:22] <Steve-o>	linux looks fine here for count=1 
| [Thursday 02 December 2010] [07:14:27] <Steve-o>	LD_LIBRARY_PATH=src/.libs/ ./perf/.libs/remote_thr --rate-limit 100 "epgm://eth0;239.192.0.1:7500" 100 1
| [Thursday 02 December 2010] [07:14:41] <Steve-o>	sends 1 packet as expected
| [Thursday 02 December 2010] [07:22:51] <sustrik_>	so it only happens on windows, right?
| [Thursday 02 December 2010] [07:23:04] <sustrik_>	i don't have a win box here
| [Thursday 02 December 2010] [07:26:50] <Steve-o>	appears so, just tested on another box and reproduced it
| [Thursday 02 December 2010] [07:30:50] <Steve-o>	that's why I'm wondering if it is another MSVC compiler optimisation bug
| [Thursday 02 December 2010] [07:31:10] <Steve-o>	you really need some heavy unit testing to catch annoying features like this
| [Thursday 02 December 2010] [07:31:50] <sustrik_>	Steve-o: yes, but win32 is a platform that i am not really using
| [Thursday 02 December 2010] [07:35:18] <Steve-o>	unfortunately most VMs are too helpful either for multicast testing
| [Thursday 02 December 2010] [07:37:01] <Steve-o>	I think it's still only limited to ESX virtual NICs
| [Thursday 02 December 2010] [07:37:38] <sustrik_>	no idea
| [Thursday 02 December 2010] [07:38:53] <sustrik_>	anyway, the obvious problem is that the whole win/pgm thing is not going to move forward at any reasonable pace if there's no infrastructure to test it on
| [Thursday 02 December 2010] [07:43:52] <Steve-o>	yup, and I guess some assistance in testing the .net libraries would help developers too
| [Thursday 02 December 2010] [07:46:18] <Steve-o>	if MSVC is causing this there should be negative consequences on the TCP transport too
| [Thursday 02 December 2010] [07:50:29] <Steve-o>	I'm currently using 2008R2 trial on a server and Windows 7 on desktop, but on separate networks :-)
| [Thursday 02 December 2010] [09:00:35] <mikko>	mato: found it
| [Thursday 02 December 2010] [09:00:35] <mikko>	- backport C++ visibility patches, -fvisibility*, #pragma GCC visibility
| [Thursday 02 December 2010] [09:00:44] <mikko>	from RHEL gcc changelog
| [Thursday 02 December 2010] [09:10:28] <Guthur>	i there any caveats with having multiple contexts in the one application?
| [Thursday 02 December 2010] [09:10:49] <Guthur>	i/is
| [Thursday 02 December 2010] [09:11:16] <mato>	mikko: Thought so ... usual silly attitude from RHAT
| [Thursday 02 December 2010] [09:11:48] <mato>	mikko: Anyway, I'd suggest going with the approach in your patch for now (don't enable it at all on GCC < 4)
| [Thursday 02 December 2010] [09:11:59] <mato>	mikko: I've not reviewed it yet in detail, busy today...
| [Thursday 02 December 2010] [09:14:06] <mikko>	mato: check this
| [Thursday 02 December 2010] [09:14:14] <mikko>	http://valokuva.org/~mikko/visibility-rhel.patch
| [Thursday 02 December 2010] [09:14:18] <mikko>	this is the latest
| [Thursday 02 December 2010] [09:14:29] <mikko>	it uses AC_COMPILE_IFELSE to test the visibility
| [Thursday 02 December 2010] [09:14:54] <mikko>	the AC_COMPILE_IFELSE should fail if the compiler is not one of the defined
| [Thursday 02 December 2010] [09:15:09] <mikko>	additionally it uses 'nm' to check that the symbol actually has the expected visibility
| [Thursday 02 December 2010] [09:16:13] <mato>	mikko: 'nm' is not a good idea due to non-portability of it's output
| [Thursday 02 December 2010] [09:16:23] <mato>	mikko: e.g. solaris nm by default produces completely different output
| [Thursday 02 December 2010] [09:16:57] <mato>	mikko: if you really want to go the whole hog and actually test if -fvisibility works, then you'd need to compile a shared object and try and link against it
| [Thursday 02 December 2010] [09:17:04] <mato>	mikko: not sure if that's worth the work...
| [Thursday 02 December 2010] [09:17:33] <mato>	mikko: since compiling a shared lib would need to be done thru libtool to be portable, etc etc.
| [Thursday 02 December 2010] [09:18:20] <mato>	mikko: why not just stick with the bruteforce approach for now and don't even try -fvisibility on GCC < 4?
| [Thursday 02 December 2010] [09:18:25] <mikko>	mato: nm format is defined in posix
| [Thursday 02 December 2010] [09:18:34] <mikko>	not sure if everyone follows that htough
| [Thursday 02 December 2010] [09:18:36] <mato>	mikko: Yes, but not everyone follows thhat
| [Thursday 02 December 2010] [09:18:57] <mikko>	ok
| [Thursday 02 December 2010] [09:19:00] <mikko>	ill remove the nm part
| [Thursday 02 December 2010] [09:19:12] <mikko>	the AC_TRY_COMPILE should still fail with gcc 4<
| [Thursday 02 December 2010] [09:19:19] <mikko>	gcc <4
| [Thursday 02 December 2010] [09:20:01] <mikko>	let me update the patch
| [Thursday 02 December 2010] [09:20:42] <mikko>	mato: you mean something like this:http://valokuva.org/~mikko/visibility.patch
| [Thursday 02 December 2010] [09:22:10] <mato>	mikko: guess so
| [Thursday 02 December 2010] [09:23:08] <mikko>	i can also just remove the AC_TRY_COMPILE and use the compiler check
| [Thursday 02 December 2010] [09:23:16] <mikko>	if test "x$ac_ .. etc
| [Thursday 02 December 2010] [09:23:34] <mato>	make it as simple as possible, this is just for people with broken redhat GCC
| [Thursday 02 December 2010] [09:24:02] <mikko>	ok
| [Thursday 02 December 2010] [09:24:09] <mikko>	i'll juggle it a bit later
| [Thursday 02 December 2010] [09:27:32] <sustrik>	Guthur: you can, but what is it good for?
| [Thursday 02 December 2010] [09:28:54] <Guthur>	To make my object disposal strategy in a C# application a little bit more naive
| [Thursday 02 December 2010] [09:29:47] <Guthur>	I have a background thread listening for requests on a ZMQ_REQ, it'd like it to able to take care of it's own disposal
| [Thursday 02 December 2010] [09:29:56] <Guthur>	it'd/I'd
| [Thursday 02 December 2010] [09:30:04] <sustrik>	and?
| [Thursday 02 December 2010] [09:30:34] <Guthur>	Well if i share a context with the main thread I was thinking that I couldn't get rid of it without worrying about that socket
| [Thursday 02 December 2010] [09:31:08] <sustrik>	the socket returns ETERM when context it terminated
| [Thursday 02 December 2010] [09:31:13] <Guthur>	Does that make sense
| [Thursday 02 December 2010] [09:31:22] <Guthur>	oh ok
| [Thursday 02 December 2010] [09:31:43] <Guthur>	ignore the make sense statement
| [Thursday 02 December 2010] [09:33:19] <Guthur>	my mistake, I should have checked, I thought the open socket would block the context from disposing
| [Thursday 02 December 2010] [09:34:11] <sustrik>	it will
| [Thursday 02 December 2010] [09:34:38] <sustrik>	you'll get ETERM, then you close the socket
| [Thursday 02 December 2010] [09:34:46] <sustrik>	then the zmq_term() finishes
| [Thursday 02 December 2010] [09:39:16] <Guthur>	ok, thanks for the clarification sustrik 
| [Thursday 02 December 2010] [12:06:26] <drbobbeaty>	I'm running with the new ZMQ 2.1.0 from the new downloads site. It's running just fine, and I really appreciate all the work that's gone into it. But there is one thing, and I'm not sure what approach to take. When using epgm:// (OpenPGM) as the transport, the call to send() leaks. Not as much as 2.0.10, but it still leaks. For my application, it's still a problem. Is there anything in the "known issues" list for ZMQ or OpenPGM that might clear this up?
| [Thursday 02 December 2010] [12:06:26] <drbobbeaty>	am I on my own with the code?
| [Thursday 02 December 2010] [12:08:08] <mikko>	drbobbeaty: do you know where it leaks?
| [Thursday 02 December 2010] [12:08:26] <mikko>	im not sure if this is a known issue (first time i hear about it)
| [Thursday 02 December 2010] [12:10:25] <drbobbeaty>	I only know that if I comment out the call to send(), the leak goes away. Put it in and it leaks (for me) on the order of a couple of MB every few seconds.
| [Thursday 02 December 2010] [12:11:13] <drbobbeaty>	I know it's based on the size of the messages, but I don't have a lot of other information on it. I was going  to just get down-n-dirty with the code to try and track this down, but I wanted to ask here to see if this is something already known before I spend a few days on this.
| [Thursday 02 December 2010] [12:12:55] <mikko>	sustrik might be able to answer this better
| [Thursday 02 December 2010] [12:13:07] <mikko>	drbobbeaty: is it simple to reproduce?
| [Thursday 02 December 2010] [12:13:37] <drbobbeaty>	mikko: That's the first thing I'm going to do - make a simple test case and then go from there.
| [Thursday 02 December 2010] [12:14:03] <erickt>	does it not leak with the other protocols?
| [Thursday 02 December 2010] [12:14:39] <drbobbeaty>	erickt: not sure, going to try that too... just at the very early stages (10 min) of this process.
| [Thursday 02 December 2010] [12:21:58] <cremes>	drbobbeaty: it might just be queueing the data in memory; what kind of socket are you using?
| [Thursday 02 December 2010] [12:24:08] <cremes>	nevermind... that only makes sense for tcp transport
| [Thursday 02 December 2010] [12:24:41] <drbobbeaty>	Every idea is welcome. I'm going to do a lot of digging now and then when I have something concrete I'll send it to the mailing list.
| [Thursday 02 December 2010] [12:29:42] <mikko>	it does sound like the data is staying in some buffer
| [Thursday 02 December 2010] [12:30:27] <mikko>	drbobbeaty: are you closing the messages properly?
| [Thursday 02 December 2010] [12:30:33] <drbobbeaty>	yeah, that was my guess, because I've checked on the message itself, and that's OK -- I make a new one for each send, as I thought I read here that's the "best practices" for sending.
| [Thursday 02 December 2010] [12:30:55] <mikko>	you got message init and close for each send?
| [Thursday 02 December 2010] [12:36:32] <drbobbeaty>	I'm using the C++ API, and that does those in the zmq::message_t class, yes.
| [Thursday 02 December 2010] [12:37:14] <drbobbeaty>	mikko: I'm assuming you're asking about the message initialization and close out. The socket stays open for a "long" time.
| [Thursday 02 December 2010] [12:38:52] <mikko>	drbobbeaty: yeah, message init and close. looks like the C++ api closes the message upon destruction
| [Thursday 02 December 2010] [12:38:54] <sustrik>	drbobbeaty: are you sure you are not pushing data to 0MQ faster than PGM transfer rate?
| [Thursday 02 December 2010] [12:40:03] <sustrik>	default transmit rate is 100kb/s
| [Thursday 02 December 2010] [12:40:44] <drbobbeaty>	sustrik: I'm not sure what that rate is. I know I'm pushing about 1000 to 10,000 msgs/sec out on different epgm:// connected sockets (different sockets get different parts of the data set)... and I monitor the 10Gb Ethernet and it nowhere near the limit of the NIC - not even 50%. So I don't think I'm sending it too fast.
| [Thursday 02 December 2010] [12:41:13] <sustrik>	then look at ZMQ_RATE socket option
| [Thursday 02 December 2010] [12:41:15] <drbobbeaty>	sustrik: I set my default to 200kb/s in the construction
| [Thursday 02 December 2010] [12:41:28] <drbobbeaty>	...of each socket.
| [Thursday 02 December 2010] [12:41:36] <sustrik>	ok, and how much do you publish?
| [Thursday 02 December 2010] [12:41:52] <sustrik>	if you publish more than 200kb/s then the messages are queued
| [Thursday 02 December 2010] [12:42:42] <drbobbeaty>	I'll have to put in better measurement statistics to the logging... right now I look at messages per second, not bytes per socket per second. When I do that, I'll know.
| [Thursday 02 December 2010] [12:43:33] <sustrik>	in any case, setting transmit rate to 200kb/s on 10GbE seems overly restrictuve
| [Thursday 02 December 2010] [12:44:18] <drbobbeaty>	Yeah, I just upped it to 1Mbps and will try that
| [Thursday 02 December 2010] [14:35:27] <ngerakines>	hey folks, I've got a few questions about application design with zmq.
| [Thursday 02 December 2010] [14:36:49] <ngerakines>	In my system, i've got several load threads that subscribe to external pubsub streams and they take the messages they receive and funnel them to another thread that acts as a sort of funnel
| [Thursday 02 December 2010] [14:37:19] <ngerakines>	that funnel binds a ZMQ_PULL socket for that purpose
| [Thursday 02 December 2010] [14:37:47] <ngerakines>	what I want to do now, is create a number of worker threads that request work from that socket using ZMQ_REP
| [Thursday 02 December 2010] [14:38:17] <ngerakines>	so is it possible to have that funnel thread support both the PUSH connections from the loaders as well REP/REQ connections from workers?
| [Thursday 02 December 2010] [14:46:00] <Remoun>	ngerakines; IIUC, your use case fits into the "Request-Reply Broker" pattern, for which there's the built-in Queue device http://zguide.zeromq.org/chapter:all#toc31
| [Thursday 02 December 2010] [14:48:14] <ngerakines>	I was reading that and got the impression that messages were pushed to the workers (service b) where in my model, I want the workers to request work
| [Thursday 02 December 2010] [14:53:54] <Remoun>	AFAIK, the only way for the broker/funnel to know whether workers are available is that workers request work
| [Thursday 02 December 2010] [14:55:24] <ngerakines>	 so with that, is there a relatively easy way to create a socket that receives both PUSH and REP/REQ requests and is able to determine if an incoming message is one or the other?
| [Thursday 02 December 2010] [14:55:35] <ngerakines>	I haven't use poll much, but I'm thinking that I might have to go that route.
| [Thursday 02 December 2010] [14:55:43] <sustrik>	yes
| [Thursday 02 December 2010] [14:55:48] <sustrik>	two sockets
| [Thursday 02 December 2010] [14:55:54] <sustrik>	poll on them
| [Thursday 02 December 2010] [14:56:12] <sustrik>	read messages from both as they become available
| [Thursday 02 December 2010] [14:57:53] <ngerakines>	ok, thanks everyone
| [Thursday 02 December 2010] [17:07:10] <raydeo>	using 0mq 2.0.10 I have an inproc:// ZMQ_PAIR socket that is being used as communication between 2 threads. I'm getting an error when using zmq_connect to the socket in one thread before the other thread has done the zmq_bind... is this a known problem?
| [Thursday 02 December 2010] [17:07:26] <raydeo>	the errno received from zmq_bind is ECONNREFUSED
| [Thursday 02 December 2010] [17:14:36] <mikko>	raydeo: it's a known limitation
| [Thursday 02 December 2010] [17:14:47] <mikko>	you need to bind before connecting
| [Thursday 02 December 2010] [17:15:19] <raydeo>	mikko: that's fine, what would you suggest if I don't have control over the order those threads run? a different socket type, or a mutex?
| [Thursday 02 December 2010] [17:15:50] <mikko>	raydeo: it's a limitation of inproc transport
| [Thursday 02 December 2010] [17:16:31] <raydeo>	ok, so I'll just need to ensure externally the initialization order... shame :(
| [Thursday 02 December 2010] [18:41:50] <abrown28>	anyone listening want to answer a dumb question for me?
| [Thursday 02 December 2010] [23:20:49] <Remoun>	"If you need to know the identity of the peer you got a message from, only the XREP socket does this for you automatically. For any other socket type you must send the address explicitly, as a message part."
| [Thursday 02 December 2010] [23:21:01] <Remoun>	So how _do_ I get the address/identity?
| [Thursday 02 December 2010] [23:29:02] <the_hulk>	what is type identifier for socket, and context for C API's, or should i just declare them as void?
| [Thursday 02 December 2010] [23:44:03] <Remoun>	the_hulk; they're opaque handles, void*
| [Thursday 02 December 2010] [23:54:52] <the_hulk>	ok
| [Friday 03 December 2010] [02:16:41] <sustrik>	Remoun: just write it into the message
| [Friday 03 December 2010] [02:17:11] <Remoun>	I was/am looking for the value to write into the message :)
| [Friday 03 December 2010] [02:17:24] <sustrik>	think of something :)
| [Friday 03 December 2010] [02:19:13] <Remoun>	Relatedly, can I use semi-durable sockets such that I can actually address individual workers, but not have them eat memory when they're gone?
| [Friday 03 December 2010] [02:19:55] <Remoun>	I'm basically trying to distribute the 'broker' in the last example in the guide, while also adding a layer of authentication
| [Friday 03 December 2010] [02:22:00] <sustrik>	hm, that works only with REQ/REP pattern
| [Friday 03 December 2010] [02:22:15] <sustrik>	when you don't set identity, one is generated for you
| [Friday 03 December 2010] [02:22:40] <sustrik>	but the connections are still transient
| [Friday 03 December 2010] [02:22:46] <Remoun>	And it's generated by the REP side, right?
| [Friday 03 December 2010] [02:23:05] <sustrik>	the identity?
| [Friday 03 December 2010] [02:23:05] <Remoun>	Meaning if the worker actually talks to more than one broker, they'd have different IDs for that worker?
| [Friday 03 December 2010] [02:23:17] <sustrik>	yes
| [Friday 03 December 2010] [02:23:44] <Remoun>	Therein lies the catch...
| [Friday 03 December 2010] [02:24:16] <Remoun>	I need to avoid single points of failure, particularly with sth as involved as the broker
| [Friday 03 December 2010] [02:24:54] <Remoun>	Yet synchronizing the 'availability' across more than one node (thread, process, etc.) is nigh impossible
| [Friday 03 December 2010] [02:30:31] <Remoun>	sustrik; any ideas?
| [Friday 03 December 2010] [02:30:37] <sustrik>	i don't follow
| [Friday 03 December 2010] [02:30:40] <sustrik>	what's the problem?
| [Friday 03 December 2010] [02:32:02] <Remoun>	Splitting the load-balancing across several brokers; I don't know how to approach that
| [Friday 03 December 2010] [02:33:01] <sustrik>	connect the client to several brokers?
| [Friday 03 December 2010] [02:33:47] <Remoun>	But then more than one broker would dispatch to the same worker
| [Friday 03 December 2010] [02:33:54] <Remoun>	simultaneously, that is
| [Friday 03 December 2010] [02:35:57] <sustrik>	you have to decide what pattern are you going to use
| [Friday 03 December 2010] [02:36:11] <sustrik>	load balancing makes sense only with REQ/REP and PUSH/PULL
| [Friday 03 December 2010] [02:36:18] <sustrik>	which one are you using?
| [Friday 03 December 2010] [02:37:07] <Remoun>	I was going for REQ/REP, but now that I think about it, it can work better with PUSH/PULL
| [Friday 03 December 2010] [02:37:57] <sustrik>	what does " more than one broker would dispatch to the same worker" means with REQ/REP or PUSH/PULL?
| [Friday 03 December 2010] [02:38:56] <Remoun>	Well, a broker can only really service one request/pull at a time, right?
| [Friday 03 December 2010] [02:39:51] <sustrik>	right -- unless it dispatches it further, to a separate worker thread or somesuch
| [Friday 03 December 2010] [02:41:15] <Remoun>	I might just need to RTFM; I'll pour over the guide again
| [Friday 03 December 2010] [02:46:23] <Remoun>	Where can I read more about PUSH/PULL sockets/patterns? The guide doesn't talk much about them
| [Friday 03 December 2010] [02:47:44] <sustrik>	i think there's an chapter about it
| [Friday 03 December 2010] [02:47:49] <sustrik>	the one with "ventilator"
| [Friday 03 December 2010] [07:00:11] <the_hulk>	How do i know that server is down, from client site?
| [Friday 03 December 2010] [12:12:46] <ptrb>	if I have a push/pull set up, with one pusher and multiple pullers, is there some way to have the "push" action target a specific "puller", absent some other out-of-band communication?
| [Friday 03 December 2010] [12:13:33] <mikko>	ptrb: have each "puller" subscribe to generic and puller specific topic
| [Friday 03 December 2010] [12:13:44] <mikko>	and use puller specific topic to communicate with specific puller
| [Friday 03 December 2010] [12:15:29] <ptrb>	so pub/sub instead
| [Friday 03 December 2010] [12:16:23] <mikko>	yes
| [Friday 03 December 2010] [12:16:33] <mikko>	PUSH/PULL load balances the messages as well
| [Friday 03 December 2010] [12:16:47] <mikko>	im not sure if there is a way to message based on the ident of client using push/pull
| [Friday 03 December 2010] [12:16:52] <mikko>	sustrik might know better
| [Friday 03 December 2010] [12:17:42] <sustrik>	ptrb: PUSH socket does load balancing
| [Friday 03 December 2010] [12:17:56] <sustrik>	thus it decides which peer to send the message to itself
| [Friday 03 December 2010] [12:18:41] <mikko>	sustrik: i got solaris10 running as build slave
| [Friday 03 December 2010] [12:18:44] <mikko>	running first tests now
| [Friday 03 December 2010] [12:18:50] <mikko>	will try installing windows later on
| [Friday 03 December 2010] [12:18:58] <sustrik>	wow!
| [Friday 03 December 2010] [12:35:39] <mikko>	mato: there?
| [Friday 03 December 2010] [12:36:50] <sustrik>	mikko: i think he's travalling atm
| [Friday 03 December 2010] [12:39:55] <mikko>	i just notced that the way we unpack pgm sources doesnt seem to be portable 
| [Friday 03 December 2010] [12:39:59] <mikko>	-C option to tar
| [Friday 03 December 2010] [12:40:23] <sustrik>	shrug
| [Friday 03 December 2010] [12:41:36] <sustrik>	no idea myself
| [Friday 03 December 2010] [13:47:57] <ptrb>	is it possible to change the HWM behavior of a socket?
| [Friday 03 December 2010] [13:48:27] <ptrb>	or, failing that, poll to see the current, uh, water level?
| [Friday 03 December 2010] [13:53:46] <mikko>	watermark
| [Friday 03 December 2010] [13:53:54] <mikko>	yes, you can poll
| [Friday 03 December 2010] [13:54:04] <mikko>	it should come back as writable if hwm is reached
| [Friday 03 December 2010] [13:57:31] <ptrb>	am I stupid and missing what that function is?
| [Friday 03 December 2010] [13:58:21] <mikko>	what function?
| [Friday 03 December 2010] [13:58:58] <ptrb>	oh, you getsockopt on ZMQ_HWM?
| [Friday 03 December 2010] [13:59:15] <mikko>	zmq_poll
| [Friday 03 December 2010] [13:59:35] <mikko>	you can not get current amount of messages in transit
| [Friday 03 December 2010] [13:59:48] <mikko>	but zmq_poll should not return the socket as writable if hwm has been reached
| [Friday 03 December 2010] [14:00:40] <ptrb>	oh, okay. and that will work that way no matter what type of socket(s) you poll on
| [Friday 03 December 2010] [14:01:33] <mikko>	i've only tested on push sockets
| [Friday 03 December 2010] [14:02:04] <ptrb>	hmm.
| [Friday 03 December 2010] [14:03:01] <mikko>	not sure about pub socket
| [Friday 03 December 2010] [14:03:15] <mikko>	as the behavior with pub socket when hwm is reached is to discard messages
| [Friday 03 December 2010] [14:03:58] <ptrb>	right, which I'm trying to work around
| [Friday 03 December 2010] [14:04:36] <ptrb>	looks like the "correct" solution here is to manually manage N ZMQ_PUSH sockets... which is what I was hoping to avoid... but..
| [Friday 03 December 2010] [14:06:25] <ptrb>	OK, thanks for the tip.. if anything else strikes you in the night, feel free to let me know :)
| [Friday 03 December 2010] [14:06:41] <mikko>	you could easily test zmq_poll + pub socket
| [Friday 03 December 2010] [14:06:59] <ptrb>	yeah but that is more work than I can rightly manage at 8pm on a Friday :)
| [Friday 03 December 2010] [14:08:04] <ptrb>	cheers
| [Friday 03 December 2010] [14:09:19] <mikko>	http://zguide.zeromq.org/chapter:all
| [Friday 03 December 2010] [14:09:24] <mikko>	there is an example for zmq_poll
| [Friday 03 December 2010] [14:09:30] <mikko>	you should be able to mod that with ease
| [Saturday 04 December 2010] [17:16:10] <CIA-20>	zeromq2: 03Martin Sustrik 07master * rc80e7b8 10/ (11 files in 2 dirs): 
| [Saturday 04 December 2010] [17:16:10] <CIA-20>	zeromq2: XPUB and XSUB socket types added.
| [Saturday 04 December 2010] [17:16:10] <CIA-20>	zeromq2: These are just placeholders. At the moment XPUB behaves th same
| [Saturday 04 December 2010] [17:16:10] <CIA-20>	zeromq2: as PUB and XSUB as SUB.
| [Saturday 04 December 2010] [17:16:10] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/g8Nus1
| [Sunday 05 December 2010] [03:50:04] <CIA-20>	zeromq2: 03Martin Sustrik 07master * r2daa0bb 10/ (src/sub.cpp src/sub.hpp src/xsub.cpp src/xsub.hpp): 
| [Sunday 05 December 2010] [03:50:04] <CIA-20>	zeromq2: XSUB accepts (un)subscriptions in form of messages.
| [Sunday 05 December 2010] [03:50:04] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/ghbsFI
| [Sunday 05 December 2010] [11:20:41] <CIA-20>	rbzmq: 03Brian Buchanan 07master * r86050ce 10/ (rbzmq.c zmq.gemspec): Update to support libzmq 2.1.0 - http://bit.ly/fuzMIe
| [Sunday 05 December 2010] [17:25:20] <mikko>	mato: there?
| [Monday 06 December 2010] [00:46:54] <Guest53515>	i've been reading the docs and i see that you can send a message an basically wait for an ack (reply) back. is there a way to send and timeout in error if a reply has not been received within a timeframe
| [Monday 06 December 2010] [00:48:12] <guido_g>	no, you have to do this yourself
| [Monday 06 December 2010] [00:55:05] <Guest53515>	thanks..   can the receivee timeout or will it block forever?
| [Monday 06 December 2010] [00:56:26] <guido_g>	there is no timeout paramter for receive, but you can simulate it via poll
| [Monday 06 December 2010] [00:58:30] <guido_g>	*parameter
| [Monday 06 December 2010] [00:59:18] <Guest53515>	thanks, i was wondering about the poll.  i will have a look
| [Monday 06 December 2010] [01:00:12] <guido_g>	i'm not sure about this particular thing, but the guide is normally a good source of information
| [Monday 06 December 2010] [03:11:36] <mikko>	sustrik: there?
| [Monday 06 December 2010] [03:21:33] <sustrik>	mikko: hi
| [Monday 06 December 2010] [03:26:47] <mikko>	http://build.valokuva.org/job/ZeroMQ2-core-master_MSVC-win7/20/console
| [Monday 06 December 2010] [03:26:54] <mikko>	xpub/xsub missing from win build files?
| [Monday 06 December 2010] [03:28:16] <mikko>	brb, need to commute to the office
| [Monday 06 December 2010] [03:28:34] <sustrik>	mikko: oops
| [Monday 06 December 2010] [03:28:38] <sustrik>	let me fix that
| [Monday 06 December 2010] [03:28:53] <sustrik>	you are already building with MSVC?
| [Monday 06 December 2010] [03:29:06] <mikko>	yes, testing with win7 build slave
| [Monday 06 December 2010] [03:29:17] <sustrik>	impressive
| [Monday 06 December 2010] [03:29:20] <mikko>	http://build.valokuva.org/ -> linux, solaris10, win7 now
| [Monday 06 December 2010] [03:29:23] <mikko>	brb
| [Monday 06 December 2010] [03:29:27] <guido_g>	btw, are there already any docs xspub/ssub or is it code only currently?
| [Monday 06 December 2010] [03:29:43] <sustrik>	it's been committed yesteday
| [Monday 06 December 2010] [03:29:43] <guido_g>	*docs on xpub/xsub
| [Monday 06 December 2010] [03:29:49] <sustrik>	and does nothing useful
| [Monday 06 December 2010] [03:29:56] <guido_g>	ahhh ok
| [Monday 06 December 2010] [03:30:01] <sustrik>	it's just an infrastructure for subscription forwarding
| [Monday 06 December 2010] [03:30:02] <guido_g>	but sounds great! :)
| [Monday 06 December 2010] [03:30:25] <sustrik>	basically the idea is that subsctiptions are just messages
| [Monday 06 December 2010] [03:30:37] <sustrik>	that are passed up the message distribution tree
| [Monday 06 December 2010] [03:31:01] 	 * sustrik reboots into windows
| [Monday 06 December 2010] [03:44:33] <CIA-20>	zeromq2: 03Martin Sustrik 07master * r8a6ff4c 10/ builds/msvc/libzmq/libzmq.vcproj : 
| [Monday 06 December 2010] [03:44:33] <CIA-20>	zeromq2: xup and xsub files added to the MSVC build
| [Monday 06 December 2010] [03:44:33] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/gELabW
| [Monday 06 December 2010] [03:45:41] <guido_g>	:)
| [Monday 06 December 2010] [03:47:29] <sustrik>	re
| [Monday 06 December 2010] [03:48:34] <guido_g>	wb
| [Monday 06 December 2010] [03:50:27] <sustrik>	:)
| [Monday 06 December 2010] [04:13:18] <Steve-o>	sustrik: so any hope of back pressure on PUB sockets?
| [Monday 06 December 2010] [04:13:58] <sustrik>	what's your problem?
| [Monday 06 December 2010] [04:14:43] <Steve-o>	client sending to PGM faster than the rate limit, there's back pressure from OpenPGM but nothing from 0MQ
| [Monday 06 December 2010] [04:15:12] <Steve-o>	you can set HWM and lose messages, but the API doesn't provide any feedback
| [Monday 06 December 2010] [04:15:33] <sustrik>	Steve-o: don't set the HWM then
| [Monday 06 December 2010] [04:15:36] <Steve-o>	which forces the developer to implement their own rate engine above 0MQ at a guess
| [Monday 06 December 2010] [04:16:08] <Steve-o>	making the granular rate engine in OpenPGM pretty useless
| [Monday 06 December 2010] [04:24:15] <sustrik>	Steve-o: still there? what the problem with leaving HWM infinite?
| [Monday 06 December 2010] [04:30:09] <mikko>	sustrik: builds now
| [Monday 06 December 2010] [04:30:10] <mikko>	thanks
| [Monday 06 December 2010] [04:30:19] <sustrik>	np
| [Monday 06 December 2010] [04:30:25] <mikko>	if this trial works well ill add the win7 as permanent part
| [Monday 06 December 2010] [04:30:29] <mikko>	to the build cluster
| [Monday 06 December 2010] [04:31:14] <sustrik>	that would be great
| [Monday 06 December 2010] [04:31:23] <sustrik>	win platform is notoriously under-tested
| [Monday 06 December 2010] [04:31:54] <mikko>	sadly this build box is 32bit
| [Monday 06 December 2010] [04:32:07] <mikko>	i need to look into the stockpile of old servers if i could find 64bit iron
| [Monday 06 December 2010] [04:55:12] <mato>	mikko: hi
| [Monday 06 December 2010] [04:55:17] <mato>	mikko: you were after me?
| [Monday 06 December 2010] [05:00:49] <mikko>	mato: yeah
| [Monday 06 December 2010] [05:00:59] <mikko>	mato: -C option to tar is not portable it seems
| [Monday 06 December 2010] [05:01:10] <mato>	mikko: -C ?
| [Monday 06 December 2010] [05:01:14] <mikko>	solaris tar accepts -C when creating or replacing archive
| [Monday 06 December 2010] [05:01:23] <mato>	mikko: what is using -C?
| [Monday 06 December 2010] [05:01:34] <mikko>	yes, -C is used when extracting openpgm
| [Monday 06 December 2010] [05:02:10] <mikko>	so, im wondering that should we require gnu tar or chdir before extraction
| [Monday 06 December 2010] [05:02:17] <mikko>	i got a patch for the chdir approach somewhere
| [Monday 06 December 2010] [05:02:37] <mato>	the latter, since it is supposed to work on Solaris I guess
| [Monday 06 December 2010] [05:02:55] <mato>	anything to do with openpgm doesn't have to be portable past MinGW/Linux/Solaris
| [Monday 06 December 2010] [05:03:24] <mikko>	ok, so i'll post the patch as it is when i got time
| [Monday 06 December 2010] [05:03:36] <mikko>	mato: there is experimental win7 in the daily builds now as well
| [Monday 06 December 2010] [05:03:36] <mato>	sure, go for it
| [Monday 06 December 2010] [05:03:47] <mikko>	running visual studio 2008
| [Monday 06 December 2010] [05:03:58] <mato>	mikko: wow, how did you manage that? :-)
| [Monday 06 December 2010] [05:04:12] <mato>	mingw I could grok, but scripting VS builds ... 
| [Monday 06 December 2010] [05:04:19] <mikko>	i installed hudson as windows service and it uses msbuild command line tools to run builds
| [Monday 06 December 2010] [05:04:27] <mato>	ah, so it has support for that
| [Monday 06 December 2010] [05:04:28] <mato>	great!
| [Monday 06 December 2010] [05:04:44] <mikko>	the only pain was to install windows using vmware esx console
| [Monday 06 December 2010] [05:04:50] <mikko>	the mouse moves in jumps 
| [Monday 06 December 2010] [05:05:27] <mato>	by the way, the guy with rhat gcc3 problems solved his own problem
| [Monday 06 December 2010] [05:05:33] <mato>	so I guess we can leave that alone for now
| [Monday 06 December 2010] [05:05:51] <mikko>	i got a patch for it though
| [Monday 06 December 2010] [05:05:53] <mato>	let's see if anyone else complains that they really need to use broken RHAT gcc3 :)
| [Monday 06 December 2010] [05:06:09] <mato>	well, if you're happy with the patch, send it to the ML.
| [Monday 06 December 2010] [05:06:39] 	 * mato will be on irc somewhat intermittently this week, have builders here ...
| [Monday 06 December 2010] [06:09:00] <adalrsjr1>	hello...
| [Monday 06 December 2010] [06:09:47] <adalrsjr1>	i need run a zmq java application in machines without zmq
| [Monday 06 December 2010] [06:09:54] <adalrsjr1>	how i can do it?
| [Monday 06 December 2010] [06:10:10] <adalrsjr1>	whitout zmq installed
| [Monday 06 December 2010] [06:10:15] <adalrsjr1>	i using linux
| [Monday 06 December 2010] [06:11:29] <mikko>	adalrsjr1: currently the java binding requires libzmq
| [Monday 06 December 2010] [06:11:40] <mikko>	adalrsjr1: i don't think there is a pure java implementation
| [Monday 06 December 2010] [06:16:40] <adalrsjr1>	its my problema, i don't have libzmq in these machines
| [Monday 06 December 2010] [06:17:13] <adalrsjr1>	but i have the libzmq compiled in other pc
| [Monday 06 December 2010] [06:17:48] <mikko>	as far as i know currently you require libzmq with the java binding as it uses jni
| [Monday 06 December 2010] [06:26:17] <Steve-o>	adalrsjr1: if the Linux versions are the same you should be able to copy over the jni & core zmq dynamic libraries
| [Monday 06 December 2010] [06:28:04] <Steve-o>	well, noted for the IRC log :-)
| [Monday 06 December 2010] [06:49:02] <sustrik>	mikko, mato: a suggestion -- shouldn't we limit test_shutdown_stress to something reasonable
| [Monday 06 December 2010] [06:49:12] <sustrik>	like seting up and tearing down 100 connection
| [Monday 06 December 2010] [06:49:33] <sustrik>	so that it would work on any box without running into resource problems?
| [Monday 06 December 2010] [06:51:21] <mato>	sustrik: yes
| [Monday 06 December 2010] [06:51:29] <sustrik>	ok
| [Monday 06 December 2010] [06:51:42] <mato>	sustrik: well, maybe... it does expose problems when run properly
| [Monday 06 December 2010] [06:51:53] <sustrik>	that's nice
| [Monday 06 December 2010] [06:52:03] <mato>	sustrik: but at least on solaris there's a limit of 256 fds per process by default
| [Monday 06 December 2010] [06:52:06] <sustrik>	otoh, the builds fail bacause of it
| [Monday 06 December 2010] [06:52:23] <mato>	sure, but then how will we know we've fixed the problem :)
| [Monday 06 December 2010] [06:52:35] <mato>	maybe...
| [Monday 06 December 2010] [06:52:55] <mato>	how about we change the test to run less connections on !linux
| [Monday 06 December 2010] [06:54:19] <sustrik>	i don't think platform.hpp is included in the tests
| [Monday 06 December 2010] [06:54:29] <sustrik>	do you know you are no linux there?
| [Monday 06 December 2010] [06:59:27] <mato>	sustrik:  hang on
| [Monday 06 December 2010] [07:00:14] <mato>	sustrik: a) the tests can obviously include platform.hpp
| [Monday 06 December 2010] [07:00:34] <mato>	sustrik: b) test_shutdown_stress can call getrlimit(3) with RLIMIT_NOFILE and pick some sane value
| [Monday 06 December 2010] [07:00:40] <mato>	sustrik: for the # of iterations
| [Monday 06 December 2010] [07:00:49] <mato>	sustrik: that way we can at least ensure it won't run out of FDs
| [Monday 06 December 2010] [07:01:00] <mato>	sustrik: if it dies due to other problems then that's a valid bug...
| [Monday 06 December 2010] [07:01:23] <sustrik>	what about socket buffer size?
| [Monday 06 December 2010] [07:01:30] <mato>	what about it?
| [Monday 06 December 2010] [07:01:39] <mato>	that's a bug, we need to fix that somehow :-)
| [Monday 06 December 2010] [07:02:36] <mato>	we shouldn't be hiding bugs by modifying test cases
| [Monday 06 December 2010] [07:04:25] <sustrik>	the question is how to distinguish "out of resources" from "bug"
| [Monday 06 December 2010] [07:04:59] <mato>	then our mailbox_t needs to report back that it has run out of socket buffers, and return that to the app somehow
| [Monday 06 December 2010] [07:06:09] <sustrik>	it has to fail; at that point the system is broken beyond any hope to repair
| [Monday 06 December 2010] [07:06:51] <sustrik>	it's basically a same problem as ENOMEM
| [Monday 06 December 2010] [07:06:59] <sustrik>	is it a bug or is it not?
| [Monday 06 December 2010] [07:07:17] <mato>	well, the way we're dealing with it at the moment is a bug
| [Monday 06 December 2010] [07:07:27] <sustrik>	the assertion?
| [Monday 06 December 2010] [07:07:43] <mato>	that, and/or the fact that we're reliant on the socket buffer size so much
| [Monday 06 December 2010] [07:08:11] <mato>	step 1 would be to at least change the assertion to somehow return an errno to the application. if that's possible.
| [Monday 06 December 2010] [07:08:18] <mato>	step 2 is obviously to fix the signaler
| [Monday 06 December 2010] [07:08:36] <mato>	again, if that's possible - i know we've been through this...
| [Monday 06 December 2010] [07:08:55] <mato>	sustrik: think about it in kernel terms
| [Monday 06 December 2010] [07:09:06] <mato>	sustrik: do you panic the system if some buffer runs out? i think not.
| [Monday 06 December 2010] [07:09:47] <sustrik>	the problem is that in this case the buffer in question is part of the essential infrastructure
| [Monday 06 December 2010] [07:09:59] <sustrik>	thus when it overflows the whole thing is unusable
| [Monday 06 December 2010] [07:10:08] <sustrik>	you do panic in such a case
| [Monday 06 December 2010] [07:10:17] <sustrik>	still better than undefined behaviour
| [Monday 06 December 2010] [07:11:28] <sustrik>	anyway, i'll leave the stress test as is for now
| [Monday 06 December 2010] [08:26:59] <sustrik>	drbobbeaty: hi
| [Monday 06 December 2010] [08:28:33] <drbobbeaty>	sustrik: hi
| [Monday 06 December 2010] [08:29:40] <sustrik>	hi, have you seen steve's answer about ZMQ_RECOVERY_IVL smaller than 1 sec?
| [Monday 06 December 2010] [08:30:54] <drbobbeaty>	Yeah, he was talking about making a C-level call to OpenPGM based on the size of the buffer. Since I'm using the C++ interface, I didn't know how/if that would be possible given that I don't have access to the underlying C pointers/structs.
| [Monday 06 December 2010] [08:31:22] <sustrik>	the idea is to tweak the 0MQ source code
| [Monday 06 December 2010] [08:31:46] <sustrik>	ie. set the recovery in number of packets rather than in seconds
| [Monday 06 December 2010] [08:32:42] <sustrik>	see src/pgm_socket.cpp
| [Monday 06 December 2010] [08:33:14] <sustrik>	line 203 and 236
| [Monday 06 December 2010] [08:34:42] <drbobbeaty>	Ah! OK... I can tweak the code if needed. My question would be if this is going to be supported in some manner in the straight ZeroMQ releases. I can wait on this if it's coming out soon, or I can make the changes and then back them out when the feature becomes available from you guys.
| [Monday 06 December 2010] [08:35:08] <sustrik>	drbobbeaty: if you send a patch to the mailing list, i'll apply it
| [Monday 06 December 2010] [08:35:21] <sustrik>	just make sure that it actually works before sending it
| [Monday 06 December 2010] [08:35:35] <drbobbeaty>	he he he... yeah, that'd be a good thing to make sure :)
| [Monday 06 December 2010] [08:35:57] <sustrik>	(i don't have a test env here, so i won't be able to test it really)
| [Monday 06 December 2010] [08:35:59] <drbobbeaty>	I'll have a look and then read up on the ML diff submission process. 
| [Monday 06 December 2010] [08:36:11] <sustrik>	sure
| [Monday 06 December 2010] [08:36:19] <sustrik>	have you seen the code?
| [Monday 06 December 2010] [08:36:28] <sustrik>	the change seems to be pretty trivial
| [Monday 06 December 2010] [08:36:52] <drbobbeaty>	I think I can handle it :) But if I have any questions, I will be back to ask for help.
| [Monday 06 December 2010] [08:37:14] <sustrik>	sure
| [Monday 06 December 2010] [08:38:17] <sustrik>	drbobbeaty: ah, damn
| [Monday 06 December 2010] [08:38:42] <sustrik>	change from sec to msecs would break the backward compatibilitty :(
| [Monday 06 December 2010] [08:39:10] <drbobbeaty>	Yeah, I can imagine that... but what about a different named socket option?
| [Monday 06 December 2010] [08:39:24] <sustrik>	yes, looks like the only option atm
| [Monday 06 December 2010] [08:40:26] <drbobbeaty>	Seems fair... do you have a preference for what that name should be? ZMQ_RECOVERY_MSEC or ZMQ_RECOVERY_IVL_MSEC?
| [Monday 06 December 2010] [08:41:04] <mikko>	is that confusing?
| [Monday 06 December 2010] [08:41:12] <mikko>	two constants for effectively same option
| [Monday 06 December 2010] [08:41:34] <sustrik>	mikko: any better idea?
| [Monday 06 December 2010] [08:42:00] <mikko>	it would be still possible to change this in 2.1
| [Monday 06 December 2010] [08:42:04] <mikko>	as there is no stable release
| [Monday 06 December 2010] [08:42:17] <mikko>	beta is what it says on the tin
| [Monday 06 December 2010] [08:42:22] <sustrik>	the backward compatibility is guaranteed witin a major version
| [Monday 06 December 2010] [08:42:39] <sustrik>	so it can't be broken before 3.0
| [Monday 06 December 2010] [08:42:42] <mikko>	but things are already breaking going from 2.0 to 2.1
| [Monday 06 December 2010] [08:42:55] <mikko>	zmq_init for example
| [Monday 06 December 2010] [08:43:04] <sustrik>	how so?
| [Monday 06 December 2010] [08:43:11] <mikko>	or did that change earlier?
| [Monday 06 December 2010] [08:43:22] <sustrik>	yep, that changes somewhere at 2.0.4
| [Monday 06 December 2010] [08:43:37] <sustrik>	since then people have complained about breaking backwards compatibility
| [Monday 06 December 2010] [08:43:51] <sustrik>	so i've written compatibility guidelines
| [Monday 06 December 2010] [08:43:58] <sustrik>	let me find it...
| [Monday 06 December 2010] [08:46:54] <sustrik>	http://www.zeromq.org/docs:policies
| [Monday 06 December 2010] [08:46:59] <drbobbeaty>	sustrik, mikko: I am enjoying reading the "Contributing to 0MQ" page... as soon as I get through all this, and you guys decide how you'd like me to implement it, I'll get right on it.
| [Monday 06 December 2010] [08:47:48] <mikko>	sustrik: "It may even run, however, you should read the NEWS file so you are sure that changes made won't affect your application behaviour in subtle ways."
| [Monday 06 December 2010] [08:47:49] <sustrik>	enjoying the burocracy? :)
| [Monday 06 December 2010] [08:48:11] <mikko>	sustrik: it would still compile against the version
| [Monday 06 December 2010] [08:48:11] <sustrik>	mikko: right
| [Monday 06 December 2010] [08:48:15] <mikko>	is your policy says
| [Monday 06 December 2010] [08:48:28] <mikko>	but people using recovery IVL would need to read about the change
| [Monday 06 December 2010] [08:48:58] <sustrik>	but allocating buffer 1000x larger than expected in not really a subtle change
| [Monday 06 December 2010] [08:49:22] <sustrik>	it's pretty dangerous actually
| [Monday 06 December 2010] [08:50:20] <sustrik>	i would go for new socket option now
| [Monday 06 December 2010] [08:50:42] <sustrik>	and normalise the two options into a single one in v3.0
| [Monday 06 December 2010] [08:50:56] <mikko>	i guess that is sensible for now. i think we should keep a list things like these that need to be cleaned up on major
| [Monday 06 December 2010] [08:51:17] <sustrik>	some comments are already here: http://www.zeromq.org/docs:3-0
| [Monday 06 December 2010] [08:52:00] <sustrik>	drbobbeaty: just add a new option for now
| [Monday 06 December 2010] [08:52:13] <drbobbeaty>	sustrik: OK, that's what I'll do.
| [Monday 06 December 2010] [08:53:14] <sustrik>	something like:
| [Monday 06 December 2010] [08:53:44] <sustrik>	"RECOVERY_IVL_MSEC has precedence to RECOVERY_IVL"
| [Monday 06 December 2010] [08:54:02] <sustrik>	"however, if set to zero, it's ignored and RECOVERY_IVL is used instead"
| [Monday 06 December 2010] [08:54:07] <sustrik>	"default is zero"
| [Monday 06 December 2010] [08:54:37] <drbobbeaty>	sustrik: OK, sounds reasonable with a nice fallback.
| [Monday 06 December 2010] [09:10:51] <sustrik>	Steve-o: what out_buffer_size should I use?
| [Monday 06 December 2010] [09:11:47] <sustrik>	and what parameters you were running local_the/remote_the with?
| [Monday 06 December 2010] [09:11:53] <sustrik>	thr*
| [Monday 06 December 2010] [09:12:03] <Steve-o>	I tried 1420
| [Monday 06 December 2010] [09:12:18] <Steve-o>	and "tcp..." 100 1
| [Monday 06 December 2010] [09:12:23] <sustrik>	great
| [Monday 06 December 2010] [09:12:35] <sustrik>	i'll check that
| [Monday 06 December 2010] [09:50:42] <drbobbeaty>	sustrik: I assume all these changes for the recovery time should be to the default, 'development' release and not the 'maint' release, correct?
| [Monday 06 December 2010] [09:51:17] <mikko>	drbobbeaty: yes, just for the master branch
| [Monday 06 December 2010] [10:21:19] <toni__>	hey there. I am using a REQ socket that connects to a set of servers (XREP). Is there way to notice when a server dies? My intention is to wait for max. 2 seconds, until I consider the server as gone. But the s.recv() (s is a REQ socket) blocks. Is there a way to achieve this, or should a make use of a XREQ which is non-blocking?
| [Monday 06 December 2010] [10:21:19] <mikko>	toni__: you should be able to use zmq_poll for this
| [Monday 06 December 2010] [10:21:19] <mikko>	you can also pass ZMQ_NOBLOCK flag to zmq_recv
| [Monday 06 December 2010] [10:22:05] <toni__>	cool, thanks. great channel, for all my questions I get a answer very fast. This avoids searching the huge guide twice for such particular part of information. Thanks!
| [Monday 06 December 2010] [10:23:09] <guido_g>	toni__: there is also http://api.zeromq.org/zmq.html
| [Monday 06 December 2010] [10:26:54] <toni__>	guido_g: i know, but I expected to maybe get a correcting answer in case my solution for the problem would already be provided by zmq itself. 
| [Monday 06 December 2010] [10:27:56] <guido_g>	toni__: it was more a response to " This avoids searching the huge guide twice..."
| [Monday 06 December 2010] [10:31:06] <sustrik>	hm, this is almost a FAQ
| [Monday 06 December 2010] [10:32:13] <sustrik>	i've answered this particular question like twice in past two days
| [Monday 06 December 2010] [10:44:37] <toni__>	hey there, one more question. I could not find a way to disconnect a socket from an address it was once connected to. I can only find socket.close() but thats not what I need. So is there a way to disconnect from an address? 
| [Monday 06 December 2010] [10:49:08] <sustrik>	close the socket
| [Monday 06 December 2010] [10:50:39] <toni__>	the socket is connected to a set of addresses. In case one does not answer, I want to remove the connection to this address, so I close the socket and reconnect it to all adresses without the one that did not work?
| [Monday 06 December 2010] [10:51:49] <sustrik>	i presume that when the non answering address becomes available again, you want to reconnect to it?
| [Monday 06 December 2010] [10:52:08] <toni__>	yes
| [Monday 06 December 2010] [10:52:15] <sustrik>	0mq does that for you
| [Monday 06 December 2010] [10:52:27] <sustrik>	you don't have to care about non-anwering endpoints
| [Monday 06 December 2010] [10:53:13] <sustrik>	they are ignored and reconnected when they become available again
| [Monday 06 December 2010] [10:53:31] <toni__>	okay, thats great. Does this also mean that messages wont be send to an address that seems currently not available?
| [Monday 06 December 2010] [10:54:09] <bobdole369>	Hello everyone, tnx for letting me idle in here all weekend :x - didn't really mean to do that... OK on to it: Have a possible project in the coming weeks and am looking at 0MQ as the data transport mechanism.
| [Monday 06 December 2010] [10:54:11] <seb`>	the server side won't block if you close the socket
| [Monday 06 December 2010] [10:54:25] <bobdole369>	Few queries about a few things come to mine.
| [Monday 06 December 2010] [10:55:36] <sustrik>	toni__: yes, but set HWM to something low
| [Monday 06 December 2010] [10:55:59] <sustrik>	so that requests are not queued too much for a destination that may become unavailable later on
| [Monday 06 December 2010] [10:57:20] <toni__>	sustrik: but it can be that a message wont be sent out, and is queued until the address becomes available again? Thats what I have to avoid.
| [Monday 06 December 2010] [10:58:15] <sustrik>	that's done by resending the request once the timeout expires
| [Monday 06 December 2010] [10:58:28] <sustrik>	you should also discard duplicate replies, of course
| [Monday 06 December 2010] [10:58:55] <bobdole369>	Have a number of embedded devices in the "field" that will transmit data to a central datacenter server.  The data are infrequent small data points, perhaps 2kb of data is actually a lot.  We control these and can author the packets. Is 0MQ a suitable transport method for this data? 
| [Monday 06 December 2010] [10:59:01] <sustrik>	(the whole resend functionality should be actually implemented inside 0mq, but it's not yet)
| [Monday 06 December 2010] [10:59:48] <sustrik>	bobdole369: you want to deploy 0mq on the devices?
| [Monday 06 December 2010] [11:00:29] <toni__>	sustrik: Thanks for your help
| [Monday 06 December 2010] [11:00:49] <bobdole369>	That is possible. They are PLC style devices though, and not PC's. They do speak ansi C.
| [Monday 06 December 2010] [11:01:07] <sustrik>	toni__: you are welcome
| [Monday 06 December 2010] [11:01:29] <sustrik>	bobdole369: what about the OS?
| [Monday 06 December 2010] [11:02:01] <bobdole369>	On the PLC devices
| [Monday 06 December 2010] [11:06:13] <stephank>	bobdole369: No need to apologize for idling around, that's pretty common practice on IRC. Zeromq is C++ and builds on top of BSD sockets and threading APIs, amongst others. Those are typically implemented by an OS. Are those provided by your embedded platform.
| [Monday 06 December 2010] [11:24:34] <drbobbeaty>	sustrik: I'm looking at the code and can't find any reference to tpdu_size, but I do find references to get_max_tsdu_size(). Should I be using the tsdu_size from this call, or am I missing something obvious? I'm trying to convert either timespan into a count of sequence numbers - as per Steven's suggestion.
| [Monday 06 December 2010] [11:29:23] <bobdole369>	OIC ya sockets and the API does seem to be done by the embedded platform - M258 Schneider PLC
| [Monday 06 December 2010] [11:35:15] <sustrik>	drbobbeaty: ask steven about what value to actually use
| [Monday 06 December 2010] [11:35:35] <sustrik>	i am not an expert on PGM
| [Monday 06 December 2010] [11:35:51] <drbobbeaty>	sustrik: Got it... will do.
| [Monday 06 December 2010] [11:35:54] <sustrik>	alternatively you may find the definitions in RFC3208
| [Monday 06 December 2010] [12:34:26] <bobdole369>	I'm a fair bit noob, so can I ask what is the advantage that 0MQ holds over OS calls and sockets?
| [Monday 06 December 2010] [12:34:57] <mikko>	bobdole369: there are several
| [Monday 06 December 2010] [12:35:14] <mikko>	i think personally the biggest advantage is work in terms of messages rather than bytes
| [Monday 06 December 2010] [12:35:46] <mikko>	normally when writing a non-blocking server you have the problem of getting EAGAIN back and then reading a bit more bytes and maintaining state of where the protocol boundaries go
| [Monday 06 December 2010] [12:36:19] <mikko>	another benefit is being able to switch almost transparently between different transports
| [Monday 06 December 2010] [12:36:27] <mikko>	and of course the built-in messaging patterns
| [Monday 06 December 2010] [12:36:40] <mikko>	publish-subscribe, request-reply etc
| [Monday 06 December 2010] [12:36:50] <bobdole369>	Yes the patterns are mostly what brought me here.
| [Monday 06 December 2010] [12:37:36] <mikko>	there are several other benefits as well
| [Monday 06 December 2010] [14:10:11] <jhawk28>	sustrik: are you here?
| [Monday 06 December 2010] [14:24:25] <delaney>	are there any up to date C# examples?
| [Monday 06 December 2010] [14:29:40] <mikko>	delaney: the examples are usually pretty portable
| [Monday 06 December 2010] [14:29:52] <mikko>	you should get the hang of C# by looking at here https://github.com/zeromq/clrzmq2
| [Monday 06 December 2010] [15:08:22] <sustrik>	jhawk28: hi
| [Monday 06 December 2010] [16:36:55] <CIA-20>	zeromq2: 03Martin Sustrik 07master * rec61751 10/ (src/pub.cpp src/sub.cpp src/xpub.cpp src/xsub.cpp): 
| [Monday 06 December 2010] [16:36:55] <CIA-20>	zeromq2: options.type correctly set for PUB/SUB/XPUB/XSUB
| [Monday 06 December 2010] [16:36:55] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/g0JAEI
| [Monday 06 December 2010] [16:58:28] <CIA-20>	zeromq2: 03Martin Sustrik 07master * r8d6cafe 10/ (10 files): 
| [Monday 06 December 2010] [16:58:28] <CIA-20>	zeromq2: All devices conflated into a single implementation.
| [Monday 06 December 2010] [16:58:28] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/hbyNJH
| [Monday 06 December 2010] [17:11:12] <CIA-20>	zeromq2: 03Martin Sustrik 07master * r73bbcb5 10/ builds/msvc/libzmq/libzmq.vcproj : 
| [Monday 06 December 2010] [17:11:12] <CIA-20>	zeromq2: MSVC build fixed
| [Monday 06 December 2010] [17:11:12] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/gHkbTx
| [Tuesday 07 December 2010] [03:08:08] <the_hulk>	hi, for C API's on server side, i do not have to fork? it seems to be taken care of?
| [Tuesday 07 December 2010] [03:08:46] <Steve-o>	fork to do what?
| [Tuesday 07 December 2010] [03:12:13] <the_hulk>	fork to handle multiple clients, as we do with normal sockets fds
| [Tuesday 07 December 2010] [03:12:31] <Steve-o>	and thread pooling, etc, ok 
| [Tuesday 07 December 2010] [03:14:09] <Steve-o>	It's covered pretty well in the guide, http://zguide.zeromq.org/chapter:all
| [Tuesday 07 December 2010] [03:19:06] <the_hulk>	ohk
| [Tuesday 07 December 2010] [05:10:53] <CIA-20>	zeromq2: 03Martin Lucina 07master * r9bb5323 10/ doc/zmq_socket.txt : 
| [Tuesday 07 December 2010] [05:10:53] <CIA-20>	zeromq2: Clarify zmq_send() operation for ZMQ_PUB sockets
| [Tuesday 07 December 2010] [05:10:53] <CIA-20>	zeromq2: Signed-off-by: Martin Lucina <mato@kotelna.sk> - http://bit.ly/eNDyqm
| [Tuesday 07 December 2010] [05:16:25] <CIA-20>	zeromq2: 03Mikko Koppanen 07master * raed2eea 10/ (acinclude.m4 configure.in): 
| [Tuesday 07 December 2010] [05:16:25] <CIA-20>	zeromq2: Fix visibility on rhel4
| [Tuesday 07 December 2010] [05:16:25] <CIA-20>	zeromq2: Signed-off-by: Mikko Koppanen <mkoppanen@php.net> - http://bit.ly/hue9Av
| [Tuesday 07 December 2010] [05:16:27] <CIA-20>	zeromq2: 03Mikko Koppanen 07master * ra335315 10/ acinclude.m4 : 
| [Tuesday 07 December 2010] [05:16:27] <CIA-20>	zeromq2: Fix werror flag store/restore
| [Tuesday 07 December 2010] [05:16:27] <CIA-20>	zeromq2: Signed-off-by: Mikko Koppanen <mkoppanen@php.net> - http://bit.ly/idiJwf
| [Tuesday 07 December 2010] [05:16:28] <CIA-20>	zeromq2: 03Mikko Koppanen 07master * r1d81d2f 10/ configure.in : 
| [Tuesday 07 December 2010] [05:16:28] <CIA-20>	zeromq2: tar doesn't accept -C flag on solaris while extracting
| [Tuesday 07 December 2010] [05:16:28] <CIA-20>	zeromq2: Signed-off-by: Mikko Koppanen <mkoppanen@php.net> - http://bit.ly/hrR0E7
| [Tuesday 07 December 2010] [07:04:04] <ptrb>	just to confirm -- no problem making multiple connect() calls on a single ZMQ_SUB socket, right?
| [Tuesday 07 December 2010] [07:34:58] <drbobbeaty>	ptrb: correct. You can have multiple connect() calls to one ZMQ_SUB socket.
| [Tuesday 07 December 2010] [07:35:37] <drbobbeaty>	In order to "tear down" the socket, you have to drop/close the socket. Meaning, you can't disconnect() just one of the connections - you have to take them all down.
| [Tuesday 07 December 2010] [07:38:08] <Steve-o>	unbind/disconnect was discussed previously:  http://thread.gmane.org/gmane.network.zeromq.devel/4369
| [Tuesday 07 December 2010] [07:47:07] <ptrb>	cool. thanks.
| [Tuesday 07 December 2010] [09:43:32] <sustrik_>	drbobbeaty: hi
| [Tuesday 07 December 2010] [09:43:50] <drbobbeaty>	sustrik: hi... I sent in the patch to the ML.
| [Tuesday 07 December 2010] [09:44:15] <sustrik_>	yes, just got it
| [Tuesday 07 December 2010] [09:44:19] <sustrik_>	a minor point
| [Tuesday 07 December 2010] [09:44:32] <sustrik_>	subscribe to the mailing list
| [Tuesday 07 December 2010] [09:44:40] <sustrik_>	otherwise the messages are blocked
| [Tuesday 07 December 2010] [09:44:46] <sustrik_>	and i have to approve them by hand
| [Tuesday 07 December 2010] [09:45:00] <sustrik_>	if you don't want to get the traffic, you can switch that off
| [Tuesday 07 December 2010] [09:45:12] <sustrik_>	but still be member of the list
| [Tuesday 07 December 2010] [09:45:16] <drbobbeaty>	Funny thing, I am subscribed, and I still keep getting blocked. Pieter talked to me about that, and we walked through it together. Very puzzling.
| [Tuesday 07 December 2010] [09:45:29] <sustrik_>	hm, let me see
| [Tuesday 07 December 2010] [09:45:42] <drbobbeaty>	Please do... I'd love to not bother you guys.
| [Tuesday 07 December 2010] [09:46:29] <sustrik_>	hm, i don't see you in the members list
| [Tuesday 07 December 2010] [09:46:42] <sustrik_>	any idea what email address you have used to subscribe?
| [Tuesday 07 December 2010] [09:46:53] <drbobbeaty>	drbob@TheManFromSPUD.com
| [Tuesday 07 December 2010] [09:47:10] <drbobbeaty>	That's what I use to "maintain" the ML on it's web site. 
| [Tuesday 07 December 2010] [09:47:11] <sustrik_>	aha
| [Tuesday 07 December 2010] [09:47:21] <sustrik_>	but the emails you send are from a different address
| [Tuesday 07 December 2010] [09:47:31] <drbobbeaty>	OH! Duh.
| [Tuesday 07 December 2010] [09:47:36] <sustrik_>	comcast
| [Tuesday 07 December 2010] [09:47:46] <drbobbeaty>	That's it... outgoing != incoming. I'll change that.
| [Tuesday 07 December 2010] [09:47:51] <sustrik_>	great
| [Tuesday 07 December 2010] [09:47:52] <drbobbeaty>	Thanks for the pointer.
| [Tuesday 07 December 2010] [09:48:00] <sustrik_>	i'll have a look at your patch shortly
| [Tuesday 07 December 2010] [09:48:58] <drbobbeaty>	I hope it's clean and easy. And adheres to the buidelines.
| [Tuesday 07 December 2010] [09:51:05] <sustrik_>	one thing i am not sure of: is it possible that someone would want recovery ivl of zero?
| [Tuesday 07 December 2010] [09:51:21] <sustrik_>	unreliable multicast...
| [Tuesday 07 December 2010] [09:51:32] <sustrik_>	i am not even sure it's possible with OpenPGM
| [Tuesday 07 December 2010] [09:51:57] <sustrik_>	if so, the default should be -1 rather than 0
| [Tuesday 07 December 2010] [09:52:16] <sustrik_>	let me ask steven
| [Tuesday 07 December 2010] [10:17:32] <toni_>	hi there. I am using a REQ socket doing socket.recv(zmq.NOBLOCK), but I am getting a "ZMQError: Resource temporarily unavailable" (using the python binding). As I saw in the docs for recv and zmq.NONBLOCK, there is this little sentence:"If there are no messages available on the specified socket, the zmq_recv() function shall fail with errno set to EAGAIN." I dont really understand. So the NOBLOCK option raises an error in case no messag
| [Tuesday 07 December 2010] [10:20:32] <cremes>	toni_: you see that "resource unavailable" message when your REQ socket is *not* connected to any REP (or XREP) sockets
| [Tuesday 07 December 2010] [10:20:46] <cremes>	make sure you have a z-endpoint
| [Tuesday 07 December 2010] [10:21:01] <cremes>	with an active socket attached to it
| [Tuesday 07 December 2010] [10:21:53] <toni_>	cremes: but it should as it all works fine since I dont specify the NOBLOCk option @ recv()
| [Tuesday 07 December 2010] [10:22:32] <toni_>	maybe its not connected yet?
| [Tuesday 07 December 2010] [10:28:37] <Guthur>	Should the timeout work with subscriber nodes?
| [Tuesday 07 December 2010] [10:28:43] <Guthur>	with polling
| [Tuesday 07 December 2010] [10:29:13] <Guthur>	It works fine if I set -1, but seems to not pickup messages when a timeout value is set
| [Tuesday 07 December 2010] [10:31:40] <toni_>	cremes: okay, very strange.... the error disapears when I dont do zmq.NOBLOCK in s.recv(). When I specify the option, the error is raised. But why? The socket should be connected, as the error is not raised when no block is not specified
| [Tuesday 07 December 2010] [10:43:50] <cremes>	toni_: interesting... it's funny but i *only* ever do noblock send/recv so i don't understand what is happening in the blocking scenario
| [Tuesday 07 December 2010] [10:44:02] <cremes>	are you *certain* that the other socket has connected?
| [Tuesday 07 December 2010] [10:44:55] <toni_>	cremes: yes I am really certain. But I found the solution describes here https://github.com/zeromq/pyzmq/issues/36#issue/36
| [Tuesday 07 December 2010] [10:47:57] <cremes>	toni_: hmmm, ok
| [Tuesday 07 December 2010] [11:23:22] <mikko>	mato: looks like solaris10 is still not happy
| [Tuesday 07 December 2010] [11:24:21] <mato>	mikko: it used to be, has your visibility change broken something?
| [Tuesday 07 December 2010] [11:24:36] <mikko>	mato: http://build.valokuva.org/job/ZeroMQ2-core-master-SunStudio-solaris10/21/console
| [Tuesday 07 December 2010] [11:24:41] <mikko>	when building --with-pgm
| [Tuesday 07 December 2010] [11:25:07] <mato>	mikko: ah, ok, i'll look at it later, in the middle of dissecting the linux network stack with sustrik right now
| [Tuesday 07 December 2010] [11:25:45] <mikko>	tries to include <sys/epoll.h>
| [Tuesday 07 December 2010] [11:26:27] <mato>	i guess openpgm in zmq has not been ported to solaris properly then
| [Tuesday 07 December 2010] [11:28:50] <mikko>	will look into it tonight
| [Tuesday 07 December 2010] [12:27:21] <mikko>	pfffff
| [Tuesday 07 December 2010] [13:04:29] <toni_>	I am using  the python binding, having a REQ socket connected to a XREP socket. When I try to send from the REQ socket I get "zmq.core.error.ZMQError: Operation cannot be accomplished in current state". Any ideas?
| [Tuesday 07 December 2010] [13:06:33] <cremes>	toni_: yes, req/rep sockets enforce a strict 1 send / 1 recv model; trying to do 2 sends or 2 recvs in a row generates a state machine error
| [Tuesday 07 December 2010] [13:06:46] <cremes>	look at the docs for req/rep
| [Tuesday 07 December 2010] [13:12:42] <drbobbeaty>	sustrik: my patch has a problem with it... I need to send you an additional change for using sequence numbers with OpenPGM. My mistake. Sorry.
| [Tuesday 07 December 2010] [13:12:54] <toni_>	cremes: Thanks, thats the code snippet: https://gist.github.com/732161 the "aaaa". See the link for the traceback
| [Tuesday 07 December 2010] [13:13:27] <drbobbeaty>	sustrik: maybe it's not a problem... I'll send the details to the mailing list and you can decide.
| [Tuesday 07 December 2010] [13:13:56] <cremes>	toni_: your problem is at line 40
| [Tuesday 07 December 2010] [13:14:06] <cremes>	you need a recv in that block
| [Tuesday 07 December 2010] [13:14:12] <cremes>	again, read the docs on req/rep
| [Tuesday 07 December 2010] [13:14:20] <cremes>	you must do alternating send/recv with each one
| [Tuesday 07 December 2010] [13:14:37] <cremes>	you *cannot* just send with either socket; there must always be a matching recv
| [Tuesday 07 December 2010] [13:14:51] <cremes>	the pattern is request/reply, not request/request/request/request/reply
| [Tuesday 07 December 2010] [13:14:53] <cremes>	:)
| [Tuesday 07 December 2010] [13:19:58] <toni_>	cremes: thanks
| [Tuesday 07 December 2010] [13:20:38] <cremes>	toni_: you are welcome... be sure to check out the guide on the web site; it covers that topic
| [Tuesday 07 December 2010] [13:21:29] <cremes>	andrewvc: planning to do another ffi-rzmq and zmqmachine release after 2.1 is out of beta
| [Tuesday 07 December 2010] [13:21:41] <andrewvc>	nice!
| [Tuesday 07 December 2010] [13:21:43] <cremes>	if you have anything you'd like to be in there, that's our deadline ;)
| [Tuesday 07 December 2010] [13:22:03] <toni_>	cremes: I already read it, I also constructed the very last example in python. I just had some truble with the NOBLOCK option and tried to debug from scretch. Maybe its enough for today, after 10 hours of coding :-)
| [Tuesday 07 December 2010] [13:22:03] <andrewvc>	well, I was hoping to hack on it sometime soon, but I'm moving this weekend
| [Tuesday 07 December 2010] [13:22:15] <andrewvc>	I've had about zero free time the last couple weeks
| [Tuesday 07 December 2010] [13:22:25] <andrewvc>	unfortunately
| [Tuesday 07 December 2010] [13:22:38] <cremes>	toni_: np; we'll be here in channel next time you need help... take a break
| [Tuesday 07 December 2010] [13:22:51] <cremes>	andrewvc: yeah, real life is constantly getting in the way!
| [Tuesday 07 December 2010] [13:23:05] <andrewvc>	lol, so true
| [Tuesday 07 December 2010] [13:23:25] <andrewvc>	i'm actually going to la.rb hack night tonight, was hoping to get a little EM work there
| [Tuesday 07 December 2010] [13:23:45] <cremes>	cool... see if you can't recruit a few more 0mq hackers
| [Tuesday 07 December 2010] [13:24:06] <andrewvc>	hehe, I'm trying it's so fun to play with.
| [Tuesday 07 December 2010] [13:24:23] <andrewvc>	evanphx is usually there btw, I know you worked pretty closely with him on some ffi bugs right?
| [Tuesday 07 December 2010] [13:25:21] <cremes>	andrewvc: yeah, i did; the api drift between the rbx ffi support and the ffi gem caused him a lot of grief
| [Tuesday 07 December 2010] [13:25:35] <cremes>	he was pretty upset about *many* of the additions
| [Tuesday 07 December 2010] [13:25:51] <andrewvc>	hehe, yeah we had a similar conversation
| [Tuesday 07 December 2010] [13:25:55] <cremes>	i use 0mq with rbx daily; it's the best way to profile and debug my code these days
| [Tuesday 07 December 2010] [13:26:04] <andrewvc>	agreed, best stack trace for issues
| [Tuesday 07 December 2010] [13:26:13] <cremes>	yep, that too
| [Tuesday 07 December 2010] [13:26:26] <cremes>	it's quickly becoming my ruby of choice
| [Tuesday 07 December 2010] [13:26:38] <andrewvc>	I've wanted to test my employers code on rbx, but hpricot's sitting in the way
| [Tuesday 07 December 2010] [13:26:39] <cremes>	as soon as it gets windows support i'll use it there too
| [Tuesday 07 December 2010] [13:26:50] <cremes>	C extension issues?
| [Tuesday 07 December 2010] [13:27:08] <andrewvc>	yep, and I think it's one that no one's planning on fixing
| [Tuesday 07 December 2010] [13:27:24] <cremes>	direct RHASH access or something nutty?
| [Tuesday 07 December 2010] [13:28:48] <andrewvc>	oh, well look what google turned up https://github.com/rubinius/hpricot
| [Tuesday 07 December 2010] [13:28:57] <andrewvc>	someone did fix it lol
| [Tuesday 07 December 2010] [13:29:02] <cremes>	ha!
| [Tuesday 07 December 2010] [13:29:11] <cremes>	no more excuses, andrewvc !
| [Tuesday 07 December 2010] [13:29:14] <andrewvc>	hehe
| [Tuesday 07 December 2010] [13:29:32] <andrewvc>	nope, well, one more, engineyard doesn't officially support rbx, but that's a minor hurdle
| [Tuesday 07 December 2010] [13:29:47] <cremes>	really? well, that's got to change sometime soon
| [Tuesday 07 December 2010] [13:29:54] <cremes>	it's all ey guys working on it!
| [Tuesday 07 December 2010] [13:29:59] <andrewvc>	yeah, weird eh?
| [Tuesday 07 December 2010] [13:30:19] <cremes>	oh, i know why... they are having trouble creating an ebuild recipe for it under gentoo
| [Tuesday 07 December 2010] [13:30:29] <andrewvc>	the default choices are only 1.8.7, REE and 1.8.6
| [Tuesday 07 December 2010] [13:30:29] <cremes>	i saw whyaines chatting about it with evan recently
| [Tuesday 07 December 2010] [13:30:40] <cremes>	no jruby even?
| [Tuesday 07 December 2010] [13:30:44] <andrewvc>	no
| [Tuesday 07 December 2010] [13:30:45] <cremes>	now i'm shocked
| [Tuesday 07 December 2010] [13:30:55] <andrewvc>	but the reality of EY is that everyone uses chef and customizes everything
| [Tuesday 07 December 2010] [13:31:07] <andrewvc>	EY is more a starting point than a destination
| [Tuesday 07 December 2010] [13:31:12] <cremes>	hmmmmm
| [Tuesday 07 December 2010] [13:31:20] <andrewvc>	not like heroku at all, we have so many changes to the stack
| [Tuesday 07 December 2010] [14:11:23] <raspi>	where i could find config examples for zmq_(queue|forwarder|streamer). manual gives only TBA.
| [Tuesday 07 December 2010] [14:50:40] <mikko>	raspi: i think in the code at the moment
| [Tuesday 07 December 2010] [14:50:50] <mikko>	raspi: i don't think there are written examples anywhere
| [Tuesday 07 December 2010] [14:51:10] <raspi>	ok :)
| [Tuesday 07 December 2010] [14:51:32] <mikko>	if you look at devices/zmq_queue/ in the source
| [Tuesday 07 December 2010] [14:51:41] <mikko>	the schema should be fairly easy to deduct from the code
| [Tuesday 07 December 2010] [15:58:54] <toni_>	I have a REQ client connected to 2 XREP server. When one server dies, the socket.recv() on the client blocks for ever. The other server is still available, but doesnt get any requests. How can I prevent this starvation?
| [Tuesday 07 December 2010] [15:59:47] <toni_>	I also tried to use a nonblocking XREQ socket on the client and ran in the same issue
| [Tuesday 07 December 2010] [16:04:38] <mikko>	it blocks even if you pass ZMQ_NOBLOCK?
| [Tuesday 07 December 2010] [16:06:15] <toni_>	I thought the XREQ socket would be nonblocking?
| [Tuesday 07 December 2010] [16:07:34] <mikko>	it has unrestricted send/receive pattern but it's no non-blocking by default as far as i know
| [Tuesday 07 December 2010] [16:07:59] <mikko>	have you tried passing ZMQ_NOBLOCK to recv and checking for EAGAIN ?
| [Tuesday 07 December 2010] [16:09:04] <mikko>	you can also look at zmq_poll
| [Tuesday 07 December 2010] [16:09:23] <toni_>	mikko yes I did. I found the snippet at the pyzmq issues
| [Tuesday 07 December 2010] [16:11:20] <toni_>	mikko: thanks, I think I found my bug
| [Tuesday 07 December 2010] [16:12:02] <mikko>	np
| [Tuesday 07 December 2010] [22:25:09] <PeterTork>	Hello. I have a rather odd model that I want to build in 0MQ and was looking for some advice there. We have web servers running presentation code, and they are being designed to talk to a one or more processes (which we are jokingly calling the MCP) that will do various validation tests on the RPC calls they are making before handing them to another layer of servers that will handle actually doing stuff. We would like to h
| [Tuesday 07 December 2010] [22:38:35] <Steve-o>	like to h...?
| [Tuesday 07 December 2010] [22:39:08] <Steve-o>	Are you looking from Mongrel2?  http://mongrel2.org/home
| [Tuesday 07 December 2010] [22:46:52] <Steve-o>	PeterTork: IRC limits line length, try the mailing list if you want to post a longer question
| [Tuesday 07 December 2010] [22:54:26] <bsiemon>	hello all, A quick question about an example from the guide. In examples/C/lruqueue.c. If one removes the id assignment from the client threads, the clients see to no longer receive messages.
| [Tuesday 07 December 2010] [22:54:50] <bsiemon>	on os x, zmq build 2.0.10
| [Tuesday 07 December 2010] [22:56:46] <bsiemon>	it seems to only happen if the client is running within its own process rather than in a thread with the other example code
| [Tuesday 07 December 2010] [23:04:38] <Steve-o>	bsiemon: does this also occur with 2.1, or could it be a permission problem with the unix socket endpoint?
| [Tuesday 07 December 2010] [23:04:54] <bsiemon>	it did also occur in 2.1
| [Tuesday 07 December 2010] [23:05:00] <bsiemon>	but I think I am just being dumb
| [Tuesday 07 December 2010] [23:05:10] <bsiemon>	sorry to bother you
| [Tuesday 07 December 2010] [23:06:19] <Steve-o>	from what I can see from the source code I would move the endpoints to /tmp
| [Tuesday 07 December 2010] [23:06:47] <Steve-o>	it doesn't look like the code will work out of the box
| [Tuesday 07 December 2010] [23:09:17] <bsiemon>	Steve-o: I see
| [Tuesday 07 December 2010] [23:09:29] <bsiemon>	Steve-o: Thanks
| [Tuesday 07 December 2010] [23:09:34] <Steve-o>	look at zmq_ipc for example usage, http://api.zeromq.org/zmq_ipc.html
| [Tuesday 07 December 2010] [23:13:02] <Steve-o>	well try a different path, the example path should be the current directory
| [Tuesday 07 December 2010] [23:13:41] <Steve-o>	so you should see a frontend.ipc and backend.ipc file in the directory listing,
| [Tuesday 07 December 2010] [23:14:26] <bsiemon>	yes I see that now
| [Tuesday 07 December 2010] [23:15:05] <Steve-o>	You might have issues with multiple users, discussion can be found on the list:  http://www.mail-archive.com/zeromq-dev@lists.zeromq.org/msg03151.html
| [Tuesday 07 December 2010] [23:16:34] <bsiemon>	Steve-o: If I put the call to s_set_id back into the client code
| [Tuesday 07 December 2010] [23:16:45] <bsiemon>	Steve-o: It works with out a hitch
| [Tuesday 07 December 2010] [23:17:22] <Steve-o>	oh ok
| [Tuesday 07 December 2010] [23:18:09] <bsiemon>	Is there anything special to with uuid generation on os x?
| [Tuesday 07 December 2010] [23:18:34] <bsiemon>	from what I have read the lib call seem to be different from os x to linux
| [Tuesday 07 December 2010] [23:19:10] <bsiemon>	I am sure I will slog through it, thanks for the help!
| [Tuesday 07 December 2010] [23:21:45] <Steve-o>	bsiemon: pass, some Linux versions have another library with the same name
| [Tuesday 07 December 2010] [23:22:48] <Steve-o>	it does look the same from the documentation, http://developer.apple.com/library/mac/#documentation/Darwin/Reference/ManPages/man3/uuid.3.html
| [Tuesday 07 December 2010] [23:42:15] <Steve-o>	lol, the lruqueue example aborts on Linux
| [Wednesday 08 December 2010] [03:38:19] <zedas>	sustrik: looks like debian included mongrel2, but included the old 2.0.6 version before the api change for zmq_init
| [Wednesday 08 December 2010] [03:39:16] <sustrik>	hm
| [Wednesday 08 December 2010] [03:39:22] <sustrik>	0mq is in debian-unstable
| [Wednesday 08 December 2010] [03:40:32] <sustrik>	we deliberately haven't pushed it to the stable as we weren't 100% sure about the API by then
| [Wednesday 08 December 2010] [03:47:14] <Guthur>	circa my question yesterday, can anyone confirm that poll timeouts are working with sub nodes
| [Wednesday 08 December 2010] [03:50:30] <sustrik>	Guthur: are they not?
| [Wednesday 08 December 2010] [03:51:11] <Guthur>	does seem to be working for me, the code works fine when I set -1
| [Wednesday 08 December 2010] [03:51:17] <Guthur>	dose/doesn't
| [Wednesday 08 December 2010] [03:51:47] <Guthur>	but if I actually set a timeout it seems to timeout quickly and I receive nothing
| [Wednesday 08 December 2010] [03:56:56] <sustrik>	what version are you using?
| [Wednesday 08 December 2010] [04:00:26] <Guthur>	2.0.10
| [Wednesday 08 December 2010] [04:00:41] <sustrik>	ah, that's a documented behaviour
| [Wednesday 08 December 2010] [04:00:43] <Guthur>	sustrik: ^
| [Wednesday 08 December 2010] [04:00:51] <Guthur>	oh you seen, sorry
| [Wednesday 08 December 2010] [04:00:57] <sustrik>	zmq_poll waits for "up to" microseconds
| [Wednesday 08 December 2010] [04:01:05] <Guthur>	Yeah I seen the upto
| [Wednesday 08 December 2010] [04:01:15] <sustrik>	anyway, this have been changed in 2.1
| [Wednesday 08 December 2010] [04:01:15] <Guthur>	but it's not actually 'working' in any sense
| [Wednesday 08 December 2010] [04:01:30] <sustrik>	it honours timeouts precisely
| [Wednesday 08 December 2010] [04:01:52] <sustrik>	is there a bug?
| [Wednesday 08 December 2010] [04:01:55] <Guthur>	ok, but surely as it stands in 2.0.10 its pretty much broke
| [Wednesday 08 December 2010] [04:02:05] <sustrik>	what's the problem?
| [Wednesday 08 December 2010] [04:02:36] <Guthur>	Well it timeout so quick that I don't receive anything
| [Wednesday 08 December 2010] [04:02:45] <Guthur>	and this isn't exactly a slow connection
| [Wednesday 08 December 2010] [04:03:03] <Guthur>	It's local TCP
| [Wednesday 08 December 2010] [04:03:03] <sustrik>	well, it's documented behaviour
| [Wednesday 08 December 2010] [04:03:12] <sustrik>	you have to restart the poll in such case
| [Wednesday 08 December 2010] [04:03:17] <sustrik>	or switch to 2.1 :)
| [Wednesday 08 December 2010] [04:03:40] <Guthur>	hehe, ok
| [Wednesday 08 December 2010] [04:03:43] <sustrik>	actually, it's a performance issue
| [Wednesday 08 December 2010] [04:04:06] <sustrik>	the poll that can exit prematurely is faster than the one honouring the timeout
| [Wednesday 08 December 2010] [04:04:20] <sustrik>	what we've done in 2.1 was adding ZMQ_FD
| [Wednesday 08 December 2010] [04:04:31] <Guthur>	so I suppose in 2.0.10 what one would have to do is engineer some honourable timeout mechanism on top
| [Wednesday 08 December 2010] [04:04:47] <sustrik>	which allows you to poll and handle timeouts yourself
| [Wednesday 08 December 2010] [04:04:50] <sustrik>	efficiently
| [Wednesday 08 December 2010] [04:05:01] <sustrik>	zmq_poll is less efficient but honours timeouts
| [Wednesday 08 December 2010] [04:05:07] <Guthur>	so really it's just a non blocking poll
| [Wednesday 08 December 2010] [04:05:10] <Guthur>	essentially
| [Wednesday 08 December 2010] [04:05:27] <Guthur>	the 2.0.10 version that is
| [Wednesday 08 December 2010] [04:05:35] <sustrik>	Guthur: it blocks
| [Wednesday 08 December 2010] [04:05:39] <sustrik>	but can exit at times
| [Wednesday 08 December 2010] [04:05:54] <sustrik>	basically, it exits when "something happens"
| [Wednesday 08 December 2010] [04:06:03] <sustrik>	say a new connection is established or somesuch
| [Wednesday 08 December 2010] [04:06:15] <Guthur>	my behaviour is that it timeouts in approximately less than a second
| [Wednesday 08 December 2010] [04:06:20] <Guthur>	no matter what I set
| [Wednesday 08 December 2010] [04:06:42] <sustrik>	possibly the connection being established
| [Wednesday 08 December 2010] [04:06:57] <Guthur>	I'll try 2.1
| [Wednesday 08 December 2010] [04:07:02] <sustrik>	ok
| [Wednesday 08 December 2010] [04:07:42] <Guthur>	my only worry with 2.1 is that it is not yet very mature
| [Wednesday 08 December 2010] [04:07:57] <Guthur>	i.e. there has been very little room for feedback
| [Wednesday 08 December 2010] [04:09:32] <sustrik>	it's up to you
| [Wednesday 08 December 2010] [04:09:43] <sustrik>	in 2.0 you can simply add a wrapper function on top of zmq_poll
| [Wednesday 08 December 2010] [04:09:55] <sustrik>	that would check for whether the timout was reached
| [Wednesday 08 December 2010] [04:10:02] <sustrik>	and restart the poll if it was not
| [Wednesday 08 December 2010] [04:10:13] <Guthur>	it depends on how soon we roll out to our app
| [Wednesday 08 December 2010] [04:10:48] <Guthur>	our rollout certainly wont be until some time in 2011 so it might be ok
| [Wednesday 08 December 2010] [04:11:08] <sustrik>	that's three weeks :)
| [Wednesday 08 December 2010] [04:11:19] <sustrik>	anyway, even the wrapper function is viable
| [Wednesday 08 December 2010] [04:11:25] <sustrik>	it's 10 lines of code
| [Wednesday 08 December 2010] [04:13:02] <Guthur>	hehe, I suppose writing a wrapper will give me some coding to do this morning
| [Wednesday 08 December 2010] [04:14:10] <sustrik>	now = gettimeofday ();
| [Wednesday 08 December 2010] [04:14:18] <sustrik>	while (true) {
| [Wednesday 08 December 2010] [04:14:32] <sustrik>	    events = zmq_poll ();
| [Wednesday 08 December 2010] [04:14:57] <sustrik>	    if (!events && now + timeout > gettimeofday ())
| [Wednesday 08 December 2010] [04:15:03] <sustrik>	      continue;
| [Wednesday 08 December 2010] [04:15:06] <sustrik>	   break;
| [Wednesday 08 December 2010] [04:15:06] <sustrik>	}
| [Wednesday 08 December 2010] [04:15:10] <sustrik>	that's it
| [Wednesday 08 December 2010] [04:15:40] <Guthur>	man you just sucked the fun out of it, hehe
| [Wednesday 08 December 2010] [04:15:51] <sustrik>	oooooopw
| [Wednesday 08 December 2010] [04:15:54] <sustrik>	oops
| [Wednesday 08 December 2010] [04:20:02] <Guthur>	ah that's better
| [Wednesday 08 December 2010] [04:20:17] <Guthur>	three lines of C# code
| [Wednesday 08 December 2010] [04:20:31] <sustrik>	!
| [Wednesday 08 December 2010] [04:21:07] <Guthur>	Stopwatch timer = new Stopwatch();             timer.Start();             while (timer.ElapsedMilliseconds < timeout && ctx.Poll(items, timeout) == 0);
| [Wednesday 08 December 2010] [04:21:16] <Guthur>	oh it did do new lines
| [Wednesday 08 December 2010] [04:21:19] <Guthur>	sorry about hat
| [Wednesday 08 December 2010] [04:21:22] <Guthur>	that
| [Wednesday 08 December 2010] [04:21:28] <Guthur>	didn't
| [Wednesday 08 December 2010] [04:21:30] <sustrik>	np
| [Wednesday 08 December 2010] [04:21:33] <sustrik>	i see it
| [Wednesday 08 December 2010] [04:21:51] <sustrik>	yes, that's was the idea with 2.0.x
| [Wednesday 08 December 2010] [04:21:58] <sustrik>	the performace issue i've mentioned before is the need to measure time at the beginning of the function
| [Wednesday 08 December 2010] [04:22:19] <sustrik>	if you don't care about honouring timeouts precisely you can avoid that overhead
| [Wednesday 08 December 2010] [04:23:12] <Guthur>	no problem, I had read the non-honouring part, I should have heeded it more
| [Wednesday 08 December 2010] [04:24:32] <Guthur>	I kind of assumed it was more precision thing and that it would just be out by a few micros 
| [Wednesday 08 December 2010] [04:24:36] <Guthur>	damn assumptions
| [Wednesday 08 December 2010] [04:26:57] <Guthur>	cheers for clearing that up sustrik 
| [Wednesday 08 December 2010] [04:27:15] <sustrik>	you are welcome
| [Wednesday 08 December 2010] [04:32:13] <Guthur>	minor bug in mine there, I assumed milliseconds
| [Wednesday 08 December 2010] [04:32:36] <Guthur>	small change just, microsecond is really high res
| [Wednesday 08 December 2010] [12:41:38] <mikko>	howdy
| [Wednesday 08 December 2010] [12:58:32] <jhawk28_>	sustrik: has the zmq team thought about providing a durable pub/sub socket?
| [Wednesday 08 December 2010] [12:59:04] <seb`>	jhawk28_: durable? with disk sync?
| [Wednesday 08 December 2010] [13:00:22] <jhawk28_>	durable - req/rep for requesting off queue. Fully persistent on disc for when publisher goes down
| [Wednesday 08 December 2010] [13:01:37] <jhawk28_>	http://sna-projects.com/kafka/design.php has some interesting approaches to get it to be fast
| [Wednesday 08 December 2010] [13:02:14] <sustrik>	what if the disk on the middle node fails :)
| [Wednesday 08 December 2010] [13:02:33] <jhawk28_>	no, not broker style
| [Wednesday 08 December 2010] [13:02:59] <seb`>	jhawk28_: if you need a broker you could use rabbitmq with the 0mq plugin
| [Wednesday 08 December 2010] [13:03:04] <seb`>	that could be fun
| [Wednesday 08 December 2010] [13:03:10] <sustrik>	saving data to disk on endpoints?
| [Wednesday 08 December 2010] [13:03:15] <sustrik>	you can do that in you app
| [Wednesday 08 December 2010] [13:03:27] <sustrik>	your*
| [Wednesday 08 December 2010] [13:04:12] <sustrik>	this is what most applications with reliability requirements do anyway
| [Wednesday 08 December 2010] [13:04:23] <sustrik>	they have data on disk (in DB or something)
| [Wednesday 08 December 2010] [13:05:06] <mikko>	i thought about this issue at some point as well
| [Wednesday 08 December 2010] [13:05:20] <mikko>	came up in to conclusion that it is a lot easier to do in app level
| [Wednesday 08 December 2010] [13:05:40] <mikko>	as you can choose different kind of backends (such as bdb etc) without having to have that requirement in the core
| [Wednesday 08 December 2010] [13:05:56] <sustrik>	right
| [Wednesday 08 December 2010] [13:05:58] <sustrik>	and it's kind of inpossible to push reliability to the network
| [Wednesday 08 December 2010] [13:06:13] <sustrik>	the networks are notoriously unreliable
| [Wednesday 08 December 2010] [13:06:49] <mikko>	maybe we could provide an example of durable device
| [Wednesday 08 December 2010] [13:06:56] <mikko>	rather than incorporate into core
| [Wednesday 08 December 2010] [13:07:09] <jhawk28_>	I was thinking that I would start with the device route
| [Wednesday 08 December 2010] [13:07:46] <mikko>	maybe you could do a generic "callback" device
| [Wednesday 08 December 2010] [13:07:47] <jhawk28_>	but, I was thinking that it might be cleaner if it ended up as a socket
| [Wednesday 08 December 2010] [13:08:03] <mikko>	have function pointers when message is received and sent
| [Wednesday 08 December 2010] [13:08:15] <mikko>	jhawk28_: cleaner from what point of view?
| [Wednesday 08 December 2010] [13:08:30] <jhawk28_>	cleaner API
| [Wednesday 08 December 2010] [13:08:42] <jhawk28_>	the end user API
| [Wednesday 08 December 2010] [13:08:51] <mikko>	from application code point of view yes, but it does mean a) design a durable storage b) add a large dependency to core
| [Wednesday 08 December 2010] [13:09:16] <jhawk28_>	a)
| [Wednesday 08 December 2010] [13:09:30] <mikko>	designing persistent storage for this kind of task is not a trivial exercise
| [Wednesday 08 December 2010] [13:09:30] <sustrik>	well, i've seen how AMQP working group struggled for years to meld the networking and persistence together into a single spec
| [Wednesday 08 December 2010] [13:09:31] <jhawk28_>	base it off kafka or bitcask
| [Wednesday 08 December 2010] [13:09:38] <sustrik>	and it doesn't really lead to anything sane
| [Wednesday 08 December 2010] [13:09:42] <mikko>	if you for example look at how long it has taken for Varnish to nail it down
| [Wednesday 08 December 2010] [13:10:23] <jhawk28_>	kafka is probably closer since it just needs a queue mechanism, but they are both kinda similar
| [Wednesday 08 December 2010] [13:11:45] <jhawk28_>	biggest problem Ive seen with message queue persistence is that they can't scale to a huge number of messages
| [Wednesday 08 December 2010] [13:11:59] <mikko>	you possibly want a cleanup mechanism, expiration, maybe you want the store to be accessible from other programs as well
| [Wednesday 08 December 2010] [13:12:43] <jhawk28_>	kafka basically uses a directory as the message queue
| [Wednesday 08 December 2010] [13:12:54] <jhawk28_>	files are created in an ordered fashion
| [Wednesday 08 December 2010] [13:13:13] <jhawk28_>	the client is what determines what message id to start from
| [Wednesday 08 December 2010] [13:13:44] <mikko>	is there a concept of expiration?
| [Wednesday 08 December 2010] [13:13:48] <jhawk28_>	the cleanup is by default handled by time or size
| [Wednesday 08 December 2010] [13:14:23] <jhawk28_>	other mechanisms can be plugged in I believe
| [Wednesday 08 December 2010] [13:15:16] <jhawk28_>	the client effectively controls their state so they can restart if need
| [Wednesday 08 December 2010] [13:16:05] <mikko>	bbl, need to commute home ->
| [Wednesday 08 December 2010] [14:28:14] <mikko>	back
| [Wednesday 08 December 2010] [14:47:57] <wayneeseguin>	nice
| [Wednesday 08 December 2010] [14:48:22] <cremes>	welcome
| [Wednesday 08 December 2010] [14:49:49] <wayneeseguin>	I am new to this and I am trying to determine which socket type to use
| [Wednesday 08 December 2010] [14:50:33] <wayneeseguin>	I am playing around with an example just to see if I can get it working.
| [Wednesday 08 December 2010] [14:50:36] <cremes>	wayneeseguin: definitely read the guide at the zeromq site
| [Wednesday 08 December 2010] [14:50:58] <cremes>	it covers a LOT of novice questions
| [Wednesday 08 December 2010] [14:50:58] <wayneeseguin>	I had however perhaps I should do it again as that was a month or so ago
| [Wednesday 08 December 2010] [14:53:51] <cremes>	alternately, ask your question
| [Wednesday 08 December 2010] [14:54:05] <cremes>	if it's answered in the guide, i'll point you to it
| [Wednesday 08 December 2010] [14:54:06] <cremes>	othe
| [Wednesday 08 December 2010] [14:54:25] <cremes>	otherwise, i'll try to answer it
| [Wednesday 08 December 2010] [14:57:01] <wayneeseguin>	I am fine reading docs :) 
| [Wednesday 08 December 2010] [14:57:35] <wayneeseguin>	I want to have a client - server relationship where the client sends updates to the server on an interval and the server can request information from the client at random
| [Wednesday 08 December 2010] [14:57:51] <wayneeseguin>	I am unsure if there is one socket type that can facilitate that or if I should be using two distinct ones.
| [Wednesday 08 December 2010] [14:58:56] <sustrik>	is seems there are two different flows there
| [Wednesday 08 December 2010] [14:59:07] <sustrik>	PUB/SUB for updates
| [Wednesday 08 December 2010] [14:59:12] <sustrik>	REQ/REP for requests
| [Wednesday 08 December 2010] [14:59:41] <wayneeseguin>	ok
| [Wednesday 08 December 2010] [15:01:27] <cremes>	exactly
| [Wednesday 08 December 2010] [16:48:07] <toni__>	hey there. I have an issue with a XREQclient XREPserver architecture, where the client should resend a message to another server, in case the one he first sent the message dies. I described it in detail here: https://gist.github.com/733965 
| [Wednesday 08 December 2010] [17:19:27] <cremes>	toni__: you are understanding the problem correctly and 0mq is doing exactly what it should
| [Wednesday 08 December 2010] [17:19:57] <cremes>	when your server dies, the 0mq socket on the client should remove it from its list of usable endpoints
| [Wednesday 08 December 2010] [17:20:14] <toni__>	cremes: exactly
| [Wednesday 08 December 2010] [17:20:29] <cremes>	you are likely simulating a server death by putting it to sleep or something; make sure that when the server dies that it goes away completely
| [Wednesday 08 December 2010] [17:20:42] <cremes>	that way the socket will disconnect and you will get the behavior that you want
| [Wednesday 08 December 2010] [17:20:54] <cremes>	if it hangs forever, as far as 0mq is concerned it is still a valid endpoint
| [Wednesday 08 December 2010] [17:22:42] <toni__>	cremes: Yes, I am simulating a server death...
| [Wednesday 08 December 2010] [17:22:50] <toni__>	I sould make use of socket.close()
| [Wednesday 08 December 2010] [17:23:02] <cremes>	right; then you'll get what you want
| [Wednesday 08 December 2010] [17:23:02] <cremes>	\
| [Wednesday 08 December 2010] [17:23:31] <toni__>	cremes: Thanks for your hint!
| [Wednesday 08 December 2010] [17:23:57] <cremes>	np
| [Wednesday 08 December 2010] [17:51:51] <toni__>	cremes: Okay, I tried it with socket.close() but this does not seem to have any effect. I posted my 2 little code-snippets on gist: https://gist.github.com/734071 
| [Wednesday 08 December 2010] [17:54:00] <toni__>	It seems as if the client would still be connected to the server that died
| [Wednesday 08 December 2010] [17:55:13] <cremes>	toni__: how many of these servers are you starting up?
| [Wednesday 08 December 2010] [17:55:37] <toni__>	I start 3 servers, and then killing two of em
| [Wednesday 08 December 2010] [17:56:06] <cremes>	and after they print "socket closed" and die, your client is still trying to send new messages to them?
| [Wednesday 08 December 2010] [17:56:27] <toni__>	yes it is
| [Wednesday 08 December 2010] [17:56:34] <cremes>	try this...
| [Wednesday 08 December 2010] [17:56:46] <cremes>	1. have your client start and connect to 3 addresses *first*
| [Wednesday 08 December 2010] [17:56:50] <cremes>	2. start one server
| [Wednesday 08 December 2010] [17:56:55] <cremes>	see what your client does
| [Wednesday 08 December 2010] [17:57:03] <cremes>	3. start up the other 2 servers
| [Wednesday 08 December 2010] [17:57:08] <cremes>	see what your client does
| [Wednesday 08 December 2010] [17:57:16] <cremes>	4. kill 2 of your servers
| [Wednesday 08 December 2010] [17:57:20] <cremes>	see what your client does
| [Wednesday 08 December 2010] [17:57:51] <toni__>	cremes: Ill try it right now
| [Wednesday 08 December 2010] [18:12:52] <toni__>	cremes: I connected the client first. Then I started the first server. The client tries to send also to the other servers which are not running yet. Thats why it s first very slow. Then I start the next server, it goes faster. Starting the third server the client doesnt get any timeout and it s fast. Stopping the servers, it gets slow again...
| [Wednesday 08 December 2010] [18:14:26] <toni__>	seems like, the socket still tries to send to the addresses that are not available yet
| [Wednesday 08 December 2010] [18:35:44] <cremes>	toni__: weird; why don't you ask on the mailing list and include a gist of your code along with the results you have seen
| [Wednesday 08 December 2010] [18:35:54] <cremes>	maybe someone else can give a hint
| [Wednesday 08 December 2010] [18:36:58] <toni__>	cremes: I will post my snippets and the testcase. Thanks for your help.
| [Wednesday 08 December 2010] [18:43:20] <oxff>	is there any central message broker for PUB-SUB in the src distribution?
| [Wednesday 08 December 2010] [18:43:25] <oxff>	basically i look for something like rabbitmq
| [Wednesday 08 December 2010] [18:43:33] <oxff>	with an asynchronous i/o compatible c client library
| [Wednesday 08 December 2010] [18:43:38] <oxff>	so i want to have a central server
| [Wednesday 08 December 2010] [18:43:41] <oxff>	(cluster)
| [Wednesday 08 December 2010] [18:43:48] <oxff>	which publishers as well as subscribers can connect to
| [Wednesday 08 December 2010] [18:47:13] <oxff>	ah reading the doc, i get that this is not the scope of zeromq
| [Wednesday 08 December 2010] [18:47:14] <oxff>	too bad :/
| [Wednesday 08 December 2010] [18:54:33] <oxff>	ah, devices seems to be what iw ant
| [Wednesday 08 December 2010] [19:00:07] <oxff>	how can i get all FDs from a zeromq socket?
| [Wednesday 08 December 2010] [19:00:17] <oxff>	say, i want to embed zeromq into my existing libev app
| [Wednesday 08 December 2010] [19:01:08] <oxff>	seems that the only way to use zeromq asynchronously is to develop around zmq_poll
| [Wednesday 08 December 2010] [19:04:12] <cremes>	oxff: read up on ZM_FD and ZM_EVENTS
| [Wednesday 08 December 2010] [19:04:29] <cremes>	that is part of the 2.1 release (in beta) which makes it easy to use with other libraries
| [Wednesday 08 December 2010] [19:04:35] <oxff>	ah thanks
| [Wednesday 08 December 2010] [19:04:44] <cremes>	and zmq_poll is built on top of those primitives
| [Wednesday 08 December 2010] [19:05:45] <oxff>	wait it only gives me one fd per zmq_socket?
| [Wednesday 08 December 2010] [19:05:54] <oxff>	how does it work with a bind socket?
| [Wednesday 08 December 2010] [19:06:01] <oxff>	or multiple connected sockets?
| [Wednesday 08 December 2010] [19:07:25] <oxff>	does it create a fake fd/
| [Wednesday 08 December 2010] [19:07:28] <oxff>	?
| [Wednesday 08 December 2010] [19:13:04] <oxff>	looking at tcp_listener.cpp, it only returns the bound fd in get_fd
| [Wednesday 08 December 2010] [19:13:08] <oxff>	too tired to read all of the source
| [Wednesday 08 December 2010] [19:19:03] <oxff>	wait, does zeromq internally use threading / create threads for accepting new connectins etc?
| [Wednesday 08 December 2010] [19:22:10] <oxff>	how can i issue a non-blocking connect with zmq_connect?
| [Wednesday 08 December 2010] [19:28:28] <oxff>	lol you
| [Wednesday 08 December 2010] [19:28:41] <oxff>	you're threading and the fd is just some pipe fd you accumulate to?
| [Wednesday 08 December 2010] [19:28:44] <oxff>	this is bullshit
| [Wednesday 08 December 2010] [20:50:01] <testuser>	hello
| [Wednesday 08 December 2010] [22:55:31] 470	travlr #gwt ##gwt Forwarding to another channel
| [Wednesday 08 December 2010] [22:55:31] Notice	-ChanServ- [##gwt] Welcome to the unofficial Google Web Toolkit channel on freenode. This is a starting (and growing) community, and we need your help. Stick around!
| [Wednesday 08 December 2010] [22:55:45] 470	travlr #gwt ##gwt Forwarding to another channel
| [Wednesday 08 December 2010] [22:55:45] Notice	-ChanServ- [##gwt] Welcome to the unofficial Google Web Toolkit channel on freenode. This is a starting (and growing) community, and we need your help. Stick around!
| [Wednesday 08 December 2010] [22:55:55] 470	travlr #gwt ##gwt Forwarding to another channel
| [Wednesday 08 December 2010] [22:55:55] Notice	-ChanServ- [##gwt] Welcome to the unofficial Google Web Toolkit channel on freenode. This is a starting (and growing) community, and we need your help. Stick around!
| [Thursday 09 December 2010] [03:46:34] <rrg>	hi
| [Thursday 09 December 2010] [03:49:57] <rrg>	i am unsure how to implement multiplexed sending using a PUB socket. to be specific: a changing number of producers write multipart messages of varying length, at verying times and from varying threads. do i need to synchronize the writing somehow and abandon the multipart messaging alltogether?
| [Thursday 09 December 2010] [03:54:36] <Steve-o>	give each thread a 0mq socket then ensure each thread sends multi-part atomically
| [Thursday 09 December 2010] [03:57:39] <Steve-o>	you could always add extra sockets, i.e. one per session per thread too
| [Thursday 09 December 2010] [03:58:27] <mikko>	Steve-o: im getting openpgm compile failure on x86 solaris 10
| [Thursday 09 December 2010] [03:58:43] <Steve-o>	only tried opensolaris on intel
| [Thursday 09 December 2010] [03:59:07] <Steve-o>	have you updated the compiler flags?
| [Thursday 09 December 2010] [03:59:30] <Steve-o>	>> http://code.google.com/p/openpgm/source/browse/trunk/openpgm/pgm/SConstruct.OpenSolaris
| [Thursday 09 December 2010] [04:00:32] <mikko>	Steve-o: i have
| [Thursday 09 December 2010] [04:00:33] <mikko>	sec
| [Thursday 09 December 2010] [04:01:07] <mikko>	https://gist.github.com/123f088e350c12744e1c
| [Thursday 09 December 2010] [04:01:22] <mikko>	i was working on getting --with-pgm build to work on solaris10 using sun studio last night
| [Thursday 09 December 2010] [04:01:39] <Steve-o>	ok, x86/Solaris is pretty much a dead platform
| [Thursday 09 December 2010] [04:01:51] <mikko>	had to remove strict flag because __PRETTY_FUNCTION__ is not declared on strict compliance mode
| [Thursday 09 December 2010] [04:02:24] <Steve-o>	that's gcc only ?
| [Thursday 09 December 2010] [04:02:44] <mikko>	-Xc mode in solaris studio drops standards incompliant things
| [Thursday 09 December 2010] [04:02:55] <mikko>	__PRETTY_FUNCTION__ is "pseudo-standard"
| [Thursday 09 December 2010] [04:02:56] <Steve-o>	it should be picking up __func__ instead
| [Thursday 09 December 2010] [04:03:51] <Steve-o>	just checked, __PRETTY_FUNCTION__ should only be used with __GNUC__ defined
| [Thursday 09 December 2010] [04:04:12] <Steve-o>	I don't even bother with __func__, I think that's only SunPro 
| [Thursday 09 December 2010] [04:04:21] <Steve-o>	but your error is assembler
| [Thursday 09 December 2010] [04:04:25] <mikko>	__func__ is supported by all of them
| [Thursday 09 December 2010] [04:04:56] <mikko>	i guess it would be fairly easy to ifdef OPENPGM_FUNCTION or similar
| [Thursday 09 December 2010] [04:05:41] <mikko>	http://blogs.sun.com/solarisdev/entry/new_article_prefetching
| [Thursday 09 December 2010] [04:05:49] <Steve-o>	ok i see the problem
| [Thursday 09 December 2010] [04:06:00] <Steve-o>	I assume sun = sparc
| [Thursday 09 December 2010] [04:06:14] <Steve-o>	which is usually pretty good considering the other options are awful
| [Thursday 09 December 2010] [04:06:48] <Steve-o>	sunpro on linux doesn't define sun
| [Thursday 09 December 2010] [04:07:06] <Steve-o>	so what does "sun" mean?
| [Thursday 09 December 2010] [04:07:15] <Steve-o>	it's not there for opensolaris
| [Thursday 09 December 2010] [04:08:38] <mikko>	sun and __sun are defined for x86 solaris
| [Thursday 09 December 2010] [04:08:51] <mikko>	sparc and __sparc for SPARC 
| [Thursday 09 December 2010] [04:08:54] <mikko>	as far as i know
| [Thursday 09 December 2010] [04:09:01] <mikko>	i dont have access to sparc
| [Thursday 09 December 2010] [04:09:28] <Steve-o>	sparc is for ultrasparc and older
| [Thursday 09 December 2010] [04:09:45] <mikko>	http://predef.sourceforge.net/preos.html#sec35
| [Thursday 09 December 2010] [04:09:52] <mikko>	this says that it's for solaris operating system
| [Thursday 09 December 2010] [04:10:05] <Steve-o>	it's __sparcv9 for the box I have
| [Thursday 09 December 2010] [04:10:20] <Steve-o>	which probably makes __sparc a v8
| [Thursday 09 December 2010] [04:12:17] <Steve-o>	ok, have to guess which ones match gcc
| [Thursday 09 December 2010] [04:12:52] <Steve-o>	I don't even use them which makes it worse
| [Thursday 09 December 2010] [04:13:04] <Steve-o>	they're slower on the hardware I have
| [Thursday 09 December 2010] [04:13:12] <mikko>	interesting
| [Thursday 09 December 2010] [04:13:26] <mikko>	CC man page says that 'sun' is sparc only macro
| [Thursday 09 December 2010] [04:14:12] <mikko>	but that might be from time before solaris studio on x86
| [Thursday 09 December 2010] [04:14:15] <mikko>	not sure
| [Thursday 09 December 2010] [04:14:32] <Steve-o>	x86 solaris is really old, but yes there is a lot of confusion
| [Thursday 09 December 2010] [04:14:47] <Steve-o>	looks like prefetch -> sun_prefetch_read_many
| [Thursday 09 December 2010] [04:14:54] <Steve-o>	prefetchw -> sun_prefetch_write_many
| [Thursday 09 December 2010] [04:15:15] <Steve-o>	I'll have to switch on my sparc and check
| [Thursday 09 December 2010] [04:15:26] <rrg>	Steve-o: the cost of adding a socket is insignificant?
| [Thursday 09 December 2010] [04:15:35] <Steve-o>	I think I have a few fixes to back port to 5.0 too anyway
| [Thursday 09 December 2010] [04:16:13] <mikko>	Steve-o: i use +w -Xc to compile with sun studio
| [Thursday 09 December 2010] [04:16:16] <mikko>	if you want to test
| [Thursday 09 December 2010] [04:16:25] <Steve-o>	rrg:  0mq automagically manages the multiplexing, so once one underlying transport is setup it is cheap
| [Thursday 09 December 2010] [04:18:04] <rrg>	Steve-o: by setup you mean the context initialization?
| [Thursday 09 December 2010] [04:18:58] <Steve-o>	rrg: the IO thread(s) open up the TCP/IPC/PGM sockets in the background
| [Thursday 09 December 2010] [04:19:45] <rrg>	ah, ok. so context init = transport init
| [Thursday 09 December 2010] [04:20:57] <rrg>	Steve-o: but won't binding the socket work exactly once? in case of tcp/ip unicast?
| [Thursday 09 December 2010] [04:21:56] <Steve-o>	i'm going on what the whitepapers on the architecture say :-)
| [Thursday 09 December 2010] [04:24:35] <rrg>	Steve-o: ? -> /me ?
| [Thursday 09 December 2010] [04:27:28] <Steve-o>	brb, a couple of things working on
| [Thursday 09 December 2010] [04:29:24] <guido_g>	rrg: the context has nothing to do w/ a particular transport
| [Thursday 09 December 2010] [04:33:12] 	 * rrg wonders if this problem could be solved by opening multiple icp push connections and performing the actual tcp sending in a dedicated receiver thread of those multipart messages
| [Thursday 09 December 2010] [04:34:12] <guido_g>	icp?
| [Thursday 09 December 2010] [04:35:42] <rrg>	ipc
| [Thursday 09 December 2010] [04:35:51] <rrg>	guido_g: seems to work!
| [Thursday 09 December 2010] [04:37:23] <rrg>	guido_g: ok, i have single thread now which binds a pub socket to tcp and sits in a recv loop on an ipc pull socket.
| [Thursday 09 December 2010] [04:38:00] <rrg>	guide_g:  plus a certain amount of threads which send multipart messages to thread-specific ipc push sockets which they close when they terminate.
| [Thursday 09 December 2010] [04:38:31] <rrg>	guido_g: seems to work fine with 2 context i/o threads. any antipattern i'm using here?
| [Thursday 09 December 2010] [04:39:10] <guido_g>	2 contexts? seems fishy
| [Thursday 09 December 2010] [04:39:17] <Steve-o>	mikko:  aaagh, that strict mode is annoying
| [Thursday 09 December 2010] [04:41:11] <Steve-o>	I'm not even getting "sun" defined
| [Thursday 09 December 2010] [04:41:22] <toni_>	hey there. I have a XREQ client connected to a set of XREP servers. When one server dies, the client still tries to send messages to it. Is this the default zmq behavior, or am I doing something wrong? 
| [Thursday 09 December 2010] [04:42:16] <Steve-o>	mikko:  so strict mode presumably means only __sun is defined?  always the underscore requirement?
| [Thursday 09 December 2010] [04:43:13] <rrg>	guido_g: 2 i/o threads, 1 ctx
| [Thursday 09 December 2010] [04:44:21] <guido_g>	rrg: i dont think you need 2 io threads, it's a waste of ressources
| [Thursday 09 December 2010] [04:46:41] <rrg>	guido_g: is there any usecase for n>1 threads?
| [Thursday 09 December 2010] [04:47:05] <guido_g>	rrg: no, not that i know of
| [Thursday 09 December 2010] [04:48:59] <rrg>	guido_g: ok
| [Thursday 09 December 2010] [04:49:02] <rrg>	guido_g: ty
| [Thursday 09 December 2010] [04:52:00] <toni_>	I described my issue in detail here: https://gist.github.com/734545
| [Thursday 09 December 2010] [04:59:17] <Steve-o>	toni_:  send onto the list too
| [Thursday 09 December 2010] [04:59:38] <guido_g>	toni_: but first write a working test, please
| [Thursday 09 December 2010] [04:59:53] <toni_>	Steve-o: I did this. The working test is also linked
| [Thursday 09 December 2010] [04:59:54] <guido_g>	toni_: ahh... and remove the useles recursion
| [Thursday 09 December 2010] [05:00:29] <guido_g>	toni_: there're three code snippes that are obviously part of something else
| [Thursday 09 December 2010] [05:00:58] <toni_>	guido_g:  the snippets I linked ?
| [Thursday 09 December 2010] [05:01:15] <guido_g>	toni_: what else?
| [Thursday 09 December 2010] [05:01:20] <toni_>	guido_g: no thats exactly my code and my problem
| [Thursday 09 December 2010] [05:02:38] <guido_g>	toni_: why didn't you post the code as it is then? what you posted appears to be 3 unrelated snippets
| [Thursday 09 December 2010] [05:02:44] <toni_>	guido_g: My aproach is, that when a server does not answer for two seconds, I resend the message
| [Thursday 09 December 2010] [05:03:51] <toni_>	guido_g:  But the XREPServer and the XREQConnect are both used in the Testcase
| [Thursday 09 December 2010] [05:04:25] <Steve-o>	mikko:  I have trunk working with sun one in strict mode now, will have to try ICC later
| [Thursday 09 December 2010] [05:06:56] <toni_>	guido_g: in the Testcase I first start one server, than the second, then the third. Whenever one server is not available, my XREQ send method runs into the timeout as it does not get any reply for 2 seconds
| [Thursday 09 December 2010] [05:07:19] <toni_>	guido_g: and in this case I resend the message
| [Thursday 09 December 2010] [05:07:28] <guido_g>	toni_: i know, i can read
| [Thursday 09 December 2010] [05:09:10] <toni_>	guido_g: What I would need, is to tell the XREQ at XREQConnect to disconnect from the addresses that are obviously broken
| [Thursday 09 December 2010] [05:10:14] <guido_g>	toni_: mq should do that, if not, show a comprehensible working test case and file an issue
| [Thursday 09 December 2010] [05:13:05] <toni_>	guido_g: Okay, Ill open up an issue. Seems to me as if it s not working properly
| [Thursday 09 December 2010] [05:14:58] <guido_g>	toni_: make your test actually working and as small as possible, otherwise it'll be difficult to proof your point
| [Thursday 09 December 2010] [05:15:48] <toni_>	guido_g: yes I will. Thanks for your hints anyway.
| [Thursday 09 December 2010] [05:49:26] <toni_>	One question remains. In zmq I can connect a socket to some addresses (that never were bound before), send messages to it and they will be buffered until the addresses become available. So consider one client and two servers. The client connects to both. The messages are loadbalanced between the servers. When one server dies (s.close()) the client will try to send its message to that address. As it is not available they are buffered. A
| [Thursday 09 December 2010] [06:45:25] <sustrik_>	drbobbeaty: hi
| [Thursday 09 December 2010] [06:45:33] <sustrik_>	would you do the -1 default, or should i?
| [Thursday 09 December 2010] [06:47:28] <drbobbeaty>	sustrik: I'll be glad to. I just need to get a few things done this morning and then hamer it out.
| [Thursday 09 December 2010] [06:47:36] <sustrik_>	great
| [Thursday 09 December 2010] [06:47:51] <drbobbeaty>	I want to build RPMs, etc. to verify etc. So it'll take me just a little bit.
| [Thursday 09 December 2010] [06:47:59] <sustrik_>	sure, no haste
| [Thursday 09 December 2010] [06:52:10] <toni_>	I posted my problem here with a minimal testcase: https://github.com/zeromq/pyzmq/issues/issue/51
| [Thursday 09 December 2010] [06:57:39] <guido_g>	toni_: does it work if you start both servers and then kill one of them?
| [Thursday 09 December 2010] [06:59:12] <guido_g>	toni_: of course, after the client connected to them
| [Thursday 09 December 2010] [07:02:53] <toni_>	guido_g: no, when I start both servers, then starting the client e.g sending 100 000 msgs and then I kill one server, the client still tries to send to the death one
| [Thursday 09 December 2010] [07:03:50] <guido_g>	ouch
| [Thursday 09 December 2010] [07:04:02] <guido_g>	sounds really like a bug
| [Thursday 09 December 2010] [07:04:36] <toni_>	The testcase is quite simple, I hope everyone can reproduce this behavior
| [Thursday 09 December 2010] [07:10:48] <guido_g>	jepp, killing one of the servers causes a delay every other request
| [Thursday 09 December 2010] [07:13:05] <toni_>	guido_g: but actually, zmq should behave different and notice the death server?
| [Thursday 09 December 2010] [07:13:45] <guido_g>	should be in the docs
| [Thursday 09 December 2010] [07:15:55] <guido_g>	ahhh.. got it
| [Thursday 09 December 2010] [07:16:08] <guido_g>	set the HWM for the sending socket to 1, then it works
| [Thursday 09 December 2010] [07:19:01] <toni_>	guido_g: You are my hero !!!
| [Thursday 09 December 2010] [07:19:13] <toni_>	guido_g: hanging on this issue for almost 2 day now
| [Thursday 09 December 2010] [07:19:32] <toni_>	guido_g: Thanks a lot for your help!!!
| [Thursday 09 December 2010] [07:19:43] <guido_g>	the reason is -- i think -- the unbound queue for this endpoint
| [Thursday 09 December 2010] [07:20:10] <toni_>	guido_g: what do you mean by the unbound queue?
| [Thursday 09 December 2010] [07:20:50] <toni_>	guido_g: As far as I understood the HWM limits the send-buffer of the socket to the size of 1
| [Thursday 09 December 2010] [07:20:53] <guido_g>	every endpoint under a mq socket has a queue for messages to be sent to it
| [Thursday 09 December 2010] [07:21:19] <toni_>	ah okay, thats what I just called buffer...
| [Thursday 09 December 2010] [07:21:22] <guido_g>	not of the mq socket, but the underlying endpoint
| [Thursday 09 December 2010] [07:23:12] <toni_>	guido_g:  thanks for your help. Great project and great community
| [Thursday 09 December 2010] [08:38:25] <bobdole369>	Hello good morning, is zeromq used often with embedded devices? Specifically Rabbit Semiconductor stuff, or Schnieder (or others) PLC's?
| [Thursday 09 December 2010] [10:17:29] <mikko>	bobdole369: it might make sense to ask that question on the mailing-lists to reach bigger audience
| [Thursday 09 December 2010] [10:21:55] <Steve-o>	mikko: what strict parameters are you using for ICC?  I'll check tomorrow and update trunk for PGM
| [Thursday 09 December 2010] [10:31:25] <mikko>	Steve-o: sec
| [Thursday 09 December 2010] [10:31:46] <mikko>	-strict-ansi
| [Thursday 09 December 2010] [10:43:10] <Steve-o>	taa, will test with 5.1 and backport to 5.0
| [Thursday 09 December 2010] [10:43:18] <mikko>	cool
| [Thursday 09 December 2010] [10:44:04] <Steve-o>	only OSX needs 5.1 because of the lack of spin locks
| [Thursday 09 December 2010] [10:44:31] <Steve-o>	maybe something with Win x64 too but I can't recall
| [Thursday 09 December 2010] [11:25:48] <mikko>	sustrik: there?
| [Thursday 09 December 2010] [12:04:17] <sustrik>	mikko: hi
| [Thursday 09 December 2010] [12:05:19] <mikko>	sustrik: im having issues with ZMQ_QUEUE
| [Thursday 09 December 2010] [12:05:34] <sustrik>	yes?
| [Thursday 09 December 2010] [12:05:39] <mikko>	it seems that my messages are not being closed
| [Thursday 09 December 2010] [12:05:48] <mikko>	it's a bit tricky to reproduce
| [Thursday 09 December 2010] [12:05:59] <mikko>	but i got front=pull, back=push device
| [Thursday 09 December 2010] [12:06:14] <mikko>	and if i am not consuming the message the memory usage goes up steadily
| [Thursday 09 December 2010] [12:06:28] <mikko>	if i then start consumer the memory usage doesn't go down
| [Thursday 09 December 2010] [12:06:32] <mikko>	even though messages are flowing
| [Thursday 09 December 2010] [12:06:45] <mikko>	i can see using valgrind that memory is held in the messages
| [Thursday 09 December 2010] [12:06:53] <sustrik>	are you publishing at full spead?
| [Thursday 09 December 2010] [12:06:58] <sustrik>	speed
| [Thursday 09 December 2010] [12:07:25] <mikko>	yes
| [Thursday 09 December 2010] [12:07:54] <mikko>	is it expected that memory usage never goes down?
| [Thursday 09 December 2010] [12:08:31] <sustrik>	well, if receiver is slower than publisher it can happen
| [Thursday 09 December 2010] [12:08:54] <mikko>	but even if i stop publisher and start consuming
| [Thursday 09 December 2010] [12:09:03] <mikko>	it seems that usage does not go down
| [Thursday 09 December 2010] [12:12:27] <sustrik>	that looks like a leak
| [Thursday 09 December 2010] [12:12:51] <sustrik>	can you report the problem along with the test program?
| [Thursday 09 December 2010] [12:13:04] <mikko>	does this make sense:
| [Thursday 09 December 2010] [12:13:20] <mikko>	i generate 10k messages, then turn consumer on/off/on/off
| [Thursday 09 December 2010] [12:13:25] <mikko>	until no more messages flow through
| [Thursday 09 December 2010] [12:13:34] <mikko>	kinda simulating flaky network
| [Thursday 09 December 2010] [12:13:48] <mikko>	and at the end it seems that not all messages get freed
| [Thursday 09 December 2010] [12:13:54] <mikko>	but there is no more coming from pipe
| [Thursday 09 December 2010] [12:14:38] <sustrik>	how do you know they weren't freed?
| [Thursday 09 December 2010] [12:15:55] <mikko>	valgrind show them in "still reachable" memory
| [Thursday 09 December 2010] [12:18:10] <mikko>	it might be something in my app as well
| [Thursday 09 December 2010] [12:18:28] <mikko>	i will investigate further and open a ticket if it's somewhat reproducible
| [Thursday 09 December 2010] [12:36:51] <sustrik>	mikko: how did you shut down the device?
| [Thursday 09 December 2010] [12:37:06] <mikko>	sustrik: ctrl + c
| [Thursday 09 December 2010] [12:37:17] <sustrik>	let me check the code...
| [Thursday 09 December 2010] [12:37:27] <sustrik>	master?
| [Thursday 09 December 2010] [12:37:35] <mikko>	yes
| [Thursday 09 December 2010] [12:37:41] <mikko>	it could very well be my test code
| [Thursday 09 December 2010] [12:38:11] <mikko>	i need a statistics collection over http
| [Thursday 09 December 2010] [12:38:25] <mikko>	so im writing a small webserver that distributes the messages to backend nodes for processing
| [Thursday 09 December 2010] [12:43:20] <sustrik>	mikko: aha
| [Thursday 09 December 2010] [12:43:30] <sustrik>	the devices are not shutting down decently
| [Thursday 09 December 2010] [12:43:32] <sustrik>	if (errno == ETERM)
| [Thursday 09 December 2010] [12:43:32] <sustrik>	                        return -1;
| [Thursday 09 December 2010] [12:43:51] <sustrik>	what they should do, i guess
| [Thursday 09 December 2010] [12:44:05] <sustrik>	is to set LINGER to 0
| [Thursday 09 December 2010] [12:44:12] <sustrik>	and terminate via zmq_term()
| [Thursday 09 December 2010] [13:51:25] <delaney>	are there any examples of the proper use of socket.RecvAll() for C#?
| [Thursday 09 December 2010] [13:54:20] <sustrik>	delaney: i don't think there are much examples for clrzmq2, try asking on the mailing list
| [Thursday 09 December 2010] [13:54:49] <delaney>	k
| [Thursday 09 December 2010] [15:26:06] <sustrik_>	mikko: hm, i was wrong
| [Thursday 09 December 2010] [15:27:14] <sustrik_>	Ctrl+C actually kills the program, thus not freeing the allocated memory 
| [Thursday 09 December 2010] [15:27:29] <sustrik_>	so valgrind would naturally report leaks
| [Thursday 09 December 2010] [15:27:58] <sustrik_>	alternative would be to install SIGINT handler and try to clean-up before exiting
| [Thursday 09 December 2010] [15:45:10] <CIA-20>	zeromq2: 03Bob Beaty 07master * rfcfad56 10/ (6 files in 3 dirs): (log message trimmed)
| [Thursday 09 December 2010] [15:45:10] <CIA-20>	zeromq2: Added Recovery Interval in Milliseconds
| [Thursday 09 December 2010] [15:45:10] <CIA-20>	zeromq2: For very high-speed message systems, the memory used for recovery can get to
| [Thursday 09 December 2010] [15:45:10] <CIA-20>	zeromq2: be very large. The corrent limitation on that reduction is the ZMQ_RECOVERY_IVL
| [Thursday 09 December 2010] [15:45:10] <CIA-20>	zeromq2: of 1 sec. I added in an additional option ZMQ_RECOVERY_IVL_MSEC, which is the
| [Thursday 09 December 2010] [15:45:11] <CIA-20>	zeromq2: Recovery Interval in milliseconds. If used, this will override the previous
| [Thursday 09 December 2010] [15:45:11] <CIA-20>	zeromq2: one, and allow you to set a sub-second recovery interval. If not set, the
| [Thursday 09 December 2010] [15:45:12] <CIA-20>	zeromq2: 03Martin Sustrik 07master * ra9d969a 10/ AUTHORS : 
| [Thursday 09 December 2010] [15:45:13] <CIA-20>	zeromq2: Bob Beaty added to the AUTHORS file
| [Thursday 09 December 2010] [15:45:13] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/hqM7T8
| [Thursday 09 December 2010] [16:41:14] <mikko>	sustrik_: the thing i was seeing is that the memory just 'sits' there
| [Thursday 09 December 2010] [16:41:24] <mikko>	and doesn't go down during when the program runs
| [Thursday 09 December 2010] [16:46:02] <sustrik_>	that's the OS problem AFAIK
| [Thursday 09 December 2010] [16:46:24] <sustrik_>	OS doesn't return deallocated memory back to the shared pool
| [Thursday 09 December 2010] [16:46:36] <sustrik_>	rather the memory is kept by the running process
| [Thursday 09 December 2010] [16:47:19] <sustrik_>	Solaris claims that it's able to reuse the memory, but my tests haven't confirmed it
| [Thursday 09 December 2010] [16:49:29] <mikko>	i shouldn't see that memory in still reachable in valgrind though
| [Thursday 09 December 2010] [16:49:51] <sustrik_>	right, that's interesting
| [Thursday 09 December 2010] [16:49:58] <mikko>	but it might've been an application as i don't seem to be able to reproduce after a couple of hours of refactoring
| [Thursday 09 December 2010] [16:50:29] <sustrik_>	yes, this kind of problems is pretty hard to track down
| [Thursday 09 December 2010] [16:52:02] <sustrik_>	if you are able to reproduce in the future we can give it a try though
| [Thursday 09 December 2010] [16:54:29] <mikko>	cool
| [Thursday 09 December 2010] [16:54:36] <mikko>	the tool feels pretty stable now
| [Thursday 09 December 2010] [16:54:59] <mikko>	can push a bit over 3k http requests per second on my virtual machine which seems more than enough
| [Thursday 09 December 2010] [17:02:51] <sustrik_>	:)
| [Friday 10 December 2010] [00:55:58] <samBiotic>	could someone please help me get my ruby bindings working on osx.
| [Friday 10 December 2010] [00:56:17] <andrewvc>	samBiotic
| [Friday 10 December 2010] [00:56:23] <andrewvc>	what's going on on OSX?
| [Friday 10 December 2010] [00:56:25] <samBiotic>	zeromq has been installed with homebrew
| [Friday 10 December 2010] [00:56:33] <samBiotic>	brew install zeromq
| [Friday 10 December 2010] [00:56:33] <andrewvc>	also, which lib, ffi-rzmq or rbzmq
| [Friday 10 December 2010] [00:57:24] <andrewvc>	hmm, but which ruby binding
| [Friday 10 December 2010] [00:57:31] <andrewvc>	have you installed either of the zeromq gems yet?
| [Friday 10 December 2010] [00:57:36] <samBiotic>	yes
| [Friday 10 December 2010] [00:57:53] <andrewvc>	which one?
| [Friday 10 December 2010] [00:58:08] <samBiotic>	gem install zmq -- --with-zmq-dir=/usr/local
| [Friday 10 December 2010] [00:58:39] <andrewvc>	hmmm, I installed zmq for the tarball, and gem install zmq worked fine
| [Friday 10 December 2010] [00:58:42] <andrewvc>	*from
| [Friday 10 December 2010] [00:58:48] <andrewvc>	no idea about homebrew though
| [Friday 10 December 2010] [00:58:52] <samBiotic>	checking for zmq_init() in -lzmq... no
| [Friday 10 December 2010] [00:58:57] <andrewvc>	you could just try using the zmq tarball
| [Friday 10 December 2010] [00:59:16] <samBiotic>	hmm yes i could
| [Friday 10 December 2010] [00:59:17] <andrewvc>	I've never installed it through brew myself
| [Friday 10 December 2010] [00:59:24] <samBiotic>	ok will try now
| [Friday 10 December 2010] [00:59:37] <andrewvc>	cool, I know more about the search paths for ffi-rzmq
| [Friday 10 December 2010] [00:59:51] <andrewvc>	you might want to consider using ffi-rzmq btw
| [Friday 10 December 2010] [00:59:55] <samBiotic>	ok
| [Friday 10 December 2010] [01:00:18] <andrewvc>	unless you have a specific need for the slight speed boost of rbzmq (just my $0.02)
| [Friday 10 December 2010] [01:00:24] <samBiotic>	my aim is to build an open sound control multicaster eventually
| [Friday 10 December 2010] [01:00:59] <andrewvc>	cool project
| [Friday 10 December 2010] [01:01:45] <samBiotic>	i have forward scheduling of packets working but time to live reductions would be preferable
| [Friday 10 December 2010] [01:02:16] <Steve-o>	samBiotic: is that like the BBCs project?
| [Friday 10 December 2010] [01:02:29] <samBiotic>	what would that be?
| [Friday 10 December 2010] [01:03:00] <andrewvc>	samBiotic, with that kind of time constraint, wouldn't ruby's GC cause issues?
| [Friday 10 December 2010] [01:03:10] <Steve-o>	they have a music collaboration tool
| [Friday 10 December 2010] [01:03:10] <andrewvc>	at least MRI
| [Friday 10 December 2010] [01:04:03] <samBiotic>	andrewvc: possibly, using this http://opensoundcontrol.org/implementation/ruby-osc-implementation
| [Friday 10 December 2010] [01:04:10] <Steve-o>	built upon Kamaelia http://www.bbc.co.uk/opensource/projects/kamaelia/
| [Friday 10 December 2010] [01:04:45] <samBiotic>	Steve-o: looks interesting
| [Friday 10 December 2010] [01:05:00] <andrewvc>	if you have GC issues btw, jRuby might be the way to go.
| [Friday 10 December 2010] [01:05:16] <andrewvc>	plus, you'll get real multithreading if you need it
| [Friday 10 December 2010] [01:06:36] <andrewvc>	the Kamaelia site seems abandoned
| [Friday 10 December 2010] [01:07:09] <Steve-o>	try here, http://www.kamaelia.org/Home.html
| [Friday 10 December 2010] [01:07:30] <Steve-o>	broken default page
| [Friday 10 December 2010] [01:07:40] <andrewvc>	oh, there we go
| [Friday 10 December 2010] [01:09:44] <Steve-o>	kamaelia jam from a gsoc 2008 project, http://www.bbc.co.uk/blogs/bbcinternet/2008/05/google_summer_of_code.html
| [Friday 10 December 2010] [01:09:55] <samBiotic>	basically, i aim to eliminate network jitter at a slight expense of increased but static delay by forward syncronising timetagged packets
| [Friday 10 December 2010] [01:10:38] <Steve-o>	more like pulseaudio then?
| [Friday 10 December 2010] [01:11:27] <samBiotic>	control data only
| [Friday 10 December 2010] [01:15:15] <Steve-o>	ok, similar to the pro light control system, what ever that is called
| [Friday 10 December 2010] [01:15:42] <Steve-o>	DMX?
| [Friday 10 December 2010] [01:18:14] <samBiotic>	yeah kind of, it's just a network procotol developed by MIT. http://opensoundcontrol.org/introduction-osc
| [Friday 10 December 2010] [01:18:59] <samBiotic>	sorry CNMAT
| [Friday 10 December 2010] [01:19:53] <andrewvc>	samBiotic what's zeromq bring to the table that the OSC protocol doesn't?
| [Friday 10 December 2010] [01:20:03] <andrewvc>	I'm not familiar with OSC at all
| [Friday 10 December 2010] [01:20:31] <Steve-o>	I'm guesing OSC over 0MQ
| [Friday 10 December 2010] [01:20:40] <samBiotic>	thats what i was going to test
| [Friday 10 December 2010] [01:20:50] <Steve-o>	whilst DMX is commercially licensed
| [Friday 10 December 2010] [01:26:07] <andrewvc>	btw, did you ever get it up and running on OSX steve?
| [Friday 10 December 2010] [01:26:11] <andrewvc>	errr Sam
| [Friday 10 December 2010] [01:27:47] <samBiotic>	still at it
| [Friday 10 December 2010] [01:27:50] <andrewvc>	I should mention, if you use zerocopy the ffi binding can beat out the speed of the C binding. Not sure if you need to actually open the msgs as they go through
| [Friday 10 December 2010] [01:28:19] <samBiotic>	trying gem install ffi-rzmq now
| [Friday 10 December 2010] [01:28:42] <andrewvc>	btw, some versions of the ffi gem don't play well with ffi-rzmq
| [Friday 10 December 2010] [01:29:07] <samBiotic>	seems to have work with my zeromq homebrew install
| [Friday 10 December 2010] [01:29:12] <andrewvc>	nice
| [Friday 10 December 2010] [01:29:16] <andrewvc>	I think the most recent one is fine, but if you have weird hanging issues  related to threads, try building it from the ffi github repo
| [Friday 10 December 2010] [01:29:16] <samBiotic>	worked*
| [Friday 10 December 2010] [01:30:22] <andrewvc>	cool
| [Friday 10 December 2010] [02:00:08] <samBiotic>	andrewvc and Steve-o thanks for the help
| [Friday 10 December 2010] [02:00:18] <samBiotic>	bye for now
| [Friday 10 December 2010] [09:25:49] <matias_>	hi all :-)
| [Friday 10 December 2010] [09:39:42] <Steve-o>	mikko: I've backported many fixes to PGM 5.0 but ANSI strict is a bit too much work, therefore 5.1 must be used for Cygwin/Solaris x6/ANSI strict/OSX
| [Friday 10 December 2010] [09:40:11] <mikko>	Steve-o: ok
| [Friday 10 December 2010] [09:40:20] <mikko>	maybe we should remove the strict flags for solaris for now
| [Friday 10 December 2010] [09:40:28] <mikko>	until we can use 5.1 in zeromq
| [Friday 10 December 2010] [09:41:34] <Steve-o>	I need to run through all the tests then I can ship a 5.0.93 and the first 5.1 release
| [Friday 10 December 2010] [09:43:59] <Steve-o>	Sun ONE is odd as ever, it wants __asm__ only in C++ ANSI strict
| [Friday 10 December 2010] [09:44:11] <Steve-o>	every other combination is fine with __asm
| [Friday 10 December 2010] [10:29:37] <mikko>	sustrik_: how does HWM interact with ZMQ_QUEUE?
| [Friday 10 December 2010] [10:32:39] <sustrik_>	mikko: you have to set it by hand
| [Friday 10 December 2010] [10:32:53] <sustrik_>	i.e.
| [Friday 10 December 2010] [10:33:01] <sustrik_>	create socket 1, sreate socket 2
| [Friday 10 December 2010] [10:33:08] <sustrik_>	set hwm on 1. set hwm on 2
| [Friday 10 December 2010] [10:33:17] <sustrik_>	zmq_device (ZMQ_QUEUEU, s1, s2);
| [Friday 10 December 2010] [10:35:31] <mikko>	ok, so in order to get messages swapped out when there is no consumer on the back socket i would just set on s2 ?
| [Friday 10 December 2010] [10:42:00] <mikko>	Assertion failed: rc == 0 (pipe.cpp:187)
| [Friday 10 December 2010] [10:43:07] <mikko>	swap init
| [Friday 10 December 2010] [10:43:42] <mikko>	makes sense now
| [Friday 10 December 2010] [10:43:52] <mikko>	so permission issues on swap file causes an assertion
| [Friday 10 December 2010] [10:43:54] <mikko>	it looks like
| [Friday 10 December 2010] [10:44:18] <mikko>	maybe hte swap location should be a sockopt
| [Friday 10 December 2010] [10:44:32] <mikko>	as for example this daemon chdirs to / and drops privileges 
| [Friday 10 December 2010] [10:44:40] <mikko>	so it makes sense that it cant write
| [Friday 10 December 2010] [10:44:55] <sustrik_>	mikko: yes
| [Friday 10 December 2010] [10:45:10] <sustrik_>	it's a problem
| [Friday 10 December 2010] [10:47:25] <sustrik_>	zmq should not fail
| [Friday 10 December 2010] [10:47:47] <sustrik_>	however, i am not sure what the solution should be
| [Friday 10 December 2010] [10:47:54] <mikko>	in this case it would be easy to return error and set errno to eperm
| [Friday 10 December 2010] [10:48:09] <sustrik_>	it happens on setsockopt?
| [Friday 10 December 2010] [10:48:25] <mikko>	it happens later
| [Friday 10 December 2010] [10:48:47] <sustrik_>	i would say it should happen during setsockopt
| [Friday 10 December 2010] [10:49:02] <sustrik_>	the async error later on is just confusing
| [Friday 10 December 2010] [10:49:02] <mikko>	thats impossible
| [Friday 10 December 2010] [10:49:07] <sustrik_>	why so?
| [Friday 10 December 2010] [10:49:15] <mikko>	you create sequential files
| [Friday 10 December 2010] [10:49:31] <mikko>	someone might have one file present with same name which is not writable
| [Friday 10 December 2010] [10:49:48] <mikko>	maybe the closes you can get is:
| [Friday 10 December 2010] [10:49:56] <mikko>	a) give a sockopt for setting swap dir
| [Friday 10 December 2010] [10:50:04] <mikko>	b) check that swap dir is writable
| [Friday 10 December 2010] [10:50:14] <mikko>	c) leave the rest to user
| [Friday 10 December 2010] [10:50:24] <sustrik_>	what i mean was to crate the file would be created directly when setsockopt(SWAP) is called
| [Friday 10 December 2010] [10:50:28] <sustrik_>	rather than later on
| [Friday 10 December 2010] [10:50:39] <sustrik_>	thus the credentials would be checked immediately
| [Friday 10 December 2010] [10:50:59] <mikko>	yes, that would work as well
| [Friday 10 December 2010] [10:51:19] <sustrik_>	that should be rathereasy
| [Friday 10 December 2010] [10:51:20] <mikko>	and allow setting swap file name by sockopt
| [Friday 10 December 2010] [10:51:35] <sustrik_>	yes, that's an option
| [Friday 10 December 2010] [10:51:43] <mikko>	if not set default to current
| [Friday 10 December 2010] [10:52:05] <mikko>	a lot of daemons won't have write permissions to $PWD
| [Friday 10 December 2010] [10:52:15] <sustrik_>	right
| [Friday 10 December 2010] [10:52:29] <sustrik_>	can you fill an issue in the bugtracker so that we don't forget about it?
| [Friday 10 December 2010] [10:54:09] <mikko>	sustrik_: even better, i can create an issue and try to create patch tonight
| [Friday 10 December 2010] [10:57:23] <mikko>	issue 140
| [Friday 10 December 2010] [10:58:49] <sustrik_>	:)
| [Saturday 11 December 2010] [06:43:41] <mikko>	sustrik: you there?
| [Saturday 11 December 2010] [06:43:52] <sustrik>	hi
| [Saturday 11 December 2010] [06:44:11] <mikko>	i created a small patch for the swap
| [Saturday 11 December 2010] [06:44:33] <mikko>	now it fails when you try to set invalid swap file. the implementation doesn't feel ideal but it works
| [Saturday 11 December 2010] [06:44:47] <sustrik>	mikko: i'll review it
| [Saturday 11 December 2010] [06:44:53] <sustrik>	just send it to the ml
| [Saturday 11 December 2010] [06:46:05] <mikko>	is there a portable PATH_MAX ?
| [Saturday 11 December 2010] [06:57:26] <sustrik>	mikko: let me see
| [Saturday 11 December 2010] [06:58:05] <sustrik>	it's POSIX
| [Saturday 11 December 2010] [06:58:05] <sustrik>	http://www.opengroup.org/onlinepubs/009695399/basedefs/limits.h.html
| [Saturday 11 December 2010] [07:18:51] <mikko>	http://valokuva.org/~mikko/swap.patch it's there for now. does it look sensible?
| [Saturday 11 December 2010] [07:19:09] <mikko>	i'll mail ml later, now i need to vacuum before my better half comes back from hair dresser :)
| [Saturday 11 December 2010] [07:31:11] <mikko>	hmm
| [Saturday 11 December 2010] [07:31:24] <mikko>	maybe it would make more sense to move swap to options
| [Saturday 11 December 2010] [07:31:38] <mikko>	and initialize it when user sets swap size 
| [Saturday 11 December 2010] [07:34:21] <sustrik>	mikko: yes, that's what i had in mind originally
| [Saturday 11 December 2010] [07:34:32] <sustrik>	there's one problem though
| [Saturday 11 December 2010] [07:34:53] <sustrik>	on the bind side there are N connections
| [Saturday 11 December 2010] [07:35:01] <sustrik>	the number is unspecified
| [Saturday 11 December 2010] [07:35:09] <sustrik>	so you cannot create the files in advance
| [Saturday 11 December 2010] [07:35:28] <sustrik>	maybe creating a single dummy file to check the permissions would do?
| [Saturday 11 December 2010] [07:37:35] <mikko>	that should be fine
| [Saturday 11 December 2010] [07:37:53] <mikko>	or maybe even check if the folder is writable
| [Saturday 11 December 2010] [07:38:01] <mikko>	not sure how that works with windows acls etc
| [Saturday 11 December 2010] [07:38:06] <sustrik>	if possible with POSIX API...
| [Saturday 11 December 2010] [07:38:24] <sustrik>	creating a dummy seems easier imo
| [Saturday 11 December 2010] [07:40:43] <mikko>	should the swap append sequence number to filename given?
| [Saturday 11 December 2010] [07:41:02] <mikko>	so if i give /tmp/test.swap the actual filename would be /tmp/test.swap.1
| [Saturday 11 December 2010] [07:41:05] <mikko>	or something
| [Saturday 11 December 2010] [09:46:36] <mikko>	sustrik: i think swap_dir option makes more sense than swap file
| [Sunday 12 December 2010] [05:35:43] <mathijs>	Hi all, is it possible to find out how many messages are currently buffered?
| [Sunday 12 December 2010] [05:36:56] <mathijs>	I like the HWM and the transparent way things get handled in 0mq, but I would like to do some custom stuff when problems arise
| [Sunday 12 December 2010] [05:38:27] <mathijs>	So if a buffer starts to fill up, or reaches HWM, I would like my program to log warnings about it, or talk to some controller process about it.
| [Sunday 12 December 2010] [05:40:59] <mathijs>	ofcourse I can have my processes all log every received/sent message through some other socket to have a central process track overall flow, but it would be nice if there was a more low-level way
| [Sunday 12 December 2010] [05:42:32] <sustrik>	set hwm, send in non-blocking way
| [Sunday 12 December 2010] [05:42:47] <rgl>	mathijs, I don't think its possible right now; but from what I understood, future ZMQ version will have a way to accesses those events.
| [Sunday 12 December 2010] [05:42:48] <sustrik>	when zmq_send returns EAGAIN, the buffer is full
| [Sunday 12 December 2010] [05:43:04] <rgl>	oh we can? *G*
| [Sunday 12 December 2010] [05:43:34] <mathijs>	sustrik: so set a low hwm to have the application handle it?
| [Sunday 12 December 2010] [05:43:47] <sustrik>	if you want so
| [Sunday 12 December 2010] [05:44:08] <sustrik>	think of the queue as a network buffer
| [Sunday 12 December 2010] [05:44:10] <rgl>	we can also store the messages in a file, right?
| [Sunday 12 December 2010] [05:44:31] <sustrik>	you can offload them to the disk,yes
| [Sunday 12 December 2010] [05:46:18] <mathijs>	hmmm ok, that will work for preventing problems.   but what I would like as well is a way to shut down an application safely. I understood 0mq 2.1 will wait for all messages to be handled (empty buffers). So in case one buffer isn't empty yet, and waiting for some other process to come up, I would like to find out what socket/buffer is waiting
| [Sunday 12 December 2010] [05:50:28] <rgl>	indeed, it would be nice to get the current state of a socket (or receive events about state changes). this is something that will be available on the future right sustrik?
| [Sunday 12 December 2010] [07:30:26] <sustrik>	mathijs, rgl: the number of messages in 0MQ queue is an irrelevant statistic, the messages are queue along the whole path from sender to receiver, in 0MQ buffers, TCP buffers, NICs, switch and router queues etc.
| [Sunday 12 December 2010] [07:33:43] <rgl>	sustrik, humm. sure, but they give you some hint if anything might be wrong. for example, how do we known why the messages are pilling up? it might be because a single consumer is delaying the whole seebang.
| [Sunday 12 December 2010] [07:34:38] <rgl>	or for some reason we stopped to be able to connect the socket that once was working fine.
| [Sunday 12 December 2010] [07:34:42] <sustrik>	that's why slow consumers are disconnected in pub/sub pattern
| [Sunday 12 December 2010] [07:35:05] <rgl>	indeed, but currently, how do you known it was disconnected?
| [Sunday 12 December 2010] [07:35:17] <sustrik>	yes, "cannot reconnect" problem should be logged
| [Sunday 12 December 2010] [07:35:34] <sustrik>	because it may be a signal to admins that something went wrong
| [Sunday 12 December 2010] [07:35:39] <sustrik>	and manual intervntion is needed
| [Sunday 12 December 2010] [07:36:12] <rgl>	indeed, thats something that we should be able to log, and to monitor, so we can act uppon it.
| [Sunday 12 December 2010] [07:36:27] <sustrik>	there's a logging mechanism in 0MQ, but at the moment nobody logs anything
| [Sunday 12 December 2010] [07:36:29] <sustrik>	TODO
| [Sunday 12 December 2010] [07:38:12] <rgl>	I might be wrong, but I though there were some messages on the ML about funneling that into some in-queue that could be consumed as a regular socket.
| [Sunday 12 December 2010] [10:02:43] <mikko>	sustrik: Assertion failed: stored (pipe.cpp:238)
| [Sunday 12 December 2010] [10:02:54] <mikko>	what should be the behavior when swap fills up?
| [Sunday 12 December 2010] [10:03:14] <mikko>	happens in zmq::writer_t::write pipe.cpp
| [Sunday 12 December 2010] [10:06:17] <mikko>	actually it should probably return false in bool zmq::writer_t::write (zmq_msg_t *msg_)
| [Sunday 12 December 2010] [10:34:05] <benoitc>	hi all
| [Sunday 12 December 2010] [10:34:47] <benoitc>	can we fork processes and share a zeromq "socket" between children ?
| [Sunday 12 December 2010] [10:34:54] <benoitc>	with pyzmq
| [Sunday 12 December 2010] [10:49:01] <cremes>	benoitc: i doubt that is supported; it's not a good idea at all
| [Sunday 12 December 2010] [10:49:35] <cremes>	if the children need to communicate with each other, open up sockets that are specific to that job
| [Sunday 12 December 2010] [11:04:55] <benoitc>	so i need to open a zmq socket per worker on the parent process ?
| [Sunday 12 December 2010] [11:06:12] <cremes>	benoitc: that's what i would recommend
| [Sunday 12 December 2010] [11:06:25] <cremes>	these sockets are "cheap" so i wouldn't worry about computational cost
| [Sunday 12 December 2010] [11:07:18] <benoitc>	hm ok
| [Sunday 12 December 2010] [11:07:20] <benoitc>	thanks
| [Sunday 12 December 2010] [11:07:52] <cremes>	saying "hmmm" implies you either don't agree or you don't understand why
| [Sunday 12 December 2010] [11:07:58] <cremes>	do you still have a question?
| [Sunday 12 December 2010] [11:08:22] <benoitc>	well it means i've to rethink my design :)
| [Sunday 12 December 2010] [11:08:58] <benoitc>	i was thinking at first to just open a zmq like any socket and make it not blocking
| [Sunday 12 December 2010] [11:09:04] <cremes>	not necessarily; if your design called for multiple children to all listen to the same socket then perhaps a device in the middle will solve your issue
| [Sunday 12 December 2010] [11:09:50] <cremes>	all children can connect to the device on the same port and the device will (depending on socket type) deliver messages to the children
| [Sunday 12 December 2010] [11:09:51] <benoitc>	well idea was to balance between workers as soon as a message is send to the socket
| [Sunday 12 December 2010] [11:10:00] <cremes>	definitely read the guide if you haven't done so yet
| [Sunday 12 December 2010] [11:10:12] <cremes>	so you are using req/rep sockets?
| [Sunday 12 December 2010] [11:13:32] <cremes>	i need to run out for about 90m; feel free to post a description of what you are trying to do
| [Sunday 12 December 2010] [11:13:39] <cremes>	i'll try to give some guidance when i return
| [Sunday 12 December 2010] [11:14:14] <benoitc>	mm yes I should reply i took the message I guess
| [Sunday 12 December 2010] [11:14:43] <benoitc>	in my first approach wanted to have this balancing you can do with "normal" sockets
| [Sunday 12 December 2010] [11:14:51] <benoitc>	anyway later
| [Sunday 12 December 2010] [11:15:41] 	 * benoitc want the sockett.accept like
| [Sunday 12 December 2010] [11:53:37] <mikko>	benoitc: 0MQ has load-balancing built-in
| [Sunday 12 December 2010] [11:56:29] <benoitc>	mikko: so once the message is get by one listsner in req/rep it won't be send to other listeners ?
| [Sunday 12 December 2010] [11:56:36] <benoitc>	(just want to make sure)
| [Sunday 12 December 2010] [11:58:24] <mikko>	benoitc: different socket types have different kind of distribution algorithms
| [Sunday 12 December 2010] [11:58:37] <mikko>	for example in PUB/SUB the published message is sent to all subscribers
| [Sunday 12 December 2010] [11:59:07] <mikko>	but for example PUSH/PULL balances between live connections
| [Sunday 12 December 2010] [11:59:14] <mikko>	you should really read zguide
| [Sunday 12 December 2010] [13:00:52] <cremes>	benoitc: mikko is right; most of this is covered in the guide:  http://zguide.zeromq.org/chapter:all
| [Sunday 12 December 2010] [13:01:02] <cremes>	for some reason, that link is returning a 503 right now
| [Sunday 12 December 2010] [13:01:20] <cremes>	sustrik, pieterh: the guide is offline
| [Sunday 12 December 2010] [13:01:30] <cremes>	it's returning a 503 error
| [Sunday 12 December 2010] [13:26:35] <mikko>	cremes: works from here
| [Sunday 12 December 2010] [13:27:07] <cremes>	mikko: it's responding now for me too but it wasn't before
| [Sunday 12 December 2010] [14:18:38] <benoitc>	yeah reading it 
| [Sunday 12 December 2010] [14:18:41] <benoitc>	thanks
| [Sunday 12 December 2010] [15:14:53] <sustrik>	mikko: what version is that?
| [Sunday 12 December 2010] [15:15:19] <sustrik>	what it should do is behave the same way is if HWM is reached
| [Sunday 12 December 2010] [15:15:30] <sustrik>	block, drop, whatever
| [Sunday 12 December 2010] [15:15:37] <sustrik>	depending on the pattern
| [Sunday 12 December 2010] [15:18:32] <mikko>	sustrik: trunk, the lines won't match as i have some local changes
| [Sunday 12 December 2010] [15:19:15] <mikko>	sustrik: yes, probably
| [Sunday 12 December 2010] [15:19:16] <sustrik>	i see, so which assertion was actually hit?
| [Sunday 12 December 2010] [15:19:28] <mikko>	sustrik: writer_t::write
| [Sunday 12 December 2010] [15:19:35] <mikko>	when swap is full 
| [Sunday 12 December 2010] [15:19:40] <mikko>	let me check the upstread lineno
| [Sunday 12 December 2010] [15:19:43] <sustrik>	zmq_assert (stored); ?
| [Sunday 12 December 2010] [15:20:20] <mikko>	https://github.com/zeromq/zeromq2/blob/master/src/pipe.cpp#L237
| [Sunday 12 December 2010] [15:20:22] <mikko>	yes
| [Sunday 12 December 2010] [15:20:53] <sustrik>	looks like a bug
| [Sunday 12 December 2010] [15:20:57] <mathijs>	I read some discussion about socket migrations and memory barriers. I never heard of those before, so I probably shouldn't touch stuff...  but I think I have a possible usecase. GHC (haskell) uses a IO manager which manages a pool of OS threads. On top of those, it runs "green threads". A green thread can signal it's waiting for some FD. execution stops. When the fd is ready (epoll), execution resumes. But it's possible that it's mapped to a
| [Sunday 12 December 2010] [15:20:57] <mathijs>	 different OS thread
| [Sunday 12 December 2010] [15:21:10] <sustrik>	afaiu the saving of messages to the swap is not atomic
| [Sunday 12 December 2010] [15:21:37] <sustrik>	i.e. you can store one message part and next one is rejected
| [Sunday 12 December 2010] [15:21:44] <sustrik>	should be fixed
| [Sunday 12 December 2010] [15:22:40] <mathijs>	is the case I describe a valid one for using socket migrations? 
| [Sunday 12 December 2010] [15:24:47] <sustrik>	yes, that was the main use case for the "migration" feature
| [Sunday 12 December 2010] [15:25:14] <sustrik>	you can assume that the memory barriers are handled correctly by haskell runtime
| [Sunday 12 December 2010] [15:25:23] <mathijs>	I can signal the IO manager that a certain green thread gets mapped to the same OS thread every time it runs/continues, but having them scheduled on the least-busy OS thread sounds better.
| [Sunday 12 December 2010] [15:25:48] <sustrik>	yes, it should work
| [Sunday 12 December 2010] [15:25:58] <mathijs>	sustrik: thanks
| [Sunday 12 December 2010] [16:08:57] <mikko>	sustrik: so, i'm thinking about the whole swap thing
| [Sunday 12 December 2010] [16:09:20] <mikko>	what do you think about abstracting the swap slightly further?
| [Sunday 12 December 2010] [16:09:46] <mikko>	maybe something like: make the swap implementation pluggable and use inproc pipe to communicate with the swap engine
| [Sunday 12 December 2010] [16:24:25] <sustrik>	mikko: that way you would introduce a bottleneck
| [Sunday 12 December 2010] [16:25:05] <mikko>	but swap is going to be a bottleneck in any case
| [Sunday 12 December 2010] [16:25:05] <sustrik>	you can always make a device that would store messages on the disk if you want to
| [Sunday 12 December 2010] [16:25:43] <mikko>	the whole concept of swapping is more preserving operation rather than performance
| [Sunday 12 December 2010] [16:26:17] <sustrik>	the point is that you want the swap as fast as possible exactly because it is slow
| [Sunday 12 December 2010] [16:26:25] <sustrik>	so, for example
| [Sunday 12 December 2010] [16:26:38] <sustrik>	if your apps falls over into swap mode
| [Sunday 12 December 2010] [16:27:00] <sustrik>	you want it to get out of it as fast as possible once the network is up and running again
| [Sunday 12 December 2010] [16:29:04] <sustrik>	if you make it slow it may even happen that it will never get out of the swap mode
| [Sunday 12 December 2010] [16:29:14] <sustrik>	it's kind of tricky
| [Sunday 12 December 2010] [16:29:26] <mikko>	how much overhead does forwarding a message over inproc pipe add?
| [Sunday 12 December 2010] [16:29:48] <sustrik>	dunno
| [Sunday 12 December 2010] [16:29:52] <sustrik>	should be measured
| [Sunday 12 December 2010] [16:30:56] <sustrik>	maybe it would make no difference at all
| [Sunday 12 December 2010] [16:31:59] <mikko>	if there is little or no overhead it would allow people to implement optimised swap solutions
| [Sunday 12 December 2010] [16:32:07] <sustrik>	sure
| [Sunday 12 December 2010] [16:32:34] <mikko>	i noticed that there is the posix_fadvise for linux 
| [Sunday 12 December 2010] [16:32:39] <sustrik>	yes
| [Sunday 12 December 2010] [16:32:46] <mikko>	but there are probably available optimizations for other platforms as well
| [Sunday 12 December 2010] [16:33:16] <mikko>	my point with this was: swap is really something that doesn't necessarily need to be in 0MQ core
| [Sunday 12 December 2010] [16:33:24] <sustrik>	ack
| [Sunday 12 December 2010] [16:33:33] <mikko>	if the implementation was pluggable it would allow people to make their own and share them
| [Sunday 12 December 2010] [16:33:41] <mikko>	not sure, it's tricky
| [Sunday 12 December 2010] [16:33:48] <sustrik>	it was added as a feature paid for by a customer
| [Sunday 12 December 2010] [16:34:26] <sustrik>	so it's kind of a hack atm
| [Sunday 12 December 2010] [16:35:20] <mikko>	void zmq::swap_t::rollback ()
| [Sunday 12 December 2010] [16:35:24] <mikko>	is that used ?
| [Sunday 12 December 2010] [16:35:25] <sustrik>	let me think about it...
| [Sunday 12 December 2010] [16:35:37] <mikko>	as it seems that it ends up into assertion in any possible path
| [Sunday 12 December 2010] [16:35:38] <sustrik>	mikko: it should be afaics
| [Sunday 12 December 2010] [16:35:59] <mikko>	well, possibly ends up
| [Sunday 12 December 2010] [16:36:04] <sustrik>	hm, quite possibly i've broken the implementation when i did all the changes for 2.1
| [Sunday 12 December 2010] [16:37:15] <sustrik>	well, it would be nice is swapping was implemented as a device
| [Sunday 12 December 2010] [16:37:30] <sustrik>	so you would just plug it in-between two nodes to get swap
| [Sunday 12 December 2010] [16:38:02] <sustrik>	one problem is that by doing so you have to do two hops instead of a single one
| [Sunday 12 December 2010] [16:38:17] <sustrik>	even though swap is not being used at the moment
| [Sunday 12 December 2010] [16:38:23] <mikko>	that is true
| [Sunday 12 December 2010] [16:38:43] <mikko>	but would you use swap if you were aiming for absolute performance?
| [Sunday 12 December 2010] [16:38:59] <sustrik>	actually, i like the idea
| [Sunday 12 December 2010] [16:39:28] <sustrik>	we could just say 'sorry, there's performance impact with swap'
| [Sunday 12 December 2010] [16:39:49] <mikko>	so, if you were to generalise this a bit further
| [Sunday 12 December 2010] [16:40:29] <mikko>	zmq_callback_device which takes function pointers for message received from front and sent out to back
| [Sunday 12 December 2010] [16:40:43] <mikko>	then swap would implement functions for storing and removing
| [Sunday 12 December 2010] [16:40:55] <mikko>	you could use the same pattern for implementing 'persistent' things
| [Sunday 12 December 2010] [16:41:04] <mikko>	not sure about exact details yet
| [Sunday 12 December 2010] [16:41:12] <sustrik>	right, it's just a device
| [Sunday 12 December 2010] [16:41:32] <sustrik>	i would like to move devices out of core 0mq with 3.0
| [Sunday 12 December 2010] [16:41:49] <sustrik>	swap could be removed as well at that point
| [Sunday 12 December 2010] [16:41:55] <mikko>	i think for devices to be more useful is a way to stop them without SIGINT
| [Sunday 12 December 2010] [16:42:01] <sustrik>	and instead we can provide a standalone swapping device
| [Sunday 12 December 2010] [16:42:24] <sustrik>	yes, you want a remote managementy
| [Sunday 12 December 2010] [16:42:46] <mikko>	void *device = zmq_device(...); while (1) { if (shutdown) { device_shutdown(device); } sleep(5); }
| [Sunday 12 December 2010] [16:42:49] <mikko>	something like that
| [Sunday 12 December 2010] [16:43:26] <sustrik>	shutdown sent as a message to the device, right?
| [Sunday 12 December 2010] [16:43:31] <mikko>	yes, currently in my small program i run device in a thread and just use pthread_cancel to stop the device thread
| [Sunday 12 December 2010] [16:43:33] <sustrik>	from the management console
| [Sunday 12 December 2010] [16:43:44] <mikko>	that is a possibility yes
| [Sunday 12 December 2010] [16:43:57] <mikko>	but does it open the device for DoS ?
| [Sunday 12 December 2010] [16:44:07] <mikko>	or do you mean some sort of internal message?
| [Sunday 12 December 2010] [16:44:16] <sustrik>	you need authentication etc.
| [Sunday 12 December 2010] [16:44:30] <sustrik>	the whole device thing is where development will happen in the future imo
| [Sunday 12 December 2010] [16:45:11] <sustrik>	actually, what i foresee is that devices will be removed from core 0mq
| [Sunday 12 December 2010] [16:45:35] <sustrik>	there will be various open source devices
| [Sunday 12 December 2010] [16:45:51] <sustrik>	but there can also be complex proprietary devices
| [Sunday 12 December 2010] [16:46:05] <mikko>	we should have a hackathon on removing all these assertions at some point
| [Sunday 12 December 2010] [16:46:14] <sustrik>	think of how cisco builds boxes for TCP/IP stack
| [Sunday 12 December 2010] [16:46:47] <sustrik>	yes, but it has to happen with new major version
| [Sunday 12 December 2010] [16:46:50] <sustrik>	i.e. 3.0
| [Sunday 12 December 2010] [16:47:01] <sustrik>	as it's not backward compatible
| [Sunday 12 December 2010] [16:49:41] <mikko>	thats true
| [Sunday 12 December 2010] [18:36:00] Notice	-tomaw- [Global Notice] We're restarting services to fix some database issues; please remain patient as it will return soon.
| [Monday 13 December 2010] [07:09:29] <mikko>	sustrik: hi
| [Monday 13 December 2010] [07:13:54] <sustrik>	hi
| [Monday 13 December 2010] [07:16:19] <mikko>	again, thinking out loud here: extending uris to allow shortcut for setting socket options
| [Monday 13 December 2010] [07:16:46] <mikko>	tcp://127.0.0.1:5555?linger=1000&identity=mytestsocket
| [Monday 13 December 2010] [07:17:11] <mikko>	although this could be done in the user application as well
| [Monday 13 December 2010] [07:17:16] <sustrik>	can be useful but should be implemented as a layer on top of 0mq
| [Monday 13 December 2010] [07:17:24] <sustrik>	exactly
| [Monday 13 December 2010] [07:17:48] <sustrik>	the problem is that this kind of thing means wandering far away from POSIX
| [Monday 13 December 2010] [07:17:53] <ianbarber>	maybe a standard function in zfl for creating sockets from a url like that?
| [Monday 13 December 2010] [07:18:01] <sustrik>	for example
| [Monday 13 December 2010] [07:18:15] <sustrik>	it's useful, so it's worth of implementing it
| [Monday 13 December 2010] [07:24:05] <sustrik>	mikko: btw, i've added your idea about swap->device to 3.0 roadmap
| [Monday 13 December 2010] [07:24:09] <sustrik>	http://www.zeromq.org/docs:3-0
| [Monday 13 December 2010] [07:25:56] <mikko>	sustrik: cool
| [Monday 13 December 2010] [07:26:14] <mikko>	i was thinking about the control channel
| [Monday 13 December 2010] [07:26:29] <mikko>	it's not necessary to do it over a remote management
| [Monday 13 December 2010] [07:26:49] <mikko>	as if there was a device handle (void *) like with sockets then people could build their own if that is a requirement
| [Monday 13 December 2010] [07:26:55] <mikko>	lunch ->
| [Monday 13 December 2010] [07:29:31] <sustrik>	i don't follow
| [Monday 13 December 2010] [07:29:46] <sustrik>	people can build their own device even now, no?
| [Monday 13 December 2010] [07:30:29] <mrm2m>	Hey ho!
| [Monday 13 December 2010] [07:31:57] <ianbarber>	sustrik: i think the idea was to allow control flow outside the device, so the device runs in another thread, and the control is done through the parent process. 
| [Monday 13 December 2010] [07:32:25] <sustrik>	hi
| [Monday 13 December 2010] [07:32:32] <sustrik>	ianbarber: sure
| [Monday 13 December 2010] [07:32:46] <sustrik>	what i meant was that you can do such thing even today
| [Monday 13 December 2010] [07:32:54] <mrm2m>	Is there a one directional socket type? I've got some data I'd like to send to a server, but I'm not interested in any message if the data was received correctly or even if it was received. 
| [Monday 13 December 2010] [07:33:03] <ianbarber>	push
| [Monday 13 December 2010] [07:33:11] <sustrik>	mrm2m: PUB/SUB presumably
| [Monday 13 December 2010] [07:33:22] <sustrik>	it's completely uni-directional
| [Monday 13 December 2010] [07:33:43] <ianbarber>	sustrik: yeah, you can, but only if you create the device yourself - though I guess you could wrap a device available from elsewhere with one your own
| [Monday 13 December 2010] [07:34:13] <mrm2m>	Ah - I thought that was for one PUB sending to several SUBs. 
| [Monday 13 December 2010] [07:34:21] <sustrik>	yes
| [Monday 13 December 2010] [07:34:30] <sustrik>	and what do you need instead?
| [Monday 13 December 2010] [07:34:37] <mrm2m>	I need to send from several PUBs to one SUB.
| [Monday 13 December 2010] [07:34:49] <sustrik>	that would work as well
| [Monday 13 December 2010] [07:34:55] <sustrik>	ianbarber: ah, the plan is to move devices out of 0mq core anyway
| [Monday 13 December 2010] [07:35:05] <sustrik>	and make them separate projects
| [Monday 13 December 2010] [07:35:08] <ianbarber>	ah, ok. that makes sense
| [Monday 13 December 2010] [07:35:16] <sustrik>	so you could have different types of devices
| [Monday 13 December 2010] [07:35:37] <sustrik>	the one with control socket propsed above could be one available device
| [Monday 13 December 2010] [07:35:38] <sustrik>	etc.
| [Monday 13 December 2010] [07:35:40] <mrm2m>	sustrik: Ok. Then I'll have a look on SUB/PUB. 
| [Monday 13 December 2010] [08:19:34] <CIA-20>	zeromq2: 03Dhammika Pathirana 07master * r22b2b9a 10/ (src/tcp_listener.cpp src/tcp_listener.hpp): 
| [Monday 13 December 2010] [08:19:34] <CIA-20>	zeromq2: fix overwriting errno on bind failure
| [Monday 13 December 2010] [08:19:34] <CIA-20>	zeromq2: Signed-off-by: Dhammika Pathirana <dhammika@gmail.com> - http://bit.ly/eB0FKT
| [Monday 13 December 2010] [09:17:54] <ianbarber>	yay, that's all the zguide examples translated into php :) committed the version one I needed mikko's patch for
| [Monday 13 December 2010] [09:26:08] <mikko>	sustrik: pipe.cpp:56
| [Monday 13 December 2010] [09:26:28] <mikko>	i reckon that should exit the device rather than assert
| [Monday 13 December 2010] [09:26:45] <sustrik>	let me see
| [Monday 13 December 2010] [09:27:07] <sustrik>	i have a comment on that line :(
| [Monday 13 December 2010] [09:27:13] <sustrik>	can you paste the line here?
| [Monday 13 December 2010] [09:27:28] <mikko>	errno_assert (false);
| [Monday 13 December 2010] [09:27:37] <mikko>	after rc = zmq_poll (&items [0], 2, -1);
| [Monday 13 December 2010] [09:27:48] <mikko>	i got a signal handler in my process that catches SIGINT
| [Monday 13 December 2010] [09:28:00] <mikko>	it seems to however cause zmq_poll to return
| [Monday 13 December 2010] [09:28:05] <mikko>	and causes following assertion:
| [Monday 13 December 2010] [09:28:11] <mikko>	^CInterrupted system call
| [Monday 13 December 2010] [09:28:11] <mikko>	false (device.cpp:56)
| [Monday 13 December 2010] [09:28:12] <mikko>	Aborted
| [Monday 13 December 2010] [09:28:42] <mikko>	if i don't catch sigint then the program exits immediately
| [Monday 13 December 2010] [09:29:01] <sustrik>	device or pipe.coo?
| [Monday 13 December 2010] [09:29:03] <sustrik>	cpp
| [Monday 13 December 2010] [09:29:21] <mikko>	sorry, device.cpp
| [Monday 13 December 2010] [09:29:21] <sustrik>	ah, have it
| [Monday 13 December 2010] [09:29:52] <sustrik>	yes, it works that way
| [Monday 13 December 2010] [09:30:03] <sustrik>	what should be presumably done
| [Monday 13 December 2010] [09:30:16] <sustrik>	is to return EINTR from the zmq_device call
| [Monday 13 December 2010] [09:31:33] <mikko>	yeah, would allow clean termination of parent program
| [Monday 13 December 2010] [09:31:56] <mikko>	as running device in a thread and then doing pthread_cancel doesn't seem particulary clean either
| [Monday 13 December 2010] [09:32:09] <mikko>	im surprised that it doesn't assert on pthread_cancel
| [Monday 13 December 2010] [09:34:18] <sustrik>	i assume that just kills the thread at the spot
| [Monday 13 December 2010] [09:34:26] <sustrik>	so it has no chance to assert
| [Monday 13 December 2010] [09:37:53] <mikko>	looking at the code, i think it shouldn't assert at all
| [Monday 13 December 2010] [09:38:00] <mikko>	as the caller can handle device exiting
| [Monday 13 December 2010] [09:41:08] <CIA-20>	zeromq2: 03Dhammika Pathirana 07master * rf749f2d 10/ (src/socket_base.cpp src/socket_base.hpp): 
| [Monday 13 December 2010] [09:41:08] <CIA-20>	zeromq2: add basic uri validations
| [Monday 13 December 2010] [09:41:08] <CIA-20>	zeromq2: Signed-off-by: Dhammika Pathirana <dhammika@gmail.com> - http://bit.ly/hptlRa
| [Monday 13 December 2010] [09:41:37] <sustrik>	mikko: good point
| [Monday 13 December 2010] [09:43:14] <mikko>	you could even send the original errno back
| [Monday 13 December 2010] [09:46:07] <sustrik>	yes
| [Monday 13 December 2010] [09:59:04] <mikko>	sustrik: https://gist.github.com/cc8ca1efb295254bc634
| [Monday 13 December 2010] [10:03:13] <sustrik>	mikko: looks good
| [Monday 13 December 2010] [10:03:19] <sustrik>	can you send it as patch to the ml?
| [Monday 13 December 2010] [10:20:42] <sustrik>	mikko: checking your swapdir patch
| [Monday 13 December 2010] [10:20:51] <sustrik>	what's the point of having 3 test functions?
| [Monday 13 December 2010] [10:20:55] <sustrik>	+        static bool test (const std::string& directory_);
| [Monday 13 December 2010] [10:20:55] <sustrik>	+
| [Monday 13 December 2010] [10:20:55] <sustrik>	+        static bool test (const char* directory_);
| [Monday 13 December 2010] [10:20:55] <sustrik>	+
| [Monday 13 December 2010] [10:20:55] <sustrik>	+        static bool test ();
| [Monday 13 December 2010] [10:29:00] <mikko>	sustrik: overloaded for different types i guess
| [Monday 13 December 2010] [10:29:16] <sustrik>	i mean, do you use all 3 of them?
| [Monday 13 December 2010] [10:29:21] <mikko>	sustrik: yes
| [Monday 13 December 2010] [10:29:32] <mikko>	what i think about now
| [Monday 13 December 2010] [10:29:38] <mikko>	does it make sense to amend the swap now
| [Monday 13 December 2010] [10:29:45] <mikko>	if it goes to heavy refactoring soon
| [Monday 13 December 2010] [10:29:57] <sustrik>	well, depends on you
| [Monday 13 December 2010] [10:30:10] <sustrik>	if you need it asap, i'll apply it
| [Monday 13 December 2010] [10:30:59] <mikko>	i don't need asap
| [Monday 13 December 2010] [10:31:09] <mikko>	i can work around it and document for php extension
| [Monday 13 December 2010] [10:31:43] <mikko>	at the moment doing const char *tmp = getenv("TMPDIR"); if (!tmp) { tmp = "/tmp"; } chdir(tmp);
| [Monday 13 December 2010] [10:31:45] <sustrik>	ok then
| [Monday 13 December 2010] [10:32:27] <sustrik>	maybe just write a comment about it on the ml
| [Monday 13 December 2010] [10:32:36] <sustrik>	so that people know what happened to the patch
| [Monday 13 December 2010] [10:34:09] <mikko>	i'll write comment and send device patch today
| [Monday 13 December 2010] [10:34:39] <sustrik>	ok
| [Monday 13 December 2010] [12:37:13] <mikko>	sustrik: call to device is not consistent between C and C++
| [Monday 13 December 2010] [12:37:18] <mikko>	seems to be void in C++
| [Monday 13 December 2010] [12:37:21] <mikko>	and int in C
| [Monday 13 December 2010] [12:37:26] <mikko>	return type that is
| [Monday 13 December 2010] [12:39:16] <mikko>	error_t is int?
| [Monday 13 December 2010] [12:42:14] <mikko>	no, wait. got it
| [Monday 13 December 2010] [13:15:31] <myraft>	complete noob - quick question - where do I start? I am not sure if I even installed it correctly. Is there a zmq on linux that should be in the path?
| [Monday 13 December 2010] [13:17:15] <myraft>	Nevermind - found some Java examples on Github - will scan and ask the questions again. 
| [Monday 13 December 2010] [13:17:19] <myraft>	Thanks though.
| [Monday 13 December 2010] [13:18:21] <cremes>	myraft: make sure you run ldconfig so that the zmq libs get added to your linux library paths
| [Monday 13 December 2010] [13:19:00] <drbobbeaty>	myraft: it's probably best to read The Guide (it's that important): http://zguide.zeromq.org/chapter:all
| [Monday 13 December 2010] [13:19:25] <drbobbeaty>	It contains a lot of good information as well as a lot of examples in all kinds of languages.
| [Monday 13 December 2010] [13:21:11] 	 * davetoo is n00b but needs to figure out how one might do pub/sub with 0mq 
| [Monday 13 December 2010] [13:21:21] <davetoo>	with topic exchange-like behavior :)
| [Monday 13 December 2010] [13:23:21] <cremes>	davetoo: that's described in the guide too ;)
| [Monday 13 December 2010] [13:27:44] <myraft>	thanks folks - just found the guide as well 
| [Monday 13 December 2010] [14:13:32] <mikko>	sustrik: https://gist.github.com/848e949008e67ca542f7
| [Monday 13 December 2010] [14:14:31] <sustrik>	hm, that may be the problem that dhammika fixed
| [Monday 13 December 2010] [14:14:39] <sustrik>	i'll apply his patch tomorrow
| [Monday 13 December 2010] [14:15:15] <mikko>	cool
| [Monday 13 December 2010] [14:15:24] <mikko>	ianbarber stumbled on this with the php extension
| [Monday 13 December 2010] [14:15:26] <sustrik>	it's a heisenbug, right?
| [Monday 13 December 2010] [14:15:39] <mikko>	nope, can reproduce reliably
| [Monday 13 December 2010] [14:15:53] <sustrik>	ah, then it may be something different
| [Monday 13 December 2010] [14:16:05] <mikko>	if you take the .c file attached to the paste
| [Monday 13 December 2010] [14:16:09] <mikko>	compile and and 
| [Monday 13 December 2010] [14:16:14] <mikko>	compile and run
| [Monday 13 December 2010] [14:16:20] <sustrik>	right
| [Monday 13 December 2010] [14:16:22] <mikko>	it should segfault / show memory errors
| [Monday 13 December 2010] [15:32:22] <mikko>	i to the b
| [Monday 13 December 2010] [15:33:26] <ianbarber>	m to the k
| [Monday 13 December 2010] [15:40:58] <myraft>	when trying to run java program I get "UnsatisfiedLinkError: no jzmq in java.library.path" - I have done ldconfig -p |grep zmq and see they so are a loaded. I have tried recompiling the code. Any ideas ?
| [Monday 13 December 2010] [15:51:15] <mikko>	myraft: it seems to be complaining about jzmq
| [Monday 13 December 2010] [15:51:19] <mikko>	rather than zmq itself
| [Monday 13 December 2010] [15:52:09] <myraft>	ok
| [Monday 13 December 2010] [15:52:31] <myraft>	but not sure how to proceed - followed the instructions - 
| [Monday 13 December 2010] [15:53:20] <myraft>	nathanmarz - if I do ldconfig -p|grep for zmq I see libzmq.so along with ligjzmq.so  - 
| [Monday 13 December 2010] [15:53:42] <myraft>	I meant to direct that at mikko - 
| [Monday 13 December 2010] [15:54:05] <mikko>	myraft: is the directory where libjzmq.so is in java.library.path ?
| [Monday 13 December 2010] [15:55:07] <myraft>	mikko : libjzmq.so is in /usr/local/lib - "sheepishly" - not sure if it is java.library.path, how do I set it ?
| [Monday 13 December 2010] [15:56:36] <mikko>	myraft: i've no idea tbh, i don't use java myself
| [Monday 13 December 2010] [15:56:43] <mikko>	myraft: what version of zeromq are you using?
| [Monday 13 December 2010] [15:58:05] <myraft>	mikko: 2.0.10
| [Monday 13 December 2010] [15:58:28] <mikko>	myraft: can you test with current github trunk?
| [Monday 13 December 2010] [15:58:29] <mikko>	just in case
| [Monday 13 December 2010] [15:58:38] <mikko>	git clone https://github.com/zeromq/zeromq2.git
| [Monday 13 December 2010] [15:58:51] <mikko>	cd zeromq2 && ./autogen.sh && ./configure && make install
| [Monday 13 December 2010] [16:00:38] <myraft>	mikko: will do and postback  - thanks 
| [Monday 13 December 2010] [16:04:03] <myraft>	mikko - did that and see libzmq.so.1 created in /usr/local/bin - running the Java program still gives the same error. 
| [Monday 13 December 2010] [16:04:43] <myraft>	I did go thru installation instructions - and was confused about setting java.library.path - I did CLASSPATH instead in the .bashrc 
| [Monday 13 December 2010] [16:08:36] <myraft>	I wonder if I need to restart the system - since there is libconf daemon - and that will not see the changes. 
| [Monday 13 December 2010] [16:08:59] <myraft>	Anyways - thanks for the attempt - let me know if you have any more ideas.
| [Monday 13 December 2010] [16:14:08] <myraft>	I will leaving the workstation for a little bit and will be online later.
| [Monday 13 December 2010] [16:19:13] <mikko>	i dont think that makes a different
| [Monday 13 December 2010] [16:19:18] <mikko>	difference*
| [Monday 13 December 2010] [16:19:24] <mikko>	i can give it a go later
| [Monday 13 December 2010] [16:35:08] <mikko>	sustrik: still there?
| [Tuesday 14 December 2010] [00:07:52] <gandhijee>	hey, installed zmq on my system, and for my cross compiler, now my c++ programs won't compile unless i link in zmq, any ideas?
| [Tuesday 14 December 2010] [00:21:48] <EricL>	I am debating using 0mq as a possible 'logserver'. Basically just listen for messages and write them to a file (but these messages are JSON and will be coming at a very high rate of speed).  Is there a good use-case?
| [Tuesday 14 December 2010] [04:08:37] <mikko>	good morning
| [Tuesday 14 December 2010] [04:09:04] <Steve-o>	good afternoon
| [Tuesday 14 December 2010] [04:09:35] <Steve-o>	:P
| [Tuesday 14 December 2010] [04:12:30] <Steve-o>	quiet morning, nothing but net splits
| [Tuesday 14 December 2010] [04:13:44] <mikko>	indeed
| [Tuesday 14 December 2010] [04:13:49] <mikko>	europe is just waking up
| [Tuesday 14 December 2010] [04:14:41] <Steve-o>	I released OpenPGM 5.0.93 and 5.1.99, hopefully the latter is more friendly towards Solaris/x86
| [Tuesday 14 December 2010] [04:15:50] <Steve-o>	builds in ICC and Sun ONE strict mode, along with OSX and Cygwin too
| [Tuesday 14 December 2010] [04:16:48] <Steve-o>	I keep on messing up byte order macros on Solaris, the builds definitely work on Sparc
| [Tuesday 14 December 2010] [04:18:54] <mikko>	nice!
| [Tuesday 14 December 2010] [04:19:17] <Steve-o>	OSX is tedious as the libc is really old
| [Tuesday 14 December 2010] [04:19:39] <mikko>	i'll fix zeromq --with-pgm to build properly on solaris x86 at some point
| [Tuesday 14 December 2010] [04:19:47] <mikko>	haven't got access to sparc yet
| [Tuesday 14 December 2010] [04:20:06] <Steve-o>	remember there are 3 compilers on sparc to test
| [Tuesday 14 December 2010] [04:20:17] <Steve-o>	Sun ONE, Sun GCC, and GCC
| [Tuesday 14 December 2010] [04:20:28] <Steve-o>	all each with their own quirks
| [Tuesday 14 December 2010] [04:20:40] <mikko>	i can test all those on x86
| [Tuesday 14 December 2010] [04:21:13] <mikko>	hmm, currently the win7 builds using visual studio 2008
| [Tuesday 14 December 2010] [04:21:22] <mikko>	might upgrade to 2010 at some point
| [Tuesday 14 December 2010] [04:22:11] <Steve-o>	PGM should work in 2008, it is just that I found some really annoying bugs in the CRT socket libraries
| [Tuesday 14 December 2010] [04:22:35] <mikko>	that's not surprising
| [Tuesday 14 December 2010] [04:23:14] <Steve-o>	haven't tried mingw32 on Windows, only cross compiles
| [Tuesday 14 December 2010] [04:23:27] <Steve-o>	Scons on Cygwin is pretty terrible, although I think it's Python at fault
| [Tuesday 14 December 2010] [04:23:40] <mikko>	i could add mingw32 on windows to daily builds 
| [Tuesday 14 December 2010] [04:23:55] <mikko>	and possibly a BSD box
| [Tuesday 14 December 2010] [04:24:14] <Steve-o>	FreeBSD is nice to catch portability bugs
| [Tuesday 14 December 2010] [04:24:27] <Steve-o>	but the IP header quirk is annoying
| [Tuesday 14 December 2010] [04:24:48] <mikko>	should i go for OpenBSD might be even a bit more exotic
| [Tuesday 14 December 2010] [04:25:15] <mikko>	FreeBSD is a bit more user-friendly though
| [Tuesday 14 December 2010] [04:25:19] <Steve-o>	good luck, I've only used OpenBSD on Sparc
| [Tuesday 14 December 2010] [04:25:43] <mikko>	OpenBSD doesn't use GCC iirc
| [Tuesday 14 December 2010] [04:25:46] <Steve-o>	can be annoying to install, especially since getting the install is inconvenient
| [Tuesday 14 December 2010] [04:25:54] <Steve-o>	GCC 2.95 I believe
| [Tuesday 14 December 2010] [04:25:56] <mikko>	Portable C Compiler
| [Tuesday 14 December 2010] [04:26:09] <mikko>	ermm
| [Tuesday 14 December 2010] [04:27:30] <Steve-o>	maybe the change was recent
| [Tuesday 14 December 2010] [04:27:42] <mikko>	added to openbsd source tree 2007
| [Tuesday 14 December 2010] [04:27:49] <mikko>	was able to compile x86 kernel image 2009
| [Tuesday 14 December 2010] [04:27:56] <mikko>	according to wikipedia
| [Tuesday 14 December 2010] [04:28:13] <mikko>	but probably not the 'default' compiler yet
| [Tuesday 14 December 2010] [04:28:33] <Steve-o>	ok
| [Tuesday 14 December 2010] [04:28:42] <Steve-o>	tea time, catch you laters
| [Tuesday 14 December 2010] [04:29:11] <Steve-o>	I thnk Theo wants compiler that isn't GCC 3
| [Tuesday 14 December 2010] [04:29:17] <Steve-o>	hence the search for others
| [Tuesday 14 December 2010] [04:29:50] <mikko>	see you later
| [Tuesday 14 December 2010] [04:42:18] <sustrik>	morning
| [Tuesday 14 December 2010] [04:42:50] <mikko>	sustrik: did you see the patch for swap?
| [Tuesday 14 December 2010] [04:43:47] <sustrik>	juse seen it
| [Tuesday 14 December 2010] [04:43:58] <sustrik>	i have to do some administrative stuff
| [Tuesday 14 December 2010] [04:44:02] <sustrik>	then i'll have a look
| [Tuesday 14 December 2010] [04:44:26] <mikko>	col
| [Tuesday 14 December 2010] [04:44:28] <mikko>	+o
| [Tuesday 14 December 2010] [06:05:51] <mikko>	sustrik: does HWM option only work if set before bind/connect? If yes should the setsockopt fail?
| [Tuesday 14 December 2010] [06:09:45] <sustrik>	yes
| [Tuesday 14 December 2010] [06:09:55] <sustrik>	why should it fail?
| [Tuesday 14 December 2010] [06:10:10] <mikko>	if it has no effect
| [Tuesday 14 December 2010] [06:11:55] <sustrik>	it has effect on all subsequent connects and binds
| [Tuesday 14 December 2010] [06:56:55] <mikko>	hmm
| [Tuesday 14 December 2010] [06:57:02] <mikko>	how does that work?
| [Tuesday 14 December 2010] [06:57:10] <mikko>	i got a PUSH socket
| [Tuesday 14 December 2010] [06:57:16] <mikko>	connect, set hwm, connect
| [Tuesday 14 December 2010] [06:57:44] <mikko>	so that allows to do weighted load-balancing
| [Tuesday 14 December 2010] [06:59:28] <sustrik>	then the two connections have different HWMs
| [Tuesday 14 December 2010] [06:59:33] <sustrik>	the first is unlimited
| [Tuesday 14 December 2010] [06:59:44] <sustrik>	the second one has the hwm you've set
| [Tuesday 14 December 2010] [07:00:41] <mikko>	yeah, so in a scenario where second has HWM of 5 and it fills up the messages would go to first one
| [Tuesday 14 December 2010] [07:00:53] <mikko>	which makes sense, if you for example you have slower consumer on second socket
| [Tuesday 14 December 2010] [07:01:03] <mikko>	second connection i mean
| [Tuesday 14 December 2010] [08:53:40] <EricL>	I am debating using 0mq as a possible 'logserver'. Basically just listen for messages and write them to a file (but these messages are JSON and will be coming at a very high rate of speed).  Is this a good use-case?
| [Tuesday 14 December 2010] [09:02:38] <spht>	EricL: Do you have control over what is sending the log entries? If yes, perfect match (including possibilites for distributed logging), if no...uncertain
| [Tuesday 14 December 2010] [09:03:09] <EricL>	spht: I have 100% control over what's sending the logs.  I am writing what is sending the logs.
| [Tuesday 14 December 2010] [09:03:24] <spht>	EricL: Then it's perfect
| [Tuesday 14 December 2010] [09:03:26] <spht>	:)
| [Tuesday 14 December 2010] [09:04:22] <EricL>	spht: That's great news.  Problem is that I need to get it working quickly.  The client (sending piece) is in Ruby so that should be easy.  But I feel like the receiver should be in C for as much speed as possible (unless the receiver language doesn't matter).
| [Tuesday 14 December 2010] [09:04:57] <spht>	EricL: Prototype it in Ruby (I mean, a prototype will be just a few lines) and benchmark it. won't cost you much time
| [Tuesday 14 December 2010] [09:05:19] <spht>	EricL: Disclaimer:  I'm a 0mq-newbie ;)
| [Tuesday 14 December 2010] [09:05:37] <EricL>	spht: Fair enough.  How long did it take you to get something up and running?
| [Tuesday 14 December 2010] [09:06:26] <spht>	EricL:  I read the guide back to back, from there it's a matter of minutes in python (which is my weapon of choice), should be the same in ruby.  Read the guide though
| [Tuesday 14 December 2010] [09:07:02] <EricL>	I read the beginner part already, not the other 2 parts.
| [Tuesday 14 December 2010] [09:08:06] <spht>	I would bet that disk io will be the limiting factor not the messaging overhead...
| [Tuesday 14 December 2010] [09:08:18] <spht>	depending on what network you have of course :)
| [Tuesday 14 December 2010] [09:08:20] <EricL>	spht: I am thinking the same thing.
| [Tuesday 14 December 2010] [09:08:31] <EricL>	The network is a local GigE network.
| [Tuesday 14 December 2010] [09:12:25] <guido_g>	so split the work between multiple writers each with its own disk
| [Tuesday 14 December 2010] [09:13:08] <EricL>	guido_g: Sounds like that's the advanced stuff I need to work out.  Right now I am fine with a single machine.  The heavy load will be a month or two down the road.
| [Tuesday 14 December 2010] [09:13:14] <guido_g>	PUSH/PULL sockets would do the trick out of the box
| [Tuesday 14 December 2010] [09:14:00] <guido_g>	EricL: you were worried about the speed
| [Tuesday 14 December 2010] [09:17:13] <EricL>	guido_g: I am. That's why I am asking the questions.
| [Tuesday 14 December 2010] [09:18:12] <brandyn>	Hey I have a pub/sub setup where the sub is too busy to read all of the pub's messages.  What is happening now is that sub seems to be buffering everything.  How do I fix that?  I am using the python wrapper (I tried release and now dev from git)
| [Tuesday 14 December 2010] [09:19:03] <brandyn>	I have already set the HWM to 1, that didn't help.  And it is the client that seems to be buffering as it's memory usage balloons out of control
| [Tuesday 14 December 2010] [09:19:04] <guido_g>	if the sub is to slow, make it faster
| [Tuesday 14 December 2010] [09:19:23] <brandyn>	guido_g, not an option I'm shooting video frames at it and some devices can't handle all ofit
| [Tuesday 14 December 2010] [09:19:34] <guido_g>	if you set HWM you'll lose messages
| [Tuesday 14 December 2010] [09:19:41] <brandyn>	guido_g, yes that is what I want
| [Tuesday 14 December 2010] [09:19:54] <guido_g>	brandyn: too bad
| [Tuesday 14 December 2010] [09:19:56] <brandyn>	but I am not losing them enough clearly, the client is still buffering
| [Tuesday 14 December 2010] [09:20:44] <brandyn>	I guess I'm in the wrong place
| [Tuesday 14 December 2010] [09:30:03] <spht>	Uhm, 2 minute attention span is pretty short for asking questions on IRC :)
| [Tuesday 14 December 2010] [09:34:23] <spht>	EricL: You could also make the writer a pub socket and have different loggers listening to different messages, one way to partition the writes
| [Tuesday 14 December 2010] [09:35:57] <spht>	push socket on the other hand will give you round-robin style load balancing between different clients if you don't want to partition by message type
| [Tuesday 14 December 2010] [09:37:39] <guido_g>	don't forget that for now, the topic is filtered at the sub side
| [Tuesday 14 December 2010] [09:37:56] <guido_g>	so the message will be received and at least partially processed
| [Tuesday 14 December 2010] [09:38:22] <spht>	guido_g:  true!
| [Tuesday 14 December 2010] [09:38:46] <guido_g>	but i would go this route anyway, i'm a pub/sub fan :)
| [Tuesday 14 December 2010] [09:40:12] <EricL>	So the clients would be the pubs and the server would sub to multiiple clients?
| [Tuesday 14 December 2010] [09:40:51] <EricL>	I know that sounds backwards, but do I have the concept right?
| [Tuesday 14 December 2010] [09:41:18] <spht>	EricL:  no the clients should be sub sockets of course :)
| [Tuesday 14 December 2010] [09:41:37] <guido_g>	don't think in terms of sockets or connections
| [Tuesday 14 December 2010] [09:41:44] <guido_g>	start to think in messages instead
| [Tuesday 14 December 2010] [09:41:50] <EricL>	spht: The clients are the ones publishing the connections.
| [Tuesday 14 December 2010] [09:41:52] <guido_g>	makes life much easier
| [Tuesday 14 December 2010] [09:42:16] <guido_g>	publishing connections?
| [Tuesday 14 December 2010] [09:43:01] <spht>	why?
| [Tuesday 14 December 2010] [09:43:34] <guido_g>	why what?
| [Tuesday 14 December 2010] [09:44:18] <spht>	guido_g:  why the clients should bind and not the server
| [Tuesday 14 December 2010] [09:44:35] <guido_g>	spht: huh? where did i say that?
| [Tuesday 14 December 2010] [09:44:43] <spht>	guido_g:  you didn't, EricL did :)
| [Tuesday 14 December 2010] [09:44:47] <guido_g>	ahhh
| [Tuesday 14 December 2010] [09:45:03] <spht>	or, I didn't get enough coffee and is confused as usual ;)
| [Tuesday 14 December 2010] [09:45:20] <EricL>	spht: Maybe I should re-read the beginner stuff.  I guess I don't understand it.
| [Tuesday 14 December 2010] [09:46:00] <guido_g>	EricL: don't overreate the socket/connection/bind stuff
| [Tuesday 14 December 2010] [09:46:24] <EricL>	I am thinking that clients (the ones pushing the log messages) are the publishers and the server can subscribe to each client.
| [Tuesday 14 December 2010] [09:46:33] <guido_g>	as i said, to think in terms of messages is much more important
| [Tuesday 14 December 2010] [09:46:52] <guido_g>	client and server are way to overloaded
| [Tuesday 14 December 2010] [09:47:08] <guido_g>	i suggest using words like sender and receiver
| [Tuesday 14 December 2010] [09:47:29] <EricL>	guido_g: Ok.  Let me go back and do some reading.
| [Tuesday 14 December 2010] [09:47:51] <EricL>	I have to jump into a few meetings.  I'll be back later today if I can't figure this out.
| [Tuesday 14 December 2010] [09:48:23] <spht>	same here, bbl
| [Tuesday 14 December 2010] [09:48:34] <guido_g>	ahhh... the joys of working in a professional environment...   ]:->
| [Tuesday 14 December 2010] [11:38:37] <mikko>	good evening
| [Tuesday 14 December 2010] [12:07:56] <sustrik>	mikko: i haven't had chance to review the patch :(
| [Tuesday 14 December 2010] [12:08:03] <sustrik>	i have to leave now
| [Tuesday 14 December 2010] [12:08:08] <sustrik>	will do tomorrow
| [Tuesday 14 December 2010] [12:08:09] <sustrik>	sorry
| [Tuesday 14 December 2010] [12:08:20] <mikko>	no worries
| [Tuesday 14 December 2010] [12:08:44] <gandhijee>	hey, i installed zmq on my system, now my C++ programs won't compile unless i use -lzmq
| [Tuesday 14 December 2010] [12:09:07] <sustrik>	you mean unrelated C++ programs?
| [Tuesday 14 December 2010] [12:09:12] <mikko>	gandhijee: what system is that?
| [Tuesday 14 December 2010] [12:09:42] <gandhijee>	sustrik: right, even if i don't have the zmq header in, i still need -lzmq
| [Tuesday 14 December 2010] [12:10:00] <gandhijee>	2 systems, my gentoo laptop, plus my ARM toolchain thats installed on it
| [Tuesday 14 December 2010] [12:10:37] <mikko>	what is the error message you get?
| [Tuesday 14 December 2010] [12:10:56] <gandhijee>	one second
| [Tuesday 14 December 2010] [12:12:23] <gandhijee>	hmm, actually i guess it might be the way i am invoking the compile
| [Tuesday 14 December 2010] [12:12:34] <gandhijee>	i was calling gcc instead of g++ to compile to code
| [Tuesday 14 December 2010] [12:13:39] <mikko>	have you got CLFAGS, LDFLAGS or similar set?
| [Tuesday 14 December 2010] [12:20:53] <gandhijee>	no
| [Tuesday 14 December 2010] [14:41:16] <brandyn>	I have a pub/sub setup where the sub is too busy to read all of the pub's messages.  What is happening now is that sub seems to be buffering everything.  How do I fix that?  I am using the python wrapper (I tried release and now dev from git)
| [Tuesday 14 December 2010] [14:44:08] <cremes>	brandyn: question:  is the sub unable to keep up due to processing in python? or it can't read the messages fast enough (and you are not processing them at all)?
| [Tuesday 14 December 2010] [14:45:19] <brandyn>	cremes, it can't keep up
| [Tuesday 14 December 2010] [14:45:37] <brandyn>	cremes, I would like it to drop ones that it can't process, like the HWM
| [Tuesday 14 December 2010] [14:45:45] <cremes>	brandyn: can it keep up if you drop *all* messages?
| [Tuesday 14 December 2010] [14:45:45] <brandyn>	cremes, but it seems like there isn't an option like that
| [Tuesday 14 December 2010] [14:45:56] <brandyn>	cremes, yes if I just keep recv'ing
| [Tuesday 14 December 2010] [14:45:59] <cremes>	ok
| [Tuesday 14 December 2010] [14:46:13] <brandyn>	it is from a streaming sensor
| [Tuesday 14 December 2010] [14:46:18] <brandyn>	and some devices can't handle the data
| [Tuesday 14 December 2010] [14:46:22] <brandyn>	and it is ok to get some of the packets
| [Tuesday 14 December 2010] [14:46:29] <cremes>	then you're only hope is to increase the speed of your python processor; use a faster language or throw hardware at it
| [Tuesday 14 December 2010] [14:46:39] <brandyn>	but shouldn't there be a way to leak the buffer
| [Tuesday 14 December 2010] [14:46:45] <brandyn>	like the HWM on the PUB side
| [Tuesday 14 December 2010] [14:46:58] <cremes>	no, you can't tell how many messages are queued; that information is not exposed
| [Tuesday 14 December 2010] [14:47:14] <brandyn>	sure, but it knows
| [Tuesday 14 December 2010] [14:47:23] <brandyn>	so if I said "don't queue more than X messages"
| [Tuesday 14 December 2010] [14:47:27] <cremes>	the best you could do is process 1 out of X packets and drop the rest; that logic should be easy
| [Tuesday 14 December 2010] [14:47:29] <brandyn>	then it should work, just like HWM does now
| [Tuesday 14 December 2010] [14:47:47] <brandyn>	I see, so I can just close and reopen the socket?
| [Tuesday 14 December 2010] [14:48:28] <brandyn>	that seems like a hack, if the SUB listened to the HWM, then it could just drop packets and keep the newest ones
| [Tuesday 14 December 2010] [14:48:53] <cremes>	brandyn: no, you should not close & reopen the socket
| [Tuesday 14 December 2010] [14:49:00] <brandyn>	how do you drop the packets then?
| [Tuesday 14 December 2010] [14:49:15] <brandyn>	just recv really fast? or something
| [Tuesday 14 December 2010] [14:49:17] <cremes>	i meant that your python logic should drop x-1 of x packets; e.g. don't process them, just read and toss
| [Tuesday 14 December 2010] [14:49:24] <cremes>	yes
| [Tuesday 14 December 2010] [14:49:26] <brandyn>	ah gotcha, ok yeah I guess that can work
| [Tuesday 14 December 2010] [14:49:46] <brandyn>	so what I can probably do is set to to nonblocking
| [Tuesday 14 December 2010] [14:49:49] <cremes>	if (counter MOD 10 == 0) process else drop end
| [Tuesday 14 December 2010] [14:49:57] <brandyn>	and then keep recv'ing until I get the exception
| [Tuesday 14 December 2010] [14:49:59] <brandyn>	and just use the last one
| [Tuesday 14 December 2010] [14:50:06] <cremes>	non-blocking reads/writes aren't going to help you here
| [Tuesday 14 December 2010] [14:50:22] <cremes>	a regular blocking read should be fine
| [Tuesday 14 December 2010] [14:50:24] <brandyn>	what I mean is that I just want my app to get access to the newest message
| [Tuesday 14 December 2010] [14:50:30] <brandyn>	so I can just read all of them
| [Tuesday 14 December 2010] [14:50:36] <brandyn>	which will flush the buffer
| [Tuesday 14 December 2010] [14:50:40] <brandyn>	and then use the last one
| [Tuesday 14 December 2010] [14:51:06] <brandyn>	the nonblocking would tell me when the buffer is done
| [Tuesday 14 December 2010] [14:51:09] <cremes>	sure, that's fine
| [Tuesday 14 December 2010] [14:51:16] <brandyn>	cremes, you rock man, thank you
| [Tuesday 14 December 2010] [14:51:24] <cremes>	pay it forward... :)
| [Tuesday 14 December 2010] [14:52:03] <cremes>	brandyn: are you sure setting HWM on the publisher didn't help?
| [Tuesday 14 December 2010] [14:52:18] <cremes>	when a pub socket hits HWM for a subscriber, it should drop messages
| [Tuesday 14 December 2010] [14:52:28] <cremes>	try HWM = 1 if you haven't
| [Tuesday 14 December 2010] [14:54:24] <brandyn>	yeah I did
| [Tuesday 14 December 2010] [14:54:27] <brandyn>	but the client can read them
| [Tuesday 14 December 2010] [14:54:29] <brandyn>	that's the problem
| [Tuesday 14 December 2010] [14:54:48] <brandyn>	it appears there is no similar HWM for the sub
| [Tuesday 14 December 2010] [14:54:54] <brandyn>	but that's ok
| [Tuesday 14 December 2010] [14:55:17] <brandyn>	this is good enough, basically I offload ZMQ's SUB buffer to myself, and then apply my own restrictions
| [Tuesday 14 December 2010] [14:55:36] <cremes>	i'm not sure i follow; if a sub socket has more than HWM messages in its queue then the pub socket should detect that and drop packets
| [Tuesday 14 December 2010] [14:55:42] <cremes>	but whatever...
| [Tuesday 14 December 2010] [14:55:46] <cremes>	you have a solution
| [Tuesday 14 December 2010] [14:56:44] <brandyn>	oh I see, yeah it doesn't appear to do that
| [Tuesday 14 December 2010] [14:56:57] <brandyn>	I think the HWM applies only to the queue on the PUB size
| [Tuesday 14 December 2010] [14:57:02] <brandyn>	for each SUB
| [Tuesday 14 December 2010] [14:57:24] <brandyn>	like if I don't call recv, then my buffer blows up
| [Tuesday 14 December 2010] [14:57:35] <brandyn>	so it tells me that in the background is it buffering lots of goodies for me
| [Tuesday 14 December 2010] [14:57:40] <brandyn>	and I just didn't ask for them
| [Tuesday 14 December 2010] [14:59:41] <cremes>	hmmm, that's surprising; you might want to ask on the ML for clarification with your use-case
| [Tuesday 14 December 2010] [15:00:27] <brandyn>	yeah for sure, this is just a rushed project so I need a fix. It's the first time I've used ZMQ
| [Tuesday 14 December 2010] [15:14:00] <brandyn>	cremes, ok so strange problem.  If I read the socket opt for HWM, it is zero, if I set it, I get a totally different number
| [Tuesday 14 December 2010] [15:15:02] <cremes>	0 is the default
| [Tuesday 14 December 2010] [15:15:18] <cremes>	what value are you trying to set it to? and what do you get back when you read that option again?
| [Tuesday 14 December 2010] [15:15:39] <cremes>	btw, 0 means no limit
| [Tuesday 14 December 2010] [15:15:42] <brandyn>	yeah I know that
| [Tuesday 14 December 2010] [15:16:26] <brandyn>	so I set it to 1, and got thishttp://pastebin.com/xh9dCw6C
| [Tuesday 14 December 2010] [15:16:49] <brandyn>	crazy right?
| [Tuesday 14 December 2010] [15:17:52] <cremes>	HWM takes an unsigned 64-bit integer; maybe the python bindings aren't handling that right?
| [Tuesday 14 December 2010] [15:18:43] <brandyn>	yeah I see that
| [Tuesday 14 December 2010] [15:18:48] <brandyn>	I'll fix it an put in a patch
| [Tuesday 14 December 2010] [15:19:25] <brandyn>	yeah simple fix
| [Tuesday 14 December 2010] [15:22:42] <brandyn>	so I fixed that, it now returns the correct HWM, but same semantics
| [Tuesday 14 December 2010] [15:25:19] <cremes>	cool
| [Tuesday 14 December 2010] [16:10:51] <mikko>	evening ladies and gents
| [Tuesday 14 December 2010] [16:12:32] <cremes>	evening
| [Tuesday 14 December 2010] [16:18:16] <brandyn>	anyone here a python wrapper contributor?
| [Tuesday 14 December 2010] [16:18:58] <mikko>	brandyn: MinRK and bgranger pop in occasionally
| [Tuesday 14 December 2010] [16:19:34] <brandyn>	thanks
| [Tuesday 14 December 2010] [21:51:36] <brandyn>	does the new xpub/xsub allow for PUB side filtering?
| [Tuesday 14 December 2010] [21:51:57] <brandyn>	I haven't seen any documentation on it, just a few mailing list posts
| [Tuesday 14 December 2010] [21:56:07] <Steve-o>	that is what the design is for
| [Tuesday 14 December 2010] [21:56:31] <Steve-o>	the spec is on the mailing list
| [Tuesday 14 December 2010] [22:19:12] <Steve-o>	http://www.mail-archive.com/zeromq-dev@lists.zeromq.org/msg06247.html
| [Tuesday 14 December 2010] [23:18:48] <EricL>	Is anyone around?
| [Tuesday 14 December 2010] [23:20:42] <Steve-o>	all sleeping
| [Tuesday 14 December 2010] [23:21:24] <EricL>	I am trying to figure out what the best approach for my setup is to use 0MQ
| [Tuesday 14 December 2010] [23:22:39] <Steve-o>	to do what?
| [Tuesday 14 December 2010] [23:22:52] <EricL>	I have a log server and a few clients that are pushing a lot of data to the server.  I think I want something similar to pub/sub that is a queue on the client.
| [Tuesday 14 December 2010] [23:23:12] <EricL>	This way any one of multiple log servers can grab a line from the client and it pops off the queue.
| [Tuesday 14 December 2010] [23:24:43] <EricL>	from any client rather.
| [Tuesday 14 December 2010] [23:25:03] <Steve-o>	as in polling the logger
| [Tuesday 14 December 2010] [23:25:47] <EricL>	Kind of.  The way the logging happens is that there is a Ruby Resque job that does a few things and dumps the output to a log.
| [Tuesday 14 December 2010] [23:26:11] <Steve-o>	so, REQ/REP sockets then
| [Tuesday 14 December 2010] [23:26:51] <Steve-o>	it's not ideal to have the chatter back and forth though
| [Tuesday 14 December 2010] [23:27:44] <Steve-o>	you end up slowing the communication down to the RTT
| [Tuesday 14 December 2010] [23:28:28] <EricL>	That's what I am curious about.
| [Tuesday 14 December 2010] [23:30:10] <Steve-o>	which is why PUB is preferred, 
| [Tuesday 14 December 2010] [23:30:36] <Steve-o>	so what do you not like about PUB/SUB implementation?
| [Tuesday 14 December 2010] [23:31:03] <EricL>	Because then multiple log servers will be receiving the same msgs, no?
| [Tuesday 14 December 2010] [23:32:15] <Steve-o>	you can use different topics for each server
| [Tuesday 14 December 2010] [23:33:48] <EricL>	Log server?
| [Tuesday 14 December 2010] [23:34:05] <Steve-o>	yes, or only have the client connect to one log server
| [Tuesday 14 December 2010] [23:34:24] <Steve-o>	you can partition by connection or topic/subject
| [Tuesday 14 December 2010] [23:35:06] <EricL>	The problem there is that there is more data coming from the client than can be written to disk (on a MB/s basis)
| [Tuesday 14 December 2010] [23:36:13] <EricL>	That's why I am interested in something like 0MQ.  I just am not sure how to segment the write load across multiple servers.
| [Tuesday 14 December 2010] [23:36:15] <Steve-o>	so the messages will queue up on the log clients
| [Tuesday 14 December 2010] [23:36:40] <Steve-o>	you will probably want to use the zmq_swap function to spool onto disk too
| [Tuesday 14 December 2010] [23:38:43] <Steve-o>	log client: send messages as soon as available, zmq queues up messages if log server is congested receiving
| [Tuesday 14 December 2010] [23:38:44] <EricL>	That won't solve the issue since it's constantly going to be backing up.
| [Tuesday 14 December 2010] [23:39:21] <brandyn>	any know the state of pub side filtering?
| [Tuesday 14 December 2010] [23:40:24] <Steve-o>	EricL:  zmq is managing the queue and congestion for you, so it sounds ideal
| [Tuesday 14 December 2010] [23:40:26] <brandyn>	that is a really essential feature for my application and I have to emulate it now
| [Tuesday 14 December 2010] [23:40:46] <Steve-o>	brandyn:  have you checked the source in git/master?  
| [Tuesday 14 December 2010] [23:41:58] <brandyn>	Steve-o, yeah I got it this morning but it looks to be a copy of pub/sub (the XPUB/SUB that is)
| [Tuesday 14 December 2010] [23:42:28] <EricL>	It's only ideal if I can avoid duplication of msg logging on the server side.
| [Tuesday 14 December 2010] [23:43:13] <Steve-o>	duplication?  As in re-transmits?
| [Tuesday 14 December 2010] [23:43:15] <brandyn>	https://github.com/zeromq/zeromq2/commit/c80e7b80cc726ca7c29493c2553c8d19792bb6e5
| [Tuesday 14 December 2010] [23:44:31] <EricL>	duplication meaning that if I have more than 1 logserver and 3 clients pushing out msgs, I don't care which logserver the msgs go to as long as there are not any duplicate msgs.
| [Tuesday 14 December 2010] [23:44:42] <Steve-o>	brandyn:  I guess you have to ask Gerard Toonstra, he was submitting the patches and RFC
| [Tuesday 14 December 2010] [23:44:48] <EricL>	(from logserver to logserver)
| [Tuesday 14 December 2010] [23:45:41] <Steve-o>	EricL: so you also have a question of which logserver is being targetted
| [Tuesday 14 December 2010] [23:47:06] <EricL>	I don't care which logserver is being targeted as long as it gets there.
| [Tuesday 14 December 2010] [23:52:14] <Steve-o>	k, the link for loggly's notes has disappeared, http://www.zeromq.org/blog:loggy-switches-to-0mq
| [Tuesday 14 December 2010] [23:52:32] <EricL>	Looking.
| [Tuesday 14 December 2010] [23:55:38] <EricL>	Yea, that doesn't tell much.
| [Tuesday 14 December 2010] [23:57:32] <Steve-o>	maybe PUSH/PULL sockets, implements load sharing, not sure about guarantees on one only delivery
| [Wednesday 15 December 2010] [00:06:36] <EricL>	Hmm...I guess I am not sure of the best approach in general.
| [Wednesday 15 December 2010] [00:08:55] <EricL>	So you think I should setup a PUSH socket on the client and then write everything from the Resque processes to that socket (which will then do the buffering).
| [Wednesday 15 December 2010] [00:10:40] <EricL>	Then on the server(s), I should do a PULL and hope that I am not receiving duplicates.
| [Wednesday 15 December 2010] [00:13:25] <Steve-o>	yes, although I'd check with the devs on the mailing list about duplicate delivery
| [Wednesday 15 December 2010] [00:15:13] <Steve-o>	otherwise you need req/rep and you suffer RTT time
| [Wednesday 15 December 2010] [00:20:52] <EricL>	Alright.  I think I have some reading to do in order to understand how to implement all this.
| [Wednesday 15 December 2010] [00:21:27] <Steve-o>	the main devs should be online in a few hours time
| [Wednesday 15 December 2010] [00:21:43] <EricL>	They in EST?
| [Wednesday 15 December 2010] [00:22:30] <Steve-o>	MET I think
| [Wednesday 15 December 2010] [00:22:48] <Steve-o>	I only look after PGM stuff, all my middleware knowledge is TIBCO stuff
| [Wednesday 15 December 2010] [00:23:06] <EricL>	Gotchya.
| [Wednesday 15 December 2010] [00:25:42] <Steve-o>	In TIBCO you would use a Rendezvous Distributed Queue (RVDQ), but the implementation is very layered and not as efficient as 0MQ
| [Wednesday 15 December 2010] [00:28:20] <EricL>	I think I need the efficiency of 0MQ because of the amount of data I am dealing with.
| [Wednesday 15 December 2010] [02:01:43] <EricL>	Steve-o: Thanks.
| [Wednesday 15 December 2010] [06:09:20] <gb_>	hello
| [Wednesday 15 December 2010] [06:22:02] <sustrik>	hello
| [Wednesday 15 December 2010] [06:26:02] <mikko>	hi
| [Wednesday 15 December 2010] [06:35:39] <sustrik>	finally i'm getting to your patch
| [Wednesday 15 December 2010] [06:35:43] <sustrik>	sorry for the delay
| [Wednesday 15 December 2010] [06:35:52] <mikko>	i'm patching jmeter at the moment
| [Wednesday 15 December 2010] [06:36:05] <mikko>	only works master-slave if it's in the same network / no firewalls
| [Wednesday 15 December 2010] [07:04:33] <mikko>	sustrik: it seems that swap_t::full() was maybe an old implementation from where
| [Wednesday 15 December 2010] [07:04:46] <mikko>	sustrik: it seems unlikely that buffer_space () == 1 in any case
| [Wednesday 15 December 2010] [07:06:51] <sustrik>	mikko: the swap isn't my code
| [Wednesday 15 December 2010] [07:06:58] <sustrik>	i'm trying to make sense of it
| [Wednesday 15 December 2010] [07:07:35] <mikko>	the problem is was hitting was that swap was not full but there wasn't enough space for the given message
| [Wednesday 15 December 2010] [07:07:45] <mikko>	hence swap_t::fits(..
| [Wednesday 15 December 2010] [07:11:03] <Steve-o>	why does swap_t call GetCurrentThreadId on Windows but getpid on POSIX?  brain fart.
| [Wednesday 15 December 2010] [07:12:42] <sustrik>	it just need some unique number
| [Wednesday 15 December 2010] [07:13:01] <sustrik>	i think the code was written before 0mq was linked with libuuid
| [Wednesday 15 December 2010] [07:13:24] <Steve-o>	but not both thread id or process id, one of each
| [Wednesday 15 December 2010] [07:15:28] <Steve-o>	meh, also how many people use octets as a counter?  old people :P
| [Wednesday 15 December 2010] [07:21:20] <sustrik>	well, it's always one of them afaics
| [Wednesday 15 December 2010] [07:21:29] <sustrik>	tid on windows
| [Wednesday 15 December 2010] [07:21:33] <sustrik>	pid on posix
| [Wednesday 15 December 2010] [07:21:54] <sustrik>	but, presumably, uuid would be better
| [Wednesday 15 December 2010] [08:05:03] <sustrik>	mikko: still there?
| [Wednesday 15 December 2010] [08:29:13] <mikko>	yes
| [Wednesday 15 December 2010] [08:32:42] <sustrik>	mikko: i've sent a modified swap patch
| [Wednesday 15 December 2010] [08:32:56] <sustrik>	basically i've just removed some dead code
| [Wednesday 15 December 2010] [08:33:07] <mikko>	sustrik: you still have the implementation of full there
| [Wednesday 15 December 2010] [08:33:16] <sustrik>	oh my
| [Wednesday 15 December 2010] [08:33:17] <mikko>	no you dont
| [Wednesday 15 December 2010] [08:33:22] <mikko>	misread the patch
| [Wednesday 15 December 2010] [08:33:23] <sustrik>	it's commented out
| [Wednesday 15 December 2010] [08:33:40] <mikko>	yes, looks good to me. i can test it after i get a haircut
| [Wednesday 15 December 2010] [08:33:46] <sustrik>	goodo
| [Wednesday 15 December 2010] [08:33:50] <sustrik>	just ping me then
| [Wednesday 15 December 2010] [08:33:53] <sustrik>	and i'll apply it
| [Wednesday 15 December 2010] [08:34:37] <mikko>	i'll give you ping
| [Wednesday 15 December 2010] [08:34:42] <mikko>	i added freebsd 8.1 to build cluster
| [Wednesday 15 December 2010] [08:34:48] <mikko>	linux, solaris, win, freebsd now
| [Wednesday 15 December 2010] [08:36:02] <sustrik>	it's getting pretty complete :)
| [Wednesday 15 December 2010] [08:36:33] <mikko>	Bad file descriptor
| [Wednesday 15 December 2010] [08:36:33] <mikko>	nbytes != -1 (tcp_socket.cpp:197)
| [Wednesday 15 December 2010] [08:36:33] <mikko>	Abort trap (core dumped)
| [Wednesday 15 December 2010] [08:36:47] <mikko>	shutdown_stress on freebsd 8.1
| [Wednesday 15 December 2010] [08:41:30] <CIA-20>	zeromq2: 03Mikko Koppanen 07master * ra46980b 10/ (4 files in 4 dirs): 
| [Wednesday 15 December 2010] [08:41:30] <CIA-20>	zeromq2: Remove assertions from devices
| [Wednesday 15 December 2010] [08:41:30] <CIA-20>	zeromq2: Signed-off-by: Mikko Koppanen <mkoppanen@php.net> - http://bit.ly/e4ZWpR
| [Wednesday 15 December 2010] [08:42:23] <sustrik>	mikko: that's presumably the bug dhammika fixed
| [Wednesday 15 December 2010] [08:42:40] <sustrik>	i still have to look at the one you've reported yesterday
| [Wednesday 15 December 2010] [09:58:43] <mikko>	sustrik: you mean the HWM one?
| [Wednesday 15 December 2010] [10:00:05] <sustrik>	mikko: https://gist.github.com/848e949008e67ca542f7
| [Wednesday 15 December 2010] [10:07:14] <Guthur>	sustrik: I just noticed that clrzmq2 issue there now
| [Wednesday 15 December 2010] [10:07:19] <Guthur>	I've replied
| [Wednesday 15 December 2010] [10:07:35] <sustrik>	Guthur: good
| [Wednesday 15 December 2010] [10:07:46] <Guthur>	all I can say is... at least he finally got it built
| [Wednesday 15 December 2010] [10:08:21] <sustrik>	problem with clrzmq or problem with the user?
| [Wednesday 15 December 2010] [10:08:35] <Guthur>	user 
| [Wednesday 15 December 2010] [10:08:39] <sustrik>	:)
| [Wednesday 15 December 2010] [10:08:59] <Guthur>	He's wondering why passing in a String encoding object only returns strings
| [Wednesday 15 December 2010] [10:09:12] <Guthur>	he wanted binary
| [Wednesday 15 December 2010] [10:09:30] <Guthur>	which is the standard method, returning a byte array
| [Wednesday 15 December 2010] [10:10:00] <Guthur>	I need to check the comments again, I'm sure I was pretty explicit
| [Wednesday 15 December 2010] [10:10:34] <sustrik>	depends on the user
| [Wednesday 15 December 2010] [10:10:59] <sustrik>	however simply you explain, there's still someone who's not going to understand
| [Wednesday 15 December 2010] [10:11:03] <Guthur>	hehe comment -> Listen for message, and return it in string format
| [Wednesday 15 December 2010] [10:12:07] <Guthur>	actually to be fair there could be some improvement in the comment for the method he wanted
| [Wednesday 15 December 2010] [10:12:17] <Guthur>	I'll look into updating later
| [Wednesday 15 December 2010] [10:15:00] <sustrik>	Guthur: there have been something else wrt clrzmq discussed on the ML
| [Saturday 18 December 2010] [16:32:02] <mikko>	sustrik: no more race condition failures
| [Saturday 18 December 2010] [16:33:52] <mikko>	in the daily builds
| [Saturday 18 December 2010] [21:15:14] <raydeo>	is it possible that libcurl is interfering with zeromq? I have a system that uses 3 IPC sockets that runs very smoothly but when I turn on network uploading via libcurl I get bizarre behavior like dropped messages.
| [Saturday 18 December 2010] [22:01:22] <raydeo>	is there a reliable way to ensure that zmq is closing properly? I'm discovering that if a process dies without cleaning up it brings the whole system down.
| [Sunday 19 December 2010] [02:59:38] <mikko>	raydeo: is your libcurl thingia running in a thread?
| [Sunday 19 December 2010] [02:59:54] <mikko>	raydeo: just wondering because it would most likely block (?)
| [Sunday 19 December 2010] [12:17:42] <mikko>	good evening
| [Sunday 19 December 2010] [16:39:37] <mikko>	sustrik: found a segfault
| [Sunday 19 December 2010] [22:28:02] <davidstrauss>	I'm trying to figure out why my first attempt at a C++ echo/client implementation isn't exchanging any messages.
| [Sunday 19 December 2010] [22:28:32] <davidstrauss>	http://pastie.org/1390975
| [Sunday 19 December 2010] [22:28:51] <davidstrauss>	(the code is pastied)
| [Sunday 19 December 2010] [22:35:57] <Steve-o>	isn't rep supposed to bind?
| [Sunday 19 December 2010] [22:36:39] <davidstrauss>	Steve-o, I've tried that
| [Sunday 19 December 2010] [22:36:57] <davidstrauss>	Steve-o, Converting the connect to a bind on the echo.cpp doesn't make it work
| [Sunday 19 December 2010] [22:37:11] <Steve-o>	k
| [Sunday 19 December 2010] [22:37:15] <davidstrauss>	Steve-o, I have nearly identical code in Python working
| [Sunday 19 December 2010] [22:37:58] <Steve-o>	aha, nice
| [Sunday 19 December 2010] [22:38:04] <davidstrauss>	Steve-o, The echo.cpp version starts and then just waits forever for a message
| [Sunday 19 December 2010] [22:38:18] <davidstrauss>	Steve-o, And the client.cpp code "sends" a message without error.
| [Sunday 19 December 2010] [22:38:28] <davidstrauss>	Steve-o, But echo.cpp doesn't seem to get it
| [Sunday 19 December 2010] [22:39:03] <davidstrauss>	Steve-o, If I can get this working, I would happily publish this as a public example
| [Sunday 19 December 2010] [22:39:14] <Steve-o>	local_lat uses REP sockets
| [Sunday 19 December 2010] [22:39:26] <davidstrauss>	Steve-o, local_lat?
| [Sunday 19 December 2010] [22:39:37] <Steve-o>	latency performance test tool
| [Sunday 19 December 2010] [22:40:02] <Steve-o>	>> https://github.com/zeromq/zeromq2/blob/master/perf/local_lat.cpp
| [Sunday 19 December 2010] [22:40:44] <Steve-o>	with remote_lat being the REQ client
| [Sunday 19 December 2010] [22:41:21] <davidstrauss>	Steve-o, Unfortunately, that uses the C API, even though the code is C++
| [Sunday 19 December 2010] [22:43:01] <Steve-o>	the bind on the REQ socket should be something like tcp://eth0:5555
| [Sunday 19 December 2010] [22:43:29] <davidstrauss>	Steve-o, I need to bind on the REQ socket? Not just connect?
| [Sunday 19 December 2010] [22:44:07] <Steve-o>	bind only
| [Sunday 19 December 2010] [22:44:27] <Steve-o>	actually forget the eth0 thing, according to http://api.zeromq.org/zmq_tcp.html using the IP address should work too
| [Sunday 19 December 2010] [22:44:37] <davidstrauss>	Steve-o, All the demos I see have the ZMQ_REP server bind and the ZMQ_REQ connect
| [Sunday 19 December 2010] [22:44:49] <Steve-o>	change line 11 to socket.bind("tcp://127.0.0.1:5000");
| [Sunday 19 December 2010] [22:45:07] <Steve-o>	sorry, getting confused
| [Sunday 19 December 2010] [22:45:09] <davidstrauss>	Steve-o, I can't have the server and client both bind
| [Sunday 19 December 2010] [22:45:22] <Steve-o>	REQ should connect only, REP should bind only, right?
| [Sunday 19 December 2010] [22:45:43] <davidstrauss>	Steve-o, That's the impression i'm under, and it's not working for me.
| [Sunday 19 December 2010] [22:45:51] <davidstrauss>	Steve-o, Nor is it giving any errors.
| [Sunday 19 December 2010] [22:47:34] <Steve-o>	mmm, don't you have to do a bit more work in the echo.cpp loop
| [Sunday 19 December 2010] [22:47:49] <Steve-o>	it looks like you are re-using one message object all the time
| [Sunday 19 December 2010] [22:47:49] <davidstrauss>	Steve-o, How so?
| [Sunday 19 December 2010] [22:48:05] <davidstrauss>	Steve-o, Even reusing the same message object should work at least once
| [Sunday 19 December 2010] [22:48:19] <Steve-o>	yes, I would think so
| [Sunday 19 December 2010] [22:48:32] <davidstrauss>	Steve-o, The code never reaches "cout << "Message: " << (char *) message.data() << endl;"
| [Sunday 19 December 2010] [22:48:58] <Steve-o>	stuck in recv?
| [Sunday 19 December 2010] [22:49:12] <davidstrauss>	Steve-o, yes, blocking on getting a message
| [Sunday 19 December 2010] [22:49:44] <davidstrauss>	Steve-o, I just see "Waiting on message" when I run it
| [Sunday 19 December 2010] [22:51:54] <Steve-o>	but Python version is working?
| [Sunday 19 December 2010] [22:52:03] <davidstrauss>	Steve-o, yes
| [Sunday 19 December 2010] [22:52:41] <davidstrauss>	Steve-o, http://pastie.org/1391002
| [Sunday 19 December 2010] [22:53:37] <Steve-o>	try adding a socket.recv() in the client.cpp
| [Sunday 19 December 2010] [22:53:49] <Steve-o>	I'm guessing the client is terminating too quickly
| [Sunday 19 December 2010] [22:54:35] <davidstrauss>	Steve-o, woo hoo
| [Sunday 19 December 2010] [22:55:03] <davidstrauss>	Steve-o, the works!
| [Sunday 19 December 2010] [22:55:06] <davidstrauss>	that*
| [Sunday 19 December 2010] [22:55:18] <Steve-o>	which version of 0mq is this?
| [Sunday 19 December 2010] [22:56:27] <davidstrauss>	Steve-o, 2.0.10
| [Sunday 19 December 2010] [22:56:49] <Steve-o>	ok 2.1.0 will wait for you in zmq_term
| [Sunday 19 December 2010] [22:56:59] <Steve-o>	2.0 will exit out early
| [Sunday 19 December 2010] [22:57:01] <davidstrauss>	Steve-o, i see
| [Sunday 19 December 2010] [22:57:11] <Steve-o>	ZMQ_LINGER option
| [Sunday 19 December 2010] [22:57:38] <Steve-o>	otherwise you need to sleep or some other hack
| [Sunday 19 December 2010] [22:57:51] <davidstrauss>	Steve-o, honestly, it's kind of silly to use REP/REQ without the client waiting on the reply
| [Sunday 19 December 2010] [22:58:01] <davidstrauss>	Steve-o, I was just trying to get things working
| [Sunday 19 December 2010] [22:58:26] <Steve-o>	it also affects other sockets, like trying to PUB on message and quit
| [Sunday 19 December 2010] [22:58:53] <Steve-o>	which makes command line utilities a bit useless
| [Sunday 19 December 2010] [23:01:52] <Steve-o>	REQ/REP limits you on speed to RTT, you need other socket types for faster performance
| [Sunday 19 December 2010] [23:04:33] <davidstrauss>	Steve-o, to RTT?
| [Sunday 19 December 2010] [23:04:44] <Steve-o>	round-trip-time on the LAN/MAN/WAN
| [Sunday 19 December 2010] [23:05:41] <Steve-o>	0mq excels when you can batch up messages
| [Sunday 19 December 2010] [23:06:47] <Steve-o>	depends on application architecture and requirements
| [Sunday 19 December 2010] [23:07:05] <Steve-o>	whether you wish to allow several outstanding requests for example
| [Sunday 19 December 2010] [23:18:10] <davidstrauss>	Steve-o, Cool. So, I have PHP, Python, and C++ interoperating on the REQ/REP pattern. I'll try to clean up the code and publish it.
| [Sunday 19 December 2010] [23:19:10] <davidstrauss>	Steve-o, thanks for your help
| [Sunday 19 December 2010] [23:26:34] <Steve-o>	np
| [Sunday 19 December 2010] [23:28:35] <davidstrauss>	Is there any good comparison between using Thrift's built-in RPC support vs. using ZeroMQ?
| [Sunday 19 December 2010] [23:32:30] <Steve-o>	I've seen it come up, but nothing detailed apart from discussing it
| [Sunday 19 December 2010] [23:35:30] <Steve-o>	I think there was a protobuf vs thrift as message format above zeromq
| [Sunday 19 December 2010] [23:35:41] <Steve-o>	nothing on the actual RPC implementation
| [Sunday 19 December 2010] [23:36:13] <Steve-o>	lol, thrift over 0mq:  http://www.mail-archive.com/thrift-dev@incubator.apache.org/msg08473.html
| [Sunday 19 December 2010] [23:36:41] <davidstrauss>	Steve-o, Well, it is necessary to pick *some* sort of format for messages.
| [Sunday 19 December 2010] [23:37:00] <davidstrauss>	Steve-o, I'm looking at pure Thrift vs. Thrift serialization + ZeroMQ
| [Sunday 19 December 2010] [23:37:49] <Steve-o>	ok, I like protobufs as it is easy to roll
| [Sunday 19 December 2010] [23:38:12] <Steve-o>	still a bit backward compared with TIBCO quick forms though
| [Sunday 19 December 2010] [23:38:36] <davidstrauss>	Steve-o, Yeah, but I'm working with primarily PHP clients, and Protobufs only have experimental PHP support with no accelerated serialization
| [Sunday 19 December 2010] [23:39:33] <Steve-o>	ok
| [Sunday 19 December 2010] [23:40:01] <Steve-o>	You also have JSON and derivatives to pick from then
| [Sunday 19 December 2010] [23:40:39] <davidstrauss>	Steve-o, JSON isn't great for C++ servers, nor is it a terribly efficient format :-/
| [Sunday 19 December 2010] [23:41:39] <Steve-o>	but it's easy for PHP, JavaScript, and humans to read :D
| [Sunday 19 December 2010] [23:41:56] <Steve-o>	and there are libraries for it everywhere
| [Sunday 19 December 2010] [23:42:04] <davidstrauss>	Steve-o, agreed
| [Sunday 19 December 2010] [23:42:19] <Steve-o>	it's less cumbersome than XDR anyhow
| [Sunday 19 December 2010] [23:44:00] <Steve-o>	you could roll your own PHP extension with fixed scope,
| [Sunday 19 December 2010] [23:48:47] <Steve-o>	Google lacks dynamic forms, everything is static compiled
| [Monday 20 December 2010] [03:16:36] <sustrik>	hi mikko: what segfault?
| [Monday 20 December 2010] [05:22:49] <mikko>	sustrik: https://gist.github.com/17fb87b54e83832354b5
| [Monday 20 December 2010] [05:24:39] <sustrik>	mikko: looks like a deallocation of invalid message
| [Monday 20 December 2010] [05:24:56] <sustrik>	do you have a test program?
| [Monday 20 December 2010] [05:25:07] <mikko>	the way i reproduce is by creating a rep socket
| [Monday 20 December 2010] [05:25:11] <mikko>	then telnet in
| [Monday 20 December 2010] [05:25:19] <mikko>	press ctrl+c in telnet 
| [Monday 20 December 2010] [05:25:22] <mikko>	and enter twice
| [Monday 20 December 2010] [05:25:33] <sustrik>	sorry, what's enter twice?
| [Monday 20 December 2010] [05:25:46] <mikko>	 
| [Monday 20 December 2010] [05:25:47] <mikko>	 
| [Monday 20 December 2010] [05:25:54] <sustrik>	in telnet?
| [Monday 20 December 2010] [05:25:57] <mikko>	yes
| [Monday 20 December 2010] [05:26:11] <sustrik>	let me try...
| [Monday 20 December 2010] [05:26:11] <mikko>	i've been too lazy to check the exact bytes that combo sends :)
| [Monday 20 December 2010] [05:26:20] <sustrik>	doesn't matter
| [Monday 20 December 2010] [05:27:16] <sustrik>	reproduced
| [Monday 20 December 2010] [05:27:18] <sustrik>	thanks!
| [Monday 20 December 2010] [05:30:43] <mikko>	np
| [Monday 20 December 2010] [05:31:47] <mikko>	https://gist.github.com/21ee1c85b1b2f6cbba66
| [Monday 20 December 2010] [05:31:54] <mikko>	that's from my gdb session last night
| [Monday 20 December 2010] [05:47:52] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r112d0cd 10/ src/decoder.cpp : 
| [Monday 20 December 2010] [05:47:52] <CIA-21>	zeromq2: Fix the segfault when over-sized message is rejected.
| [Monday 20 December 2010] [05:47:52] <CIA-21>	zeromq2: The in_progress message inside of decoder was left
| [Monday 20 December 2010] [05:47:52] <CIA-21>	zeromq2: uninitialised in such a case.
| [Monday 20 December 2010] [05:47:52] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/grKk2b
| [Monday 20 December 2010] [05:53:09] <mikko>	sustrik: gj, that was quick
| [Monday 20 December 2010] [06:12:00] <sustrik>	:)
| [Monday 20 December 2010] [07:05:46] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r51d2d9b 10/ src/decoder.cpp : 
| [Monday 20 December 2010] [07:05:46] <CIA-21>	zeromq2: Yet one more fix for oversized messages.
| [Monday 20 December 2010] [07:05:46] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/ez2JYr
| [Monday 20 December 2010] [13:41:56] <myraft_>	mikko - I haven't been back here for a while. Quick update - got past the initial Java HelloWorld queue setup. The problem was the way I was running the Java code on Ubuntu.
| [Monday 20 December 2010] [13:42:05] <myraft_>	Thanks for the help the other day.
| [Monday 20 December 2010] [13:44:51] <mikko>	no problem
| [Monday 20 December 2010] [13:45:01] <mikko>	what is the problem of running java code on ubuntu?
| [Monday 20 December 2010] [14:01:58] <myraft_>	mikko - the guide explicitly states to calls to run it with -Djava.library.path="/usr/local/lib". I did sudo ldconfig , which in theory should have loaded it and be avaiable for any program to use (at least that was my impression). Once I set that as VM Argument - everythigng started working.
| [Monday 20 December 2010] [14:09:58] <mikko>	nice!
| [Monday 20 December 2010] [14:10:05] <mikko>	so the error message was correct after all
| [Monday 20 December 2010] [14:10:34] <mikko>	good to know, now we know what to tell the next guy asking
| [Monday 20 December 2010] [14:25:09] <dv_>	woot
| [Monday 20 December 2010] [14:25:19] <dv_>	i can now send asynchronous function calls through zeromq
| [Monday 20 December 2010] [14:32:41] <mikko>	dv_: cool!
| [Monday 20 December 2010] [14:32:52] <mikko>	dv_: what language are you working in?
| [Monday 20 December 2010] [14:32:55] <dv_>	its not rpc, mind you
| [Monday 20 December 2010] [14:33:05] <dv_>	more like boost signals/libsigc++/qt signals
| [Monday 20 December 2010] [14:33:14] <dv_>	mikko, right now its for c++ and ruby
| [Monday 20 December 2010] [14:33:32] <dv_>	i plan on adding support for more languages. especially javascript through websockets
| [Monday 20 December 2010] [14:33:32] <mikko>	im doing something similar in my current project
| [Monday 20 December 2010] [14:33:40] <mikko>	i got "intercomm" for communicating between threads
| [Monday 20 December 2010] [14:33:47] <mikko>	sending shutdown messages etc
| [Monday 20 December 2010] [14:33:50] <dv_>	on one side, i do send_call("foobar", params); 
| [Monday 20 December 2010] [14:33:57] <dv_>	on the other side, i previously registered a "foobar" callback
| [Monday 20 December 2010] [14:34:03] <mikko>	nice
| [Monday 20 December 2010] [14:34:14] <dv_>	and it transmits the params etc. through the wire
| [Monday 20 December 2010] [14:34:21] <dv_>	the c++ side uses a lot of metaprogramming fu :)
| [Monday 20 December 2010] [14:34:29] <mikko>	nice, nice
| [Monday 20 December 2010] [14:35:13] <dv_>	do you send more complex types, such as arrays?
| [Monday 20 December 2010] [14:35:31] <mikko>	no, my use-case is very simple
| [Monday 20 December 2010] [14:35:32] <dv_>	i want to limit things, that is, primitive types, and maybe binary buffers
| [Monday 20 December 2010] [14:35:39] <mikko>	just sending ints
| [Monday 20 December 2010] [14:35:57] <dv_>	but more heavyweight transmissions need their dedicated channel anyway in my opinion
| [Monday 20 December 2010] [14:36:16] <mikko>	im sending enums like HTTPD_SHUTDOWN, SEND_STATS etc
| [Monday 20 December 2010] [14:36:20] <mikko>	fairly simple
| [Monday 20 December 2010] [14:36:41] <dv_>	yeah, usually this kind of communication makes up the majority of it all
| [Monday 20 December 2010] [14:36:57] <mikko>	i got a libevent based httpd that pushes data down to 0MQ, which is consumed by classifier nodes and then aggregated from classifiers in aggregator nodes
| [Monday 20 December 2010] [14:37:07] <mikko>	in=in to
| [Monday 20 December 2010] [14:40:43] <dv_>	btw. in case you do something with epgm,
| [Monday 20 December 2010] [14:40:55] <dv_>	try using your IP address instead of the NIC name
| [Monday 20 December 2010] [14:41:38] <dv_>	sometimes openpgm seems to have problems with the nic's name, this issue was discussed a bit in the mailing list a while ago
| [Monday 20 December 2010] [20:25:15] <falconair>	hi all, a few newbie questions: can zeromq api be used to do raw tcp/ip programming?
| [Monday 20 December 2010] [21:21:08] <xpromache1>	hello guys, I'm considering zmq for replacing corba in an application
| [Monday 20 December 2010] [21:21:25] <xpromache1>	the typical rpc stuff I think I know how to implement
| [Monday 20 December 2010] [21:22:00] <xpromache1>	but at some point a client can send a request to the server that will have to send some large amounts of data back to the clinet
| [Monday 20 December 2010] [21:22:13] <xpromache1>	how is this best done?
| [Monday 20 December 2010] [21:22:47] <xpromache1>	I guess I need to answer the request with "OK, here it comes", and then to open another socket for pushing the data?
| [Monday 20 December 2010] [21:22:55] <xpromache1>	what sort of socket?
| [Monday 20 December 2010] [23:53:37] <cremes>	falconair: no
| [Monday 20 December 2010] [23:53:54] <cremes>	it's a higher level api than that with a few abstractions
| [Monday 20 December 2010] [23:54:02] <cremes>	make sure to read the guide linked off of the main page
| [Monday 20 December 2010] [23:54:34] <cremes>	xpromache1: open a socket for each kind of messaging pattern you plan to use
| [Monday 20 December 2010] [23:54:59] <cremes>	if you are waiting for a request/reply to start a large data download, use the REQ/REP sockets for that purpose
| [Monday 20 December 2010] [23:55:21] <cremes>	for the big data download, consider PUB/SUB or PUSH/PULL depending on what you need
| [Monday 20 December 2010] [23:55:36] <cremes>	you may even want to look at PAIR; it really depends on your app requirement
| [Monday 20 December 2010] [23:56:03] <cremes>	make sure to read the guide linked off of the main page; it may help you pick the right pattern and its associated sockets
| [Monday 20 December 2010] [23:56:40] <xpromache1>	ok, thanks for the answer
| [Monday 20 December 2010] [23:56:51] <xpromache1>	is there a way to use all these over a limited number of ports
| [Monday 20 December 2010] [23:57:00] <xpromache1>	like one for req/rep
| [Monday 20 December 2010] [23:57:08] <xpromache1>	and another one for the data tansfer
| [Tuesday 21 December 2010] [00:00:39] <cremes>	absolutely; each socket should get its own transport (tcp/pgm/ipc/inproc) and port (not necessary for transports other than tcp)
| [Tuesday 21 December 2010] [00:01:20] <cremes>	0mq doesn't use "random" ports; you specifically connect or bind to whatever you need
| [Tuesday 21 December 2010] [00:02:33] <xpromache1>	yes but I want to use the same port for all clients
| [Tuesday 21 December 2010] [00:02:40] <xpromache1>	or maybe this doesn't make sense
| [Tuesday 21 December 2010] [00:02:59] <xpromache1>	I mean it only makes sense when there is some firewalls in between
| [Tuesday 21 December 2010] [00:03:14] <xpromache1>	but this is not the use case where zeromq should be used, right?
| [Tuesday 21 December 2010] [00:03:57] <cremes>	xpromache1: not really sure what you are trying to d
| [Tuesday 21 December 2010] [00:04:13] <cremes>	if you have a complex use-case, you may consider posting it to the ML for comment
| [Tuesday 21 December 2010] [00:04:58] <xpromache1>	not really complex
| [Tuesday 21 December 2010] [00:05:06] <xpromache1>	it's like a database driver
| [Tuesday 21 December 2010] [00:05:16] <xpromache1>	you execute some small queries from time to time
| [Tuesday 21 December 2010] [00:05:27] <xpromache1>	but ocasionally you want to retrieve a lot of data
| [Tuesday 21 December 2010] [00:05:37] <xpromache1>	and I prefer not to have a request for each row
| [Tuesday 21 December 2010] [00:07:36] <cremes>	then you would probably use the pattern i suggested above; REQ/REP for the query, PUB/SUB for the data transmission
| [Tuesday 21 December 2010] [00:08:04] <cremes>	but if thisis over tcp,then the reqp/rep would get its own port as would the pub/sub
| [Tuesday 21 December 2010] [00:08:14] <cremes>	they cannot share the same port simultaneously
| [Tuesday 21 December 2010] [00:08:41] <xpromache1>	so if I have 10 clients connected simultaneously, how many ports do I need?
| [Tuesday 21 December 2010] [00:09:14] <cremes>	2, one for the req/rep and 1 for the pub/sub
| [Tuesday 21 December 2010] [00:10:02] <xpromache1>	but then all the clients will get all the data even from the requests of the other clients?
| [Tuesday 21 December 2010] [00:10:34] <cremes>	they could ignore it if the published topic is not something they are interested in; altnerately, use the XREQ/XREP socket types
| [Tuesday 21 December 2010] [00:10:38] <cremes>	have you read the guide yet?
| [Tuesday 21 December 2010] [00:11:22] <xpromache1>	I did partly but this is not clear to me
| [Tuesday 21 December 2010] [00:11:32] <xpromache1>	exactly what you can multiplex on a server socket
| [Tuesday 21 December 2010] [00:12:22] <cremes>	i may not be able to clarify it completely for you :)
| [Tuesday 21 December 2010] [00:12:51] <cremes>	a 0mq socket is a smart socket; it can connect/bind to multiple endpoints simultaneously
| [Tuesday 21 December 2010] [00:13:13] <cremes>	so in your situation the server would likely bind a REP or XREP socket
| [Tuesday 21 December 2010] [00:13:36] <xpromache1>	yes, that's clear for the response reply pattern
| [Tuesday 21 December 2010] [00:13:38] <cremes>	the clients would come in with REQ (or XREQ) sockets via  "connect" call; 0mq handles the multiplexing for you
| [Tuesday 21 December 2010] [00:13:48] <xpromache1>	what is not clear is for the data transfer
| [Tuesday 21 December 2010] [00:14:07] <cremes>	well, i suggested pub/sub but maybe that's not appropriate
| [Tuesday 21 December 2010] [00:14:16] <xpromache1>	so a client connects and sends a request for the data
| [Tuesday 21 December 2010] [00:14:18] <cremes>	you could use the xreq/xrep sockets for the data transfer
| [Tuesday 21 December 2010] [00:14:27] <cremes>	go on
| [Tuesday 21 December 2010] [00:14:27] <xpromache1>	I can send a reply saying connect here to get the data
| [Tuesday 21 December 2010] [00:14:32] <cremes>	sure
| [Tuesday 21 December 2010] [00:14:41] <xpromache1>	but what does it mean here
| [Tuesday 21 December 2010] [00:15:08] <cremes>	"here" where? explain.
| [Tuesday 21 December 2010] [00:15:17] <xpromache1>	that's my question
| [Tuesday 21 December 2010] [00:15:24] <xpromache1>	what do I answer to the client
| [Tuesday 21 December 2010] [00:15:30] <xpromache1>	where to connect to get its data
| [Tuesday 21 December 2010] [00:15:55] <xpromache1>	do I have to start a new thread, create a new socket on a random port, and start pushing data once a client is connected
| [Tuesday 21 December 2010] [00:16:05] <xpromache1>	or there is a smarter way
| [Tuesday 21 December 2010] [00:16:11] <cremes>	you could send in your reply something like: :transport => :tcp, :address => '10.10.4.48', :port => 1800
| [Tuesday 21 December 2010] [00:16:30] <cremes>	then the client would know where to go for getting the data
| [Tuesday 21 December 2010] [00:16:49] <cremes>	you can't do random ports without informing the client what it will be
| [Tuesday 21 December 2010] [00:17:02] <xpromache1>	yes, I realize that
| [Tuesday 21 December 2010] [00:17:13] <xpromache1>	I was hoping that it is somehow possible to do without random ports
| [Tuesday 21 December 2010] [00:17:13] <cremes>	you *could* use another thread or use the poll api to do it all within one
| [Tuesday 21 December 2010] [00:17:17] <xpromache1>	just one fixed port
| [Tuesday 21 December 2010] [00:17:37] <xpromache1>	like I have port x for request/reply
| [Tuesday 21 December 2010] [00:17:43] <xpromache1>	and port y for data transfer
| [Tuesday 21 December 2010] [00:17:52] <cremes>	sure, you could use 1 fixed port but you could run into issues if you have lots of concurrent requests/replies
| [Tuesday 21 December 2010] [00:18:36] <cremes>	you would probably want to use xreq/xrep sockets so your data transfer could target the right client
| [Tuesday 21 December 2010] [00:18:53] <cremes>	take a look at the "advanced routing" section of the guide; i'm pretty sure they wrote about that
| [Tuesday 21 December 2010] [00:19:15] <xpromache1>	but xreq/xrep needs one message in both ways
| [Tuesday 21 December 2010] [00:19:23] <cremes>	not true
| [Tuesday 21 December 2010] [00:19:24] <xpromache1>	I would need something like xpush xpull
| [Tuesday 21 December 2010] [00:19:31] <cremes>	not true
| [Tuesday 21 December 2010] [00:19:48] <cremes>	reqp/rep enforces a strict request/reply/request/reply pattern
| [Tuesday 21 December 2010] [00:19:59] <cremes>	the xreq/xrep sockets do *not* enforce that
| [Tuesday 21 December 2010] [00:20:32] <cremes>	so, using xreq/xrep, you could send a single request and get a multiple message reply
| [Tuesday 21 December 2010] [00:21:45] <xpromache1>	ok, I didn't know that
| [Tuesday 21 December 2010] [00:22:08] <xpromache1>	I will look further into it, thanks for the hints
| [Tuesday 21 December 2010] [00:22:40] <cremes>	no prob...
| [Tuesday 21 December 2010] [00:22:43] <cremes>	time for bed!
| [Tuesday 21 December 2010] [00:26:11] <xpromache1>	me too, I have to go to work in 2 hours :(
| [Tuesday 21 December 2010] [01:15:25] <bkad>	anyone know how to get the zmq_server binary? cant find it in the installation instructions
| [Tuesday 21 December 2010] [01:22:04] <guido_g>	what server?
| [Tuesday 21 December 2010] [01:23:23] <bkad>	zmq_server?
| [Tuesday 21 December 2010] [01:23:39] <bkad>	there's lots of references to it in the zmq docs
| [Tuesday 21 December 2010] [01:24:10] <bkad>	but the ./configure, make, make install didn't build that binary
| [Tuesday 21 December 2010] [01:24:58] <guido_g>	the docs are a bit outdated i fear
| [Tuesday 21 December 2010] [01:25:07] <bkad>	in http://www.zeromq.org/code:examples-exchange
| [Tuesday 21 December 2010] [01:25:12] <bkad>	under Running It
| [Tuesday 21 December 2010] [01:25:20] <guido_g>	there is a devices directory w/ some executables
| [Tuesday 21 December 2010] [01:25:27] <guido_g>	ouch
| [Tuesday 21 December 2010] [01:25:38] <guido_g>	this example is way outdated
| [Tuesday 21 December 2010] [01:25:46] <sustrik>	see the top of the page
| [Tuesday 21 December 2010] [01:25:48] <sustrik>	WARNING: This text is deprecated and refers to an old version of MQ. It remains here for historical interest. DO NOT USE THIS TO LEARN MQ.
| [Tuesday 21 December 2010] [01:25:56] <guido_g>	it'S even pre zeromq2 afair
| [Tuesday 21 December 2010] [01:26:03] <bkad>	ahhh, oops
| [Tuesday 21 December 2010] [03:34:47] <sustrik>	mikko: there's a build patch on the mailing list
| [Tuesday 21 December 2010] [03:34:53] <sustrik>	can you give it a look?
| [Tuesday 21 December 2010] [03:35:20] <sustrik>	mato is on his way to new zealand for next few days
| [Tuesday 21 December 2010] [03:56:25] <mikko>	sustrik: sure
| [Tuesday 21 December 2010] [03:56:37] <mikko>	it looks like my flight is departing today
| [Tuesday 21 December 2010] [03:56:45] <mikko>	causiously excited
| [Tuesday 21 December 2010] [03:57:52] <sustrik>	good luck :)
| [Tuesday 21 December 2010] [04:28:07] <mikko>	reviewed
| [Tuesday 21 December 2010] [04:29:05] <sustrik>	thanks
| [Tuesday 21 December 2010] [04:56:53] <mikko>	Steve-o: hi
| [Tuesday 21 December 2010] [04:57:03] <mikko>	what does the scons build produce?
| [Tuesday 21 December 2010] [04:57:05] <mikko>	Makefiles?
| [Tuesday 21 December 2010] [04:57:27] <Steve-o>	No it runs commands in Python directly
| [Tuesday 21 December 2010] [04:58:00] <Steve-o>	CMake is the Make wrapper
| [Tuesday 21 December 2010] [04:58:48] <mikko>	ok
| [Tuesday 21 December 2010] [04:58:56] <Steve-o>	you are supposed to be able to see the commands by "scons -Q" but I haven't seen that working on my Scons files in a long time
| [Tuesday 21 December 2010] [04:59:00] <mikko>	would've been nice if it produced something that could be directly used
| [Tuesday 21 December 2010] [04:59:29] <Steve-o>	well, all the other build systems kinda suck though :P
| [Tuesday 21 December 2010] [05:00:20] <Steve-o>	Although I think I had to patch Scons again for Intel C on Linux, urgh
| [Tuesday 21 December 2010] [05:00:50] <Steve-o>	CMake just doesn't support anything interesting
| [Tuesday 21 December 2010] [05:02:26] <mikko>	interesting development, my airline sends twitter DMs to inform about flights
| [Tuesday 21 December 2010] [05:04:06] <Steve-o>	Cathay likes to send emails after the flight has left
| [Tuesday 21 December 2010] [05:04:10] <mikko>	im wondering if we should split OS specific builds to separate automake files in zmq
| [Tuesday 21 December 2010] [05:04:24] <mikko>	it might be more maintainable than conditionals in one file
| [Tuesday 21 December 2010] [05:04:54] <Steve-o>	Makes patching a bit cleaner
| [Tuesday 21 December 2010] [05:06:37] <Steve-o>	unless you want to write several new autoconf rules
| [Tuesday 21 December 2010] [05:06:37] <mikko>	yeah
| [Tuesday 21 December 2010] [05:08:41] <Steve-o>	only ~24 tests required :P
| [Tuesday 21 December 2010] [05:09:17] <Steve-o>	many should already have autoconf macros available
| [Tuesday 21 December 2010] [05:11:08] <mikko>	it feels like duplicating work
| [Tuesday 21 December 2010] [05:11:10] <mikko>	hmm
| [Tuesday 21 December 2010] [05:11:28] <mikko>	would be nicer to launch scons from zmq build
| [Tuesday 21 December 2010] [05:11:34] <mikko>	and then just link
| [Tuesday 21 December 2010] [05:12:18] <Steve-o>	I've looked for a long time for building Debian packages
| [Tuesday 21 December 2010] [05:13:02] <Steve-o>	there isn't much out there despite all the big packages using SCons (Blender, Quake 3, etc)
| [Tuesday 21 December 2010] [05:14:37] <Steve-o>	as in, for nice hooks for the deb-buildpackager
| [Tuesday 21 December 2010] [05:14:58] <Steve-o>	you can always build a basic scons command based off uname otherwise
| [Tuesday 21 December 2010] [05:15:11] <mikko>	autoconf might be slightly dreadful but its fairly well supported
| [Tuesday 21 December 2010] [05:19:10] <Steve-o>	I don't think you can easily get multiple build environments in autoconf/automake though
| [Tuesday 21 December 2010] [05:19:30] <Steve-o>	Scons is killing me on crap compiler dependencies for unit tests
| [Tuesday 21 December 2010] [05:29:32] <Steve-o>	autoconf is a bit too cumbersome for testing different compilers on one platform
| [Tuesday 21 December 2010] [05:29:56] <Steve-o>	I'm sure there has to be a better way \:D/
| [Tuesday 21 December 2010] [05:30:54] <mikko>	it is slightly cumbersome yes
| [Tuesday 21 December 2010] [09:15:45] <ptrb>	correct me if I'm wrong, but if I'm sitting in a blocking recv() on a socket in one thread, and I zmq_term() the context in another thread, the recv() should return (in C++, should throw) -- right?
| [Tuesday 21 December 2010] [09:22:10] <sustrik>	ptrb: right
| [Tuesday 21 December 2010] [09:22:17] <sustrik>	ETERM
| [Tuesday 21 December 2010] [09:26:06] <ptrb>	hmm... the zmq_term() goes through OK, but I'm still blocking in the other thread... time for a minimal test case I guess :\
| [Tuesday 21 December 2010] [09:28:41] <sustrik>	yes, please
| [Tuesday 21 December 2010] [10:48:50] <mikko>	sustrik: zmq_term(ZMQ_NOBLOCK) would be useful
| [Tuesday 21 December 2010] [10:48:56] <mikko>	or another function call
| [Tuesday 21 December 2010] [10:51:11] <cremes>	mikko: something similar has been discussed on the ML; sustrik says it isn't possible
| [Tuesday 21 December 2010] [10:51:37] <sustrik>	you mean, instead setting all the sockets to ZMQ_LINGER=0
| [Tuesday 21 December 2010] [10:51:44] <sustrik>	right?
| [Tuesday 21 December 2010] [10:54:11] <mikko>	sustrik: no
| [Tuesday 21 December 2010] [10:54:21] <mikko>	sustrik: i mean instead of manually closing all sockets
| [Tuesday 21 December 2010] [10:54:36] <mikko>	because currently it's not possible to force closing of sockets
| [Tuesday 21 December 2010] [10:55:07] <sustrik>	hm, how would you migrate all the sockets to the thread calling zmq_term()?
| [Tuesday 21 December 2010] [10:55:48] <mikko>	do they need to be migrated to obtain information whether zmq_term would block?
| [Tuesday 21 December 2010] [10:56:18] <mikko>	i meant that zmq_term() would return EGAIN if given a flag
| [Tuesday 21 December 2010] [10:56:23] <mikko>	EAGAIN*
| [Tuesday 21 December 2010] [10:56:29] <sustrik>	how would the main thread know that they are not used in the moment otherwise?
| [Tuesday 21 December 2010] [10:56:43] <sustrik>	at the moment*
| [Tuesday 21 December 2010] [10:57:31] <sustrik>	you cannot grab a socket from underneath the feer of another thread
| [Tuesday 21 December 2010] [10:58:54] <mikko>	sockets is removed from sockets array in context when it's closed?
| [Tuesday 21 December 2010] [10:59:21] <sustrik>	yes
| [Tuesday 21 December 2010] [10:59:23] <mikko>	slightly laggy connection at the moment
| [Tuesday 21 December 2010] [10:59:36] <mikko>	sockets.size() > 0 would block, yes?
| [Tuesday 21 December 2010] [10:59:46] <sustrik>	yes
| [Tuesday 21 December 2010] [11:00:14] <mikko>	sozmq_term_nb woudl return EAGAIN if sockets.size() > 0
| [Tuesday 21 December 2010] [11:00:26] <sustrik>	aha
| [Tuesday 21 December 2010] [11:00:26] <mikko>	no need to migrate anything (?)
| [Tuesday 21 December 2010] [11:00:48] <sustrik>	i though you want zmq_term to close the sockets
| [Tuesday 21 December 2010] [11:01:28] <mikko>	im after info whether call to zmq_term will block
| [Tuesday 21 December 2010] [11:01:32] <mikko>	not to close sockets
| [Tuesday 21 December 2010] [11:01:52] <sustrik>	yes, that should be doable
| [Tuesday 21 December 2010] [11:02:09] <sustrik>	if you have a look atc ctx.cpp
| [Tuesday 21 December 2010] [11:02:14] <sustrik>	::terminate()
| [Tuesday 21 December 2010] [11:02:35] <mikko>	around line 118?
| [Tuesday 21 December 2010] [11:02:53] <sustrik>	the function begins at 107
| [Tuesday 21 December 2010] [11:03:05] <sustrik>	you have 2 waits there
| [Tuesday 21 December 2010] [11:03:25] <sustrik>	line 130:
| [Tuesday 21 December 2010] [11:03:27] <sustrik>	no_sockets_sync.wait ();
| [Tuesday 21 December 2010] [11:03:39] <sustrik>	and line 152:
| [Tuesday 21 December 2010] [11:03:41] <sustrik>	usleep (1000);
| [Tuesday 21 December 2010] [11:04:03] <sustrik>	the first wait waits for all sockets being closed (zmq_close)
| [Tuesday 21 December 2010] [11:04:12] <sustrik>	the second one wait for all pending data to be sent
| [Tuesday 21 December 2010] [11:04:21] <mikko>	ok
| [Tuesday 21 December 2010] [11:08:59] <cremes>	i like this EAGAIN idea for zmq_term()
| [Tuesday 21 December 2010] [11:27:36] <Skaag>	Hello!
| [Tuesday 21 December 2010] [11:27:40] <Skaag>	(again)
| [Tuesday 21 December 2010] [11:27:42] <mikko>	i
| [Tuesday 21 December 2010] [11:27:43] <mikko>	hi
| [Tuesday 21 December 2010] [11:27:47] <Skaag>	hi mikko :)
| [Tuesday 21 December 2010] [11:28:41] <Skaag>	we're about to perform a POC for ZMQ, and if all goes well, convert a system to ZMQ that uses RabbitMQ at the moment.
| [Tuesday 21 December 2010] [11:29:12] <Skaag>	but I wanted to ask, in general, about the theoretical potential of ZMQ to scale to thousands of servers...
| [Tuesday 21 December 2010] [11:29:43] <mikko>	Skaag: can you describe your specific use-case?
| [Tuesday 21 December 2010] [11:29:48] <mikko>	it would give some context
| [Tuesday 21 December 2010] [11:29:52] <Skaag>	And also how practical it is to use the multicast functionality - does it require special network equipment? is it IP Multicast? Or is it just a name really, and the multicast is just synonimous for sending the message at once to many hosts?
| [Tuesday 21 December 2010] [11:29:57] <Skaag>	sure!
| [Tuesday 21 December 2010] [11:30:07] <Skaag>	I have at the moment only 16 nodes, distributed around the world
| [Tuesday 21 December 2010] [11:30:22] <Skaag>	they send once per second a small block of data, statistical data about themselves
| [Tuesday 21 December 2010] [11:30:30] <Skaag>	less than 512 bytes
| [Tuesday 21 December 2010] [11:31:07] <Skaag>	so it's "all to all", and all of them need to collect this data, and produce historical graphs, etc.
| [Tuesday 21 December 2010] [11:31:23] <Skaag>	so i'm asking myself what will happen when this scales, to 1000 nodes
| [Tuesday 21 December 2010] [11:32:45] <mikko>	so every node needs to know about all others?
| [Tuesday 21 December 2010] [11:35:00] <cremes>	sounds like a perfect use-case for pub/sub with a forwarder device
| [Tuesday 21 December 2010] [11:35:38] <cremes>	Skaag: need more info; do you have particular latency requirements? how frequent is the data generated?
| [Tuesday 21 December 2010] [11:36:11] <mikko>	yeah, if latency is not a problem you could batch updates
| [Tuesday 21 December 2010] [11:36:16] <Skaag>	every 1 second, the nodes send to all other nodes a less than 512 byte data structure (json or binary, I don't mind)
| [Tuesday 21 December 2010] [11:36:35] <Skaag>	could also be every 5 seconds. still fine.
| [Tuesday 21 December 2010] [11:36:49] <Skaag>	but while the cluster is small, it would be cool to have fast updates.
| [Tuesday 21 December 2010] [11:36:58] <mikko>	sure
| [Tuesday 21 December 2010] [11:37:04] <mikko>	you could have quick local updates
| [Tuesday 21 December 2010] [11:37:10] <Skaag>	the latency between the nodes is a maximum of 100ms.
| [Tuesday 21 December 2010] [11:37:11] <mikko>	and batch the packets to remote locations
| [Tuesday 21 December 2010] [11:37:22] <Skaag>	there are at the moment 6 locations around the world
| [Tuesday 21 December 2010] [11:37:27] <Skaag>	with a bunch of machines in each location
| [Tuesday 21 December 2010] [11:37:30] <mikko>	update every second locally and send out every 5 seconds
| [Tuesday 21 December 2010] [11:37:48] <mikko>	so every five seconds you would send five updates to remote locations
| [Tuesday 21 December 2010] [11:37:50] <cremes>	multicast/pgm transport won't help you if this is over a public network (internet)
| [Tuesday 21 December 2010] [11:38:09] <Skaag>	ok so I was right to assume it is IP Multicast...
| [Tuesday 21 December 2010] [11:38:19] <Skaag>	and not some internal terminology
| [Tuesday 21 December 2010] [11:38:19] <mikko>	i would probably look into something like zookeeper for service discovery
| [Tuesday 21 December 2010] [11:38:33] <Skaag>	sounds interesting!
| [Tuesday 21 December 2010] [11:38:39] <mikko>	create ephimeral nodes of available endpoints
| [Tuesday 21 December 2010] [11:38:58] <mikko>	i used zookeeper ages ago for services discovery
| [Tuesday 21 December 2010] [11:39:18] <mikko>	wrote a small daemon called 'myservices' and each node on cluster had a configuration file of services it has
| [Tuesday 21 December 2010] [11:39:44] <mikko>	so as long as node was up the ephimeral node existed in zookeeper
| [Tuesday 21 December 2010] [11:39:58] <mikko>	when a node died the ephimeral node is automatically removed by zookeeper
| [Tuesday 21 December 2010] [11:40:08] <mikko>	allows 'automatic' graceful failure handling
| [Tuesday 21 December 2010] [11:40:53] <Skaag>	that's absolutely awesome
| [Tuesday 21 December 2010] [11:41:20] <mikko>	sadly the project never went live so i cant really tell how well it would've worked in production
| [Tuesday 21 December 2010] [11:44:00] <mikko>	im gonna go get some coffee
| [Tuesday 21 December 2010] [11:44:00] <mikko>	bbl
| [Tuesday 21 December 2010] [11:45:21] <ngerakines>	is there a list of large companies that use zmq on the site?
| [Tuesday 21 December 2010] [11:52:10] <Skaag>	mikko: Would love to take a look at your 'myservices' code ;)
| [Tuesday 21 December 2010] [11:54:19] <cremes>	ngerakines: i don't think so
| [Tuesday 21 December 2010] [11:54:26] <ngerakines>	cremes: ok, thanks
| [Tuesday 21 December 2010] [11:58:42] <sustrik>	Skaag: one thing to understand is that "all to all" model is inherently unscalable
| [Tuesday 21 December 2010] [11:59:12] <Skaag>	I thought about creating 'bubbles'
| [Tuesday 21 December 2010] [11:59:22] <Skaag>	so machines in the same DC would update quickly, internally
| [Tuesday 21 December 2010] [11:59:30] <sustrik>	at some point the number of nodes would be so high, that amount of messages will overload any receiver
| [Tuesday 21 December 2010] [11:59:37] <Skaag>	with less frequent updates being sent between such bubbles, aggregated
| [Tuesday 21 December 2010] [11:59:50] <sustrik>	yes, aggregation solves the problem
| [Tuesday 21 December 2010] [12:00:06] <Skaag>	we should probably do that from the start
| [Tuesday 21 December 2010] [12:00:26] <sustrik>	depends on the requirements
| [Tuesday 21 December 2010] [12:00:35] <sustrik>	it the goal is to have 1000 nodes
| [Tuesday 21 December 2010] [12:00:44] <sustrik>	with 1 msg per 5 secs
| [Tuesday 21 December 2010] [12:00:53] <sustrik>	you probably don't need it
| [Tuesday 21 December 2010] [12:13:49] <Skaag>	yes that's more or less the goal.
| [Tuesday 21 December 2010] [12:13:57] <Skaag>	it will take some time to get there, too...
| [Tuesday 21 December 2010] [12:14:04] <Skaag>	for now we have just 25 machines.
| [Tuesday 21 December 2010] [12:14:16] <Skaag>	I expect in 6 month it will maybe grow to 150.
| [Tuesday 21 December 2010] [12:14:50] <Skaag>	so there is time to ameliorate the system.
| [Tuesday 21 December 2010] [12:15:00] <Skaag>	uh, to improve the system.
| [Tuesday 21 December 2010] [12:15:11] <Skaag>	(I think maybe I used a french word?)
| [Tuesday 21 December 2010] [12:25:21] <mikko>	Skaag: what is this system doing?
| [Tuesday 21 December 2010] [12:25:32] <mikko>	what kinda of data are you pushing through?
| [Tuesday 21 December 2010] [12:25:37] <mikko>	just out of interest
| [Tuesday 21 December 2010] [12:28:12] <Skaag>	I can tell you exactly..!
| [Tuesday 21 December 2010] [12:28:18] <Skaag>	it is a bunch of media streamers
| [Tuesday 21 December 2010] [12:28:35] <Skaag>	the important information is cpu load, bandwidth usage, and number of connections
| [Tuesday 21 December 2010] [12:28:54] <Skaag>	and in the future, cost per traffic (actual cost, in dollars)
| [Tuesday 21 December 2010] [12:29:11] <Skaag>	or some combination of cost, and remaining quota
| [Tuesday 21 December 2010] [12:29:17] <Skaag>	but that's "phase 2" stuff :)
| [Tuesday 21 December 2010] [12:29:34] <Skaag>	and this will be used to make smart decisions about where to send new traffic
| [Tuesday 21 December 2010] [12:29:58] <Skaag>	and indirectly, will also be used to generate graphs for me and other admins, to view what's going on in the network
| [Tuesday 21 December 2010] [12:31:37] <mikko>	how do you do the routing on global level?
| [Tuesday 21 December 2010] [13:05:19] <Skaag>	Level3 fibers, connect all the DC's
| [Tuesday 21 December 2010] [13:06:43] <Skaag>	you can see our map here: http://bams.iptp.net/cacti/plugins/weathermap/output/weathermap_7.png
| [Tuesday 21 December 2010] [13:07:04] <Skaag>	right now, I am near m9.msk.ru :-)
| [Tuesday 21 December 2010] [13:07:15] <Skaag>	(physically speaking)
| [Tuesday 21 December 2010] [13:11:42] <Skaag>	and this means that this year, I will celebrate xmas in moscow  \o/  yey!
| [Wednesday 22 December 2010] [02:14:22] <ytang>	hi, anyone online?
| [Wednesday 22 December 2010] [02:33:39] <sustrik>	hi
| [Wednesday 22 December 2010] [02:38:47] <Steve-o>	good morning
| [Wednesday 22 December 2010] [03:05:04] <mindful>	anybody in
| [Wednesday 22 December 2010] [03:08:03] <sustrik>	yup
| [Wednesday 22 December 2010] [05:29:54] <mikko>	good morning
| [Wednesday 22 December 2010] [05:29:59] <mikko>	i made it 
| [Wednesday 22 December 2010] [05:39:12] <Skaag_>	made what?
| [Wednesday 22 December 2010] [05:39:16] <Skaag_>	to work? :)
| [Wednesday 22 December 2010] [07:29:42] <mikko>	Skaag: made it home for christmas
| [Wednesday 22 December 2010] [07:29:52] <mikko>	Skaag: i was flying from london to finland
| [Wednesday 22 December 2010] [07:30:09] <mikko>	took five days 
| [Wednesday 22 December 2010] [07:31:24] <Skaag>	wow!
| [Wednesday 22 December 2010] [07:31:27] <Skaag>	why 5 days?!
| [Wednesday 22 December 2010] [07:31:47] <Skaag>	I thought 5 days is with a ferry
| [Wednesday 22 December 2010] [07:31:55] <Skaag>	London to Stockholm, then Stockholm to Helsinki
| [Wednesday 22 December 2010] [07:32:18] <Skaag>	brb
| [Wednesday 22 December 2010] [07:34:20] <mikko>	Skaag: tons of canceled flights 
| [Wednesday 22 December 2010] [07:34:50] <mikko>	i was supposed to fly last friday and finally managed to fly tuesday evening
| [Wednesday 22 December 2010] [07:35:17] <Skaag>	sounds like a nightmare
| [Wednesday 22 December 2010] [07:40:10] <Skaag_>	back.
| [Wednesday 22 December 2010] [07:40:23] <Skaag>	I really should bring my bouncer into freenode as well...
| [Wednesday 22 December 2010] [10:55:02] <dos000>	howdy
| [Wednesday 22 December 2010] [10:55:56] <dos000>	can someone tell me if concurrent lock free circular buffers are used in zmq ? i read something recently that was talking about the perf improvements
| [Wednesday 22 December 2010] [11:43:20] <cremes>	dos000: 0mq definitely uses lock-free algos; i don't know if they protect a circular buffer though
| [Wednesday 22 December 2010] [11:43:34] <cremes>	the code answers all!
| [Wednesday 22 December 2010] [11:43:37] <Skaag>	lol
| [Wednesday 22 December 2010] [11:43:51] <Skaag>	*snicker* typical developer answer ;)
| [Wednesday 22 December 2010] [11:44:04] <Skaag>	what documentation? look at the comments in the code... ;)
| [Wednesday 22 December 2010] [11:44:09] <cremes>	yep ;)
| [Wednesday 22 December 2010] [11:45:18] <cremes>	docs usually don't cover those kinds of implementation details anyway
| [Wednesday 22 December 2010] [11:45:40] <cremes>	they are intended to remain hidden under the covers; anyone using the api shouldn't care what the algo is
| [Wednesday 22 December 2010] [11:46:12] <cremes>	since dos000 was asking specifically about it, the only way to get the real answer is to 1) ask sustrik
| [Wednesday 22 December 2010] [11:46:16] <cremes>	or 2) check the source
| [Wednesday 22 December 2010] [11:46:44] <dos000>	ah!
| [Wednesday 22 December 2010] [11:48:19] <dos000>	i was also looking for some experience in other libs offering lock-free circular buffers
| [Wednesday 22 December 2010] [11:48:32] <dos000>	this stuff seems like black magic 
| [Wednesday 22 December 2010] [11:48:55] <cremes>	yes, very dark :)
| [Wednesday 22 December 2010] [11:49:05] <dos000>	no one is doing it or talking about their implementation 
| [Wednesday 22 December 2010] [11:49:25] <dos000>	and no central de facto to go fo this .. evryone rolls their own
| [Wednesday 22 December 2010] [11:49:33] <cremes>	true
| [Wednesday 22 December 2010] [11:49:53] <cremes>	the main idea behind lock-free is to leverage a platform's atomic compare-and-swap operation
| [Wednesday 22 December 2010] [11:50:12] <cremes>	if your hw supports that, a lock-free impl is fairly "easy" to create
| [Wednesday 22 December 2010] [11:50:17] <dos000>	yes .. and i am hoping (please) support it
| [Wednesday 22 December 2010] [11:50:31] <cremes>	the hard part then becomes dealing with cache coherency and its perf implications
| [Wednesday 22 December 2010] [11:50:49] <dos000>	i am hoping 0mq has it for sparc and x86 and/or x86_64
| [Wednesday 22 December 2010] [11:51:08] <cremes>	it definitely has it for x86 and x86_64; not sure on sparc
| [Wednesday 22 December 2010] [11:51:45] <dos000>	cremes: zmq does not deal with threads correct ? i was thinking a way of "forcing" a thread to run on a particular core
| [Wednesday 22 December 2010] [11:52:19] <cremes>	dos000: not correct; you can force cpu affinity for sockets
| [Wednesday 22 December 2010] [11:52:28] <cremes>	check the setsockopt docs on the web site
| [Wednesday 22 December 2010] [11:52:38] <dos000>	ok
| [Wednesday 22 December 2010] [11:52:40] <cremes>	(i haven't used it myself otherwise i'd be more helpful...)
| [Wednesday 22 December 2010] [11:52:56] <dos000>	here is the (interesting) talk http://www.infoq.com/presentations/LMAX
| [Wednesday 22 December 2010] [11:53:15] <cremes>	ah, i just saw that this morning! it's in my queue to watch a bit later
| [Wednesday 22 December 2010] [11:53:30] <dos000>	ah!
| [Wednesday 22 December 2010] [11:53:31] <cremes>	i do trading stuff but i'm not in the super high-freq space
| [Wednesday 22 December 2010] [11:54:35] <dos000>	they mention someway of sending a packet straight to user space bypassing (virtually) the kernel ... but they dont explain how or which os supports it
| [Wednesday 22 December 2010] [11:55:09] <dos000>	very interestng talk indeed
| [Wednesday 22 December 2010] [11:55:52] <dos000>	cremes, which blog/sites do you follow for this types of talks ?
| [Wednesday 22 December 2010] [11:56:08] <dos000>	how did you stumble on the LMAX presentation ?
| [Wednesday 22 December 2010] [11:56:26] <cremes>	i subscribe to reddit rss feeds as well as the infoq rss stuff
| [Wednesday 22 December 2010] [11:58:10] <dos000>	the solution they propose starts from 36:00 if you want to skip through .. a picture is worth a thousand words
| [Wednesday 22 December 2010] [11:58:28] <cremes>	cool, thanks for the heads up
| [Wednesday 22 December 2010] [11:58:37] <cremes>	are you involved with trading systems or similar?
| [Wednesday 22 December 2010] [11:58:55] <dos000>	yes very similar .. payment systems
| [Wednesday 22 December 2010] [11:59:53] <Skaag>	dos000: don't the boost libraries do this type of locking?
| [Wednesday 22 December 2010] [12:00:54] <dos000>	i asked already in #C++ it might be only circular buffers .. not lock free implementations
| [Wednesday 22 December 2010] [12:01:40] <Skaag>	weren't all such kernel modules that broke the core -> user space membrane been kicked from the kernel project by Linus?
| [Wednesday 22 December 2010] [12:02:03] <dos000>	no idea!
| [Wednesday 22 December 2010] [12:02:10] <Skaag>	they are doing this without a custom kernel module?
| [Wednesday 22 December 2010] [12:02:25] <dos000>	not sure how .. its just a blimp in the video
| [Wednesday 22 December 2010] [12:40:07] <dos000>	ok ... now i found this http://www.puppetmastertrading.com/blog/2010/02/16/lock-free/
| [Wednesday 22 December 2010] [12:52:10] <mikko>	dos000: http://www.zeromq.org/blog:multithreading-magic
| [Wednesday 22 December 2010] [12:52:15] <mikko>	this might be interesting read as well
| [Wednesday 22 December 2010] [12:52:20] <mikko>	not directly related
| [Wednesday 22 December 2010] [12:58:59] <dos000>	fastflow seems to be up there with 0mq .. lots of similarities
| [Wednesday 22 December 2010] [13:03:57] <cremes>	dos000: they diss ruby in that blog so now i need to go on a rant! ;)
| [Wednesday 22 December 2010] [13:08:18] <Skaag>	lol!!!
| [Wednesday 22 December 2010] [13:08:37] <dos000>	lol
| [Wednesday 22 December 2010] [15:11:03] <Skaag>	the developer I work with tells me he managed to publish and consume a message on a topic with rabbitmq, but it's still unclear to him how to cluster the thing ;)
| [Wednesday 22 December 2010] [16:41:57] <mikko>	Skaag: you can publish and consume a message with zeromq within minutes 
| [Wednesday 22 December 2010] [16:41:58] <mikko>	:)
| [Wednesday 22 December 2010] [16:42:06] <Skaag>	I know
| [Wednesday 22 December 2010] [16:42:33] <Skaag>	anyway, what I am thinking to answer him, is that Zookeeper will be in charge of managing a list of IP addresses of available hosts
| [Wednesday 22 December 2010] [16:42:50] <Skaag>	and he will just connect to all of them and subscribe
| [Wednesday 22 December 2010] [16:43:07] <mikko>	did you test zookeeper
| [Wednesday 22 December 2010] [16:43:09] <mikko>	?
| [Wednesday 22 December 2010] [16:43:21] <Skaag>	not yet
| [Wednesday 22 December 2010] [16:43:25] <Skaag>	I'm installing it as we speak
| [Wednesday 22 December 2010] [16:44:07] <mikko>	the only annoyance i found was that zookeeper didnt have rhel packaging
| [Wednesday 22 December 2010] [16:44:12] <mikko>	i think i made spec-files back then
| [Wednesday 22 December 2010] [16:45:13] <Skaag>	well I am running on Ubuntu myself. I can't stand rhel.
| [Wednesday 22 December 2010] [16:45:31] <Skaag>	I used to be very redhat oriented
| [Wednesday 22 December 2010] [16:45:54] <Skaag>	but once I was exposed to debian, and then to ubuntu, I knew my destiny was sealed ;)
| [Wednesday 22 December 2010] [16:46:12] <mikko>	i use debian on my own stuff
| [Wednesday 22 December 2010] [16:46:16] <Skaag>	I know it may sound stupid, and rhel is considered a kind of 'standard'.
| [Wednesday 22 December 2010] [16:46:23] <mikko>	but many companies i work with prefer rhel
| [Wednesday 22 December 2010] [16:46:52] <dos000>	i hate rhel .. anything non debian (based) for that matter
| [Wednesday 22 December 2010] [16:47:13] <dos000>	apt-get is sweet
| [Wednesday 22 December 2010] [16:47:14] <mikko>	rhel packaging is far more pleasant to make imho
| [Wednesday 22 December 2010] [16:47:20] <mikko>	compared to debs
| [Wednesday 22 December 2010] [16:47:31] <Skaag>	i disagree
| [Wednesday 22 December 2010] [16:47:33] <dos000>	to use however isa different thing
| [Wednesday 22 December 2010] [16:47:37] <Skaag>	I make a deb in 3 minutes.
| [Wednesday 22 December 2010] [16:47:47] <Skaag>	less...
| [Wednesday 22 December 2010] [16:48:05] <Skaag>	well I have a ready skeleton, from the first 5 minutes I spent trying to make a deb
| [Wednesday 22 December 2010] [16:48:17] <dos000>	there are some utilities that will create the pkgs for you .. based on make && make installl
| [Wednesday 22 December 2010] [16:48:31] <Skaag>	so now to make a deb is a matter of copying the files to the right places, specifying dependencies, and perhaps adding some install / uninstall scripts...
| [Wednesday 22 December 2010] [16:48:53] <Skaag>	not to mention how easy it is to create a repository
| [Wednesday 22 December 2010] [16:49:12] <mikko>	Skaag: it's easy for yum as well
| [Wednesday 22 December 2010] [16:49:18] <mikko>	createrepo /path/to
| [Wednesday 22 December 2010] [16:49:45] <dos000>	i did not find companies that do support for debian so far 
| [Wednesday 22 December 2010] [16:50:04] <dos000>	something that passes the CEO test
| [Wednesday 22 December 2010] [16:51:13] <Skaag>	the CEO test is different in every company...
| [Wednesday 22 December 2010] [16:51:16] <Skaag>	in some, the money talks
| [Wednesday 22 December 2010] [16:51:29] <Skaag>	in some others, it's how large the support company is
| [Wednesday 22 December 2010] [16:51:38] <Skaag>	and in some, it's how technically knowledgable :-)
| [Wednesday 22 December 2010] [16:51:41] <dos000>	in some companies the CEO (and evryone around him) is dumb !
| [Wednesday 22 December 2010] [16:51:52] <dos000>	thats the problem
| [Wednesday 22 December 2010] [16:51:55] <Skaag>	and here in Russia! It's about how much money you slip into the CEO's pocket, behind the back of the board of directors...! ;-)
| [Wednesday 22 December 2010] [16:52:07] <dos000>	heh!
| [Wednesday 22 December 2010] [16:53:06] <mikko>	im not far from russia atm
| [Wednesday 22 December 2010] [16:53:13] <mikko>	a few hundred km if even that
| [Wednesday 22 December 2010] [16:54:01] <mikko>	Skaag: https://github.com/mkoppanen/myservices
| [Wednesday 22 December 2010] [16:54:15] <mikko>	it's not very well tested but should give some ideas for zk integration
| [Wednesday 22 December 2010] [16:54:21] <Skaag>	mikko: I read your page already ;)
| [Wednesday 22 December 2010] [16:54:52] <Skaag>	ah, that's another page
| [Wednesday 22 December 2010] [16:54:54] <Skaag>	sorry
| [Wednesday 22 December 2010] [16:54:58] <Skaag>	Where in Finland are you?
| [Wednesday 22 December 2010] [16:55:46] <Skaag>	I took the bus from Helsinki to St. Petersburg, just 6 month ago :-)
| [Wednesday 22 December 2010] [16:55:54] <Skaag>	17 euros and I was in Russia!
| [Wednesday 22 December 2010] [16:56:03] <mikko>	they got a new fast train as well
| [Wednesday 22 December 2010] [16:56:12] <mikko>	three hours to st petersburg from helsinki
| [Wednesday 22 December 2010] [16:56:27] <Skaag>	amazing
| [Wednesday 22 December 2010] [16:56:31] <dos000>	lets say i had 3 packets coming from 3 different sources ... and all packets are sequentially numbered. 
| [Wednesday 22 December 2010] [16:56:38] <Skaag>	but I doubt in such a weather condition?
| [Wednesday 22 December 2010] [16:57:01] <dos000>	what would you do to wait for three packets with the same seq numbers ?
| [Wednesday 22 December 2010] [16:57:06] <mikko>	Skaag: even in such conditions
| [Wednesday 22 December 2010] [16:57:11] <Skaag>	amazing!
| [Wednesday 22 December 2010] [16:57:12] <mikko>	things dont stop in .fi even when its cold
| [Wednesday 22 December 2010] [16:57:20] <Skaag>	I know
| [Wednesday 22 December 2010] [16:57:25] <Skaag>	but on the russian side...?
| [Wednesday 22 December 2010] [16:57:26] <Skaag>	:-)
| [Wednesday 22 December 2010] [16:57:35] <Skaag>	I lived in Helsinki for 5 month
| [Wednesday 22 December 2010] [16:57:45] <Skaag>	I absolutely love Finland
| [Wednesday 22 December 2010] [16:57:52] <Skaag>	awesome country.
| [Wednesday 22 December 2010] [16:57:58] <Skaag>	I loved it since childhood.
| [Wednesday 22 December 2010] [16:58:10] <Skaag>	and recently, after living there, I understood why.
| [Wednesday 22 December 2010] [16:58:56] <mikko>	i dislike the winter. thats why i moved to london
| [Wednesday 22 December 2010] [16:59:19] <Skaag>	maybe because you grew up with it.
| [Wednesday 22 December 2010] [16:59:50] <Skaag>	this is my second REAL winter here in Moscow, first time in Helsinki, where it was almost constantly under -10c
| [Wednesday 22 December 2010] [16:59:58] <Skaag>	and I don't mind it much.
| [Wednesday 22 December 2010] [17:01:07] <mikko>	im in middle .fi now
| [Wednesday 22 December 2010] [17:01:14] <mikko>	-30 outside
| [Wednesday 22 December 2010] [17:02:31] <mikko>	does your company operate in russia?
| [Wednesday 22 December 2010] [17:03:00] <Skaag>	yes
| [Wednesday 22 December 2010] [17:03:03] <Skaag>	among other places
| [Wednesday 22 December 2010] [17:03:27] <Skaag>	middle = near Sodankyl?
| [Wednesday 22 December 2010] [17:03:52] <mikko>	thats the northest place in finland
| [Wednesday 22 December 2010] [17:04:04] <mikko>	close to the sea up north
| [Wednesday 22 December 2010] [17:04:52] <mikko>	pretty close to Jyvskyl
| [Wednesday 22 December 2010] [17:05:03] <Skaag>	cool
| [Wednesday 22 December 2010] [17:05:41] <Skaag>	I have a good friend in Mikkeli
| [Wednesday 22 December 2010] [17:07:10] <Skaag>	I actually passed through Jyvskyl one time
| [Wednesday 22 December 2010] [17:09:44] <Skaag>	they just prepared Olutglgi
| [Wednesday 22 December 2010] [17:09:54] <Skaag>	http://mika.letonsaari.net/foobar/olutglgi/14.jpg
| [Wednesday 22 December 2010] [17:10:11] <Skaag>	some part of me is glad I can not taste it.
| [Wednesday 22 December 2010] [17:11:31] <mikko>	warm beer and spices?
| [Wednesday 22 December 2010] [17:11:57] <Skaag>	actually it looks interesting
| [Wednesday 22 December 2010] [17:13:15] <Skaag>	yes
| [Wednesday 22 December 2010] [17:59:27] <ryandmonk>	hello... curious if someone can help me out with at pyzmq issue
| [Wednesday 22 December 2010] [17:59:52] <ryandmonk>	i followed the instructions on site
| [Wednesday 22 December 2010] [17:59:56] <ryandmonk>	and ran python setup.py install
| [Wednesday 22 December 2010] [18:00:32] <ryandmonk>	its spits out some stuff.. but eventually gives an error saying "zmq/core/constants.c:1: error: #error Do not use this file, it is the result of a failed Cython compilation."
| [Wednesday 22 December 2010] [18:01:29] <ryandmonk>	im on ubuntu 10.10.. using zeromq-2.0.10
| [Wednesday 22 December 2010] [18:10:56] <cremes>	ryandmonk: try searching the ML archives; i have seen discussions on python binding problems there before
| [Wednesday 22 December 2010] [18:11:03] <cremes>	perhaps the solution is buried in the archives
| [Wednesday 22 December 2010] [18:12:44] <ryandmonk>	where are these archives?
| [Wednesday 22 December 2010] [18:13:15] <Skaag>	cool - I have a working 16 node zookeeper cluster :)
| [Wednesday 22 December 2010] [18:18:57] <ryandmonk>	found em.. thanks cremes!
| [Wednesday 22 December 2010] [20:26:13] <dos000>	how does the network/tcp driver deliver packets for the same flow when a new packet arrives ? does it look up a hash tree to find the correct app listening on that socket ?
| [Wednesday 22 December 2010] [20:26:36] <dos000>	i have to do kinda same thing ... and zmq does also
| [Wednesday 22 December 2010] [20:47:01] <Steve-o>	morning all
| [Wednesday 22 December 2010] [21:15:03] <Skaag>	morning Steve-o 
| [Wednesday 22 December 2010] [23:45:20] <NoobFukaire>	I'm trying to test out the hello world stuff for C++ and zeromq
| [Wednesday 22 December 2010] [23:45:37] <NoobFukaire>	the server binds and I can see it's there with netstat (and I can telnet into it)
| [Wednesday 22 December 2010] [23:45:46] <NoobFukaire>	but when I connect with the client, I get Assertion failed: fetched (rep.cpp:232)
| [Wednesday 22 December 2010] [23:46:26] <NoobFukaire>	which is:
| [Wednesday 22 December 2010] [23:46:27] <NoobFukaire>	            //  Get next part of the message.
| [Wednesday 22 December 2010] [23:46:28] <NoobFukaire>	            bool fetched = in_pipes [current]->read (msg_);
| [Wednesday 22 December 2010] [23:46:28] <NoobFukaire>	            zmq_assert (fetched);
| [Wednesday 22 December 2010] [23:46:43] <NoobFukaire>	I'm not sure whats up with this lib?
| [Wednesday 22 December 2010] [23:49:55] <NoobFukaire>	http://pastebin.com/piwK7gxL
| [Wednesday 22 December 2010] [23:49:59] <NoobFukaire>	the stack trace
| [Wednesday 22 December 2010] [23:54:06] <NoobFukaire>	https://github.com/imatix/zguide/blob/master/examples/C++/hwserver.cpp
| [Wednesday 22 December 2010] [23:54:11] <NoobFukaire>	https://github.com/imatix/zguide/blob/master/examples/C++/hwclient.cpp
| [Wednesday 22 December 2010] [23:54:13] <NoobFukaire>	that's the code
| [Thursday 23 December 2010] [00:07:48] <NoobFukaire>	okay nm, it had to do with some of my build paths
| [Thursday 23 December 2010] [01:55:03] <andrewvc>	cremes: you around?
| [Thursday 23 December 2010] [02:59:33] <sustrik>	hi mikko!
| [Thursday 23 December 2010] [03:16:20] <mikko>	sustrik: hi
| [Thursday 23 December 2010] [03:16:27] <sustrik>	morning
| [Thursday 23 December 2010] [03:16:41] <sustrik>	there's a build patch from steve in the ML
| [Thursday 23 December 2010] [03:16:51] <sustrik>	can i apply it?
| [Thursday 23 December 2010] [03:16:52] <mikko>	steve-o?
| [Thursday 23 December 2010] [03:16:56] <sustrik>	yes
| [Thursday 23 December 2010] [03:17:16] <mikko>	i'll review today if thats ok
| [Thursday 23 December 2010] [03:17:23] <sustrik>	sure, no haste
| [Thursday 23 December 2010] [03:17:31] <mikko>	i would like to change the way we build openpgm
| [Thursday 23 December 2010] [03:17:44] <sustrik>	what's the idea?
| [Thursday 23 December 2010] [03:17:48] <mikko>	it seems that we are duplicating a lot of work at the moment
| [Thursday 23 December 2010] [03:17:53] <mikko>	somehow that doesn't feel right
| [Thursday 23 December 2010] [03:17:59] <sustrik>	yes, we are
| [Thursday 23 December 2010] [03:18:12] <sustrik>	the alternative was to use scons
| [Thursday 23 December 2010] [03:18:40] <sustrik>	which create additional dependencies
| [Thursday 23 December 2010] [03:18:50] <sustrik>	any better idea?
| [Thursday 23 December 2010] [03:19:02] <mikko>	i was thinking about two options:
| [Thursday 23 December 2010] [03:19:06] <mikko>	a) invoke scons
| [Thursday 23 December 2010] [03:19:14] <mikko>	b) isolate openpgm flags to their own files
| [Thursday 23 December 2010] [03:19:47] <sustrik>	a) IMO is just shifting work from 0mq maintainers to 0mq users
| [Thursday 23 December 2010] [03:19:52] <mikko>	i think that having large amount of conditionals in the Makefile.am isn't maintainable in the long run. also makes patching harder
| [Thursday 23 December 2010] [03:20:19] <sustrik>	yes, agreed
| [Thursday 23 December 2010] [03:20:32] <sustrik>	would b) help with that?
| [Thursday 23 December 2010] [03:20:36] <mikko>	yes
| [Thursday 23 December 2010] [03:20:52] <mikko>	we would have something like foreign/Makefile.linux.am
| [Thursday 23 December 2010] [03:21:04] <mikko>	and include from configure.in based on OS/compiler
| [Thursday 23 December 2010] [03:21:14] <sustrik>	i see
| [Thursday 23 December 2010] [03:21:20] <mikko>	not sure if that works yet but ill try today
| [Thursday 23 December 2010] [03:21:26] <sustrik>	ok
| [Thursday 23 December 2010] [03:21:36] <mikko>	that way we could track openpgm build changes more easily
| [Thursday 23 December 2010] [03:21:56] <sustrik>	ack
| [Thursday 23 December 2010] [03:23:10] <mikko>	also, we should add support for solaris / freebsd with openpgm and the other steve is working on os x build
| [Thursday 23 December 2010] [03:23:20] <mikko>	so that's 5 conditionals in Makefile
| [Thursday 23 December 2010] [03:24:35] <sustrik>	sounds messy
| [Thursday 23 December 2010] [03:25:00] <mikko>	yeah, that was originally why i wanted to investigate invoking scons
| [Thursday 23 December 2010] [03:25:15] <mikko>	as steve has done a lot of work with different platforms / compilers to get the build working
| [Thursday 23 December 2010] [11:55:37] <NoobFukaire>	whats the best way to implement bidirectional messaging with zeromq?
| [Thursday 23 December 2010] [11:56:14] <NoobFukaire>	two REQ-REP sockets?
| [Thursday 23 December 2010] [11:56:45] <NoobFukaire>	I need either client to be able to send and receive messages at any point
| [Thursday 23 December 2010] [12:10:44] <sustrik>	what are you trying to do?
| [Thursday 23 December 2010] [12:11:17] <NoobFukaire>	I have two processes that need to exchange event information
| [Thursday 23 December 2010] [12:11:39] <NoobFukaire>	those events can be created at any time, on either end
| [Thursday 23 December 2010] [12:12:08] <NoobFukaire>	I wish there was some non blocking way to process inbound messages
| [Thursday 23 December 2010] [12:12:13] <NoobFukaire>	with zeromq
| [Thursday 23 December 2010] [12:16:26] <sustrik>	is that some kind of "multicast bus" scenario?
| [Thursday 23 December 2010] [12:16:42] <sustrik>	i.e. any message published by anyone is received by anyone else?
| [Thursday 23 December 2010] [12:17:05] <NoobFukaire>	no, it's basically client server
| [Thursday 23 December 2010] [12:17:18] <NoobFukaire>	right now it's 1:1 but there might be multiple clients in the future
| [Thursday 23 December 2010] [12:17:28] <NoobFukaire>	I'm find with 1:1 for now though
| [Thursday 23 December 2010] [12:17:29] <sustrik>	so it's 1 server and N clients
| [Thursday 23 December 2010] [12:17:50] <NoobFukaire>	*fine
| [Thursday 23 December 2010] [12:18:11] <NoobFukaire>	I'll refactor for multiple clients when the time comes and I know zeromq better ;)
| [Thursday 23 December 2010] [12:18:18] <sustrik>	what kind of interactions there are between server & client?
| [Thursday 23 December 2010] [12:18:32] <sustrik>	server publishing stream of events to be received by each client?
| [Thursday 23 December 2010] [12:18:34] <NoobFukaire>	I'm sending google protobuf messages back and forth
| [Thursday 23 December 2010] [12:19:05] <sustrik>	back & forth = client initiated handshake?
| [Thursday 23 December 2010] [12:19:07] <NoobFukaire>	they're just "events" they can be generated asynchronously by either side
| [Thursday 23 December 2010] [12:19:51] <sustrik>	0mq doesn't work that way, you have to identify patterns in the communications
| [Thursday 23 December 2010] [12:19:54] <sustrik>	handshakes
| [Thursday 23 December 2010] [12:20:02] <sustrik>	data distribution
| [Thursday 23 December 2010] [12:20:05] <sustrik>	load balancing
| [Thursday 23 December 2010] [12:20:07] <sustrik>	and similar
| [Thursday 23 December 2010] [12:20:14] <NoobFukaire>	okay I don't care about any of that
| [Thursday 23 December 2010] [12:20:24] <NoobFukaire>	this is about two process that exist on the same machine
| [Thursday 23 December 2010] [12:20:27] <NoobFukaire>	and need to communicate
| [Thursday 23 December 2010] [12:20:33] <sustrik>	use TCP then
| [Thursday 23 December 2010] [12:20:34] <NoobFukaire>	there will never be a performance issue
| [Thursday 23 December 2010] [12:20:42] <NoobFukaire>	gagh
| [Thursday 23 December 2010] [12:21:22] <sustrik>	well, 0mq needs to know what you are trying to achieve to help you
| [Thursday 23 December 2010] [12:21:25] <spht>	NoobFukaire:  Just because you're scenario is 1:1 doesn't mean a 1:N solution doesn't fit
| [Thursday 23 December 2010] [12:21:34] <spht>	s/you're/your
| [Thursday 23 December 2010] [12:21:34] <sustrik>	just saying "anything" doesn't work
| [Thursday 23 December 2010] [12:21:52] <NoobFukaire>	that's true but I'm just trying to keep things as simple as possible until I'm more familiar with zeromq
| [Thursday 23 December 2010] [12:22:34] <sustrik>	you can use PAIR socket
| [Thursday 23 December 2010] [12:22:39] <sustrik>	it's strictly 1:1
| [Thursday 23 December 2010] [12:22:55] <sustrik>	but there are some features missing, like auto-reconnection etc.
| [Thursday 23 December 2010] [12:23:55] <NoobFukaire>	spht: is there no way to check read zeromq input in a non blocking fashion?
| [Thursday 23 December 2010] [12:24:10] <NoobFukaire>	I have a function that gets called at a regular interval
| [Thursday 23 December 2010] [12:24:24] <NoobFukaire>	ideally, I'd like to have that check for input, process it and then process outbound messages
| [Thursday 23 December 2010] [12:24:24] <sustrik>	use ZMQ_NOBLOCK flag in recv()
| [Thursday 23 December 2010] [12:24:25] <spht>	NoobFukaire:   you can setup zeromq non-blocking IIRC, 
| [Thursday 23 December 2010] [12:24:54] <spht>	what sustrik said ;)
| [Thursday 23 December 2010] [12:24:58] <NoobFukaire>	right now it's blocking, so once recv is called, it blocks until input is returned
| [Thursday 23 December 2010] [12:25:02] <NoobFukaire>	what did he say
| [Thursday 23 December 2010] [12:25:33] <spht>	ZMQ_NOBLOCK
| [Thursday 23 December 2010] [12:25:55] <NoobFukaire>	thanks
| [Thursday 23 December 2010] [12:26:38] <spht>	but if your app is event driven to start with maybe you want to hook up the zeromq fd's into your runloop/reactor or what you use
| [Thursday 23 December 2010] [12:26:55] <spht>	sustrik:  IIRC thats possible, right?
| [Thursday 23 December 2010] [12:27:16] <spht>	I'm a newbie myself so I hope I'm not spreading lies ;)
| [Thursday 23 December 2010] [12:29:29] <NoobFukaire>	in my case, latency is very important and networking is not required at all
| [Thursday 23 December 2010] [12:29:40] <NoobFukaire>	because these events may have UI functionality executed as a result
| [Thursday 23 December 2010] [12:33:33] <sustrik>	spht: yes, it's possible
| [Thursday 23 December 2010] [12:34:25] <sustrik>	VoobFukaire: for best latency you can collacate the sender and receiver in the same process
| [Thursday 23 December 2010] [12:34:32] <sustrik>	each running is a different thread
| [Thursday 23 December 2010] [12:35:13] <spht>	And for low latency you probably do not want to poll for new messages (as I guess was what you wanted with the non-blocking sockets)
| [Thursday 23 December 2010] [12:52:20] <NoobFukaire>	I need to keep the UI responses ideally under ~100ms to eliminate any lag for the end user
| [Thursday 23 December 2010] [12:52:45] <NoobFukaire>	granted the UI stuff itself is done in the toolkit's thread, so these events are more of a "trigger" for those
| [Thursday 23 December 2010] [12:53:08] <NoobFukaire>	thank you for your help and suggestions
| [Thursday 23 December 2010] [12:54:59] <NoobFukaire>	ZMQ_NOBLOCK seems to do what I want with nonblocking io, thank you sustrik 
| [Thursday 23 December 2010] [12:57:46] <sustrik>	you are welcome
| [Thursday 23 December 2010] [13:58:55] <mikko>	sustrik: why doesn't pair auto-reconnect?
| [Thursday 23 December 2010] [13:59:10] <sustrik>	nobody implemented it :)
| [Thursday 23 December 2010] [13:59:21] <mikko>	is that a hint ?
| [Thursday 23 December 2010] [13:59:23] <mikko>	:)
| [Thursday 23 December 2010] [13:59:26] <sustrik>	:)
| [Thursday 23 December 2010] [13:59:35] <mikko>	drove 800km today
| [Thursday 23 December 2010] [13:59:36] <sustrik>	well, the thing is that PAIR is a socket type
| [Thursday 23 December 2010] [13:59:45] <sustrik>	that is most prone to misuse
| [Thursday 23 December 2010] [14:00:00] <sustrik>	so i quite like it being slightly broken
| [Thursday 23 December 2010] [14:00:10] <mikko>	i abuse pair heavily in my program
| [Thursday 23 December 2010] [14:00:15] <sustrik>	:)
| [Thursday 23 December 2010] [14:00:23] <sustrik>	where have you gone?
| [Thursday 23 December 2010] [14:00:28] <mikko>	dark place
| [Thursday 23 December 2010] [14:00:32] <sustrik>	finland?
| [Thursday 23 December 2010] [14:00:34] <mikko>	yeah
| [Thursday 23 December 2010] [14:01:06] <sustrik>	800km, than must be somewhere behing polar cirscle
| [Thursday 23 December 2010] [14:01:08] <sustrik>	circle
| [Thursday 23 December 2010] [14:01:16] <mikko>	drove to helsinki and back
| [Thursday 23 December 2010] [14:01:28] <mikko>	just to find out that my friend's flight is so late that we drove back
| [Thursday 23 December 2010] [14:01:38] <sustrik>	:|
| [Thursday 23 December 2010] [14:01:52] <mikko>	now he might even miss the last bus 
| [Thursday 23 December 2010] [14:02:27] <sustrik>	what's exactly the problem with flights?
| [Thursday 23 December 2010] [14:02:31] <sustrik>	too cold or what?
| [Thursday 23 December 2010] [14:03:42] <mikko>	he is flying from london heathrow
| [Thursday 23 December 2010] [14:03:49] <mikko>	the problem at heathrow is incompetence
| [Thursday 23 December 2010] [14:03:57] <sustrik>	i guess so
| [Thursday 23 December 2010] [14:04:14] <mikko>	it's not -29.5 celsius where i am
| [Thursday 23 December 2010] [14:04:27] <mikko>	and all airports open
| [Thursday 23 December 2010] [14:04:39] <sustrik>	actually, it's nice warm here in Bratislava today
| [Thursday 23 December 2010] [14:05:01] <sustrik>	temperature went up by 20 degress or so
| [Thursday 23 December 2010] [14:05:41] <sustrik>	btw, i'm messing with linux kernel
| [Thursday 23 December 2010] [14:06:45] <sustrik>	the experience so far is that in comparison 0MQ codebase is pretty sane and well documented
| [Thursday 23 December 2010] [14:07:46] <mikko>	heheh
| [Thursday 23 December 2010] [14:07:50] <mikko>	im not suprised
| [Thursday 23 December 2010] [14:08:19] <sustrik>	well, it's an old project so some amount of messiness is expected
| [Thursday 23 December 2010] [14:08:38] <sustrik>	but the network stack seems to have no comments at all
| [Thursday 23 December 2010] [14:08:42] <sustrik>	:(
| [Thursday 23 December 2010] [14:19:43] <mikko>	dark arts
| [Thursday 23 December 2010] [17:06:28] <andrewvc>	cremes: you around?
| [Thursday 23 December 2010] [20:25:43] Notice	-NickServ- travlr_ is not a registered nickname.
| [Thursday 23 December 2010] [21:26:56] <justanewbie>	Hi,i've installed the zeromq,but i cannot find a executable named zmq_server,just zmq_queue,zmq_streamer,zmq_forward,why?
| [Thursday 23 December 2010] [21:27:51] <justanewbie>	i wanted to know how to write config file of zmq_queue,but don't know how
| [Thursday 23 December 2010] [21:32:18] <mikko>	justanewbie: what are you trying to achieve?
| [Thursday 23 December 2010] [21:32:24] <mikko>	justanewbie: just run a device?
| [Thursday 23 December 2010] [21:32:58] <mikko>	i don't think the device configuration files are documented at the moment 
| [Thursday 23 December 2010] [21:33:13] <mikko>	it should be fairly easy to decipher the config from the code
| [Thursday 23 December 2010] [21:33:51] <mikko>	https://github.com/zeromq/zeromq2/blob/master/devices/zmq_streamer/zmq_streamer.cpp
| [Thursday 23 December 2010] [21:33:54] <mikko>	for exampe that
| [Thursday 23 December 2010] [21:35:25] <justanewbie>	thank u mikko,i'll take a look and c
| [Thursday 23 December 2010] [23:51:06] <neopallium>	Hey everyone, I just wanted to let you know about this https://github.com/Neopallium/lua-handlers lua project that I created it wraps lua-ev(event loop) & lua-zmq(requires ZeroMQ 2.1.0).  It makes it easy to work with many zmq/tcp/udp sockets in non-blocking mode.
| [Friday 24 December 2010] [02:37:58] <sustrik>	naopallium: announce it on the mailing list rather, there's much more people there
| [Friday 24 December 2010] [04:44:51] <cods>	Hi. Just to make sure I understand: for any type of 1-1 connection (push/pull, pub/sub, req/rep), it doesn't matter which side do a connect and which one do the bind, right? (of course, differences occurs when talking about 1-n or n-n)
| [Friday 24 December 2010] [05:00:31] <seb`>	afaik yes it does not matter
| [Friday 24 December 2010] [05:03:28] <cods>	ok
| [Friday 24 December 2010] [05:07:53] <neopallium>	cods: from what I know it doesn't even matter with 1-n or n-n connections.
| [Friday 24 December 2010] [05:11:01] <cods>	neopallium: well, I meant that when reversing role (binder/connecter) you have to adapt code to create many socket (connect) instead of one (bind) if you're the server for example, but apart from that, I understand what you mean (messages will be handled the same way at the end I guess)
| [Friday 24 December 2010] [05:16:44] <neopallium>	looks like you can bind & connect on the same zmq socket
| [Friday 24 December 2010] [05:17:25] <neopallium>	I just modified one of my test scripts which creates a PUB socket and had it bind to port 5555 and connect to port 5556
| [Friday 24 December 2010] [05:18:00] <neopallium>	on port 5556 was a script with a SUB socket
| [Friday 24 December 2010] [05:18:31] <neopallium>	both server & client SUB sockets where able to receive messages from the PUB socket.
| [Friday 24 December 2010] [05:18:51] <neopallium>	I didn't even think that was possible until now.
| [Friday 24 December 2010] [05:19:06] <cods>	oh, that's interesting. I have not seen that documented.
| [Friday 24 December 2010] [05:20:07] <neopallium>	I have read somewhere in the docs that zmq sockets don't put restrictions on who connects and who binds.
| [Friday 24 December 2010] [05:20:40] <neopallium>	but I didn't think that applied to binding & connection with the same socket.
| [Friday 24 December 2010] [05:22:08] <cods>	I like how 0mq is versatile. Great design.
| [Friday 24 December 2010] [05:33:05] <sustrik>	:)
| [Friday 24 December 2010] [05:34:15] <sustrik>	neopallium: you can also add the link to your project here:
| [Friday 24 December 2010] [05:34:16] <sustrik>	http://www.zeromq.org/docs:labs
| [Friday 24 December 2010] [06:22:19] <neopallium>	sustrik: thanks I just sent an email to the mailinglist.
| [Friday 24 December 2010] [06:48:01] <cods>	just curious while looking at the data on the wire, what the 0x01 0x01 header means? (before what looks like the "SPB" encoding) Is this documented somewhere? (or alternatively, where is it handled in the source code?)
| [Friday 24 December 2010] [10:02:59] <DasIch>	i'm currently trying to install pyzmq on a machine running ubuntu 10.10, even with libzmq-dev installed pip install pyzmq reports that a zmq_utils.h is missing
| [Friday 24 December 2010] [10:03:33] <DasIch>	i wasn't able to find any information regarding this issue is there a ppa i should use?
| [Friday 24 December 2010] [10:06:21] <DasIch>	ah, ppa:chris-lea-zeromq does the job
| [Friday 24 December 2010] [10:07:07] <DasIch>	uh no, i get an Assertion failed: !pgm_supported () (zmq.cpp:240)
| [Friday 24 December 2010] [10:07:50] <guido_g>	DasIch: do the versions of libzmq and pyzmq match?
| [Friday 24 December 2010] [10:11:37] <DasIch>	pyzmq version is 2.0.10, how do i find out the libzmq version?
| [Friday 24 December 2010] [10:12:17] <guido_g>	from the package? apt-cache show ... 
| [Friday 24 December 2010] [10:12:27] <DasIch>	ah it's also 2.0.10
| [Friday 24 December 2010] [10:13:05] <guido_g>	then it seems to be build w/o pgm
| [Friday 24 December 2010] [10:14:00] <guido_g>	get the source and compile it yourself
| [Friday 24 December 2010] [10:14:13] <DasIch>	guido_g: ok, thanks
| [Friday 24 December 2010] [11:55:51] <cremes>	andrewvc: i'm around for about 30m this morning; what's up?
| [Friday 24 December 2010] [12:12:57] <cremes>	andrewvc: send me a message offline and i'll answer it; i'll be off irc for the next 3 days or so...
| [Friday 24 December 2010] [12:13:21] <cremes>	merry christmas, everybody!
| [Friday 24 December 2010] [21:01:23] <lorph>	is there a API for communicating between TCP/UDP and zeromq, or do I have to make that myself
| [Saturday 25 December 2010] [11:05:11] <kuka>	hi! how to install zeroMQ lib in tomcat for using in web apps?
| [Saturday 25 December 2010] [11:05:34] <kuka>	ivan help us
| [Saturday 25 December 2010] [12:19:11] <keffo>	Merry off-work-period, everyone!
| [Saturday 25 December 2010] [17:28:45] <roxlu>	hi
| [Saturday 25 December 2010] [17:31:20] <roxlu>	I just found zeromq, and read the intro pages of the manual but I'm confused what's so good about zeromq?
| [Saturday 25 December 2010] [17:31:54] <roxlu>	It's a networking library; but what makes it different from other libs
| [Saturday 25 December 2010] [17:52:48] <keffo>	Might I suggest you keep reading beyond the intro pages?
| [Saturday 25 December 2010] [18:14:39] <Skaag>	yes, I suggest you do that, as well. I know for a fact that after you read more, it will become clear to you, because I just re-read those documents myself this week.
| [Saturday 25 December 2010] [18:15:02] <Skaag>	assume it's deeper and more important than you might imagine... ;-)
| [Saturday 25 December 2010] [21:22:00] <andrewvc>	cremes: around?
| [Sunday 26 December 2010] [03:42:06] <neopallium>	how does one detect if a request sent to a REQ socket is lost? (i.e. the server dies/restarts before sending the message from it's REP socket)
| [Sunday 26 December 2010] [03:44:36] <neopallium>	I have an example of a job queue server with worker clients, the workers connect a REQ socket to the server's XREP socket and pull for jobs, but if the server is restarted when the workers are waiting for a job, they get stuck.
| [Sunday 26 December 2010] [03:46:53] <guido_g>	you can't
| [Sunday 26 December 2010] [03:47:27] <guido_g>	or better, mq can't, you've to build a timeout yourself
| [Sunday 26 December 2010] [03:55:12] <neopallium>	one option I though of to try and solve this is to use PUB/SUB sockets so the server can tell the workers to re-connect.  But I don't think that will be an option for other uses of REQ/REP sockets.
| [Sunday 26 December 2010] [03:57:57] <guido_g>	right, req/rep is simple but doesn't work
| [Sunday 26 December 2010] [03:58:41] <guido_g>	you have to augment it w/ poll for timeout
| [Sunday 26 December 2010] [15:52:00] <andrewvc>	sustrik, cremes, I was wondering if either of you were around
| [Sunday 26 December 2010] [15:52:14] <andrewvc>	or anyone who's done work with FDs lately, they seem to act funky for me
| [Sunday 26 December 2010] [15:52:38] <andrewvc>	initially, they notify via 'select' properly, but after a point, they don't seem to
| [Sunday 26 December 2010] [15:52:59] <andrewvc>	select(15, [12 14], [], [], {0, 90000}) = 1 (in [12], left {0, 89997})
| [Sunday 26 December 2010] [15:52:59] <andrewvc>	select(15, [12 14], [], [], {0, 90000}) = 1 (in [12], left {0, 36581})
| [Sunday 26 December 2010] [15:53:00] <andrewvc>	select(15, [12 14], [], [], {0, 90000}) = 0 (Timeout)
| [Sunday 26 December 2010] [15:53:00] <andrewvc>	select(15, [12 14], [], [], {0, 90000}) = 0 (Timeout)
| [Sunday 26 December 2010] [15:53:00] <andrewvc>	select(15, [12 14], [], [], {0, 90000}) = 0 (Timeout)
| [Sunday 26 December 2010] [15:53:00] <andrewvc>	select(15, [12 14], [], [], {0, 90000}) = 0 (Timeout)
| [Sunday 26 December 2010] [15:53:12] <andrewvc>	even with a constant stream of messages
| [Sunday 26 December 2010] [16:06:10] <andrewvc>	oh, I'm not sure if this is true in general for select (or a total noob mistake), but previously I was reading a single message at a time off the socket whenever EM was notified by either select() or epoll(). This apparently does not work, your handler must repeatedly read off the socket until there is nothing left to read. I'm doing this by repeatedly checking ZMQ::EVENTS after reading each message. 
| [Sunday 26 December 2010] [21:49:22] <swills>	ping?
| [Sunday 26 December 2010] [21:49:39] <swills>	i was in here a while back asking about zeromq perl modules
| [Sunday 26 December 2010] [21:49:44] <swills>	http://travlr.github.com/zmqirclog/2010-November.html
| [Sunday 26 December 2010] [21:52:27] <swills>	i'me back to looking at that, but i think i've decided the issue is that the perl zeromq module is written to expect a threaded perl and threaded zeromq
| [Monday 27 December 2010] [08:29:48] <monokrome>	hey
| [Monday 27 December 2010] [08:30:04] <monokrome>	Does anyone know if I can use zeromq without using exceptions?
| [Monday 27 December 2010] [08:31:55] <monokrome>	I guess that I could use the C libraries :/
| [Monday 27 December 2010] [10:47:21] <andrewvc>	cremes: around?
| [Monday 27 December 2010] [10:52:01] <andrewvc>	actually, anyone else around? sustrik?
| [Monday 27 December 2010] [11:48:33] <andrewvc>	Anyone know why if you monitor a ZMQ FD with select for a read, and the select gets triggered, subsequent calls to select will show the socket as readable until all messages have been read off the socket?
| [Monday 27 December 2010] [12:30:50] <andrewvc>	cremes, thanks for the email wrt to edge triggering
| [Monday 27 December 2010] [12:34:40] <andrewvc>	you know if I after it gets triggered I should use a loop that checks ZMQ::EVENTS before reading each message, or just repeatedly calls recv(ZMQ::NOBLOCK) without checking ZMQ::EVENTS for reads. i'm guessing that recv alone is probably fine for reads, but ZMQ::EVENTS is probably a good thing to check for before sending a message
| [Monday 27 December 2010] [12:49:10] <neopallium>	andrewvc: I have used ZMQ::FD with the an event loop and the way I did it was to call recv()/send() until they return EAGAIN.  When recv() returns EAGAIN then wait for a read event before calling recv() again.  When send() returns EAGAIN then queue the data and wait for a write event.
| [Monday 27 December 2010] [12:49:31] <andrewvc>	cool
| [Monday 27 December 2010] [12:49:54] <andrewvc>	so, ZMQ_EVENTS is there only if you're curious, but don't actually want to send/read
| [Monday 27 December 2010] [12:49:57] <neopallium>	you can see how I did it in Lua code here: https://github.com/Neopallium/lua-handlers/blob/master/handler/nsocket.lua
| [Monday 27 December 2010] [12:50:04] <andrewvc>	nice! thanks
| [Monday 27 December 2010] [12:50:21] <neopallium>	I didn't use ZMQ_EVENTS
| [Monday 27 December 2010] [12:51:23] <neopallium>	seems like event mongrel2 which uses zeromq with an eventloop doesn't use ZMQ_EVENTS
| [Monday 27 December 2010] [12:51:29] <neopallium>	*even
| [Monday 27 December 2010] [12:51:30] <andrewvc>	interesting
| [Monday 27 December 2010] [12:51:56] <neopallium>	basically that is how you should work with an edge-trigger socket.
| [Monday 27 December 2010] [12:52:17] <andrewvc>	cool, yeah, I don't know where I got it into my head that ZMQ_EVENTS should be checked first
| [Monday 27 December 2010] [12:52:34] <neopallium>	you only pause your sending/receiving when you get an EAGAIN from the socket.
| [Monday 27 December 2010] [12:53:05] <andrewvc>	cool, yeah I've never really mucked around much with select/epoll before, I appreciate the pointers
| [Monday 27 December 2010] [12:53:06] <neopallium>	I really don't know what ZMQ_EVENTS is good for.
| [Monday 27 December 2010] [12:54:35] <neopallium>	oops that was the wrong file the one for zeromq socket is this one: https://github.com/Neopallium/lua-handlers/blob/master/handler/zsocket.lua
| [Monday 27 December 2010] [12:55:18] <neopallium>	the nsocket.lua file is for tcp/udp sockets which are level-triggered.
| [Monday 27 December 2010] [12:57:27] <andrewvc>	well
| [Monday 27 December 2010] [12:57:31] <andrewvc>	I recall someone saying
| [Monday 27 December 2010] [12:57:39] <cremes>	andrewvc: ZM_EVENTS is used to determine if there is a "whole" message ready on the FD
| [Monday 27 December 2010] [12:57:42] <andrewvc>	yeah
| [Monday 27 December 2010] [12:57:50] <andrewvc>	was about to say :)
| [Monday 27 December 2010] [12:57:52] <andrewvc>	lol
| [Monday 27 December 2010] [12:57:53] <cremes>	otherwise you would try to read a partial which eoesn't work in 0mq
| [Monday 27 December 2010] [12:58:01] <andrewvc>	but you'd get an EAGAIN right?
| [Monday 27 December 2010] [12:58:23] <andrewvc>	i mean, I assume it'd be a waste of cycles to call ZMQ_EVENTS before each recv
| [Monday 27 December 2010] [12:58:25] <cremes>	andrewvc: i don't know; i assume so but my assumptions are sometimes wildly wrong
| [Monday 27 December 2010] [12:58:33] <andrewvc>	lol
| [Monday 27 December 2010] [12:58:54] <cremes>	no, you wouldn't need to call it *each* time, just *once* after ZM_FD triggered
| [Monday 27 December 2010] [12:59:11] <cremes>	once ZM_FD and ZM_EVENTS agree, read until EAGAIN
| [Monday 27 December 2010] [13:03:06] <andrewvc>	gotcha
| [Monday 27 December 2010] [13:03:40] <andrewvc>	how about for a writable handler.
| [Monday 27 December 2010] [13:03:54] <andrewvc>	it's conceivable the writable state could change after any given message no?
| [Monday 27 December 2010] [13:10:58] <zedas>	neopallium: i think ZMQ_EVENTS is new, and I just use zmq_poll directly instead.
| [Monday 27 December 2010] [13:11:34] <neopallium>	ah, yeah I forgot about that.
| [Monday 27 December 2010] [15:20:38] <cremes>	andrewvc: what you said doesn't make sense from the write side
| [Monday 27 December 2010] [15:20:48] <andrewvc>	oh?
| [Monday 27 December 2010] [15:20:50] <cremes>	just write until you get EAGAIN; no need to check ZM_EVENTS
| [Monday 27 December 2010] [15:20:56] <andrewvc>	ah, gotcha
| [Tuesday 28 December 2010] [00:32:58] <lestrrat>	oh, woot, emails for build failures ;)
| [Tuesday 28 December 2010] [00:33:00] <lestrrat>	cool
| [Tuesday 28 December 2010] [06:02:30] <Skaag>	anyone here uses zookeeper with zmq?
| [Tuesday 28 December 2010] [06:46:50] <newbie2207>	hi
| [Tuesday 28 December 2010] [13:29:29] <CIA-21>	jzmq: 03Gonzalo Diethelm 07master * rb623601 10/ (4 files in 3 dirs): 
| [Tuesday 28 December 2010] [13:29:29] <CIA-21>	jzmq: Added new files (Streamer, Forwarder, Queue) to MSCV project.
| [Tuesday 28 December 2010] [13:29:29] <CIA-21>	jzmq: Corrected permissions. (+10 more commits...) - http://bit.ly/fgP0rH
| [Tuesday 28 December 2010] [13:35:55] <CIA-21>	jzmq: 03Gonzalo Diethelm 07master * r76b78bf 10/ README : 
| [Tuesday 28 December 2010] [13:35:55] <CIA-21>	jzmq: Merge branch 'master' of http://github.com/yawn/jzmq into yawn-master
| [Tuesday 28 December 2010] [13:35:55] <CIA-21>	jzmq: Conflicts:
| [Tuesday 28 December 2010] [13:35:55] <CIA-21>	jzmq:  README - http://bit.ly/fXVvAM
| [Tuesday 28 December 2010] [14:17:38] <shykes_>	hello
| [Tuesday 28 December 2010] [14:19:06] <shykes_>	I'm thinking of implementing a device with a simple "routing key" mechanism - does that exist already?
| [Tuesday 28 December 2010] [18:16:35] <lestrrat>	Can the hudson tests run the perl binding tests using "make test TEST_VERBOSE=1"? that would give me more hints for debugging
| [Tuesday 28 December 2010] [19:40:59] <s0undt3ch>	hello ppl
| [Tuesday 28 December 2010] [19:41:20] <s0undt3ch>	I'm getting "Assertion failed: !pgm_supported() ...." when trying to run one of the pyzmq examples
| [Tuesday 28 December 2010] [20:02:37] <bgranger>	s0undt3ch: what version of pyzmq and zeromq are you running?
| [Tuesday 28 December 2010] [20:03:11] <s0undt3ch>	bgranger: well the ones I get from the ppa repo are pyzmq 2.0.7 and zmq 2.0.10
| [Tuesday 28 December 2010] [20:03:39] <s0undt3ch>	bgranger: I'm now trying to build local versions of the libraries to see if I can get over that
| [Tuesday 28 December 2010] [20:03:40] <bgranger>	This is a known bug that has been fixed in 2.0.10 of pyzmq.  Can you give that a shot?
| [Tuesday 28 December 2010] [20:03:47] <bgranger>	Yep, that would solve it.
| [Tuesday 28 December 2010] [20:03:59] <s0undt3ch>	oh sorry
| [Tuesday 28 December 2010] [20:04:08] <bgranger>	But, just so you know, the library should work fine even though the tests fail.
| [Tuesday 28 December 2010] [20:04:08] <s0undt3ch>	I think I was using 2.0.10 of pyzmq
| [Tuesday 28 December 2010] [20:04:24] <s0undt3ch>	let me clean up the mess first
| [Tuesday 28 December 2010] [20:04:26] <bgranger>	OK
| [Tuesday 28 December 2010] [20:05:08] <bgranger>	Which example were you running.
| [Tuesday 28 December 2010] [20:05:16] <s0undt3ch>	heartbeat/heart.py
| [Tuesday 28 December 2010] [20:05:26] <s0undt3ch>	I'm building 2.0.10 now
| [Tuesday 28 December 2010] [20:07:33] <s0undt3ch>	ok, I now have the 2.0.10 pyzmq
| [Tuesday 28 December 2010] [20:07:46] <s0undt3ch>	bgranger: same error
| [Tuesday 28 December 2010] [20:08:59] <s0undt3ch>	ok, both packages libzmq0 and pyzmq are at 2.0.10
| [Tuesday 28 December 2010] [20:09:47] <s0undt3ch>	bgranger: yep, I've added a print statement at the top of heart.py
| [Tuesday 28 December 2010] [20:09:56] <s0undt3ch>	print zmq.__version__, zmq.__file__
| [Tuesday 28 December 2010] [20:10:00] <s0undt3ch>	output  is:
| [Tuesday 28 December 2010] [20:10:09] <s0undt3ch>	2.0.10 /home/vampas/projects/.virtual_python/lib/python2.6/site-packages/zmq/__init__.pyc
| [Tuesday 28 December 2010] [20:10:09] <s0undt3ch>	Assertion failed: !pgm_supported () (zmq.cpp:240)
| [Tuesday 28 December 2010] [20:10:09] <s0undt3ch>	Aborted
| [Tuesday 28 December 2010] [20:12:29] <bgranger>	Can you comment out line 17 of the heart.py and retry?
| [Tuesday 28 December 2010] [20:12:37] <bgranger>	The one where the Context is created.
| [Tuesday 28 December 2010] [20:13:47] <s0undt3ch>	bgranger: yeah, the Context() was what was causing it
| [Tuesday 28 December 2010] [20:16:38] <bgranger>	The issue is that when pgm is enabled (multicast), only 1 context can be created.  The ThreadDevice creates one (which is fine), but so did line 17.  The one in L17 was never used though.
| [Tuesday 28 December 2010] [20:16:52] <s0undt3ch>	bgranger: zmq.Context() wasn't doin' anything there right?
| [Tuesday 28 December 2010] [20:17:05] <bgranger>	This is a general limitation of zeromq - that with pgm, only 1 context can be used.
| [Tuesday 28 December 2010] [20:17:32] <bgranger>	But, pyzmq+zeromq should be working fine for you.
| [Tuesday 28 December 2010] [20:17:42] <s0undt3ch>	bgranger: but instead of completely failing can't it just warn or ignore and continue?
| [Tuesday 28 December 2010] [20:18:56] <bgranger>	As far as pyzmq goes, we don't have a clean way of doing that yet in general.  We would need zeromq to handle it differently, but zeromq is limited by the initialization model of pgm.
| [Tuesday 28 December 2010] [20:19:00] <bgranger>	Tough to get around.
| [Tuesday 28 December 2010] [20:19:23] <bgranger>	At least, that is how I remember the situation for now.
| [Tuesday 28 December 2010] [20:19:45] <s0undt3ch>	well Thanks!
| [Tuesday 28 December 2010] [20:19:48] <s0undt3ch>	:)
| [Tuesday 28 December 2010] [20:19:48] <bgranger>	Sure
| [Tuesday 28 December 2010] [20:19:54] <bgranger>	At least it is working.
| [Tuesday 28 December 2010] [20:20:04] <s0undt3ch>	anyway, now for some implementation thought
| [Tuesday 28 December 2010] [20:20:09] <s0undt3ch>	*thoughts
| [Tuesday 28 December 2010] [20:20:20] <s0undt3ch>	here's my problem
| [Tuesday 28 December 2010] [20:20:25] <bgranger>	Sure
| [Tuesday 28 December 2010] [20:21:06] <s0undt3ch>	I need to build a system that listens to audio streams, analyses them, and sends events to clients
| [Tuesday 28 December 2010] [20:21:31] <s0undt3ch>	I created this already using twisted, not that good though
| [Tuesday 28 December 2010] [20:21:59] <bgranger>	OK
| [Tuesday 28 December 2010] [20:22:00] <s0undt3ch>	what I'm trying to achieve now is use green threads, ie, eventlet or gevent
| [Tuesday 28 December 2010] [20:22:32] <bgranger>	Are the audio streams coming over zeromq as well?
| [Tuesday 28 December 2010] [20:22:34] <s0undt3ch>	the issue with this is that gstreamer the audio lib I'll use is not integrated with either eventlet nor gevent
| [Tuesday 28 December 2010] [20:23:14] <s0undt3ch>	bgranger: nope, zmq was going at first to be used for the events messaging
| [Tuesday 28 December 2010] [20:23:20] <bgranger>	OK
| [Tuesday 28 December 2010] [20:23:41] <bgranger>	So you have 1 process that is using gstreamer to look at audio streams and you want to fire off event to clients.
| [Tuesday 28 December 2010] [20:23:44] <bgranger>	How many clients?
| [Tuesday 28 December 2010] [20:23:50] <s0undt3ch>	what I've been advised by some eventlet ppl is to run each gstreamer audio stream in it's own process
| [Tuesday 28 December 2010] [20:24:02] <s0undt3ch>	at most 100 clients at least for now
| [Tuesday 28 December 2010] [20:24:06] <bgranger>	OK
| [Tuesday 28 December 2010] [20:24:16] <s0undt3ch>	this is going to be a tool to be used inside the company
| [Tuesday 28 December 2010] [20:24:19] <bgranger>	OK
| [Tuesday 28 December 2010] [20:24:31] <bgranger>	So you actually have N gstreamer processes and M clients
| [Tuesday 28 December 2010] [20:24:37] <s0undt3ch>	yes
| [Tuesday 28 December 2010] [20:24:39] <bgranger>	OK
| [Tuesday 28 December 2010] [20:24:55] <bgranger>	And you want all M clients to get the events from all N streaming processes?
| [Tuesday 28 December 2010] [20:25:31] <s0undt3ch>	so what I'm thinking now is, also use zmq to communicate between the gstreamer processes and a "core daemon" which will get all messages and deliver them to clients
| [Tuesday 28 December 2010] [20:25:43] <s0undt3ch>	well, all clients should receive all messages
| [Tuesday 28 December 2010] [20:25:54] <s0undt3ch>	so
| [Tuesday 28 December 2010] [20:25:56] <s0undt3ch>	yes
| [Tuesday 28 December 2010] [20:26:04] <s0undt3ch>	"all M clients to get the events from all N streaming processes"
| [Tuesday 28 December 2010] [20:26:36] <s0undt3ch>	since the core daemon and the gstreamer process will be on the same machine I though of using ipc
| [Tuesday 28 December 2010] [20:27:16] <s0undt3ch>	but as you can see there are several needs for the zmq lib which I'm just starting to get aquainted
| [Tuesday 28 December 2010] [20:27:25] <s0undt3ch>	oh
| [Tuesday 28 December 2010] [20:27:25] <bgranger>	Yes
| [Tuesday 28 December 2010] [20:27:37] <s0undt3ch>	the gstreamer processes will need to be controlable
| [Tuesday 28 December 2010] [20:27:45] <bgranger>	In what sense?
| [Tuesday 28 December 2010] [20:27:52] <s0undt3ch>	ie, I'll need to pass "commands" to it
| [Tuesday 28 December 2010] [20:28:24] <s0undt3ch>	ie, should it stop, change the stream configuration variables, etc
| [Tuesday 28 December 2010] [20:28:56] <bgranger>	OK, let's start with the basics of getting the events to the clients.
| [Tuesday 28 December 2010] [20:29:02] <s0undt3ch>	ok
| [Tuesday 28 December 2010] [20:29:09] <bgranger>	Let's call the gstreamer processes source processes.
| [Tuesday 28 December 2010] [20:29:13] <s0undt3ch>	sure
| [Tuesday 28 December 2010] [20:29:23] <bgranger>	For each source process, you will have a PUB socket.
| [Tuesday 28 December 2010] [20:29:53] <bgranger>	Each of those PUB sockets will connect to a FORWARDER device that runs in a separate process.
| [Tuesday 28 December 2010] [20:30:34] <bgranger>	The job of the FOWARDER process is to collect all the events and publish them to all clients.  The clients will each have a SUB socket that is connected to the other end of the FORWARDER process.
| [Tuesday 28 December 2010] [20:31:16] <s0undt3ch>	ok
| [Tuesday 28 December 2010] [20:31:30] <s0undt3ch>	so far, I'm understanding :)
| [Tuesday 28 December 2010] [20:32:05] <bgranger>	You could do all of this w/o the FORWARDER in the middle, but having it will make it much easier for all the clients to get the events of all the sources.
| [Tuesday 28 December 2010] [20:32:18] <s0undt3ch>	ok
| [Tuesday 28 December 2010] [20:32:19] <bgranger>	I would start out by prototyping that.
| [Tuesday 28 December 2010] [20:32:50] <s0undt3ch>	yeah, get some example code going on right?
| [Tuesday 28 December 2010] [20:33:01] <bgranger>	Then if you want to enable the clients to control the sources, I would use REQ/REP or XREQ/XREP sockets separately
| [Tuesday 28 December 2010] [20:33:02] <bgranger>	Yes
| [Tuesday 28 December 2010] [20:33:52] <bgranger>	The overall idea is to use different socket pairs for each type of communication pattern in your distributed application.  In some of our more complicated apps, we have many different zeromq sockets.
| [Tuesday 28 December 2010] [20:34:21] <s0undt3ch>	what are the diferences between the req/rep and x version of them
| [Tuesday 28 December 2010] [20:36:05] <bgranger>	There are a number of differences, I would check out the guide:
| [Tuesday 28 December 2010] [20:36:06] <bgranger>	http://zguide.zeromq.org/chapter:all#toc41
| [Tuesday 28 December 2010] [20:36:14] <s0undt3ch>	I will
| [Tuesday 28 December 2010] [20:36:39] <bgranger>	In most cases find myself using the X variants as they are more flexible and handle multiple peers asynchronously.
| [Tuesday 28 December 2010] [21:13:31] <s0undt3ch>	nice reading
| [Tuesday 28 December 2010] [21:13:47] <s0undt3ch>	so far I'm not thinking about scalability, at least at the sources level
| [Tuesday 28 December 2010] [21:14:10] <s0undt3ch>	the only part that should be scalable is client handling
| [Tuesday 28 December 2010] [21:14:23] <s0undt3ch>	anyway, let cook up some code...
| [Tuesday 28 December 2010] [21:14:29] <s0undt3ch>	*let's
| [Wednesday 29 December 2010] [03:49:51] <jugg>	Having an xrep (bind)/req (connect) setup, with xrep implementation using zmq 2.1.x and the req implementation using 2.0.10, and the req implementation being a single process with multiple threads, each thread having a req-socket.   It is always the case that eventually the req-socket after send'ing blocks on recv never getting a response.  Upgrading the req implementation to 2.1.0 greatly reduces this occurrence frequency, but it still happens.
| [Wednesday 29 December 2010] [03:50:10] <jugg>	Sometimes instead of locking on recv,  zmq asserts while blocking in recv with this error (zmq v2.1.0): Assertion failed: zmq_msg_size (msg_) == 0 (req.cpp:87). 
| [Wednesday 29 December 2010] [03:51:49] <jugg>	Has that use case xrep(bind)/req(connect) been tested much?
| [Wednesday 29 December 2010] [03:54:52] <sustrik>	the assert looks like there's an malformed message being received on the wire
| [Wednesday 29 December 2010] [03:56:27] <jugg>	Perhaps the xrep isn't filtering the id part correctly, and sending the separator message?
| [Wednesday 29 December 2010] [03:56:52] <sustrik>	dunno, can you make a minimal test case?
| [Wednesday 29 December 2010] [03:56:58] <jugg>	I'm still working on that...
| [Wednesday 29 December 2010] [03:57:36] <jugg>	I jumped in here where I found that changing the req implementation zmq library version changed the behavior...   I had been expecting to find the issue on the xrep side.
| [Wednesday 29 December 2010] [03:59:40] <jugg>	is the use case known to be robust, or does it have little known exposure?
| [Wednesday 29 December 2010] [04:03:32] <sustrik>	which part are you speaking about now? the blocking on recv or the assert?
| [Wednesday 29 December 2010] [04:09:47] <jugg>	one xrep(bind)/many req(connect) pair.
| [Wednesday 29 December 2010] [04:11:58] <sustrik>	what behaviour change?
| [Wednesday 29 December 2010] [04:12:30] <sustrik>	the assert?
| [Wednesday 29 December 2010] [04:12:49] <jugg>	the blocking on recv frequency diminished moving from 2.0.10 to 2.1.0.
| [Wednesday 29 December 2010] [04:13:00] <jugg>	The assert is random as ever with both versions.
| [Wednesday 29 December 2010] [04:13:53] <sustrik>	are you closing the req peer at that moment?
| [Wednesday 29 December 2010] [04:15:13] <jugg>	no, it happens at various points in the set of messages/responses I'm processing.
| [Wednesday 29 December 2010] [04:16:34] <sustrik>	are you setting HWMs?
| [Wednesday 29 December 2010] [04:16:43] <jugg>	no
| [Wednesday 29 December 2010] [04:16:55] <sustrik>	then it should not happen imo
| [Wednesday 29 December 2010] [04:17:11] <sustrik>	looks like a bug
| [Wednesday 29 December 2010] [04:18:31] <jugg>	If I can reproduce the issue on a simple test case, I'll pass it along.
| [Wednesday 29 December 2010] [04:18:44] <sustrik>	thanks
| [Wednesday 29 December 2010] [04:31:24] <s0undt3ch>	hello ppl, are there any issue using pyzmq inside a chroot?
| [Wednesday 29 December 2010] [04:31:30] <s0undt3ch>	http://paste.pocoo.org/show/311220/
| [Wednesday 29 December 2010] [09:30:10] <CIA-21>	jzmq: 03Gonzalo Diethelm 07master * ree2d21e 10/ (6 files in 2 dirs): 
| [Wednesday 29 December 2010] [09:30:10] <CIA-21>	jzmq: Added support for unregistering sockets from poller.
| [Wednesday 29 December 2010] [09:30:10] <CIA-21>	jzmq: Applied standard indentation everywhere on Java files. - http://bit.ly/fcb5Pi
| [Wednesday 29 December 2010] [09:43:58] <jgarbers>	Hi! I'm trying to build zmq under Visual Studio 2008 -- but the current source release seems to have VS2010 .vcproj files in its solution, so VS2008 can't read them. Is there a straightforward way to use VS2008 instead of VS2010?
| [Wednesday 29 December 2010] [09:45:58] <sustrik>	are they vs2010 project files?
| [Wednesday 29 December 2010] [09:46:13] <sustrik>	i recall i built it with vs2008 last time i tried
| [Wednesday 29 December 2010] [09:46:52] <jgarbers>	seems so, or maybe i'm doing something wrong
| [Wednesday 29 December 2010] [09:47:02] <jgarbers>	the VS2008 reports an error when opening the .sln
| [Wednesday 29 December 2010] [09:47:08] <jgarbers>	let me get the details again
| [Wednesday 29 December 2010] [09:47:37] <jgarbers>	i'm hoping this is a simple pilot error that will make me feel stupid for 5 minutes and let me get back to work :-)
| [Wednesday 29 December 2010] [09:48:17] <jgarbers>	says "...libzmq\libzmq.vcproj' cannot be opened because its project type (.vcproj) is not supported by this version of Visual Studio."
| [Wednesday 29 December 2010] [09:48:30] <jgarbers>	get that same error for each of the projects
| [Wednesday 29 December 2010] [09:50:18] <sustrik>	hm, no idea, sorry
| [Wednesday 29 December 2010] [09:51:45] <jgarbers>	darn. thanks anyway!
| [Wednesday 29 December 2010] [10:01:30] <jgarbers>	okay, it was indeed pilot stupidity. my VS2008 doesn't have C++ -- just C# and VB.  Cripes.  Off to go get the appropriate compiler, which *may* help.
| [Wednesday 29 December 2010] [11:49:20] <shykes_>	hello
| [Wednesday 29 December 2010] [11:49:46] <shykes_>	I'm seeing a weird issue when trying to PUB via a higher-latency link
| [Wednesday 29 December 2010] [11:50:09] <cremes>	what do you see?
| [Wednesday 29 December 2010] [11:50:38] <seb`>	REQ messages arrive with no problem
| [Wednesday 29 December 2010] [11:50:53] <seb`>	but PUB and PUSH messages never arrive
| [Wednesday 29 December 2010] [11:51:26] <shykes_>	... they never arrive *if sent from a home DSL link*
| [Wednesday 29 December 2010] [11:51:42] <shykes_>	PUB and PUSH messages *do* arrive at the same location if sent from the same datacenter
| [Wednesday 29 December 2010] [11:51:57] <seb`>	on tcp sockets btw
| [Wednesday 29 December 2010] [11:52:29] <cremes>	are you both working on the same issue? interleaving your messages like that is confusing....
| [Wednesday 29 December 2010] [11:52:43] <seb`>	sorry yes:-)
| [Wednesday 29 December 2010] [11:52:50] <cremes>	ok
| [Wednesday 29 December 2010] [11:53:22] <cremes>	what does the "on tcp sockets btw" comment mean? you are using both 0mq and your own sockets?
| [Wednesday 29 December 2010] [11:53:54] <seb`>	no I mean it's a tcp link
| [Wednesday 29 December 2010] [11:54:06] <seb`>	not epgm & co
| [Wednesday 29 December 2010] [11:54:07] <cremes>	ok, tcp transport in 0mq-speak
| [Wednesday 29 December 2010] [11:54:12] <seb`>	yes
| [Wednesday 29 December 2010] [11:54:30] <seb`>	"transport" that's the word I was looking for:-)
| [Wednesday 29 December 2010] [11:54:32] <cremes>	so to recap, req/rep works but pub & push do not
| [Wednesday 29 December 2010] [11:54:54] <seb`>	exactly
| [Wednesday 29 December 2010] [11:55:08] <sustrik>	strange
| [Wednesday 29 December 2010] [11:55:12] <cremes>	do *all* messages disappear or do you get *some* of them?
| [Wednesday 29 December 2010] [11:55:17] <seb`>	all of them
| [Wednesday 29 December 2010] [11:55:21] <seb`>	nothing arrives
| [Wednesday 29 December 2010] [11:55:50] <sustrik>	have a look whether the underlying tcp connection exists
| [Wednesday 29 December 2010] [11:56:01] <sustrik>	netstat or something
| [Wednesday 29 December 2010] [11:56:09] <cremes>	in your client program with the SUB socket, do you use setsockopt with ZM_SUBSCRIBE to set your subscription?
| [Wednesday 29 December 2010] [11:56:25] <cremes>	if you don't, all messages are dropped
| [Wednesday 29 December 2010] [11:56:31] <seb`>	cremes: yes we did
| [Wednesday 29 December 2010] [11:56:36] <cremes>	good
| [Wednesday 29 December 2010] [11:56:40] <seb`>	sustrik: I'll check
| [Wednesday 29 December 2010] [11:58:02] <seb`>	sustrik: netcat is able to connect
| [Wednesday 29 December 2010] [11:58:07] <sustrik>	i mean -- there may be a problem establishing the connection is particular direction
| [Wednesday 29 December 2010] [11:58:22] <sustrik>	due to firewalls
| [Wednesday 29 December 2010] [11:58:32] <sustrik>	the same way as in your use case?
| [Wednesday 29 December 2010] [11:59:06] <seb`>	sustrik: no it's not firewalls since a switch to req/rep works
| [Wednesday 29 December 2010] [11:59:30] <sustrik>	it may depend on the direction of connection establishment
| [Wednesday 29 December 2010] [11:59:39] <sustrik>	i.e. where you do bind and where you do connecty
| [Wednesday 29 December 2010] [12:00:00] <seb`>	the bind is server side
| [Wednesday 29 December 2010] [12:00:08] <sustrik>	same as in your use case?
| [Wednesday 29 December 2010] [12:00:43] <sustrik>	anyway, start you app and check whether the TCP connection is established
| [Wednesday 29 December 2010] [12:01:00] <sustrik>	that would be the best point to start the investigation
| [Wednesday 29 December 2010] [12:01:05] <seb`>	sustrik: yes checking now
| [Wednesday 29 December 2010] [12:02:16] <seb`>	yes it's established
| [Wednesday 29 December 2010] [12:03:31] <sustrik>	it's PUSH/PULL, right?
| [Wednesday 29 December 2010] [12:04:01] <seb`>	yes it is
| [Wednesday 29 December 2010] [12:04:11] <seb`>	but the problem is the same with PUB/SUB
| [Wednesday 29 December 2010] [12:04:29] <seb`>	but REQ/REP works (exactly the same conditions)
| [Wednesday 29 December 2010] [12:04:34] <sustrik>	let's focus on push/pull now
| [Wednesday 29 December 2010] [12:04:47] <seb`>	ok
| [Wednesday 29 December 2010] [12:04:56] <sustrik>	can you check whether data are passed on the wire?
| [Wednesday 29 December 2010] [12:05:08] <sustrik>	using wireshark or tcp dump?
| [Wednesday 29 December 2010] [12:05:17] <seb`>	yup
| [Wednesday 29 December 2010] [12:05:19] <seb`>	hold on
| [Wednesday 29 December 2010] [12:09:02] <shykes_>	Ok, we just found the problem ;)
| [Wednesday 29 December 2010] [12:09:10] <shykes_>	(taking over from seb`, sorry for the interleaving)
| [Wednesday 29 December 2010] [12:09:52] <shykes_>	in order to give you netstat information, we had the client stay open and wait for manual input to send
| [Wednesday 29 December 2010] [12:10:23] <shykes_>	instead of sending a pre-defined message and exiting instnatly
| [Wednesday 29 December 2010] [12:10:54] <shykes_>	when the client stays connected for a second or two, the messages start arriving
| [Wednesday 29 December 2010] [12:11:10] <shykes_>	looks like there's no guarantee that a connect() is ready when we start sending?
| [Wednesday 29 December 2010] [12:11:25] <shykes_>	I suppose in the context of a never-ending stream of messages, it's no big deal
| [Wednesday 29 December 2010] [12:11:26] <sustrik>	right
| [Wednesday 29 December 2010] [12:11:32] <sustrik>	zmq_connect is async
| [Wednesday 29 December 2010] [12:11:43] <shykes_>	So our problem is a non-problem :)
| [Wednesday 29 December 2010] [12:11:49] <sustrik>	great :)
| [Wednesday 29 December 2010] [12:12:00] <shykes_>	out of curiosity, any way to hook into connect?
| [Wednesday 29 December 2010] [12:12:11] <shykes_>	if we *do* need to wait for it to succeed? (ie for an automated test)
| [Wednesday 29 December 2010] [12:12:25] <seb`>	I think we could use zmq_poll for that
| [Wednesday 29 December 2010] [12:12:38] <sustrik>	not really, because the connection can be dropped and reestablished in the background
| [Wednesday 29 December 2010] [12:12:57] <sustrik>	so connect can happen even when no zmq_connect is being executed
| [Wednesday 29 December 2010] [12:13:56] <shykes_>	I see
| [Wednesday 29 December 2010] [12:14:00] <seb`>	sustrik: it should work to wait for POLLOUT right?
| [Wednesday 29 December 2010] [12:14:41] <sustrik>	pollout will succeed even though the connection is not established yet
| [Wednesday 29 December 2010] [12:14:48] <seb`>	ah?
| [Wednesday 29 December 2010] [12:14:57] <sustrik>	there's a message buffer
| [Wednesday 29 December 2010] [12:15:07] <sustrik>	if there's still space in the buffer
| [Wednesday 29 December 2010] [12:15:11] <seb`>	I see
| [Wednesday 29 December 2010] [12:15:12] <sustrik>	you can send messages
| [Wednesday 29 December 2010] [12:15:23] <sustrik>	they will be passed to the peer as soon as possible
| [Wednesday 29 December 2010] [12:15:48] <sustrik>	(i.e. when connection is established)
| [Wednesday 29 December 2010] [12:15:57] <seb`>	ok
| [Wednesday 29 December 2010] [12:16:04] <seb`>	thanks for your help
| [Wednesday 29 December 2010] [12:16:09] <sustrik>	you are welcome
| [Wednesday 29 December 2010] [17:39:52] <s0undt3ch>	hello ppl, here's a gdb session where I'm having troubles daemonizing my app -> http://paste.pocoo.org/show/311220/ <- seems to be related to pyzmq
| [Wednesday 29 December 2010] [17:57:03] <mikko>	s0undt3ch: do you fork() ?
| [Wednesday 29 December 2010] [17:57:18] <mikko>	and if yes do you init zmq before or after fork?
| [Wednesday 29 December 2010] [17:57:24] <s0undt3ch>	mikko: I'm using python-daemon and yes, it forks
| [Wednesday 29 December 2010] [17:57:35] <s0undt3ch>	mikko: and yes, I think zmq is setup before the fork
| [Wednesday 29 December 2010] [17:57:37] <s0undt3ch>	work?
| [Wednesday 29 December 2010] [17:57:41] <s0undt3ch>	*wrong
| [Wednesday 29 December 2010] [17:57:43] <s0undt3ch>	*wrong?
| [Wednesday 29 December 2010] [17:57:58] <mikko>	i remember someone having issues with that
| [Wednesday 29 December 2010] [17:58:07] <mikko>	try initializing all 0mq stuff after fork
| [Wednesday 29 December 2010] [17:59:32] <s0undt3ch>	mikko: hmm, zmq is beeing used to message that the app has forket, but I'll try to cook something up
| [Wednesday 29 December 2010] [18:02:16] <mikko>	are you forking just to daemonize?
| [Wednesday 29 December 2010] [18:05:04] <s0undt3ch>	mikko: hmm, lemme look at python-daemon's code
| [Wednesday 29 December 2010] [18:06:05] <s0undt3ch>	mikko: yes, it's forking to daemonize
| [Wednesday 29 December 2010] [18:06:33] <s0undt3ch>	mikko: http://paste.pocoo.org/show/311724/
| [Wednesday 29 December 2010] [18:13:07] <s0undt3ch>	mikko: if an app is chrooted, can it still reach the outside through tcp?
| [Wednesday 29 December 2010] [18:13:17] <s0undt3ch>	ie, will zmq connected to a tcp socket work?
| [Wednesday 29 December 2010] [18:13:49] <s0undt3ch>	doesn't seem to
| [Wednesday 29 December 2010] [18:18:29] <s0undt3ch>	hmm, I aparently have to mount proc inside the chroot, have a proper resolv.conf
| [Wednesday 29 December 2010] [18:18:59] <s0undt3ch>	so, aparently I have to solve both the daemonizing issues and also the chroot issues
| [Wednesday 29 December 2010] [18:22:23] <s0undt3ch>	hmm, how the hell does mogrel2 chroot
| [Wednesday 29 December 2010] [18:53:24] <mikko>	s0undt3ch: im not sure whether the fork actually causes the issues
| [Wednesday 29 December 2010] [18:53:45] <mikko>	but i think you are supposed to init zmq context for each fork
| [Wednesday 29 December 2010] [19:16:12] <s0undt3ch>	mikko: well, each for will have it's own context, nothing is shared between forks, hence zmq for the messaging between them
| [Wednesday 29 December 2010] [19:17:22] <mikko>	s0undt3ch: the gdb trace doesn't really tell anything
| [Wednesday 29 December 2010] [19:17:26] <mikko>	no symbols
| [Wednesday 29 December 2010] [19:18:23] <s0undt3ch>	mikko: well, it's a python virtualenv, don't know how to add debug symbols there
| [Wednesday 29 December 2010] [19:19:35] <mikko>	s0undt3ch: which version of zeromq is this?
| [Wednesday 29 December 2010] [19:19:50] <s0undt3ch>	mikko: both zmq and pyzmq are at 2.0.10
| [Wednesday 29 December 2010] [19:20:13] <mikko>	can you compile zmq with -O0 -g ?
| [Wednesday 29 December 2010] [19:20:25] <mikko>	hmm
| [Wednesday 29 December 2010] [19:20:53] <mikko>	looks like it aborts somewhere in zmq::epoll_t::loop but cant really know where/why
| [Wednesday 29 December 2010] [19:21:02] <mikko>	also testing with 2.1.0 would be helpful
| [Wednesday 29 December 2010] [19:22:34] <s0undt3ch>	mikko: well, I'd have to compile it myself and since this project is going to be deployd on a server which I'm trying to only have distro packages, I'm trying to avoid that
| [Wednesday 29 December 2010] [19:23:00] <s0undt3ch>	although 2.1.0 seems to make it easier to "attach" zmq to other event loops
| [Wednesday 29 December 2010] [19:25:19] <mikko>	s0undt3ch: does your distro provide a debug symbols package?
| [Wednesday 29 December 2010] [19:25:37] <s0undt3ch>	mikko: for what?
| [Wednesday 29 December 2010] [19:25:38] <s0undt3ch>	hmm
| [Wednesday 29 December 2010] [19:25:40] <s0undt3ch>	zmq
| [Wednesday 29 December 2010] [19:25:42] <s0undt3ch>	I think so
| [Wednesday 29 December 2010] [19:25:48] <s0undt3ch>	let me get it
| [Wednesday 29 December 2010] [19:26:58] <s0undt3ch>	mikko: however, after setting up zmq after the fork/chroot seems not to cause the issue anymore
| [Wednesday 29 December 2010] [19:30:34] <mikko>	cool
| [Wednesday 29 December 2010] [20:08:10] <s0undt3ch>	hmm
| [Wednesday 29 December 2010] [20:08:52] <s0undt3ch>	if I don't daemonize, zmq messages pass through outside the chroot, if I daemonize, they don't :\
| [Wednesday 29 December 2010] [20:17:40] <s0undt3ch>	hmm, I should not worry about chrooting right now, there' s a bunch of problems that will arrise, python libraries not found, etc, etc
| [Thursday 30 December 2010] [12:27:33] <mikko>	lestrrat: zeromq perl builds failing
| [Thursday 30 December 2010] [13:58:43] <mikko>	i to the b
| [Thursday 30 December 2010] [14:06:08] <ianbarber>	mikizzy
| [Thursday 30 December 2010] [14:07:26] <mikko>	are you back in UK?
| [Thursday 30 December 2010] [14:24:48] <Thomas_aboutus>	Hey everyone. I was wondering if someone could help me with a __stack_chk_fail problem I am having?
| [Thursday 30 December 2010] [14:26:33] <mikko>	Thomas_aboutus: what sort of problem is that?
| [Thursday 30 December 2010] [14:26:41] <mikko>	build time?
| [Thursday 30 December 2010] [14:27:43] <Thomas_aboutus>	No, it's at run time
| [Thursday 30 December 2010] [14:28:07] <Thomas_aboutus>	__stack_chk_fail is called when a stack smash is detected by stdlib (according to google).
| [Thursday 30 December 2010] [14:28:08] <mikko>	what language are you using?
| [Thursday 30 December 2010] [14:29:10] <Thomas_aboutus>	C
| [Thursday 30 December 2010] [14:29:14] <Thomas_aboutus>	The code is here: https://gist.github.com/760174
| [Thursday 30 December 2010] [14:29:19] <mikko>	are you sure you dont have stack overflow there?
| [Thursday 30 December 2010] [14:29:32] <Thomas_aboutus>	The gist description is the build command I'm using. I'm running it on mac os x
| [Thursday 30 December 2010] [14:29:41] <Thomas_aboutus>	It's possible, but if I do, I can't find it.
| [Thursday 30 December 2010] [14:29:58] <Thomas_aboutus>	I've had a couple folks here at the office take a look as well, and they are scratching their heads too.
| [Thursday 30 December 2010] [14:31:36] <Thomas_aboutus>	The basic idea of the code is a simple queue mechanism that I can use in bash scripts, etc. The error comes up when cat files to it on stdin, and passing it the "-o tcp://127.0.0.1:12345" option to have the output get pushed onto a queue. You can read off of it by kicking of another one with the -i flag set to the same value.
| [Thursday 30 December 2010] [14:34:02] <mikko>	sec
| [Thursday 30 December 2010] [14:34:06] <mikko>	let me look at the code
| [Thursday 30 December 2010] [14:35:20] <Thomas_aboutus>	Cool. I really appreciate it!
| [Thursday 30 December 2010] [14:35:22] <mikko>	line 22
| [Thursday 30 December 2010] [14:35:30] <mikko>	you init the message to size strlen(message)
| [Thursday 30 December 2010] [14:35:46] <mikko>	but wouldnt strncpy copy the terminating \0 as well?
| [Thursday 30 December 2010] [14:36:09] <mikko>	also, lines 18 and 22 dont really play well
| [Thursday 30 December 2010] [14:37:18] <Thomas_aboutus>	Good point. Okay, I'll change that and see if that helps
| [Thursday 30 December 2010] [14:37:40] <mikko>	and i think you should use memcpy rather than strcpy
| [Thursday 30 December 2010] [14:37:47] <mikko>	conceptually the data is a void *
| [Thursday 30 December 2010] [14:38:46] <mikko>	and there is zmq_msg_init_data as well
| [Thursday 30 December 2010] [14:43:30] <Thomas_aboutus>	Alright, so I changed the code (I updated the gist in case you care) and it all seems to be working now! I also had to change the reading part, but that did the trick.
| [Thursday 30 December 2010] [14:43:50] <Thomas_aboutus>	Thank you again! I just couldn't see pas the wall staring at it, and a simple bug like that just got overlooked.
| [Thursday 30 December 2010] [14:44:05] <mikko>	zmq_close(&in_socket);
| [Thursday 30 December 2010] [14:44:11] <mikko>	that doesnt look right either
| [Thursday 30 December 2010] [14:46:20] <Thomas_aboutus>	Yup, you're right. I've been killing the running processes with Ctrl-C so it never came up, but good catch.
| [Thursday 30 December 2010] [14:46:59] <Thomas_aboutus>	Thanks again!
| [Thursday 30 December 2010] [15:03:45] Notice	-NickServ- travlr__ is not a registered nickname.
| [Thursday 30 December 2010] [15:41:59] <lestrrat>	mikko: Yes, but can you change the "make test" in the test to "make test TEST_VERBOSE=1" so I can see where the tests are halting
| [Thursday 30 December 2010] [15:42:22] <mikko>	cool
| [Thursday 30 December 2010] [15:42:24] <mikko>	ill check
| [Thursday 30 December 2010] [15:42:31] <mikko>	should i change the build to do that as well?
| [Thursday 30 December 2010] [15:43:20] <mikko>	currently the daily build uses ./autobuild/run.sh
| [Thursday 30 December 2010] [15:44:57] <mikko>	https://gist.github.com/24e54efd2f763ea5bee1
| [Friday 31 December 2010] [08:56:41] <fliebel>	Hey, What would be the best way to have a many-to-many message queue, where clients publish messages to all other clients?
| [Friday 31 December 2010] [09:29:55] <sustrik>	use forwarder device in the middle
| [Friday 31 December 2010] [10:05:08] <Skaag>	what forwarder device?
| [Friday 31 December 2010] [12:58:42] <neopallium>	Skaag: When you install ZeroMQ you should get an exe called: zmq_forwarder
| [Friday 31 December 2010] [12:59:03] <neopallium>	also you can see how the forwarder would be coded in C at: http://zguide.zeromq.org/chapter:all#toc30
| [Friday 31 December 2010] [12:59:34] <neopallium>	there are other devices: zmq_queue & zmq_streamer
| [Friday 31 December 2010] [13:12:18] <Skaag>	oh that one
| [Friday 31 December 2010] [13:12:20] <Skaag>	ok
| [Friday 31 December 2010] [13:12:21] <Skaag>	:)
| [Friday 31 December 2010] [13:32:21] <neopallium>	When a custom identity is used on a socket, should it always be set before making bind()/connect() calls on that socket?
| [Friday 31 December 2010] [13:37:00] <neopallium>	ah, I found the answer at the end of this section: http://zguide.zeromq.org/chapter:all#toc37
| [Friday 31 December 2010] [16:33:24] <d4de>	Happy New Year - Egypt (^_^)
| [Wednesday 01 December 2010] [00:40:43] <guido_g>	Nate75Sanders: no HWM means: queue all messages as long as memory permits.
| [Wednesday 01 December 2010] [00:41:34] <Nate75Sanders>	guido_g: Fair enough, but that means the documentation is wrong.
| [Wednesday 01 December 2010] [00:41:41] <guido_g>	Nate75Sanders: i think the "no downstream nodes" only applies when there _never_ were one
| [Wednesday 01 December 2010] [00:42:12] <guido_g>	because if there was a connection, then there is a queue and the hwm applies
| [Wednesday 01 December 2010] [00:42:28] <Nate75Sanders>	guido_g: strange....I definitely think the man page should describe this in more detail
| [Wednesday 01 December 2010] [00:42:54] <guido_g>	than attach a fix to the issue or post a patch to the ml
| [Wednesday 01 December 2010] [00:42:54] <Nate75Sanders>	guido_g: could you tell me where you gained this particular understanding of things? so i can read there instead?
| [Wednesday 01 December 2010] [00:43:30] <Nate75Sanders>	guido_g: I'd like to make _sure_ what you're saying is correct (it sounds like it is).
| [Wednesday 01 December 2010] [00:43:49] <guido_g>	Nate75Sanders: easy, hang around here for 3 to 4 month, read the things from the core devs that fly by and you'll know :)
| [Wednesday 01 December 2010] [00:44:10] <Nate75Sanders>	guido_g: understood :)
| [Wednesday 01 December 2010] [00:44:16] <guido_g>	Nate75Sanders: then write a test case and check what'S going on
| [Wednesday 01 December 2010] [00:44:34] <Nate75Sanders>	well, i'm halfway there -- based on my bug report
| [Wednesday 01 December 2010] [00:44:52] <Nate75Sanders>	just need a no-receiver at all case
| [Wednesday 01 December 2010] [00:45:06] <guido_g>	btw, writing a bug report w/o proof (aka test/show case) isn't worth much
| [Wednesday 01 December 2010] [00:45:16] <Nate75Sanders>	you know what? actually i think i tested that earlier
| [Wednesday 01 December 2010] [00:45:45] <Nate75Sanders>	yeah
| [Wednesday 01 December 2010] [00:45:45] <Nate75Sanders>	i did
| [Wednesday 01 December 2010] [00:45:48] <Nate75Sanders>	and i just did now, too
| [Wednesday 01 December 2010] [00:46:02] <Nate75Sanders>	there was never a downstream node
| [Wednesday 01 December 2010] [00:46:06] <Nate75Sanders>	and it still does NOT block
| [Wednesday 01 December 2010] [00:46:09] <guido_g>	then attach your test incl. program to the issue, so that it can be verified
| [Wednesday 01 December 2010] [00:46:17] <Nate75Sanders>	i did
| [Wednesday 01 December 2010] [00:46:21] <Nate75Sanders>	it's in the bug report
| [Wednesday 01 December 2010] [00:46:22] <Nate75Sanders>	2 scripts
| [Wednesday 01 December 2010] [00:46:35] <Nate75Sanders>	you can run the PUSHer without the PULLer and it refutes what you said earlier
| [Wednesday 01 December 2010] [00:47:45] <Nate75Sanders>	when you have a PUSHer, if there's no HWM present (whether or not there ever was) the behavior is that it will not block
| [Wednesday 01 December 2010] [00:47:58] <Nate75Sanders>	sorry, meant to say
| [Wednesday 01 December 2010] [00:48:21] <Nate75Sanders>	if there's no HWM and no receiver (whether or not there ever was a receiver) the behavior is that it will not block
| [Wednesday 01 December 2010] [00:48:51] <Nate75Sanders>	so, I'm not sure where you got your info, but it isn't correct
| [Wednesday 01 December 2010] [00:49:34] <Nate75Sanders>	you can run my code if you don't believe me
| [Wednesday 01 December 2010] [00:49:38] <Nate75Sanders>	maybe i'm crazy somehow
| [Wednesday 01 December 2010] [00:49:42] <Nate75Sanders>	but it's in the bug report
| [Wednesday 01 December 2010] [00:50:36] <Nate75Sanders>	wish sustrik was around....
| [Wednesday 01 December 2010] [00:51:00] <guido_g>	he will be in an hour or so
| [Wednesday 01 December 2010] [00:51:06] <guido_g>	he's an early bird
| [Wednesday 01 December 2010] [00:53:33] <guido_g>	hmm hmm mhmm
| [Wednesday 01 December 2010] [00:53:56] <guido_g>	if you use bind instead of connect on the push side, it works
| [Wednesday 01 December 2010] [00:54:16] <guido_g>	i just used "socket.bind("tcp://127.0.0.1:5555")"
| [Wednesday 01 December 2010] [00:54:23] <guido_g>	and it blocks, as described
| [Wednesday 01 December 2010] [00:55:10] <guido_g>	and with connect the hwm works too
| [Wednesday 01 December 2010] [00:56:14] <guido_g>	so it's more a documentation issue on bind vs connect, i'd say
| [Wednesday 01 December 2010] [00:58:25] <Nate75Sanders>	fair enough
| [Wednesday 01 December 2010] [00:58:27] <guido_g>	Nate75Sanders: just added that as a comment to your issue
| [Wednesday 01 December 2010] [00:58:30] <Nate75Sanders>	i had considered that, but not tested it
| [Wednesday 01 December 2010] [00:58:36] <guido_g>	tz tz tz
| [Wednesday 01 December 2010] [00:58:52] <Nate75Sanders>	i think in one part of the docks they make a big point to say that bind vs connect shouldn't affect socket semantics
| [Wednesday 01 December 2010] [00:59:04] <Nate75Sanders>	just the stable vs non-knowable parts of your architecture
| [Wednesday 01 December 2010] [00:59:11] <Nate75Sanders>	so i really do think that should be dealt with
| [Wednesday 01 December 2010] [00:59:24] <Nate75Sanders>	but good detective work
| [Wednesday 01 December 2010] [00:59:52] <guido_g>	before first coffee
| [Wednesday 01 December 2010] [01:00:02] <Nate75Sanders>	are you in europe?
| [Wednesday 01 December 2010] [01:00:06] <guido_g>	yes
| [Wednesday 01 December 2010] [01:00:19] <Nate75Sanders>	italy?
| [Wednesday 01 December 2010] [01:00:23] <guido_g>	no
| [Wednesday 01 December 2010] [01:00:25] <Nate75Sanders>	oh :)
| [Wednesday 01 December 2010] [01:00:26] <Nate75Sanders>	hehe
| [Wednesday 01 December 2010] [01:00:29] <Nate75Sanders>	I'm in Honolulu
| [Wednesday 01 December 2010] [01:00:34] <Nate75Sanders>	so it's 8PM here
| [Wednesday 01 December 2010] [01:00:37] <guido_g>	*sigh*
| [Wednesday 01 December 2010] [01:00:39] <Nate75Sanders>	"yesterday" :)
| [Wednesday 01 December 2010] [01:00:52] <Nate75Sanders>	moving soon
| [Wednesday 01 December 2010] [01:01:01] <Nate75Sanders>	this is a fun place to live, but not good for hackers
| [Wednesday 01 December 2010] [01:01:23] <Nate75Sanders>	i will miss the weather, though
| [Wednesday 01 December 2010] [01:01:27] <Nate75Sanders>	truly, truly amazing
| [Wednesday 01 December 2010] [01:01:34] <Nate75Sanders>	in the winter it's 75 and sunny
| [Wednesday 01 December 2010] [01:01:36] <guido_g>	given that outside are -7C i tend to be a bit jealous
| [Wednesday 01 December 2010] [01:01:38] <Nate75Sanders>	in the summer, it's 85 and sunny
| [Wednesday 01 December 2010] [01:02:50] <guido_g>	and i need to go to the office soon *shudder*
| [Wednesday 01 December 2010] [01:03:27] <Nate75Sanders>	What kind of place do you work?
| [Wednesday 01 December 2010] [01:03:58] <guido_g>	i'm a freelancer, at the moment i'm working at a local bank
| [Wednesday 01 December 2010] [01:04:04] <Nate75Sanders>	I decided to work for a place that doesn't really do as much code (half code, half sysadmin for an oceanographic science team)
| [Wednesday 01 December 2010] [01:04:06] <Nate75Sanders>	it's been great
| [Wednesday 01 December 2010] [01:04:17] <guido_g>	sounds good
| [Wednesday 01 December 2010] [01:04:18] <Nate75Sanders>	i help them immensely and everything i do is magic
| [Wednesday 01 December 2010] [01:04:21] <Nate75Sanders>	and i have plenty of free time
| [Wednesday 01 December 2010] [01:04:25] <Nate75Sanders>	didn't expect this
| [Wednesday 01 December 2010] [01:04:34] <Nate75Sanders>	i used to work more dev jobs....
| [Wednesday 01 December 2010] [01:04:35] <guido_g>	sounds even better :)
| [Wednesday 01 December 2010] [01:04:39] <Nate75Sanders>	they just left me feeling bad
| [Wednesday 01 December 2010] [01:04:50] <Nate75Sanders>	turning the thing i loved into terrible terrible work
| [Wednesday 01 December 2010] [01:05:03] <Nate75Sanders>	come home.....hardly interested in the computer....
| [Wednesday 01 December 2010] [01:05:12] <Nate75Sanders>	now? i'm happy to dive in and work on something
| [Wednesday 01 December 2010] [01:05:17] <Nate75Sanders>	not tired at the end of a day
| [Wednesday 01 December 2010] [01:05:19] <guido_g>	that's the price to pay, i know that
| [Wednesday 01 December 2010] [01:05:24] <Nate75Sanders>	yeah
| [Wednesday 01 December 2010] [01:07:16] <guido_g>	more coffee
| [Wednesday 01 December 2010] [01:07:28] <Nate75Sanders>	indeed :)
| [Wednesday 01 December 2010] [01:07:34] <Nate75Sanders>	don't work too hard today....
| [Wednesday 01 December 2010] [01:07:36] <Nate75Sanders>	pace yourself
| [Wednesday 01 December 2010] [01:07:48] <guido_g>	hey, it's a bank
| [Wednesday 01 December 2010] [01:07:51] <Nate75Sanders>	your 6 hours is easily worth someone else's 9
| [Wednesday 01 December 2010] [01:07:58] <Nate75Sanders>	deep breaths
| [Wednesday 01 December 2010] [01:07:59] <Nate75Sanders>	;)
| [Wednesday 01 December 2010] [01:08:05] <guido_g>	ahhh... 
| [Wednesday 01 December 2010] [01:08:11] <Nate75Sanders>	mindfulness
| [Wednesday 01 December 2010] [01:08:23] <guido_g>	i should have mentioned that today is my weekend
| [Wednesday 01 December 2010] [01:08:28] <Nate75Sanders>	oh, nice
| [Wednesday 01 December 2010] [01:08:32] <guido_g>	doing only 3 days a week
| [Wednesday 01 December 2010] [01:08:35] <Nate75Sanders>	sweet
| [Wednesday 01 December 2010] [01:08:40] <guido_g>	yeah
| [Wednesday 01 December 2010] [01:08:40] <Nate75Sanders>	hey you have it good, then
| [Wednesday 01 December 2010] [01:09:01] <Nate75Sanders>	i'm about to go half-time/half-salary myself
| [Wednesday 01 December 2010] [01:09:04] <Nate75Sanders>	and move
| [Wednesday 01 December 2010] [01:09:11] <guido_g>	i'm surprised that it worked
| [Wednesday 01 December 2010] [01:09:22] <Nate75Sanders>	which part?
| [Wednesday 01 December 2010] [01:09:25] <guido_g>	as i said, it's a bank
| [Wednesday 01 December 2010] [01:09:31] <guido_g>	the part time thingy
| [Wednesday 01 December 2010] [01:09:37] <Nate75Sanders>	yeah
| [Wednesday 01 December 2010] [01:09:41] <Nate75Sanders>	i am surprised too
| [Wednesday 01 December 2010] [01:09:48] <guido_g>	there not _that_ flexible usually
| [Wednesday 01 December 2010] [01:09:52] <Nate75Sanders>	yep
| [Wednesday 01 December 2010] [01:09:53] <Nate75Sanders>	agreed
| [Wednesday 01 December 2010] [01:09:55] <Nate75Sanders>	my dad runs a bank
| [Wednesday 01 December 2010] [01:10:23] <guido_g>	ahh so you know a little
| [Wednesday 01 December 2010] [01:11:29] <Nate75Sanders>	so what do you do with your spare time?
| [Wednesday 01 December 2010] [01:12:13] <guido_g>	reading funny irc channels on obscure software things, linke brokerless messaging and such
| [Wednesday 01 December 2010] [01:12:28] <guido_g>	noone will ever need this shit! :)
| [Wednesday 01 December 2010] [01:13:36] <Nate75Sanders>	haha
| [Wednesday 01 December 2010] [01:13:38] <Nate75Sanders>	nice
| [Wednesday 01 December 2010] [01:16:06] <guido_g>	i'd have a project using all this fun stuff -- if i would be better sales guy
| [Wednesday 01 December 2010] [04:21:15] <mikko>	good morning
| [Wednesday 01 December 2010] [04:27:55] <CIA-20>	zeromq2: 03Martin Lucina 07maint * r289b1f5 10/ src/kqueue.cpp : 
| [Wednesday 01 December 2010] [04:27:55] <CIA-20>	zeromq2: Remove unnecessary cast in kevent_delete
| [Wednesday 01 December 2010] [04:27:55] <CIA-20>	zeromq2: Fixes the build on NetBSD where the compiler complains about casting NULL
| [Wednesday 01 December 2010] [04:27:55] <CIA-20>	zeromq2: to (int).
| [Wednesday 01 December 2010] [04:27:55] <CIA-20>	zeromq2: Signed-off-by: Martin Lucina <mato@kotelna.sk> - http://bit.ly/esACki
| [Wednesday 01 December 2010] [04:27:56] <CIA-20>	zeromq2: 03Martin Lucina 07master * r289b1f5 10/ src/kqueue.cpp : 
| [Wednesday 01 December 2010] [04:27:56] <CIA-20>	zeromq2: Remove unnecessary cast in kevent_delete
| [Wednesday 01 December 2010] [04:27:57] <CIA-20>	zeromq2: Fixes the build on NetBSD where the compiler complains about casting NULL
| [Wednesday 01 December 2010] [04:27:57] <CIA-20>	zeromq2: to (int).
| [Wednesday 01 December 2010] [04:27:58] <CIA-20>	zeromq2: Signed-off-by: Martin Lucina <mato@kotelna.sk> - http://bit.ly/esACki
| [Wednesday 01 December 2010] [04:27:58] <CIA-20>	zeromq2: 03Martin Sustrik 07master * r17d7e6e 10/ src/kqueue.cpp : 
| [Wednesday 01 December 2010] [04:27:59] <CIA-20>	zeromq2: Merge branch 'maint'
| [Wednesday 01 December 2010] [04:28:53] <CIA-20>	zeromq2:  Remove unnecessary cast in kevent_delete
| [Wednesday 01 December 2010] [04:28:53] <CIA-20>	zeromq2: Conflicts:
| [Wednesday 01 December 2010] [04:28:53] <CIA-20>	zeromq2:  src/kqueue.cpp
| [Wednesday 01 December 2010] [04:28:53] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/gqsKEN
| [Wednesday 01 December 2010] [04:34:02] <CIA-20>	zeromq2: 03Mikko Koppanen 07master * r5bb0a33 10/ (5 files in 2 dirs): (log message trimmed)
| [Wednesday 01 December 2010] [04:34:02] <CIA-20>	zeromq2: Prefix variables with "ac_zmq_"
| [Wednesday 01 December 2010] [04:34:02] <CIA-20>	zeromq2:  - Added a macro for checking clang compiler
| [Wednesday 01 December 2010] [04:34:02] <CIA-20>	zeromq2:  - Moved basic compiler checks to a macro
| [Wednesday 01 December 2010] [04:34:02] <CIA-20>	zeromq2:  - Added a macro for checking if compiler supports a flag
| [Wednesday 01 December 2010] [04:34:02] <CIA-20>	zeromq2:  - Added --enable-debug flag
| [Wednesday 01 December 2010] [04:34:03] <CIA-20>	zeromq2:  - Added a macro for running normal autoconf check with compiler flags
| [Wednesday 01 December 2010] [04:47:39] <m_>	exit
| [Wednesday 01 December 2010] [04:58:17] <CIA-20>	zeromq2: 03Martin Lucina 07master * rb70d628 10/ (11 files): 
| [Wednesday 01 December 2010] [04:58:18] <CIA-20>	zeromq2: Documentation updates for 2.1
| [Wednesday 01 December 2010] [04:58:18] <CIA-20>	zeromq2: - Clarify ZMQ_LINGER, zmq_close (), zmq_term () relationship
| [Wednesday 01 December 2010] [04:58:18] <CIA-20>	zeromq2: - New socket options
| [Wednesday 01 December 2010] [04:58:18] <CIA-20>	zeromq2: - Clarify thread safety of sockets and migration between threads
| [Wednesday 01 December 2010] [04:58:18] <CIA-20>	zeromq2: - Other minor and spelling fixes
| [Wednesday 01 December 2010] [04:58:18] <CIA-20>	zeromq2: Signed-off-by: Martin Lucina <mato@kotelna.sk> - http://bit.ly/hV39nD
| [Wednesday 01 December 2010] [05:12:05] <CIA-20>	zeromq2: 03Martin Lucina 07master * r520d621 10/ configure.in : 
| [Wednesday 01 December 2010] [05:12:05] <CIA-20>	zeromq2: Bump ABI version to 1:0:0 for ZeroMQ 2.1.0 release
| [Wednesday 01 December 2010] [05:12:05] <CIA-20>	zeromq2: Signed-off-by: Martin Lucina <mato@kotelna.sk> - http://bit.ly/h94kRn
| [Wednesday 01 December 2010] [05:34:28] <vaadim>	Hello, all.
| [Wednesday 01 December 2010] [05:34:57] <vaadim>	Anybody can to help me?
| [Wednesday 01 December 2010] [05:35:26] <vaadim>	I have a critical error in object.cpp file.
| [Wednesday 01 December 2010] [05:35:41] <mikko>	vaadim: what is the error?
| [Wednesday 01 December 2010] [05:36:01] <vaadim>	Version 2.0.10 for windows.
| [Wednesday 01 December 2010] [05:37:11] <vaadim>	I write test project for client and server applications. Run zmq::queue() function.
| [Wednesday 01 December 2010] [05:37:57] <mikko>	what is the actual error?
| [Wednesday 01 December 2010] [05:38:15] <vaadim>	This function call zmq_poll->zmq::app_thread_t::process_commands->process_bind and
| [Wednesday 01 December 2010] [05:38:45] <vaadim>	in  case command_t::bind:  process_bind (cmd_.args.bind.in_pipe, cmd_.args.bind.out_pipe,             blob_t (cmd_.args.bind.peer_identity,             cmd_.args.bind.peer_identity_size));
| [Wednesday 01 December 2010] [05:39:20] <vaadim>	and cmd_.args.bind.peer_identity have a Bad Ptr == 0x0000000
| [Wednesday 01 December 2010] [05:39:26] <vaadim>	crash
| [Wednesday 01 December 2010] [05:40:22] <mikko>	does the same thing happen with github master?
| [Wednesday 01 December 2010] [05:40:27] <mikko>	can you test?
| [Wednesday 01 December 2010] [05:40:38] <mikko>	and is this easy to reproduce?
| [Wednesday 01 December 2010] [05:42:28] <vaadim>	I was try latest version in github, but this version have another problems, and i revert to version 2.0.10 back
| [Wednesday 01 December 2010] [05:42:45] <vaadim>	I can show my test project
| [Wednesday 01 December 2010] [05:42:59] <mikko>	what is the problem you had with the latest version?
| [Wednesday 01 December 2010] [05:44:34] <vaadim>	Current version in github is stable ? I need stable version for commercial project.
| [Wednesday 01 December 2010] [05:45:28] <mikko>	what i am intersted in what are the problems you are seeing so that they can be fixed
| [Wednesday 01 December 2010] [05:45:44] <mikko>	i would like you to test the github master to see if the issue with the null pointer has been fixed already
| [Wednesday 01 December 2010] [05:47:32] <vaadim>	OK. I will try master from github again. And I will come back with another bag's :)
| [Wednesday 01 December 2010] [05:47:52] <vaadim>	Thank you for help :)
| [Wednesday 01 December 2010] [05:52:53] <CIA-20>	zeromq2: 03Steven McCoy 07master * r4a3ed39 10/ (3 files in 2 dirs): 
| [Wednesday 01 December 2010] [05:52:53] <CIA-20>	zeromq2: Bump OpenPGM to 5.0.92.
| [Wednesday 01 December 2010] [05:52:53] <CIA-20>	zeromq2: Signed-off-by: Steven McCoy <steven.mccoy@miru.hk> - http://bit.ly/fLKN5H
| [Wednesday 01 December 2010] [05:57:05] <Steve-o>	thx Mato
| [Wednesday 01 December 2010] [05:57:31] <CIA-20>	zeromq2: 03Martin Lucina 07master * rabc8b5e 10/ NEWS : 
| [Wednesday 01 December 2010] [05:57:31] <CIA-20>	zeromq2: Update NEWS file for 2.1.0 release
| [Wednesday 01 December 2010] [05:57:31] <CIA-20>	zeromq2: Signed-off-by: Martin Lucina <mato@kotelna.sk> - http://bit.ly/hXdp5N
| [Wednesday 01 December 2010] [06:16:40] <rgl>	w00t 2.1 has hit the streets?
| [Wednesday 01 December 2010] [06:16:48] <mato>	almost
| [Wednesday 01 December 2010] [06:16:59] <mato>	due to DNS issues the announcement will go out this evening
| [Wednesday 01 December 2010] [06:17:06] <mato>	but it's in Git anyhow :-)
| [Wednesday 01 December 2010] [06:18:57] <mikko>	ill run daily builds now just to see that everything works
| [Wednesday 01 December 2010] [06:19:03] <rgl>	:)
| [Wednesday 01 December 2010] [06:19:28] <mikko>	building now
| [Wednesday 01 December 2010] [06:19:38] <rgl>	I just noticed Sockets may now be migrated between OS threads, as long as the
| [Wednesday 01 December 2010] [06:19:38] <rgl>	 application ensures that a full memory barrier is issued.  ... are there any examples how to do it?
| [Wednesday 01 December 2010] [06:21:02] <mikko>	is 2.1.0 going out as alpha or beta?
| [Wednesday 01 December 2010] [06:22:38] <rgl>	from the NEWS files its Beta
| [Wednesday 01 December 2010] [06:24:19] <sustrik>	rgl: when you migrate a thread you have no notify the other thread somehow
| [Wednesday 01 December 2010] [06:24:42] <sustrik>	the mechanism you use for the notfication will execute the barrier
| [Wednesday 01 December 2010] [06:24:53] <sustrik>	unless you are doing some black magic
| [Wednesday 01 December 2010] [06:26:08] <rgl>	I see. alright :D
| [Wednesday 01 December 2010] [06:33:07] <mikko>	success on all builds this far
| [Wednesday 01 December 2010] [06:33:33] <sustrik>	goodo
| [Wednesday 01 December 2010] [06:34:20] <mikko>	icc failed
| [Wednesday 01 December 2010] [06:34:22] <mikko>	let's see
| [Wednesday 01 December 2010] [06:34:37] <mikko>	it might be the shutdown stress test failing
| [Wednesday 01 December 2010] [06:34:55] <mikko>	Bad file descriptor
| [Wednesday 01 December 2010] [06:34:55] <mikko>	nbytes != -1 (tcp_socket.cpp:197)
| [Wednesday 01 December 2010] [06:34:56] <mikko>	yes
| [Wednesday 01 December 2010] [06:35:58] <sustrik>	yep, known issue
| [Wednesday 01 December 2010] [06:36:53] <rgl>	mikko, where is the build system? got url?
| [Wednesday 01 December 2010] [06:37:03] <mikko>	http://build.valokuva.org/
| [Wednesday 01 December 2010] [06:38:12] <mikko>	i got my eye on sunfire server on ebay
| [Wednesday 01 December 2010] [06:38:18] <mikko>	to add sparc into the build system
| [Wednesday 01 December 2010] [06:38:36] <Steve-o>	incredibly cheap these days, ~US$100
| [Wednesday 01 December 2010] [06:39:00] <Steve-o>	but also slow as lard, 100mb NICs often
| [Wednesday 01 December 2010] [06:39:20] <mikko>	this one is Dual 1.3Ghz Processors
| [Wednesday 01 December 2010] [06:39:29] <mikko>	i don't mind 100mb nic as it's just for building
| [Wednesday 01 December 2010] [06:39:32] <mikko>	not really for testing
| [Wednesday 01 December 2010] [06:40:17] <rgl>	mikko, no msvc build?
| [Wednesday 01 December 2010] [06:40:26] <Steve-o>	memory is the most important though, don't skimp on that
| [Wednesday 01 December 2010] [06:40:33] <mikko>	rgl: haven't got a windows running
| [Wednesday 01 December 2010] [06:40:41] <mikko>	Steve-o: it comes with 4GB
| [Wednesday 01 December 2010] [06:40:55] <vaadim>	Hello, I am here again.
| [Wednesday 01 December 2010] [06:41:07] <mikko>	the annoyance is that the build machines are running in finland
| [Wednesday 01 December 2010] [06:41:10] <mikko>	and i live in london
| [Wednesday 01 December 2010] [06:41:18] <mikko>	need to either host it here or ship it over
| [Wednesday 01 December 2010] [06:41:42] <sustrik>	does it make any difference?
| [Wednesday 01 December 2010] [06:41:43] <rgl>	mikko, http://build.valokuva.org/view/clrzmq/ is using mono then?
| [Wednesday 01 December 2010] [06:41:51] <mikko>	rgl: yes
| [Wednesday 01 December 2010] [06:41:51] <vaadim>	mikko: i try the current version from github in my test project
| [Wednesday 01 December 2010] [06:41:59] <mikko>	vaadim: ok
| [Wednesday 01 December 2010] [06:42:12] <mikko>	sustrik: i got free hosting in finland
| [Wednesday 01 December 2010] [06:42:16] <mikko>	that's the only difference
| [Wednesday 01 December 2010] [06:42:42] <sustrik>	i see
| [Wednesday 01 December 2010] [06:43:09] <rgl>	mikko, can you add clrmq2 into the clrmq tab too?
| [Wednesday 01 December 2010] [06:43:32] <mikko>	rgl: done
| [Wednesday 01 December 2010] [06:43:42] <mikko>	the regex for adding jobs there was outdated
| [Wednesday 01 December 2010] [06:43:45] <vaadim>	My server stoped with error while i try break zmq_device by call zmq_term() for kill context
| [Wednesday 01 December 2010] [06:43:46] <mikko>	clrzmq-.*
| [Wednesday 01 December 2010] [06:43:53] <rgl>	thanks :)
| [Wednesday 01 December 2010] [06:44:10] <mikko>	sustrik: what is the clean way to stop zmq device?
| [Wednesday 01 December 2010] [06:44:24] <mikko>	vaadim: i am not sure if that is the way to stop a device
| [Wednesday 01 December 2010] [06:46:21] <sustrik>	mikko: Ctrl+C?
| [Wednesday 01 December 2010] [06:46:33] <sustrik>	there's no remote management for devices yet
| [Wednesday 01 December 2010] [06:46:40] <vaadim>	I read this way in your mailing list archiew
| [Wednesday 01 December 2010] [06:47:00] <vaadim>	wait a moment...
| [Wednesday 01 December 2010] [06:47:51] <vaadim>	http://thread.gmane.org/gmane.network.zeromq.devel/2338/focus=2340
| [Wednesday 01 December 2010] [06:48:30] <sustrik>	vaadim: the devices are dumb pieces of code
| [Wednesday 01 December 2010] [06:48:43] <sustrik>	basically just a loop that reads from one socket and writes to another one
| [Wednesday 01 December 2010] [06:49:00] <sustrik>	if you want a better functionality, like a remote management
| [Wednesday 01 December 2010] [06:49:08] <sustrik>	you can add it there
| [Wednesday 01 December 2010] [06:51:42] <vaadim>	Sorry, i'm not understand, how to stop loop in device. I need to stop both sockets ?
| [Wednesday 01 December 2010] [06:52:51] <sustrik>	you just break out of the loop
| [Wednesday 01 December 2010] [06:53:01] <sustrik>	that's it
| [Wednesday 01 December 2010] [06:53:16] <vaadim>	How? Kill thread?
| [Wednesday 01 December 2010] [06:53:37] <sustrik>	while (true) {
| [Wednesday 01 December 2010] [06:53:39] <sustrik>	...
| [Wednesday 01 December 2010] [06:53:50] <sustrik>	    if (...)
| [Wednesday 01 December 2010] [06:53:52] <sustrik>	       break;
| [Wednesday 01 December 2010] [06:53:55] <sustrik>	...
| [Wednesday 01 December 2010] [06:53:55] <sustrik>	}
| [Wednesday 01 December 2010] [06:55:11] <vaadim>	But zmq_device(ZMQ_QUEUE, clients, workers); bon't return control, and i can't make loop myself.
| [Wednesday 01 December 2010] [06:55:26] <sustrik>	have a look at the source code
| [Wednesday 01 December 2010] [06:55:27] <mikko>	vaadim: have you looked at the device code?
| [Wednesday 01 December 2010] [06:55:47] <sustrik>	you just create your own device
| [Wednesday 01 December 2010] [06:55:55] <sustrik>	and modify it in any way you want
| [Wednesday 01 December 2010] [06:57:38] <vaadim>	Yeah, well, I'm gonna go build my own device, with blackjack and hookers. In fact, forget the device! :)
| [Wednesday 01 December 2010] [06:59:54] <vaadim>	Ok, i can append third parameter to my_zmq_device with stop socket.
| [Wednesday 01 December 2010] [07:00:25] <vaadim>	Thank's.
| [Wednesday 01 December 2010] [11:06:31] <Remoun>	hi
| [Wednesday 01 December 2010] [11:06:36] <Remoun>	I'm perusing the guide right now, but I thought I'd ask ahead: Can I overlay some sort of authentication mechanism for workers in a 0MQ-based system?
| [Wednesday 01 December 2010] [11:07:01] <mikko>	Remoun: i don't see why what would prevent you from doing that
| [Wednesday 01 December 2010] [11:07:29] <Remoun>	I don't see any reason, either; I just have no idea how yet
| [Wednesday 01 December 2010] [11:07:41] <Remoun>	But it should be doable (in a transparent manner), right?
| [Wednesday 01 December 2010] [11:07:52] <mikko>	what do you mean by transparent?
| [Wednesday 01 December 2010] [11:07:59] <mikko>	you would need to implement it in your code
| [Wednesday 01 December 2010] [11:08:06] <Remoun>	of course
| [Wednesday 01 December 2010] [11:08:43] <Remoun>	basically, layering the auth on top of the sockets
| [Wednesday 01 December 2010] [11:08:59] <Remoun>	So that I don't have to decorate every bit of code using 0MQ sockets with auth handling
| [Wednesday 01 December 2010] [11:09:32] <mikko>	there are plenty of ways to approach the problem
| [Wednesday 01 December 2010] [11:09:33] <Remoun>	... Does that make sense?
| [Wednesday 01 December 2010] [11:09:44] <mikko>	you could do a small device that handles the authentication
| [Wednesday 01 December 2010] [11:09:51] <mikko>	and forwards the messages using inproc
| [Wednesday 01 December 2010] [11:10:21] <mikko>	so your client code would communicate with inproc and the device decorates with authentication info and forwards the messages
| [Wednesday 01 December 2010] [11:13:51] <Remoun>	sounds good
| [Wednesday 01 December 2010] [11:13:54] <Remoun>	thanks mikko 
| [Wednesday 01 December 2010] [11:24:14] <shales>	hi, has anyone used eventlet with zmq? I'm wondering if or how eventlet works with zmq.REP sockets or do I have to switch to XREP sockets to avoid the state kept in the REP socket from messing up with multiple threads?
| [Wednesday 01 December 2010] [11:30:02] <mikko>	shales: sorry, no idea what eventlet is 
| [Wednesday 01 December 2010] [11:30:06] <mikko>	shales: is it ruby?
| [Wednesday 01 December 2010] [11:31:00] <mikko>	ah, python
| [Wednesday 01 December 2010] [11:31:03] <shales>	python
| [Wednesday 01 December 2010] [11:31:40] <shales>	it's ok, someone on #eventlet just gave me an easy workaround
| [Wednesday 01 December 2010] [11:31:58] <shales>	just give each greenthread its own REP socket
| [Wednesday 01 December 2010] [13:47:25] <jhawk28>	Hello. Congrats on the 2.1.0 beta!
| [Wednesday 01 December 2010] [14:58:58] <mikko>	mato: hmm, does 3.4.6 report that it supports dso visibility?
| [Wednesday 01 December 2010] [15:00:04] <mikko>	#   elif (defined __GNUC__ && __GNUC__ >= 4) || defined __INTEL_COMPILER
| [Wednesday 01 December 2010] [15:00:09] <mikko>	this error reported makes no sense
| [Wednesday 01 December 2010] [15:00:21] <mato>	mikko: it shouldn't, i'm just replying asking for more info
| [Wednesday 01 December 2010] [15:00:47] <mato>	unless RHAT borked it of course :-)
| [Wednesday 01 December 2010] [15:01:00] <mikko>	but in any case it should not pass __GNUC__ >= 4
| [Wednesday 01 December 2010] [15:01:13] <mato>	ISTR some problems related to OpenPGM use of __attribute__((visibility)) on old RHAT also
| [Wednesday 01 December 2010] [15:01:36] <mikko>	downloading centos4 now
| [Wednesday 01 December 2010] [15:01:42] <mato>	:-)
| [Wednesday 01 December 2010] [15:01:59] 	 * mato is not at the office, no VM-capable hardware here ...
| [Wednesday 01 December 2010] [15:02:38] <mikko>	http://cgi.ebay.co.uk/SUN-MICRO-SUNFIRE-V210-RACKMOUNT-SERVER-/230553957004?pt=UK_Computing_Networking_SM&hash=item35ae16328c
| [Wednesday 01 December 2010] [15:02:41] <mikko>	i got my eye on that
| [Wednesday 01 December 2010] [15:02:44] <mikko>	to add to build cluster
| [Wednesday 01 December 2010] [15:02:57] <mikko>	if the price doesn't go up much i'll try to snatch it
| [Wednesday 01 December 2010] [15:04:31] <prokos>	does ZMQ_SUBSCRIBE filter on the client side or the server side? 
| [Wednesday 01 December 2010] [15:04:49] <mikko>	prokos: client side
| [Wednesday 01 December 2010] [15:05:00] <mato>	heh, I got offered a Sun Fire 15k for free some time ago, declined on the grounds that I don't have an empty data center and free electricity to run it...
| [Wednesday 01 December 2010] [15:05:04] <mikko>	if by client you mean the subscriber
| [Wednesday 01 December 2010] [15:05:28] <mikko>	mato: i'm hoping to put this in the server room at work
| [Wednesday 01 December 2010] [15:05:36] <mikko>	and as a backup plan im gonna ship it to finland
| [Wednesday 01 December 2010] [15:06:02] <mato>	well, 50 GBP is damn cheap
| [Wednesday 01 December 2010] [15:06:33] <prokos>	yes i mean the subscriber.. Is there a reason to not filter on the publisher side?
| [Wednesday 01 December 2010] [15:07:00] <mikko>	prokos: it's very complicated to implement but i think it's on the list of things to do
| [Wednesday 01 December 2010] [15:11:13] <jhawk28>	has anyone seen this: http://sna-projects.com/kafka/
| [Wednesday 01 December 2010] [15:20:02] <mato>	mikko: I've forwarded you the outputs Chris Patti sent me just now
| [Wednesday 01 December 2010] [15:20:30] <mato>	mikko: It looks to me like his GCC claims to support -fvisibility=hidden but the results are completely bogus
| [Wednesday 01 December 2010] [15:20:54] <mato>	mikko: the symbol table in libzmq.so is missing anything which would normally be hidden
| [Wednesday 01 December 2010] [15:21:17] <mikko>	mato: yes
| [Wednesday 01 December 2010] [15:21:34] <mato>	mikko: looks like we need an autoconf check for "Checking to see if g++ -fvisibility=hidden actually works" :-)
| [Wednesday 01 December 2010] [15:21:36] <mikko>	i got centos4 running soon
| [Wednesday 01 December 2010] [15:22:23] <mato>	no point in fighting with getting it to work on buggy/old compilers, but it shouldn't break completely...
| [Wednesday 01 December 2010] [15:23:42] <mikko>	mato: does it support the pragma?
| [Wednesday 01 December 2010] [15:23:48] <mikko>	if it supports -fvisibility
| [Wednesday 01 December 2010] [15:24:11] <mato>	probably not
| [Wednesday 01 December 2010] [15:24:23] <mato>	or it's some bastardized RHAT version
| [Wednesday 01 December 2010] [15:26:06] <mikko>	got centos4 running now
| [Wednesday 01 December 2010] [15:27:36] <mikko>	yum is _slow_ on centos4
| [Wednesday 01 December 2010] [15:36:37] <mikko>	mato: gcc version 3.4.6 20060404 (Red Hat 3.4.6-11)
| [Wednesday 01 December 2010] [15:36:43] <mikko>	visibility works
| [Wednesday 01 December 2010] [15:36:52] <mikko>	no wait
| [Wednesday 01 December 2010] [15:36:58] <mikko>	it supports -fvisibility
| [Wednesday 01 December 2010] [15:37:04] <mikko>	but ignores the attribute
| [Wednesday 01 December 2010] [15:37:40] <mato>	geez
| [Wednesday 01 December 2010] [15:37:46] <mikko>	hmm
| [Wednesday 01 December 2010] [15:37:50] <mikko>	thats not completely true
| [Wednesday 01 December 2010] [15:38:00] <mikko>	https://gist.github.com/b2f2ef8f5bc92d2688b3
| [Wednesday 01 December 2010] [15:38:51] <mato>	well, in any case, we can't detect this case in zmq.h sanely
| [Wednesday 01 December 2010] [15:39:03] <mato>	so we need to account for it in the autoconf tests somehowe
| [Wednesday 01 December 2010] [15:40:06] <mato>	I reckon for now the easiest thing is to explicitly check the GCC version
| [Wednesday 01 December 2010] [15:40:23] <mato>	and not enable -fvisibility if it's < 4
| [Wednesday 01 December 2010] [15:40:28] <mikko>	yes, i was thinking the same
| [Wednesday 01 December 2010] [15:40:35] <mikko>	let me wrap a macro for that
| [Wednesday 01 December 2010] [15:55:12] <mikko>	brb
| [Wednesday 01 December 2010] [16:17:51] <prokos>	f
| [Wednesday 01 December 2010] [17:10:04] <mikko>	mato: take a look at http://valokuva.org/~mikko/visibility.patch when you got time
| [Wednesday 01 December 2010] [17:41:25] <jhawk28_>	hey sustrik
| [Wednesday 01 December 2010] [17:43:24] <sustrik>	hi
| [Wednesday 01 December 2010] [17:47:32] <Guthur>	is there tests for the new features?
| [Wednesday 01 December 2010] [17:47:38] <Guthur>	in 2.1.0
| [Wednesday 01 December 2010] [19:19:13] <erickt>	Hi #zeromq! congrats on 2.1.0. I was wondering, did sys://log make it into 2.1.0?
| [Wednesday 01 December 2010] [19:20:47] <erickt>	and if so, what is getting logged?
| [Wednesday 01 December 2010] [20:54:02] <Remoun>	How can I get the remote IP (of the sender) when receiving over TCP?
| [Wednesday 01 December 2010] [23:20:06] <DanielHolth>	any word on a ctypes zeromq binding?
| [Wednesday 01 December 2010] [23:20:11] <DanielHolth>	for Python?
| [Thursday 02 December 2010] [02:32:59] <delaney__>	has anyone had any luck getting pyzmq to build with 3.1?
| [Thursday 02 December 2010] [02:34:03] <delaney__>	trying with the 2.0.10
| [Thursday 02 December 2010] [02:53:58] <sustrik>	delaney: autobuilds: http://build.valokuva.org/
| [Thursday 02 December 2010] [02:54:33] <sustrik>	Remoun: you can't
| [Thursday 02 December 2010] [02:55:04] <sustrik>	erickt: it have made it in
| [Thursday 02 December 2010] [02:55:16] <sustrik>	you can subscribe to it
| [Thursday 02 December 2010] [02:55:23] <sustrik>	but nothing is logged yet :)
| [Thursday 02 December 2010] [02:59:16] <delaney__>	sustrik that looks cool but doesn't seem to have a link to the zmq package, or is that not available?  http://build.valokuva.org/view/pyzmq/job/pyzmq-master_ZeroMQ2-master_GCC/lastBuild/
| [Thursday 02 December 2010] [02:59:49] <sustrik>	nope, it doesn't create packages
| [Thursday 02 December 2010] [03:00:05] <sustrik>	but it shows that the pyzmq can be built with master
| [Thursday 02 December 2010] [03:03:33] <delaney__>	oh i don't doubt it
| [Thursday 02 December 2010] [03:03:50] <delaney__>	actually just got it working with 32bit visual studio 2008
| [Thursday 02 December 2010] [03:04:07] <delaney__>	but can't seem to with 64bit visual studio 2010
| [Thursday 02 December 2010] [03:09:09] <sustrik>	report the problem on the mailing list then...
| [Thursday 02 December 2010] [03:09:34] <sustrik>	i cannot really help myself is a don't have win64
| [Thursday 02 December 2010] [03:14:27] <Steve-o>	sustrik, hope you like the bug I found on MSVC :-)
| [Thursday 02 December 2010] [03:23:34] <sustrik>	Steve-o: haven't read all emails yet
| [Thursday 02 December 2010] [03:23:39] <sustrik>	which one is that?
| [Thursday 02 December 2010] [03:24:13] <Steve-o>	ok, end of "encoder hanging in remote_thr tests" thread.  
| [Thursday 02 December 2010] [03:24:29] <Steve-o>	compiler over-optimisation
| [Thursday 02 December 2010] [03:25:01] <sustrik>	uh, you've sent a patch
| [Thursday 02 December 2010] [03:25:16] <Steve-o>	it's a workaround, not a real patch
| [Thursday 02 December 2010] [03:25:31] <sustrik>	anyway, mark the emails containing patches with [PATCH]
| [Thursday 02 December 2010] [03:25:31] <Steve-o>	I have no idea what is a good solution, leave that up to you
| [Thursday 02 December 2010] [03:25:44] <sustrik>	otherwise it's pretty easy to forget about it
| [Thursday 02 December 2010] [03:26:01] <Steve-o>	I've dumped a Win32 API call in there, it's not useful to commit it
| [Thursday 02 December 2010] [03:26:10] <sustrik>	ok, i see
| [Thursday 02 December 2010] [03:26:52] <Steve-o>	still working on why linger isn't working
| [Thursday 02 December 2010] [03:27:06] <Steve-o>	is it supposed to on pub sockets?
| [Thursday 02 December 2010] [03:27:25] <sustrik>	Steve-o: i would say the problem is that OpenPGM doesn't have linger
| [Thursday 02 December 2010] [03:27:32] <sustrik>	so the LINGER is set on 0MQ level
| [Thursday 02 December 2010] [03:27:42] <sustrik>	when 0MQ pushes all data to OpenPGM
| [Thursday 02 December 2010] [03:27:53] <sustrik>	it considers the work done
| [Thursday 02 December 2010] [03:27:56] <sustrik>	and exits
| [Thursday 02 December 2010] [03:28:01] <sustrik>	which closes the process
| [Thursday 02 December 2010] [03:28:07] <Steve-o>	the problem here is 0MQ isn't sending anything to PGM
| [Thursday 02 December 2010] [03:28:10] <sustrik>	thus dropping the PGM tx buffers
| [Thursday 02 December 2010] [03:28:14] <sustrik>	ah
| [Thursday 02 December 2010] [03:28:27] <Steve-o>	it only init's the pgm_socket object
| [Thursday 02 December 2010] [03:28:31] <Steve-o>	the destroys it
| [Thursday 02 December 2010] [03:28:41] <Steve-o>	core bug
| [Thursday 02 December 2010] [03:28:50] <sustrik>	ok, i'll give it a look
| [Thursday 02 December 2010] [03:28:51] <Steve-o>	or "feature"
| [Thursday 02 December 2010] [03:29:08] <Steve-o>	check your mails and get back to me on the list later
| [Thursday 02 December 2010] [03:29:15] <sustrik>	sure, will do
| [Thursday 02 December 2010] [05:01:25] <PiotrSikora>	guys, are there any complete examples/guides about integrating zeromq with existing event poll using ZMQ_FD & ZMQ_EVENTS?
| [Thursday 02 December 2010] [05:20:41] <sustrik_>	PiotrSikora: have a look at src/zmq.cpp
| [Thursday 02 December 2010] [05:20:51] <sustrik_>	there's implementation of zmq_poll
| [Thursday 02 December 2010] [05:21:00] <sustrik_>	which uses ZMQ_FD and ZMQ_EVENTS underneath
| [Thursday 02 December 2010] [05:21:33] <sustrik_>	combined with either select(2) or poll(2)
| [Thursday 02 December 2010] [05:25:47] <PiotrSikora>	sustrik_: yeah, i looked at it... let me clarify...
| [Thursday 02 December 2010] [05:27:34] <PiotrSikora>	sustrik_: it is my understanding that in order to hook ZMQ into existing event look (kevent, epoll, etc) i need to get existing fd via getsockopt(ZMQ_FD), then when system will notice my about event on that fd, I need to verify that there is complete ZMQ message available via getsockopt(ZMQ_EVENTS)
| [Thursday 02 December 2010] [05:27:54] <PiotrSikora>	however i'm lost at how can i retrieve this message without blocking?
| [Thursday 02 December 2010] [05:28:02] <PiotrSikora>	zmq_poll? doesn't look like
| [Thursday 02 December 2010] [05:29:11] <PiotrSikora>	or would zmq_recv() be ok?
| [Thursday 02 December 2010] [05:29:35] <sustrik_>	zmq_recv()
| [Thursday 02 December 2010] [05:29:40] <sustrik_>	you know it's there
| [Thursday 02 December 2010] [05:29:50] <sustrik_>	so you just call zmq_recv() and you'll get it
| [Thursday 02 December 2010] [05:30:40] <PiotrSikora>	ok, thx :)
| [Thursday 02 December 2010] [05:31:07] <PiotrSikora>	seems like those new features make it extremely easy to integrate now
| [Thursday 02 December 2010] [05:31:30] <PiotrSikora>	i remember i looked into this (integrating with existing event loop) a while ago and it seemd rather impossible to do
| [Thursday 02 December 2010] [06:09:21] <mikko>	this is odd
| [Thursday 02 December 2010] [06:09:31] <mikko>	out of the box gcc 3.4.6 does not support -fvisibility=hidden flag
| [Thursday 02 December 2010] [06:09:44] <mikko>	but redhat "fixed" version does support it but messes up visibility
| [Thursday 02 December 2010] [06:55:18] <sustrik_>	Steve-o: hi
| [Thursday 02 December 2010] [06:55:26] <Steve-o>	hi
| [Thursday 02 December 2010] [06:55:40] <sustrik_>	aren't there 2 different problems there?
| [Thursday 02 December 2010] [06:55:49] <sustrik_>	one of them is solved by sleep()
| [Thursday 02 December 2010] [06:56:11] <Steve-o>	at least 2 possibly more
| [Thursday 02 December 2010] [06:56:26] <sustrik_>	yep
| [Thursday 02 December 2010] [06:56:35] <sustrik_>	so let's solve these seaprately
| [Thursday 02 December 2010] [06:56:49] <Steve-o>	the memory barrier / fence is the most odd
| [Thursday 02 December 2010] [06:57:08] <sustrik_>	mikko: mato says you are right
| [Thursday 02 December 2010] [06:57:15] <sustrik_>	and it's RH bug
| [Thursday 02 December 2010] [06:57:29] <sustrik_>	Steve-o: yes
| [Thursday 02 December 2010] [06:57:42] <sustrik_>	anyway, one problem that's pretty obvious is that 0MQ doesn't wait for OpenPGM when terminating
| [Thursday 02 December 2010] [06:58:09] <sustrik_>	can we solve that one somehow?
| [Thursday 02 December 2010] [06:58:22] <Steve-o>	isn't something broken in the linger implementation?
| [Thursday 02 December 2010] [06:58:37] <sustrik_>	maybe, but that's not the point
| [Thursday 02 December 2010] [06:58:52] <sustrik_>	the point is that 0mq doesn't know when openpgm have sent all the data
| [Thursday 02 December 2010] [06:59:06] <Steve-o>	ok three problems
| [Thursday 02 December 2010] [06:59:26] <sustrik_>	ok
| [Thursday 02 December 2010] [06:59:34] <Steve-o>	#1 0mq does not flush complete batch of messages, instead it only sends first message
| [Thursday 02 December 2010] [06:59:50] <Steve-o>	#2 a MSVC 2010 compiler optimisation bug causes encoder.get_data to hang
| [Thursday 02 December 2010] [07:00:13] <Steve-o>	#3 short PUB runs followed by zmq_term do not plug the underlying transport
| [Thursday 02 December 2010] [07:00:38] <mikko>	sustrik_: i think i got a feasible patch
| [Thursday 02 December 2010] [07:01:20] <mikko>	ill talk with mato when he is back
| [Thursday 02 December 2010] [07:01:25] <sustrik_>	sure
| [Thursday 02 December 2010] [07:02:15] <Steve-o>	note #1 & #3 may also be MSVC bugs, no idea
| [Thursday 02 December 2010] [07:03:00] <sustrik_>	Steve-o: ok, can it be reproduced on a single box?
| [Thursday 02 December 2010] [07:03:31] <Steve-o>	#3 is really easy, just run remote_thr with size=100 and count=1 ... 2000
| [Thursday 02 December 2010] [07:03:55] <Steve-o>	i added printf statements to every call in pgm_sender.cpp to see what if ever is called
| [Thursday 02 December 2010] [07:04:37] <Steve-o>	#2 randomly occurs when data is actually sent
| [Thursday 02 December 2010] [07:04:48] <Steve-o>	#1 not so important as the others
| [Thursday 02 December 2010] [07:06:01] <Steve-o>	of course it will be more annoying if it is hardware dependent
| [Thursday 02 December 2010] [07:06:50] <sustrik_>	so let's start with #3
| [Thursday 02 December 2010] [07:07:00] <sustrik_>	pgm?
| [Thursday 02 December 2010] [07:07:02] <sustrik_>	epgm?
| [Thursday 02 December 2010] [07:07:04] <sustrik_>	loopback?
| [Thursday 02 December 2010] [07:07:07] <Steve-o>	epgm,
| [Thursday 02 December 2010] [07:07:44] <sustrik_>	does it happen on linux as well?
| [Thursday 02 December 2010] [07:07:53] <Steve-o>	haven't checked yet
| [Thursday 02 December 2010] [07:08:26] <sustrik_>	let me try
| [Thursday 02 December 2010] [07:08:30] <Steve-o>	i only saw #1 on linux so far
| [Thursday 02 December 2010] [07:13:22] <Steve-o>	linux looks fine here for count=1 
| [Thursday 02 December 2010] [07:14:27] <Steve-o>	LD_LIBRARY_PATH=src/.libs/ ./perf/.libs/remote_thr --rate-limit 100 "epgm://eth0;239.192.0.1:7500" 100 1
| [Thursday 02 December 2010] [07:14:41] <Steve-o>	sends 1 packet as expected
| [Thursday 02 December 2010] [07:22:51] <sustrik_>	so it only happens on windows, right?
| [Thursday 02 December 2010] [07:23:04] <sustrik_>	i don't have a win box here
| [Thursday 02 December 2010] [07:26:50] <Steve-o>	appears so, just tested on another box and reproduced it
| [Thursday 02 December 2010] [07:30:50] <Steve-o>	that's why I'm wondering if it is another MSVC compiler optimisation bug
| [Thursday 02 December 2010] [07:31:10] <Steve-o>	you really need some heavy unit testing to catch annoying features like this
| [Thursday 02 December 2010] [07:31:50] <sustrik_>	Steve-o: yes, but win32 is a platform that i am not really using
| [Thursday 02 December 2010] [07:35:18] <Steve-o>	unfortunately most VMs are too helpful either for multicast testing
| [Thursday 02 December 2010] [07:37:01] <Steve-o>	I think it's still only limited to ESX virtual NICs
| [Thursday 02 December 2010] [07:37:38] <sustrik_>	no idea
| [Thursday 02 December 2010] [07:38:53] <sustrik_>	anyway, the obvious problem is that the whole win/pgm thing is not going to move forward at any reasonable pace if there's no infrastructure to test it on
| [Thursday 02 December 2010] [07:43:52] <Steve-o>	yup, and I guess some assistance in testing the .net libraries would help developers too
| [Thursday 02 December 2010] [07:46:18] <Steve-o>	if MSVC is causing this there should be negative consequences on the TCP transport too
| [Thursday 02 December 2010] [07:50:29] <Steve-o>	I'm currently using 2008R2 trial on a server and Windows 7 on desktop, but on separate networks :-)
| [Thursday 02 December 2010] [09:00:35] <mikko>	mato: found it
| [Thursday 02 December 2010] [09:00:35] <mikko>	- backport C++ visibility patches, -fvisibility*, #pragma GCC visibility
| [Thursday 02 December 2010] [09:00:44] <mikko>	from RHEL gcc changelog
| [Thursday 02 December 2010] [09:10:28] <Guthur>	i there any caveats with having multiple contexts in the one application?
| [Thursday 02 December 2010] [09:10:49] <Guthur>	i/is
| [Thursday 02 December 2010] [09:11:16] <mato>	mikko: Thought so ... usual silly attitude from RHAT
| [Thursday 02 December 2010] [09:11:48] <mato>	mikko: Anyway, I'd suggest going with the approach in your patch for now (don't enable it at all on GCC < 4)
| [Thursday 02 December 2010] [09:11:59] <mato>	mikko: I've not reviewed it yet in detail, busy today...
| [Thursday 02 December 2010] [09:14:06] <mikko>	mato: check this
| [Thursday 02 December 2010] [09:14:14] <mikko>	http://valokuva.org/~mikko/visibility-rhel.patch
| [Thursday 02 December 2010] [09:14:18] <mikko>	this is the latest
| [Thursday 02 December 2010] [09:14:29] <mikko>	it uses AC_COMPILE_IFELSE to test the visibility
| [Thursday 02 December 2010] [09:14:54] <mikko>	the AC_COMPILE_IFELSE should fail if the compiler is not one of the defined
| [Thursday 02 December 2010] [09:15:09] <mikko>	additionally it uses 'nm' to check that the symbol actually has the expected visibility
| [Thursday 02 December 2010] [09:16:13] <mato>	mikko: 'nm' is not a good idea due to non-portability of it's output
| [Thursday 02 December 2010] [09:16:23] <mato>	mikko: e.g. solaris nm by default produces completely different output
| [Thursday 02 December 2010] [09:16:57] <mato>	mikko: if you really want to go the whole hog and actually test if -fvisibility works, then you'd need to compile a shared object and try and link against it
| [Thursday 02 December 2010] [09:17:04] <mato>	mikko: not sure if that's worth the work...
| [Thursday 02 December 2010] [09:17:33] <mato>	mikko: since compiling a shared lib would need to be done thru libtool to be portable, etc etc.
| [Thursday 02 December 2010] [09:18:20] <mato>	mikko: why not just stick with the bruteforce approach for now and don't even try -fvisibility on GCC < 4?
| [Thursday 02 December 2010] [09:18:25] <mikko>	mato: nm format is defined in posix
| [Thursday 02 December 2010] [09:18:34] <mikko>	not sure if everyone follows that htough
| [Thursday 02 December 2010] [09:18:36] <mato>	mikko: Yes, but not everyone follows thhat
| [Thursday 02 December 2010] [09:18:57] <mikko>	ok
| [Thursday 02 December 2010] [09:19:00] <mikko>	ill remove the nm part
| [Thursday 02 December 2010] [09:19:12] <mikko>	the AC_TRY_COMPILE should still fail with gcc 4<
| [Thursday 02 December 2010] [09:19:19] <mikko>	gcc <4
| [Thursday 02 December 2010] [09:20:01] <mikko>	let me update the patch
| [Thursday 02 December 2010] [09:20:42] <mikko>	mato: you mean something like this:http://valokuva.org/~mikko/visibility.patch
| [Thursday 02 December 2010] [09:22:10] <mato>	mikko: guess so
| [Thursday 02 December 2010] [09:23:08] <mikko>	i can also just remove the AC_TRY_COMPILE and use the compiler check
| [Thursday 02 December 2010] [09:23:16] <mikko>	if test "x$ac_ .. etc
| [Thursday 02 December 2010] [09:23:34] <mato>	make it as simple as possible, this is just for people with broken redhat GCC
| [Thursday 02 December 2010] [09:24:02] <mikko>	ok
| [Thursday 02 December 2010] [09:24:09] <mikko>	i'll juggle it a bit later
| [Thursday 02 December 2010] [09:27:32] <sustrik>	Guthur: you can, but what is it good for?
| [Thursday 02 December 2010] [09:28:54] <Guthur>	To make my object disposal strategy in a C# application a little bit more naive
| [Thursday 02 December 2010] [09:29:47] <Guthur>	I have a background thread listening for requests on a ZMQ_REQ, it'd like it to able to take care of it's own disposal
| [Thursday 02 December 2010] [09:29:56] <Guthur>	it'd/I'd
| [Thursday 02 December 2010] [09:30:04] <sustrik>	and?
| [Thursday 02 December 2010] [09:30:34] <Guthur>	Well if i share a context with the main thread I was thinking that I couldn't get rid of it without worrying about that socket
| [Thursday 02 December 2010] [09:31:08] <sustrik>	the socket returns ETERM when context it terminated
| [Thursday 02 December 2010] [09:31:13] <Guthur>	Does that make sense
| [Thursday 02 December 2010] [09:31:22] <Guthur>	oh ok
| [Thursday 02 December 2010] [09:31:43] <Guthur>	ignore the make sense statement
| [Thursday 02 December 2010] [09:33:19] <Guthur>	my mistake, I should have checked, I thought the open socket would block the context from disposing
| [Thursday 02 December 2010] [09:34:11] <sustrik>	it will
| [Thursday 02 December 2010] [09:34:38] <sustrik>	you'll get ETERM, then you close the socket
| [Thursday 02 December 2010] [09:34:46] <sustrik>	then the zmq_term() finishes
| [Thursday 02 December 2010] [09:39:16] <Guthur>	ok, thanks for the clarification sustrik 
| [Thursday 02 December 2010] [12:06:26] <drbobbeaty>	I'm running with the new ZMQ 2.1.0 from the new downloads site. It's running just fine, and I really appreciate all the work that's gone into it. But there is one thing, and I'm not sure what approach to take. When using epgm:// (OpenPGM) as the transport, the call to send() leaks. Not as much as 2.0.10, but it still leaks. For my application, it's still a problem. Is there anything in the "known issues" list for ZMQ or OpenPGM that might clear this up?
| [Thursday 02 December 2010] [12:06:26] <drbobbeaty>	am I on my own with the code?
| [Thursday 02 December 2010] [12:08:08] <mikko>	drbobbeaty: do you know where it leaks?
| [Thursday 02 December 2010] [12:08:26] <mikko>	im not sure if this is a known issue (first time i hear about it)
| [Thursday 02 December 2010] [12:10:25] <drbobbeaty>	I only know that if I comment out the call to send(), the leak goes away. Put it in and it leaks (for me) on the order of a couple of MB every few seconds.
| [Thursday 02 December 2010] [12:11:13] <drbobbeaty>	I know it's based on the size of the messages, but I don't have a lot of other information on it. I was going  to just get down-n-dirty with the code to try and track this down, but I wanted to ask here to see if this is something already known before I spend a few days on this.
| [Thursday 02 December 2010] [12:12:55] <mikko>	sustrik might be able to answer this better
| [Thursday 02 December 2010] [12:13:07] <mikko>	drbobbeaty: is it simple to reproduce?
| [Thursday 02 December 2010] [12:13:37] <drbobbeaty>	mikko: That's the first thing I'm going to do - make a simple test case and then go from there.
| [Thursday 02 December 2010] [12:14:03] <erickt>	does it not leak with the other protocols?
| [Thursday 02 December 2010] [12:14:39] <drbobbeaty>	erickt: not sure, going to try that too... just at the very early stages (10 min) of this process.
| [Thursday 02 December 2010] [12:21:58] <cremes>	drbobbeaty: it might just be queueing the data in memory; what kind of socket are you using?
| [Thursday 02 December 2010] [12:24:08] <cremes>	nevermind... that only makes sense for tcp transport
| [Thursday 02 December 2010] [12:24:41] <drbobbeaty>	Every idea is welcome. I'm going to do a lot of digging now and then when I have something concrete I'll send it to the mailing list.
| [Thursday 02 December 2010] [12:29:42] <mikko>	it does sound like the data is staying in some buffer
| [Thursday 02 December 2010] [12:30:27] <mikko>	drbobbeaty: are you closing the messages properly?
| [Thursday 02 December 2010] [12:30:33] <drbobbeaty>	yeah, that was my guess, because I've checked on the message itself, and that's OK -- I make a new one for each send, as I thought I read here that's the "best practices" for sending.
| [Thursday 02 December 2010] [12:30:55] <mikko>	you got message init and close for each send?
| [Thursday 02 December 2010] [12:36:32] <drbobbeaty>	I'm using the C++ API, and that does those in the zmq::message_t class, yes.
| [Thursday 02 December 2010] [12:37:14] <drbobbeaty>	mikko: I'm assuming you're asking about the message initialization and close out. The socket stays open for a "long" time.
| [Thursday 02 December 2010] [12:38:52] <mikko>	drbobbeaty: yeah, message init and close. looks like the C++ api closes the message upon destruction
| [Thursday 02 December 2010] [12:38:54] <sustrik>	drbobbeaty: are you sure you are not pushing data to 0MQ faster than PGM transfer rate?
| [Thursday 02 December 2010] [12:40:03] <sustrik>	default transmit rate is 100kb/s
| [Thursday 02 December 2010] [12:40:44] <drbobbeaty>	sustrik: I'm not sure what that rate is. I know I'm pushing about 1000 to 10,000 msgs/sec out on different epgm:// connected sockets (different sockets get different parts of the data set)... and I monitor the 10Gb Ethernet and it nowhere near the limit of the NIC - not even 50%. So I don't think I'm sending it too fast.
| [Thursday 02 December 2010] [12:41:13] <sustrik>	then look at ZMQ_RATE socket option
| [Thursday 02 December 2010] [12:41:15] <drbobbeaty>	sustrik: I set my default to 200kb/s in the construction
| [Thursday 02 December 2010] [12:41:28] <drbobbeaty>	...of each socket.
| [Thursday 02 December 2010] [12:41:36] <sustrik>	ok, and how much do you publish?
| [Thursday 02 December 2010] [12:41:52] <sustrik>	if you publish more than 200kb/s then the messages are queued
| [Thursday 02 December 2010] [12:42:42] <drbobbeaty>	I'll have to put in better measurement statistics to the logging... right now I look at messages per second, not bytes per socket per second. When I do that, I'll know.
| [Thursday 02 December 2010] [12:43:33] <sustrik>	in any case, setting transmit rate to 200kb/s on 10GbE seems overly restrictuve
| [Thursday 02 December 2010] [12:44:18] <drbobbeaty>	Yeah, I just upped it to 1Mbps and will try that
| [Thursday 02 December 2010] [14:35:27] <ngerakines>	hey folks, I've got a few questions about application design with zmq.
| [Thursday 02 December 2010] [14:36:49] <ngerakines>	In my system, i've got several load threads that subscribe to external pubsub streams and they take the messages they receive and funnel them to another thread that acts as a sort of funnel
| [Thursday 02 December 2010] [14:37:19] <ngerakines>	that funnel binds a ZMQ_PULL socket for that purpose
| [Thursday 02 December 2010] [14:37:47] <ngerakines>	what I want to do now, is create a number of worker threads that request work from that socket using ZMQ_REP
| [Thursday 02 December 2010] [14:38:17] <ngerakines>	so is it possible to have that funnel thread support both the PUSH connections from the loaders as well REP/REQ connections from workers?
| [Thursday 02 December 2010] [14:46:00] <Remoun>	ngerakines; IIUC, your use case fits into the "Request-Reply Broker" pattern, for which there's the built-in Queue device http://zguide.zeromq.org/chapter:all#toc31
| [Thursday 02 December 2010] [14:48:14] <ngerakines>	I was reading that and got the impression that messages were pushed to the workers (service b) where in my model, I want the workers to request work
| [Thursday 02 December 2010] [14:53:54] <Remoun>	AFAIK, the only way for the broker/funnel to know whether workers are available is that workers request work
| [Thursday 02 December 2010] [14:55:24] <ngerakines>	 so with that, is there a relatively easy way to create a socket that receives both PUSH and REP/REQ requests and is able to determine if an incoming message is one or the other?
| [Thursday 02 December 2010] [14:55:35] <ngerakines>	I haven't use poll much, but I'm thinking that I might have to go that route.
| [Thursday 02 December 2010] [14:55:43] <sustrik>	yes
| [Thursday 02 December 2010] [14:55:48] <sustrik>	two sockets
| [Thursday 02 December 2010] [14:55:54] <sustrik>	poll on them
| [Thursday 02 December 2010] [14:56:12] <sustrik>	read messages from both as they become available
| [Thursday 02 December 2010] [14:57:53] <ngerakines>	ok, thanks everyone
| [Thursday 02 December 2010] [17:07:10] <raydeo>	using 0mq 2.0.10 I have an inproc:// ZMQ_PAIR socket that is being used as communication between 2 threads. I'm getting an error when using zmq_connect to the socket in one thread before the other thread has done the zmq_bind... is this a known problem?
| [Thursday 02 December 2010] [17:07:26] <raydeo>	the errno received from zmq_bind is ECONNREFUSED
| [Thursday 02 December 2010] [17:14:36] <mikko>	raydeo: it's a known limitation
| [Thursday 02 December 2010] [17:14:47] <mikko>	you need to bind before connecting
| [Thursday 02 December 2010] [17:15:19] <raydeo>	mikko: that's fine, what would you suggest if I don't have control over the order those threads run? a different socket type, or a mutex?
| [Thursday 02 December 2010] [17:15:50] <mikko>	raydeo: it's a limitation of inproc transport
| [Thursday 02 December 2010] [17:16:31] <raydeo>	ok, so I'll just need to ensure externally the initialization order... shame :(
| [Thursday 02 December 2010] [18:41:50] <abrown28>	anyone listening want to answer a dumb question for me?
| [Thursday 02 December 2010] [23:20:49] <Remoun>	"If you need to know the identity of the peer you got a message from, only the XREP socket does this for you automatically. For any other socket type you must send the address explicitly, as a message part."
| [Thursday 02 December 2010] [23:21:01] <Remoun>	So how _do_ I get the address/identity?
| [Thursday 02 December 2010] [23:29:02] <the_hulk>	what is type identifier for socket, and context for C API's, or should i just declare them as void?
| [Thursday 02 December 2010] [23:44:03] <Remoun>	the_hulk; they're opaque handles, void*
| [Thursday 02 December 2010] [23:54:52] <the_hulk>	ok
| [Friday 03 December 2010] [02:16:41] <sustrik>	Remoun: just write it into the message
| [Friday 03 December 2010] [02:17:11] <Remoun>	I was/am looking for the value to write into the message :)
| [Friday 03 December 2010] [02:17:24] <sustrik>	think of something :)
| [Friday 03 December 2010] [02:19:13] <Remoun>	Relatedly, can I use semi-durable sockets such that I can actually address individual workers, but not have them eat memory when they're gone?
| [Friday 03 December 2010] [02:19:55] <Remoun>	I'm basically trying to distribute the 'broker' in the last example in the guide, while also adding a layer of authentication
| [Friday 03 December 2010] [02:22:00] <sustrik>	hm, that works only with REQ/REP pattern
| [Friday 03 December 2010] [02:22:15] <sustrik>	when you don't set identity, one is generated for you
| [Friday 03 December 2010] [02:22:40] <sustrik>	but the connections are still transient
| [Friday 03 December 2010] [02:22:46] <Remoun>	And it's generated by the REP side, right?
| [Friday 03 December 2010] [02:23:05] <sustrik>	the identity?
| [Friday 03 December 2010] [02:23:05] <Remoun>	Meaning if the worker actually talks to more than one broker, they'd have different IDs for that worker?
| [Friday 03 December 2010] [02:23:17] <sustrik>	yes
| [Friday 03 December 2010] [02:23:44] <Remoun>	Therein lies the catch...
| [Friday 03 December 2010] [02:24:16] <Remoun>	I need to avoid single points of failure, particularly with sth as involved as the broker
| [Friday 03 December 2010] [02:24:54] <Remoun>	Yet synchronizing the 'availability' across more than one node (thread, process, etc.) is nigh impossible
| [Friday 03 December 2010] [02:30:31] <Remoun>	sustrik; any ideas?
| [Friday 03 December 2010] [02:30:37] <sustrik>	i don't follow
| [Friday 03 December 2010] [02:30:40] <sustrik>	what's the problem?
| [Friday 03 December 2010] [02:32:02] <Remoun>	Splitting the load-balancing across several brokers; I don't know how to approach that
| [Friday 03 December 2010] [02:33:01] <sustrik>	connect the client to several brokers?
| [Friday 03 December 2010] [02:33:47] <Remoun>	But then more than one broker would dispatch to the same worker
| [Friday 03 December 2010] [02:33:54] <Remoun>	simultaneously, that is
| [Friday 03 December 2010] [02:35:57] <sustrik>	you have to decide what pattern are you going to use
| [Friday 03 December 2010] [02:36:11] <sustrik>	load balancing makes sense only with REQ/REP and PUSH/PULL
| [Friday 03 December 2010] [02:36:18] <sustrik>	which one are you using?
| [Friday 03 December 2010] [02:37:07] <Remoun>	I was going for REQ/REP, but now that I think about it, it can work better with PUSH/PULL
| [Friday 03 December 2010] [02:37:57] <sustrik>	what does " more than one broker would dispatch to the same worker" means with REQ/REP or PUSH/PULL?
| [Friday 03 December 2010] [02:38:56] <Remoun>	Well, a broker can only really service one request/pull at a time, right?
| [Friday 03 December 2010] [02:39:51] <sustrik>	right -- unless it dispatches it further, to a separate worker thread or somesuch
| [Friday 03 December 2010] [02:41:15] <Remoun>	I might just need to RTFM; I'll pour over the guide again
| [Friday 03 December 2010] [02:46:23] <Remoun>	Where can I read more about PUSH/PULL sockets/patterns? The guide doesn't talk much about them
| [Friday 03 December 2010] [02:47:44] <sustrik>	i think there's an chapter about it
| [Friday 03 December 2010] [02:47:49] <sustrik>	the one with "ventilator"
| [Friday 03 December 2010] [07:00:11] <the_hulk>	How do i know that server is down, from client site?
| [Friday 03 December 2010] [12:12:46] <ptrb>	if I have a push/pull set up, with one pusher and multiple pullers, is there some way to have the "push" action target a specific "puller", absent some other out-of-band communication?
| [Friday 03 December 2010] [12:13:33] <mikko>	ptrb: have each "puller" subscribe to generic and puller specific topic
| [Friday 03 December 2010] [12:13:44] <mikko>	and use puller specific topic to communicate with specific puller
| [Friday 03 December 2010] [12:15:29] <ptrb>	so pub/sub instead
| [Friday 03 December 2010] [12:16:23] <mikko>	yes
| [Friday 03 December 2010] [12:16:33] <mikko>	PUSH/PULL load balances the messages as well
| [Friday 03 December 2010] [12:16:47] <mikko>	im not sure if there is a way to message based on the ident of client using push/pull
| [Friday 03 December 2010] [12:16:52] <mikko>	sustrik might know better
| [Friday 03 December 2010] [12:17:42] <sustrik>	ptrb: PUSH socket does load balancing
| [Friday 03 December 2010] [12:17:56] <sustrik>	thus it decides which peer to send the message to itself
| [Friday 03 December 2010] [12:18:41] <mikko>	sustrik: i got solaris10 running as build slave
| [Friday 03 December 2010] [12:18:44] <mikko>	running first tests now
| [Friday 03 December 2010] [12:18:50] <mikko>	will try installing windows later on
| [Friday 03 December 2010] [12:18:58] <sustrik>	wow!
| [Friday 03 December 2010] [12:35:39] <mikko>	mato: there?
| [Friday 03 December 2010] [12:36:50] <sustrik>	mikko: i think he's travalling atm
| [Friday 03 December 2010] [12:39:55] <mikko>	i just notced that the way we unpack pgm sources doesnt seem to be portable 
| [Friday 03 December 2010] [12:39:59] <mikko>	-C option to tar
| [Friday 03 December 2010] [12:40:23] <sustrik>	shrug
| [Friday 03 December 2010] [12:41:36] <sustrik>	no idea myself
| [Friday 03 December 2010] [13:47:57] <ptrb>	is it possible to change the HWM behavior of a socket?
| [Friday 03 December 2010] [13:48:27] <ptrb>	or, failing that, poll to see the current, uh, water level?
| [Friday 03 December 2010] [13:53:46] <mikko>	watermark
| [Friday 03 December 2010] [13:53:54] <mikko>	yes, you can poll
| [Friday 03 December 2010] [13:54:04] <mikko>	it should come back as writable if hwm is reached
| [Friday 03 December 2010] [13:57:31] <ptrb>	am I stupid and missing what that function is?
| [Friday 03 December 2010] [13:58:21] <mikko>	what function?
| [Friday 03 December 2010] [13:58:58] <ptrb>	oh, you getsockopt on ZMQ_HWM?
| [Friday 03 December 2010] [13:59:15] <mikko>	zmq_poll
| [Friday 03 December 2010] [13:59:35] <mikko>	you can not get current amount of messages in transit
| [Friday 03 December 2010] [13:59:48] <mikko>	but zmq_poll should not return the socket as writable if hwm has been reached
| [Friday 03 December 2010] [14:00:40] <ptrb>	oh, okay. and that will work that way no matter what type of socket(s) you poll on
| [Friday 03 December 2010] [14:01:33] <mikko>	i've only tested on push sockets
| [Friday 03 December 2010] [14:02:04] <ptrb>	hmm.
| [Friday 03 December 2010] [14:03:01] <mikko>	not sure about pub socket
| [Friday 03 December 2010] [14:03:15] <mikko>	as the behavior with pub socket when hwm is reached is to discard messages
| [Friday 03 December 2010] [14:03:58] <ptrb>	right, which I'm trying to work around
| [Friday 03 December 2010] [14:04:36] <ptrb>	looks like the "correct" solution here is to manually manage N ZMQ_PUSH sockets... which is what I was hoping to avoid... but..
| [Friday 03 December 2010] [14:06:25] <ptrb>	OK, thanks for the tip.. if anything else strikes you in the night, feel free to let me know :)
| [Friday 03 December 2010] [14:06:41] <mikko>	you could easily test zmq_poll + pub socket
| [Friday 03 December 2010] [14:06:59] <ptrb>	yeah but that is more work than I can rightly manage at 8pm on a Friday :)
| [Friday 03 December 2010] [14:08:04] <ptrb>	cheers
| [Friday 03 December 2010] [14:09:19] <mikko>	http://zguide.zeromq.org/chapter:all
| [Friday 03 December 2010] [14:09:24] <mikko>	there is an example for zmq_poll
| [Friday 03 December 2010] [14:09:30] <mikko>	you should be able to mod that with ease
| [Saturday 04 December 2010] [17:16:10] <CIA-20>	zeromq2: 03Martin Sustrik 07master * rc80e7b8 10/ (11 files in 2 dirs): 
| [Saturday 04 December 2010] [17:16:10] <CIA-20>	zeromq2: XPUB and XSUB socket types added.
| [Saturday 04 December 2010] [17:16:10] <CIA-20>	zeromq2: These are just placeholders. At the moment XPUB behaves th same
| [Saturday 04 December 2010] [17:16:10] <CIA-20>	zeromq2: as PUB and XSUB as SUB.
| [Saturday 04 December 2010] [17:16:10] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/g8Nus1
| [Sunday 05 December 2010] [03:50:04] <CIA-20>	zeromq2: 03Martin Sustrik 07master * r2daa0bb 10/ (src/sub.cpp src/sub.hpp src/xsub.cpp src/xsub.hpp): 
| [Sunday 05 December 2010] [03:50:04] <CIA-20>	zeromq2: XSUB accepts (un)subscriptions in form of messages.
| [Sunday 05 December 2010] [03:50:04] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/ghbsFI
| [Sunday 05 December 2010] [11:20:41] <CIA-20>	rbzmq: 03Brian Buchanan 07master * r86050ce 10/ (rbzmq.c zmq.gemspec): Update to support libzmq 2.1.0 - http://bit.ly/fuzMIe
| [Sunday 05 December 2010] [17:25:20] <mikko>	mato: there?
| [Monday 06 December 2010] [00:46:54] <Guest53515>	i've been reading the docs and i see that you can send a message an basically wait for an ack (reply) back. is there a way to send and timeout in error if a reply has not been received within a timeframe
| [Monday 06 December 2010] [00:48:12] <guido_g>	no, you have to do this yourself
| [Monday 06 December 2010] [00:55:05] <Guest53515>	thanks..   can the receivee timeout or will it block forever?
| [Monday 06 December 2010] [00:56:26] <guido_g>	there is no timeout paramter for receive, but you can simulate it via poll
| [Monday 06 December 2010] [00:58:30] <guido_g>	*parameter
| [Monday 06 December 2010] [00:59:18] <Guest53515>	thanks, i was wondering about the poll.  i will have a look
| [Monday 06 December 2010] [01:00:12] <guido_g>	i'm not sure about this particular thing, but the guide is normally a good source of information
| [Monday 06 December 2010] [03:11:36] <mikko>	sustrik: there?
| [Monday 06 December 2010] [03:21:33] <sustrik>	mikko: hi
| [Monday 06 December 2010] [03:26:47] <mikko>	http://build.valokuva.org/job/ZeroMQ2-core-master_MSVC-win7/20/console
| [Monday 06 December 2010] [03:26:54] <mikko>	xpub/xsub missing from win build files?
| [Monday 06 December 2010] [03:28:16] <mikko>	brb, need to commute to the office
| [Monday 06 December 2010] [03:28:34] <sustrik>	mikko: oops
| [Monday 06 December 2010] [03:28:38] <sustrik>	let me fix that
| [Monday 06 December 2010] [03:28:53] <sustrik>	you are already building with MSVC?
| [Monday 06 December 2010] [03:29:06] <mikko>	yes, testing with win7 build slave
| [Monday 06 December 2010] [03:29:17] <sustrik>	impressive
| [Monday 06 December 2010] [03:29:20] <mikko>	http://build.valokuva.org/ -> linux, solaris10, win7 now
| [Monday 06 December 2010] [03:29:23] <mikko>	brb
| [Monday 06 December 2010] [03:29:27] <guido_g>	btw, are there already any docs xspub/ssub or is it code only currently?
| [Monday 06 December 2010] [03:29:43] <sustrik>	it's been committed yesteday
| [Monday 06 December 2010] [03:29:43] <guido_g>	*docs on xpub/xsub
| [Monday 06 December 2010] [03:29:49] <sustrik>	and does nothing useful
| [Monday 06 December 2010] [03:29:56] <guido_g>	ahhh ok
| [Monday 06 December 2010] [03:30:01] <sustrik>	it's just an infrastructure for subscription forwarding
| [Monday 06 December 2010] [03:30:02] <guido_g>	but sounds great! :)
| [Monday 06 December 2010] [03:30:25] <sustrik>	basically the idea is that subsctiptions are just messages
| [Monday 06 December 2010] [03:30:37] <sustrik>	that are passed up the message distribution tree
| [Monday 06 December 2010] [03:31:01] 	 * sustrik reboots into windows
| [Monday 06 December 2010] [03:44:33] <CIA-20>	zeromq2: 03Martin Sustrik 07master * r8a6ff4c 10/ builds/msvc/libzmq/libzmq.vcproj : 
| [Monday 06 December 2010] [03:44:33] <CIA-20>	zeromq2: xup and xsub files added to the MSVC build
| [Monday 06 December 2010] [03:44:33] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/gELabW
| [Monday 06 December 2010] [03:45:41] <guido_g>	:)
| [Monday 06 December 2010] [03:47:29] <sustrik>	re
| [Monday 06 December 2010] [03:48:34] <guido_g>	wb
| [Monday 06 December 2010] [03:50:27] <sustrik>	:)
| [Monday 06 December 2010] [04:13:18] <Steve-o>	sustrik: so any hope of back pressure on PUB sockets?
| [Monday 06 December 2010] [04:13:58] <sustrik>	what's your problem?
| [Monday 06 December 2010] [04:14:43] <Steve-o>	client sending to PGM faster than the rate limit, there's back pressure from OpenPGM but nothing from 0MQ
| [Monday 06 December 2010] [04:15:12] <Steve-o>	you can set HWM and lose messages, but the API doesn't provide any feedback
| [Monday 06 December 2010] [04:15:33] <sustrik>	Steve-o: don't set the HWM then
| [Monday 06 December 2010] [04:15:36] <Steve-o>	which forces the developer to implement their own rate engine above 0MQ at a guess
| [Monday 06 December 2010] [04:16:08] <Steve-o>	making the granular rate engine in OpenPGM pretty useless
| [Monday 06 December 2010] [04:24:15] <sustrik>	Steve-o: still there? what the problem with leaving HWM infinite?
| [Monday 06 December 2010] [04:30:09] <mikko>	sustrik: builds now
| [Monday 06 December 2010] [04:30:10] <mikko>	thanks
| [Monday 06 December 2010] [04:30:19] <sustrik>	np
| [Monday 06 December 2010] [04:30:25] <mikko>	if this trial works well ill add the win7 as permanent part
| [Monday 06 December 2010] [04:30:29] <mikko>	to the build cluster
| [Monday 06 December 2010] [04:31:14] <sustrik>	that would be great
| [Monday 06 December 2010] [04:31:23] <sustrik>	win platform is notoriously under-tested
| [Monday 06 December 2010] [04:31:54] <mikko>	sadly this build box is 32bit
| [Monday 06 December 2010] [04:32:07] <mikko>	i need to look into the stockpile of old servers if i could find 64bit iron
| [Monday 06 December 2010] [04:55:12] <mato>	mikko: hi
| [Monday 06 December 2010] [04:55:17] <mato>	mikko: you were after me?
| [Monday 06 December 2010] [05:00:49] <mikko>	mato: yeah
| [Monday 06 December 2010] [05:00:59] <mikko>	mato: -C option to tar is not portable it seems
| [Monday 06 December 2010] [05:01:10] <mato>	mikko: -C ?
| [Monday 06 December 2010] [05:01:14] <mikko>	solaris tar accepts -C when creating or replacing archive
| [Monday 06 December 2010] [05:01:23] <mato>	mikko: what is using -C?
| [Monday 06 December 2010] [05:01:34] <mikko>	yes, -C is used when extracting openpgm
| [Monday 06 December 2010] [05:02:10] <mikko>	so, im wondering that should we require gnu tar or chdir before extraction
| [Monday 06 December 2010] [05:02:17] <mikko>	i got a patch for the chdir approach somewhere
| [Monday 06 December 2010] [05:02:37] <mato>	the latter, since it is supposed to work on Solaris I guess
| [Monday 06 December 2010] [05:02:55] <mato>	anything to do with openpgm doesn't have to be portable past MinGW/Linux/Solaris
| [Monday 06 December 2010] [05:03:24] <mikko>	ok, so i'll post the patch as it is when i got time
| [Monday 06 December 2010] [05:03:36] <mikko>	mato: there is experimental win7 in the daily builds now as well
| [Monday 06 December 2010] [05:03:36] <mato>	sure, go for it
| [Monday 06 December 2010] [05:03:47] <mikko>	running visual studio 2008
| [Monday 06 December 2010] [05:03:58] <mato>	mikko: wow, how did you manage that? :-)
| [Monday 06 December 2010] [05:04:12] <mato>	mingw I could grok, but scripting VS builds ... 
| [Monday 06 December 2010] [05:04:19] <mikko>	i installed hudson as windows service and it uses msbuild command line tools to run builds
| [Monday 06 December 2010] [05:04:27] <mato>	ah, so it has support for that
| [Monday 06 December 2010] [05:04:28] <mato>	great!
| [Monday 06 December 2010] [05:04:44] <mikko>	the only pain was to install windows using vmware esx console
| [Monday 06 December 2010] [05:04:50] <mikko>	the mouse moves in jumps 
| [Monday 06 December 2010] [05:05:27] <mato>	by the way, the guy with rhat gcc3 problems solved his own problem
| [Monday 06 December 2010] [05:05:33] <mato>	so I guess we can leave that alone for now
| [Monday 06 December 2010] [05:05:51] <mikko>	i got a patch for it though
| [Monday 06 December 2010] [05:05:53] <mato>	let's see if anyone else complains that they really need to use broken RHAT gcc3 :)
| [Monday 06 December 2010] [05:06:09] <mato>	well, if you're happy with the patch, send it to the ML.
| [Monday 06 December 2010] [05:06:39] 	 * mato will be on irc somewhat intermittently this week, have builders here ...
| [Monday 06 December 2010] [06:09:00] <adalrsjr1>	hello...
| [Monday 06 December 2010] [06:09:47] <adalrsjr1>	i need run a zmq java application in machines without zmq
| [Monday 06 December 2010] [06:09:54] <adalrsjr1>	how i can do it?
| [Monday 06 December 2010] [06:10:10] <adalrsjr1>	whitout zmq installed
| [Monday 06 December 2010] [06:10:15] <adalrsjr1>	i using linux
| [Monday 06 December 2010] [06:11:29] <mikko>	adalrsjr1: currently the java binding requires libzmq
| [Monday 06 December 2010] [06:11:40] <mikko>	adalrsjr1: i don't think there is a pure java implementation
| [Monday 06 December 2010] [06:16:40] <adalrsjr1>	its my problema, i don't have libzmq in these machines
| [Monday 06 December 2010] [06:17:13] <adalrsjr1>	but i have the libzmq compiled in other pc
| [Monday 06 December 2010] [06:17:48] <mikko>	as far as i know currently you require libzmq with the java binding as it uses jni
| [Monday 06 December 2010] [06:26:17] <Steve-o>	adalrsjr1: if the Linux versions are the same you should be able to copy over the jni & core zmq dynamic libraries
| [Monday 06 December 2010] [06:28:04] <Steve-o>	well, noted for the IRC log :-)
| [Monday 06 December 2010] [06:49:02] <sustrik>	mikko, mato: a suggestion -- shouldn't we limit test_shutdown_stress to something reasonable
| [Monday 06 December 2010] [06:49:12] <sustrik>	like seting up and tearing down 100 connection
| [Monday 06 December 2010] [06:49:33] <sustrik>	so that it would work on any box without running into resource problems?
| [Monday 06 December 2010] [06:51:21] <mato>	sustrik: yes
| [Monday 06 December 2010] [06:51:29] <sustrik>	ok
| [Monday 06 December 2010] [06:51:42] <mato>	sustrik: well, maybe... it does expose problems when run properly
| [Monday 06 December 2010] [06:51:53] <sustrik>	that's nice
| [Monday 06 December 2010] [06:52:03] <mato>	sustrik: but at least on solaris there's a limit of 256 fds per process by default
| [Monday 06 December 2010] [06:52:06] <sustrik>	otoh, the builds fail bacause of it
| [Monday 06 December 2010] [06:52:23] <mato>	sure, but then how will we know we've fixed the problem :)
| [Monday 06 December 2010] [06:52:35] <mato>	maybe...
| [Monday 06 December 2010] [06:52:55] <mato>	how about we change the test to run less connections on !linux
| [Monday 06 December 2010] [06:54:19] <sustrik>	i don't think platform.hpp is included in the tests
| [Monday 06 December 2010] [06:54:29] <sustrik>	do you know you are no linux there?
| [Monday 06 December 2010] [06:59:27] <mato>	sustrik:  hang on
| [Monday 06 December 2010] [07:00:14] <mato>	sustrik: a) the tests can obviously include platform.hpp
| [Monday 06 December 2010] [07:00:34] <mato>	sustrik: b) test_shutdown_stress can call getrlimit(3) with RLIMIT_NOFILE and pick some sane value
| [Monday 06 December 2010] [07:00:40] <mato>	sustrik: for the # of iterations
| [Monday 06 December 2010] [07:00:49] <mato>	sustrik: that way we can at least ensure it won't run out of FDs
| [Monday 06 December 2010] [07:01:00] <mato>	sustrik: if it dies due to other problems then that's a valid bug...
| [Monday 06 December 2010] [07:01:23] <sustrik>	what about socket buffer size?
| [Monday 06 December 2010] [07:01:30] <mato>	what about it?
| [Monday 06 December 2010] [07:01:39] <mato>	that's a bug, we need to fix that somehow :-)
| [Monday 06 December 2010] [07:02:36] <mato>	we shouldn't be hiding bugs by modifying test cases
| [Monday 06 December 2010] [07:04:25] <sustrik>	the question is how to distinguish "out of resources" from "bug"
| [Monday 06 December 2010] [07:04:59] <mato>	then our mailbox_t needs to report back that it has run out of socket buffers, and return that to the app somehow
| [Monday 06 December 2010] [07:06:09] <sustrik>	it has to fail; at that point the system is broken beyond any hope to repair
| [Monday 06 December 2010] [07:06:51] <sustrik>	it's basically a same problem as ENOMEM
| [Monday 06 December 2010] [07:06:59] <sustrik>	is it a bug or is it not?
| [Monday 06 December 2010] [07:07:17] <mato>	well, the way we're dealing with it at the moment is a bug
| [Monday 06 December 2010] [07:07:27] <sustrik>	the assertion?
| [Monday 06 December 2010] [07:07:43] <mato>	that, and/or the fact that we're reliant on the socket buffer size so much
| [Monday 06 December 2010] [07:08:11] <mato>	step 1 would be to at least change the assertion to somehow return an errno to the application. if that's possible.
| [Monday 06 December 2010] [07:08:18] <mato>	step 2 is obviously to fix the signaler
| [Monday 06 December 2010] [07:08:36] <mato>	again, if that's possible - i know we've been through this...
| [Monday 06 December 2010] [07:08:55] <mato>	sustrik: think about it in kernel terms
| [Monday 06 December 2010] [07:09:06] <mato>	sustrik: do you panic the system if some buffer runs out? i think not.
| [Monday 06 December 2010] [07:09:47] <sustrik>	the problem is that in this case the buffer in question is part of the essential infrastructure
| [Monday 06 December 2010] [07:09:59] <sustrik>	thus when it overflows the whole thing is unusable
| [Monday 06 December 2010] [07:10:08] <sustrik>	you do panic in such a case
| [Monday 06 December 2010] [07:10:17] <sustrik>	still better than undefined behaviour
| [Monday 06 December 2010] [07:11:28] <sustrik>	anyway, i'll leave the stress test as is for now
| [Monday 06 December 2010] [08:26:59] <sustrik>	drbobbeaty: hi
| [Monday 06 December 2010] [08:28:33] <drbobbeaty>	sustrik: hi
| [Monday 06 December 2010] [08:29:40] <sustrik>	hi, have you seen steve's answer about ZMQ_RECOVERY_IVL smaller than 1 sec?
| [Monday 06 December 2010] [08:30:54] <drbobbeaty>	Yeah, he was talking about making a C-level call to OpenPGM based on the size of the buffer. Since I'm using the C++ interface, I didn't know how/if that would be possible given that I don't have access to the underlying C pointers/structs.
| [Monday 06 December 2010] [08:31:22] <sustrik>	the idea is to tweak the 0MQ source code
| [Monday 06 December 2010] [08:31:46] <sustrik>	ie. set the recovery in number of packets rather than in seconds
| [Monday 06 December 2010] [08:32:42] <sustrik>	see src/pgm_socket.cpp
| [Monday 06 December 2010] [08:33:14] <sustrik>	line 203 and 236
| [Monday 06 December 2010] [08:34:42] <drbobbeaty>	Ah! OK... I can tweak the code if needed. My question would be if this is going to be supported in some manner in the straight ZeroMQ releases. I can wait on this if it's coming out soon, or I can make the changes and then back them out when the feature becomes available from you guys.
| [Monday 06 December 2010] [08:35:08] <sustrik>	drbobbeaty: if you send a patch to the mailing list, i'll apply it
| [Monday 06 December 2010] [08:35:21] <sustrik>	just make sure that it actually works before sending it
| [Monday 06 December 2010] [08:35:35] <drbobbeaty>	he he he... yeah, that'd be a good thing to make sure :)
| [Monday 06 December 2010] [08:35:57] <sustrik>	(i don't have a test env here, so i won't be able to test it really)
| [Monday 06 December 2010] [08:35:59] <drbobbeaty>	I'll have a look and then read up on the ML diff submission process. 
| [Monday 06 December 2010] [08:36:11] <sustrik>	sure
| [Monday 06 December 2010] [08:36:19] <sustrik>	have you seen the code?
| [Monday 06 December 2010] [08:36:28] <sustrik>	the change seems to be pretty trivial
| [Monday 06 December 2010] [08:36:52] <drbobbeaty>	I think I can handle it :) But if I have any questions, I will be back to ask for help.
| [Monday 06 December 2010] [08:37:14] <sustrik>	sure
| [Monday 06 December 2010] [08:38:17] <sustrik>	drbobbeaty: ah, damn
| [Monday 06 December 2010] [08:38:42] <sustrik>	change from sec to msecs would break the backward compatibilitty :(
| [Monday 06 December 2010] [08:39:10] <drbobbeaty>	Yeah, I can imagine that... but what about a different named socket option?
| [Monday 06 December 2010] [08:39:24] <sustrik>	yes, looks like the only option atm
| [Monday 06 December 2010] [08:40:26] <drbobbeaty>	Seems fair... do you have a preference for what that name should be? ZMQ_RECOVERY_MSEC or ZMQ_RECOVERY_IVL_MSEC?
| [Monday 06 December 2010] [08:41:04] <mikko>	is that confusing?
| [Monday 06 December 2010] [08:41:12] <mikko>	two constants for effectively same option
| [Monday 06 December 2010] [08:41:34] <sustrik>	mikko: any better idea?
| [Monday 06 December 2010] [08:42:00] <mikko>	it would be still possible to change this in 2.1
| [Monday 06 December 2010] [08:42:04] <mikko>	as there is no stable release
| [Monday 06 December 2010] [08:42:17] <mikko>	beta is what it says on the tin
| [Monday 06 December 2010] [08:42:22] <sustrik>	the backward compatibility is guaranteed witin a major version
| [Monday 06 December 2010] [08:42:39] <sustrik>	so it can't be broken before 3.0
| [Monday 06 December 2010] [08:42:42] <mikko>	but things are already breaking going from 2.0 to 2.1
| [Monday 06 December 2010] [08:42:55] <mikko>	zmq_init for example
| [Monday 06 December 2010] [08:43:04] <sustrik>	how so?
| [Monday 06 December 2010] [08:43:11] <mikko>	or did that change earlier?
| [Monday 06 December 2010] [08:43:22] <sustrik>	yep, that changes somewhere at 2.0.4
| [Monday 06 December 2010] [08:43:37] <sustrik>	since then people have complained about breaking backwards compatibility
| [Monday 06 December 2010] [08:43:51] <sustrik>	so i've written compatibility guidelines
| [Monday 06 December 2010] [08:43:58] <sustrik>	let me find it...
| [Monday 06 December 2010] [08:46:54] <sustrik>	http://www.zeromq.org/docs:policies
| [Monday 06 December 2010] [08:46:59] <drbobbeaty>	sustrik, mikko: I am enjoying reading the "Contributing to 0MQ" page... as soon as I get through all this, and you guys decide how you'd like me to implement it, I'll get right on it.
| [Monday 06 December 2010] [08:47:48] <mikko>	sustrik: "It may even run, however, you should read the NEWS file so you are sure that changes made won't affect your application behaviour in subtle ways."
| [Monday 06 December 2010] [08:47:49] <sustrik>	enjoying the burocracy? :)
| [Monday 06 December 2010] [08:48:11] <mikko>	sustrik: it would still compile against the version
| [Monday 06 December 2010] [08:48:11] <sustrik>	mikko: right
| [Monday 06 December 2010] [08:48:15] <mikko>	is your policy says
| [Monday 06 December 2010] [08:48:28] <mikko>	but people using recovery IVL would need to read about the change
| [Monday 06 December 2010] [08:48:58] <sustrik>	but allocating buffer 1000x larger than expected in not really a subtle change
| [Monday 06 December 2010] [08:49:22] <sustrik>	it's pretty dangerous actually
| [Monday 06 December 2010] [08:50:20] <sustrik>	i would go for new socket option now
| [Monday 06 December 2010] [08:50:42] <sustrik>	and normalise the two options into a single one in v3.0
| [Monday 06 December 2010] [08:50:56] <mikko>	i guess that is sensible for now. i think we should keep a list things like these that need to be cleaned up on major
| [Monday 06 December 2010] [08:51:17] <sustrik>	some comments are already here: http://www.zeromq.org/docs:3-0
| [Monday 06 December 2010] [08:52:00] <sustrik>	drbobbeaty: just add a new option for now
| [Monday 06 December 2010] [08:52:13] <drbobbeaty>	sustrik: OK, that's what I'll do.
| [Monday 06 December 2010] [08:53:14] <sustrik>	something like:
| [Monday 06 December 2010] [08:53:44] <sustrik>	"RECOVERY_IVL_MSEC has precedence to RECOVERY_IVL"
| [Monday 06 December 2010] [08:54:02] <sustrik>	"however, if set to zero, it's ignored and RECOVERY_IVL is used instead"
| [Monday 06 December 2010] [08:54:07] <sustrik>	"default is zero"
| [Monday 06 December 2010] [08:54:37] <drbobbeaty>	sustrik: OK, sounds reasonable with a nice fallback.
| [Monday 06 December 2010] [09:10:51] <sustrik>	Steve-o: what out_buffer_size should I use?
| [Monday 06 December 2010] [09:11:47] <sustrik>	and what parameters you were running local_the/remote_the with?
| [Monday 06 December 2010] [09:11:53] <sustrik>	thr*
| [Monday 06 December 2010] [09:12:03] <Steve-o>	I tried 1420
| [Monday 06 December 2010] [09:12:18] <Steve-o>	and "tcp..." 100 1
| [Monday 06 December 2010] [09:12:23] <sustrik>	great
| [Monday 06 December 2010] [09:12:35] <sustrik>	i'll check that
| [Monday 06 December 2010] [09:50:42] <drbobbeaty>	sustrik: I assume all these changes for the recovery time should be to the default, 'development' release and not the 'maint' release, correct?
| [Monday 06 December 2010] [09:51:17] <mikko>	drbobbeaty: yes, just for the master branch
| [Monday 06 December 2010] [10:21:19] <toni__>	hey there. I am using a REQ socket that connects to a set of servers (XREP). Is there way to notice when a server dies? My intention is to wait for max. 2 seconds, until I consider the server as gone. But the s.recv() (s is a REQ socket) blocks. Is there a way to achieve this, or should a make use of a XREQ which is non-blocking?
| [Monday 06 December 2010] [10:21:19] <mikko>	toni__: you should be able to use zmq_poll for this
| [Monday 06 December 2010] [10:21:19] <mikko>	you can also pass ZMQ_NOBLOCK flag to zmq_recv
| [Monday 06 December 2010] [10:22:05] <toni__>	cool, thanks. great channel, for all my questions I get a answer very fast. This avoids searching the huge guide twice for such particular part of information. Thanks!
| [Monday 06 December 2010] [10:23:09] <guido_g>	toni__: there is also http://api.zeromq.org/zmq.html
| [Monday 06 December 2010] [10:26:54] <toni__>	guido_g: i know, but I expected to maybe get a correcting answer in case my solution for the problem would already be provided by zmq itself. 
| [Monday 06 December 2010] [10:27:56] <guido_g>	toni__: it was more a response to " This avoids searching the huge guide twice..."
| [Monday 06 December 2010] [10:31:06] <sustrik>	hm, this is almost a FAQ
| [Monday 06 December 2010] [10:32:13] <sustrik>	i've answered this particular question like twice in past two days
| [Monday 06 December 2010] [10:44:37] <toni__>	hey there, one more question. I could not find a way to disconnect a socket from an address it was once connected to. I can only find socket.close() but thats not what I need. So is there a way to disconnect from an address? 
| [Monday 06 December 2010] [10:49:08] <sustrik>	close the socket
| [Monday 06 December 2010] [10:50:39] <toni__>	the socket is connected to a set of addresses. In case one does not answer, I want to remove the connection to this address, so I close the socket and reconnect it to all adresses without the one that did not work?
| [Monday 06 December 2010] [10:51:49] <sustrik>	i presume that when the non answering address becomes available again, you want to reconnect to it?
| [Monday 06 December 2010] [10:52:08] <toni__>	yes
| [Monday 06 December 2010] [10:52:15] <sustrik>	0mq does that for you
| [Monday 06 December 2010] [10:52:27] <sustrik>	you don't have to care about non-anwering endpoints
| [Monday 06 December 2010] [10:53:13] <sustrik>	they are ignored and reconnected when they become available again
| [Monday 06 December 2010] [10:53:31] <toni__>	okay, thats great. Does this also mean that messages wont be send to an address that seems currently not available?
| [Monday 06 December 2010] [10:54:09] <bobdole369>	Hello everyone, tnx for letting me idle in here all weekend :x - didn't really mean to do that... OK on to it: Have a possible project in the coming weeks and am looking at 0MQ as the data transport mechanism.
| [Monday 06 December 2010] [10:54:11] <seb`>	the server side won't block if you close the socket
| [Monday 06 December 2010] [10:54:25] <bobdole369>	Few queries about a few things come to mine.
| [Monday 06 December 2010] [10:55:36] <sustrik>	toni__: yes, but set HWM to something low
| [Monday 06 December 2010] [10:55:59] <sustrik>	so that requests are not queued too much for a destination that may become unavailable later on
| [Monday 06 December 2010] [10:57:20] <toni__>	sustrik: but it can be that a message wont be sent out, and is queued until the address becomes available again? Thats what I have to avoid.
| [Monday 06 December 2010] [10:58:15] <sustrik>	that's done by resending the request once the timeout expires
| [Monday 06 December 2010] [10:58:28] <sustrik>	you should also discard duplicate replies, of course
| [Monday 06 December 2010] [10:58:55] <bobdole369>	Have a number of embedded devices in the "field" that will transmit data to a central datacenter server.  The data are infrequent small data points, perhaps 2kb of data is actually a lot.  We control these and can author the packets. Is 0MQ a suitable transport method for this data? 
| [Monday 06 December 2010] [10:59:01] <sustrik>	(the whole resend functionality should be actually implemented inside 0mq, but it's not yet)
| [Monday 06 December 2010] [10:59:48] <sustrik>	bobdole369: you want to deploy 0mq on the devices?
| [Monday 06 December 2010] [11:00:29] <toni__>	sustrik: Thanks for your help
| [Monday 06 December 2010] [11:00:49] <bobdole369>	That is possible. They are PLC style devices though, and not PC's. They do speak ansi C.
| [Monday 06 December 2010] [11:01:07] <sustrik>	toni__: you are welcome
| [Monday 06 December 2010] [11:01:29] <sustrik>	bobdole369: what about the OS?
| [Monday 06 December 2010] [11:02:01] <bobdole369>	On the PLC devices
| [Monday 06 December 2010] [11:06:13] <stephank>	bobdole369: No need to apologize for idling around, that's pretty common practice on IRC. Zeromq is C++ and builds on top of BSD sockets and threading APIs, amongst others. Those are typically implemented by an OS. Are those provided by your embedded platform.
| [Monday 06 December 2010] [11:24:34] <drbobbeaty>	sustrik: I'm looking at the code and can't find any reference to tpdu_size, but I do find references to get_max_tsdu_size(). Should I be using the tsdu_size from this call, or am I missing something obvious? I'm trying to convert either timespan into a count of sequence numbers - as per Steven's suggestion.
| [Monday 06 December 2010] [11:29:23] <bobdole369>	OIC ya sockets and the API does seem to be done by the embedded platform - M258 Schneider PLC
| [Monday 06 December 2010] [11:35:15] <sustrik>	drbobbeaty: ask steven about what value to actually use
| [Monday 06 December 2010] [11:35:35] <sustrik>	i am not an expert on PGM
| [Monday 06 December 2010] [11:35:51] <drbobbeaty>	sustrik: Got it... will do.
| [Monday 06 December 2010] [11:35:54] <sustrik>	alternatively you may find the definitions in RFC3208
| [Monday 06 December 2010] [12:34:26] <bobdole369>	I'm a fair bit noob, so can I ask what is the advantage that 0MQ holds over OS calls and sockets?
| [Monday 06 December 2010] [12:34:57] <mikko>	bobdole369: there are several
| [Monday 06 December 2010] [12:35:14] <mikko>	i think personally the biggest advantage is work in terms of messages rather than bytes
| [Monday 06 December 2010] [12:35:46] <mikko>	normally when writing a non-blocking server you have the problem of getting EAGAIN back and then reading a bit more bytes and maintaining state of where the protocol boundaries go
| [Monday 06 December 2010] [12:36:19] <mikko>	another benefit is being able to switch almost transparently between different transports
| [Monday 06 December 2010] [12:36:27] <mikko>	and of course the built-in messaging patterns
| [Monday 06 December 2010] [12:36:40] <mikko>	publish-subscribe, request-reply etc
| [Monday 06 December 2010] [12:36:50] <bobdole369>	Yes the patterns are mostly what brought me here.
| [Monday 06 December 2010] [12:37:36] <mikko>	there are several other benefits as well
| [Monday 06 December 2010] [14:10:11] <jhawk28>	sustrik: are you here?
| [Monday 06 December 2010] [14:24:25] <delaney>	are there any up to date C# examples?
| [Monday 06 December 2010] [14:29:40] <mikko>	delaney: the examples are usually pretty portable
| [Monday 06 December 2010] [14:29:52] <mikko>	you should get the hang of C# by looking at here https://github.com/zeromq/clrzmq2
| [Monday 06 December 2010] [15:08:22] <sustrik>	jhawk28: hi
| [Monday 06 December 2010] [16:36:55] <CIA-20>	zeromq2: 03Martin Sustrik 07master * rec61751 10/ (src/pub.cpp src/sub.cpp src/xpub.cpp src/xsub.cpp): 
| [Monday 06 December 2010] [16:36:55] <CIA-20>	zeromq2: options.type correctly set for PUB/SUB/XPUB/XSUB
| [Monday 06 December 2010] [16:36:55] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/g0JAEI
| [Monday 06 December 2010] [16:58:28] <CIA-20>	zeromq2: 03Martin Sustrik 07master * r8d6cafe 10/ (10 files): 
| [Monday 06 December 2010] [16:58:28] <CIA-20>	zeromq2: All devices conflated into a single implementation.
| [Monday 06 December 2010] [16:58:28] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/hbyNJH
| [Monday 06 December 2010] [17:11:12] <CIA-20>	zeromq2: 03Martin Sustrik 07master * r73bbcb5 10/ builds/msvc/libzmq/libzmq.vcproj : 
| [Monday 06 December 2010] [17:11:12] <CIA-20>	zeromq2: MSVC build fixed
| [Monday 06 December 2010] [17:11:12] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/gHkbTx
| [Tuesday 07 December 2010] [03:08:08] <the_hulk>	hi, for C API's on server side, i do not have to fork? it seems to be taken care of?
| [Tuesday 07 December 2010] [03:08:46] <Steve-o>	fork to do what?
| [Tuesday 07 December 2010] [03:12:13] <the_hulk>	fork to handle multiple clients, as we do with normal sockets fds
| [Tuesday 07 December 2010] [03:12:31] <Steve-o>	and thread pooling, etc, ok 
| [Tuesday 07 December 2010] [03:14:09] <Steve-o>	It's covered pretty well in the guide, http://zguide.zeromq.org/chapter:all
| [Tuesday 07 December 2010] [03:19:06] <the_hulk>	ohk
| [Tuesday 07 December 2010] [05:10:53] <CIA-20>	zeromq2: 03Martin Lucina 07master * r9bb5323 10/ doc/zmq_socket.txt : 
| [Tuesday 07 December 2010] [05:10:53] <CIA-20>	zeromq2: Clarify zmq_send() operation for ZMQ_PUB sockets
| [Tuesday 07 December 2010] [05:10:53] <CIA-20>	zeromq2: Signed-off-by: Martin Lucina <mato@kotelna.sk> - http://bit.ly/eNDyqm
| [Tuesday 07 December 2010] [05:16:25] <CIA-20>	zeromq2: 03Mikko Koppanen 07master * raed2eea 10/ (acinclude.m4 configure.in): 
| [Tuesday 07 December 2010] [05:16:25] <CIA-20>	zeromq2: Fix visibility on rhel4
| [Tuesday 07 December 2010] [05:16:25] <CIA-20>	zeromq2: Signed-off-by: Mikko Koppanen <mkoppanen@php.net> - http://bit.ly/hue9Av
| [Tuesday 07 December 2010] [05:16:27] <CIA-20>	zeromq2: 03Mikko Koppanen 07master * ra335315 10/ acinclude.m4 : 
| [Tuesday 07 December 2010] [05:16:27] <CIA-20>	zeromq2: Fix werror flag store/restore
| [Tuesday 07 December 2010] [05:16:27] <CIA-20>	zeromq2: Signed-off-by: Mikko Koppanen <mkoppanen@php.net> - http://bit.ly/idiJwf
| [Tuesday 07 December 2010] [05:16:28] <CIA-20>	zeromq2: 03Mikko Koppanen 07master * r1d81d2f 10/ configure.in : 
| [Tuesday 07 December 2010] [05:16:28] <CIA-20>	zeromq2: tar doesn't accept -C flag on solaris while extracting
| [Tuesday 07 December 2010] [05:16:28] <CIA-20>	zeromq2: Signed-off-by: Mikko Koppanen <mkoppanen@php.net> - http://bit.ly/hrR0E7
| [Tuesday 07 December 2010] [07:04:04] <ptrb>	just to confirm -- no problem making multiple connect() calls on a single ZMQ_SUB socket, right?
| [Tuesday 07 December 2010] [07:34:58] <drbobbeaty>	ptrb: correct. You can have multiple connect() calls to one ZMQ_SUB socket.
| [Tuesday 07 December 2010] [07:35:37] <drbobbeaty>	In order to "tear down" the socket, you have to drop/close the socket. Meaning, you can't disconnect() just one of the connections - you have to take them all down.
| [Tuesday 07 December 2010] [07:38:08] <Steve-o>	unbind/disconnect was discussed previously:  http://thread.gmane.org/gmane.network.zeromq.devel/4369
| [Tuesday 07 December 2010] [07:47:07] <ptrb>	cool. thanks.
| [Tuesday 07 December 2010] [09:43:32] <sustrik_>	drbobbeaty: hi
| [Tuesday 07 December 2010] [09:43:50] <drbobbeaty>	sustrik: hi... I sent in the patch to the ML.
| [Tuesday 07 December 2010] [09:44:15] <sustrik_>	yes, just got it
| [Tuesday 07 December 2010] [09:44:19] <sustrik_>	a minor point
| [Tuesday 07 December 2010] [09:44:32] <sustrik_>	subscribe to the mailing list
| [Tuesday 07 December 2010] [09:44:40] <sustrik_>	otherwise the messages are blocked
| [Tuesday 07 December 2010] [09:44:46] <sustrik_>	and i have to approve them by hand
| [Tuesday 07 December 2010] [09:45:00] <sustrik_>	if you don't want to get the traffic, you can switch that off
| [Tuesday 07 December 2010] [09:45:12] <sustrik_>	but still be member of the list
| [Tuesday 07 December 2010] [09:45:16] <drbobbeaty>	Funny thing, I am subscribed, and I still keep getting blocked. Pieter talked to me about that, and we walked through it together. Very puzzling.
| [Tuesday 07 December 2010] [09:45:29] <sustrik_>	hm, let me see
| [Tuesday 07 December 2010] [09:45:42] <drbobbeaty>	Please do... I'd love to not bother you guys.
| [Tuesday 07 December 2010] [09:46:29] <sustrik_>	hm, i don't see you in the members list
| [Tuesday 07 December 2010] [09:46:42] <sustrik_>	any idea what email address you have used to subscribe?
| [Tuesday 07 December 2010] [09:46:53] <drbobbeaty>	drbob@TheManFromSPUD.com
| [Tuesday 07 December 2010] [09:47:10] <drbobbeaty>	That's what I use to "maintain" the ML on it's web site. 
| [Tuesday 07 December 2010] [09:47:11] <sustrik_>	aha
| [Tuesday 07 December 2010] [09:47:21] <sustrik_>	but the emails you send are from a different address
| [Tuesday 07 December 2010] [09:47:31] <drbobbeaty>	OH! Duh.
| [Tuesday 07 December 2010] [09:47:36] <sustrik_>	comcast
| [Tuesday 07 December 2010] [09:47:46] <drbobbeaty>	That's it... outgoing != incoming. I'll change that.
| [Tuesday 07 December 2010] [09:47:51] <sustrik_>	great
| [Tuesday 07 December 2010] [09:47:52] <drbobbeaty>	Thanks for the pointer.
| [Tuesday 07 December 2010] [09:48:00] <sustrik_>	i'll have a look at your patch shortly
| [Tuesday 07 December 2010] [09:48:58] <drbobbeaty>	I hope it's clean and easy. And adheres to the buidelines.
| [Tuesday 07 December 2010] [09:51:05] <sustrik_>	one thing i am not sure of: is it possible that someone would want recovery ivl of zero?
| [Tuesday 07 December 2010] [09:51:21] <sustrik_>	unreliable multicast...
| [Tuesday 07 December 2010] [09:51:32] <sustrik_>	i am not even sure it's possible with OpenPGM
| [Tuesday 07 December 2010] [09:51:57] <sustrik_>	if so, the default should be -1 rather than 0
| [Tuesday 07 December 2010] [09:52:16] <sustrik_>	let me ask steven
| [Tuesday 07 December 2010] [10:17:32] <toni_>	hi there. I am using a REQ socket doing socket.recv(zmq.NOBLOCK), but I am getting a "ZMQError: Resource temporarily unavailable" (using the python binding). As I saw in the docs for recv and zmq.NONBLOCK, there is this little sentence:"If there are no messages available on the specified socket, the zmq_recv() function shall fail with errno set to EAGAIN." I dont really understand. So the NOBLOCK option raises an error in case no messag
| [Tuesday 07 December 2010] [10:20:32] <cremes>	toni_: you see that "resource unavailable" message when your REQ socket is *not* connected to any REP (or XREP) sockets
| [Tuesday 07 December 2010] [10:20:46] <cremes>	make sure you have a z-endpoint
| [Tuesday 07 December 2010] [10:21:01] <cremes>	with an active socket attached to it
| [Tuesday 07 December 2010] [10:21:53] <toni_>	cremes: but it should as it all works fine since I dont specify the NOBLOCk option @ recv()
| [Tuesday 07 December 2010] [10:22:32] <toni_>	maybe its not connected yet?
| [Tuesday 07 December 2010] [10:28:37] <Guthur>	Should the timeout work with subscriber nodes?
| [Tuesday 07 December 2010] [10:28:43] <Guthur>	with polling
| [Tuesday 07 December 2010] [10:29:13] <Guthur>	It works fine if I set -1, but seems to not pickup messages when a timeout value is set
| [Tuesday 07 December 2010] [10:31:40] <toni_>	cremes: okay, very strange.... the error disapears when I dont do zmq.NOBLOCK in s.recv(). When I specify the option, the error is raised. But why? The socket should be connected, as the error is not raised when no block is not specified
| [Tuesday 07 December 2010] [10:43:50] <cremes>	toni_: interesting... it's funny but i *only* ever do noblock send/recv so i don't understand what is happening in the blocking scenario
| [Tuesday 07 December 2010] [10:44:02] <cremes>	are you *certain* that the other socket has connected?
| [Tuesday 07 December 2010] [10:44:55] <toni_>	cremes: yes I am really certain. But I found the solution describes here https://github.com/zeromq/pyzmq/issues/36#issue/36
| [Tuesday 07 December 2010] [10:47:57] <cremes>	toni_: hmmm, ok
| [Tuesday 07 December 2010] [11:23:22] <mikko>	mato: looks like solaris10 is still not happy
| [Tuesday 07 December 2010] [11:24:21] <mato>	mikko: it used to be, has your visibility change broken something?
| [Tuesday 07 December 2010] [11:24:36] <mikko>	mato: http://build.valokuva.org/job/ZeroMQ2-core-master-SunStudio-solaris10/21/console
| [Tuesday 07 December 2010] [11:24:41] <mikko>	when building --with-pgm
| [Tuesday 07 December 2010] [11:25:07] <mato>	mikko: ah, ok, i'll look at it later, in the middle of dissecting the linux network stack with sustrik right now
| [Tuesday 07 December 2010] [11:25:45] <mikko>	tries to include <sys/epoll.h>
| [Tuesday 07 December 2010] [11:26:27] <mato>	i guess openpgm in zmq has not been ported to solaris properly then
| [Tuesday 07 December 2010] [11:28:50] <mikko>	will look into it tonight
| [Tuesday 07 December 2010] [12:27:21] <mikko>	pfffff
| [Tuesday 07 December 2010] [13:04:29] <toni_>	I am using  the python binding, having a REQ socket connected to a XREP socket. When I try to send from the REQ socket I get "zmq.core.error.ZMQError: Operation cannot be accomplished in current state". Any ideas?
| [Tuesday 07 December 2010] [13:06:33] <cremes>	toni_: yes, req/rep sockets enforce a strict 1 send / 1 recv model; trying to do 2 sends or 2 recvs in a row generates a state machine error
| [Tuesday 07 December 2010] [13:06:46] <cremes>	look at the docs for req/rep
| [Tuesday 07 December 2010] [13:12:42] <drbobbeaty>	sustrik: my patch has a problem with it... I need to send you an additional change for using sequence numbers with OpenPGM. My mistake. Sorry.
| [Tuesday 07 December 2010] [13:12:54] <toni_>	cremes: Thanks, thats the code snippet: https://gist.github.com/732161 the "aaaa". See the link for the traceback
| [Tuesday 07 December 2010] [13:13:27] <drbobbeaty>	sustrik: maybe it's not a problem... I'll send the details to the mailing list and you can decide.
| [Tuesday 07 December 2010] [13:13:56] <cremes>	toni_: your problem is at line 40
| [Tuesday 07 December 2010] [13:14:06] <cremes>	you need a recv in that block
| [Tuesday 07 December 2010] [13:14:12] <cremes>	again, read the docs on req/rep
| [Tuesday 07 December 2010] [13:14:20] <cremes>	you must do alternating send/recv with each one
| [Tuesday 07 December 2010] [13:14:37] <cremes>	you *cannot* just send with either socket; there must always be a matching recv
| [Tuesday 07 December 2010] [13:14:51] <cremes>	the pattern is request/reply, not request/request/request/request/reply
| [Tuesday 07 December 2010] [13:14:53] <cremes>	:)
| [Tuesday 07 December 2010] [13:19:58] <toni_>	cremes: thanks
| [Tuesday 07 December 2010] [13:20:38] <cremes>	toni_: you are welcome... be sure to check out the guide on the web site; it covers that topic
| [Tuesday 07 December 2010] [13:21:29] <cremes>	andrewvc: planning to do another ffi-rzmq and zmqmachine release after 2.1 is out of beta
| [Tuesday 07 December 2010] [13:21:41] <andrewvc>	nice!
| [Tuesday 07 December 2010] [13:21:43] <cremes>	if you have anything you'd like to be in there, that's our deadline ;)
| [Tuesday 07 December 2010] [13:22:03] <toni_>	cremes: I already read it, I also constructed the very last example in python. I just had some truble with the NOBLOCK option and tried to debug from scretch. Maybe its enough for today, after 10 hours of coding :-)
| [Tuesday 07 December 2010] [13:22:03] <andrewvc>	well, I was hoping to hack on it sometime soon, but I'm moving this weekend
| [Tuesday 07 December 2010] [13:22:15] <andrewvc>	I've had about zero free time the last couple weeks
| [Tuesday 07 December 2010] [13:22:25] <andrewvc>	unfortunately
| [Tuesday 07 December 2010] [13:22:38] <cremes>	toni_: np; we'll be here in channel next time you need help... take a break
| [Tuesday 07 December 2010] [13:22:51] <cremes>	andrewvc: yeah, real life is constantly getting in the way!
| [Tuesday 07 December 2010] [13:23:05] <andrewvc>	lol, so true
| [Tuesday 07 December 2010] [13:23:25] <andrewvc>	i'm actually going to la.rb hack night tonight, was hoping to get a little EM work there
| [Tuesday 07 December 2010] [13:23:45] <cremes>	cool... see if you can't recruit a few more 0mq hackers
| [Tuesday 07 December 2010] [13:24:06] <andrewvc>	hehe, I'm trying it's so fun to play with.
| [Tuesday 07 December 2010] [13:24:23] <andrewvc>	evanphx is usually there btw, I know you worked pretty closely with him on some ffi bugs right?
| [Tuesday 07 December 2010] [13:25:21] <cremes>	andrewvc: yeah, i did; the api drift between the rbx ffi support and the ffi gem caused him a lot of grief
| [Tuesday 07 December 2010] [13:25:35] <cremes>	he was pretty upset about *many* of the additions
| [Tuesday 07 December 2010] [13:25:51] <andrewvc>	hehe, yeah we had a similar conversation
| [Tuesday 07 December 2010] [13:25:55] <cremes>	i use 0mq with rbx daily; it's the best way to profile and debug my code these days
| [Tuesday 07 December 2010] [13:26:04] <andrewvc>	agreed, best stack trace for issues
| [Tuesday 07 December 2010] [13:26:13] <cremes>	yep, that too
| [Tuesday 07 December 2010] [13:26:26] <cremes>	it's quickly becoming my ruby of choice
| [Tuesday 07 December 2010] [13:26:38] <andrewvc>	I've wanted to test my employers code on rbx, but hpricot's sitting in the way
| [Tuesday 07 December 2010] [13:26:39] <cremes>	as soon as it gets windows support i'll use it there too
| [Tuesday 07 December 2010] [13:26:50] <cremes>	C extension issues?
| [Tuesday 07 December 2010] [13:27:08] <andrewvc>	yep, and I think it's one that no one's planning on fixing
| [Tuesday 07 December 2010] [13:27:24] <cremes>	direct RHASH access or something nutty?
| [Tuesday 07 December 2010] [13:28:48] <andrewvc>	oh, well look what google turned up https://github.com/rubinius/hpricot
| [Tuesday 07 December 2010] [13:28:57] <andrewvc>	someone did fix it lol
| [Tuesday 07 December 2010] [13:29:02] <cremes>	ha!
| [Tuesday 07 December 2010] [13:29:11] <cremes>	no more excuses, andrewvc !
| [Tuesday 07 December 2010] [13:29:14] <andrewvc>	hehe
| [Tuesday 07 December 2010] [13:29:32] <andrewvc>	nope, well, one more, engineyard doesn't officially support rbx, but that's a minor hurdle
| [Tuesday 07 December 2010] [13:29:47] <cremes>	really? well, that's got to change sometime soon
| [Tuesday 07 December 2010] [13:29:54] <cremes>	it's all ey guys working on it!
| [Tuesday 07 December 2010] [13:29:59] <andrewvc>	yeah, weird eh?
| [Tuesday 07 December 2010] [13:30:19] <cremes>	oh, i know why... they are having trouble creating an ebuild recipe for it under gentoo
| [Tuesday 07 December 2010] [13:30:29] <andrewvc>	the default choices are only 1.8.7, REE and 1.8.6
| [Tuesday 07 December 2010] [13:30:29] <cremes>	i saw whyaines chatting about it with evan recently
| [Tuesday 07 December 2010] [13:30:40] <cremes>	no jruby even?
| [Tuesday 07 December 2010] [13:30:44] <andrewvc>	no
| [Tuesday 07 December 2010] [13:30:45] <cremes>	now i'm shocked
| [Tuesday 07 December 2010] [13:30:55] <andrewvc>	but the reality of EY is that everyone uses chef and customizes everything
| [Tuesday 07 December 2010] [13:31:07] <andrewvc>	EY is more a starting point than a destination
| [Tuesday 07 December 2010] [13:31:12] <cremes>	hmmmmm
| [Tuesday 07 December 2010] [13:31:20] <andrewvc>	not like heroku at all, we have so many changes to the stack
| [Tuesday 07 December 2010] [14:11:23] <raspi>	where i could find config examples for zmq_(queue|forwarder|streamer). manual gives only TBA.
| [Tuesday 07 December 2010] [14:50:40] <mikko>	raspi: i think in the code at the moment
| [Tuesday 07 December 2010] [14:50:50] <mikko>	raspi: i don't think there are written examples anywhere
| [Tuesday 07 December 2010] [14:51:10] <raspi>	ok :)
| [Tuesday 07 December 2010] [14:51:32] <mikko>	if you look at devices/zmq_queue/ in the source
| [Tuesday 07 December 2010] [14:51:41] <mikko>	the schema should be fairly easy to deduct from the code
| [Tuesday 07 December 2010] [15:58:54] <toni_>	I have a REQ client connected to 2 XREP server. When one server dies, the socket.recv() on the client blocks for ever. The other server is still available, but doesnt get any requests. How can I prevent this starvation?
| [Tuesday 07 December 2010] [15:59:47] <toni_>	I also tried to use a nonblocking XREQ socket on the client and ran in the same issue
| [Tuesday 07 December 2010] [16:04:38] <mikko>	it blocks even if you pass ZMQ_NOBLOCK?
| [Tuesday 07 December 2010] [16:06:15] <toni_>	I thought the XREQ socket would be nonblocking?
| [Tuesday 07 December 2010] [16:07:34] <mikko>	it has unrestricted send/receive pattern but it's no non-blocking by default as far as i know
| [Tuesday 07 December 2010] [16:07:59] <mikko>	have you tried passing ZMQ_NOBLOCK to recv and checking for EAGAIN ?
| [Tuesday 07 December 2010] [16:09:04] <mikko>	you can also look at zmq_poll
| [Tuesday 07 December 2010] [16:09:23] <toni_>	mikko yes I did. I found the snippet at the pyzmq issues
| [Tuesday 07 December 2010] [16:11:20] <toni_>	mikko: thanks, I think I found my bug
| [Tuesday 07 December 2010] [16:12:02] <mikko>	np
| [Tuesday 07 December 2010] [22:25:09] <PeterTork>	Hello. I have a rather odd model that I want to build in 0MQ and was looking for some advice there. We have web servers running presentation code, and they are being designed to talk to a one or more processes (which we are jokingly calling the MCP) that will do various validation tests on the RPC calls they are making before handing them to another layer of servers that will handle actually doing stuff. We would like to h
| [Tuesday 07 December 2010] [22:38:35] <Steve-o>	like to h...?
| [Tuesday 07 December 2010] [22:39:08] <Steve-o>	Are you looking from Mongrel2?  http://mongrel2.org/home
| [Tuesday 07 December 2010] [22:46:52] <Steve-o>	PeterTork: IRC limits line length, try the mailing list if you want to post a longer question
| [Tuesday 07 December 2010] [22:54:26] <bsiemon>	hello all, A quick question about an example from the guide. In examples/C/lruqueue.c. If one removes the id assignment from the client threads, the clients see to no longer receive messages.
| [Tuesday 07 December 2010] [22:54:50] <bsiemon>	on os x, zmq build 2.0.10
| [Tuesday 07 December 2010] [22:56:46] <bsiemon>	it seems to only happen if the client is running within its own process rather than in a thread with the other example code
| [Tuesday 07 December 2010] [23:04:38] <Steve-o>	bsiemon: does this also occur with 2.1, or could it be a permission problem with the unix socket endpoint?
| [Tuesday 07 December 2010] [23:04:54] <bsiemon>	it did also occur in 2.1
| [Tuesday 07 December 2010] [23:05:00] <bsiemon>	but I think I am just being dumb
| [Tuesday 07 December 2010] [23:05:10] <bsiemon>	sorry to bother you
| [Tuesday 07 December 2010] [23:06:19] <Steve-o>	from what I can see from the source code I would move the endpoints to /tmp
| [Tuesday 07 December 2010] [23:06:47] <Steve-o>	it doesn't look like the code will work out of the box
| [Tuesday 07 December 2010] [23:09:17] <bsiemon>	Steve-o: I see
| [Tuesday 07 December 2010] [23:09:29] <bsiemon>	Steve-o: Thanks
| [Tuesday 07 December 2010] [23:09:34] <Steve-o>	look at zmq_ipc for example usage, http://api.zeromq.org/zmq_ipc.html
| [Tuesday 07 December 2010] [23:13:02] <Steve-o>	well try a different path, the example path should be the current directory
| [Tuesday 07 December 2010] [23:13:41] <Steve-o>	so you should see a frontend.ipc and backend.ipc file in the directory listing,
| [Tuesday 07 December 2010] [23:14:26] <bsiemon>	yes I see that now
| [Tuesday 07 December 2010] [23:15:05] <Steve-o>	You might have issues with multiple users, discussion can be found on the list:  http://www.mail-archive.com/zeromq-dev@lists.zeromq.org/msg03151.html
| [Tuesday 07 December 2010] [23:16:34] <bsiemon>	Steve-o: If I put the call to s_set_id back into the client code
| [Tuesday 07 December 2010] [23:16:45] <bsiemon>	Steve-o: It works with out a hitch
| [Tuesday 07 December 2010] [23:17:22] <Steve-o>	oh ok
| [Tuesday 07 December 2010] [23:18:09] <bsiemon>	Is there anything special to with uuid generation on os x?
| [Tuesday 07 December 2010] [23:18:34] <bsiemon>	from what I have read the lib call seem to be different from os x to linux
| [Tuesday 07 December 2010] [23:19:10] <bsiemon>	I am sure I will slog through it, thanks for the help!
| [Tuesday 07 December 2010] [23:21:45] <Steve-o>	bsiemon: pass, some Linux versions have another library with the same name
| [Tuesday 07 December 2010] [23:22:48] <Steve-o>	it does look the same from the documentation, http://developer.apple.com/library/mac/#documentation/Darwin/Reference/ManPages/man3/uuid.3.html
| [Tuesday 07 December 2010] [23:42:15] <Steve-o>	lol, the lruqueue example aborts on Linux
| [Wednesday 08 December 2010] [03:38:19] <zedas>	sustrik: looks like debian included mongrel2, but included the old 2.0.6 version before the api change for zmq_init
| [Wednesday 08 December 2010] [03:39:16] <sustrik>	hm
| [Wednesday 08 December 2010] [03:39:22] <sustrik>	0mq is in debian-unstable
| [Wednesday 08 December 2010] [03:40:32] <sustrik>	we deliberately haven't pushed it to the stable as we weren't 100% sure about the API by then
| [Wednesday 08 December 2010] [03:47:14] <Guthur>	circa my question yesterday, can anyone confirm that poll timeouts are working with sub nodes
| [Wednesday 08 December 2010] [03:50:30] <sustrik>	Guthur: are they not?
| [Wednesday 08 December 2010] [03:51:11] <Guthur>	does seem to be working for me, the code works fine when I set -1
| [Wednesday 08 December 2010] [03:51:17] <Guthur>	dose/doesn't
| [Wednesday 08 December 2010] [03:51:47] <Guthur>	but if I actually set a timeout it seems to timeout quickly and I receive nothing
| [Wednesday 08 December 2010] [03:56:56] <sustrik>	what version are you using?
| [Wednesday 08 December 2010] [04:00:26] <Guthur>	2.0.10
| [Wednesday 08 December 2010] [04:00:41] <sustrik>	ah, that's a documented behaviour
| [Wednesday 08 December 2010] [04:00:43] <Guthur>	sustrik: ^
| [Wednesday 08 December 2010] [04:00:51] <Guthur>	oh you seen, sorry
| [Wednesday 08 December 2010] [04:00:57] <sustrik>	zmq_poll waits for "up to" microseconds
| [Wednesday 08 December 2010] [04:01:05] <Guthur>	Yeah I seen the upto
| [Wednesday 08 December 2010] [04:01:15] <sustrik>	anyway, this have been changed in 2.1
| [Wednesday 08 December 2010] [04:01:15] <Guthur>	but it's not actually 'working' in any sense
| [Wednesday 08 December 2010] [04:01:30] <sustrik>	it honours timeouts precisely
| [Wednesday 08 December 2010] [04:01:52] <sustrik>	is there a bug?
| [Wednesday 08 December 2010] [04:01:55] <Guthur>	ok, but surely as it stands in 2.0.10 its pretty much broke
| [Wednesday 08 December 2010] [04:02:05] <sustrik>	what's the problem?
| [Wednesday 08 December 2010] [04:02:36] <Guthur>	Well it timeout so quick that I don't receive anything
| [Wednesday 08 December 2010] [04:02:45] <Guthur>	and this isn't exactly a slow connection
| [Wednesday 08 December 2010] [04:03:03] <Guthur>	It's local TCP
| [Wednesday 08 December 2010] [04:03:03] <sustrik>	well, it's documented behaviour
| [Wednesday 08 December 2010] [04:03:12] <sustrik>	you have to restart the poll in such case
| [Wednesday 08 December 2010] [04:03:17] <sustrik>	or switch to 2.1 :)
| [Wednesday 08 December 2010] [04:03:40] <Guthur>	hehe, ok
| [Wednesday 08 December 2010] [04:03:43] <sustrik>	actually, it's a performance issue
| [Wednesday 08 December 2010] [04:04:06] <sustrik>	the poll that can exit prematurely is faster than the one honouring the timeout
| [Wednesday 08 December 2010] [04:04:20] <sustrik>	what we've done in 2.1 was adding ZMQ_FD
| [Wednesday 08 December 2010] [04:04:31] <Guthur>	so I suppose in 2.0.10 what one would have to do is engineer some honourable timeout mechanism on top
| [Wednesday 08 December 2010] [04:04:47] <sustrik>	which allows you to poll and handle timeouts yourself
| [Wednesday 08 December 2010] [04:04:50] <sustrik>	efficiently
| [Wednesday 08 December 2010] [04:05:01] <sustrik>	zmq_poll is less efficient but honours timeouts
| [Wednesday 08 December 2010] [04:05:07] <Guthur>	so really it's just a non blocking poll
| [Wednesday 08 December 2010] [04:05:10] <Guthur>	essentially
| [Wednesday 08 December 2010] [04:05:27] <Guthur>	the 2.0.10 version that is
| [Wednesday 08 December 2010] [04:05:35] <sustrik>	Guthur: it blocks
| [Wednesday 08 December 2010] [04:05:39] <sustrik>	but can exit at times
| [Wednesday 08 December 2010] [04:05:54] <sustrik>	basically, it exits when "something happens"
| [Wednesday 08 December 2010] [04:06:03] <sustrik>	say a new connection is established or somesuch
| [Wednesday 08 December 2010] [04:06:15] <Guthur>	my behaviour is that it timeouts in approximately less than a second
| [Wednesday 08 December 2010] [04:06:20] <Guthur>	no matter what I set
| [Wednesday 08 December 2010] [04:06:42] <sustrik>	possibly the connection being established
| [Wednesday 08 December 2010] [04:06:57] <Guthur>	I'll try 2.1
| [Wednesday 08 December 2010] [04:07:02] <sustrik>	ok
| [Wednesday 08 December 2010] [04:07:42] <Guthur>	my only worry with 2.1 is that it is not yet very mature
| [Wednesday 08 December 2010] [04:07:57] <Guthur>	i.e. there has been very little room for feedback
| [Wednesday 08 December 2010] [04:09:32] <sustrik>	it's up to you
| [Wednesday 08 December 2010] [04:09:43] <sustrik>	in 2.0 you can simply add a wrapper function on top of zmq_poll
| [Wednesday 08 December 2010] [04:09:55] <sustrik>	that would check for whether the timout was reached
| [Wednesday 08 December 2010] [04:10:02] <sustrik>	and restart the poll if it was not
| [Wednesday 08 December 2010] [04:10:13] <Guthur>	it depends on how soon we roll out to our app
| [Wednesday 08 December 2010] [04:10:48] <Guthur>	our rollout certainly wont be until some time in 2011 so it might be ok
| [Wednesday 08 December 2010] [04:11:08] <sustrik>	that's three weeks :)
| [Wednesday 08 December 2010] [04:11:19] <sustrik>	anyway, even the wrapper function is viable
| [Wednesday 08 December 2010] [04:11:25] <sustrik>	it's 10 lines of code
| [Wednesday 08 December 2010] [04:13:02] <Guthur>	hehe, I suppose writing a wrapper will give me some coding to do this morning
| [Wednesday 08 December 2010] [04:14:10] <sustrik>	now = gettimeofday ();
| [Wednesday 08 December 2010] [04:14:18] <sustrik>	while (true) {
| [Wednesday 08 December 2010] [04:14:32] <sustrik>	    events = zmq_poll ();
| [Wednesday 08 December 2010] [04:14:57] <sustrik>	    if (!events && now + timeout > gettimeofday ())
| [Wednesday 08 December 2010] [04:15:03] <sustrik>	      continue;
| [Wednesday 08 December 2010] [04:15:06] <sustrik>	   break;
| [Wednesday 08 December 2010] [04:15:06] <sustrik>	}
| [Wednesday 08 December 2010] [04:15:10] <sustrik>	that's it
| [Wednesday 08 December 2010] [04:15:40] <Guthur>	man you just sucked the fun out of it, hehe
| [Wednesday 08 December 2010] [04:15:51] <sustrik>	oooooopw
| [Wednesday 08 December 2010] [04:15:54] <sustrik>	oops
| [Wednesday 08 December 2010] [04:20:02] <Guthur>	ah that's better
| [Wednesday 08 December 2010] [04:20:17] <Guthur>	three lines of C# code
| [Wednesday 08 December 2010] [04:20:31] <sustrik>	!
| [Wednesday 08 December 2010] [04:21:07] <Guthur>	Stopwatch timer = new Stopwatch();             timer.Start();             while (timer.ElapsedMilliseconds < timeout && ctx.Poll(items, timeout) == 0);
| [Wednesday 08 December 2010] [04:21:16] <Guthur>	oh it did do new lines
| [Wednesday 08 December 2010] [04:21:19] <Guthur>	sorry about hat
| [Wednesday 08 December 2010] [04:21:22] <Guthur>	that
| [Wednesday 08 December 2010] [04:21:28] <Guthur>	didn't
| [Wednesday 08 December 2010] [04:21:30] <sustrik>	np
| [Wednesday 08 December 2010] [04:21:33] <sustrik>	i see it
| [Wednesday 08 December 2010] [04:21:51] <sustrik>	yes, that's was the idea with 2.0.x
| [Wednesday 08 December 2010] [04:21:58] <sustrik>	the performace issue i've mentioned before is the need to measure time at the beginning of the function
| [Wednesday 08 December 2010] [04:22:19] <sustrik>	if you don't care about honouring timeouts precisely you can avoid that overhead
| [Wednesday 08 December 2010] [04:23:12] <Guthur>	no problem, I had read the non-honouring part, I should have heeded it more
| [Wednesday 08 December 2010] [04:24:32] <Guthur>	I kind of assumed it was more precision thing and that it would just be out by a few micros 
| [Wednesday 08 December 2010] [04:24:36] <Guthur>	damn assumptions
| [Wednesday 08 December 2010] [04:26:57] <Guthur>	cheers for clearing that up sustrik 
| [Wednesday 08 December 2010] [04:27:15] <sustrik>	you are welcome
| [Wednesday 08 December 2010] [04:32:13] <Guthur>	minor bug in mine there, I assumed milliseconds
| [Wednesday 08 December 2010] [04:32:36] <Guthur>	small change just, microsecond is really high res
| [Wednesday 08 December 2010] [12:41:38] <mikko>	howdy
| [Wednesday 08 December 2010] [12:58:32] <jhawk28_>	sustrik: has the zmq team thought about providing a durable pub/sub socket?
| [Wednesday 08 December 2010] [12:59:04] <seb`>	jhawk28_: durable? with disk sync?
| [Wednesday 08 December 2010] [13:00:22] <jhawk28_>	durable - req/rep for requesting off queue. Fully persistent on disc for when publisher goes down
| [Wednesday 08 December 2010] [13:01:37] <jhawk28_>	http://sna-projects.com/kafka/design.php has some interesting approaches to get it to be fast
| [Wednesday 08 December 2010] [13:02:14] <sustrik>	what if the disk on the middle node fails :)
| [Wednesday 08 December 2010] [13:02:33] <jhawk28_>	no, not broker style
| [Wednesday 08 December 2010] [13:02:59] <seb`>	jhawk28_: if you need a broker you could use rabbitmq with the 0mq plugin
| [Wednesday 08 December 2010] [13:03:04] <seb`>	that could be fun
| [Wednesday 08 December 2010] [13:03:10] <sustrik>	saving data to disk on endpoints?
| [Wednesday 08 December 2010] [13:03:15] <sustrik>	you can do that in you app
| [Wednesday 08 December 2010] [13:03:27] <sustrik>	your*
| [Wednesday 08 December 2010] [13:04:12] <sustrik>	this is what most applications with reliability requirements do anyway
| [Wednesday 08 December 2010] [13:04:23] <sustrik>	they have data on disk (in DB or something)
| [Wednesday 08 December 2010] [13:05:06] <mikko>	i thought about this issue at some point as well
| [Wednesday 08 December 2010] [13:05:20] <mikko>	came up in to conclusion that it is a lot easier to do in app level
| [Wednesday 08 December 2010] [13:05:40] <mikko>	as you can choose different kind of backends (such as bdb etc) without having to have that requirement in the core
| [Wednesday 08 December 2010] [13:05:56] <sustrik>	right
| [Wednesday 08 December 2010] [13:05:58] <sustrik>	and it's kind of inpossible to push reliability to the network
| [Wednesday 08 December 2010] [13:06:13] <sustrik>	the networks are notoriously unreliable
| [Wednesday 08 December 2010] [13:06:49] <mikko>	maybe we could provide an example of durable device
| [Wednesday 08 December 2010] [13:06:56] <mikko>	rather than incorporate into core
| [Wednesday 08 December 2010] [13:07:09] <jhawk28_>	I was thinking that I would start with the device route
| [Wednesday 08 December 2010] [13:07:46] <mikko>	maybe you could do a generic "callback" device
| [Wednesday 08 December 2010] [13:07:47] <jhawk28_>	but, I was thinking that it might be cleaner if it ended up as a socket
| [Wednesday 08 December 2010] [13:08:03] <mikko>	have function pointers when message is received and sent
| [Wednesday 08 December 2010] [13:08:15] <mikko>	jhawk28_: cleaner from what point of view?
| [Wednesday 08 December 2010] [13:08:30] <jhawk28_>	cleaner API
| [Wednesday 08 December 2010] [13:08:42] <jhawk28_>	the end user API
| [Wednesday 08 December 2010] [13:08:51] <mikko>	from application code point of view yes, but it does mean a) design a durable storage b) add a large dependency to core
| [Wednesday 08 December 2010] [13:09:16] <jhawk28_>	a)
| [Wednesday 08 December 2010] [13:09:30] <mikko>	designing persistent storage for this kind of task is not a trivial exercise
| [Wednesday 08 December 2010] [13:09:30] <sustrik>	well, i've seen how AMQP working group struggled for years to meld the networking and persistence together into a single spec
| [Wednesday 08 December 2010] [13:09:31] <jhawk28_>	base it off kafka or bitcask
| [Wednesday 08 December 2010] [13:09:38] <sustrik>	and it doesn't really lead to anything sane
| [Wednesday 08 December 2010] [13:09:42] <mikko>	if you for example look at how long it has taken for Varnish to nail it down
| [Wednesday 08 December 2010] [13:10:23] <jhawk28_>	kafka is probably closer since it just needs a queue mechanism, but they are both kinda similar
| [Wednesday 08 December 2010] [13:11:45] <jhawk28_>	biggest problem Ive seen with message queue persistence is that they can't scale to a huge number of messages
| [Wednesday 08 December 2010] [13:11:59] <mikko>	you possibly want a cleanup mechanism, expiration, maybe you want the store to be accessible from other programs as well
| [Wednesday 08 December 2010] [13:12:43] <jhawk28_>	kafka basically uses a directory as the message queue
| [Wednesday 08 December 2010] [13:12:54] <jhawk28_>	files are created in an ordered fashion
| [Wednesday 08 December 2010] [13:13:13] <jhawk28_>	the client is what determines what message id to start from
| [Wednesday 08 December 2010] [13:13:44] <mikko>	is there a concept of expiration?
| [Wednesday 08 December 2010] [13:13:48] <jhawk28_>	the cleanup is by default handled by time or size
| [Wednesday 08 December 2010] [13:14:23] <jhawk28_>	other mechanisms can be plugged in I believe
| [Wednesday 08 December 2010] [13:15:16] <jhawk28_>	the client effectively controls their state so they can restart if need
| [Wednesday 08 December 2010] [13:16:05] <mikko>	bbl, need to commute home ->
| [Wednesday 08 December 2010] [14:28:14] <mikko>	back
| [Wednesday 08 December 2010] [14:47:57] <wayneeseguin>	nice
| [Wednesday 08 December 2010] [14:48:22] <cremes>	welcome
| [Wednesday 08 December 2010] [14:49:49] <wayneeseguin>	I am new to this and I am trying to determine which socket type to use
| [Wednesday 08 December 2010] [14:50:33] <wayneeseguin>	I am playing around with an example just to see if I can get it working.
| [Wednesday 08 December 2010] [14:50:36] <cremes>	wayneeseguin: definitely read the guide at the zeromq site
| [Wednesday 08 December 2010] [14:50:58] <cremes>	it covers a LOT of novice questions
| [Wednesday 08 December 2010] [14:50:58] <wayneeseguin>	I had however perhaps I should do it again as that was a month or so ago
| [Wednesday 08 December 2010] [14:53:51] <cremes>	alternately, ask your question
| [Wednesday 08 December 2010] [14:54:05] <cremes>	if it's answered in the guide, i'll point you to it
| [Wednesday 08 December 2010] [14:54:06] <cremes>	othe
| [Wednesday 08 December 2010] [14:54:25] <cremes>	otherwise, i'll try to answer it
| [Wednesday 08 December 2010] [14:57:01] <wayneeseguin>	I am fine reading docs :) 
| [Wednesday 08 December 2010] [14:57:35] <wayneeseguin>	I want to have a client - server relationship where the client sends updates to the server on an interval and the server can request information from the client at random
| [Wednesday 08 December 2010] [14:57:51] <wayneeseguin>	I am unsure if there is one socket type that can facilitate that or if I should be using two distinct ones.
| [Wednesday 08 December 2010] [14:58:56] <sustrik>	is seems there are two different flows there
| [Wednesday 08 December 2010] [14:59:07] <sustrik>	PUB/SUB for updates
| [Wednesday 08 December 2010] [14:59:12] <sustrik>	REQ/REP for requests
| [Wednesday 08 December 2010] [14:59:41] <wayneeseguin>	ok
| [Wednesday 08 December 2010] [15:01:27] <cremes>	exactly
| [Wednesday 08 December 2010] [16:48:07] <toni__>	hey there. I have an issue with a XREQclient XREPserver architecture, where the client should resend a message to another server, in case the one he first sent the message dies. I described it in detail here: https://gist.github.com/733965 
| [Wednesday 08 December 2010] [17:19:27] <cremes>	toni__: you are understanding the problem correctly and 0mq is doing exactly what it should
| [Wednesday 08 December 2010] [17:19:57] <cremes>	when your server dies, the 0mq socket on the client should remove it from its list of usable endpoints
| [Wednesday 08 December 2010] [17:20:14] <toni__>	cremes: exactly
| [Wednesday 08 December 2010] [17:20:29] <cremes>	you are likely simulating a server death by putting it to sleep or something; make sure that when the server dies that it goes away completely
| [Wednesday 08 December 2010] [17:20:42] <cremes>	that way the socket will disconnect and you will get the behavior that you want
| [Wednesday 08 December 2010] [17:20:54] <cremes>	if it hangs forever, as far as 0mq is concerned it is still a valid endpoint
| [Wednesday 08 December 2010] [17:22:42] <toni__>	cremes: Yes, I am simulating a server death...
| [Wednesday 08 December 2010] [17:22:50] <toni__>	I sould make use of socket.close()
| [Wednesday 08 December 2010] [17:23:02] <cremes>	right; then you'll get what you want
| [Wednesday 08 December 2010] [17:23:02] <cremes>	\
| [Wednesday 08 December 2010] [17:23:31] <toni__>	cremes: Thanks for your hint!
| [Wednesday 08 December 2010] [17:23:57] <cremes>	np
| [Wednesday 08 December 2010] [17:51:51] <toni__>	cremes: Okay, I tried it with socket.close() but this does not seem to have any effect. I posted my 2 little code-snippets on gist: https://gist.github.com/734071 
| [Wednesday 08 December 2010] [17:54:00] <toni__>	It seems as if the client would still be connected to the server that died
| [Wednesday 08 December 2010] [17:55:13] <cremes>	toni__: how many of these servers are you starting up?
| [Wednesday 08 December 2010] [17:55:37] <toni__>	I start 3 servers, and then killing two of em
| [Wednesday 08 December 2010] [17:56:06] <cremes>	and after they print "socket closed" and die, your client is still trying to send new messages to them?
| [Wednesday 08 December 2010] [17:56:27] <toni__>	yes it is
| [Wednesday 08 December 2010] [17:56:34] <cremes>	try this...
| [Wednesday 08 December 2010] [17:56:46] <cremes>	1. have your client start and connect to 3 addresses *first*
| [Wednesday 08 December 2010] [17:56:50] <cremes>	2. start one server
| [Wednesday 08 December 2010] [17:56:55] <cremes>	see what your client does
| [Wednesday 08 December 2010] [17:57:03] <cremes>	3. start up the other 2 servers
| [Wednesday 08 December 2010] [17:57:08] <cremes>	see what your client does
| [Wednesday 08 December 2010] [17:57:16] <cremes>	4. kill 2 of your servers
| [Wednesday 08 December 2010] [17:57:20] <cremes>	see what your client does
| [Wednesday 08 December 2010] [17:57:51] <toni__>	cremes: Ill try it right now
| [Wednesday 08 December 2010] [18:12:52] <toni__>	cremes: I connected the client first. Then I started the first server. The client tries to send also to the other servers which are not running yet. Thats why it s first very slow. Then I start the next server, it goes faster. Starting the third server the client doesnt get any timeout and it s fast. Stopping the servers, it gets slow again...
| [Wednesday 08 December 2010] [18:14:26] <toni__>	seems like, the socket still tries to send to the addresses that are not available yet
| [Wednesday 08 December 2010] [18:35:44] <cremes>	toni__: weird; why don't you ask on the mailing list and include a gist of your code along with the results you have seen
| [Wednesday 08 December 2010] [18:35:54] <cremes>	maybe someone else can give a hint
| [Wednesday 08 December 2010] [18:36:58] <toni__>	cremes: I will post my snippets and the testcase. Thanks for your help.
| [Wednesday 08 December 2010] [18:43:20] <oxff>	is there any central message broker for PUB-SUB in the src distribution?
| [Wednesday 08 December 2010] [18:43:25] <oxff>	basically i look for something like rabbitmq
| [Wednesday 08 December 2010] [18:43:33] <oxff>	with an asynchronous i/o compatible c client library
| [Wednesday 08 December 2010] [18:43:38] <oxff>	so i want to have a central server
| [Wednesday 08 December 2010] [18:43:41] <oxff>	(cluster)
| [Wednesday 08 December 2010] [18:43:48] <oxff>	which publishers as well as subscribers can connect to
| [Wednesday 08 December 2010] [18:47:13] <oxff>	ah reading the doc, i get that this is not the scope of zeromq
| [Wednesday 08 December 2010] [18:47:14] <oxff>	too bad :/
| [Wednesday 08 December 2010] [18:54:33] <oxff>	ah, devices seems to be what iw ant
| [Wednesday 08 December 2010] [19:00:07] <oxff>	how can i get all FDs from a zeromq socket?
| [Wednesday 08 December 2010] [19:00:17] <oxff>	say, i want to embed zeromq into my existing libev app
| [Wednesday 08 December 2010] [19:01:08] <oxff>	seems that the only way to use zeromq asynchronously is to develop around zmq_poll
| [Wednesday 08 December 2010] [19:04:12] <cremes>	oxff: read up on ZM_FD and ZM_EVENTS
| [Wednesday 08 December 2010] [19:04:29] <cremes>	that is part of the 2.1 release (in beta) which makes it easy to use with other libraries
| [Wednesday 08 December 2010] [19:04:35] <oxff>	ah thanks
| [Wednesday 08 December 2010] [19:04:44] <cremes>	and zmq_poll is built on top of those primitives
| [Wednesday 08 December 2010] [19:05:45] <oxff>	wait it only gives me one fd per zmq_socket?
| [Wednesday 08 December 2010] [19:05:54] <oxff>	how does it work with a bind socket?
| [Wednesday 08 December 2010] [19:06:01] <oxff>	or multiple connected sockets?
| [Wednesday 08 December 2010] [19:07:25] <oxff>	does it create a fake fd/
| [Wednesday 08 December 2010] [19:07:28] <oxff>	?
| [Wednesday 08 December 2010] [19:13:04] <oxff>	looking at tcp_listener.cpp, it only returns the bound fd in get_fd
| [Wednesday 08 December 2010] [19:13:08] <oxff>	too tired to read all of the source
| [Wednesday 08 December 2010] [19:19:03] <oxff>	wait, does zeromq internally use threading / create threads for accepting new connectins etc?
| [Wednesday 08 December 2010] [19:22:10] <oxff>	how can i issue a non-blocking connect with zmq_connect?
| [Wednesday 08 December 2010] [19:28:28] <oxff>	lol you
| [Wednesday 08 December 2010] [19:28:41] <oxff>	you're threading and the fd is just some pipe fd you accumulate to?
| [Wednesday 08 December 2010] [19:28:44] <oxff>	this is bullshit
| [Wednesday 08 December 2010] [20:50:01] <testuser>	hello
| [Wednesday 08 December 2010] [22:55:31] 470	travlr #gwt ##gwt Forwarding to another channel
| [Wednesday 08 December 2010] [22:55:31] Notice	-ChanServ- [##gwt] Welcome to the unofficial Google Web Toolkit channel on freenode. This is a starting (and growing) community, and we need your help. Stick around!
| [Wednesday 08 December 2010] [22:55:45] 470	travlr #gwt ##gwt Forwarding to another channel
| [Wednesday 08 December 2010] [22:55:45] Notice	-ChanServ- [##gwt] Welcome to the unofficial Google Web Toolkit channel on freenode. This is a starting (and growing) community, and we need your help. Stick around!
| [Wednesday 08 December 2010] [22:55:55] 470	travlr #gwt ##gwt Forwarding to another channel
| [Wednesday 08 December 2010] [22:55:55] Notice	-ChanServ- [##gwt] Welcome to the unofficial Google Web Toolkit channel on freenode. This is a starting (and growing) community, and we need your help. Stick around!
| [Thursday 09 December 2010] [03:46:34] <rrg>	hi
| [Thursday 09 December 2010] [03:49:57] <rrg>	i am unsure how to implement multiplexed sending using a PUB socket. to be specific: a changing number of producers write multipart messages of varying length, at verying times and from varying threads. do i need to synchronize the writing somehow and abandon the multipart messaging alltogether?
| [Thursday 09 December 2010] [03:54:36] <Steve-o>	give each thread a 0mq socket then ensure each thread sends multi-part atomically
| [Thursday 09 December 2010] [03:57:39] <Steve-o>	you could always add extra sockets, i.e. one per session per thread too
| [Thursday 09 December 2010] [03:58:27] <mikko>	Steve-o: im getting openpgm compile failure on x86 solaris 10
| [Thursday 09 December 2010] [03:58:43] <Steve-o>	only tried opensolaris on intel
| [Thursday 09 December 2010] [03:59:07] <Steve-o>	have you updated the compiler flags?
| [Thursday 09 December 2010] [03:59:30] <Steve-o>	>> http://code.google.com/p/openpgm/source/browse/trunk/openpgm/pgm/SConstruct.OpenSolaris
| [Thursday 09 December 2010] [04:00:32] <mikko>	Steve-o: i have
| [Thursday 09 December 2010] [04:00:33] <mikko>	sec
| [Thursday 09 December 2010] [04:01:07] <mikko>	https://gist.github.com/123f088e350c12744e1c
| [Thursday 09 December 2010] [04:01:22] <mikko>	i was working on getting --with-pgm build to work on solaris10 using sun studio last night
| [Thursday 09 December 2010] [04:01:39] <Steve-o>	ok, x86/Solaris is pretty much a dead platform
| [Thursday 09 December 2010] [04:01:51] <mikko>	had to remove strict flag because __PRETTY_FUNCTION__ is not declared on strict compliance mode
| [Thursday 09 December 2010] [04:02:24] <Steve-o>	that's gcc only ?
| [Thursday 09 December 2010] [04:02:44] <mikko>	-Xc mode in solaris studio drops standards incompliant things
| [Thursday 09 December 2010] [04:02:55] <mikko>	__PRETTY_FUNCTION__ is "pseudo-standard"
| [Thursday 09 December 2010] [04:02:56] <Steve-o>	it should be picking up __func__ instead
| [Thursday 09 December 2010] [04:03:51] <Steve-o>	just checked, __PRETTY_FUNCTION__ should only be used with __GNUC__ defined
| [Thursday 09 December 2010] [04:04:12] <Steve-o>	I don't even bother with __func__, I think that's only SunPro 
| [Thursday 09 December 2010] [04:04:21] <Steve-o>	but your error is assembler
| [Thursday 09 December 2010] [04:04:25] <mikko>	__func__ is supported by all of them
| [Thursday 09 December 2010] [04:04:56] <mikko>	i guess it would be fairly easy to ifdef OPENPGM_FUNCTION or similar
| [Thursday 09 December 2010] [04:05:41] <mikko>	http://blogs.sun.com/solarisdev/entry/new_article_prefetching
| [Thursday 09 December 2010] [04:05:49] <Steve-o>	ok i see the problem
| [Thursday 09 December 2010] [04:06:00] <Steve-o>	I assume sun = sparc
| [Thursday 09 December 2010] [04:06:14] <Steve-o>	which is usually pretty good considering the other options are awful
| [Thursday 09 December 2010] [04:06:48] <Steve-o>	sunpro on linux doesn't define sun
| [Thursday 09 December 2010] [04:07:06] <Steve-o>	so what does "sun" mean?
| [Thursday 09 December 2010] [04:07:15] <Steve-o>	it's not there for opensolaris
| [Thursday 09 December 2010] [04:08:38] <mikko>	sun and __sun are defined for x86 solaris
| [Thursday 09 December 2010] [04:08:51] <mikko>	sparc and __sparc for SPARC 
| [Thursday 09 December 2010] [04:08:54] <mikko>	as far as i know
| [Thursday 09 December 2010] [04:09:01] <mikko>	i dont have access to sparc
| [Thursday 09 December 2010] [04:09:28] <Steve-o>	sparc is for ultrasparc and older
| [Thursday 09 December 2010] [04:09:45] <mikko>	http://predef.sourceforge.net/preos.html#sec35
| [Thursday 09 December 2010] [04:09:52] <mikko>	this says that it's for solaris operating system
| [Thursday 09 December 2010] [04:10:05] <Steve-o>	it's __sparcv9 for the box I have
| [Thursday 09 December 2010] [04:10:20] <Steve-o>	which probably makes __sparc a v8
| [Thursday 09 December 2010] [04:12:17] <Steve-o>	ok, have to guess which ones match gcc
| [Thursday 09 December 2010] [04:12:52] <Steve-o>	I don't even use them which makes it worse
| [Thursday 09 December 2010] [04:13:04] <Steve-o>	they're slower on the hardware I have
| [Thursday 09 December 2010] [04:13:12] <mikko>	interesting
| [Thursday 09 December 2010] [04:13:26] <mikko>	CC man page says that 'sun' is sparc only macro
| [Thursday 09 December 2010] [04:14:12] <mikko>	but that might be from time before solaris studio on x86
| [Thursday 09 December 2010] [04:14:15] <mikko>	not sure
| [Thursday 09 December 2010] [04:14:32] <Steve-o>	x86 solaris is really old, but yes there is a lot of confusion
| [Thursday 09 December 2010] [04:14:47] <Steve-o>	looks like prefetch -> sun_prefetch_read_many
| [Thursday 09 December 2010] [04:14:54] <Steve-o>	prefetchw -> sun_prefetch_write_many
| [Thursday 09 December 2010] [04:15:15] <Steve-o>	I'll have to switch on my sparc and check
| [Thursday 09 December 2010] [04:15:26] <rrg>	Steve-o: the cost of adding a socket is insignificant?
| [Thursday 09 December 2010] [04:15:35] <Steve-o>	I think I have a few fixes to back port to 5.0 too anyway
| [Thursday 09 December 2010] [04:16:13] <mikko>	Steve-o: i use +w -Xc to compile with sun studio
| [Thursday 09 December 2010] [04:16:16] <mikko>	if you want to test
| [Thursday 09 December 2010] [04:16:25] <Steve-o>	rrg:  0mq automagically manages the multiplexing, so once one underlying transport is setup it is cheap
| [Thursday 09 December 2010] [04:18:04] <rrg>	Steve-o: by setup you mean the context initialization?
| [Thursday 09 December 2010] [04:18:58] <Steve-o>	rrg: the IO thread(s) open up the TCP/IPC/PGM sockets in the background
| [Thursday 09 December 2010] [04:19:45] <rrg>	ah, ok. so context init = transport init
| [Thursday 09 December 2010] [04:20:57] <rrg>	Steve-o: but won't binding the socket work exactly once? in case of tcp/ip unicast?
| [Thursday 09 December 2010] [04:21:56] <Steve-o>	i'm going on what the whitepapers on the architecture say :-)
| [Thursday 09 December 2010] [04:24:35] <rrg>	Steve-o: ? -> /me ?
| [Thursday 09 December 2010] [04:27:28] <Steve-o>	brb, a couple of things working on
| [Thursday 09 December 2010] [04:29:24] <guido_g>	rrg: the context has nothing to do w/ a particular transport
| [Thursday 09 December 2010] [04:33:12] 	 * rrg wonders if this problem could be solved by opening multiple icp push connections and performing the actual tcp sending in a dedicated receiver thread of those multipart messages
| [Thursday 09 December 2010] [04:34:12] <guido_g>	icp?
| [Thursday 09 December 2010] [04:35:42] <rrg>	ipc
| [Thursday 09 December 2010] [04:35:51] <rrg>	guido_g: seems to work!
| [Thursday 09 December 2010] [04:37:23] <rrg>	guido_g: ok, i have single thread now which binds a pub socket to tcp and sits in a recv loop on an ipc pull socket.
| [Thursday 09 December 2010] [04:38:00] <rrg>	guide_g:  plus a certain amount of threads which send multipart messages to thread-specific ipc push sockets which they close when they terminate.
| [Thursday 09 December 2010] [04:38:31] <rrg>	guido_g: seems to work fine with 2 context i/o threads. any antipattern i'm using here?
| [Thursday 09 December 2010] [04:39:10] <guido_g>	2 contexts? seems fishy
| [Thursday 09 December 2010] [04:39:17] <Steve-o>	mikko:  aaagh, that strict mode is annoying
| [Thursday 09 December 2010] [04:41:11] <Steve-o>	I'm not even getting "sun" defined
| [Thursday 09 December 2010] [04:41:22] <toni_>	hey there. I have a XREQ client connected to a set of XREP servers. When one server dies, the client still tries to send messages to it. Is this the default zmq behavior, or am I doing something wrong? 
| [Thursday 09 December 2010] [04:42:16] <Steve-o>	mikko:  so strict mode presumably means only __sun is defined?  always the underscore requirement?
| [Thursday 09 December 2010] [04:43:13] <rrg>	guido_g: 2 i/o threads, 1 ctx
| [Thursday 09 December 2010] [04:44:21] <guido_g>	rrg: i dont think you need 2 io threads, it's a waste of ressources
| [Thursday 09 December 2010] [04:46:41] <rrg>	guido_g: is there any usecase for n>1 threads?
| [Thursday 09 December 2010] [04:47:05] <guido_g>	rrg: no, not that i know of
| [Thursday 09 December 2010] [04:48:59] <rrg>	guido_g: ok
| [Thursday 09 December 2010] [04:49:02] <rrg>	guido_g: ty
| [Thursday 09 December 2010] [04:52:00] <toni_>	I described my issue in detail here: https://gist.github.com/734545
| [Thursday 09 December 2010] [04:59:17] <Steve-o>	toni_:  send onto the list too
| [Thursday 09 December 2010] [04:59:38] <guido_g>	toni_: but first write a working test, please
| [Thursday 09 December 2010] [04:59:53] <toni_>	Steve-o: I did this. The working test is also linked
| [Thursday 09 December 2010] [04:59:54] <guido_g>	toni_: ahh... and remove the useles recursion
| [Thursday 09 December 2010] [05:00:29] <guido_g>	toni_: there're three code snippes that are obviously part of something else
| [Thursday 09 December 2010] [05:00:58] <toni_>	guido_g:  the snippets I linked ?
| [Thursday 09 December 2010] [05:01:15] <guido_g>	toni_: what else?
| [Thursday 09 December 2010] [05:01:20] <toni_>	guido_g: no thats exactly my code and my problem
| [Thursday 09 December 2010] [05:02:38] <guido_g>	toni_: why didn't you post the code as it is then? what you posted appears to be 3 unrelated snippets
| [Thursday 09 December 2010] [05:02:44] <toni_>	guido_g: My aproach is, that when a server does not answer for two seconds, I resend the message
| [Thursday 09 December 2010] [05:03:51] <toni_>	guido_g:  But the XREPServer and the XREQConnect are both used in the Testcase
| [Thursday 09 December 2010] [05:04:25] <Steve-o>	mikko:  I have trunk working with sun one in strict mode now, will have to try ICC later
| [Thursday 09 December 2010] [05:06:56] <toni_>	guido_g: in the Testcase I first start one server, than the second, then the third. Whenever one server is not available, my XREQ send method runs into the timeout as it does not get any reply for 2 seconds
| [Thursday 09 December 2010] [05:07:19] <toni_>	guido_g: and in this case I resend the message
| [Thursday 09 December 2010] [05:07:28] <guido_g>	toni_: i know, i can read
| [Thursday 09 December 2010] [05:09:10] <toni_>	guido_g: What I would need, is to tell the XREQ at XREQConnect to disconnect from the addresses that are obviously broken
| [Thursday 09 December 2010] [05:10:14] <guido_g>	toni_: mq should do that, if not, show a comprehensible working test case and file an issue
| [Thursday 09 December 2010] [05:13:05] <toni_>	guido_g: Okay, Ill open up an issue. Seems to me as if it s not working properly
| [Thursday 09 December 2010] [05:14:58] <guido_g>	toni_: make your test actually working and as small as possible, otherwise it'll be difficult to proof your point
| [Thursday 09 December 2010] [05:15:48] <toni_>	guido_g: yes I will. Thanks for your hints anyway.
| [Thursday 09 December 2010] [05:49:26] <toni_>	One question remains. In zmq I can connect a socket to some addresses (that never were bound before), send messages to it and they will be buffered until the addresses become available. So consider one client and two servers. The client connects to both. The messages are loadbalanced between the servers. When one server dies (s.close()) the client will try to send its message to that address. As it is not available they are buffered. A
| [Thursday 09 December 2010] [06:45:25] <sustrik_>	drbobbeaty: hi
| [Thursday 09 December 2010] [06:45:33] <sustrik_>	would you do the -1 default, or should i?
| [Thursday 09 December 2010] [06:47:28] <drbobbeaty>	sustrik: I'll be glad to. I just need to get a few things done this morning and then hamer it out.
| [Thursday 09 December 2010] [06:47:36] <sustrik_>	great
| [Thursday 09 December 2010] [06:47:51] <drbobbeaty>	I want to build RPMs, etc. to verify etc. So it'll take me just a little bit.
| [Thursday 09 December 2010] [06:47:59] <sustrik_>	sure, no haste
| [Thursday 09 December 2010] [06:52:10] <toni_>	I posted my problem here with a minimal testcase: https://github.com/zeromq/pyzmq/issues/issue/51
| [Thursday 09 December 2010] [06:57:39] <guido_g>	toni_: does it work if you start both servers and then kill one of them?
| [Thursday 09 December 2010] [06:59:12] <guido_g>	toni_: of course, after the client connected to them
| [Thursday 09 December 2010] [07:02:53] <toni_>	guido_g: no, when I start both servers, then starting the client e.g sending 100 000 msgs and then I kill one server, the client still tries to send to the death one
| [Thursday 09 December 2010] [07:03:50] <guido_g>	ouch
| [Thursday 09 December 2010] [07:04:02] <guido_g>	sounds really like a bug
| [Thursday 09 December 2010] [07:04:36] <toni_>	The testcase is quite simple, I hope everyone can reproduce this behavior
| [Thursday 09 December 2010] [07:10:48] <guido_g>	jepp, killing one of the servers causes a delay every other request
| [Thursday 09 December 2010] [07:13:05] <toni_>	guido_g: but actually, zmq should behave different and notice the death server?
| [Thursday 09 December 2010] [07:13:45] <guido_g>	should be in the docs
| [Thursday 09 December 2010] [07:15:55] <guido_g>	ahhh.. got it
| [Thursday 09 December 2010] [07:16:08] <guido_g>	set the HWM for the sending socket to 1, then it works
| [Thursday 09 December 2010] [07:19:01] <toni_>	guido_g: You are my hero !!!
| [Thursday 09 December 2010] [07:19:13] <toni_>	guido_g: hanging on this issue for almost 2 day now
| [Thursday 09 December 2010] [07:19:32] <toni_>	guido_g: Thanks a lot for your help!!!
| [Thursday 09 December 2010] [07:19:43] <guido_g>	the reason is -- i think -- the unbound queue for this endpoint
| [Thursday 09 December 2010] [07:20:10] <toni_>	guido_g: what do you mean by the unbound queue?
| [Thursday 09 December 2010] [07:20:50] <toni_>	guido_g: As far as I understood the HWM limits the send-buffer of the socket to the size of 1
| [Thursday 09 December 2010] [07:20:53] <guido_g>	every endpoint under a mq socket has a queue for messages to be sent to it
| [Thursday 09 December 2010] [07:21:19] <toni_>	ah okay, thats what I just called buffer...
| [Thursday 09 December 2010] [07:21:22] <guido_g>	not of the mq socket, but the underlying endpoint
| [Thursday 09 December 2010] [07:23:12] <toni_>	guido_g:  thanks for your help. Great project and great community
| [Thursday 09 December 2010] [08:38:25] <bobdole369>	Hello good morning, is zeromq used often with embedded devices? Specifically Rabbit Semiconductor stuff, or Schnieder (or others) PLC's?
| [Thursday 09 December 2010] [10:17:29] <mikko>	bobdole369: it might make sense to ask that question on the mailing-lists to reach bigger audience
| [Thursday 09 December 2010] [10:21:55] <Steve-o>	mikko: what strict parameters are you using for ICC?  I'll check tomorrow and update trunk for PGM
| [Thursday 09 December 2010] [10:31:25] <mikko>	Steve-o: sec
| [Thursday 09 December 2010] [10:31:46] <mikko>	-strict-ansi
| [Thursday 09 December 2010] [10:43:10] <Steve-o>	taa, will test with 5.1 and backport to 5.0
| [Thursday 09 December 2010] [10:43:18] <mikko>	cool
| [Thursday 09 December 2010] [10:44:04] <Steve-o>	only OSX needs 5.1 because of the lack of spin locks
| [Thursday 09 December 2010] [10:44:31] <Steve-o>	maybe something with Win x64 too but I can't recall
| [Thursday 09 December 2010] [11:25:48] <mikko>	sustrik: there?
| [Thursday 09 December 2010] [12:04:17] <sustrik>	mikko: hi
| [Thursday 09 December 2010] [12:05:19] <mikko>	sustrik: im having issues with ZMQ_QUEUE
| [Thursday 09 December 2010] [12:05:34] <sustrik>	yes?
| [Thursday 09 December 2010] [12:05:39] <mikko>	it seems that my messages are not being closed
| [Thursday 09 December 2010] [12:05:48] <mikko>	it's a bit tricky to reproduce
| [Thursday 09 December 2010] [12:05:59] <mikko>	but i got front=pull, back=push device
| [Thursday 09 December 2010] [12:06:14] <mikko>	and if i am not consuming the message the memory usage goes up steadily
| [Thursday 09 December 2010] [12:06:28] <mikko>	if i then start consumer the memory usage doesn't go down
| [Thursday 09 December 2010] [12:06:32] <mikko>	even though messages are flowing
| [Thursday 09 December 2010] [12:06:45] <mikko>	i can see using valgrind that memory is held in the messages
| [Thursday 09 December 2010] [12:06:53] <sustrik>	are you publishing at full spead?
| [Thursday 09 December 2010] [12:06:58] <sustrik>	speed
| [Thursday 09 December 2010] [12:07:25] <mikko>	yes
| [Thursday 09 December 2010] [12:07:54] <mikko>	is it expected that memory usage never goes down?
| [Thursday 09 December 2010] [12:08:31] <sustrik>	well, if receiver is slower than publisher it can happen
| [Thursday 09 December 2010] [12:08:54] <mikko>	but even if i stop publisher and start consuming
| [Thursday 09 December 2010] [12:09:03] <mikko>	it seems that usage does not go down
| [Thursday 09 December 2010] [12:12:27] <sustrik>	that looks like a leak
| [Thursday 09 December 2010] [12:12:51] <sustrik>	can you report the problem along with the test program?
| [Thursday 09 December 2010] [12:13:04] <mikko>	does this make sense:
| [Thursday 09 December 2010] [12:13:20] <mikko>	i generate 10k messages, then turn consumer on/off/on/off
| [Thursday 09 December 2010] [12:13:25] <mikko>	until no more messages flow through
| [Thursday 09 December 2010] [12:13:34] <mikko>	kinda simulating flaky network
| [Thursday 09 December 2010] [12:13:48] <mikko>	and at the end it seems that not all messages get freed
| [Thursday 09 December 2010] [12:13:54] <mikko>	but there is no more coming from pipe
| [Thursday 09 December 2010] [12:14:38] <sustrik>	how do you know they weren't freed?
| [Thursday 09 December 2010] [12:15:55] <mikko>	valgrind show them in "still reachable" memory
| [Thursday 09 December 2010] [12:18:10] <mikko>	it might be something in my app as well
| [Thursday 09 December 2010] [12:18:28] <mikko>	i will investigate further and open a ticket if it's somewhat reproducible
| [Thursday 09 December 2010] [12:36:51] <sustrik>	mikko: how did you shut down the device?
| [Thursday 09 December 2010] [12:37:06] <mikko>	sustrik: ctrl + c
| [Thursday 09 December 2010] [12:37:17] <sustrik>	let me check the code...
| [Thursday 09 December 2010] [12:37:27] <sustrik>	master?
| [Thursday 09 December 2010] [12:37:35] <mikko>	yes
| [Thursday 09 December 2010] [12:37:41] <mikko>	it could very well be my test code
| [Thursday 09 December 2010] [12:38:11] <mikko>	i need a statistics collection over http
| [Thursday 09 December 2010] [12:38:25] <mikko>	so im writing a small webserver that distributes the messages to backend nodes for processing
| [Thursday 09 December 2010] [12:43:20] <sustrik>	mikko: aha
| [Thursday 09 December 2010] [12:43:30] <sustrik>	the devices are not shutting down decently
| [Thursday 09 December 2010] [12:43:32] <sustrik>	if (errno == ETERM)
| [Thursday 09 December 2010] [12:43:32] <sustrik>	                        return -1;
| [Thursday 09 December 2010] [12:43:51] <sustrik>	what they should do, i guess
| [Thursday 09 December 2010] [12:44:05] <sustrik>	is to set LINGER to 0
| [Thursday 09 December 2010] [12:44:12] <sustrik>	and terminate via zmq_term()
| [Thursday 09 December 2010] [13:51:25] <delaney>	are there any examples of the proper use of socket.RecvAll() for C#?
| [Thursday 09 December 2010] [13:54:20] <sustrik>	delaney: i don't think there are much examples for clrzmq2, try asking on the mailing list
| [Thursday 09 December 2010] [13:54:49] <delaney>	k
| [Thursday 09 December 2010] [15:26:06] <sustrik_>	mikko: hm, i was wrong
| [Thursday 09 December 2010] [15:27:14] <sustrik_>	Ctrl+C actually kills the program, thus not freeing the allocated memory 
| [Thursday 09 December 2010] [15:27:29] <sustrik_>	so valgrind would naturally report leaks
| [Thursday 09 December 2010] [15:27:58] <sustrik_>	alternative would be to install SIGINT handler and try to clean-up before exiting
| [Thursday 09 December 2010] [15:45:10] <CIA-20>	zeromq2: 03Bob Beaty 07master * rfcfad56 10/ (6 files in 3 dirs): (log message trimmed)
| [Thursday 09 December 2010] [15:45:10] <CIA-20>	zeromq2: Added Recovery Interval in Milliseconds
| [Thursday 09 December 2010] [15:45:10] <CIA-20>	zeromq2: For very high-speed message systems, the memory used for recovery can get to
| [Thursday 09 December 2010] [15:45:10] <CIA-20>	zeromq2: be very large. The corrent limitation on that reduction is the ZMQ_RECOVERY_IVL
| [Thursday 09 December 2010] [15:45:10] <CIA-20>	zeromq2: of 1 sec. I added in an additional option ZMQ_RECOVERY_IVL_MSEC, which is the
| [Thursday 09 December 2010] [15:45:11] <CIA-20>	zeromq2: Recovery Interval in milliseconds. If used, this will override the previous
| [Thursday 09 December 2010] [15:45:11] <CIA-20>	zeromq2: one, and allow you to set a sub-second recovery interval. If not set, the
| [Thursday 09 December 2010] [15:45:12] <CIA-20>	zeromq2: 03Martin Sustrik 07master * ra9d969a 10/ AUTHORS : 
| [Thursday 09 December 2010] [15:45:13] <CIA-20>	zeromq2: Bob Beaty added to the AUTHORS file
| [Thursday 09 December 2010] [15:45:13] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/hqM7T8
| [Thursday 09 December 2010] [16:41:14] <mikko>	sustrik_: the thing i was seeing is that the memory just 'sits' there
| [Thursday 09 December 2010] [16:41:24] <mikko>	and doesn't go down during when the program runs
| [Thursday 09 December 2010] [16:46:02] <sustrik_>	that's the OS problem AFAIK
| [Thursday 09 December 2010] [16:46:24] <sustrik_>	OS doesn't return deallocated memory back to the shared pool
| [Thursday 09 December 2010] [16:46:36] <sustrik_>	rather the memory is kept by the running process
| [Thursday 09 December 2010] [16:47:19] <sustrik_>	Solaris claims that it's able to reuse the memory, but my tests haven't confirmed it
| [Thursday 09 December 2010] [16:49:29] <mikko>	i shouldn't see that memory in still reachable in valgrind though
| [Thursday 09 December 2010] [16:49:51] <sustrik_>	right, that's interesting
| [Thursday 09 December 2010] [16:49:58] <mikko>	but it might've been an application as i don't seem to be able to reproduce after a couple of hours of refactoring
| [Thursday 09 December 2010] [16:50:29] <sustrik_>	yes, this kind of problems is pretty hard to track down
| [Thursday 09 December 2010] [16:52:02] <sustrik_>	if you are able to reproduce in the future we can give it a try though
| [Thursday 09 December 2010] [16:54:29] <mikko>	cool
| [Thursday 09 December 2010] [16:54:36] <mikko>	the tool feels pretty stable now
| [Thursday 09 December 2010] [16:54:59] <mikko>	can push a bit over 3k http requests per second on my virtual machine which seems more than enough
| [Thursday 09 December 2010] [17:02:51] <sustrik_>	:)
| [Friday 10 December 2010] [00:55:58] <samBiotic>	could someone please help me get my ruby bindings working on osx.
| [Friday 10 December 2010] [00:56:17] <andrewvc>	samBiotic
| [Friday 10 December 2010] [00:56:23] <andrewvc>	what's going on on OSX?
| [Friday 10 December 2010] [00:56:25] <samBiotic>	zeromq has been installed with homebrew
| [Friday 10 December 2010] [00:56:33] <samBiotic>	brew install zeromq
| [Friday 10 December 2010] [00:56:33] <andrewvc>	also, which lib, ffi-rzmq or rbzmq
| [Friday 10 December 2010] [00:57:24] <andrewvc>	hmm, but which ruby binding
| [Friday 10 December 2010] [00:57:31] <andrewvc>	have you installed either of the zeromq gems yet?
| [Friday 10 December 2010] [00:57:36] <samBiotic>	yes
| [Friday 10 December 2010] [00:57:53] <andrewvc>	which one?
| [Friday 10 December 2010] [00:58:08] <samBiotic>	gem install zmq -- --with-zmq-dir=/usr/local
| [Friday 10 December 2010] [00:58:39] <andrewvc>	hmmm, I installed zmq for the tarball, and gem install zmq worked fine
| [Friday 10 December 2010] [00:58:42] <andrewvc>	*from
| [Friday 10 December 2010] [00:58:48] <andrewvc>	no idea about homebrew though
| [Friday 10 December 2010] [00:58:52] <samBiotic>	checking for zmq_init() in -lzmq... no
| [Friday 10 December 2010] [00:58:57] <andrewvc>	you could just try using the zmq tarball
| [Friday 10 December 2010] [00:59:16] <samBiotic>	hmm yes i could
| [Friday 10 December 2010] [00:59:17] <andrewvc>	I've never installed it through brew myself
| [Friday 10 December 2010] [00:59:24] <samBiotic>	ok will try now
| [Friday 10 December 2010] [00:59:37] <andrewvc>	cool, I know more about the search paths for ffi-rzmq
| [Friday 10 December 2010] [00:59:51] <andrewvc>	you might want to consider using ffi-rzmq btw
| [Friday 10 December 2010] [00:59:55] <samBiotic>	ok
| [Friday 10 December 2010] [01:00:18] <andrewvc>	unless you have a specific need for the slight speed boost of rbzmq (just my $0.02)
| [Friday 10 December 2010] [01:00:24] <samBiotic>	my aim is to build an open sound control multicaster eventually
| [Friday 10 December 2010] [01:00:59] <andrewvc>	cool project
| [Friday 10 December 2010] [01:01:45] <samBiotic>	i have forward scheduling of packets working but time to live reductions would be preferable
| [Friday 10 December 2010] [01:02:16] <Steve-o>	samBiotic: is that like the BBCs project?
| [Friday 10 December 2010] [01:02:29] <samBiotic>	what would that be?
| [Friday 10 December 2010] [01:03:00] <andrewvc>	samBiotic, with that kind of time constraint, wouldn't ruby's GC cause issues?
| [Friday 10 December 2010] [01:03:10] <Steve-o>	they have a music collaboration tool
| [Friday 10 December 2010] [01:03:10] <andrewvc>	at least MRI
| [Friday 10 December 2010] [01:04:03] <samBiotic>	andrewvc: possibly, using this http://opensoundcontrol.org/implementation/ruby-osc-implementation
| [Friday 10 December 2010] [01:04:10] <Steve-o>	built upon Kamaelia http://www.bbc.co.uk/opensource/projects/kamaelia/
| [Friday 10 December 2010] [01:04:45] <samBiotic>	Steve-o: looks interesting
| [Friday 10 December 2010] [01:05:00] <andrewvc>	if you have GC issues btw, jRuby might be the way to go.
| [Friday 10 December 2010] [01:05:16] <andrewvc>	plus, you'll get real multithreading if you need it
| [Friday 10 December 2010] [01:06:36] <andrewvc>	the Kamaelia site seems abandoned
| [Friday 10 December 2010] [01:07:09] <Steve-o>	try here, http://www.kamaelia.org/Home.html
| [Friday 10 December 2010] [01:07:30] <Steve-o>	broken default page
| [Friday 10 December 2010] [01:07:40] <andrewvc>	oh, there we go
| [Friday 10 December 2010] [01:09:44] <Steve-o>	kamaelia jam from a gsoc 2008 project, http://www.bbc.co.uk/blogs/bbcinternet/2008/05/google_summer_of_code.html
| [Friday 10 December 2010] [01:09:55] <samBiotic>	basically, i aim to eliminate network jitter at a slight expense of increased but static delay by forward syncronising timetagged packets
| [Friday 10 December 2010] [01:10:38] <Steve-o>	more like pulseaudio then?
| [Friday 10 December 2010] [01:11:27] <samBiotic>	control data only
| [Friday 10 December 2010] [01:15:15] <Steve-o>	ok, similar to the pro light control system, what ever that is called
| [Friday 10 December 2010] [01:15:42] <Steve-o>	DMX?
| [Friday 10 December 2010] [01:18:14] <samBiotic>	yeah kind of, it's just a network procotol developed by MIT. http://opensoundcontrol.org/introduction-osc
| [Friday 10 December 2010] [01:18:59] <samBiotic>	sorry CNMAT
| [Friday 10 December 2010] [01:19:53] <andrewvc>	samBiotic what's zeromq bring to the table that the OSC protocol doesn't?
| [Friday 10 December 2010] [01:20:03] <andrewvc>	I'm not familiar with OSC at all
| [Friday 10 December 2010] [01:20:31] <Steve-o>	I'm guesing OSC over 0MQ
| [Friday 10 December 2010] [01:20:40] <samBiotic>	thats what i was going to test
| [Friday 10 December 2010] [01:20:50] <Steve-o>	whilst DMX is commercially licensed
| [Friday 10 December 2010] [01:26:07] <andrewvc>	btw, did you ever get it up and running on OSX steve?
| [Friday 10 December 2010] [01:26:11] <andrewvc>	errr Sam
| [Friday 10 December 2010] [01:27:47] <samBiotic>	still at it
| [Friday 10 December 2010] [01:27:50] <andrewvc>	I should mention, if you use zerocopy the ffi binding can beat out the speed of the C binding. Not sure if you need to actually open the msgs as they go through
| [Friday 10 December 2010] [01:28:19] <samBiotic>	trying gem install ffi-rzmq now
| [Friday 10 December 2010] [01:28:42] <andrewvc>	btw, some versions of the ffi gem don't play well with ffi-rzmq
| [Friday 10 December 2010] [01:29:07] <samBiotic>	seems to have work with my zeromq homebrew install
| [Friday 10 December 2010] [01:29:12] <andrewvc>	nice
| [Friday 10 December 2010] [01:29:16] <andrewvc>	I think the most recent one is fine, but if you have weird hanging issues  related to threads, try building it from the ffi github repo
| [Friday 10 December 2010] [01:29:16] <samBiotic>	worked*
| [Friday 10 December 2010] [01:30:22] <andrewvc>	cool
| [Friday 10 December 2010] [02:00:08] <samBiotic>	andrewvc and Steve-o thanks for the help
| [Friday 10 December 2010] [02:00:18] <samBiotic>	bye for now
| [Friday 10 December 2010] [09:25:49] <matias_>	hi all :-)
| [Friday 10 December 2010] [09:39:42] <Steve-o>	mikko: I've backported many fixes to PGM 5.0 but ANSI strict is a bit too much work, therefore 5.1 must be used for Cygwin/Solaris x6/ANSI strict/OSX
| [Friday 10 December 2010] [09:40:11] <mikko>	Steve-o: ok
| [Friday 10 December 2010] [09:40:20] <mikko>	maybe we should remove the strict flags for solaris for now
| [Friday 10 December 2010] [09:40:28] <mikko>	until we can use 5.1 in zeromq
| [Friday 10 December 2010] [09:41:34] <Steve-o>	I need to run through all the tests then I can ship a 5.0.93 and the first 5.1 release
| [Friday 10 December 2010] [09:43:59] <Steve-o>	Sun ONE is odd as ever, it wants __asm__ only in C++ ANSI strict
| [Friday 10 December 2010] [09:44:11] <Steve-o>	every other combination is fine with __asm
| [Friday 10 December 2010] [10:29:37] <mikko>	sustrik_: how does HWM interact with ZMQ_QUEUE?
| [Friday 10 December 2010] [10:32:39] <sustrik_>	mikko: you have to set it by hand
| [Friday 10 December 2010] [10:32:53] <sustrik_>	i.e.
| [Friday 10 December 2010] [10:33:01] <sustrik_>	create socket 1, sreate socket 2
| [Friday 10 December 2010] [10:33:08] <sustrik_>	set hwm on 1. set hwm on 2
| [Friday 10 December 2010] [10:33:17] <sustrik_>	zmq_device (ZMQ_QUEUEU, s1, s2);
| [Friday 10 December 2010] [10:35:31] <mikko>	ok, so in order to get messages swapped out when there is no consumer on the back socket i would just set on s2 ?
| [Friday 10 December 2010] [10:42:00] <mikko>	Assertion failed: rc == 0 (pipe.cpp:187)
| [Friday 10 December 2010] [10:43:07] <mikko>	swap init
| [Friday 10 December 2010] [10:43:42] <mikko>	makes sense now
| [Friday 10 December 2010] [10:43:52] <mikko>	so permission issues on swap file causes an assertion
| [Friday 10 December 2010] [10:43:54] <mikko>	it looks like
| [Friday 10 December 2010] [10:44:18] <mikko>	maybe hte swap location should be a sockopt
| [Friday 10 December 2010] [10:44:32] <mikko>	as for example this daemon chdirs to / and drops privileges 
| [Friday 10 December 2010] [10:44:40] <mikko>	so it makes sense that it cant write
| [Friday 10 December 2010] [10:44:55] <sustrik_>	mikko: yes
| [Friday 10 December 2010] [10:45:10] <sustrik_>	it's a problem
| [Friday 10 December 2010] [10:47:25] <sustrik_>	zmq should not fail
| [Friday 10 December 2010] [10:47:47] <sustrik_>	however, i am not sure what the solution should be
| [Friday 10 December 2010] [10:47:54] <mikko>	in this case it would be easy to return error and set errno to eperm
| [Friday 10 December 2010] [10:48:09] <sustrik_>	it happens on setsockopt?
| [Friday 10 December 2010] [10:48:25] <mikko>	it happens later
| [Friday 10 December 2010] [10:48:47] <sustrik_>	i would say it should happen during setsockopt
| [Friday 10 December 2010] [10:49:02] <sustrik_>	the async error later on is just confusing
| [Friday 10 December 2010] [10:49:02] <mikko>	thats impossible
| [Friday 10 December 2010] [10:49:07] <sustrik_>	why so?
| [Friday 10 December 2010] [10:49:15] <mikko>	you create sequential files
| [Friday 10 December 2010] [10:49:31] <mikko>	someone might have one file present with same name which is not writable
| [Friday 10 December 2010] [10:49:48] <mikko>	maybe the closes you can get is:
| [Friday 10 December 2010] [10:49:56] <mikko>	a) give a sockopt for setting swap dir
| [Friday 10 December 2010] [10:50:04] <mikko>	b) check that swap dir is writable
| [Friday 10 December 2010] [10:50:14] <mikko>	c) leave the rest to user
| [Friday 10 December 2010] [10:50:24] <sustrik_>	what i mean was to crate the file would be created directly when setsockopt(SWAP) is called
| [Friday 10 December 2010] [10:50:28] <sustrik_>	rather than later on
| [Friday 10 December 2010] [10:50:39] <sustrik_>	thus the credentials would be checked immediately
| [Friday 10 December 2010] [10:50:59] <mikko>	yes, that would work as well
| [Friday 10 December 2010] [10:51:19] <sustrik_>	that should be rathereasy
| [Friday 10 December 2010] [10:51:20] <mikko>	and allow setting swap file name by sockopt
| [Friday 10 December 2010] [10:51:35] <sustrik_>	yes, that's an option
| [Friday 10 December 2010] [10:51:43] <mikko>	if not set default to current
| [Friday 10 December 2010] [10:52:05] <mikko>	a lot of daemons won't have write permissions to $PWD
| [Friday 10 December 2010] [10:52:15] <sustrik_>	right
| [Friday 10 December 2010] [10:52:29] <sustrik_>	can you fill an issue in the bugtracker so that we don't forget about it?
| [Friday 10 December 2010] [10:54:09] <mikko>	sustrik_: even better, i can create an issue and try to create patch tonight
| [Friday 10 December 2010] [10:57:23] <mikko>	issue 140
| [Friday 10 December 2010] [10:58:49] <sustrik_>	:)
| [Saturday 11 December 2010] [06:43:41] <mikko>	sustrik: you there?
| [Saturday 11 December 2010] [06:43:52] <sustrik>	hi
| [Saturday 11 December 2010] [06:44:11] <mikko>	i created a small patch for the swap
| [Saturday 11 December 2010] [06:44:33] <mikko>	now it fails when you try to set invalid swap file. the implementation doesn't feel ideal but it works
| [Saturday 11 December 2010] [06:44:47] <sustrik>	mikko: i'll review it
| [Saturday 11 December 2010] [06:44:53] <sustrik>	just send it to the ml
| [Saturday 11 December 2010] [06:46:05] <mikko>	is there a portable PATH_MAX ?
| [Saturday 11 December 2010] [06:57:26] <sustrik>	mikko: let me see
| [Saturday 11 December 2010] [06:58:05] <sustrik>	it's POSIX
| [Saturday 11 December 2010] [06:58:05] <sustrik>	http://www.opengroup.org/onlinepubs/009695399/basedefs/limits.h.html
| [Saturday 11 December 2010] [07:18:51] <mikko>	http://valokuva.org/~mikko/swap.patch it's there for now. does it look sensible?
| [Saturday 11 December 2010] [07:19:09] <mikko>	i'll mail ml later, now i need to vacuum before my better half comes back from hair dresser :)
| [Saturday 11 December 2010] [07:31:11] <mikko>	hmm
| [Saturday 11 December 2010] [07:31:24] <mikko>	maybe it would make more sense to move swap to options
| [Saturday 11 December 2010] [07:31:38] <mikko>	and initialize it when user sets swap size 
| [Saturday 11 December 2010] [07:34:21] <sustrik>	mikko: yes, that's what i had in mind originally
| [Saturday 11 December 2010] [07:34:32] <sustrik>	there's one problem though
| [Saturday 11 December 2010] [07:34:53] <sustrik>	on the bind side there are N connections
| [Saturday 11 December 2010] [07:35:01] <sustrik>	the number is unspecified
| [Saturday 11 December 2010] [07:35:09] <sustrik>	so you cannot create the files in advance
| [Saturday 11 December 2010] [07:35:28] <sustrik>	maybe creating a single dummy file to check the permissions would do?
| [Saturday 11 December 2010] [07:37:35] <mikko>	that should be fine
| [Saturday 11 December 2010] [07:37:53] <mikko>	or maybe even check if the folder is writable
| [Saturday 11 December 2010] [07:38:01] <mikko>	not sure how that works with windows acls etc
| [Saturday 11 December 2010] [07:38:06] <sustrik>	if possible with POSIX API...
| [Saturday 11 December 2010] [07:38:24] <sustrik>	creating a dummy seems easier imo
| [Saturday 11 December 2010] [07:40:43] <mikko>	should the swap append sequence number to filename given?
| [Saturday 11 December 2010] [07:41:02] <mikko>	so if i give /tmp/test.swap the actual filename would be /tmp/test.swap.1
| [Saturday 11 December 2010] [07:41:05] <mikko>	or something
| [Saturday 11 December 2010] [09:46:36] <mikko>	sustrik: i think swap_dir option makes more sense than swap file
| [Sunday 12 December 2010] [05:35:43] <mathijs>	Hi all, is it possible to find out how many messages are currently buffered?
| [Sunday 12 December 2010] [05:36:56] <mathijs>	I like the HWM and the transparent way things get handled in 0mq, but I would like to do some custom stuff when problems arise
| [Sunday 12 December 2010] [05:38:27] <mathijs>	So if a buffer starts to fill up, or reaches HWM, I would like my program to log warnings about it, or talk to some controller process about it.
| [Sunday 12 December 2010] [05:40:59] <mathijs>	ofcourse I can have my processes all log every received/sent message through some other socket to have a central process track overall flow, but it would be nice if there was a more low-level way
| [Sunday 12 December 2010] [05:42:32] <sustrik>	set hwm, send in non-blocking way
| [Sunday 12 December 2010] [05:42:47] <rgl>	mathijs, I don't think its possible right now; but from what I understood, future ZMQ version will have a way to accesses those events.
| [Sunday 12 December 2010] [05:42:48] <sustrik>	when zmq_send returns EAGAIN, the buffer is full
| [Sunday 12 December 2010] [05:43:04] <rgl>	oh we can? *G*
| [Sunday 12 December 2010] [05:43:34] <mathijs>	sustrik: so set a low hwm to have the application handle it?
| [Sunday 12 December 2010] [05:43:47] <sustrik>	if you want so
| [Sunday 12 December 2010] [05:44:08] <sustrik>	think of the queue as a network buffer
| [Sunday 12 December 2010] [05:44:10] <rgl>	we can also store the messages in a file, right?
| [Sunday 12 December 2010] [05:44:31] <sustrik>	you can offload them to the disk,yes
| [Sunday 12 December 2010] [05:46:18] <mathijs>	hmmm ok, that will work for preventing problems.   but what I would like as well is a way to shut down an application safely. I understood 0mq 2.1 will wait for all messages to be handled (empty buffers). So in case one buffer isn't empty yet, and waiting for some other process to come up, I would like to find out what socket/buffer is waiting
| [Sunday 12 December 2010] [05:50:28] <rgl>	indeed, it would be nice to get the current state of a socket (or receive events about state changes). this is something that will be available on the future right sustrik?
| [Sunday 12 December 2010] [07:30:26] <sustrik>	mathijs, rgl: the number of messages in 0MQ queue is an irrelevant statistic, the messages are queue along the whole path from sender to receiver, in 0MQ buffers, TCP buffers, NICs, switch and router queues etc.
| [Sunday 12 December 2010] [07:33:43] <rgl>	sustrik, humm. sure, but they give you some hint if anything might be wrong. for example, how do we known why the messages are pilling up? it might be because a single consumer is delaying the whole seebang.
| [Sunday 12 December 2010] [07:34:38] <rgl>	or for some reason we stopped to be able to connect the socket that once was working fine.
| [Sunday 12 December 2010] [07:34:42] <sustrik>	that's why slow consumers are disconnected in pub/sub pattern
| [Sunday 12 December 2010] [07:35:05] <rgl>	indeed, but currently, how do you known it was disconnected?
| [Sunday 12 December 2010] [07:35:17] <sustrik>	yes, "cannot reconnect" problem should be logged
| [Sunday 12 December 2010] [07:35:34] <sustrik>	because it may be a signal to admins that something went wrong
| [Sunday 12 December 2010] [07:35:39] <sustrik>	and manual intervntion is needed
| [Sunday 12 December 2010] [07:36:12] <rgl>	indeed, thats something that we should be able to log, and to monitor, so we can act uppon it.
| [Sunday 12 December 2010] [07:36:27] <sustrik>	there's a logging mechanism in 0MQ, but at the moment nobody logs anything
| [Sunday 12 December 2010] [07:36:29] <sustrik>	TODO
| [Sunday 12 December 2010] [07:38:12] <rgl>	I might be wrong, but I though there were some messages on the ML about funneling that into some in-queue that could be consumed as a regular socket.
| [Sunday 12 December 2010] [10:02:43] <mikko>	sustrik: Assertion failed: stored (pipe.cpp:238)
| [Sunday 12 December 2010] [10:02:54] <mikko>	what should be the behavior when swap fills up?
| [Sunday 12 December 2010] [10:03:14] <mikko>	happens in zmq::writer_t::write pipe.cpp
| [Sunday 12 December 2010] [10:06:17] <mikko>	actually it should probably return false in bool zmq::writer_t::write (zmq_msg_t *msg_)
| [Sunday 12 December 2010] [10:34:05] <benoitc>	hi all
| [Sunday 12 December 2010] [10:34:47] <benoitc>	can we fork processes and share a zeromq "socket" between children ?
| [Sunday 12 December 2010] [10:34:54] <benoitc>	with pyzmq
| [Sunday 12 December 2010] [10:49:01] <cremes>	benoitc: i doubt that is supported; it's not a good idea at all
| [Sunday 12 December 2010] [10:49:35] <cremes>	if the children need to communicate with each other, open up sockets that are specific to that job
| [Sunday 12 December 2010] [11:04:55] <benoitc>	so i need to open a zmq socket per worker on the parent process ?
| [Sunday 12 December 2010] [11:06:12] <cremes>	benoitc: that's what i would recommend
| [Sunday 12 December 2010] [11:06:25] <cremes>	these sockets are "cheap" so i wouldn't worry about computational cost
| [Sunday 12 December 2010] [11:07:18] <benoitc>	hm ok
| [Sunday 12 December 2010] [11:07:20] <benoitc>	thanks
| [Sunday 12 December 2010] [11:07:52] <cremes>	saying "hmmm" implies you either don't agree or you don't understand why
| [Sunday 12 December 2010] [11:07:58] <cremes>	do you still have a question?
| [Sunday 12 December 2010] [11:08:22] <benoitc>	well it means i've to rethink my design :)
| [Sunday 12 December 2010] [11:08:58] <benoitc>	i was thinking at first to just open a zmq like any socket and make it not blocking
| [Sunday 12 December 2010] [11:09:04] <cremes>	not necessarily; if your design called for multiple children to all listen to the same socket then perhaps a device in the middle will solve your issue
| [Sunday 12 December 2010] [11:09:50] <cremes>	all children can connect to the device on the same port and the device will (depending on socket type) deliver messages to the children
| [Sunday 12 December 2010] [11:09:51] <benoitc>	well idea was to balance between workers as soon as a message is send to the socket
| [Sunday 12 December 2010] [11:10:00] <cremes>	definitely read the guide if you haven't done so yet
| [Sunday 12 December 2010] [11:10:12] <cremes>	so you are using req/rep sockets?
| [Sunday 12 December 2010] [11:13:32] <cremes>	i need to run out for about 90m; feel free to post a description of what you are trying to do
| [Sunday 12 December 2010] [11:13:39] <cremes>	i'll try to give some guidance when i return
| [Sunday 12 December 2010] [11:14:14] <benoitc>	mm yes I should reply i took the message I guess
| [Sunday 12 December 2010] [11:14:43] <benoitc>	in my first approach wanted to have this balancing you can do with "normal" sockets
| [Sunday 12 December 2010] [11:14:51] <benoitc>	anyway later
| [Sunday 12 December 2010] [11:15:41] 	 * benoitc want the sockett.accept like
| [Sunday 12 December 2010] [11:53:37] <mikko>	benoitc: 0MQ has load-balancing built-in
| [Sunday 12 December 2010] [11:56:29] <benoitc>	mikko: so once the message is get by one listsner in req/rep it won't be send to other listeners ?
| [Sunday 12 December 2010] [11:56:36] <benoitc>	(just want to make sure)
| [Sunday 12 December 2010] [11:58:24] <mikko>	benoitc: different socket types have different kind of distribution algorithms
| [Sunday 12 December 2010] [11:58:37] <mikko>	for example in PUB/SUB the published message is sent to all subscribers
| [Sunday 12 December 2010] [11:59:07] <mikko>	but for example PUSH/PULL balances between live connections
| [Sunday 12 December 2010] [11:59:14] <mikko>	you should really read zguide
| [Sunday 12 December 2010] [13:00:52] <cremes>	benoitc: mikko is right; most of this is covered in the guide:  http://zguide.zeromq.org/chapter:all
| [Sunday 12 December 2010] [13:01:02] <cremes>	for some reason, that link is returning a 503 right now
| [Sunday 12 December 2010] [13:01:20] <cremes>	sustrik, pieterh: the guide is offline
| [Sunday 12 December 2010] [13:01:30] <cremes>	it's returning a 503 error
| [Sunday 12 December 2010] [13:26:35] <mikko>	cremes: works from here
| [Sunday 12 December 2010] [13:27:07] <cremes>	mikko: it's responding now for me too but it wasn't before
| [Sunday 12 December 2010] [14:18:38] <benoitc>	yeah reading it 
| [Sunday 12 December 2010] [14:18:41] <benoitc>	thanks
| [Sunday 12 December 2010] [15:14:53] <sustrik>	mikko: what version is that?
| [Sunday 12 December 2010] [15:15:19] <sustrik>	what it should do is behave the same way is if HWM is reached
| [Sunday 12 December 2010] [15:15:30] <sustrik>	block, drop, whatever
| [Sunday 12 December 2010] [15:15:37] <sustrik>	depending on the pattern
| [Sunday 12 December 2010] [15:18:32] <mikko>	sustrik: trunk, the lines won't match as i have some local changes
| [Sunday 12 December 2010] [15:19:15] <mikko>	sustrik: yes, probably
| [Sunday 12 December 2010] [15:19:16] <sustrik>	i see, so which assertion was actually hit?
| [Sunday 12 December 2010] [15:19:28] <mikko>	sustrik: writer_t::write
| [Sunday 12 December 2010] [15:19:35] <mikko>	when swap is full 
| [Sunday 12 December 2010] [15:19:40] <mikko>	let me check the upstread lineno
| [Sunday 12 December 2010] [15:19:43] <sustrik>	zmq_assert (stored); ?
| [Sunday 12 December 2010] [15:20:20] <mikko>	https://github.com/zeromq/zeromq2/blob/master/src/pipe.cpp#L237
| [Sunday 12 December 2010] [15:20:22] <mikko>	yes
| [Sunday 12 December 2010] [15:20:53] <sustrik>	looks like a bug
| [Sunday 12 December 2010] [15:20:57] <mathijs>	I read some discussion about socket migrations and memory barriers. I never heard of those before, so I probably shouldn't touch stuff...  but I think I have a possible usecase. GHC (haskell) uses a IO manager which manages a pool of OS threads. On top of those, it runs "green threads". A green thread can signal it's waiting for some FD. execution stops. When the fd is ready (epoll), execution resumes. But it's possible that it's mapped to a
| [Sunday 12 December 2010] [15:20:57] <mathijs>	 different OS thread
| [Sunday 12 December 2010] [15:21:10] <sustrik>	afaiu the saving of messages to the swap is not atomic
| [Sunday 12 December 2010] [15:21:37] <sustrik>	i.e. you can store one message part and next one is rejected
| [Sunday 12 December 2010] [15:21:44] <sustrik>	should be fixed
| [Sunday 12 December 2010] [15:22:40] <mathijs>	is the case I describe a valid one for using socket migrations? 
| [Sunday 12 December 2010] [15:24:47] <sustrik>	yes, that was the main use case for the "migration" feature
| [Sunday 12 December 2010] [15:25:14] <sustrik>	you can assume that the memory barriers are handled correctly by haskell runtime
| [Sunday 12 December 2010] [15:25:23] <mathijs>	I can signal the IO manager that a certain green thread gets mapped to the same OS thread every time it runs/continues, but having them scheduled on the least-busy OS thread sounds better.
| [Sunday 12 December 2010] [15:25:48] <sustrik>	yes, it should work
| [Sunday 12 December 2010] [15:25:58] <mathijs>	sustrik: thanks
| [Sunday 12 December 2010] [16:08:57] <mikko>	sustrik: so, i'm thinking about the whole swap thing
| [Sunday 12 December 2010] [16:09:20] <mikko>	what do you think about abstracting the swap slightly further?
| [Sunday 12 December 2010] [16:09:46] <mikko>	maybe something like: make the swap implementation pluggable and use inproc pipe to communicate with the swap engine
| [Sunday 12 December 2010] [16:24:25] <sustrik>	mikko: that way you would introduce a bottleneck
| [Sunday 12 December 2010] [16:25:05] <mikko>	but swap is going to be a bottleneck in any case
| [Sunday 12 December 2010] [16:25:05] <sustrik>	you can always make a device that would store messages on the disk if you want to
| [Sunday 12 December 2010] [16:25:43] <mikko>	the whole concept of swapping is more preserving operation rather than performance
| [Sunday 12 December 2010] [16:26:17] <sustrik>	the point is that you want the swap as fast as possible exactly because it is slow
| [Sunday 12 December 2010] [16:26:25] <sustrik>	so, for example
| [Sunday 12 December 2010] [16:26:38] <sustrik>	if your apps falls over into swap mode
| [Sunday 12 December 2010] [16:27:00] <sustrik>	you want it to get out of it as fast as possible once the network is up and running again
| [Sunday 12 December 2010] [16:29:04] <sustrik>	if you make it slow it may even happen that it will never get out of the swap mode
| [Sunday 12 December 2010] [16:29:14] <sustrik>	it's kind of tricky
| [Sunday 12 December 2010] [16:29:26] <mikko>	how much overhead does forwarding a message over inproc pipe add?
| [Sunday 12 December 2010] [16:29:48] <sustrik>	dunno
| [Sunday 12 December 2010] [16:29:52] <sustrik>	should be measured
| [Sunday 12 December 2010] [16:30:56] <sustrik>	maybe it would make no difference at all
| [Sunday 12 December 2010] [16:31:59] <mikko>	if there is little or no overhead it would allow people to implement optimised swap solutions
| [Sunday 12 December 2010] [16:32:07] <sustrik>	sure
| [Sunday 12 December 2010] [16:32:34] <mikko>	i noticed that there is the posix_fadvise for linux 
| [Sunday 12 December 2010] [16:32:39] <sustrik>	yes
| [Sunday 12 December 2010] [16:32:46] <mikko>	but there are probably available optimizations for other platforms as well
| [Sunday 12 December 2010] [16:33:16] <mikko>	my point with this was: swap is really something that doesn't necessarily need to be in 0MQ core
| [Sunday 12 December 2010] [16:33:24] <sustrik>	ack
| [Sunday 12 December 2010] [16:33:33] <mikko>	if the implementation was pluggable it would allow people to make their own and share them
| [Sunday 12 December 2010] [16:33:41] <mikko>	not sure, it's tricky
| [Sunday 12 December 2010] [16:33:48] <sustrik>	it was added as a feature paid for by a customer
| [Sunday 12 December 2010] [16:34:26] <sustrik>	so it's kind of a hack atm
| [Sunday 12 December 2010] [16:35:20] <mikko>	void zmq::swap_t::rollback ()
| [Sunday 12 December 2010] [16:35:24] <mikko>	is that used ?
| [Sunday 12 December 2010] [16:35:25] <sustrik>	let me think about it...
| [Sunday 12 December 2010] [16:35:37] <mikko>	as it seems that it ends up into assertion in any possible path
| [Sunday 12 December 2010] [16:35:38] <sustrik>	mikko: it should be afaics
| [Sunday 12 December 2010] [16:35:59] <mikko>	well, possibly ends up
| [Sunday 12 December 2010] [16:36:04] <sustrik>	hm, quite possibly i've broken the implementation when i did all the changes for 2.1
| [Sunday 12 December 2010] [16:37:15] <sustrik>	well, it would be nice is swapping was implemented as a device
| [Sunday 12 December 2010] [16:37:30] <sustrik>	so you would just plug it in-between two nodes to get swap
| [Sunday 12 December 2010] [16:38:02] <sustrik>	one problem is that by doing so you have to do two hops instead of a single one
| [Sunday 12 December 2010] [16:38:17] <sustrik>	even though swap is not being used at the moment
| [Sunday 12 December 2010] [16:38:23] <mikko>	that is true
| [Sunday 12 December 2010] [16:38:43] <mikko>	but would you use swap if you were aiming for absolute performance?
| [Sunday 12 December 2010] [16:38:59] <sustrik>	actually, i like the idea
| [Sunday 12 December 2010] [16:39:28] <sustrik>	we could just say 'sorry, there's performance impact with swap'
| [Sunday 12 December 2010] [16:39:49] <mikko>	so, if you were to generalise this a bit further
| [Sunday 12 December 2010] [16:40:29] <mikko>	zmq_callback_device which takes function pointers for message received from front and sent out to back
| [Sunday 12 December 2010] [16:40:43] <mikko>	then swap would implement functions for storing and removing
| [Sunday 12 December 2010] [16:40:55] <mikko>	you could use the same pattern for implementing 'persistent' things
| [Sunday 12 December 2010] [16:41:04] <mikko>	not sure about exact details yet
| [Sunday 12 December 2010] [16:41:12] <sustrik>	right, it's just a device
| [Sunday 12 December 2010] [16:41:32] <sustrik>	i would like to move devices out of core 0mq with 3.0
| [Sunday 12 December 2010] [16:41:49] <sustrik>	swap could be removed as well at that point
| [Sunday 12 December 2010] [16:41:55] <mikko>	i think for devices to be more useful is a way to stop them without SIGINT
| [Sunday 12 December 2010] [16:42:01] <sustrik>	and instead we can provide a standalone swapping device
| [Sunday 12 December 2010] [16:42:24] <sustrik>	yes, you want a remote managementy
| [Sunday 12 December 2010] [16:42:46] <mikko>	void *device = zmq_device(...); while (1) { if (shutdown) { device_shutdown(device); } sleep(5); }
| [Sunday 12 December 2010] [16:42:49] <mikko>	something like that
| [Sunday 12 December 2010] [16:43:26] <sustrik>	shutdown sent as a message to the device, right?
| [Sunday 12 December 2010] [16:43:31] <mikko>	yes, currently in my small program i run device in a thread and just use pthread_cancel to stop the device thread
| [Sunday 12 December 2010] [16:43:33] <sustrik>	from the management console
| [Sunday 12 December 2010] [16:43:44] <mikko>	that is a possibility yes
| [Sunday 12 December 2010] [16:43:57] <mikko>	but does it open the device for DoS ?
| [Sunday 12 December 2010] [16:44:07] <mikko>	or do you mean some sort of internal message?
| [Sunday 12 December 2010] [16:44:16] <sustrik>	you need authentication etc.
| [Sunday 12 December 2010] [16:44:30] <sustrik>	the whole device thing is where development will happen in the future imo
| [Sunday 12 December 2010] [16:45:11] <sustrik>	actually, what i foresee is that devices will be removed from core 0mq
| [Sunday 12 December 2010] [16:45:35] <sustrik>	there will be various open source devices
| [Sunday 12 December 2010] [16:45:51] <sustrik>	but there can also be complex proprietary devices
| [Sunday 12 December 2010] [16:46:05] <mikko>	we should have a hackathon on removing all these assertions at some point
| [Sunday 12 December 2010] [16:46:14] <sustrik>	think of how cisco builds boxes for TCP/IP stack
| [Sunday 12 December 2010] [16:46:47] <sustrik>	yes, but it has to happen with new major version
| [Sunday 12 December 2010] [16:46:50] <sustrik>	i.e. 3.0
| [Sunday 12 December 2010] [16:47:01] <sustrik>	as it's not backward compatible
| [Sunday 12 December 2010] [16:49:41] <mikko>	thats true
| [Sunday 12 December 2010] [18:36:00] Notice	-tomaw- [Global Notice] We're restarting services to fix some database issues; please remain patient as it will return soon.
| [Monday 13 December 2010] [07:09:29] <mikko>	sustrik: hi
| [Monday 13 December 2010] [07:13:54] <sustrik>	hi
| [Monday 13 December 2010] [07:16:19] <mikko>	again, thinking out loud here: extending uris to allow shortcut for setting socket options
| [Monday 13 December 2010] [07:16:46] <mikko>	tcp://127.0.0.1:5555?linger=1000&identity=mytestsocket
| [Monday 13 December 2010] [07:17:11] <mikko>	although this could be done in the user application as well
| [Monday 13 December 2010] [07:17:16] <sustrik>	can be useful but should be implemented as a layer on top of 0mq
| [Monday 13 December 2010] [07:17:24] <sustrik>	exactly
| [Monday 13 December 2010] [07:17:48] <sustrik>	the problem is that this kind of thing means wandering far away from POSIX
| [Monday 13 December 2010] [07:17:53] <ianbarber>	maybe a standard function in zfl for creating sockets from a url like that?
| [Monday 13 December 2010] [07:18:01] <sustrik>	for example
| [Monday 13 December 2010] [07:18:15] <sustrik>	it's useful, so it's worth of implementing it
| [Monday 13 December 2010] [07:24:05] <sustrik>	mikko: btw, i've added your idea about swap->device to 3.0 roadmap
| [Monday 13 December 2010] [07:24:09] <sustrik>	http://www.zeromq.org/docs:3-0
| [Monday 13 December 2010] [07:25:56] <mikko>	sustrik: cool
| [Monday 13 December 2010] [07:26:14] <mikko>	i was thinking about the control channel
| [Monday 13 December 2010] [07:26:29] <mikko>	it's not necessary to do it over a remote management
| [Monday 13 December 2010] [07:26:49] <mikko>	as if there was a device handle (void *) like with sockets then people could build their own if that is a requirement
| [Monday 13 December 2010] [07:26:55] <mikko>	lunch ->
| [Monday 13 December 2010] [07:29:31] <sustrik>	i don't follow
| [Monday 13 December 2010] [07:29:46] <sustrik>	people can build their own device even now, no?
| [Monday 13 December 2010] [07:30:29] <mrm2m>	Hey ho!
| [Monday 13 December 2010] [07:31:57] <ianbarber>	sustrik: i think the idea was to allow control flow outside the device, so the device runs in another thread, and the control is done through the parent process. 
| [Monday 13 December 2010] [07:32:25] <sustrik>	hi
| [Monday 13 December 2010] [07:32:32] <sustrik>	ianbarber: sure
| [Monday 13 December 2010] [07:32:46] <sustrik>	what i meant was that you can do such thing even today
| [Monday 13 December 2010] [07:32:54] <mrm2m>	Is there a one directional socket type? I've got some data I'd like to send to a server, but I'm not interested in any message if the data was received correctly or even if it was received. 
| [Monday 13 December 2010] [07:33:03] <ianbarber>	push
| [Monday 13 December 2010] [07:33:11] <sustrik>	mrm2m: PUB/SUB presumably
| [Monday 13 December 2010] [07:33:22] <sustrik>	it's completely uni-directional
| [Monday 13 December 2010] [07:33:43] <ianbarber>	sustrik: yeah, you can, but only if you create the device yourself - though I guess you could wrap a device available from elsewhere with one your own
| [Monday 13 December 2010] [07:34:13] <mrm2m>	Ah - I thought that was for one PUB sending to several SUBs. 
| [Monday 13 December 2010] [07:34:21] <sustrik>	yes
| [Monday 13 December 2010] [07:34:30] <sustrik>	and what do you need instead?
| [Monday 13 December 2010] [07:34:37] <mrm2m>	I need to send from several PUBs to one SUB.
| [Monday 13 December 2010] [07:34:49] <sustrik>	that would work as well
| [Monday 13 December 2010] [07:34:55] <sustrik>	ianbarber: ah, the plan is to move devices out of 0mq core anyway
| [Monday 13 December 2010] [07:35:05] <sustrik>	and make them separate projects
| [Monday 13 December 2010] [07:35:08] <ianbarber>	ah, ok. that makes sense
| [Monday 13 December 2010] [07:35:16] <sustrik>	so you could have different types of devices
| [Monday 13 December 2010] [07:35:37] <sustrik>	the one with control socket propsed above could be one available device
| [Monday 13 December 2010] [07:35:38] <sustrik>	etc.
| [Monday 13 December 2010] [07:35:40] <mrm2m>	sustrik: Ok. Then I'll have a look on SUB/PUB. 
| [Monday 13 December 2010] [08:19:34] <CIA-20>	zeromq2: 03Dhammika Pathirana 07master * r22b2b9a 10/ (src/tcp_listener.cpp src/tcp_listener.hpp): 
| [Monday 13 December 2010] [08:19:34] <CIA-20>	zeromq2: fix overwriting errno on bind failure
| [Monday 13 December 2010] [08:19:34] <CIA-20>	zeromq2: Signed-off-by: Dhammika Pathirana <dhammika@gmail.com> - http://bit.ly/eB0FKT
| [Monday 13 December 2010] [09:17:54] <ianbarber>	yay, that's all the zguide examples translated into php :) committed the version one I needed mikko's patch for
| [Monday 13 December 2010] [09:26:08] <mikko>	sustrik: pipe.cpp:56
| [Monday 13 December 2010] [09:26:28] <mikko>	i reckon that should exit the device rather than assert
| [Monday 13 December 2010] [09:26:45] <sustrik>	let me see
| [Monday 13 December 2010] [09:27:07] <sustrik>	i have a comment on that line :(
| [Monday 13 December 2010] [09:27:13] <sustrik>	can you paste the line here?
| [Monday 13 December 2010] [09:27:28] <mikko>	errno_assert (false);
| [Monday 13 December 2010] [09:27:37] <mikko>	after rc = zmq_poll (&items [0], 2, -1);
| [Monday 13 December 2010] [09:27:48] <mikko>	i got a signal handler in my process that catches SIGINT
| [Monday 13 December 2010] [09:28:00] <mikko>	it seems to however cause zmq_poll to return
| [Monday 13 December 2010] [09:28:05] <mikko>	and causes following assertion:
| [Monday 13 December 2010] [09:28:11] <mikko>	^CInterrupted system call
| [Monday 13 December 2010] [09:28:11] <mikko>	false (device.cpp:56)
| [Monday 13 December 2010] [09:28:12] <mikko>	Aborted
| [Monday 13 December 2010] [09:28:42] <mikko>	if i don't catch sigint then the program exits immediately
| [Monday 13 December 2010] [09:29:01] <sustrik>	device or pipe.coo?
| [Monday 13 December 2010] [09:29:03] <sustrik>	cpp
| [Monday 13 December 2010] [09:29:21] <mikko>	sorry, device.cpp
| [Monday 13 December 2010] [09:29:21] <sustrik>	ah, have it
| [Monday 13 December 2010] [09:29:52] <sustrik>	yes, it works that way
| [Monday 13 December 2010] [09:30:03] <sustrik>	what should be presumably done
| [Monday 13 December 2010] [09:30:16] <sustrik>	is to return EINTR from the zmq_device call
| [Monday 13 December 2010] [09:31:33] <mikko>	yeah, would allow clean termination of parent program
| [Monday 13 December 2010] [09:31:56] <mikko>	as running device in a thread and then doing pthread_cancel doesn't seem particulary clean either
| [Monday 13 December 2010] [09:32:09] <mikko>	im surprised that it doesn't assert on pthread_cancel
| [Monday 13 December 2010] [09:34:18] <sustrik>	i assume that just kills the thread at the spot
| [Monday 13 December 2010] [09:34:26] <sustrik>	so it has no chance to assert
| [Monday 13 December 2010] [09:37:53] <mikko>	looking at the code, i think it shouldn't assert at all
| [Monday 13 December 2010] [09:38:00] <mikko>	as the caller can handle device exiting
| [Monday 13 December 2010] [09:41:08] <CIA-20>	zeromq2: 03Dhammika Pathirana 07master * rf749f2d 10/ (src/socket_base.cpp src/socket_base.hpp): 
| [Monday 13 December 2010] [09:41:08] <CIA-20>	zeromq2: add basic uri validations
| [Monday 13 December 2010] [09:41:08] <CIA-20>	zeromq2: Signed-off-by: Dhammika Pathirana <dhammika@gmail.com> - http://bit.ly/hptlRa
| [Monday 13 December 2010] [09:41:37] <sustrik>	mikko: good point
| [Monday 13 December 2010] [09:43:14] <mikko>	you could even send the original errno back
| [Monday 13 December 2010] [09:46:07] <sustrik>	yes
| [Monday 13 December 2010] [09:59:04] <mikko>	sustrik: https://gist.github.com/cc8ca1efb295254bc634
| [Monday 13 December 2010] [10:03:13] <sustrik>	mikko: looks good
| [Monday 13 December 2010] [10:03:19] <sustrik>	can you send it as patch to the ml?
| [Monday 13 December 2010] [10:20:42] <sustrik>	mikko: checking your swapdir patch
| [Monday 13 December 2010] [10:20:51] <sustrik>	what's the point of having 3 test functions?
| [Monday 13 December 2010] [10:20:55] <sustrik>	+        static bool test (const std::string& directory_);
| [Monday 13 December 2010] [10:20:55] <sustrik>	+
| [Monday 13 December 2010] [10:20:55] <sustrik>	+        static bool test (const char* directory_);
| [Monday 13 December 2010] [10:20:55] <sustrik>	+
| [Monday 13 December 2010] [10:20:55] <sustrik>	+        static bool test ();
| [Monday 13 December 2010] [10:29:00] <mikko>	sustrik: overloaded for different types i guess
| [Monday 13 December 2010] [10:29:16] <sustrik>	i mean, do you use all 3 of them?
| [Monday 13 December 2010] [10:29:21] <mikko>	sustrik: yes
| [Monday 13 December 2010] [10:29:32] <mikko>	what i think about now
| [Monday 13 December 2010] [10:29:38] <mikko>	does it make sense to amend the swap now
| [Monday 13 December 2010] [10:29:45] <mikko>	if it goes to heavy refactoring soon
| [Monday 13 December 2010] [10:29:57] <sustrik>	well, depends on you
| [Monday 13 December 2010] [10:30:10] <sustrik>	if you need it asap, i'll apply it
| [Monday 13 December 2010] [10:30:59] <mikko>	i don't need asap
| [Monday 13 December 2010] [10:31:09] <mikko>	i can work around it and document for php extension
| [Monday 13 December 2010] [10:31:43] <mikko>	at the moment doing const char *tmp = getenv("TMPDIR"); if (!tmp) { tmp = "/tmp"; } chdir(tmp);
| [Monday 13 December 2010] [10:31:45] <sustrik>	ok then
| [Monday 13 December 2010] [10:32:27] <sustrik>	maybe just write a comment about it on the ml
| [Monday 13 December 2010] [10:32:36] <sustrik>	so that people know what happened to the patch
| [Monday 13 December 2010] [10:34:09] <mikko>	i'll write comment and send device patch today
| [Monday 13 December 2010] [10:34:39] <sustrik>	ok
| [Monday 13 December 2010] [12:37:13] <mikko>	sustrik: call to device is not consistent between C and C++
| [Monday 13 December 2010] [12:37:18] <mikko>	seems to be void in C++
| [Monday 13 December 2010] [12:37:21] <mikko>	and int in C
| [Monday 13 December 2010] [12:37:26] <mikko>	return type that is
| [Monday 13 December 2010] [12:39:16] <mikko>	error_t is int?
| [Monday 13 December 2010] [12:42:14] <mikko>	no, wait. got it
| [Monday 13 December 2010] [13:15:31] <myraft>	complete noob - quick question - where do I start? I am not sure if I even installed it correctly. Is there a zmq on linux that should be in the path?
| [Monday 13 December 2010] [13:17:15] <myraft>	Nevermind - found some Java examples on Github - will scan and ask the questions again. 
| [Monday 13 December 2010] [13:17:19] <myraft>	Thanks though.
| [Monday 13 December 2010] [13:18:21] <cremes>	myraft: make sure you run ldconfig so that the zmq libs get added to your linux library paths
| [Monday 13 December 2010] [13:19:00] <drbobbeaty>	myraft: it's probably best to read The Guide (it's that important): http://zguide.zeromq.org/chapter:all
| [Monday 13 December 2010] [13:19:25] <drbobbeaty>	It contains a lot of good information as well as a lot of examples in all kinds of languages.
| [Monday 13 December 2010] [13:21:11] 	 * davetoo is n00b but needs to figure out how one might do pub/sub with 0mq 
| [Monday 13 December 2010] [13:21:21] <davetoo>	with topic exchange-like behavior :)
| [Monday 13 December 2010] [13:23:21] <cremes>	davetoo: that's described in the guide too ;)
| [Monday 13 December 2010] [13:27:44] <myraft>	thanks folks - just found the guide as well 
| [Monday 13 December 2010] [14:13:32] <mikko>	sustrik: https://gist.github.com/848e949008e67ca542f7
| [Monday 13 December 2010] [14:14:31] <sustrik>	hm, that may be the problem that dhammika fixed
| [Monday 13 December 2010] [14:14:39] <sustrik>	i'll apply his patch tomorrow
| [Monday 13 December 2010] [14:15:15] <mikko>	cool
| [Monday 13 December 2010] [14:15:24] <mikko>	ianbarber stumbled on this with the php extension
| [Monday 13 December 2010] [14:15:26] <sustrik>	it's a heisenbug, right?
| [Monday 13 December 2010] [14:15:39] <mikko>	nope, can reproduce reliably
| [Monday 13 December 2010] [14:15:53] <sustrik>	ah, then it may be something different
| [Monday 13 December 2010] [14:16:05] <mikko>	if you take the .c file attached to the paste
| [Monday 13 December 2010] [14:16:09] <mikko>	compile and and 
| [Monday 13 December 2010] [14:16:14] <mikko>	compile and run
| [Monday 13 December 2010] [14:16:20] <sustrik>	right
| [Monday 13 December 2010] [14:16:22] <mikko>	it should segfault / show memory errors
| [Monday 13 December 2010] [15:32:22] <mikko>	i to the b
| [Monday 13 December 2010] [15:33:26] <ianbarber>	m to the k
| [Monday 13 December 2010] [15:40:58] <myraft>	when trying to run java program I get "UnsatisfiedLinkError: no jzmq in java.library.path" - I have done ldconfig -p |grep zmq and see they so are a loaded. I have tried recompiling the code. Any ideas ?
| [Monday 13 December 2010] [15:51:15] <mikko>	myraft: it seems to be complaining about jzmq
| [Monday 13 December 2010] [15:51:19] <mikko>	rather than zmq itself
| [Monday 13 December 2010] [15:52:09] <myraft>	ok
| [Monday 13 December 2010] [15:52:31] <myraft>	but not sure how to proceed - followed the instructions - 
| [Monday 13 December 2010] [15:53:20] <myraft>	nathanmarz - if I do ldconfig -p|grep for zmq I see libzmq.so along with ligjzmq.so  - 
| [Monday 13 December 2010] [15:53:42] <myraft>	I meant to direct that at mikko - 
| [Monday 13 December 2010] [15:54:05] <mikko>	myraft: is the directory where libjzmq.so is in java.library.path ?
| [Monday 13 December 2010] [15:55:07] <myraft>	mikko : libjzmq.so is in /usr/local/lib - "sheepishly" - not sure if it is java.library.path, how do I set it ?
| [Monday 13 December 2010] [15:56:36] <mikko>	myraft: i've no idea tbh, i don't use java myself
| [Monday 13 December 2010] [15:56:43] <mikko>	myraft: what version of zeromq are you using?
| [Monday 13 December 2010] [15:58:05] <myraft>	mikko: 2.0.10
| [Monday 13 December 2010] [15:58:28] <mikko>	myraft: can you test with current github trunk?
| [Monday 13 December 2010] [15:58:29] <mikko>	just in case
| [Monday 13 December 2010] [15:58:38] <mikko>	git clone https://github.com/zeromq/zeromq2.git
| [Monday 13 December 2010] [15:58:51] <mikko>	cd zeromq2 && ./autogen.sh && ./configure && make install
| [Monday 13 December 2010] [16:00:38] <myraft>	mikko: will do and postback  - thanks 
| [Monday 13 December 2010] [16:04:03] <myraft>	mikko - did that and see libzmq.so.1 created in /usr/local/bin - running the Java program still gives the same error. 
| [Monday 13 December 2010] [16:04:43] <myraft>	I did go thru installation instructions - and was confused about setting java.library.path - I did CLASSPATH instead in the .bashrc 
| [Monday 13 December 2010] [16:08:36] <myraft>	I wonder if I need to restart the system - since there is libconf daemon - and that will not see the changes. 
| [Monday 13 December 2010] [16:08:59] <myraft>	Anyways - thanks for the attempt - let me know if you have any more ideas.
| [Monday 13 December 2010] [16:14:08] <myraft>	I will leaving the workstation for a little bit and will be online later.
| [Monday 13 December 2010] [16:19:13] <mikko>	i dont think that makes a different
| [Monday 13 December 2010] [16:19:18] <mikko>	difference*
| [Monday 13 December 2010] [16:19:24] <mikko>	i can give it a go later
| [Monday 13 December 2010] [16:35:08] <mikko>	sustrik: still there?
| [Tuesday 14 December 2010] [00:07:52] <gandhijee>	hey, installed zmq on my system, and for my cross compiler, now my c++ programs won't compile unless i link in zmq, any ideas?
| [Tuesday 14 December 2010] [00:21:48] <EricL>	I am debating using 0mq as a possible 'logserver'. Basically just listen for messages and write them to a file (but these messages are JSON and will be coming at a very high rate of speed).  Is there a good use-case?
| [Tuesday 14 December 2010] [04:08:37] <mikko>	good morning
| [Tuesday 14 December 2010] [04:09:04] <Steve-o>	good afternoon
| [Tuesday 14 December 2010] [04:09:35] <Steve-o>	:P
| [Tuesday 14 December 2010] [04:12:30] <Steve-o>	quiet morning, nothing but net splits
| [Tuesday 14 December 2010] [04:13:44] <mikko>	indeed
| [Tuesday 14 December 2010] [04:13:49] <mikko>	europe is just waking up
| [Tuesday 14 December 2010] [04:14:41] <Steve-o>	I released OpenPGM 5.0.93 and 5.1.99, hopefully the latter is more friendly towards Solaris/x86
| [Tuesday 14 December 2010] [04:15:50] <Steve-o>	builds in ICC and Sun ONE strict mode, along with OSX and Cygwin too
| [Tuesday 14 December 2010] [04:16:48] <Steve-o>	I keep on messing up byte order macros on Solaris, the builds definitely work on Sparc
| [Tuesday 14 December 2010] [04:18:54] <mikko>	nice!
| [Tuesday 14 December 2010] [04:19:17] <Steve-o>	OSX is tedious as the libc is really old
| [Tuesday 14 December 2010] [04:19:39] <mikko>	i'll fix zeromq --with-pgm to build properly on solaris x86 at some point
| [Tuesday 14 December 2010] [04:19:47] <mikko>	haven't got access to sparc yet
| [Tuesday 14 December 2010] [04:20:06] <Steve-o>	remember there are 3 compilers on sparc to test
| [Tuesday 14 December 2010] [04:20:17] <Steve-o>	Sun ONE, Sun GCC, and GCC
| [Tuesday 14 December 2010] [04:20:28] <Steve-o>	all each with their own quirks
| [Tuesday 14 December 2010] [04:20:40] <mikko>	i can test all those on x86
| [Tuesday 14 December 2010] [04:21:13] <mikko>	hmm, currently the win7 builds using visual studio 2008
| [Tuesday 14 December 2010] [04:21:22] <mikko>	might upgrade to 2010 at some point
| [Tuesday 14 December 2010] [04:22:11] <Steve-o>	PGM should work in 2008, it is just that I found some really annoying bugs in the CRT socket libraries
| [Tuesday 14 December 2010] [04:22:35] <mikko>	that's not surprising
| [Tuesday 14 December 2010] [04:23:14] <Steve-o>	haven't tried mingw32 on Windows, only cross compiles
| [Tuesday 14 December 2010] [04:23:27] <Steve-o>	Scons on Cygwin is pretty terrible, although I think it's Python at fault
| [Tuesday 14 December 2010] [04:23:40] <mikko>	i could add mingw32 on windows to daily builds 
| [Tuesday 14 December 2010] [04:23:55] <mikko>	and possibly a BSD box
| [Tuesday 14 December 2010] [04:24:14] <Steve-o>	FreeBSD is nice to catch portability bugs
| [Tuesday 14 December 2010] [04:24:27] <Steve-o>	but the IP header quirk is annoying
| [Tuesday 14 December 2010] [04:24:48] <mikko>	should i go for OpenBSD might be even a bit more exotic
| [Tuesday 14 December 2010] [04:25:15] <mikko>	FreeBSD is a bit more user-friendly though
| [Tuesday 14 December 2010] [04:25:19] <Steve-o>	good luck, I've only used OpenBSD on Sparc
| [Tuesday 14 December 2010] [04:25:43] <mikko>	OpenBSD doesn't use GCC iirc
| [Tuesday 14 December 2010] [04:25:46] <Steve-o>	can be annoying to install, especially since getting the install is inconvenient
| [Tuesday 14 December 2010] [04:25:54] <Steve-o>	GCC 2.95 I believe
| [Tuesday 14 December 2010] [04:25:56] <mikko>	Portable C Compiler
| [Tuesday 14 December 2010] [04:26:09] <mikko>	ermm
| [Tuesday 14 December 2010] [04:27:30] <Steve-o>	maybe the change was recent
| [Tuesday 14 December 2010] [04:27:42] <mikko>	added to openbsd source tree 2007
| [Tuesday 14 December 2010] [04:27:49] <mikko>	was able to compile x86 kernel image 2009
| [Tuesday 14 December 2010] [04:27:56] <mikko>	according to wikipedia
| [Tuesday 14 December 2010] [04:28:13] <mikko>	but probably not the 'default' compiler yet
| [Tuesday 14 December 2010] [04:28:33] <Steve-o>	ok
| [Tuesday 14 December 2010] [04:28:42] <Steve-o>	tea time, catch you laters
| [Tuesday 14 December 2010] [04:29:11] <Steve-o>	I thnk Theo wants compiler that isn't GCC 3
| [Tuesday 14 December 2010] [04:29:17] <Steve-o>	hence the search for others
| [Tuesday 14 December 2010] [04:29:50] <mikko>	see you later
| [Tuesday 14 December 2010] [04:42:18] <sustrik>	morning
| [Tuesday 14 December 2010] [04:42:50] <mikko>	sustrik: did you see the patch for swap?
| [Tuesday 14 December 2010] [04:43:47] <sustrik>	juse seen it
| [Tuesday 14 December 2010] [04:43:58] <sustrik>	i have to do some administrative stuff
| [Tuesday 14 December 2010] [04:44:02] <sustrik>	then i'll have a look
| [Tuesday 14 December 2010] [04:44:26] <mikko>	col
| [Tuesday 14 December 2010] [04:44:28] <mikko>	+o
| [Tuesday 14 December 2010] [06:05:51] <mikko>	sustrik: does HWM option only work if set before bind/connect? If yes should the setsockopt fail?
| [Tuesday 14 December 2010] [06:09:45] <sustrik>	yes
| [Tuesday 14 December 2010] [06:09:55] <sustrik>	why should it fail?
| [Tuesday 14 December 2010] [06:10:10] <mikko>	if it has no effect
| [Tuesday 14 December 2010] [06:11:55] <sustrik>	it has effect on all subsequent connects and binds
| [Tuesday 14 December 2010] [06:56:55] <mikko>	hmm
| [Tuesday 14 December 2010] [06:57:02] <mikko>	how does that work?
| [Tuesday 14 December 2010] [06:57:10] <mikko>	i got a PUSH socket
| [Tuesday 14 December 2010] [06:57:16] <mikko>	connect, set hwm, connect
| [Tuesday 14 December 2010] [06:57:44] <mikko>	so that allows to do weighted load-balancing
| [Tuesday 14 December 2010] [06:59:28] <sustrik>	then the two connections have different HWMs
| [Tuesday 14 December 2010] [06:59:33] <sustrik>	the first is unlimited
| [Tuesday 14 December 2010] [06:59:44] <sustrik>	the second one has the hwm you've set
| [Tuesday 14 December 2010] [07:00:41] <mikko>	yeah, so in a scenario where second has HWM of 5 and it fills up the messages would go to first one
| [Tuesday 14 December 2010] [07:00:53] <mikko>	which makes sense, if you for example you have slower consumer on second socket
| [Tuesday 14 December 2010] [07:01:03] <mikko>	second connection i mean
| [Tuesday 14 December 2010] [08:53:40] <EricL>	I am debating using 0mq as a possible 'logserver'. Basically just listen for messages and write them to a file (but these messages are JSON and will be coming at a very high rate of speed).  Is this a good use-case?
| [Tuesday 14 December 2010] [09:02:38] <spht>	EricL: Do you have control over what is sending the log entries? If yes, perfect match (including possibilites for distributed logging), if no...uncertain
| [Tuesday 14 December 2010] [09:03:09] <EricL>	spht: I have 100% control over what's sending the logs.  I am writing what is sending the logs.
| [Tuesday 14 December 2010] [09:03:24] <spht>	EricL: Then it's perfect
| [Tuesday 14 December 2010] [09:03:26] <spht>	:)
| [Tuesday 14 December 2010] [09:04:22] <EricL>	spht: That's great news.  Problem is that I need to get it working quickly.  The client (sending piece) is in Ruby so that should be easy.  But I feel like the receiver should be in C for as much speed as possible (unless the receiver language doesn't matter).
| [Tuesday 14 December 2010] [09:04:57] <spht>	EricL: Prototype it in Ruby (I mean, a prototype will be just a few lines) and benchmark it. won't cost you much time
| [Tuesday 14 December 2010] [09:05:19] <spht>	EricL: Disclaimer:  I'm a 0mq-newbie ;)
| [Tuesday 14 December 2010] [09:05:37] <EricL>	spht: Fair enough.  How long did it take you to get something up and running?
| [Tuesday 14 December 2010] [09:06:26] <spht>	EricL:  I read the guide back to back, from there it's a matter of minutes in python (which is my weapon of choice), should be the same in ruby.  Read the guide though
| [Tuesday 14 December 2010] [09:07:02] <EricL>	I read the beginner part already, not the other 2 parts.
| [Tuesday 14 December 2010] [09:08:06] <spht>	I would bet that disk io will be the limiting factor not the messaging overhead...
| [Tuesday 14 December 2010] [09:08:18] <spht>	depending on what network you have of course :)
| [Tuesday 14 December 2010] [09:08:20] <EricL>	spht: I am thinking the same thing.
| [Tuesday 14 December 2010] [09:08:31] <EricL>	The network is a local GigE network.
| [Tuesday 14 December 2010] [09:12:25] <guido_g>	so split the work between multiple writers each with its own disk
| [Tuesday 14 December 2010] [09:13:08] <EricL>	guido_g: Sounds like that's the advanced stuff I need to work out.  Right now I am fine with a single machine.  The heavy load will be a month or two down the road.
| [Tuesday 14 December 2010] [09:13:14] <guido_g>	PUSH/PULL sockets would do the trick out of the box
| [Tuesday 14 December 2010] [09:14:00] <guido_g>	EricL: you were worried about the speed
| [Tuesday 14 December 2010] [09:17:13] <EricL>	guido_g: I am. That's why I am asking the questions.
| [Tuesday 14 December 2010] [09:18:12] <brandyn>	Hey I have a pub/sub setup where the sub is too busy to read all of the pub's messages.  What is happening now is that sub seems to be buffering everything.  How do I fix that?  I am using the python wrapper (I tried release and now dev from git)
| [Tuesday 14 December 2010] [09:19:03] <brandyn>	I have already set the HWM to 1, that didn't help.  And it is the client that seems to be buffering as it's memory usage balloons out of control
| [Tuesday 14 December 2010] [09:19:04] <guido_g>	if the sub is to slow, make it faster
| [Tuesday 14 December 2010] [09:19:23] <brandyn>	guido_g, not an option I'm shooting video frames at it and some devices can't handle all ofit
| [Tuesday 14 December 2010] [09:19:34] <guido_g>	if you set HWM you'll lose messages
| [Tuesday 14 December 2010] [09:19:41] <brandyn>	guido_g, yes that is what I want
| [Tuesday 14 December 2010] [09:19:54] <guido_g>	brandyn: too bad
| [Tuesday 14 December 2010] [09:19:56] <brandyn>	but I am not losing them enough clearly, the client is still buffering
| [Tuesday 14 December 2010] [09:20:44] <brandyn>	I guess I'm in the wrong place
| [Tuesday 14 December 2010] [09:30:03] <spht>	Uhm, 2 minute attention span is pretty short for asking questions on IRC :)
| [Tuesday 14 December 2010] [09:34:23] <spht>	EricL: You could also make the writer a pub socket and have different loggers listening to different messages, one way to partition the writes
| [Tuesday 14 December 2010] [09:35:57] <spht>	push socket on the other hand will give you round-robin style load balancing between different clients if you don't want to partition by message type
| [Tuesday 14 December 2010] [09:37:39] <guido_g>	don't forget that for now, the topic is filtered at the sub side
| [Tuesday 14 December 2010] [09:37:56] <guido_g>	so the message will be received and at least partially processed
| [Tuesday 14 December 2010] [09:38:22] <spht>	guido_g:  true!
| [Tuesday 14 December 2010] [09:38:46] <guido_g>	but i would go this route anyway, i'm a pub/sub fan :)
| [Tuesday 14 December 2010] [09:40:12] <EricL>	So the clients would be the pubs and the server would sub to multiiple clients?
| [Tuesday 14 December 2010] [09:40:51] <EricL>	I know that sounds backwards, but do I have the concept right?
| [Tuesday 14 December 2010] [09:41:18] <spht>	EricL:  no the clients should be sub sockets of course :)
| [Tuesday 14 December 2010] [09:41:37] <guido_g>	don't think in terms of sockets or connections
| [Tuesday 14 December 2010] [09:41:44] <guido_g>	start to think in messages instead
| [Tuesday 14 December 2010] [09:41:50] <EricL>	spht: The clients are the ones publishing the connections.
| [Tuesday 14 December 2010] [09:41:52] <guido_g>	makes life much easier
| [Tuesday 14 December 2010] [09:42:16] <guido_g>	publishing connections?
| [Tuesday 14 December 2010] [09:43:01] <spht>	why?
| [Tuesday 14 December 2010] [09:43:34] <guido_g>	why what?
| [Tuesday 14 December 2010] [09:44:18] <spht>	guido_g:  why the clients should bind and not the server
| [Tuesday 14 December 2010] [09:44:35] <guido_g>	spht: huh? where did i say that?
| [Tuesday 14 December 2010] [09:44:43] <spht>	guido_g:  you didn't, EricL did :)
| [Tuesday 14 December 2010] [09:44:47] <guido_g>	ahhh
| [Tuesday 14 December 2010] [09:45:03] <spht>	or, I didn't get enough coffee and is confused as usual ;)
| [Tuesday 14 December 2010] [09:45:20] <EricL>	spht: Maybe I should re-read the beginner stuff.  I guess I don't understand it.
| [Tuesday 14 December 2010] [09:46:00] <guido_g>	EricL: don't overreate the socket/connection/bind stuff
| [Tuesday 14 December 2010] [09:46:24] <EricL>	I am thinking that clients (the ones pushing the log messages) are the publishers and the server can subscribe to each client.
| [Tuesday 14 December 2010] [09:46:33] <guido_g>	as i said, to think in terms of messages is much more important
| [Tuesday 14 December 2010] [09:46:52] <guido_g>	client and server are way to overloaded
| [Tuesday 14 December 2010] [09:47:08] <guido_g>	i suggest using words like sender and receiver
| [Tuesday 14 December 2010] [09:47:29] <EricL>	guido_g: Ok.  Let me go back and do some reading.
| [Tuesday 14 December 2010] [09:47:51] <EricL>	I have to jump into a few meetings.  I'll be back later today if I can't figure this out.
| [Tuesday 14 December 2010] [09:48:23] <spht>	same here, bbl
| [Tuesday 14 December 2010] [09:48:34] <guido_g>	ahhh... the joys of working in a professional environment...   ]:->
| [Tuesday 14 December 2010] [11:38:37] <mikko>	good evening
| [Tuesday 14 December 2010] [12:07:56] <sustrik>	mikko: i haven't had chance to review the patch :(
| [Tuesday 14 December 2010] [12:08:03] <sustrik>	i have to leave now
| [Tuesday 14 December 2010] [12:08:08] <sustrik>	will do tomorrow
| [Tuesday 14 December 2010] [12:08:09] <sustrik>	sorry
| [Tuesday 14 December 2010] [12:08:20] <mikko>	no worries
| [Tuesday 14 December 2010] [12:08:44] <gandhijee>	hey, i installed zmq on my system, now my C++ programs won't compile unless i use -lzmq
| [Tuesday 14 December 2010] [12:09:07] <sustrik>	you mean unrelated C++ programs?
| [Tuesday 14 December 2010] [12:09:12] <mikko>	gandhijee: what system is that?
| [Tuesday 14 December 2010] [12:09:42] <gandhijee>	sustrik: right, even if i don't have the zmq header in, i still need -lzmq
| [Tuesday 14 December 2010] [12:10:00] <gandhijee>	2 systems, my gentoo laptop, plus my ARM toolchain thats installed on it
| [Tuesday 14 December 2010] [12:10:37] <mikko>	what is the error message you get?
| [Tuesday 14 December 2010] [12:10:56] <gandhijee>	one second
| [Tuesday 14 December 2010] [12:12:23] <gandhijee>	hmm, actually i guess it might be the way i am invoking the compile
| [Tuesday 14 December 2010] [12:12:34] <gandhijee>	i was calling gcc instead of g++ to compile to code
| [Tuesday 14 December 2010] [12:13:39] <mikko>	have you got CLFAGS, LDFLAGS or similar set?
| [Tuesday 14 December 2010] [12:20:53] <gandhijee>	no
| [Tuesday 14 December 2010] [14:41:16] <brandyn>	I have a pub/sub setup where the sub is too busy to read all of the pub's messages.  What is happening now is that sub seems to be buffering everything.  How do I fix that?  I am using the python wrapper (I tried release and now dev from git)
| [Tuesday 14 December 2010] [14:44:08] <cremes>	brandyn: question:  is the sub unable to keep up due to processing in python? or it can't read the messages fast enough (and you are not processing them at all)?
| [Tuesday 14 December 2010] [14:45:19] <brandyn>	cremes, it can't keep up
| [Tuesday 14 December 2010] [14:45:37] <brandyn>	cremes, I would like it to drop ones that it can't process, like the HWM
| [Tuesday 14 December 2010] [14:45:45] <cremes>	brandyn: can it keep up if you drop *all* messages?
| [Tuesday 14 December 2010] [14:45:45] <brandyn>	cremes, but it seems like there isn't an option like that
| [Tuesday 14 December 2010] [14:45:56] <brandyn>	cremes, yes if I just keep recv'ing
| [Tuesday 14 December 2010] [14:45:59] <cremes>	ok
| [Tuesday 14 December 2010] [14:46:13] <brandyn>	it is from a streaming sensor
| [Tuesday 14 December 2010] [14:46:18] <brandyn>	and some devices can't handle the data
| [Tuesday 14 December 2010] [14:46:22] <brandyn>	and it is ok to get some of the packets
| [Tuesday 14 December 2010] [14:46:29] <cremes>	then you're only hope is to increase the speed of your python processor; use a faster language or throw hardware at it
| [Tuesday 14 December 2010] [14:46:39] <brandyn>	but shouldn't there be a way to leak the buffer
| [Tuesday 14 December 2010] [14:46:45] <brandyn>	like the HWM on the PUB side
| [Tuesday 14 December 2010] [14:46:58] <cremes>	no, you can't tell how many messages are queued; that information is not exposed
| [Tuesday 14 December 2010] [14:47:14] <brandyn>	sure, but it knows
| [Tuesday 14 December 2010] [14:47:23] <brandyn>	so if I said "don't queue more than X messages"
| [Tuesday 14 December 2010] [14:47:27] <cremes>	the best you could do is process 1 out of X packets and drop the rest; that logic should be easy
| [Tuesday 14 December 2010] [14:47:29] <brandyn>	then it should work, just like HWM does now
| [Tuesday 14 December 2010] [14:47:47] <brandyn>	I see, so I can just close and reopen the socket?
| [Tuesday 14 December 2010] [14:48:28] <brandyn>	that seems like a hack, if the SUB listened to the HWM, then it could just drop packets and keep the newest ones
| [Tuesday 14 December 2010] [14:48:53] <cremes>	brandyn: no, you should not close & reopen the socket
| [Tuesday 14 December 2010] [14:49:00] <brandyn>	how do you drop the packets then?
| [Tuesday 14 December 2010] [14:49:15] <brandyn>	just recv really fast? or something
| [Tuesday 14 December 2010] [14:49:17] <cremes>	i meant that your python logic should drop x-1 of x packets; e.g. don't process them, just read and toss
| [Tuesday 14 December 2010] [14:49:24] <cremes>	yes
| [Tuesday 14 December 2010] [14:49:26] <brandyn>	ah gotcha, ok yeah I guess that can work
| [Tuesday 14 December 2010] [14:49:46] <brandyn>	so what I can probably do is set to to nonblocking
| [Tuesday 14 December 2010] [14:49:49] <cremes>	if (counter MOD 10 == 0) process else drop end
| [Tuesday 14 December 2010] [14:49:57] <brandyn>	and then keep recv'ing until I get the exception
| [Tuesday 14 December 2010] [14:49:59] <brandyn>	and just use the last one
| [Tuesday 14 December 2010] [14:50:06] <cremes>	non-blocking reads/writes aren't going to help you here
| [Tuesday 14 December 2010] [14:50:22] <cremes>	a regular blocking read should be fine
| [Tuesday 14 December 2010] [14:50:24] <brandyn>	what I mean is that I just want my app to get access to the newest message
| [Tuesday 14 December 2010] [14:50:30] <brandyn>	so I can just read all of them
| [Tuesday 14 December 2010] [14:50:36] <brandyn>	which will flush the buffer
| [Tuesday 14 December 2010] [14:50:40] <brandyn>	and then use the last one
| [Tuesday 14 December 2010] [14:51:06] <brandyn>	the nonblocking would tell me when the buffer is done
| [Tuesday 14 December 2010] [14:51:09] <cremes>	sure, that's fine
| [Tuesday 14 December 2010] [14:51:16] <brandyn>	cremes, you rock man, thank you
| [Tuesday 14 December 2010] [14:51:24] <cremes>	pay it forward... :)
| [Tuesday 14 December 2010] [14:52:03] <cremes>	brandyn: are you sure setting HWM on the publisher didn't help?
| [Tuesday 14 December 2010] [14:52:18] <cremes>	when a pub socket hits HWM for a subscriber, it should drop messages
| [Tuesday 14 December 2010] [14:52:28] <cremes>	try HWM = 1 if you haven't
| [Tuesday 14 December 2010] [14:54:24] <brandyn>	yeah I did
| [Tuesday 14 December 2010] [14:54:27] <brandyn>	but the client can read them
| [Tuesday 14 December 2010] [14:54:29] <brandyn>	that's the problem
| [Tuesday 14 December 2010] [14:54:48] <brandyn>	it appears there is no similar HWM for the sub
| [Tuesday 14 December 2010] [14:54:54] <brandyn>	but that's ok
| [Tuesday 14 December 2010] [14:55:17] <brandyn>	this is good enough, basically I offload ZMQ's SUB buffer to myself, and then apply my own restrictions
| [Tuesday 14 December 2010] [14:55:36] <cremes>	i'm not sure i follow; if a sub socket has more than HWM messages in its queue then the pub socket should detect that and drop packets
| [Tuesday 14 December 2010] [14:55:42] <cremes>	but whatever...
| [Tuesday 14 December 2010] [14:55:46] <cremes>	you have a solution
| [Tuesday 14 December 2010] [14:56:44] <brandyn>	oh I see, yeah it doesn't appear to do that
| [Tuesday 14 December 2010] [14:56:57] <brandyn>	I think the HWM applies only to the queue on the PUB size
| [Tuesday 14 December 2010] [14:57:02] <brandyn>	for each SUB
| [Tuesday 14 December 2010] [14:57:24] <brandyn>	like if I don't call recv, then my buffer blows up
| [Tuesday 14 December 2010] [14:57:35] <brandyn>	so it tells me that in the background is it buffering lots of goodies for me
| [Tuesday 14 December 2010] [14:57:40] <brandyn>	and I just didn't ask for them
| [Tuesday 14 December 2010] [14:59:41] <cremes>	hmmm, that's surprising; you might want to ask on the ML for clarification with your use-case
| [Tuesday 14 December 2010] [15:00:27] <brandyn>	yeah for sure, this is just a rushed project so I need a fix. It's the first time I've used ZMQ
| [Tuesday 14 December 2010] [15:14:00] <brandyn>	cremes, ok so strange problem.  If I read the socket opt for HWM, it is zero, if I set it, I get a totally different number
| [Tuesday 14 December 2010] [15:15:02] <cremes>	0 is the default
| [Tuesday 14 December 2010] [15:15:18] <cremes>	what value are you trying to set it to? and what do you get back when you read that option again?
| [Tuesday 14 December 2010] [15:15:39] <cremes>	btw, 0 means no limit
| [Tuesday 14 December 2010] [15:15:42] <brandyn>	yeah I know that
| [Tuesday 14 December 2010] [15:16:26] <brandyn>	so I set it to 1, and got thishttp://pastebin.com/xh9dCw6C
| [Tuesday 14 December 2010] [15:16:49] <brandyn>	crazy right?
| [Tuesday 14 December 2010] [15:17:52] <cremes>	HWM takes an unsigned 64-bit integer; maybe the python bindings aren't handling that right?
| [Tuesday 14 December 2010] [15:18:43] <brandyn>	yeah I see that
| [Tuesday 14 December 2010] [15:18:48] <brandyn>	I'll fix it an put in a patch
| [Tuesday 14 December 2010] [15:19:25] <brandyn>	yeah simple fix
| [Tuesday 14 December 2010] [15:22:42] <brandyn>	so I fixed that, it now returns the correct HWM, but same semantics
| [Tuesday 14 December 2010] [15:25:19] <cremes>	cool
| [Tuesday 14 December 2010] [16:10:51] <mikko>	evening ladies and gents
| [Tuesday 14 December 2010] [16:12:32] <cremes>	evening
| [Tuesday 14 December 2010] [16:18:16] <brandyn>	anyone here a python wrapper contributor?
| [Tuesday 14 December 2010] [16:18:58] <mikko>	brandyn: MinRK and bgranger pop in occasionally
| [Tuesday 14 December 2010] [16:19:34] <brandyn>	thanks
| [Tuesday 14 December 2010] [21:51:36] <brandyn>	does the new xpub/xsub allow for PUB side filtering?
| [Tuesday 14 December 2010] [21:51:57] <brandyn>	I haven't seen any documentation on it, just a few mailing list posts
| [Tuesday 14 December 2010] [21:56:07] <Steve-o>	that is what the design is for
| [Tuesday 14 December 2010] [21:56:31] <Steve-o>	the spec is on the mailing list
| [Tuesday 14 December 2010] [22:19:12] <Steve-o>	http://www.mail-archive.com/zeromq-dev@lists.zeromq.org/msg06247.html
| [Tuesday 14 December 2010] [23:18:48] <EricL>	Is anyone around?
| [Tuesday 14 December 2010] [23:20:42] <Steve-o>	all sleeping
| [Tuesday 14 December 2010] [23:21:24] <EricL>	I am trying to figure out what the best approach for my setup is to use 0MQ
| [Tuesday 14 December 2010] [23:22:39] <Steve-o>	to do what?
| [Tuesday 14 December 2010] [23:22:52] <EricL>	I have a log server and a few clients that are pushing a lot of data to the server.  I think I want something similar to pub/sub that is a queue on the client.
| [Tuesday 14 December 2010] [23:23:12] <EricL>	This way any one of multiple log servers can grab a line from the client and it pops off the queue.
| [Tuesday 14 December 2010] [23:24:43] <EricL>	from any client rather.
| [Tuesday 14 December 2010] [23:25:03] <Steve-o>	as in polling the logger
| [Tuesday 14 December 2010] [23:25:47] <EricL>	Kind of.  The way the logging happens is that there is a Ruby Resque job that does a few things and dumps the output to a log.
| [Tuesday 14 December 2010] [23:26:11] <Steve-o>	so, REQ/REP sockets then
| [Tuesday 14 December 2010] [23:26:51] <Steve-o>	it's not ideal to have the chatter back and forth though
| [Tuesday 14 December 2010] [23:27:44] <Steve-o>	you end up slowing the communication down to the RTT
| [Tuesday 14 December 2010] [23:28:28] <EricL>	That's what I am curious about.
| [Tuesday 14 December 2010] [23:30:10] <Steve-o>	which is why PUB is preferred, 
| [Tuesday 14 December 2010] [23:30:36] <Steve-o>	so what do you not like about PUB/SUB implementation?
| [Tuesday 14 December 2010] [23:31:03] <EricL>	Because then multiple log servers will be receiving the same msgs, no?
| [Tuesday 14 December 2010] [23:32:15] <Steve-o>	you can use different topics for each server
| [Tuesday 14 December 2010] [23:33:48] <EricL>	Log server?
| [Tuesday 14 December 2010] [23:34:05] <Steve-o>	yes, or only have the client connect to one log server
| [Tuesday 14 December 2010] [23:34:24] <Steve-o>	you can partition by connection or topic/subject
| [Tuesday 14 December 2010] [23:35:06] <EricL>	The problem there is that there is more data coming from the client than can be written to disk (on a MB/s basis)
| [Tuesday 14 December 2010] [23:36:13] <EricL>	That's why I am interested in something like 0MQ.  I just am not sure how to segment the write load across multiple servers.
| [Tuesday 14 December 2010] [23:36:15] <Steve-o>	so the messages will queue up on the log clients
| [Tuesday 14 December 2010] [23:36:40] <Steve-o>	you will probably want to use the zmq_swap function to spool onto disk too
| [Tuesday 14 December 2010] [23:38:43] <Steve-o>	log client: send messages as soon as available, zmq queues up messages if log server is congested receiving
| [Tuesday 14 December 2010] [23:38:44] <EricL>	That won't solve the issue since it's constantly going to be backing up.
| [Tuesday 14 December 2010] [23:39:21] <brandyn>	any know the state of pub side filtering?
| [Tuesday 14 December 2010] [23:40:24] <Steve-o>	EricL:  zmq is managing the queue and congestion for you, so it sounds ideal
| [Tuesday 14 December 2010] [23:40:26] <brandyn>	that is a really essential feature for my application and I have to emulate it now
| [Tuesday 14 December 2010] [23:40:46] <Steve-o>	brandyn:  have you checked the source in git/master?  
| [Tuesday 14 December 2010] [23:41:58] <brandyn>	Steve-o, yeah I got it this morning but it looks to be a copy of pub/sub (the XPUB/SUB that is)
| [Tuesday 14 December 2010] [23:42:28] <EricL>	It's only ideal if I can avoid duplication of msg logging on the server side.
| [Tuesday 14 December 2010] [23:43:13] <Steve-o>	duplication?  As in re-transmits?
| [Tuesday 14 December 2010] [23:43:15] <brandyn>	https://github.com/zeromq/zeromq2/commit/c80e7b80cc726ca7c29493c2553c8d19792bb6e5
| [Tuesday 14 December 2010] [23:44:31] <EricL>	duplication meaning that if I have more than 1 logserver and 3 clients pushing out msgs, I don't care which logserver the msgs go to as long as there are not any duplicate msgs.
| [Tuesday 14 December 2010] [23:44:42] <Steve-o>	brandyn:  I guess you have to ask Gerard Toonstra, he was submitting the patches and RFC
| [Tuesday 14 December 2010] [23:44:48] <EricL>	(from logserver to logserver)
| [Tuesday 14 December 2010] [23:45:41] <Steve-o>	EricL: so you also have a question of which logserver is being targetted
| [Tuesday 14 December 2010] [23:47:06] <EricL>	I don't care which logserver is being targeted as long as it gets there.
| [Tuesday 14 December 2010] [23:52:14] <Steve-o>	k, the link for loggly's notes has disappeared, http://www.zeromq.org/blog:loggy-switches-to-0mq
| [Tuesday 14 December 2010] [23:52:32] <EricL>	Looking.
| [Tuesday 14 December 2010] [23:55:38] <EricL>	Yea, that doesn't tell much.
| [Tuesday 14 December 2010] [23:57:32] <Steve-o>	maybe PUSH/PULL sockets, implements load sharing, not sure about guarantees on one only delivery
| [Wednesday 15 December 2010] [00:06:36] <EricL>	Hmm...I guess I am not sure of the best approach in general.
| [Wednesday 15 December 2010] [00:08:55] <EricL>	So you think I should setup a PUSH socket on the client and then write everything from the Resque processes to that socket (which will then do the buffering).
| [Wednesday 15 December 2010] [00:10:40] <EricL>	Then on the server(s), I should do a PULL and hope that I am not receiving duplicates.
| [Wednesday 15 December 2010] [00:13:25] <Steve-o>	yes, although I'd check with the devs on the mailing list about duplicate delivery
| [Wednesday 15 December 2010] [00:15:13] <Steve-o>	otherwise you need req/rep and you suffer RTT time
| [Wednesday 15 December 2010] [00:20:52] <EricL>	Alright.  I think I have some reading to do in order to understand how to implement all this.
| [Wednesday 15 December 2010] [00:21:27] <Steve-o>	the main devs should be online in a few hours time
| [Wednesday 15 December 2010] [00:21:43] <EricL>	They in EST?
| [Wednesday 15 December 2010] [00:22:30] <Steve-o>	MET I think
| [Wednesday 15 December 2010] [00:22:48] <Steve-o>	I only look after PGM stuff, all my middleware knowledge is TIBCO stuff
| [Wednesday 15 December 2010] [00:23:06] <EricL>	Gotchya.
| [Wednesday 15 December 2010] [00:25:42] <Steve-o>	In TIBCO you would use a Rendezvous Distributed Queue (RVDQ), but the implementation is very layered and not as efficient as 0MQ
| [Wednesday 15 December 2010] [00:28:20] <EricL>	I think I need the efficiency of 0MQ because of the amount of data I am dealing with.
| [Wednesday 15 December 2010] [02:01:43] <EricL>	Steve-o: Thanks.
| [Wednesday 15 December 2010] [06:09:20] <gb_>	hello
| [Wednesday 15 December 2010] [06:22:02] <sustrik>	hello
| [Wednesday 15 December 2010] [06:26:02] <mikko>	hi
| [Wednesday 15 December 2010] [06:35:39] <sustrik>	finally i'm getting to your patch
| [Wednesday 15 December 2010] [06:35:43] <sustrik>	sorry for the delay
| [Wednesday 15 December 2010] [06:35:52] <mikko>	i'm patching jmeter at the moment
| [Wednesday 15 December 2010] [06:36:05] <mikko>	only works master-slave if it's in the same network / no firewalls
| [Wednesday 15 December 2010] [07:04:33] <mikko>	sustrik: it seems that swap_t::full() was maybe an old implementation from where
| [Wednesday 15 December 2010] [07:04:46] <mikko>	sustrik: it seems unlikely that buffer_space () == 1 in any case
| [Wednesday 15 December 2010] [07:06:51] <sustrik>	mikko: the swap isn't my code
| [Wednesday 15 December 2010] [07:06:58] <sustrik>	i'm trying to make sense of it
| [Wednesday 15 December 2010] [07:07:35] <mikko>	the problem is was hitting was that swap was not full but there wasn't enough space for the given message
| [Wednesday 15 December 2010] [07:07:45] <mikko>	hence swap_t::fits(..
| [Wednesday 15 December 2010] [07:11:03] <Steve-o>	why does swap_t call GetCurrentThreadId on Windows but getpid on POSIX?  brain fart.
| [Wednesday 15 December 2010] [07:12:42] <sustrik>	it just need some unique number
| [Wednesday 15 December 2010] [07:13:01] <sustrik>	i think the code was written before 0mq was linked with libuuid
| [Wednesday 15 December 2010] [07:13:24] <Steve-o>	but not both thread id or process id, one of each
| [Wednesday 15 December 2010] [07:15:28] <Steve-o>	meh, also how many people use octets as a counter?  old people :P
| [Wednesday 15 December 2010] [07:21:20] <sustrik>	well, it's always one of them afaics
| [Wednesday 15 December 2010] [07:21:29] <sustrik>	tid on windows
| [Wednesday 15 December 2010] [07:21:33] <sustrik>	pid on posix
| [Wednesday 15 December 2010] [07:21:54] <sustrik>	but, presumably, uuid would be better
| [Wednesday 15 December 2010] [08:05:03] <sustrik>	mikko: still there?
| [Wednesday 15 December 2010] [08:29:13] <mikko>	yes
| [Wednesday 15 December 2010] [08:32:42] <sustrik>	mikko: i've sent a modified swap patch
| [Wednesday 15 December 2010] [08:32:56] <sustrik>	basically i've just removed some dead code
| [Wednesday 15 December 2010] [08:33:07] <mikko>	sustrik: you still have the implementation of full there
| [Wednesday 15 December 2010] [08:33:16] <sustrik>	oh my
| [Wednesday 15 December 2010] [08:33:17] <mikko>	no you dont
| [Wednesday 15 December 2010] [08:33:22] <mikko>	misread the patch
| [Wednesday 15 December 2010] [08:33:23] <sustrik>	it's commented out
| [Wednesday 15 December 2010] [08:33:40] <mikko>	yes, looks good to me. i can test it after i get a haircut
| [Wednesday 15 December 2010] [08:33:46] <sustrik>	goodo
| [Wednesday 15 December 2010] [08:33:50] <sustrik>	just ping me then
| [Wednesday 15 December 2010] [08:33:53] <sustrik>	and i'll apply it
| [Wednesday 15 December 2010] [08:34:37] <mikko>	i'll give you ping
| [Wednesday 15 December 2010] [08:34:42] <mikko>	i added freebsd 8.1 to build cluster
| [Wednesday 15 December 2010] [08:34:48] <mikko>	linux, solaris, win, freebsd now
| [Wednesday 15 December 2010] [08:36:02] <sustrik>	it's getting pretty complete :)
| [Wednesday 15 December 2010] [08:36:33] <mikko>	Bad file descriptor
| [Wednesday 15 December 2010] [08:36:33] <mikko>	nbytes != -1 (tcp_socket.cpp:197)
| [Wednesday 15 December 2010] [08:36:33] <mikko>	Abort trap (core dumped)
| [Wednesday 15 December 2010] [08:36:47] <mikko>	shutdown_stress on freebsd 8.1
| [Wednesday 15 December 2010] [08:41:30] <CIA-20>	zeromq2: 03Mikko Koppanen 07master * ra46980b 10/ (4 files in 4 dirs): 
| [Wednesday 15 December 2010] [08:41:30] <CIA-20>	zeromq2: Remove assertions from devices
| [Wednesday 15 December 2010] [08:41:30] <CIA-20>	zeromq2: Signed-off-by: Mikko Koppanen <mkoppanen@php.net> - http://bit.ly/e4ZWpR
| [Wednesday 15 December 2010] [08:42:23] <sustrik>	mikko: that's presumably the bug dhammika fixed
| [Wednesday 15 December 2010] [08:42:40] <sustrik>	i still have to look at the one you've reported yesterday
| [Wednesday 15 December 2010] [09:58:43] <mikko>	sustrik: you mean the HWM one?
| [Wednesday 15 December 2010] [10:00:05] <sustrik>	mikko: https://gist.github.com/848e949008e67ca542f7
| [Wednesday 15 December 2010] [10:07:14] <Guthur>	sustrik: I just noticed that clrzmq2 issue there now
| [Wednesday 15 December 2010] [10:07:19] <Guthur>	I've replied
| [Wednesday 15 December 2010] [10:07:35] <sustrik>	Guthur: good
| [Wednesday 15 December 2010] [10:07:46] <Guthur>	all I can say is... at least he finally got it built
| [Wednesday 15 December 2010] [10:08:21] <sustrik>	problem with clrzmq or problem with the user?
| [Wednesday 15 December 2010] [10:08:35] <Guthur>	user 
| [Wednesday 15 December 2010] [10:08:39] <sustrik>	:)
| [Wednesday 15 December 2010] [10:08:59] <Guthur>	He's wondering why passing in a String encoding object only returns strings
| [Wednesday 15 December 2010] [10:09:12] <Guthur>	he wanted binary
| [Wednesday 15 December 2010] [10:09:30] <Guthur>	which is the standard method, returning a byte array
| [Wednesday 15 December 2010] [10:10:00] <Guthur>	I need to check the comments again, I'm sure I was pretty explicit
| [Wednesday 15 December 2010] [10:10:34] <sustrik>	depends on the user
| [Wednesday 15 December 2010] [10:10:59] <sustrik>	however simply you explain, there's still someone who's not going to understand
| [Wednesday 15 December 2010] [10:11:03] <Guthur>	hehe comment -> Listen for message, and return it in string format
| [Wednesday 15 December 2010] [10:12:07] <Guthur>	actually to be fair there could be some improvement in the comment for the method he wanted
| [Wednesday 15 December 2010] [10:12:17] <Guthur>	I'll look into updating later
| [Wednesday 15 December 2010] [10:15:00] <sustrik>	Guthur: there have been something else wrt clrzmq discussed on the ML
| [Saturday 18 December 2010] [16:32:02] <mikko>	sustrik: no more race condition failures
| [Saturday 18 December 2010] [16:33:52] <mikko>	in the daily builds
| [Saturday 18 December 2010] [21:15:14] <raydeo>	is it possible that libcurl is interfering with zeromq? I have a system that uses 3 IPC sockets that runs very smoothly but when I turn on network uploading via libcurl I get bizarre behavior like dropped messages.
| [Saturday 18 December 2010] [22:01:22] <raydeo>	is there a reliable way to ensure that zmq is closing properly? I'm discovering that if a process dies without cleaning up it brings the whole system down.
| [Sunday 19 December 2010] [02:59:38] <mikko>	raydeo: is your libcurl thingia running in a thread?
| [Sunday 19 December 2010] [02:59:54] <mikko>	raydeo: just wondering because it would most likely block (?)
| [Sunday 19 December 2010] [12:17:42] <mikko>	good evening
| [Sunday 19 December 2010] [16:39:37] <mikko>	sustrik: found a segfault
| [Sunday 19 December 2010] [22:28:02] <davidstrauss>	I'm trying to figure out why my first attempt at a C++ echo/client implementation isn't exchanging any messages.
| [Sunday 19 December 2010] [22:28:32] <davidstrauss>	http://pastie.org/1390975
| [Sunday 19 December 2010] [22:28:51] <davidstrauss>	(the code is pastied)
| [Sunday 19 December 2010] [22:35:57] <Steve-o>	isn't rep supposed to bind?
| [Sunday 19 December 2010] [22:36:39] <davidstrauss>	Steve-o, I've tried that
| [Sunday 19 December 2010] [22:36:57] <davidstrauss>	Steve-o, Converting the connect to a bind on the echo.cpp doesn't make it work
| [Sunday 19 December 2010] [22:37:11] <Steve-o>	k
| [Sunday 19 December 2010] [22:37:15] <davidstrauss>	Steve-o, I have nearly identical code in Python working
| [Sunday 19 December 2010] [22:37:58] <Steve-o>	aha, nice
| [Sunday 19 December 2010] [22:38:04] <davidstrauss>	Steve-o, The echo.cpp version starts and then just waits forever for a message
| [Sunday 19 December 2010] [22:38:18] <davidstrauss>	Steve-o, And the client.cpp code "sends" a message without error.
| [Sunday 19 December 2010] [22:38:28] <davidstrauss>	Steve-o, But echo.cpp doesn't seem to get it
| [Sunday 19 December 2010] [22:39:03] <davidstrauss>	Steve-o, If I can get this working, I would happily publish this as a public example
| [Sunday 19 December 2010] [22:39:14] <Steve-o>	local_lat uses REP sockets
| [Sunday 19 December 2010] [22:39:26] <davidstrauss>	Steve-o, local_lat?
| [Sunday 19 December 2010] [22:39:37] <Steve-o>	latency performance test tool
| [Sunday 19 December 2010] [22:40:02] <Steve-o>	>> https://github.com/zeromq/zeromq2/blob/master/perf/local_lat.cpp
| [Sunday 19 December 2010] [22:40:44] <Steve-o>	with remote_lat being the REQ client
| [Sunday 19 December 2010] [22:41:21] <davidstrauss>	Steve-o, Unfortunately, that uses the C API, even though the code is C++
| [Sunday 19 December 2010] [22:43:01] <Steve-o>	the bind on the REQ socket should be something like tcp://eth0:5555
| [Sunday 19 December 2010] [22:43:29] <davidstrauss>	Steve-o, I need to bind on the REQ socket? Not just connect?
| [Sunday 19 December 2010] [22:44:07] <Steve-o>	bind only
| [Sunday 19 December 2010] [22:44:27] <Steve-o>	actually forget the eth0 thing, according to http://api.zeromq.org/zmq_tcp.html using the IP address should work too
| [Sunday 19 December 2010] [22:44:37] <davidstrauss>	Steve-o, All the demos I see have the ZMQ_REP server bind and the ZMQ_REQ connect
| [Sunday 19 December 2010] [22:44:49] <Steve-o>	change line 11 to socket.bind("tcp://127.0.0.1:5000");
| [Sunday 19 December 2010] [22:45:07] <Steve-o>	sorry, getting confused
| [Sunday 19 December 2010] [22:45:09] <davidstrauss>	Steve-o, I can't have the server and client both bind
| [Sunday 19 December 2010] [22:45:22] <Steve-o>	REQ should connect only, REP should bind only, right?
| [Sunday 19 December 2010] [22:45:43] <davidstrauss>	Steve-o, That's the impression i'm under, and it's not working for me.
| [Sunday 19 December 2010] [22:45:51] <davidstrauss>	Steve-o, Nor is it giving any errors.
| [Sunday 19 December 2010] [22:47:34] <Steve-o>	mmm, don't you have to do a bit more work in the echo.cpp loop
| [Sunday 19 December 2010] [22:47:49] <Steve-o>	it looks like you are re-using one message object all the time
| [Sunday 19 December 2010] [22:47:49] <davidstrauss>	Steve-o, How so?
| [Sunday 19 December 2010] [22:48:05] <davidstrauss>	Steve-o, Even reusing the same message object should work at least once
| [Sunday 19 December 2010] [22:48:19] <Steve-o>	yes, I would think so
| [Sunday 19 December 2010] [22:48:32] <davidstrauss>	Steve-o, The code never reaches "cout << "Message: " << (char *) message.data() << endl;"
| [Sunday 19 December 2010] [22:48:58] <Steve-o>	stuck in recv?
| [Sunday 19 December 2010] [22:49:12] <davidstrauss>	Steve-o, yes, blocking on getting a message
| [Sunday 19 December 2010] [22:49:44] <davidstrauss>	Steve-o, I just see "Waiting on message" when I run it
| [Sunday 19 December 2010] [22:51:54] <Steve-o>	but Python version is working?
| [Sunday 19 December 2010] [22:52:03] <davidstrauss>	Steve-o, yes
| [Sunday 19 December 2010] [22:52:41] <davidstrauss>	Steve-o, http://pastie.org/1391002
| [Sunday 19 December 2010] [22:53:37] <Steve-o>	try adding a socket.recv() in the client.cpp
| [Sunday 19 December 2010] [22:53:49] <Steve-o>	I'm guessing the client is terminating too quickly
| [Sunday 19 December 2010] [22:54:35] <davidstrauss>	Steve-o, woo hoo
| [Sunday 19 December 2010] [22:55:03] <davidstrauss>	Steve-o, the works!
| [Sunday 19 December 2010] [22:55:06] <davidstrauss>	that*
| [Sunday 19 December 2010] [22:55:18] <Steve-o>	which version of 0mq is this?
| [Sunday 19 December 2010] [22:56:27] <davidstrauss>	Steve-o, 2.0.10
| [Sunday 19 December 2010] [22:56:49] <Steve-o>	ok 2.1.0 will wait for you in zmq_term
| [Sunday 19 December 2010] [22:56:59] <Steve-o>	2.0 will exit out early
| [Sunday 19 December 2010] [22:57:01] <davidstrauss>	Steve-o, i see
| [Sunday 19 December 2010] [22:57:11] <Steve-o>	ZMQ_LINGER option
| [Sunday 19 December 2010] [22:57:38] <Steve-o>	otherwise you need to sleep or some other hack
| [Sunday 19 December 2010] [22:57:51] <davidstrauss>	Steve-o, honestly, it's kind of silly to use REP/REQ without the client waiting on the reply
| [Sunday 19 December 2010] [22:58:01] <davidstrauss>	Steve-o, I was just trying to get things working
| [Sunday 19 December 2010] [22:58:26] <Steve-o>	it also affects other sockets, like trying to PUB on message and quit
| [Sunday 19 December 2010] [22:58:53] <Steve-o>	which makes command line utilities a bit useless
| [Sunday 19 December 2010] [23:01:52] <Steve-o>	REQ/REP limits you on speed to RTT, you need other socket types for faster performance
| [Sunday 19 December 2010] [23:04:33] <davidstrauss>	Steve-o, to RTT?
| [Sunday 19 December 2010] [23:04:44] <Steve-o>	round-trip-time on the LAN/MAN/WAN
| [Sunday 19 December 2010] [23:05:41] <Steve-o>	0mq excels when you can batch up messages
| [Sunday 19 December 2010] [23:06:47] <Steve-o>	depends on application architecture and requirements
| [Sunday 19 December 2010] [23:07:05] <Steve-o>	whether you wish to allow several outstanding requests for example
| [Sunday 19 December 2010] [23:18:10] <davidstrauss>	Steve-o, Cool. So, I have PHP, Python, and C++ interoperating on the REQ/REP pattern. I'll try to clean up the code and publish it.
| [Sunday 19 December 2010] [23:19:10] <davidstrauss>	Steve-o, thanks for your help
| [Sunday 19 December 2010] [23:26:34] <Steve-o>	np
| [Sunday 19 December 2010] [23:28:35] <davidstrauss>	Is there any good comparison between using Thrift's built-in RPC support vs. using ZeroMQ?
| [Sunday 19 December 2010] [23:32:30] <Steve-o>	I've seen it come up, but nothing detailed apart from discussing it
| [Sunday 19 December 2010] [23:35:30] <Steve-o>	I think there was a protobuf vs thrift as message format above zeromq
| [Sunday 19 December 2010] [23:35:41] <Steve-o>	nothing on the actual RPC implementation
| [Sunday 19 December 2010] [23:36:13] <Steve-o>	lol, thrift over 0mq:  http://www.mail-archive.com/thrift-dev@incubator.apache.org/msg08473.html
| [Sunday 19 December 2010] [23:36:41] <davidstrauss>	Steve-o, Well, it is necessary to pick *some* sort of format for messages.
| [Sunday 19 December 2010] [23:37:00] <davidstrauss>	Steve-o, I'm looking at pure Thrift vs. Thrift serialization + ZeroMQ
| [Sunday 19 December 2010] [23:37:49] <Steve-o>	ok, I like protobufs as it is easy to roll
| [Sunday 19 December 2010] [23:38:12] <Steve-o>	still a bit backward compared with TIBCO quick forms though
| [Sunday 19 December 2010] [23:38:36] <davidstrauss>	Steve-o, Yeah, but I'm working with primarily PHP clients, and Protobufs only have experimental PHP support with no accelerated serialization
| [Sunday 19 December 2010] [23:39:33] <Steve-o>	ok
| [Sunday 19 December 2010] [23:40:01] <Steve-o>	You also have JSON and derivatives to pick from then
| [Sunday 19 December 2010] [23:40:39] <davidstrauss>	Steve-o, JSON isn't great for C++ servers, nor is it a terribly efficient format :-/
| [Sunday 19 December 2010] [23:41:39] <Steve-o>	but it's easy for PHP, JavaScript, and humans to read :D
| [Sunday 19 December 2010] [23:41:56] <Steve-o>	and there are libraries for it everywhere
| [Sunday 19 December 2010] [23:42:04] <davidstrauss>	Steve-o, agreed
| [Sunday 19 December 2010] [23:42:19] <Steve-o>	it's less cumbersome than XDR anyhow
| [Sunday 19 December 2010] [23:44:00] <Steve-o>	you could roll your own PHP extension with fixed scope,
| [Sunday 19 December 2010] [23:48:47] <Steve-o>	Google lacks dynamic forms, everything is static compiled
| [Monday 20 December 2010] [03:16:36] <sustrik>	hi mikko: what segfault?
| [Monday 20 December 2010] [05:22:49] <mikko>	sustrik: https://gist.github.com/17fb87b54e83832354b5
| [Monday 20 December 2010] [05:24:39] <sustrik>	mikko: looks like a deallocation of invalid message
| [Monday 20 December 2010] [05:24:56] <sustrik>	do you have a test program?
| [Monday 20 December 2010] [05:25:07] <mikko>	the way i reproduce is by creating a rep socket
| [Monday 20 December 2010] [05:25:11] <mikko>	then telnet in
| [Monday 20 December 2010] [05:25:19] <mikko>	press ctrl+c in telnet 
| [Monday 20 December 2010] [05:25:22] <mikko>	and enter twice
| [Monday 20 December 2010] [05:25:33] <sustrik>	sorry, what's enter twice?
| [Monday 20 December 2010] [05:25:46] <mikko>	 
| [Monday 20 December 2010] [05:25:47] <mikko>	 
| [Monday 20 December 2010] [05:25:54] <sustrik>	in telnet?
| [Monday 20 December 2010] [05:25:57] <mikko>	yes
| [Monday 20 December 2010] [05:26:11] <sustrik>	let me try...
| [Monday 20 December 2010] [05:26:11] <mikko>	i've been too lazy to check the exact bytes that combo sends :)
| [Monday 20 December 2010] [05:26:20] <sustrik>	doesn't matter
| [Monday 20 December 2010] [05:27:16] <sustrik>	reproduced
| [Monday 20 December 2010] [05:27:18] <sustrik>	thanks!
| [Monday 20 December 2010] [05:30:43] <mikko>	np
| [Monday 20 December 2010] [05:31:47] <mikko>	https://gist.github.com/21ee1c85b1b2f6cbba66
| [Monday 20 December 2010] [05:31:54] <mikko>	that's from my gdb session last night
| [Monday 20 December 2010] [05:47:52] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r112d0cd 10/ src/decoder.cpp : 
| [Monday 20 December 2010] [05:47:52] <CIA-21>	zeromq2: Fix the segfault when over-sized message is rejected.
| [Monday 20 December 2010] [05:47:52] <CIA-21>	zeromq2: The in_progress message inside of decoder was left
| [Monday 20 December 2010] [05:47:52] <CIA-21>	zeromq2: uninitialised in such a case.
| [Monday 20 December 2010] [05:47:52] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/grKk2b
| [Monday 20 December 2010] [05:53:09] <mikko>	sustrik: gj, that was quick
| [Monday 20 December 2010] [06:12:00] <sustrik>	:)
| [Monday 20 December 2010] [07:05:46] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r51d2d9b 10/ src/decoder.cpp : 
| [Monday 20 December 2010] [07:05:46] <CIA-21>	zeromq2: Yet one more fix for oversized messages.
| [Monday 20 December 2010] [07:05:46] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/ez2JYr
| [Monday 20 December 2010] [13:41:56] <myraft_>	mikko - I haven't been back here for a while. Quick update - got past the initial Java HelloWorld queue setup. The problem was the way I was running the Java code on Ubuntu.
| [Monday 20 December 2010] [13:42:05] <myraft_>	Thanks for the help the other day.
| [Monday 20 December 2010] [13:44:51] <mikko>	no problem
| [Monday 20 December 2010] [13:45:01] <mikko>	what is the problem of running java code on ubuntu?
| [Monday 20 December 2010] [14:01:58] <myraft_>	mikko - the guide explicitly states to calls to run it with -Djava.library.path="/usr/local/lib". I did sudo ldconfig , which in theory should have loaded it and be avaiable for any program to use (at least that was my impression). Once I set that as VM Argument - everythigng started working.
| [Monday 20 December 2010] [14:09:58] <mikko>	nice!
| [Monday 20 December 2010] [14:10:05] <mikko>	so the error message was correct after all
| [Monday 20 December 2010] [14:10:34] <mikko>	good to know, now we know what to tell the next guy asking
| [Monday 20 December 2010] [14:25:09] <dv_>	woot
| [Monday 20 December 2010] [14:25:19] <dv_>	i can now send asynchronous function calls through zeromq
| [Monday 20 December 2010] [14:32:41] <mikko>	dv_: cool!
| [Monday 20 December 2010] [14:32:52] <mikko>	dv_: what language are you working in?
| [Monday 20 December 2010] [14:32:55] <dv_>	its not rpc, mind you
| [Monday 20 December 2010] [14:33:05] <dv_>	more like boost signals/libsigc++/qt signals
| [Monday 20 December 2010] [14:33:14] <dv_>	mikko, right now its for c++ and ruby
| [Monday 20 December 2010] [14:33:32] <dv_>	i plan on adding support for more languages. especially javascript through websockets
| [Monday 20 December 2010] [14:33:32] <mikko>	im doing something similar in my current project
| [Monday 20 December 2010] [14:33:40] <mikko>	i got "intercomm" for communicating between threads
| [Monday 20 December 2010] [14:33:47] <mikko>	sending shutdown messages etc
| [Monday 20 December 2010] [14:33:50] <dv_>	on one side, i do send_call("foobar", params); 
| [Monday 20 December 2010] [14:33:57] <dv_>	on the other side, i previously registered a "foobar" callback
| [Monday 20 December 2010] [14:34:03] <mikko>	nice
| [Monday 20 December 2010] [14:34:14] <dv_>	and it transmits the params etc. through the wire
| [Monday 20 December 2010] [14:34:21] <dv_>	the c++ side uses a lot of metaprogramming fu :)
| [Monday 20 December 2010] [14:34:29] <mikko>	nice, nice
| [Monday 20 December 2010] [14:35:13] <dv_>	do you send more complex types, such as arrays?
| [Monday 20 December 2010] [14:35:31] <mikko>	no, my use-case is very simple
| [Monday 20 December 2010] [14:35:32] <dv_>	i want to limit things, that is, primitive types, and maybe binary buffers
| [Monday 20 December 2010] [14:35:39] <mikko>	just sending ints
| [Monday 20 December 2010] [14:35:57] <dv_>	but more heavyweight transmissions need their dedicated channel anyway in my opinion
| [Monday 20 December 2010] [14:36:16] <mikko>	im sending enums like HTTPD_SHUTDOWN, SEND_STATS etc
| [Monday 20 December 2010] [14:36:20] <mikko>	fairly simple
| [Monday 20 December 2010] [14:36:41] <dv_>	yeah, usually this kind of communication makes up the majority of it all
| [Monday 20 December 2010] [14:36:57] <mikko>	i got a libevent based httpd that pushes data down to 0MQ, which is consumed by classifier nodes and then aggregated from classifiers in aggregator nodes
| [Monday 20 December 2010] [14:37:07] <mikko>	in=in to
| [Monday 20 December 2010] [14:40:43] <dv_>	btw. in case you do something with epgm,
| [Monday 20 December 2010] [14:40:55] <dv_>	try using your IP address instead of the NIC name
| [Monday 20 December 2010] [14:41:38] <dv_>	sometimes openpgm seems to have problems with the nic's name, this issue was discussed a bit in the mailing list a while ago
| [Monday 20 December 2010] [20:25:15] <falconair>	hi all, a few newbie questions: can zeromq api be used to do raw tcp/ip programming?
| [Monday 20 December 2010] [21:21:08] <xpromache1>	hello guys, I'm considering zmq for replacing corba in an application
| [Monday 20 December 2010] [21:21:25] <xpromache1>	the typical rpc stuff I think I know how to implement
| [Monday 20 December 2010] [21:22:00] <xpromache1>	but at some point a client can send a request to the server that will have to send some large amounts of data back to the clinet
| [Monday 20 December 2010] [21:22:13] <xpromache1>	how is this best done?
| [Monday 20 December 2010] [21:22:47] <xpromache1>	I guess I need to answer the request with "OK, here it comes", and then to open another socket for pushing the data?
| [Monday 20 December 2010] [21:22:55] <xpromache1>	what sort of socket?
| [Monday 20 December 2010] [23:53:37] <cremes>	falconair: no
| [Monday 20 December 2010] [23:53:54] <cremes>	it's a higher level api than that with a few abstractions
| [Monday 20 December 2010] [23:54:02] <cremes>	make sure to read the guide linked off of the main page
| [Monday 20 December 2010] [23:54:34] <cremes>	xpromache1: open a socket for each kind of messaging pattern you plan to use
| [Monday 20 December 2010] [23:54:59] <cremes>	if you are waiting for a request/reply to start a large data download, use the REQ/REP sockets for that purpose
| [Monday 20 December 2010] [23:55:21] <cremes>	for the big data download, consider PUB/SUB or PUSH/PULL depending on what you need
| [Monday 20 December 2010] [23:55:36] <cremes>	you may even want to look at PAIR; it really depends on your app requirement
| [Monday 20 December 2010] [23:56:03] <cremes>	make sure to read the guide linked off of the main page; it may help you pick the right pattern and its associated sockets
| [Monday 20 December 2010] [23:56:40] <xpromache1>	ok, thanks for the answer
| [Monday 20 December 2010] [23:56:51] <xpromache1>	is there a way to use all these over a limited number of ports
| [Monday 20 December 2010] [23:57:00] <xpromache1>	like one for req/rep
| [Monday 20 December 2010] [23:57:08] <xpromache1>	and another one for the data tansfer
| [Tuesday 21 December 2010] [00:00:39] <cremes>	absolutely; each socket should get its own transport (tcp/pgm/ipc/inproc) and port (not necessary for transports other than tcp)
| [Tuesday 21 December 2010] [00:01:20] <cremes>	0mq doesn't use "random" ports; you specifically connect or bind to whatever you need
| [Tuesday 21 December 2010] [00:02:33] <xpromache1>	yes but I want to use the same port for all clients
| [Tuesday 21 December 2010] [00:02:40] <xpromache1>	or maybe this doesn't make sense
| [Tuesday 21 December 2010] [00:02:59] <xpromache1>	I mean it only makes sense when there is some firewalls in between
| [Tuesday 21 December 2010] [00:03:14] <xpromache1>	but this is not the use case where zeromq should be used, right?
| [Tuesday 21 December 2010] [00:03:57] <cremes>	xpromache1: not really sure what you are trying to d
| [Tuesday 21 December 2010] [00:04:13] <cremes>	if you have a complex use-case, you may consider posting it to the ML for comment
| [Tuesday 21 December 2010] [00:04:58] <xpromache1>	not really complex
| [Tuesday 21 December 2010] [00:05:06] <xpromache1>	it's like a database driver
| [Tuesday 21 December 2010] [00:05:16] <xpromache1>	you execute some small queries from time to time
| [Tuesday 21 December 2010] [00:05:27] <xpromache1>	but ocasionally you want to retrieve a lot of data
| [Tuesday 21 December 2010] [00:05:37] <xpromache1>	and I prefer not to have a request for each row
| [Tuesday 21 December 2010] [00:07:36] <cremes>	then you would probably use the pattern i suggested above; REQ/REP for the query, PUB/SUB for the data transmission
| [Tuesday 21 December 2010] [00:08:04] <cremes>	but if thisis over tcp,then the reqp/rep would get its own port as would the pub/sub
| [Tuesday 21 December 2010] [00:08:14] <cremes>	they cannot share the same port simultaneously
| [Tuesday 21 December 2010] [00:08:41] <xpromache1>	so if I have 10 clients connected simultaneously, how many ports do I need?
| [Tuesday 21 December 2010] [00:09:14] <cremes>	2, one for the req/rep and 1 for the pub/sub
| [Tuesday 21 December 2010] [00:10:02] <xpromache1>	but then all the clients will get all the data even from the requests of the other clients?
| [Tuesday 21 December 2010] [00:10:34] <cremes>	they could ignore it if the published topic is not something they are interested in; altnerately, use the XREQ/XREP socket types
| [Tuesday 21 December 2010] [00:10:38] <cremes>	have you read the guide yet?
| [Tuesday 21 December 2010] [00:11:22] <xpromache1>	I did partly but this is not clear to me
| [Tuesday 21 December 2010] [00:11:32] <xpromache1>	exactly what you can multiplex on a server socket
| [Tuesday 21 December 2010] [00:12:22] <cremes>	i may not be able to clarify it completely for you :)
| [Tuesday 21 December 2010] [00:12:51] <cremes>	a 0mq socket is a smart socket; it can connect/bind to multiple endpoints simultaneously
| [Tuesday 21 December 2010] [00:13:13] <cremes>	so in your situation the server would likely bind a REP or XREP socket
| [Tuesday 21 December 2010] [00:13:36] <xpromache1>	yes, that's clear for the response reply pattern
| [Tuesday 21 December 2010] [00:13:38] <cremes>	the clients would come in with REQ (or XREQ) sockets via  "connect" call; 0mq handles the multiplexing for you
| [Tuesday 21 December 2010] [00:13:48] <xpromache1>	what is not clear is for the data transfer
| [Tuesday 21 December 2010] [00:14:07] <cremes>	well, i suggested pub/sub but maybe that's not appropriate
| [Tuesday 21 December 2010] [00:14:16] <xpromache1>	so a client connects and sends a request for the data
| [Tuesday 21 December 2010] [00:14:18] <cremes>	you could use the xreq/xrep sockets for the data transfer
| [Tuesday 21 December 2010] [00:14:27] <cremes>	go on
| [Tuesday 21 December 2010] [00:14:27] <xpromache1>	I can send a reply saying connect here to get the data
| [Tuesday 21 December 2010] [00:14:32] <cremes>	sure
| [Tuesday 21 December 2010] [00:14:41] <xpromache1>	but what does it mean here
| [Tuesday 21 December 2010] [00:15:08] <cremes>	"here" where? explain.
| [Tuesday 21 December 2010] [00:15:17] <xpromache1>	that's my question
| [Tuesday 21 December 2010] [00:15:24] <xpromache1>	what do I answer to the client
| [Tuesday 21 December 2010] [00:15:30] <xpromache1>	where to connect to get its data
| [Tuesday 21 December 2010] [00:15:55] <xpromache1>	do I have to start a new thread, create a new socket on a random port, and start pushing data once a client is connected
| [Tuesday 21 December 2010] [00:16:05] <xpromache1>	or there is a smarter way
| [Tuesday 21 December 2010] [00:16:11] <cremes>	you could send in your reply something like: :transport => :tcp, :address => '10.10.4.48', :port => 1800
| [Tuesday 21 December 2010] [00:16:30] <cremes>	then the client would know where to go for getting the data
| [Tuesday 21 December 2010] [00:16:49] <cremes>	you can't do random ports without informing the client what it will be
| [Tuesday 21 December 2010] [00:17:02] <xpromache1>	yes, I realize that
| [Tuesday 21 December 2010] [00:17:13] <xpromache1>	I was hoping that it is somehow possible to do without random ports
| [Tuesday 21 December 2010] [00:17:13] <cremes>	you *could* use another thread or use the poll api to do it all within one
| [Tuesday 21 December 2010] [00:17:17] <xpromache1>	just one fixed port
| [Tuesday 21 December 2010] [00:17:37] <xpromache1>	like I have port x for request/reply
| [Tuesday 21 December 2010] [00:17:43] <xpromache1>	and port y for data transfer
| [Tuesday 21 December 2010] [00:17:52] <cremes>	sure, you could use 1 fixed port but you could run into issues if you have lots of concurrent requests/replies
| [Tuesday 21 December 2010] [00:18:36] <cremes>	you would probably want to use xreq/xrep sockets so your data transfer could target the right client
| [Tuesday 21 December 2010] [00:18:53] <cremes>	take a look at the "advanced routing" section of the guide; i'm pretty sure they wrote about that
| [Tuesday 21 December 2010] [00:19:15] <xpromache1>	but xreq/xrep needs one message in both ways
| [Tuesday 21 December 2010] [00:19:23] <cremes>	not true
| [Tuesday 21 December 2010] [00:19:24] <xpromache1>	I would need something like xpush xpull
| [Tuesday 21 December 2010] [00:19:31] <cremes>	not true
| [Tuesday 21 December 2010] [00:19:48] <cremes>	reqp/rep enforces a strict request/reply/request/reply pattern
| [Tuesday 21 December 2010] [00:19:59] <cremes>	the xreq/xrep sockets do *not* enforce that
| [Tuesday 21 December 2010] [00:20:32] <cremes>	so, using xreq/xrep, you could send a single request and get a multiple message reply
| [Tuesday 21 December 2010] [00:21:45] <xpromache1>	ok, I didn't know that
| [Tuesday 21 December 2010] [00:22:08] <xpromache1>	I will look further into it, thanks for the hints
| [Tuesday 21 December 2010] [00:22:40] <cremes>	no prob...
| [Tuesday 21 December 2010] [00:22:43] <cremes>	time for bed!
| [Tuesday 21 December 2010] [00:26:11] <xpromache1>	me too, I have to go to work in 2 hours :(
| [Tuesday 21 December 2010] [01:15:25] <bkad>	anyone know how to get the zmq_server binary? cant find it in the installation instructions
| [Tuesday 21 December 2010] [01:22:04] <guido_g>	what server?
| [Tuesday 21 December 2010] [01:23:23] <bkad>	zmq_server?
| [Tuesday 21 December 2010] [01:23:39] <bkad>	there's lots of references to it in the zmq docs
| [Tuesday 21 December 2010] [01:24:10] <bkad>	but the ./configure, make, make install didn't build that binary
| [Tuesday 21 December 2010] [01:24:58] <guido_g>	the docs are a bit outdated i fear
| [Tuesday 21 December 2010] [01:25:07] <bkad>	in http://www.zeromq.org/code:examples-exchange
| [Tuesday 21 December 2010] [01:25:12] <bkad>	under Running It
| [Tuesday 21 December 2010] [01:25:20] <guido_g>	there is a devices directory w/ some executables
| [Tuesday 21 December 2010] [01:25:27] <guido_g>	ouch
| [Tuesday 21 December 2010] [01:25:38] <guido_g>	this example is way outdated
| [Tuesday 21 December 2010] [01:25:46] <sustrik>	see the top of the page
| [Tuesday 21 December 2010] [01:25:48] <sustrik>	WARNING: This text is deprecated and refers to an old version of MQ. It remains here for historical interest. DO NOT USE THIS TO LEARN MQ.
| [Tuesday 21 December 2010] [01:25:56] <guido_g>	it'S even pre zeromq2 afair
| [Tuesday 21 December 2010] [01:26:03] <bkad>	ahhh, oops
| [Tuesday 21 December 2010] [03:34:47] <sustrik>	mikko: there's a build patch on the mailing list
| [Tuesday 21 December 2010] [03:34:53] <sustrik>	can you give it a look?
| [Tuesday 21 December 2010] [03:35:20] <sustrik>	mato is on his way to new zealand for next few days
| [Tuesday 21 December 2010] [03:56:25] <mikko>	sustrik: sure
| [Tuesday 21 December 2010] [03:56:37] <mikko>	it looks like my flight is departing today
| [Tuesday 21 December 2010] [03:56:45] <mikko>	causiously excited
| [Tuesday 21 December 2010] [03:57:52] <sustrik>	good luck :)
| [Tuesday 21 December 2010] [04:28:07] <mikko>	reviewed
| [Tuesday 21 December 2010] [04:29:05] <sustrik>	thanks
| [Tuesday 21 December 2010] [04:56:53] <mikko>	Steve-o: hi
| [Tuesday 21 December 2010] [04:57:03] <mikko>	what does the scons build produce?
| [Tuesday 21 December 2010] [04:57:05] <mikko>	Makefiles?
| [Tuesday 21 December 2010] [04:57:27] <Steve-o>	No it runs commands in Python directly
| [Tuesday 21 December 2010] [04:58:00] <Steve-o>	CMake is the Make wrapper
| [Tuesday 21 December 2010] [04:58:48] <mikko>	ok
| [Tuesday 21 December 2010] [04:58:56] <Steve-o>	you are supposed to be able to see the commands by "scons -Q" but I haven't seen that working on my Scons files in a long time
| [Tuesday 21 December 2010] [04:59:00] <mikko>	would've been nice if it produced something that could be directly used
| [Tuesday 21 December 2010] [04:59:29] <Steve-o>	well, all the other build systems kinda suck though :P
| [Tuesday 21 December 2010] [05:00:20] <Steve-o>	Although I think I had to patch Scons again for Intel C on Linux, urgh
| [Tuesday 21 December 2010] [05:00:50] <Steve-o>	CMake just doesn't support anything interesting
| [Tuesday 21 December 2010] [05:02:26] <mikko>	interesting development, my airline sends twitter DMs to inform about flights
| [Tuesday 21 December 2010] [05:04:06] <Steve-o>	Cathay likes to send emails after the flight has left
| [Tuesday 21 December 2010] [05:04:10] <mikko>	im wondering if we should split OS specific builds to separate automake files in zmq
| [Tuesday 21 December 2010] [05:04:24] <mikko>	it might be more maintainable than conditionals in one file
| [Tuesday 21 December 2010] [05:04:54] <Steve-o>	Makes patching a bit cleaner
| [Tuesday 21 December 2010] [05:06:37] <Steve-o>	unless you want to write several new autoconf rules
| [Tuesday 21 December 2010] [05:06:37] <mikko>	yeah
| [Tuesday 21 December 2010] [05:08:41] <Steve-o>	only ~24 tests required :P
| [Tuesday 21 December 2010] [05:09:17] <Steve-o>	many should already have autoconf macros available
| [Tuesday 21 December 2010] [05:11:08] <mikko>	it feels like duplicating work
| [Tuesday 21 December 2010] [05:11:10] <mikko>	hmm
| [Tuesday 21 December 2010] [05:11:28] <mikko>	would be nicer to launch scons from zmq build
| [Tuesday 21 December 2010] [05:11:34] <mikko>	and then just link
| [Tuesday 21 December 2010] [05:12:18] <Steve-o>	I've looked for a long time for building Debian packages
| [Tuesday 21 December 2010] [05:13:02] <Steve-o>	there isn't much out there despite all the big packages using SCons (Blender, Quake 3, etc)
| [Tuesday 21 December 2010] [05:14:37] <Steve-o>	as in, for nice hooks for the deb-buildpackager
| [Tuesday 21 December 2010] [05:14:58] <Steve-o>	you can always build a basic scons command based off uname otherwise
| [Tuesday 21 December 2010] [05:15:11] <mikko>	autoconf might be slightly dreadful but its fairly well supported
| [Tuesday 21 December 2010] [05:19:10] <Steve-o>	I don't think you can easily get multiple build environments in autoconf/automake though
| [Tuesday 21 December 2010] [05:19:30] <Steve-o>	Scons is killing me on crap compiler dependencies for unit tests
| [Tuesday 21 December 2010] [05:29:32] <Steve-o>	autoconf is a bit too cumbersome for testing different compilers on one platform
| [Tuesday 21 December 2010] [05:29:56] <Steve-o>	I'm sure there has to be a better way \:D/
| [Tuesday 21 December 2010] [05:30:54] <mikko>	it is slightly cumbersome yes
| [Tuesday 21 December 2010] [09:15:45] <ptrb>	correct me if I'm wrong, but if I'm sitting in a blocking recv() on a socket in one thread, and I zmq_term() the context in another thread, the recv() should return (in C++, should throw) -- right?
| [Tuesday 21 December 2010] [09:22:10] <sustrik>	ptrb: right
| [Tuesday 21 December 2010] [09:22:17] <sustrik>	ETERM
| [Tuesday 21 December 2010] [09:26:06] <ptrb>	hmm... the zmq_term() goes through OK, but I'm still blocking in the other thread... time for a minimal test case I guess :\
| [Tuesday 21 December 2010] [09:28:41] <sustrik>	yes, please
| [Tuesday 21 December 2010] [10:48:50] <mikko>	sustrik: zmq_term(ZMQ_NOBLOCK) would be useful
| [Tuesday 21 December 2010] [10:48:56] <mikko>	or another function call
| [Tuesday 21 December 2010] [10:51:11] <cremes>	mikko: something similar has been discussed on the ML; sustrik says it isn't possible
| [Tuesday 21 December 2010] [10:51:37] <sustrik>	you mean, instead setting all the sockets to ZMQ_LINGER=0
| [Tuesday 21 December 2010] [10:51:44] <sustrik>	right?
| [Tuesday 21 December 2010] [10:54:11] <mikko>	sustrik: no
| [Tuesday 21 December 2010] [10:54:21] <mikko>	sustrik: i mean instead of manually closing all sockets
| [Tuesday 21 December 2010] [10:54:36] <mikko>	because currently it's not possible to force closing of sockets
| [Tuesday 21 December 2010] [10:55:07] <sustrik>	hm, how would you migrate all the sockets to the thread calling zmq_term()?
| [Tuesday 21 December 2010] [10:55:48] <mikko>	do they need to be migrated to obtain information whether zmq_term would block?
| [Tuesday 21 December 2010] [10:56:18] <mikko>	i meant that zmq_term() would return EGAIN if given a flag
| [Tuesday 21 December 2010] [10:56:23] <mikko>	EAGAIN*
| [Tuesday 21 December 2010] [10:56:29] <sustrik>	how would the main thread know that they are not used in the moment otherwise?
| [Tuesday 21 December 2010] [10:56:43] <sustrik>	at the moment*
| [Tuesday 21 December 2010] [10:57:31] <sustrik>	you cannot grab a socket from underneath the feer of another thread
| [Tuesday 21 December 2010] [10:58:54] <mikko>	sockets is removed from sockets array in context when it's closed?
| [Tuesday 21 December 2010] [10:59:21] <sustrik>	yes
| [Tuesday 21 December 2010] [10:59:23] <mikko>	slightly laggy connection at the moment
| [Tuesday 21 December 2010] [10:59:36] <mikko>	sockets.size() > 0 would block, yes?
| [Tuesday 21 December 2010] [10:59:46] <sustrik>	yes
| [Tuesday 21 December 2010] [11:00:14] <mikko>	sozmq_term_nb woudl return EAGAIN if sockets.size() > 0
| [Tuesday 21 December 2010] [11:00:26] <sustrik>	aha
| [Tuesday 21 December 2010] [11:00:26] <mikko>	no need to migrate anything (?)
| [Tuesday 21 December 2010] [11:00:48] <sustrik>	i though you want zmq_term to close the sockets
| [Tuesday 21 December 2010] [11:01:28] <mikko>	im after info whether call to zmq_term will block
| [Tuesday 21 December 2010] [11:01:32] <mikko>	not to close sockets
| [Tuesday 21 December 2010] [11:01:52] <sustrik>	yes, that should be doable
| [Tuesday 21 December 2010] [11:02:09] <sustrik>	if you have a look atc ctx.cpp
| [Tuesday 21 December 2010] [11:02:14] <sustrik>	::terminate()
| [Tuesday 21 December 2010] [11:02:35] <mikko>	around line 118?
| [Tuesday 21 December 2010] [11:02:53] <sustrik>	the function begins at 107
| [Tuesday 21 December 2010] [11:03:05] <sustrik>	you have 2 waits there
| [Tuesday 21 December 2010] [11:03:25] <sustrik>	line 130:
| [Tuesday 21 December 2010] [11:03:27] <sustrik>	no_sockets_sync.wait ();
| [Tuesday 21 December 2010] [11:03:39] <sustrik>	and line 152:
| [Tuesday 21 December 2010] [11:03:41] <sustrik>	usleep (1000);
| [Tuesday 21 December 2010] [11:04:03] <sustrik>	the first wait waits for all sockets being closed (zmq_close)
| [Tuesday 21 December 2010] [11:04:12] <sustrik>	the second one wait for all pending data to be sent
| [Tuesday 21 December 2010] [11:04:21] <mikko>	ok
| [Tuesday 21 December 2010] [11:08:59] <cremes>	i like this EAGAIN idea for zmq_term()
| [Tuesday 21 December 2010] [11:27:36] <Skaag>	Hello!
| [Tuesday 21 December 2010] [11:27:40] <Skaag>	(again)
| [Tuesday 21 December 2010] [11:27:42] <mikko>	i
| [Tuesday 21 December 2010] [11:27:43] <mikko>	hi
| [Tuesday 21 December 2010] [11:27:47] <Skaag>	hi mikko :)
| [Tuesday 21 December 2010] [11:28:41] <Skaag>	we're about to perform a POC for ZMQ, and if all goes well, convert a system to ZMQ that uses RabbitMQ at the moment.
| [Tuesday 21 December 2010] [11:29:12] <Skaag>	but I wanted to ask, in general, about the theoretical potential of ZMQ to scale to thousands of servers...
| [Tuesday 21 December 2010] [11:29:43] <mikko>	Skaag: can you describe your specific use-case?
| [Tuesday 21 December 2010] [11:29:48] <mikko>	it would give some context
| [Tuesday 21 December 2010] [11:29:52] <Skaag>	And also how practical it is to use the multicast functionality - does it require special network equipment? is it IP Multicast? Or is it just a name really, and the multicast is just synonimous for sending the message at once to many hosts?
| [Tuesday 21 December 2010] [11:29:57] <Skaag>	sure!
| [Tuesday 21 December 2010] [11:30:07] <Skaag>	I have at the moment only 16 nodes, distributed around the world
| [Tuesday 21 December 2010] [11:30:22] <Skaag>	they send once per second a small block of data, statistical data about themselves
| [Tuesday 21 December 2010] [11:30:30] <Skaag>	less than 512 bytes
| [Tuesday 21 December 2010] [11:31:07] <Skaag>	so it's "all to all", and all of them need to collect this data, and produce historical graphs, etc.
| [Tuesday 21 December 2010] [11:31:23] <Skaag>	so i'm asking myself what will happen when this scales, to 1000 nodes
| [Tuesday 21 December 2010] [11:32:45] <mikko>	so every node needs to know about all others?
| [Tuesday 21 December 2010] [11:35:00] <cremes>	sounds like a perfect use-case for pub/sub with a forwarder device
| [Tuesday 21 December 2010] [11:35:38] <cremes>	Skaag: need more info; do you have particular latency requirements? how frequent is the data generated?
| [Tuesday 21 December 2010] [11:36:11] <mikko>	yeah, if latency is not a problem you could batch updates
| [Tuesday 21 December 2010] [11:36:16] <Skaag>	every 1 second, the nodes send to all other nodes a less than 512 byte data structure (json or binary, I don't mind)
| [Tuesday 21 December 2010] [11:36:35] <Skaag>	could also be every 5 seconds. still fine.
| [Tuesday 21 December 2010] [11:36:49] <Skaag>	but while the cluster is small, it would be cool to have fast updates.
| [Tuesday 21 December 2010] [11:36:58] <mikko>	sure
| [Tuesday 21 December 2010] [11:37:04] <mikko>	you could have quick local updates
| [Tuesday 21 December 2010] [11:37:10] <Skaag>	the latency between the nodes is a maximum of 100ms.
| [Tuesday 21 December 2010] [11:37:11] <mikko>	and batch the packets to remote locations
| [Tuesday 21 December 2010] [11:37:22] <Skaag>	there are at the moment 6 locations around the world
| [Tuesday 21 December 2010] [11:37:27] <Skaag>	with a bunch of machines in each location
| [Tuesday 21 December 2010] [11:37:30] <mikko>	update every second locally and send out every 5 seconds
| [Tuesday 21 December 2010] [11:37:48] <mikko>	so every five seconds you would send five updates to remote locations
| [Tuesday 21 December 2010] [11:37:50] <cremes>	multicast/pgm transport won't help you if this is over a public network (internet)
| [Tuesday 21 December 2010] [11:38:09] <Skaag>	ok so I was right to assume it is IP Multicast...
| [Tuesday 21 December 2010] [11:38:19] <Skaag>	and not some internal terminology
| [Tuesday 21 December 2010] [11:38:19] <mikko>	i would probably look into something like zookeeper for service discovery
| [Tuesday 21 December 2010] [11:38:33] <Skaag>	sounds interesting!
| [Tuesday 21 December 2010] [11:38:39] <mikko>	create ephimeral nodes of available endpoints
| [Tuesday 21 December 2010] [11:38:58] <mikko>	i used zookeeper ages ago for services discovery
| [Tuesday 21 December 2010] [11:39:18] <mikko>	wrote a small daemon called 'myservices' and each node on cluster had a configuration file of services it has
| [Tuesday 21 December 2010] [11:39:44] <mikko>	so as long as node was up the ephimeral node existed in zookeeper
| [Tuesday 21 December 2010] [11:39:58] <mikko>	when a node died the ephimeral node is automatically removed by zookeeper
| [Tuesday 21 December 2010] [11:40:08] <mikko>	allows 'automatic' graceful failure handling
| [Tuesday 21 December 2010] [11:40:53] <Skaag>	that's absolutely awesome
| [Tuesday 21 December 2010] [11:41:20] <mikko>	sadly the project never went live so i cant really tell how well it would've worked in production
| [Tuesday 21 December 2010] [11:44:00] <mikko>	im gonna go get some coffee
| [Tuesday 21 December 2010] [11:44:00] <mikko>	bbl
| [Tuesday 21 December 2010] [11:45:21] <ngerakines>	is there a list of large companies that use zmq on the site?
| [Tuesday 21 December 2010] [11:52:10] <Skaag>	mikko: Would love to take a look at your 'myservices' code ;)
| [Tuesday 21 December 2010] [11:54:19] <cremes>	ngerakines: i don't think so
| [Tuesday 21 December 2010] [11:54:26] <ngerakines>	cremes: ok, thanks
| [Tuesday 21 December 2010] [11:58:42] <sustrik>	Skaag: one thing to understand is that "all to all" model is inherently unscalable
| [Tuesday 21 December 2010] [11:59:12] <Skaag>	I thought about creating 'bubbles'
| [Tuesday 21 December 2010] [11:59:22] <Skaag>	so machines in the same DC would update quickly, internally
| [Tuesday 21 December 2010] [11:59:30] <sustrik>	at some point the number of nodes would be so high, that amount of messages will overload any receiver
| [Tuesday 21 December 2010] [11:59:37] <Skaag>	with less frequent updates being sent between such bubbles, aggregated
| [Tuesday 21 December 2010] [11:59:50] <sustrik>	yes, aggregation solves the problem
| [Tuesday 21 December 2010] [12:00:06] <Skaag>	we should probably do that from the start
| [Tuesday 21 December 2010] [12:00:26] <sustrik>	depends on the requirements
| [Tuesday 21 December 2010] [12:00:35] <sustrik>	it the goal is to have 1000 nodes
| [Tuesday 21 December 2010] [12:00:44] <sustrik>	with 1 msg per 5 secs
| [Tuesday 21 December 2010] [12:00:53] <sustrik>	you probably don't need it
| [Tuesday 21 December 2010] [12:13:49] <Skaag>	yes that's more or less the goal.
| [Tuesday 21 December 2010] [12:13:57] <Skaag>	it will take some time to get there, too...
| [Tuesday 21 December 2010] [12:14:04] <Skaag>	for now we have just 25 machines.
| [Tuesday 21 December 2010] [12:14:16] <Skaag>	I expect in 6 month it will maybe grow to 150.
| [Tuesday 21 December 2010] [12:14:50] <Skaag>	so there is time to ameliorate the system.
| [Tuesday 21 December 2010] [12:15:00] <Skaag>	uh, to improve the system.
| [Tuesday 21 December 2010] [12:15:11] <Skaag>	(I think maybe I used a french word?)
| [Tuesday 21 December 2010] [12:25:21] <mikko>	Skaag: what is this system doing?
| [Tuesday 21 December 2010] [12:25:32] <mikko>	what kinda of data are you pushing through?
| [Tuesday 21 December 2010] [12:25:37] <mikko>	just out of interest
| [Tuesday 21 December 2010] [12:28:12] <Skaag>	I can tell you exactly..!
| [Tuesday 21 December 2010] [12:28:18] <Skaag>	it is a bunch of media streamers
| [Tuesday 21 December 2010] [12:28:35] <Skaag>	the important information is cpu load, bandwidth usage, and number of connections
| [Tuesday 21 December 2010] [12:28:54] <Skaag>	and in the future, cost per traffic (actual cost, in dollars)
| [Tuesday 21 December 2010] [12:29:11] <Skaag>	or some combination of cost, and remaining quota
| [Tuesday 21 December 2010] [12:29:17] <Skaag>	but that's "phase 2" stuff :)
| [Tuesday 21 December 2010] [12:29:34] <Skaag>	and this will be used to make smart decisions about where to send new traffic
| [Tuesday 21 December 2010] [12:29:58] <Skaag>	and indirectly, will also be used to generate graphs for me and other admins, to view what's going on in the network
| [Tuesday 21 December 2010] [12:31:37] <mikko>	how do you do the routing on global level?
| [Tuesday 21 December 2010] [13:05:19] <Skaag>	Level3 fibers, connect all the DC's
| [Tuesday 21 December 2010] [13:06:43] <Skaag>	you can see our map here: http://bams.iptp.net/cacti/plugins/weathermap/output/weathermap_7.png
| [Tuesday 21 December 2010] [13:07:04] <Skaag>	right now, I am near m9.msk.ru :-)
| [Tuesday 21 December 2010] [13:07:15] <Skaag>	(physically speaking)
| [Tuesday 21 December 2010] [13:11:42] <Skaag>	and this means that this year, I will celebrate xmas in moscow  \o/  yey!
| [Wednesday 22 December 2010] [02:14:22] <ytang>	hi, anyone online?
| [Wednesday 22 December 2010] [02:33:39] <sustrik>	hi
| [Wednesday 22 December 2010] [02:38:47] <Steve-o>	good morning
| [Wednesday 22 December 2010] [03:05:04] <mindful>	anybody in
| [Wednesday 22 December 2010] [03:08:03] <sustrik>	yup
| [Wednesday 22 December 2010] [05:29:54] <mikko>	good morning
| [Wednesday 22 December 2010] [05:29:59] <mikko>	i made it 
| [Wednesday 22 December 2010] [05:39:12] <Skaag_>	made what?
| [Wednesday 22 December 2010] [05:39:16] <Skaag_>	to work? :)
| [Wednesday 22 December 2010] [07:29:42] <mikko>	Skaag: made it home for christmas
| [Wednesday 22 December 2010] [07:29:52] <mikko>	Skaag: i was flying from london to finland
| [Wednesday 22 December 2010] [07:30:09] <mikko>	took five days 
| [Wednesday 22 December 2010] [07:31:24] <Skaag>	wow!
| [Wednesday 22 December 2010] [07:31:27] <Skaag>	why 5 days?!
| [Wednesday 22 December 2010] [07:31:47] <Skaag>	I thought 5 days is with a ferry
| [Wednesday 22 December 2010] [07:31:55] <Skaag>	London to Stockholm, then Stockholm to Helsinki
| [Wednesday 22 December 2010] [07:32:18] <Skaag>	brb
| [Wednesday 22 December 2010] [07:34:20] <mikko>	Skaag: tons of canceled flights 
| [Wednesday 22 December 2010] [07:34:50] <mikko>	i was supposed to fly last friday and finally managed to fly tuesday evening
| [Wednesday 22 December 2010] [07:35:17] <Skaag>	sounds like a nightmare
| [Wednesday 22 December 2010] [07:40:10] <Skaag_>	back.
| [Wednesday 22 December 2010] [07:40:23] <Skaag>	I really should bring my bouncer into freenode as well...
| [Wednesday 22 December 2010] [10:55:02] <dos000>	howdy
| [Wednesday 22 December 2010] [10:55:56] <dos000>	can someone tell me if concurrent lock free circular buffers are used in zmq ? i read something recently that was talking about the perf improvements
| [Wednesday 22 December 2010] [11:43:20] <cremes>	dos000: 0mq definitely uses lock-free algos; i don't know if they protect a circular buffer though
| [Wednesday 22 December 2010] [11:43:34] <cremes>	the code answers all!
| [Wednesday 22 December 2010] [11:43:37] <Skaag>	lol
| [Wednesday 22 December 2010] [11:43:51] <Skaag>	*snicker* typical developer answer ;)
| [Wednesday 22 December 2010] [11:44:04] <Skaag>	what documentation? look at the comments in the code... ;)
| [Wednesday 22 December 2010] [11:44:09] <cremes>	yep ;)
| [Wednesday 22 December 2010] [11:45:18] <cremes>	docs usually don't cover those kinds of implementation details anyway
| [Wednesday 22 December 2010] [11:45:40] <cremes>	they are intended to remain hidden under the covers; anyone using the api shouldn't care what the algo is
| [Wednesday 22 December 2010] [11:46:12] <cremes>	since dos000 was asking specifically about it, the only way to get the real answer is to 1) ask sustrik
| [Wednesday 22 December 2010] [11:46:16] <cremes>	or 2) check the source
| [Wednesday 22 December 2010] [11:46:44] <dos000>	ah!
| [Wednesday 22 December 2010] [11:48:19] <dos000>	i was also looking for some experience in other libs offering lock-free circular buffers
| [Wednesday 22 December 2010] [11:48:32] <dos000>	this stuff seems like black magic 
| [Wednesday 22 December 2010] [11:48:55] <cremes>	yes, very dark :)
| [Wednesday 22 December 2010] [11:49:05] <dos000>	no one is doing it or talking about their implementation 
| [Wednesday 22 December 2010] [11:49:25] <dos000>	and no central de facto to go fo this .. evryone rolls their own
| [Wednesday 22 December 2010] [11:49:33] <cremes>	true
| [Wednesday 22 December 2010] [11:49:53] <cremes>	the main idea behind lock-free is to leverage a platform's atomic compare-and-swap operation
| [Wednesday 22 December 2010] [11:50:12] <cremes>	if your hw supports that, a lock-free impl is fairly "easy" to create
| [Wednesday 22 December 2010] [11:50:17] <dos000>	yes .. and i am hoping (please) support it
| [Wednesday 22 December 2010] [11:50:31] <cremes>	the hard part then becomes dealing with cache coherency and its perf implications
| [Wednesday 22 December 2010] [11:50:49] <dos000>	i am hoping 0mq has it for sparc and x86 and/or x86_64
| [Wednesday 22 December 2010] [11:51:08] <cremes>	it definitely has it for x86 and x86_64; not sure on sparc
| [Wednesday 22 December 2010] [11:51:45] <dos000>	cremes: zmq does not deal with threads correct ? i was thinking a way of "forcing" a thread to run on a particular core
| [Wednesday 22 December 2010] [11:52:19] <cremes>	dos000: not correct; you can force cpu affinity for sockets
| [Wednesday 22 December 2010] [11:52:28] <cremes>	check the setsockopt docs on the web site
| [Wednesday 22 December 2010] [11:52:38] <dos000>	ok
| [Wednesday 22 December 2010] [11:52:40] <cremes>	(i haven't used it myself otherwise i'd be more helpful...)
| [Wednesday 22 December 2010] [11:52:56] <dos000>	here is the (interesting) talk http://www.infoq.com/presentations/LMAX
| [Wednesday 22 December 2010] [11:53:15] <cremes>	ah, i just saw that this morning! it's in my queue to watch a bit later
| [Wednesday 22 December 2010] [11:53:30] <dos000>	ah!
| [Wednesday 22 December 2010] [11:53:31] <cremes>	i do trading stuff but i'm not in the super high-freq space
| [Wednesday 22 December 2010] [11:54:35] <dos000>	they mention someway of sending a packet straight to user space bypassing (virtually) the kernel ... but they dont explain how or which os supports it
| [Wednesday 22 December 2010] [11:55:09] <dos000>	very interestng talk indeed
| [Wednesday 22 December 2010] [11:55:52] <dos000>	cremes, which blog/sites do you follow for this types of talks ?
| [Wednesday 22 December 2010] [11:56:08] <dos000>	how did you stumble on the LMAX presentation ?
| [Wednesday 22 December 2010] [11:56:26] <cremes>	i subscribe to reddit rss feeds as well as the infoq rss stuff
| [Wednesday 22 December 2010] [11:58:10] <dos000>	the solution they propose starts from 36:00 if you want to skip through .. a picture is worth a thousand words
| [Wednesday 22 December 2010] [11:58:28] <cremes>	cool, thanks for the heads up
| [Wednesday 22 December 2010] [11:58:37] <cremes>	are you involved with trading systems or similar?
| [Wednesday 22 December 2010] [11:58:55] <dos000>	yes very similar .. payment systems
| [Wednesday 22 December 2010] [11:59:53] <Skaag>	dos000: don't the boost libraries do this type of locking?
| [Wednesday 22 December 2010] [12:00:54] <dos000>	i asked already in #C++ it might be only circular buffers .. not lock free implementations
| [Wednesday 22 December 2010] [12:01:40] <Skaag>	weren't all such kernel modules that broke the core -> user space membrane been kicked from the kernel project by Linus?
| [Wednesday 22 December 2010] [12:02:03] <dos000>	no idea!
| [Wednesday 22 December 2010] [12:02:10] <Skaag>	they are doing this without a custom kernel module?
| [Wednesday 22 December 2010] [12:02:25] <dos000>	not sure how .. its just a blimp in the video
| [Wednesday 22 December 2010] [12:40:07] <dos000>	ok ... now i found this http://www.puppetmastertrading.com/blog/2010/02/16/lock-free/
| [Wednesday 22 December 2010] [12:52:10] <mikko>	dos000: http://www.zeromq.org/blog:multithreading-magic
| [Wednesday 22 December 2010] [12:52:15] <mikko>	this might be interesting read as well
| [Wednesday 22 December 2010] [12:52:20] <mikko>	not directly related
| [Wednesday 22 December 2010] [12:58:59] <dos000>	fastflow seems to be up there with 0mq .. lots of similarities
| [Wednesday 22 December 2010] [13:03:57] <cremes>	dos000: they diss ruby in that blog so now i need to go on a rant! ;)
| [Wednesday 22 December 2010] [13:08:18] <Skaag>	lol!!!
| [Wednesday 22 December 2010] [13:08:37] <dos000>	lol
| [Wednesday 22 December 2010] [15:11:03] <Skaag>	the developer I work with tells me he managed to publish and consume a message on a topic with rabbitmq, but it's still unclear to him how to cluster the thing ;)
| [Wednesday 22 December 2010] [16:41:57] <mikko>	Skaag: you can publish and consume a message with zeromq within minutes 
| [Wednesday 22 December 2010] [16:41:58] <mikko>	:)
| [Wednesday 22 December 2010] [16:42:06] <Skaag>	I know
| [Wednesday 22 December 2010] [16:42:33] <Skaag>	anyway, what I am thinking to answer him, is that Zookeeper will be in charge of managing a list of IP addresses of available hosts
| [Wednesday 22 December 2010] [16:42:50] <Skaag>	and he will just connect to all of them and subscribe
| [Wednesday 22 December 2010] [16:43:07] <mikko>	did you test zookeeper
| [Wednesday 22 December 2010] [16:43:09] <mikko>	?
| [Wednesday 22 December 2010] [16:43:21] <Skaag>	not yet
| [Wednesday 22 December 2010] [16:43:25] <Skaag>	I'm installing it as we speak
| [Wednesday 22 December 2010] [16:44:07] <mikko>	the only annoyance i found was that zookeeper didnt have rhel packaging
| [Wednesday 22 December 2010] [16:44:12] <mikko>	i think i made spec-files back then
| [Wednesday 22 December 2010] [16:45:13] <Skaag>	well I am running on Ubuntu myself. I can't stand rhel.
| [Wednesday 22 December 2010] [16:45:31] <Skaag>	I used to be very redhat oriented
| [Wednesday 22 December 2010] [16:45:54] <Skaag>	but once I was exposed to debian, and then to ubuntu, I knew my destiny was sealed ;)
| [Wednesday 22 December 2010] [16:46:12] <mikko>	i use debian on my own stuff
| [Wednesday 22 December 2010] [16:46:16] <Skaag>	I know it may sound stupid, and rhel is considered a kind of 'standard'.
| [Wednesday 22 December 2010] [16:46:23] <mikko>	but many companies i work with prefer rhel
| [Wednesday 22 December 2010] [16:46:52] <dos000>	i hate rhel .. anything non debian (based) for that matter
| [Wednesday 22 December 2010] [16:47:13] <dos000>	apt-get is sweet
| [Wednesday 22 December 2010] [16:47:14] <mikko>	rhel packaging is far more pleasant to make imho
| [Wednesday 22 December 2010] [16:47:20] <mikko>	compared to debs
| [Wednesday 22 December 2010] [16:47:31] <Skaag>	i disagree
| [Wednesday 22 December 2010] [16:47:33] <dos000>	to use however isa different thing
| [Wednesday 22 December 2010] [16:47:37] <Skaag>	I make a deb in 3 minutes.
| [Wednesday 22 December 2010] [16:47:47] <Skaag>	less...
| [Wednesday 22 December 2010] [16:48:05] <Skaag>	well I have a ready skeleton, from the first 5 minutes I spent trying to make a deb
| [Wednesday 22 December 2010] [16:48:17] <dos000>	there are some utilities that will create the pkgs for you .. based on make && make installl
| [Wednesday 22 December 2010] [16:48:31] <Skaag>	so now to make a deb is a matter of copying the files to the right places, specifying dependencies, and perhaps adding some install / uninstall scripts...
| [Wednesday 22 December 2010] [16:48:53] <Skaag>	not to mention how easy it is to create a repository
| [Wednesday 22 December 2010] [16:49:12] <mikko>	Skaag: it's easy for yum as well
| [Wednesday 22 December 2010] [16:49:18] <mikko>	createrepo /path/to
| [Wednesday 22 December 2010] [16:49:45] <dos000>	i did not find companies that do support for debian so far 
| [Wednesday 22 December 2010] [16:50:04] <dos000>	something that passes the CEO test
| [Wednesday 22 December 2010] [16:51:13] <Skaag>	the CEO test is different in every company...
| [Wednesday 22 December 2010] [16:51:16] <Skaag>	in some, the money talks
| [Wednesday 22 December 2010] [16:51:29] <Skaag>	in some others, it's how large the support company is
| [Wednesday 22 December 2010] [16:51:38] <Skaag>	and in some, it's how technically knowledgable :-)
| [Wednesday 22 December 2010] [16:51:41] <dos000>	in some companies the CEO (and evryone around him) is dumb !
| [Wednesday 22 December 2010] [16:51:52] <dos000>	thats the problem
| [Wednesday 22 December 2010] [16:51:55] <Skaag>	and here in Russia! It's about how much money you slip into the CEO's pocket, behind the back of the board of directors...! ;-)
| [Wednesday 22 December 2010] [16:52:07] <dos000>	heh!
| [Wednesday 22 December 2010] [16:53:06] <mikko>	im not far from russia atm
| [Wednesday 22 December 2010] [16:53:13] <mikko>	a few hundred km if even that
| [Wednesday 22 December 2010] [16:54:01] <mikko>	Skaag: https://github.com/mkoppanen/myservices
| [Wednesday 22 December 2010] [16:54:15] <mikko>	it's not very well tested but should give some ideas for zk integration
| [Wednesday 22 December 2010] [16:54:21] <Skaag>	mikko: I read your page already ;)
| [Wednesday 22 December 2010] [16:54:52] <Skaag>	ah, that's another page
| [Wednesday 22 December 2010] [16:54:54] <Skaag>	sorry
| [Wednesday 22 December 2010] [16:54:58] <Skaag>	Where in Finland are you?
| [Wednesday 22 December 2010] [16:55:46] <Skaag>	I took the bus from Helsinki to St. Petersburg, just 6 month ago :-)
| [Wednesday 22 December 2010] [16:55:54] <Skaag>	17 euros and I was in Russia!
| [Wednesday 22 December 2010] [16:56:03] <mikko>	they got a new fast train as well
| [Wednesday 22 December 2010] [16:56:12] <mikko>	three hours to st petersburg from helsinki
| [Wednesday 22 December 2010] [16:56:27] <Skaag>	amazing
| [Wednesday 22 December 2010] [16:56:31] <dos000>	lets say i had 3 packets coming from 3 different sources ... and all packets are sequentially numbered. 
| [Wednesday 22 December 2010] [16:56:38] <Skaag>	but I doubt in such a weather condition?
| [Wednesday 22 December 2010] [16:57:01] <dos000>	what would you do to wait for three packets with the same seq numbers ?
| [Wednesday 22 December 2010] [16:57:06] <mikko>	Skaag: even in such conditions
| [Wednesday 22 December 2010] [16:57:11] <Skaag>	amazing!
| [Wednesday 22 December 2010] [16:57:12] <mikko>	things dont stop in .fi even when its cold
| [Wednesday 22 December 2010] [16:57:20] <Skaag>	I know
| [Wednesday 22 December 2010] [16:57:25] <Skaag>	but on the russian side...?
| [Wednesday 22 December 2010] [16:57:26] <Skaag>	:-)
| [Wednesday 22 December 2010] [16:57:35] <Skaag>	I lived in Helsinki for 5 month
| [Wednesday 22 December 2010] [16:57:45] <Skaag>	I absolutely love Finland
| [Wednesday 22 December 2010] [16:57:52] <Skaag>	awesome country.
| [Wednesday 22 December 2010] [16:57:58] <Skaag>	I loved it since childhood.
| [Wednesday 22 December 2010] [16:58:10] <Skaag>	and recently, after living there, I understood why.
| [Wednesday 22 December 2010] [16:58:56] <mikko>	i dislike the winter. thats why i moved to london
| [Wednesday 22 December 2010] [16:59:19] <Skaag>	maybe because you grew up with it.
| [Wednesday 22 December 2010] [16:59:50] <Skaag>	this is my second REAL winter here in Moscow, first time in Helsinki, where it was almost constantly under -10c
| [Wednesday 22 December 2010] [16:59:58] <Skaag>	and I don't mind it much.
| [Wednesday 22 December 2010] [17:01:07] <mikko>	im in middle .fi now
| [Wednesday 22 December 2010] [17:01:14] <mikko>	-30 outside
| [Wednesday 22 December 2010] [17:02:31] <mikko>	does your company operate in russia?
| [Wednesday 22 December 2010] [17:03:00] <Skaag>	yes
| [Wednesday 22 December 2010] [17:03:03] <Skaag>	among other places
| [Wednesday 22 December 2010] [17:03:27] <Skaag>	middle = near Sodankyl?
| [Wednesday 22 December 2010] [17:03:52] <mikko>	thats the northest place in finland
| [Wednesday 22 December 2010] [17:04:04] <mikko>	close to the sea up north
| [Wednesday 22 December 2010] [17:04:52] <mikko>	pretty close to Jyvskyl
| [Wednesday 22 December 2010] [17:05:03] <Skaag>	cool
| [Wednesday 22 December 2010] [17:05:41] <Skaag>	I have a good friend in Mikkeli
| [Wednesday 22 December 2010] [17:07:10] <Skaag>	I actually passed through Jyvskyl one time
| [Wednesday 22 December 2010] [17:09:44] <Skaag>	they just prepared Olutglgi
| [Wednesday 22 December 2010] [17:09:54] <Skaag>	http://mika.letonsaari.net/foobar/olutglgi/14.jpg
| [Wednesday 22 December 2010] [17:10:11] <Skaag>	some part of me is glad I can not taste it.
| [Wednesday 22 December 2010] [17:11:31] <mikko>	warm beer and spices?
| [Wednesday 22 December 2010] [17:11:57] <Skaag>	actually it looks interesting
| [Wednesday 22 December 2010] [17:13:15] <Skaag>	yes
| [Wednesday 22 December 2010] [17:59:27] <ryandmonk>	hello... curious if someone can help me out with at pyzmq issue
| [Wednesday 22 December 2010] [17:59:52] <ryandmonk>	i followed the instructions on site
| [Wednesday 22 December 2010] [17:59:56] <ryandmonk>	and ran python setup.py install
| [Wednesday 22 December 2010] [18:00:32] <ryandmonk>	its spits out some stuff.. but eventually gives an error saying "zmq/core/constants.c:1: error: #error Do not use this file, it is the result of a failed Cython compilation."
| [Wednesday 22 December 2010] [18:01:29] <ryandmonk>	im on ubuntu 10.10.. using zeromq-2.0.10
| [Wednesday 22 December 2010] [18:10:56] <cremes>	ryandmonk: try searching the ML archives; i have seen discussions on python binding problems there before
| [Wednesday 22 December 2010] [18:11:03] <cremes>	perhaps the solution is buried in the archives
| [Wednesday 22 December 2010] [18:12:44] <ryandmonk>	where are these archives?
| [Wednesday 22 December 2010] [18:13:15] <Skaag>	cool - I have a working 16 node zookeeper cluster :)
| [Wednesday 22 December 2010] [18:18:57] <ryandmonk>	found em.. thanks cremes!
| [Wednesday 22 December 2010] [20:26:13] <dos000>	how does the network/tcp driver deliver packets for the same flow when a new packet arrives ? does it look up a hash tree to find the correct app listening on that socket ?
| [Wednesday 22 December 2010] [20:26:36] <dos000>	i have to do kinda same thing ... and zmq does also
| [Wednesday 22 December 2010] [20:47:01] <Steve-o>	morning all
| [Wednesday 22 December 2010] [21:15:03] <Skaag>	morning Steve-o 
| [Wednesday 22 December 2010] [23:45:20] <NoobFukaire>	I'm trying to test out the hello world stuff for C++ and zeromq
| [Wednesday 22 December 2010] [23:45:37] <NoobFukaire>	the server binds and I can see it's there with netstat (and I can telnet into it)
| [Wednesday 22 December 2010] [23:45:46] <NoobFukaire>	but when I connect with the client, I get Assertion failed: fetched (rep.cpp:232)
| [Wednesday 22 December 2010] [23:46:26] <NoobFukaire>	which is:
| [Wednesday 22 December 2010] [23:46:27] <NoobFukaire>	            //  Get next part of the message.
| [Wednesday 22 December 2010] [23:46:28] <NoobFukaire>	            bool fetched = in_pipes [current]->read (msg_);
| [Wednesday 22 December 2010] [23:46:28] <NoobFukaire>	            zmq_assert (fetched);
| [Wednesday 22 December 2010] [23:46:43] <NoobFukaire>	I'm not sure whats up with this lib?
| [Wednesday 22 December 2010] [23:49:55] <NoobFukaire>	http://pastebin.com/piwK7gxL
| [Wednesday 22 December 2010] [23:49:59] <NoobFukaire>	the stack trace
| [Wednesday 22 December 2010] [23:54:06] <NoobFukaire>	https://github.com/imatix/zguide/blob/master/examples/C++/hwserver.cpp
| [Wednesday 22 December 2010] [23:54:11] <NoobFukaire>	https://github.com/imatix/zguide/blob/master/examples/C++/hwclient.cpp
| [Wednesday 22 December 2010] [23:54:13] <NoobFukaire>	that's the code
| [Thursday 23 December 2010] [00:07:48] <NoobFukaire>	okay nm, it had to do with some of my build paths
| [Thursday 23 December 2010] [01:55:03] <andrewvc>	cremes: you around?
| [Thursday 23 December 2010] [02:59:33] <sustrik>	hi mikko!
| [Thursday 23 December 2010] [03:16:20] <mikko>	sustrik: hi
| [Thursday 23 December 2010] [03:16:27] <sustrik>	morning
| [Thursday 23 December 2010] [03:16:41] <sustrik>	there's a build patch from steve in the ML
| [Thursday 23 December 2010] [03:16:51] <sustrik>	can i apply it?
| [Thursday 23 December 2010] [03:16:52] <mikko>	steve-o?
| [Thursday 23 December 2010] [03:16:56] <sustrik>	yes
| [Thursday 23 December 2010] [03:17:16] <mikko>	i'll review today if thats ok
| [Thursday 23 December 2010] [03:17:23] <sustrik>	sure, no haste
| [Thursday 23 December 2010] [03:17:31] <mikko>	i would like to change the way we build openpgm
| [Thursday 23 December 2010] [03:17:44] <sustrik>	what's the idea?
| [Thursday 23 December 2010] [03:17:48] <mikko>	it seems that we are duplicating a lot of work at the moment
| [Thursday 23 December 2010] [03:17:53] <mikko>	somehow that doesn't feel right
| [Thursday 23 December 2010] [03:17:59] <sustrik>	yes, we are
| [Thursday 23 December 2010] [03:18:12] <sustrik>	the alternative was to use scons
| [Thursday 23 December 2010] [03:18:40] <sustrik>	which create additional dependencies
| [Thursday 23 December 2010] [03:18:50] <sustrik>	any better idea?
| [Thursday 23 December 2010] [03:19:02] <mikko>	i was thinking about two options:
| [Thursday 23 December 2010] [03:19:06] <mikko>	a) invoke scons
| [Thursday 23 December 2010] [03:19:14] <mikko>	b) isolate openpgm flags to their own files
| [Thursday 23 December 2010] [03:19:47] <sustrik>	a) IMO is just shifting work from 0mq maintainers to 0mq users
| [Thursday 23 December 2010] [03:19:52] <mikko>	i think that having large amount of conditionals in the Makefile.am isn't maintainable in the long run. also makes patching harder
| [Thursday 23 December 2010] [03:20:19] <sustrik>	yes, agreed
| [Thursday 23 December 2010] [03:20:32] <sustrik>	would b) help with that?
| [Thursday 23 December 2010] [03:20:36] <mikko>	yes
| [Thursday 23 December 2010] [03:20:52] <mikko>	we would have something like foreign/Makefile.linux.am
| [Thursday 23 December 2010] [03:21:04] <mikko>	and include from configure.in based on OS/compiler
| [Thursday 23 December 2010] [03:21:14] <sustrik>	i see
| [Thursday 23 December 2010] [03:21:20] <mikko>	not sure if that works yet but ill try today
| [Thursday 23 December 2010] [03:21:26] <sustrik>	ok
| [Thursday 23 December 2010] [03:21:36] <mikko>	that way we could track openpgm build changes more easily
| [Thursday 23 December 2010] [03:21:56] <sustrik>	ack
| [Thursday 23 December 2010] [03:23:10] <mikko>	also, we should add support for solaris / freebsd with openpgm and the other steve is working on os x build
| [Thursday 23 December 2010] [03:23:20] <mikko>	so that's 5 conditionals in Makefile
| [Thursday 23 December 2010] [03:24:35] <sustrik>	sounds messy
| [Thursday 23 December 2010] [03:25:00] <mikko>	yeah, that was originally why i wanted to investigate invoking scons
| [Thursday 23 December 2010] [03:25:15] <mikko>	as steve has done a lot of work with different platforms / compilers to get the build working
| [Thursday 23 December 2010] [11:55:37] <NoobFukaire>	whats the best way to implement bidirectional messaging with zeromq?
| [Thursday 23 December 2010] [11:56:14] <NoobFukaire>	two REQ-REP sockets?
| [Thursday 23 December 2010] [11:56:45] <NoobFukaire>	I need either client to be able to send and receive messages at any point
| [Thursday 23 December 2010] [12:10:44] <sustrik>	what are you trying to do?
| [Thursday 23 December 2010] [12:11:17] <NoobFukaire>	I have two processes that need to exchange event information
| [Thursday 23 December 2010] [12:11:39] <NoobFukaire>	those events can be created at any time, on either end
| [Thursday 23 December 2010] [12:12:08] <NoobFukaire>	I wish there was some non blocking way to process inbound messages
| [Thursday 23 December 2010] [12:12:13] <NoobFukaire>	with zeromq
| [Thursday 23 December 2010] [12:16:26] <sustrik>	is that some kind of "multicast bus" scenario?
| [Thursday 23 December 2010] [12:16:42] <sustrik>	i.e. any message published by anyone is received by anyone else?
| [Thursday 23 December 2010] [12:17:05] <NoobFukaire>	no, it's basically client server
| [Thursday 23 December 2010] [12:17:18] <NoobFukaire>	right now it's 1:1 but there might be multiple clients in the future
| [Thursday 23 December 2010] [12:17:28] <NoobFukaire>	I'm find with 1:1 for now though
| [Thursday 23 December 2010] [12:17:29] <sustrik>	so it's 1 server and N clients
| [Thursday 23 December 2010] [12:17:50] <NoobFukaire>	*fine
| [Thursday 23 December 2010] [12:18:11] <NoobFukaire>	I'll refactor for multiple clients when the time comes and I know zeromq better ;)
| [Thursday 23 December 2010] [12:18:18] <sustrik>	what kind of interactions there are between server & client?
| [Thursday 23 December 2010] [12:18:32] <sustrik>	server publishing stream of events to be received by each client?
| [Thursday 23 December 2010] [12:18:34] <NoobFukaire>	I'm sending google protobuf messages back and forth
| [Thursday 23 December 2010] [12:19:05] <sustrik>	back & forth = client initiated handshake?
| [Thursday 23 December 2010] [12:19:07] <NoobFukaire>	they're just "events" they can be generated asynchronously by either side
| [Thursday 23 December 2010] [12:19:51] <sustrik>	0mq doesn't work that way, you have to identify patterns in the communications
| [Thursday 23 December 2010] [12:19:54] <sustrik>	handshakes
| [Thursday 23 December 2010] [12:20:02] <sustrik>	data distribution
| [Thursday 23 December 2010] [12:20:05] <sustrik>	load balancing
| [Thursday 23 December 2010] [12:20:07] <sustrik>	and similar
| [Thursday 23 December 2010] [12:20:14] <NoobFukaire>	okay I don't care about any of that
| [Thursday 23 December 2010] [12:20:24] <NoobFukaire>	this is about two process that exist on the same machine
| [Thursday 23 December 2010] [12:20:27] <NoobFukaire>	and need to communicate
| [Thursday 23 December 2010] [12:20:33] <sustrik>	use TCP then
| [Thursday 23 December 2010] [12:20:34] <NoobFukaire>	there will never be a performance issue
| [Thursday 23 December 2010] [12:20:42] <NoobFukaire>	gagh
| [Thursday 23 December 2010] [12:21:22] <sustrik>	well, 0mq needs to know what you are trying to achieve to help you
| [Thursday 23 December 2010] [12:21:25] <spht>	NoobFukaire:  Just because you're scenario is 1:1 doesn't mean a 1:N solution doesn't fit
| [Thursday 23 December 2010] [12:21:34] <spht>	s/you're/your
| [Thursday 23 December 2010] [12:21:34] <sustrik>	just saying "anything" doesn't work
| [Thursday 23 December 2010] [12:21:52] <NoobFukaire>	that's true but I'm just trying to keep things as simple as possible until I'm more familiar with zeromq
| [Thursday 23 December 2010] [12:22:34] <sustrik>	you can use PAIR socket
| [Thursday 23 December 2010] [12:22:39] <sustrik>	it's strictly 1:1
| [Thursday 23 December 2010] [12:22:55] <sustrik>	but there are some features missing, like auto-reconnection etc.
| [Thursday 23 December 2010] [12:23:55] <NoobFukaire>	spht: is there no way to check read zeromq input in a non blocking fashion?
| [Thursday 23 December 2010] [12:24:10] <NoobFukaire>	I have a function that gets called at a regular interval
| [Thursday 23 December 2010] [12:24:24] <NoobFukaire>	ideally, I'd like to have that check for input, process it and then process outbound messages
| [Thursday 23 December 2010] [12:24:24] <sustrik>	use ZMQ_NOBLOCK flag in recv()
| [Thursday 23 December 2010] [12:24:25] <spht>	NoobFukaire:   you can setup zeromq non-blocking IIRC, 
| [Thursday 23 December 2010] [12:24:54] <spht>	what sustrik said ;)
| [Thursday 23 December 2010] [12:24:58] <NoobFukaire>	right now it's blocking, so once recv is called, it blocks until input is returned
| [Thursday 23 December 2010] [12:25:02] <NoobFukaire>	what did he say
| [Thursday 23 December 2010] [12:25:33] <spht>	ZMQ_NOBLOCK
| [Thursday 23 December 2010] [12:25:55] <NoobFukaire>	thanks
| [Thursday 23 December 2010] [12:26:38] <spht>	but if your app is event driven to start with maybe you want to hook up the zeromq fd's into your runloop/reactor or what you use
| [Thursday 23 December 2010] [12:26:55] <spht>	sustrik:  IIRC thats possible, right?
| [Thursday 23 December 2010] [12:27:16] <spht>	I'm a newbie myself so I hope I'm not spreading lies ;)
| [Thursday 23 December 2010] [12:29:29] <NoobFukaire>	in my case, latency is very important and networking is not required at all
| [Thursday 23 December 2010] [12:29:40] <NoobFukaire>	because these events may have UI functionality executed as a result
| [Thursday 23 December 2010] [12:33:33] <sustrik>	spht: yes, it's possible
| [Thursday 23 December 2010] [12:34:25] <sustrik>	VoobFukaire: for best latency you can collacate the sender and receiver in the same process
| [Thursday 23 December 2010] [12:34:32] <sustrik>	each running is a different thread
| [Thursday 23 December 2010] [12:35:13] <spht>	And for low latency you probably do not want to poll for new messages (as I guess was what you wanted with the non-blocking sockets)
| [Thursday 23 December 2010] [12:52:20] <NoobFukaire>	I need to keep the UI responses ideally under ~100ms to eliminate any lag for the end user
| [Thursday 23 December 2010] [12:52:45] <NoobFukaire>	granted the UI stuff itself is done in the toolkit's thread, so these events are more of a "trigger" for those
| [Thursday 23 December 2010] [12:53:08] <NoobFukaire>	thank you for your help and suggestions
| [Thursday 23 December 2010] [12:54:59] <NoobFukaire>	ZMQ_NOBLOCK seems to do what I want with nonblocking io, thank you sustrik 
| [Thursday 23 December 2010] [12:57:46] <sustrik>	you are welcome
| [Thursday 23 December 2010] [13:58:55] <mikko>	sustrik: why doesn't pair auto-reconnect?
| [Thursday 23 December 2010] [13:59:10] <sustrik>	nobody implemented it :)
| [Thursday 23 December 2010] [13:59:21] <mikko>	is that a hint ?
| [Thursday 23 December 2010] [13:59:23] <mikko>	:)
| [Thursday 23 December 2010] [13:59:26] <sustrik>	:)
| [Thursday 23 December 2010] [13:59:35] <mikko>	drove 800km today
| [Thursday 23 December 2010] [13:59:36] <sustrik>	well, the thing is that PAIR is a socket type
| [Thursday 23 December 2010] [13:59:45] <sustrik>	that is most prone to misuse
| [Thursday 23 December 2010] [14:00:00] <sustrik>	so i quite like it being slightly broken
| [Thursday 23 December 2010] [14:00:10] <mikko>	i abuse pair heavily in my program
| [Thursday 23 December 2010] [14:00:15] <sustrik>	:)
| [Thursday 23 December 2010] [14:00:23] <sustrik>	where have you gone?
| [Thursday 23 December 2010] [14:00:28] <mikko>	dark place
| [Thursday 23 December 2010] [14:00:32] <sustrik>	finland?
| [Thursday 23 December 2010] [14:00:34] <mikko>	yeah
| [Thursday 23 December 2010] [14:01:06] <sustrik>	800km, than must be somewhere behing polar cirscle
| [Thursday 23 December 2010] [14:01:08] <sustrik>	circle
| [Thursday 23 December 2010] [14:01:16] <mikko>	drove to helsinki and back
| [Thursday 23 December 2010] [14:01:28] <mikko>	just to find out that my friend's flight is so late that we drove back
| [Thursday 23 December 2010] [14:01:38] <sustrik>	:|
| [Thursday 23 December 2010] [14:01:52] <mikko>	now he might even miss the last bus 
| [Thursday 23 December 2010] [14:02:27] <sustrik>	what's exactly the problem with flights?
| [Thursday 23 December 2010] [14:02:31] <sustrik>	too cold or what?
| [Thursday 23 December 2010] [14:03:42] <mikko>	he is flying from london heathrow
| [Thursday 23 December 2010] [14:03:49] <mikko>	the problem at heathrow is incompetence
| [Thursday 23 December 2010] [14:03:57] <sustrik>	i guess so
| [Thursday 23 December 2010] [14:04:14] <mikko>	it's not -29.5 celsius where i am
| [Thursday 23 December 2010] [14:04:27] <mikko>	and all airports open
| [Thursday 23 December 2010] [14:04:39] <sustrik>	actually, it's nice warm here in Bratislava today
| [Thursday 23 December 2010] [14:05:01] <sustrik>	temperature went up by 20 degress or so
| [Thursday 23 December 2010] [14:05:41] <sustrik>	btw, i'm messing with linux kernel
| [Thursday 23 December 2010] [14:06:45] <sustrik>	the experience so far is that in comparison 0MQ codebase is pretty sane and well documented
| [Thursday 23 December 2010] [14:07:46] <mikko>	heheh
| [Thursday 23 December 2010] [14:07:50] <mikko>	im not suprised
| [Thursday 23 December 2010] [14:08:19] <sustrik>	well, it's an old project so some amount of messiness is expected
| [Thursday 23 December 2010] [14:08:38] <sustrik>	but the network stack seems to have no comments at all
| [Thursday 23 December 2010] [14:08:42] <sustrik>	:(
| [Thursday 23 December 2010] [14:19:43] <mikko>	dark arts
| [Thursday 23 December 2010] [17:06:28] <andrewvc>	cremes: you around?
| [Thursday 23 December 2010] [20:25:43] Notice	-NickServ- travlr_ is not a registered nickname.
| [Thursday 23 December 2010] [21:26:56] <justanewbie>	Hi,i've installed the zeromq,but i cannot find a executable named zmq_server,just zmq_queue,zmq_streamer,zmq_forward,why?
| [Thursday 23 December 2010] [21:27:51] <justanewbie>	i wanted to know how to write config file of zmq_queue,but don't know how
| [Thursday 23 December 2010] [21:32:18] <mikko>	justanewbie: what are you trying to achieve?
| [Thursday 23 December 2010] [21:32:24] <mikko>	justanewbie: just run a device?
| [Thursday 23 December 2010] [21:32:58] <mikko>	i don't think the device configuration files are documented at the moment 
| [Thursday 23 December 2010] [21:33:13] <mikko>	it should be fairly easy to decipher the config from the code
| [Thursday 23 December 2010] [21:33:51] <mikko>	https://github.com/zeromq/zeromq2/blob/master/devices/zmq_streamer/zmq_streamer.cpp
| [Thursday 23 December 2010] [21:33:54] <mikko>	for exampe that
| [Thursday 23 December 2010] [21:35:25] <justanewbie>	thank u mikko,i'll take a look and c
| [Thursday 23 December 2010] [23:51:06] <neopallium>	Hey everyone, I just wanted to let you know about this https://github.com/Neopallium/lua-handlers lua project that I created it wraps lua-ev(event loop) & lua-zmq(requires ZeroMQ 2.1.0).  It makes it easy to work with many zmq/tcp/udp sockets in non-blocking mode.
| [Friday 24 December 2010] [02:37:58] <sustrik>	naopallium: announce it on the mailing list rather, there's much more people there
| [Friday 24 December 2010] [04:44:51] <cods>	Hi. Just to make sure I understand: for any type of 1-1 connection (push/pull, pub/sub, req/rep), it doesn't matter which side do a connect and which one do the bind, right? (of course, differences occurs when talking about 1-n or n-n)
| [Friday 24 December 2010] [05:00:31] <seb`>	afaik yes it does not matter
| [Friday 24 December 2010] [05:03:28] <cods>	ok
| [Friday 24 December 2010] [05:07:53] <neopallium>	cods: from what I know it doesn't even matter with 1-n or n-n connections.
| [Friday 24 December 2010] [05:11:01] <cods>	neopallium: well, I meant that when reversing role (binder/connecter) you have to adapt code to create many socket (connect) instead of one (bind) if you're the server for example, but apart from that, I understand what you mean (messages will be handled the same way at the end I guess)
| [Friday 24 December 2010] [05:16:44] <neopallium>	looks like you can bind & connect on the same zmq socket
| [Friday 24 December 2010] [05:17:25] <neopallium>	I just modified one of my test scripts which creates a PUB socket and had it bind to port 5555 and connect to port 5556
| [Friday 24 December 2010] [05:18:00] <neopallium>	on port 5556 was a script with a SUB socket
| [Friday 24 December 2010] [05:18:31] <neopallium>	both server & client SUB sockets where able to receive messages from the PUB socket.
| [Friday 24 December 2010] [05:18:51] <neopallium>	I didn't even think that was possible until now.
| [Friday 24 December 2010] [05:19:06] <cods>	oh, that's interesting. I have not seen that documented.
| [Friday 24 December 2010] [05:20:07] <neopallium>	I have read somewhere in the docs that zmq sockets don't put restrictions on who connects and who binds.
| [Friday 24 December 2010] [05:20:40] <neopallium>	but I didn't think that applied to binding & connection with the same socket.
| [Friday 24 December 2010] [05:22:08] <cods>	I like how 0mq is versatile. Great design.
| [Friday 24 December 2010] [05:33:05] <sustrik>	:)
| [Friday 24 December 2010] [05:34:15] <sustrik>	neopallium: you can also add the link to your project here:
| [Friday 24 December 2010] [05:34:16] <sustrik>	http://www.zeromq.org/docs:labs
| [Friday 24 December 2010] [06:22:19] <neopallium>	sustrik: thanks I just sent an email to the mailinglist.
| [Friday 24 December 2010] [06:48:01] <cods>	just curious while looking at the data on the wire, what the 0x01 0x01 header means? (before what looks like the "SPB" encoding) Is this documented somewhere? (or alternatively, where is it handled in the source code?)
| [Friday 24 December 2010] [10:02:59] <DasIch>	i'm currently trying to install pyzmq on a machine running ubuntu 10.10, even with libzmq-dev installed pip install pyzmq reports that a zmq_utils.h is missing
| [Friday 24 December 2010] [10:03:33] <DasIch>	i wasn't able to find any information regarding this issue is there a ppa i should use?
| [Friday 24 December 2010] [10:06:21] <DasIch>	ah, ppa:chris-lea-zeromq does the job
| [Friday 24 December 2010] [10:07:07] <DasIch>	uh no, i get an Assertion failed: !pgm_supported () (zmq.cpp:240)
| [Friday 24 December 2010] [10:07:50] <guido_g>	DasIch: do the versions of libzmq and pyzmq match?
| [Friday 24 December 2010] [10:11:37] <DasIch>	pyzmq version is 2.0.10, how do i find out the libzmq version?
| [Friday 24 December 2010] [10:12:17] <guido_g>	from the package? apt-cache show ... 
| [Friday 24 December 2010] [10:12:27] <DasIch>	ah it's also 2.0.10
| [Friday 24 December 2010] [10:13:05] <guido_g>	then it seems to be build w/o pgm
| [Friday 24 December 2010] [10:14:00] <guido_g>	get the source and compile it yourself
| [Friday 24 December 2010] [10:14:13] <DasIch>	guido_g: ok, thanks
| [Friday 24 December 2010] [11:55:51] <cremes>	andrewvc: i'm around for about 30m this morning; what's up?
| [Friday 24 December 2010] [12:12:57] <cremes>	andrewvc: send me a message offline and i'll answer it; i'll be off irc for the next 3 days or so...
| [Friday 24 December 2010] [12:13:21] <cremes>	merry christmas, everybody!
| [Friday 24 December 2010] [21:01:23] <lorph>	is there a API for communicating between TCP/UDP and zeromq, or do I have to make that myself
| [Saturday 25 December 2010] [11:05:11] <kuka>	hi! how to install zeroMQ lib in tomcat for using in web apps?
| [Saturday 25 December 2010] [11:05:34] <kuka>	ivan help us
| [Saturday 25 December 2010] [12:19:11] <keffo>	Merry off-work-period, everyone!
| [Saturday 25 December 2010] [17:28:45] <roxlu>	hi
| [Saturday 25 December 2010] [17:31:20] <roxlu>	I just found zeromq, and read the intro pages of the manual but I'm confused what's so good about zeromq?
| [Saturday 25 December 2010] [17:31:54] <roxlu>	It's a networking library; but what makes it different from other libs
| [Saturday 25 December 2010] [17:52:48] <keffo>	Might I suggest you keep reading beyond the intro pages?
| [Saturday 25 December 2010] [18:14:39] <Skaag>	yes, I suggest you do that, as well. I know for a fact that after you read more, it will become clear to you, because I just re-read those documents myself this week.
| [Saturday 25 December 2010] [18:15:02] <Skaag>	assume it's deeper and more important than you might imagine... ;-)
| [Saturday 25 December 2010] [21:22:00] <andrewvc>	cremes: around?
| [Sunday 26 December 2010] [03:42:06] <neopallium>	how does one detect if a request sent to a REQ socket is lost? (i.e. the server dies/restarts before sending the message from it's REP socket)
| [Sunday 26 December 2010] [03:44:36] <neopallium>	I have an example of a job queue server with worker clients, the workers connect a REQ socket to the server's XREP socket and pull for jobs, but if the server is restarted when the workers are waiting for a job, they get stuck.
| [Sunday 26 December 2010] [03:46:53] <guido_g>	you can't
| [Sunday 26 December 2010] [03:47:27] <guido_g>	or better, mq can't, you've to build a timeout yourself
| [Sunday 26 December 2010] [03:55:12] <neopallium>	one option I though of to try and solve this is to use PUB/SUB sockets so the server can tell the workers to re-connect.  But I don't think that will be an option for other uses of REQ/REP sockets.
| [Sunday 26 December 2010] [03:57:57] <guido_g>	right, req/rep is simple but doesn't work
| [Sunday 26 December 2010] [03:58:41] <guido_g>	you have to augment it w/ poll for timeout
| [Sunday 26 December 2010] [15:52:00] <andrewvc>	sustrik, cremes, I was wondering if either of you were around
| [Sunday 26 December 2010] [15:52:14] <andrewvc>	or anyone who's done work with FDs lately, they seem to act funky for me
| [Sunday 26 December 2010] [15:52:38] <andrewvc>	initially, they notify via 'select' properly, but after a point, they don't seem to
| [Sunday 26 December 2010] [15:52:59] <andrewvc>	select(15, [12 14], [], [], {0, 90000}) = 1 (in [12], left {0, 89997})
| [Sunday 26 December 2010] [15:52:59] <andrewvc>	select(15, [12 14], [], [], {0, 90000}) = 1 (in [12], left {0, 36581})
| [Sunday 26 December 2010] [15:53:00] <andrewvc>	select(15, [12 14], [], [], {0, 90000}) = 0 (Timeout)
| [Sunday 26 December 2010] [15:53:00] <andrewvc>	select(15, [12 14], [], [], {0, 90000}) = 0 (Timeout)
| [Sunday 26 December 2010] [15:53:00] <andrewvc>	select(15, [12 14], [], [], {0, 90000}) = 0 (Timeout)
| [Sunday 26 December 2010] [15:53:00] <andrewvc>	select(15, [12 14], [], [], {0, 90000}) = 0 (Timeout)
| [Sunday 26 December 2010] [15:53:12] <andrewvc>	even with a constant stream of messages
| [Sunday 26 December 2010] [16:06:10] <andrewvc>	oh, I'm not sure if this is true in general for select (or a total noob mistake), but previously I was reading a single message at a time off the socket whenever EM was notified by either select() or epoll(). This apparently does not work, your handler must repeatedly read off the socket until there is nothing left to read. I'm doing this by repeatedly checking ZMQ::EVENTS after reading each message. 
| [Sunday 26 December 2010] [21:49:22] <swills>	ping?
| [Sunday 26 December 2010] [21:49:39] <swills>	i was in here a while back asking about zeromq perl modules
| [Sunday 26 December 2010] [21:49:44] <swills>	http://travlr.github.com/zmqirclog/2010-November.html
| [Sunday 26 December 2010] [21:52:27] <swills>	i'me back to looking at that, but i think i've decided the issue is that the perl zeromq module is written to expect a threaded perl and threaded zeromq
| [Monday 27 December 2010] [08:29:48] <monokrome>	hey
| [Monday 27 December 2010] [08:30:04] <monokrome>	Does anyone know if I can use zeromq without using exceptions?
| [Monday 27 December 2010] [08:31:55] <monokrome>	I guess that I could use the C libraries :/
| [Monday 27 December 2010] [10:47:21] <andrewvc>	cremes: around?
| [Monday 27 December 2010] [10:52:01] <andrewvc>	actually, anyone else around? sustrik?
| [Monday 27 December 2010] [11:48:33] <andrewvc>	Anyone know why if you monitor a ZMQ FD with select for a read, and the select gets triggered, subsequent calls to select will show the socket as readable until all messages have been read off the socket?
| [Monday 27 December 2010] [12:30:50] <andrewvc>	cremes, thanks for the email wrt to edge triggering
| [Monday 27 December 2010] [12:34:40] <andrewvc>	you know if I after it gets triggered I should use a loop that checks ZMQ::EVENTS before reading each message, or just repeatedly calls recv(ZMQ::NOBLOCK) without checking ZMQ::EVENTS for reads. i'm guessing that recv alone is probably fine for reads, but ZMQ::EVENTS is probably a good thing to check for before sending a message
| [Monday 27 December 2010] [12:49:10] <neopallium>	andrewvc: I have used ZMQ::FD with the an event loop and the way I did it was to call recv()/send() until they return EAGAIN.  When recv() returns EAGAIN then wait for a read event before calling recv() again.  When send() returns EAGAIN then queue the data and wait for a write event.
| [Monday 27 December 2010] [12:49:31] <andrewvc>	cool
| [Monday 27 December 2010] [12:49:54] <andrewvc>	so, ZMQ_EVENTS is there only if you're curious, but don't actually want to send/read
| [Monday 27 December 2010] [12:49:57] <neopallium>	you can see how I did it in Lua code here: https://github.com/Neopallium/lua-handlers/blob/master/handler/nsocket.lua
| [Monday 27 December 2010] [12:50:04] <andrewvc>	nice! thanks
| [Monday 27 December 2010] [12:50:21] <neopallium>	I didn't use ZMQ_EVENTS
| [Monday 27 December 2010] [12:51:23] <neopallium>	seems like event mongrel2 which uses zeromq with an eventloop doesn't use ZMQ_EVENTS
| [Monday 27 December 2010] [12:51:29] <neopallium>	*even
| [Monday 27 December 2010] [12:51:30] <andrewvc>	interesting
| [Monday 27 December 2010] [12:51:56] <neopallium>	basically that is how you should work with an edge-trigger socket.
| [Monday 27 December 2010] [12:52:17] <andrewvc>	cool, yeah, I don't know where I got it into my head that ZMQ_EVENTS should be checked first
| [Monday 27 December 2010] [12:52:34] <neopallium>	you only pause your sending/receiving when you get an EAGAIN from the socket.
| [Monday 27 December 2010] [12:53:05] <andrewvc>	cool, yeah I've never really mucked around much with select/epoll before, I appreciate the pointers
| [Monday 27 December 2010] [12:53:06] <neopallium>	I really don't know what ZMQ_EVENTS is good for.
| [Monday 27 December 2010] [12:54:35] <neopallium>	oops that was the wrong file the one for zeromq socket is this one: https://github.com/Neopallium/lua-handlers/blob/master/handler/zsocket.lua
| [Monday 27 December 2010] [12:55:18] <neopallium>	the nsocket.lua file is for tcp/udp sockets which are level-triggered.
| [Monday 27 December 2010] [12:57:27] <andrewvc>	well
| [Monday 27 December 2010] [12:57:31] <andrewvc>	I recall someone saying
| [Monday 27 December 2010] [12:57:39] <cremes>	andrewvc: ZM_EVENTS is used to determine if there is a "whole" message ready on the FD
| [Monday 27 December 2010] [12:57:42] <andrewvc>	yeah
| [Monday 27 December 2010] [12:57:50] <andrewvc>	was about to say :)
| [Monday 27 December 2010] [12:57:52] <andrewvc>	lol
| [Monday 27 December 2010] [12:57:53] <cremes>	otherwise you would try to read a partial which eoesn't work in 0mq
| [Monday 27 December 2010] [12:58:01] <andrewvc>	but you'd get an EAGAIN right?
| [Monday 27 December 2010] [12:58:23] <andrewvc>	i mean, I assume it'd be a waste of cycles to call ZMQ_EVENTS before each recv
| [Monday 27 December 2010] [12:58:25] <cremes>	andrewvc: i don't know; i assume so but my assumptions are sometimes wildly wrong
| [Monday 27 December 2010] [12:58:33] <andrewvc>	lol
| [Monday 27 December 2010] [12:58:54] <cremes>	no, you wouldn't need to call it *each* time, just *once* after ZM_FD triggered
| [Monday 27 December 2010] [12:59:11] <cremes>	once ZM_FD and ZM_EVENTS agree, read until EAGAIN
| [Monday 27 December 2010] [13:03:06] <andrewvc>	gotcha
| [Monday 27 December 2010] [13:03:40] <andrewvc>	how about for a writable handler.
| [Monday 27 December 2010] [13:03:54] <andrewvc>	it's conceivable the writable state could change after any given message no?
| [Monday 27 December 2010] [13:10:58] <zedas>	neopallium: i think ZMQ_EVENTS is new, and I just use zmq_poll directly instead.
| [Monday 27 December 2010] [13:11:34] <neopallium>	ah, yeah I forgot about that.
| [Monday 27 December 2010] [15:20:38] <cremes>	andrewvc: what you said doesn't make sense from the write side
| [Monday 27 December 2010] [15:20:48] <andrewvc>	oh?
| [Monday 27 December 2010] [15:20:50] <cremes>	just write until you get EAGAIN; no need to check ZM_EVENTS
| [Monday 27 December 2010] [15:20:56] <andrewvc>	ah, gotcha
| [Tuesday 28 December 2010] [00:32:58] <lestrrat>	oh, woot, emails for build failures ;)
| [Tuesday 28 December 2010] [00:33:00] <lestrrat>	cool
| [Tuesday 28 December 2010] [06:02:30] <Skaag>	anyone here uses zookeeper with zmq?
| [Tuesday 28 December 2010] [06:46:50] <newbie2207>	hi
| [Tuesday 28 December 2010] [13:29:29] <CIA-21>	jzmq: 03Gonzalo Diethelm 07master * rb623601 10/ (4 files in 3 dirs): 
| [Tuesday 28 December 2010] [13:29:29] <CIA-21>	jzmq: Added new files (Streamer, Forwarder, Queue) to MSCV project.
| [Tuesday 28 December 2010] [13:29:29] <CIA-21>	jzmq: Corrected permissions. (+10 more commits...) - http://bit.ly/fgP0rH
| [Tuesday 28 December 2010] [13:35:55] <CIA-21>	jzmq: 03Gonzalo Diethelm 07master * r76b78bf 10/ README : 
| [Tuesday 28 December 2010] [13:35:55] <CIA-21>	jzmq: Merge branch 'master' of http://github.com/yawn/jzmq into yawn-master
| [Tuesday 28 December 2010] [13:35:55] <CIA-21>	jzmq: Conflicts:
| [Tuesday 28 December 2010] [13:35:55] <CIA-21>	jzmq:  README - http://bit.ly/fXVvAM
| [Tuesday 28 December 2010] [14:17:38] <shykes_>	hello
| [Tuesday 28 December 2010] [14:19:06] <shykes_>	I'm thinking of implementing a device with a simple "routing key" mechanism - does that exist already?
| [Tuesday 28 December 2010] [18:16:35] <lestrrat>	Can the hudson tests run the perl binding tests using "make test TEST_VERBOSE=1"? that would give me more hints for debugging
| [Tuesday 28 December 2010] [19:40:59] <s0undt3ch>	hello ppl
| [Tuesday 28 December 2010] [19:41:20] <s0undt3ch>	I'm getting "Assertion failed: !pgm_supported() ...." when trying to run one of the pyzmq examples
| [Tuesday 28 December 2010] [20:02:37] <bgranger>	s0undt3ch: what version of pyzmq and zeromq are you running?
| [Tuesday 28 December 2010] [20:03:11] <s0undt3ch>	bgranger: well the ones I get from the ppa repo are pyzmq 2.0.7 and zmq 2.0.10
| [Tuesday 28 December 2010] [20:03:39] <s0undt3ch>	bgranger: I'm now trying to build local versions of the libraries to see if I can get over that
| [Tuesday 28 December 2010] [20:03:40] <bgranger>	This is a known bug that has been fixed in 2.0.10 of pyzmq.  Can you give that a shot?
| [Tuesday 28 December 2010] [20:03:47] <bgranger>	Yep, that would solve it.
| [Tuesday 28 December 2010] [20:03:59] <s0undt3ch>	oh sorry
| [Tuesday 28 December 2010] [20:04:08] <bgranger>	But, just so you know, the library should work fine even though the tests fail.
| [Tuesday 28 December 2010] [20:04:08] <s0undt3ch>	I think I was using 2.0.10 of pyzmq
| [Tuesday 28 December 2010] [20:04:24] <s0undt3ch>	let me clean up the mess first
| [Tuesday 28 December 2010] [20:04:26] <bgranger>	OK
| [Tuesday 28 December 2010] [20:05:08] <bgranger>	Which example were you running.
| [Tuesday 28 December 2010] [20:05:16] <s0undt3ch>	heartbeat/heart.py
| [Tuesday 28 December 2010] [20:05:26] <s0undt3ch>	I'm building 2.0.10 now
| [Tuesday 28 December 2010] [20:07:33] <s0undt3ch>	ok, I now have the 2.0.10 pyzmq
| [Tuesday 28 December 2010] [20:07:46] <s0undt3ch>	bgranger: same error
| [Tuesday 28 December 2010] [20:08:59] <s0undt3ch>	ok, both packages libzmq0 and pyzmq are at 2.0.10
| [Tuesday 28 December 2010] [20:09:47] <s0undt3ch>	bgranger: yep, I've added a print statement at the top of heart.py
| [Tuesday 28 December 2010] [20:09:56] <s0undt3ch>	print zmq.__version__, zmq.__file__
| [Tuesday 28 December 2010] [20:10:00] <s0undt3ch>	output  is:
| [Tuesday 28 December 2010] [20:10:09] <s0undt3ch>	2.0.10 /home/vampas/projects/.virtual_python/lib/python2.6/site-packages/zmq/__init__.pyc
| [Tuesday 28 December 2010] [20:10:09] <s0undt3ch>	Assertion failed: !pgm_supported () (zmq.cpp:240)
| [Tuesday 28 December 2010] [20:10:09] <s0undt3ch>	Aborted
| [Tuesday 28 December 2010] [20:12:29] <bgranger>	Can you comment out line 17 of the heart.py and retry?
| [Tuesday 28 December 2010] [20:12:37] <bgranger>	The one where the Context is created.
| [Tuesday 28 December 2010] [20:13:47] <s0undt3ch>	bgranger: yeah, the Context() was what was causing it
| [Tuesday 28 December 2010] [20:16:38] <bgranger>	The issue is that when pgm is enabled (multicast), only 1 context can be created.  The ThreadDevice creates one (which is fine), but so did line 17.  The one in L17 was never used though.
| [Tuesday 28 December 2010] [20:16:52] <s0undt3ch>	bgranger: zmq.Context() wasn't doin' anything there right?
| [Tuesday 28 December 2010] [20:17:05] <bgranger>	This is a general limitation of zeromq - that with pgm, only 1 context can be used.
| [Tuesday 28 December 2010] [20:17:32] <bgranger>	But, pyzmq+zeromq should be working fine for you.
| [Tuesday 28 December 2010] [20:17:42] <s0undt3ch>	bgranger: but instead of completely failing can't it just warn or ignore and continue?
| [Tuesday 28 December 2010] [20:18:56] <bgranger>	As far as pyzmq goes, we don't have a clean way of doing that yet in general.  We would need zeromq to handle it differently, but zeromq is limited by the initialization model of pgm.
| [Tuesday 28 December 2010] [20:19:00] <bgranger>	Tough to get around.
| [Tuesday 28 December 2010] [20:19:23] <bgranger>	At least, that is how I remember the situation for now.
| [Tuesday 28 December 2010] [20:19:45] <s0undt3ch>	well Thanks!
| [Tuesday 28 December 2010] [20:19:48] <s0undt3ch>	:)
| [Tuesday 28 December 2010] [20:19:48] <bgranger>	Sure
| [Tuesday 28 December 2010] [20:19:54] <bgranger>	At least it is working.
| [Tuesday 28 December 2010] [20:20:04] <s0undt3ch>	anyway, now for some implementation thought
| [Tuesday 28 December 2010] [20:20:09] <s0undt3ch>	*thoughts
| [Tuesday 28 December 2010] [20:20:20] <s0undt3ch>	here's my problem
| [Tuesday 28 December 2010] [20:20:25] <bgranger>	Sure
| [Tuesday 28 December 2010] [20:21:06] <s0undt3ch>	I need to build a system that listens to audio streams, analyses them, and sends events to clients
| [Tuesday 28 December 2010] [20:21:31] <s0undt3ch>	I created this already using twisted, not that good though
| [Tuesday 28 December 2010] [20:21:59] <bgranger>	OK
| [Tuesday 28 December 2010] [20:22:00] <s0undt3ch>	what I'm trying to achieve now is use green threads, ie, eventlet or gevent
| [Tuesday 28 December 2010] [20:22:32] <bgranger>	Are the audio streams coming over zeromq as well?
| [Tuesday 28 December 2010] [20:22:34] <s0undt3ch>	the issue with this is that gstreamer the audio lib I'll use is not integrated with either eventlet nor gevent
| [Tuesday 28 December 2010] [20:23:14] <s0undt3ch>	bgranger: nope, zmq was going at first to be used for the events messaging
| [Tuesday 28 December 2010] [20:23:20] <bgranger>	OK
| [Tuesday 28 December 2010] [20:23:41] <bgranger>	So you have 1 process that is using gstreamer to look at audio streams and you want to fire off event to clients.
| [Tuesday 28 December 2010] [20:23:44] <bgranger>	How many clients?
| [Tuesday 28 December 2010] [20:23:50] <s0undt3ch>	what I've been advised by some eventlet ppl is to run each gstreamer audio stream in it's own process
| [Tuesday 28 December 2010] [20:24:02] <s0undt3ch>	at most 100 clients at least for now
| [Tuesday 28 December 2010] [20:24:06] <bgranger>	OK
| [Tuesday 28 December 2010] [20:24:16] <s0undt3ch>	this is going to be a tool to be used inside the company
| [Tuesday 28 December 2010] [20:24:19] <bgranger>	OK
| [Tuesday 28 December 2010] [20:24:31] <bgranger>	So you actually have N gstreamer processes and M clients
| [Tuesday 28 December 2010] [20:24:37] <s0undt3ch>	yes
| [Tuesday 28 December 2010] [20:24:39] <bgranger>	OK
| [Tuesday 28 December 2010] [20:24:55] <bgranger>	And you want all M clients to get the events from all N streaming processes?
| [Tuesday 28 December 2010] [20:25:31] <s0undt3ch>	so what I'm thinking now is, also use zmq to communicate between the gstreamer processes and a "core daemon" which will get all messages and deliver them to clients
| [Tuesday 28 December 2010] [20:25:43] <s0undt3ch>	well, all clients should receive all messages
| [Tuesday 28 December 2010] [20:25:54] <s0undt3ch>	so
| [Tuesday 28 December 2010] [20:25:56] <s0undt3ch>	yes
| [Tuesday 28 December 2010] [20:26:04] <s0undt3ch>	"all M clients to get the events from all N streaming processes"
| [Tuesday 28 December 2010] [20:26:36] <s0undt3ch>	since the core daemon and the gstreamer process will be on the same machine I though of using ipc
| [Tuesday 28 December 2010] [20:27:16] <s0undt3ch>	but as you can see there are several needs for the zmq lib which I'm just starting to get aquainted
| [Tuesday 28 December 2010] [20:27:25] <s0undt3ch>	oh
| [Tuesday 28 December 2010] [20:27:25] <bgranger>	Yes
| [Tuesday 28 December 2010] [20:27:37] <s0undt3ch>	the gstreamer processes will need to be controlable
| [Tuesday 28 December 2010] [20:27:45] <bgranger>	In what sense?
| [Tuesday 28 December 2010] [20:27:52] <s0undt3ch>	ie, I'll need to pass "commands" to it
| [Tuesday 28 December 2010] [20:28:24] <s0undt3ch>	ie, should it stop, change the stream configuration variables, etc
| [Tuesday 28 December 2010] [20:28:56] <bgranger>	OK, let's start with the basics of getting the events to the clients.
| [Tuesday 28 December 2010] [20:29:02] <s0undt3ch>	ok
| [Tuesday 28 December 2010] [20:29:09] <bgranger>	Let's call the gstreamer processes source processes.
| [Tuesday 28 December 2010] [20:29:13] <s0undt3ch>	sure
| [Tuesday 28 December 2010] [20:29:23] <bgranger>	For each source process, you will have a PUB socket.
| [Tuesday 28 December 2010] [20:29:53] <bgranger>	Each of those PUB sockets will connect to a FORWARDER device that runs in a separate process.
| [Tuesday 28 December 2010] [20:30:34] <bgranger>	The job of the FOWARDER process is to collect all the events and publish them to all clients.  The clients will each have a SUB socket that is connected to the other end of the FORWARDER process.
| [Tuesday 28 December 2010] [20:31:16] <s0undt3ch>	ok
| [Tuesday 28 December 2010] [20:31:30] <s0undt3ch>	so far, I'm understanding :)
| [Tuesday 28 December 2010] [20:32:05] <bgranger>	You could do all of this w/o the FORWARDER in the middle, but having it will make it much easier for all the clients to get the events of all the sources.
| [Tuesday 28 December 2010] [20:32:18] <s0undt3ch>	ok
| [Tuesday 28 December 2010] [20:32:19] <bgranger>	I would start out by prototyping that.
| [Tuesday 28 December 2010] [20:32:50] <s0undt3ch>	yeah, get some example code going on right?
| [Tuesday 28 December 2010] [20:33:01] <bgranger>	Then if you want to enable the clients to control the sources, I would use REQ/REP or XREQ/XREP sockets separately
| [Tuesday 28 December 2010] [20:33:02] <bgranger>	Yes
| [Tuesday 28 December 2010] [20:33:52] <bgranger>	The overall idea is to use different socket pairs for each type of communication pattern in your distributed application.  In some of our more complicated apps, we have many different zeromq sockets.
| [Tuesday 28 December 2010] [20:34:21] <s0undt3ch>	what are the diferences between the req/rep and x version of them
| [Tuesday 28 December 2010] [20:36:05] <bgranger>	There are a number of differences, I would check out the guide:
| [Tuesday 28 December 2010] [20:36:06] <bgranger>	http://zguide.zeromq.org/chapter:all#toc41
| [Tuesday 28 December 2010] [20:36:14] <s0undt3ch>	I will
| [Tuesday 28 December 2010] [20:36:39] <bgranger>	In most cases find myself using the X variants as they are more flexible and handle multiple peers asynchronously.
| [Tuesday 28 December 2010] [21:13:31] <s0undt3ch>	nice reading
| [Tuesday 28 December 2010] [21:13:47] <s0undt3ch>	so far I'm not thinking about scalability, at least at the sources level
| [Tuesday 28 December 2010] [21:14:10] <s0undt3ch>	the only part that should be scalable is client handling
| [Tuesday 28 December 2010] [21:14:23] <s0undt3ch>	anyway, let cook up some code...
| [Tuesday 28 December 2010] [21:14:29] <s0undt3ch>	*let's
| [Wednesday 29 December 2010] [03:49:51] <jugg>	Having an xrep (bind)/req (connect) setup, with xrep implementation using zmq 2.1.x and the req implementation using 2.0.10, and the req implementation being a single process with multiple threads, each thread having a req-socket.   It is always the case that eventually the req-socket after send'ing blocks on recv never getting a response.  Upgrading the req implementation to 2.1.0 greatly reduces this occurrence frequency, but it still happens.
| [Wednesday 29 December 2010] [03:50:10] <jugg>	Sometimes instead of locking on recv,  zmq asserts while blocking in recv with this error (zmq v2.1.0): Assertion failed: zmq_msg_size (msg_) == 0 (req.cpp:87). 
| [Wednesday 29 December 2010] [03:51:49] <jugg>	Has that use case xrep(bind)/req(connect) been tested much?
| [Wednesday 29 December 2010] [03:54:52] <sustrik>	the assert looks like there's an malformed message being received on the wire
| [Wednesday 29 December 2010] [03:56:27] <jugg>	Perhaps the xrep isn't filtering the id part correctly, and sending the separator message?
| [Wednesday 29 December 2010] [03:56:52] <sustrik>	dunno, can you make a minimal test case?
| [Wednesday 29 December 2010] [03:56:58] <jugg>	I'm still working on that...
| [Wednesday 29 December 2010] [03:57:36] <jugg>	I jumped in here where I found that changing the req implementation zmq library version changed the behavior...   I had been expecting to find the issue on the xrep side.
| [Wednesday 29 December 2010] [03:59:40] <jugg>	is the use case known to be robust, or does it have little known exposure?
| [Wednesday 29 December 2010] [04:03:32] <sustrik>	which part are you speaking about now? the blocking on recv or the assert?
| [Wednesday 29 December 2010] [04:09:47] <jugg>	one xrep(bind)/many req(connect) pair.
| [Wednesday 29 December 2010] [04:11:58] <sustrik>	what behaviour change?
| [Wednesday 29 December 2010] [04:12:30] <sustrik>	the assert?
| [Wednesday 29 December 2010] [04:12:49] <jugg>	the blocking on recv frequency diminished moving from 2.0.10 to 2.1.0.
| [Wednesday 29 December 2010] [04:13:00] <jugg>	The assert is random as ever with both versions.
| [Wednesday 29 December 2010] [04:13:53] <sustrik>	are you closing the req peer at that moment?
| [Wednesday 29 December 2010] [04:15:13] <jugg>	no, it happens at various points in the set of messages/responses I'm processing.
| [Wednesday 29 December 2010] [04:16:34] <sustrik>	are you setting HWMs?
| [Wednesday 29 December 2010] [04:16:43] <jugg>	no
| [Wednesday 29 December 2010] [04:16:55] <sustrik>	then it should not happen imo
| [Wednesday 29 December 2010] [04:17:11] <sustrik>	looks like a bug
| [Wednesday 29 December 2010] [04:18:31] <jugg>	If I can reproduce the issue on a simple test case, I'll pass it along.
| [Wednesday 29 December 2010] [04:18:44] <sustrik>	thanks
| [Wednesday 29 December 2010] [04:31:24] <s0undt3ch>	hello ppl, are there any issue using pyzmq inside a chroot?
| [Wednesday 29 December 2010] [04:31:30] <s0undt3ch>	http://paste.pocoo.org/show/311220/
| [Wednesday 29 December 2010] [09:30:10] <CIA-21>	jzmq: 03Gonzalo Diethelm 07master * ree2d21e 10/ (6 files in 2 dirs): 
| [Wednesday 29 December 2010] [09:30:10] <CIA-21>	jzmq: Added support for unregistering sockets from poller.
| [Wednesday 29 December 2010] [09:30:10] <CIA-21>	jzmq: Applied standard indentation everywhere on Java files. - http://bit.ly/fcb5Pi
| [Wednesday 29 December 2010] [09:43:58] <jgarbers>	Hi! I'm trying to build zmq under Visual Studio 2008 -- but the current source release seems to have VS2010 .vcproj files in its solution, so VS2008 can't read them. Is there a straightforward way to use VS2008 instead of VS2010?
| [Wednesday 29 December 2010] [09:45:58] <sustrik>	are they vs2010 project files?
| [Wednesday 29 December 2010] [09:46:13] <sustrik>	i recall i built it with vs2008 last time i tried
| [Wednesday 29 December 2010] [09:46:52] <jgarbers>	seems so, or maybe i'm doing something wrong
| [Wednesday 29 December 2010] [09:47:02] <jgarbers>	the VS2008 reports an error when opening the .sln
| [Wednesday 29 December 2010] [09:47:08] <jgarbers>	let me get the details again
| [Wednesday 29 December 2010] [09:47:37] <jgarbers>	i'm hoping this is a simple pilot error that will make me feel stupid for 5 minutes and let me get back to work :-)
| [Wednesday 29 December 2010] [09:48:17] <jgarbers>	says "...libzmq\libzmq.vcproj' cannot be opened because its project type (.vcproj) is not supported by this version of Visual Studio."
| [Wednesday 29 December 2010] [09:48:30] <jgarbers>	get that same error for each of the projects
| [Wednesday 29 December 2010] [09:50:18] <sustrik>	hm, no idea, sorry
| [Wednesday 29 December 2010] [09:51:45] <jgarbers>	darn. thanks anyway!
| [Wednesday 29 December 2010] [10:01:30] <jgarbers>	okay, it was indeed pilot stupidity. my VS2008 doesn't have C++ -- just C# and VB.  Cripes.  Off to go get the appropriate compiler, which *may* help.
| [Wednesday 29 December 2010] [11:49:20] <shykes_>	hello
| [Wednesday 29 December 2010] [11:49:46] <shykes_>	I'm seeing a weird issue when trying to PUB via a higher-latency link
| [Wednesday 29 December 2010] [11:50:09] <cremes>	what do you see?
| [Wednesday 29 December 2010] [11:50:38] <seb`>	REQ messages arrive with no problem
| [Wednesday 29 December 2010] [11:50:53] <seb`>	but PUB and PUSH messages never arrive
| [Wednesday 29 December 2010] [11:51:26] <shykes_>	... they never arrive *if sent from a home DSL link*
| [Wednesday 29 December 2010] [11:51:42] <shykes_>	PUB and PUSH messages *do* arrive at the same location if sent from the same datacenter
| [Wednesday 29 December 2010] [11:51:57] <seb`>	on tcp sockets btw
| [Wednesday 29 December 2010] [11:52:29] <cremes>	are you both working on the same issue? interleaving your messages like that is confusing....
| [Wednesday 29 December 2010] [11:52:43] <seb`>	sorry yes:-)
| [Wednesday 29 December 2010] [11:52:50] <cremes>	ok
| [Wednesday 29 December 2010] [11:53:22] <cremes>	what does the "on tcp sockets btw" comment mean? you are using both 0mq and your own sockets?
| [Wednesday 29 December 2010] [11:53:54] <seb`>	no I mean it's a tcp link
| [Wednesday 29 December 2010] [11:54:06] <seb`>	not epgm & co
| [Wednesday 29 December 2010] [11:54:07] <cremes>	ok, tcp transport in 0mq-speak
| [Wednesday 29 December 2010] [11:54:12] <seb`>	yes
| [Wednesday 29 December 2010] [11:54:30] <seb`>	"transport" that's the word I was looking for:-)
| [Wednesday 29 December 2010] [11:54:32] <cremes>	so to recap, req/rep works but pub & push do not
| [Wednesday 29 December 2010] [11:54:54] <seb`>	exactly
| [Wednesday 29 December 2010] [11:55:08] <sustrik>	strange
| [Wednesday 29 December 2010] [11:55:12] <cremes>	do *all* messages disappear or do you get *some* of them?
| [Wednesday 29 December 2010] [11:55:17] <seb`>	all of them
| [Wednesday 29 December 2010] [11:55:21] <seb`>	nothing arrives
| [Wednesday 29 December 2010] [11:55:50] <sustrik>	have a look whether the underlying tcp connection exists
| [Wednesday 29 December 2010] [11:56:01] <sustrik>	netstat or something
| [Wednesday 29 December 2010] [11:56:09] <cremes>	in your client program with the SUB socket, do you use setsockopt with ZM_SUBSCRIBE to set your subscription?
| [Wednesday 29 December 2010] [11:56:25] <cremes>	if you don't, all messages are dropped
| [Wednesday 29 December 2010] [11:56:31] <seb`>	cremes: yes we did
| [Wednesday 29 December 2010] [11:56:36] <cremes>	good
| [Wednesday 29 December 2010] [11:56:40] <seb`>	sustrik: I'll check
| [Wednesday 29 December 2010] [11:58:02] <seb`>	sustrik: netcat is able to connect
| [Wednesday 29 December 2010] [11:58:07] <sustrik>	i mean -- there may be a problem establishing the connection is particular direction
| [Wednesday 29 December 2010] [11:58:22] <sustrik>	due to firewalls
| [Wednesday 29 December 2010] [11:58:32] <sustrik>	the same way as in your use case?
| [Wednesday 29 December 2010] [11:59:06] <seb`>	sustrik: no it's not firewalls since a switch to req/rep works
| [Wednesday 29 December 2010] [11:59:30] <sustrik>	it may depend on the direction of connection establishment
| [Wednesday 29 December 2010] [11:59:39] <sustrik>	i.e. where you do bind and where you do connecty
| [Wednesday 29 December 2010] [12:00:00] <seb`>	the bind is server side
| [Wednesday 29 December 2010] [12:00:08] <sustrik>	same as in your use case?
| [Wednesday 29 December 2010] [12:00:43] <sustrik>	anyway, start you app and check whether the TCP connection is established
| [Wednesday 29 December 2010] [12:01:00] <sustrik>	that would be the best point to start the investigation
| [Wednesday 29 December 2010] [12:01:05] <seb`>	sustrik: yes checking now
| [Wednesday 29 December 2010] [12:02:16] <seb`>	yes it's established
| [Wednesday 29 December 2010] [12:03:31] <sustrik>	it's PUSH/PULL, right?
| [Wednesday 29 December 2010] [12:04:01] <seb`>	yes it is
| [Wednesday 29 December 2010] [12:04:11] <seb`>	but the problem is the same with PUB/SUB
| [Wednesday 29 December 2010] [12:04:29] <seb`>	but REQ/REP works (exactly the same conditions)
| [Wednesday 29 December 2010] [12:04:34] <sustrik>	let's focus on push/pull now
| [Wednesday 29 December 2010] [12:04:47] <seb`>	ok
| [Wednesday 29 December 2010] [12:04:56] <sustrik>	can you check whether data are passed on the wire?
| [Wednesday 29 December 2010] [12:05:08] <sustrik>	using wireshark or tcp dump?
| [Wednesday 29 December 2010] [12:05:17] <seb`>	yup
| [Wednesday 29 December 2010] [12:05:19] <seb`>	hold on
| [Wednesday 29 December 2010] [12:09:02] <shykes_>	Ok, we just found the problem ;)
| [Wednesday 29 December 2010] [12:09:10] <shykes_>	(taking over from seb`, sorry for the interleaving)
| [Wednesday 29 December 2010] [12:09:52] <shykes_>	in order to give you netstat information, we had the client stay open and wait for manual input to send
| [Wednesday 29 December 2010] [12:10:23] <shykes_>	instead of sending a pre-defined message and exiting instnatly
| [Wednesday 29 December 2010] [12:10:54] <shykes_>	when the client stays connected for a second or two, the messages start arriving
| [Wednesday 29 December 2010] [12:11:10] <shykes_>	looks like there's no guarantee that a connect() is ready when we start sending?
| [Wednesday 29 December 2010] [12:11:25] <shykes_>	I suppose in the context of a never-ending stream of messages, it's no big deal
| [Wednesday 29 December 2010] [12:11:26] <sustrik>	right
| [Wednesday 29 December 2010] [12:11:32] <sustrik>	zmq_connect is async
| [Wednesday 29 December 2010] [12:11:43] <shykes_>	So our problem is a non-problem :)
| [Wednesday 29 December 2010] [12:11:49] <sustrik>	great :)
| [Wednesday 29 December 2010] [12:12:00] <shykes_>	out of curiosity, any way to hook into connect?
| [Wednesday 29 December 2010] [12:12:11] <shykes_>	if we *do* need to wait for it to succeed? (ie for an automated test)
| [Wednesday 29 December 2010] [12:12:25] <seb`>	I think we could use zmq_poll for that
| [Wednesday 29 December 2010] [12:12:38] <sustrik>	not really, because the connection can be dropped and reestablished in the background
| [Wednesday 29 December 2010] [12:12:57] <sustrik>	so connect can happen even when no zmq_connect is being executed
| [Wednesday 29 December 2010] [12:13:56] <shykes_>	I see
| [Wednesday 29 December 2010] [12:14:00] <seb`>	sustrik: it should work to wait for POLLOUT right?
| [Wednesday 29 December 2010] [12:14:41] <sustrik>	pollout will succeed even though the connection is not established yet
| [Wednesday 29 December 2010] [12:14:48] <seb`>	ah?
| [Wednesday 29 December 2010] [12:14:57] <sustrik>	there's a message buffer
| [Wednesday 29 December 2010] [12:15:07] <sustrik>	if there's still space in the buffer
| [Wednesday 29 December 2010] [12:15:11] <seb`>	I see
| [Wednesday 29 December 2010] [12:15:12] <sustrik>	you can send messages
| [Wednesday 29 December 2010] [12:15:23] <sustrik>	they will be passed to the peer as soon as possible
| [Wednesday 29 December 2010] [12:15:48] <sustrik>	(i.e. when connection is established)
| [Wednesday 29 December 2010] [12:15:57] <seb`>	ok
| [Wednesday 29 December 2010] [12:16:04] <seb`>	thanks for your help
| [Wednesday 29 December 2010] [12:16:09] <sustrik>	you are welcome
| [Wednesday 29 December 2010] [17:39:52] <s0undt3ch>	hello ppl, here's a gdb session where I'm having troubles daemonizing my app -> http://paste.pocoo.org/show/311220/ <- seems to be related to pyzmq
| [Wednesday 29 December 2010] [17:57:03] <mikko>	s0undt3ch: do you fork() ?
| [Wednesday 29 December 2010] [17:57:18] <mikko>	and if yes do you init zmq before or after fork?
| [Wednesday 29 December 2010] [17:57:24] <s0undt3ch>	mikko: I'm using python-daemon and yes, it forks
| [Wednesday 29 December 2010] [17:57:35] <s0undt3ch>	mikko: and yes, I think zmq is setup before the fork
| [Wednesday 29 December 2010] [17:57:37] <s0undt3ch>	work?
| [Wednesday 29 December 2010] [17:57:41] <s0undt3ch>	*wrong
| [Wednesday 29 December 2010] [17:57:43] <s0undt3ch>	*wrong?
| [Wednesday 29 December 2010] [17:57:58] <mikko>	i remember someone having issues with that
| [Wednesday 29 December 2010] [17:58:07] <mikko>	try initializing all 0mq stuff after fork
| [Wednesday 29 December 2010] [17:59:32] <s0undt3ch>	mikko: hmm, zmq is beeing used to message that the app has forket, but I'll try to cook something up
| [Wednesday 29 December 2010] [18:02:16] <mikko>	are you forking just to daemonize?
| [Wednesday 29 December 2010] [18:05:04] <s0undt3ch>	mikko: hmm, lemme look at python-daemon's code
| [Wednesday 29 December 2010] [18:06:05] <s0undt3ch>	mikko: yes, it's forking to daemonize
| [Wednesday 29 December 2010] [18:06:33] <s0undt3ch>	mikko: http://paste.pocoo.org/show/311724/
| [Wednesday 29 December 2010] [18:13:07] <s0undt3ch>	mikko: if an app is chrooted, can it still reach the outside through tcp?
| [Wednesday 29 December 2010] [18:13:17] <s0undt3ch>	ie, will zmq connected to a tcp socket work?
| [Wednesday 29 December 2010] [18:13:49] <s0undt3ch>	doesn't seem to
| [Wednesday 29 December 2010] [18:18:29] <s0undt3ch>	hmm, I aparently have to mount proc inside the chroot, have a proper resolv.conf
| [Wednesday 29 December 2010] [18:18:59] <s0undt3ch>	so, aparently I have to solve both the daemonizing issues and also the chroot issues
| [Wednesday 29 December 2010] [18:22:23] <s0undt3ch>	hmm, how the hell does mogrel2 chroot
| [Wednesday 29 December 2010] [18:53:24] <mikko>	s0undt3ch: im not sure whether the fork actually causes the issues
| [Wednesday 29 December 2010] [18:53:45] <mikko>	but i think you are supposed to init zmq context for each fork
| [Wednesday 29 December 2010] [19:16:12] <s0undt3ch>	mikko: well, each for will have it's own context, nothing is shared between forks, hence zmq for the messaging between them
| [Wednesday 29 December 2010] [19:17:22] <mikko>	s0undt3ch: the gdb trace doesn't really tell anything
| [Wednesday 29 December 2010] [19:17:26] <mikko>	no symbols
| [Wednesday 29 December 2010] [19:18:23] <s0undt3ch>	mikko: well, it's a python virtualenv, don't know how to add debug symbols there
| [Wednesday 29 December 2010] [19:19:35] <mikko>	s0undt3ch: which version of zeromq is this?
| [Wednesday 29 December 2010] [19:19:50] <s0undt3ch>	mikko: both zmq and pyzmq are at 2.0.10
| [Wednesday 29 December 2010] [19:20:13] <mikko>	can you compile zmq with -O0 -g ?
| [Wednesday 29 December 2010] [19:20:25] <mikko>	hmm
| [Wednesday 29 December 2010] [19:20:53] <mikko>	looks like it aborts somewhere in zmq::epoll_t::loop but cant really know where/why
| [Wednesday 29 December 2010] [19:21:02] <mikko>	also testing with 2.1.0 would be helpful
| [Wednesday 29 December 2010] [19:22:34] <s0undt3ch>	mikko: well, I'd have to compile it myself and since this project is going to be deployd on a server which I'm trying to only have distro packages, I'm trying to avoid that
| [Wednesday 29 December 2010] [19:23:00] <s0undt3ch>	although 2.1.0 seems to make it easier to "attach" zmq to other event loops
| [Wednesday 29 December 2010] [19:25:19] <mikko>	s0undt3ch: does your distro provide a debug symbols package?
| [Wednesday 29 December 2010] [19:25:37] <s0undt3ch>	mikko: for what?
| [Wednesday 29 December 2010] [19:25:38] <s0undt3ch>	hmm
| [Wednesday 29 December 2010] [19:25:40] <s0undt3ch>	zmq
| [Wednesday 29 December 2010] [19:25:42] <s0undt3ch>	I think so
| [Wednesday 29 December 2010] [19:25:48] <s0undt3ch>	let me get it
| [Wednesday 29 December 2010] [19:26:58] <s0undt3ch>	mikko: however, after setting up zmq after the fork/chroot seems not to cause the issue anymore
| [Wednesday 29 December 2010] [19:30:34] <mikko>	cool
| [Wednesday 29 December 2010] [20:08:10] <s0undt3ch>	hmm
| [Wednesday 29 December 2010] [20:08:52] <s0undt3ch>	if I don't daemonize, zmq messages pass through outside the chroot, if I daemonize, they don't :\
| [Wednesday 29 December 2010] [20:17:40] <s0undt3ch>	hmm, I should not worry about chrooting right now, there' s a bunch of problems that will arrise, python libraries not found, etc, etc
| [Thursday 30 December 2010] [12:27:33] <mikko>	lestrrat: zeromq perl builds failing
| [Thursday 30 December 2010] [13:58:43] <mikko>	i to the b
| [Thursday 30 December 2010] [14:06:08] <ianbarber>	mikizzy
| [Thursday 30 December 2010] [14:07:26] <mikko>	are you back in UK?
| [Thursday 30 December 2010] [14:24:48] <Thomas_aboutus>	Hey everyone. I was wondering if someone could help me with a __stack_chk_fail problem I am having?
| [Thursday 30 December 2010] [14:26:33] <mikko>	Thomas_aboutus: what sort of problem is that?
| [Thursday 30 December 2010] [14:26:41] <mikko>	build time?
| [Thursday 30 December 2010] [14:27:43] <Thomas_aboutus>	No, it's at run time
| [Thursday 30 December 2010] [14:28:07] <Thomas_aboutus>	__stack_chk_fail is called when a stack smash is detected by stdlib (according to google).
| [Thursday 30 December 2010] [14:28:08] <mikko>	what language are you using?
| [Thursday 30 December 2010] [14:29:10] <Thomas_aboutus>	C
| [Thursday 30 December 2010] [14:29:14] <Thomas_aboutus>	The code is here: https://gist.github.com/760174
| [Thursday 30 December 2010] [14:29:19] <mikko>	are you sure you dont have stack overflow there?
| [Thursday 30 December 2010] [14:29:32] <Thomas_aboutus>	The gist description is the build command I'm using. I'm running it on mac os x
| [Thursday 30 December 2010] [14:29:41] <Thomas_aboutus>	It's possible, but if I do, I can't find it.
| [Thursday 30 December 2010] [14:29:58] <Thomas_aboutus>	I've had a couple folks here at the office take a look as well, and they are scratching their heads too.
| [Thursday 30 December 2010] [14:31:36] <Thomas_aboutus>	The basic idea of the code is a simple queue mechanism that I can use in bash scripts, etc. The error comes up when cat files to it on stdin, and passing it the "-o tcp://127.0.0.1:12345" option to have the output get pushed onto a queue. You can read off of it by kicking of another one with the -i flag set to the same value.
| [Thursday 30 December 2010] [14:34:02] <mikko>	sec
| [Thursday 30 December 2010] [14:34:06] <mikko>	let me look at the code
| [Thursday 30 December 2010] [14:35:20] <Thomas_aboutus>	Cool. I really appreciate it!
| [Thursday 30 December 2010] [14:35:22] <mikko>	line 22
| [Thursday 30 December 2010] [14:35:30] <mikko>	you init the message to size strlen(message)
| [Thursday 30 December 2010] [14:35:46] <mikko>	but wouldnt strncpy copy the terminating \0 as well?
| [Thursday 30 December 2010] [14:36:09] <mikko>	also, lines 18 and 22 dont really play well
| [Thursday 30 December 2010] [14:37:18] <Thomas_aboutus>	Good point. Okay, I'll change that and see if that helps
| [Thursday 30 December 2010] [14:37:40] <mikko>	and i think you should use memcpy rather than strcpy
| [Thursday 30 December 2010] [14:37:47] <mikko>	conceptually the data is a void *
| [Thursday 30 December 2010] [14:38:46] <mikko>	and there is zmq_msg_init_data as well
| [Thursday 30 December 2010] [14:43:30] <Thomas_aboutus>	Alright, so I changed the code (I updated the gist in case you care) and it all seems to be working now! I also had to change the reading part, but that did the trick.
| [Thursday 30 December 2010] [14:43:50] <Thomas_aboutus>	Thank you again! I just couldn't see pas the wall staring at it, and a simple bug like that just got overlooked.
| [Thursday 30 December 2010] [14:44:05] <mikko>	zmq_close(&in_socket);
| [Thursday 30 December 2010] [14:44:11] <mikko>	that doesnt look right either
| [Thursday 30 December 2010] [14:46:20] <Thomas_aboutus>	Yup, you're right. I've been killing the running processes with Ctrl-C so it never came up, but good catch.
| [Thursday 30 December 2010] [14:46:59] <Thomas_aboutus>	Thanks again!
| [Thursday 30 December 2010] [15:03:45] Notice	-NickServ- travlr__ is not a registered nickname.
| [Thursday 30 December 2010] [15:41:59] <lestrrat>	mikko: Yes, but can you change the "make test" in the test to "make test TEST_VERBOSE=1" so I can see where the tests are halting
| [Thursday 30 December 2010] [15:42:22] <mikko>	cool
| [Thursday 30 December 2010] [15:42:24] <mikko>	ill check
| [Thursday 30 December 2010] [15:42:31] <mikko>	should i change the build to do that as well?
| [Thursday 30 December 2010] [15:43:20] <mikko>	currently the daily build uses ./autobuild/run.sh
| [Thursday 30 December 2010] [15:44:57] <mikko>	https://gist.github.com/24e54efd2f763ea5bee1
| [Friday 31 December 2010] [08:56:41] <fliebel>	Hey, What would be the best way to have a many-to-many message queue, where clients publish messages to all other clients?
| [Friday 31 December 2010] [09:29:55] <sustrik>	use forwarder device in the middle
| [Friday 31 December 2010] [10:05:08] <Skaag>	what forwarder device?
| [Friday 31 December 2010] [12:58:42] <neopallium>	Skaag: When you install ZeroMQ you should get an exe called: zmq_forwarder
| [Friday 31 December 2010] [12:59:03] <neopallium>	also you can see how the forwarder would be coded in C at: http://zguide.zeromq.org/chapter:all#toc30
| [Friday 31 December 2010] [12:59:34] <neopallium>	there are other devices: zmq_queue & zmq_streamer
| [Friday 31 December 2010] [13:12:18] <Skaag>	oh that one
| [Friday 31 December 2010] [13:12:20] <Skaag>	ok
| [Friday 31 December 2010] [13:12:21] <Skaag>	:)
| [Friday 31 December 2010] [13:32:21] <neopallium>	When a custom identity is used on a socket, should it always be set before making bind()/connect() calls on that socket?
| [Friday 31 December 2010] [13:37:00] <neopallium>	ah, I found the answer at the end of this section: http://zguide.zeromq.org/chapter:all#toc37
| [Friday 31 December 2010] [16:33:24] <d4de>	Happy New Year - Egypt (^_^)