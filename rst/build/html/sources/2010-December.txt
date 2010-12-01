===============
2010-December
===============

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