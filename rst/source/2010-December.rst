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