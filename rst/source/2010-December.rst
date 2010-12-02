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