===============
2010-November
===============

| [Monday 01 November 2010] [00:23:54] <xraid>	gandhijee: http://api.zeromq.org/zmq_msg_size.html -- what binding are you using ?
| [Monday 01 November 2010] [00:26:53] <gandhijee>	xraid: C, i am using protocol buffers from google
| [Monday 01 November 2010] [00:27:27] <gandhijee>	and i am trying to figure out how to allocate the memory for the message after i get it from the sender
| [Monday 01 November 2010] [00:29:54] <gandhijee>	xraid: that was it, thanks!
| [Monday 01 November 2010] [03:27:45] <dccmx>	i have a question
| [Monday 01 November 2010] [04:28:19] <xraid>	hey whats up with the ML i am subscribed but cants send to it as i am not a member of the list ? i thought i was a member of the list if subscribed ?
| [Monday 01 November 2010] [04:33:02] <sustrik_>	xraid: what's your address?
| [Monday 01 November 2010] [04:34:51] <xraid>	zmq iprobot.com
| [Monday 01 November 2010] [04:38:34] <sustrik_>	let me see
| [Monday 01 November 2010] [04:40:25] <xraid>	hehe i tried to sub as xraid but i was banned . i then replied with a "why so" . no answer yet ...
| [Monday 01 November 2010] [04:41:52] <sustrik_>	xraid: the subscription is see is "omq at iprobot.com"
| [Monday 01 November 2010] [04:43:54] <xraid>	ahhh that explains it then ...
| [Monday 01 November 2010] [04:48:33] <xraid>	sustrik: if possible i much prefer to change omq to xraid if possible
| [Monday 01 November 2010] [04:54:15] <sustrik_>	well, do so
| [Monday 01 November 2010] [04:54:51] <sustrik_>	ah, xraid is banned?
| [Monday 01 November 2010] [04:55:34] <xraid>	huh ;-9
| [Monday 01 November 2010] [04:55:45] <xraid>	how come
| [Monday 01 November 2010] [04:56:22] <sustrik_>	hm, it's not in the ban list
| [Monday 01 November 2010] [04:56:27] <sustrik_>	???
| [Monday 01 November 2010] [04:56:40] <sustrik_>	"hehe i tried to sub as xraid but i was banned"
| [Monday 01 November 2010] [07:33:47] <Ogedei>	do I understand correctly that msg's *can* be passed between threads (as long as they are accessed in a single-threaded way), and don't have restriction that sockets have?
| [Monday 01 November 2010] [07:39:19] <sustrik>	Ogedei: yes
| [Monday 01 November 2010] [07:39:26] <sustrik>	they are plain structures
| [Monday 01 November 2010] [07:45:43] <Ogedei>	sustrik: thank you
| [Monday 01 November 2010] [07:47:37] <sustrik>	you are welcome
| [Monday 01 November 2010] [08:32:28] <mato>	sustrik: are you there?
| [Monday 01 November 2010] [08:32:50] <sustrik>	hi
| [Monday 01 November 2010] [08:33:01] <mato>	hi
| [Monday 01 November 2010] [08:33:14] <mato>	sustrik: what exactly would you like me to test with the new signaler, performance-wise?
| [Monday 01 November 2010] [08:33:33] <sustrik>	not yet, just test whether it works for you
| [Monday 01 November 2010] [08:33:47] <mato>	ah, ok
| [Monday 01 November 2010] [08:33:51] <mato>	i'll do that now then
| [Monday 01 November 2010] [08:33:55] <sustrik>	ok
| [Monday 01 November 2010] [08:35:43] <mato>	sustrik: note that my userspace (Debian lenny) is too old for eventfd, so I'll be testing the socketpair implementation
| [Monday 01 November 2010] [08:36:05] <sustrik>	goosd
| [Monday 01 November 2010] [08:36:07] <mato>	i can maybe hack something together to try and make eventfd work on my systems, but not right now
| [Monday 01 November 2010] [08:36:24] <sustrik>	just test what you have
| [Monday 01 November 2010] [09:01:19] <CIA-21>	zeromq2: 03Mikael Helbo Kjaer 07master * r0ad71f8 10/ (src/select.cpp src/select.hpp): 
| [Monday 01 November 2010] [09:01:19] <CIA-21>	zeromq2: select now uses Erase-Remove idiom for retired fds
| [Monday 01 November 2010] [09:01:19] <CIA-21>	zeromq2: Signed-off-by: Mikael Helbo Kjaer <mhk@designtech.dk> - http://bit.ly/9mdkZd
| [Monday 01 November 2010] [09:04:15] <mato>	sustrik: seems to work so far... testing with up to 600 nodes
| [Monday 01 November 2010] [09:04:29] <sustrik>	mato: the patch you've sent means that INSTALL goes to git, right?
| [Monday 01 November 2010] [09:04:50] <mato>	sustrik: the topology setup time obviously increases, and i increased the listen backlog and turned wait_before_reconnect on as usual
| [Monday 01 November 2010] [09:05:00] <mato>	sustrik: yes, that's correct, just apply the patch as is
| [Monday 01 November 2010] [09:05:14] <mato>	sustrik: it removes INSTALL from .gitignore and adds it into git, yes
| [Monday 01 November 2010] [09:05:50] <sustrik>	interestingly, git apply doesn't add the new file to the git
| [Monday 01 November 2010] [09:06:12] <mato>	probably because it's in .gitignore
| [Monday 01 November 2010] [09:06:21] <sustrik>	np
| [Monday 01 November 2010] [09:06:23] <mato>	just add it in by hand or something
| [Monday 01 November 2010] [09:06:33] <sustrik>	i did
| [Monday 01 November 2010] [09:06:37] <mato>	and don't forget to remote it from .gitignore :-)
| [Monday 01 November 2010] [09:06:53] <sustrik>	that part was applied ok
| [Monday 01 November 2010] [09:09:32] <pieterh>	sustrik: without the foreign flag, autotools will generate INSTALL automatically
| [Monday 01 November 2010] [09:10:03] <mato>	pieterh: kind of, but with the foreign flag it breaks our automatic ChangeLog generation
| [Monday 01 November 2010] [09:10:29] <pieterh>	you mean without foreign flag?
| [Monday 01 November 2010] [09:10:34] <mato>	yes, I wrote about it
| [Monday 01 November 2010] [09:10:38] <pieterh>	yes
| [Monday 01 November 2010] [09:10:47] <sustrik>	patch looks like working ok
| [Monday 01 November 2010] [09:10:50] <sustrik>	committing it
| [Monday 01 November 2010] [09:10:53] <mato>	there's a reason for that foreign flag 
| [Monday 01 November 2010] [09:10:57] <mato>	as I explained.
| [Monday 01 November 2010] [09:11:12] <pieterh>	mato: I was just explaining to sustrik that INSTALL is usually generated code
| [Monday 01 November 2010] [09:11:22] <sustrik>	it used to be
| [Monday 01 November 2010] [09:11:24] <mato>	no, it's stuck in as a template if it's not there
| [Monday 01 November 2010] [09:11:34] <sustrik>	not it's not
| [Monday 01 November 2010] [09:11:39] <pieterh>	we were looking for this yesterday but I couldn't see where the foreign flag was being set
| [Monday 01 November 2010] [09:11:42] <sustrik>	i don't care much
| [Monday 01 November 2010] [09:12:01] <mato>	whatever, the INSTALL file will eventually contain custom content anyway
| [Monday 01 November 2010] [09:12:08] <mato>	so it'll be in git anyway
| [Monday 01 November 2010] [09:12:12] <pieterh>	presumably, yes
| [Monday 01 November 2010] [09:12:51] <CIA-21>	zeromq2: 03Martin Lucina 07maint * reb83678 10/ (.gitignore INSTALL): 
| [Monday 01 November 2010] [09:12:51] <CIA-21>	zeromq2: Add INSTALL to Git, thus making it a normal file
| [Monday 01 November 2010] [09:12:51] <CIA-21>	zeromq2: INSTALL gets added in somewhat magically by automake, or not. Adding it into
| [Monday 01 November 2010] [09:12:51] <CIA-21>	zeromq2: Git ensures it's always included in the distribution.
| [Monday 01 November 2010] [09:12:51] <CIA-21>	zeromq2: Signed-off-by: Martin Lucina <mato@kotelna.sk> - http://bit.ly/bCAWcw
| [Monday 01 November 2010] [09:17:50] <sustrik>	mato, pieter: for development releases i propose we won't upload the man pages to the website
| [Monday 01 November 2010] [09:17:59] <sustrik>	they are included in the package
| [Monday 01 November 2010] [09:18:12] <mato>	sustrik: dunno, maybe... or we have two sets on the website
| [Monday 01 November 2010] [09:18:16] <sustrik>	and it would confuse users using the stable release
| [Monday 01 November 2010] [09:18:16] <mato>	to be determined
| [Monday 01 November 2010] [09:18:27] <sustrik>	it there are 2 versions of docs on the website
| [Monday 01 November 2010] [09:18:32] <pieterh>	to be determined
| [Monday 01 November 2010] [09:18:42] <pieterh>	how does, e.g. APR do this?  How does any project do this?
| [Monday 01 November 2010] [09:18:57] <sustrik>	no idea
| [Monday 01 November 2010] [09:19:07] <sustrik>	do they have 'unstable' releases?
| [Monday 01 November 2010] [09:19:10] <pieterh>	sure
| [Monday 01 November 2010] [09:19:11] <mato>	yes
| [Monday 01 November 2010] [09:19:17] <pieterh>	every serious project has
| [Monday 01 November 2010] [09:19:19] <mato>	and they have multiple versions of the docs uploaded
| [Monday 01 November 2010] [09:19:22] <mato>	clearly marked
| [Monday 01 November 2010] [09:19:22] <pieterh>	indeed
| [Monday 01 November 2010] [09:19:28] <pieterh>	it's just code at a URL
| [Monday 01 November 2010] [09:19:35] <mato>	some people will of course not read the clear marking and get confused anyway, too bad
| [Monday 01 November 2010] [09:19:38] <pieterh>	indeed
| [Monday 01 November 2010] [09:19:42] <sustrik>	ok
| [Monday 01 November 2010] [09:21:04] <mato>	sustrik: ok, so what are we going to do with the new signaler?
| [Monday 01 November 2010] [09:21:30] <mato>	sustrik: it seems to work as far as I can tell, but as I say, I've only tested on a single platform and have not done any serious performance tests...
| [Monday 01 November 2010] [09:21:53] <CIA-21>	zeromq2: 03Martin Lucina 07master * reb83678 10/ (.gitignore INSTALL): 
| [Monday 01 November 2010] [09:21:53] <CIA-21>	zeromq2: Add INSTALL to Git, thus making it a normal file
| [Monday 01 November 2010] [09:21:53] <CIA-21>	zeromq2: INSTALL gets added in somewhat magically by automake, or not. Adding it into
| [Monday 01 November 2010] [09:21:53] <CIA-21>	zeromq2: Git ensures it's always included in the distribution.
| [Monday 01 November 2010] [09:21:53] <CIA-21>	zeromq2: Signed-off-by: Martin Lucina <mato@kotelna.sk> - http://bit.ly/bCAWcw
| [Monday 01 November 2010] [09:21:53] <CIA-21>	zeromq2: 03Martin Sustrik 07master * rdbcd382 10/ (.gitignore INSTALL): 
| [Monday 01 November 2010] [09:21:55] <CIA-21>	zeromq2: Merge branch 'maint'
| [Monday 01 November 2010] [09:21:55] <CIA-21>	zeromq2: * maint:
| [Monday 01 November 2010] [09:21:55] <CIA-21>	zeromq2:  Add INSTALL to Git, thus making it a normal file - http://bit.ly/aK31FB
| [Monday 01 November 2010] [09:22:05] <sustrik>	mato: well, it's kind of complex
| [Monday 01 November 2010] [09:22:19] <sustrik>	maybe you want just to patch your version as for now?
| [Monday 01 November 2010] [09:22:26] <mato>	why?
| [Monday 01 November 2010] [09:22:32] <sustrik>	time pressure?
| [Monday 01 November 2010] [09:22:32] <mato>	that all gets very confusing rapidly
| [Monday 01 November 2010] [09:22:41] <mato>	and i'd like to avoid extra patches if at all possible...
| [Monday 01 November 2010] [09:22:51] <sustrik>	so, for starters we need win32 implementation of event
| [Monday 01 November 2010] [09:23:05] <sustrik>	i've only did linux one
| [Monday 01 November 2010] [09:23:20] <sustrik>	also, i've merged the hp-ux/aix code with linux code
| [Monday 01 November 2010] [09:23:26] <mato>	right, i saw that
| [Monday 01 November 2010] [09:23:37] <sustrik>	hopefully, brett will test that part
| [Monday 01 November 2010] [09:23:43] <mato>	that doesn't matter too much, if hp-ux/aix breaks then i'd expect those users to speak up
| [Monday 01 November 2010] [09:23:54] <mato>	we cannot obviously test on platforms we don't have
| [Monday 01 November 2010] [09:24:05] <mato>	and hp-ux/aix are a minority platform anyway
| [Monday 01 November 2010] [09:24:08] <sustrik>	so, we need win implementation
| [Monday 01 November 2010] [09:24:15] <mato>	right...
| [Monday 01 November 2010] [09:24:20] <sustrik>	test the eventfd implementation
| [Monday 01 November 2010] [09:24:35] <sustrik>	i've did a bit, but maybe running some larger payload would be good
| [Monday 01 November 2010] [09:24:41] <sustrik>	then we need to optimise it
| [Monday 01 November 2010] [09:25:17] <sustrik>	will you do the win32 part?
| [Monday 01 November 2010] [09:26:04] <mato>	i could do that, yes
| [Monday 01 November 2010] [09:26:58] <sustrik>	thx
| [Monday 01 November 2010] [09:28:51] <sustrik>	mato: btw, i copied your release process here:
| [Monday 01 November 2010] [09:28:52] <sustrik>	http://www.zeromq.org/docs:procedures#toc7
| [Monday 01 November 2010] [09:29:29] <mato>	sustrik: oh, good
| [Monday 01 November 2010] [09:29:55] <sustrik>	it's not perfect, but at least it's documented
| [Monday 01 November 2010] [09:30:04] <mato>	yup, good
| [Monday 01 November 2010] [09:34:33] <pieterh>	sustrik: very nice, we were missing this
| [Monday 01 November 2010] [10:34:55] <mato>	sustrik_: hmm, event_t::wait() is supposed to busy-loop?
| [Monday 01 November 2010] [10:35:28] <mato>	sustrik_: ah, sorry, i misread the code
| [Monday 01 November 2010] [11:10:21] <mato>	sustrik_: here?
| [Monday 01 November 2010] [11:25:51] <mato>	sustrik_: um, the signaler has always been ignoring EINTR as far as I can tell...
| [Monday 01 November 2010] [11:26:08] <mato>	sustrik_: so it would seem that is the *correct* behaviour
| [Monday 01 November 2010] [11:26:25] <mato>	sustrik_: and the do { recv() } while() loop has to stay for POSIX platforms
| [Monday 01 November 2010] [11:26:39] <sustrik_>	hm
| [Monday 01 November 2010] [11:26:58] <sustrik_>	ignoring = looping?
| [Monday 01 November 2010] [11:27:19] <mato>	yes
| [Monday 01 November 2010] [11:27:34] <sustrik_>	even blocking read?
| [Monday 01 November 2010] [11:27:36] <sustrik_>	let me see
| [Monday 01 November 2010] [11:27:41] <mato>	ah, hang on
| [Monday 01 November 2010] [11:27:51] <mato>	the different implementations are a mess...
| [Monday 01 November 2010] [11:28:06] <sustrik_>	    if (nbytes == -1 && (errno == EAGAIN || errno == EINTR))
| [Monday 01 November 2010] [11:28:07] <sustrik_>	        return -1;
| [Monday 01 November 2010] [11:28:23] <mato>	yeah, because that implementation uses MSG_DONTWAIT
| [Monday 01 November 2010] [11:28:32] <mato>	which is specific to god knows what platforms
| [Monday 01 November 2010] [11:28:44] <sustrik_>	yep
| [Monday 01 November 2010] [11:28:58] <sustrik_>	we don't need that now so we can drop it
| [Monday 01 November 2010] [11:29:24] <sustrik_>	in any case if (EINTR) return -1
| [Monday 01 November 2010] [11:29:47] <mato>	yeah but your event_t has no notion of returning anything (all the methods are void)
| [Monday 01 November 2010] [11:29:58] <mato>	i'm just wondering how that is supposed to work...
| [Monday 01 November 2010] [11:30:19] <sustrik_>	we'll have to add the reurn codes then
| [Monday 01 November 2010] [11:30:42] <sustrik_>	the idea is that application thread exits on EINTR
| [Monday 01 November 2010] [11:30:56] <sustrik_>	while I/O thread restarts the operation
| [Monday 01 November 2010] [11:31:15] <mato>	so that means that signaler_t::recv() must return EINTR if the underlying blocking call is interrupted, right?
| [Monday 01 November 2010] [11:31:26] <sustrik_>	tes
| [Monday 01 November 2010] [11:31:31] <sustrik_>	yes
| [Monday 01 November 2010] [11:31:59] <sustrik_>	actually, i am not sure EINTR can even happen in I/O thread
| [Monday 01 November 2010] [11:32:02] <mato>	so both event_t::wait() and event_t::reset() need to be able to return -1 and errno=EINTR, right?
| [Monday 01 November 2010] [11:32:12] <sustrik_>	given that signals are switched off in those threads
| [Monday 01 November 2010] [11:32:29] <mato>	good question, no idea
| [Monday 01 November 2010] [11:32:30] <sustrik_>	even set can return EINTR
| [Monday 01 November 2010] [11:32:53] <mato>	if ::send() is interrupted?
| [Monday 01 November 2010] [11:32:57] <sustrik_>	yes
| [Monday 01 November 2010] [11:33:07] <mato>	right, so all of those need to be int
| [Monday 01 November 2010] [11:33:11] <sustrik_>	ack
| [Monday 01 November 2010] [11:33:16] <mato>	i will change that
| [Monday 01 November 2010] [11:36:16] <sustrik_>	ok, I/O thread handles EINTR correctly (restarts the operation)
| [Monday 01 November 2010] [11:37:16] <mato>	ok, but what about signaler_t::send()?
| [Monday 01 November 2010] [11:37:22] <mato>	that method does not return anything...
| [Monday 01 November 2010] [11:37:38] <mato>	so what is it supposed to do if event_t::set() returns EINTR? restart it?
| [Monday 01 November 2010] [11:39:48] <sustrik_>	hmm
| [Monday 01 November 2010] [11:40:06] <sustrik_>	the problem is that by restarting you loose the signal
| [Monday 01 November 2010] [11:40:37] <sustrik_>	but the signal handling is not 100% efficient anyway
| [Monday 01 November 2010] [11:40:47] <sustrik_>	so yes, we can just restart the send
| [Monday 01 November 2010] [11:41:27] <pieterh>	sustrik: you have a second?
| [Monday 01 November 2010] [11:41:32] <pieterh>	question on code structure
| [Monday 01 November 2010] [11:41:56] <pieterh>	why does select.cpp do a bunch of stuff for windows, and then invoke select.hpp that does the same?
| [Monday 01 November 2010] [11:42:17] <pieterh>	afaics select.hpp isn't used by any other code
| [Monday 01 November 2010] [11:42:48] <sustrik_>	pieterh: historic reasons
| [Monday 01 November 2010] [11:43:04] <pieterh>	? 
| [Monday 01 November 2010] [11:43:14] <pieterh>	i mean, is this by design or just bogus?
| [Monday 01 November 2010] [11:43:19] <sustrik_>	the poll algo classes should be refactored
| [Monday 01 November 2010] [11:43:24] <sustrik_>	bogus
| [Monday 01 November 2010] [11:43:46] <pieterh>	ok... cause there's duplicate code but it's not quite the same in both cases
| [Monday 01 November 2010] [11:43:54] <pieterh>	actually it's worse, there's also windows.hpp that does the same again
| [Monday 01 November 2010] [11:44:26] <sustrik_>	i know, but it's hard to change without breaking anything
| [Monday 01 November 2010] [11:44:27] <mato>	there is much historical weird stuff to clean up wrt windows.wpp and the bits that depend on it
| [Monday 01 November 2010] [11:44:43] <mato>	but, as sustrik says, it's all pretty fragile, so if it ain't broke, don't fix it
| [Monday 01 November 2010] [11:44:46] <pieterh>	well, select.hpp is only used in one place
| [Monday 01 November 2010] [11:44:48] <pieterh>	and it is broken
| [Monday 01 November 2010] [11:45:00] <pieterh>	and I do intend to fix it, the FD_SETSIZE issue has been there for years and should go
| [Monday 01 November 2010] [11:45:16] <sustrik_>	sure, send the patch
| [Monday 01 November 2010] [11:45:22] <mato>	oh dear, not that again
| [Monday 01 November 2010] [11:45:36] <pieterh>	well, my question is whether you really want me to 'fix' three places that are all actually the same?
| [Monday 01 November 2010] [11:45:39] <mato>	FD_SETSIZE is a problem because zmq.h depends on winsock for SOCKET *
| [Monday 01 November 2010] [11:45:47] <pieterh>	mato: please
| [Monday 01 November 2010] [11:45:53] <pieterh>	we do understand the case pretty well
| [Monday 01 November 2010] [11:46:07] <pieterh>	the problem here is just 0MQ's code, not the fix in question
| [Monday 01 November 2010] [11:46:12] <mato>	sure
| [Monday 01 November 2010] [11:46:15] <pieterh>	winsock.h is included 4 times
| [Monday 01 November 2010] [11:46:20] <pieterh>	that is the problem
| [Monday 01 November 2010] [11:46:30] <sustrik_>	i don't know about FD_SETSIZE, but if there's a bug in select.cpp, just fix it and send the patch
| [Monday 01 November 2010] [11:46:34] <mato>	if you can make all the code work *correctly* *and* avoid redefining an *application's* view of FD_SETSIZE, go for it
| [Monday 01 November 2010] [11:46:47] <pieterh>	mato: we've been over this
| [Monday 01 November 2010] [11:47:06] <pieterh>	code that calls a library must defacto use that library's value for FD_SETSIZE
| [Monday 01 November 2010] [11:47:15] <mato>	pieterh: I will not accept any patch that redefines FD_SETSIZE of an *application* including zmq.h
| [Monday 01 November 2010] [11:47:22] <mato>	for reasons that I have explained
| [Monday 01 November 2010] [11:47:30] <pieterh>	you've not explained, and/or have not understood
| [Monday 01 November 2010] [11:47:43] <mato>	zmq.h is the *API* header
| [Monday 01 November 2010] [11:47:51] <pieterh>	every library that wraps select() must define a value for FD_SETSIZE
| [Monday 01 November 2010] [11:47:53] <mato>	it has no business changing the *application's* view of FD_SETSIZE
| [Monday 01 November 2010] [11:48:00] <mato>	yes, sure
| [Monday 01 November 2010] [11:48:03] <pieterh>	lll
| [Monday 01 November 2010] [11:48:08] <mato>	i have no problem with that
| [Monday 01 November 2010] [11:48:10] <pieterh>	it changes the API's definition
| [Monday 01 November 2010] [11:48:21] <pieterh>	this is standard stuff
| [Monday 01 November 2010] [11:48:31] <pieterh>	now, including zmq.h magically sets FD_SETSIZE to 64
| [Monday 01 November 2010] [11:48:40] <pieterh>	which is not a feature, but a bug
| [Monday 01 November 2010] [11:48:53] <mato>	no it doesn't, it leaves it at whatever the default is
| [Monday 01 November 2010] [11:48:57] <pieterh>	no it doesn't
| [Monday 01 November 2010] [11:49:02] <pieterh>	winsock.h defines it
| [Monday 01 November 2010] [11:49:03] <mato>	bah
| [Monday 01 November 2010] [11:49:05] <pieterh>	unless it's already defined
| [Monday 01 November 2010] [11:49:10] <mato>	exactly
| [Monday 01 November 2010] [11:49:21] <pieterh>	well... did you think I'd ignore a previous definition?
| [Monday 01 November 2010] [11:49:24] <pieterh>	/  Raise max sockets from default of 64 to more usable value
| [Monday 01 November 2010] [11:49:24] <pieterh>	/  Must be consistent in any code that shares FD sets
| [Monday 01 November 2010] [11:49:24] <pieterh>	#ifndef FD_SETSIZE
| [Monday 01 November 2010] [11:49:24] <pieterh>	#define FD_SETSIZE   1024
| [Monday 01 November 2010] [11:49:24] <pieterh>	#endif
| [Monday 01 November 2010] [11:49:32] <sustrik_>	afaiu, the problem is that 0mq and the application have to have same value of FD_SETSIZE to work well
| [Monday 01 November 2010] [11:49:40] <sustrik_>	right?
| [Monday 01 November 2010] [11:49:45] <pieterh>	it's just an array max for the select call
| [Monday 01 November 2010] [11:49:47] <mato>	no, i don't think so
| [Monday 01 November 2010] [11:50:03] <pieterh>	so any code that shares fdsets must agree on the max
| [Monday 01 November 2010] [11:50:04] <mato>	sustrik_: libzmq.dll's FD_SETSIZE AFAICT has nothing to do with the app's FD_SETSIZE
| [Monday 01 November 2010] [11:50:20] <pieterh>	mato: there is no 'app's FD_SETSIZE'
| [Monday 01 November 2010] [11:50:33] <mato>	huh?
| [Monday 01 November 2010] [11:50:33] <pieterh>	every select call has an FD_SETSIZE
| [Monday 01 November 2010] [11:50:39] <pieterh>	it's not per application or per binary
| [Monday 01 November 2010] [11:50:43] <pieterh>	it's per select() call...
| [Monday 01 November 2010] [11:50:45] <mato>	sure
| [Monday 01 November 2010] [11:50:47] <mato>	my point is...
| [Monday 01 November 2010] [11:51:02] <mato>	what if you have an existing application which is mixing normal sockets and zmq code
| [Monday 01 November 2010] [11:51:15] <mato>	including zmq.h should not go and magically change that app's FD_SETSIZE...
| [Monday 01 November 2010] [11:51:21] <pieterh>	(a) that is 1% of the case where as 'normal 0MQ apps' are 99% of the case
| [Monday 01 November 2010] [11:51:35] <pieterh>	(b) you can set your own FD_SETSIZE beforehand
| [Monday 01 November 2010] [11:51:45] <pieterh>	(c) you need to recompile ALL your code then to match
| [Monday 01 November 2010] [11:51:47] <pieterh>	including 0MQ
| [Monday 01 November 2010] [11:51:52] <pieterh>	that's pretty straight-forward
| [Monday 01 November 2010] [11:52:02] <mato>	does it really work that way? (c) included?
| [Monday 01 November 2010] [11:52:05] <pieterh>	what is not acceptable is "install 0MQ, build app, watch it break at 64 sockets'
| [Monday 01 November 2010] [11:52:08] <pieterh>	yes mato
| [Monday 01 November 2010] [11:52:17] <pieterh>	define the macro in your project, rebuild
| [Monday 01 November 2010] [11:52:19] <pieterh>	period
| [Monday 01 November 2010] [11:52:29] <pieterh>	i've been doing this for 15 years or so with Xitami / SFL /...
| [Monday 01 November 2010] [11:52:48] <mato>	ok, ok, i believe you
| [Monday 01 November 2010] [11:53:04] <mato>	i was just trying to avoid zmq.h doing anything "surprising"
| [Monday 01 November 2010] [11:53:08] <pieterh>	the _only_ difficulty here is that 0MQ includes winsock 4 times in different places
| [Monday 01 November 2010] [11:53:13] <pieterh>	which is... less than elegant
| [Monday 01 November 2010] [11:53:19] <mato>	yes, that needs to be refactored
| [Monday 01 November 2010] [11:53:35] <mato>	oh
| [Monday 01 November 2010] [11:53:42] <mato>	there is one other complexity
| [Monday 01 November 2010] [11:53:48] <mato>	when building zmq on windows
| [Monday 01 November 2010] [11:53:51] <pieterh>	yes?
| [Monday 01 November 2010] [11:54:10] <mato>	FD_SETSIZE must be defined correctly the 1st time winsock.h is included in the app
| [Monday 01 November 2010] [11:54:18] <pieterh>	there is no 'app'
| [Monday 01 November 2010] [11:54:21] <mato>	which for zmq basically means changing all those places 
| [Monday 01 November 2010] [11:54:23] <pieterh>	you keep speaking of 'apps'
| [Monday 01 November 2010] [11:54:34] <mato>	i'm sorry, zeromq *library*
| [Monday 01 November 2010] [11:54:38] <pieterh>	every source file
| [Monday 01 November 2010] [11:54:46] <pieterh>	is compiled with a certain value for FD_SETSIZE
| [Monday 01 November 2010] [11:54:54] <pieterh>	winsock.h is included 4 times in different places
| [Monday 01 November 2010] [11:55:09] <pieterh>	some are obviously redundant (select.cpp, select.hpp)
| [Monday 01 November 2010] [11:55:12] <pieterh>	others are less so
| [Monday 01 November 2010] [11:55:29] <sustrik_>	can someone explain what FD_SETSIZE actually affects? if every call to select can have different FD_SETSIZE why not define it to 1024 in our cpp files and leave the header alone?
| [Monday 01 November 2010] [11:55:45] <pieterh>	sustrik_, it tells the win32 library how large the fdset arrays are
| [Monday 01 November 2010] [11:56:02] <sustrik_>	and can it differ throughout the program?
| [Monday 01 November 2010] [11:56:08] <mato>	no one knows :-)
| [Monday 01 November 2010] [11:56:11] <pieterh>	if you include winsock.h or winsock2.h without defining this, it sets a value of 64
| [Monday 01 November 2010] [11:56:23] <pieterh>	so each source file can have different values compiled into it
| [Monday 01 November 2010] [11:56:39] <pieterh>	winsock.h passes the macro value to the win32 functions
| [Monday 01 November 2010] [11:56:52] <pieterh>	so it can differ in every call to select()
| [Monday 01 November 2010] [11:57:05] <pieterh>	does that make sense?
| [Monday 01 November 2010] [11:57:23] <mato>	if that's how it actually works, then yes, i think so
| [Monday 01 November 2010] [11:57:24] <sustrik_>	then why not go for defining FD_SETSIZE only for select.cpp and zmq.cpp?
| [Monday 01 November 2010] [11:57:37] <pieterh>	sustrik: if those are the only places you call select(), yes
| [Monday 01 November 2010] [11:57:45] <pieterh>	in fact only in select.cpp then
| [Monday 01 November 2010] [11:57:52] <mato>	zmq.cpp also calls select()
| [Monday 01 November 2010] [11:57:55] <sustrik_>	yes
| [Monday 01 November 2010] [11:57:57] <pieterh>	right
| [Monday 01 November 2010] [11:57:59] <mato>	for the zmq_poll() implementation
| [Monday 01 November 2010] [11:58:11] 	 * pieterh doesn't understand why this is not abstracted
| [Monday 01 November 2010] [11:58:39] <pieterh>	ok, i'll make a patch and ask for volunteers to test that under win32
| [Monday 01 November 2010] [11:58:46] <pieterh>	if it's stable we can include it
| [Monday 01 November 2010] [11:58:53] <pieterh>	zmq.h and select.cpp only then
| [Monday 01 November 2010] [11:59:08] <mato>	zmq.h?
| [Monday 01 November 2010] [11:59:09] <sustrik_>	noo
| [Monday 01 November 2010] [11:59:12] <mato>	zmq.cpp you mean
| [Monday 01 November 2010] [11:59:51] <pieterh>	well, it has to be defined _before_ including winsock.h
| [Monday 01 November 2010] [11:59:57] <pieterh>	that happens in zmq.h
| [Monday 01 November 2010] [11:59:57] <mato>	yes, so?
| [Monday 01 November 2010] [12:00:08] <pieterh>	so you want me to add this code to the very start of zmq.cpp?
| [Monday 01 November 2010] [12:00:11] <pieterh>	wow
| [Monday 01 November 2010] [12:00:12] <mato>	then put the #define in zmq.cpp before it include anything
| [Monday 01 November 2010] [12:00:13] <mato>	yes
| [Monday 01 November 2010] [12:00:15] <pieterh>	no way
| [Monday 01 November 2010] [12:00:23] <pieterh>	that's so ugly
| [Monday 01 November 2010] [12:00:33] <mato>	the whole FD_SETSIZE thing is ugly
| [Monday 01 November 2010] [12:00:35] <mato>	not our fault
| [Monday 01 November 2010] [12:00:38] <pieterh>	'here's our global header file but wait, some magic stuff happens before that!'
| [Monday 01 November 2010] [12:00:48] <pieterh>	no, it's the fault of this code structure
| [Monday 01 November 2010] [12:00:54] <pieterh>	it should be done in windows.hpp
| [Monday 01 November 2010] [12:01:10] <pieterh>	or somewhere for 'include all random windows stuff'
| [Monday 01 November 2010] [12:01:19] <mato>	yes, but not in zmq.h
| [Monday 01 November 2010] [12:01:29] <mato>	that's the only point i'm making, pieter
| [Monday 01 November 2010] [12:01:37] <mato>	do it any way you like, just not in zmq.h please
| [Monday 01 November 2010] [12:01:49] <sustrik_>	windows.hpp is actually a nice place to set it
| [Monday 01 November 2010] [12:01:51] <mato>	if you clean up the mess with windows.hpp while you're at it, so much the better
| [Monday 01 November 2010] [12:01:52] <pieterh>	you're not making a point, you're just imposing an arbitrary limitation
| [Monday 01 November 2010] [12:02:00] <mato>	it's not arbitrary
| [Monday 01 November 2010] [12:02:01] <sustrik_>	as it's included from all 0mq compilation units
| [Monday 01 November 2010] [12:02:04] <sustrik_>	but not from zmq.h
| [Monday 01 November 2010] [12:02:06] <pieterh>	it should be _consistent_ for the whole library
| [Monday 01 November 2010] [12:02:15] <pieterh>	and it should be easy to override from the project file
| [Monday 01 November 2010] [12:02:16] <pieterh>	period
| [Monday 01 November 2010] [12:02:44] <pieterh>	look, I'm willing to spend some effort cleaning this up, but not to navigate random opinions
| [Monday 01 November 2010] [12:02:47] <mato>	sustrik_: do you understand why making the change in zmq.h seems like a bad idea? or am I alone in this?
| [Monday 01 November 2010] [12:02:50] <pieterh>	the windows build of 0MQ is broken
| [Monday 01 November 2010] [12:02:55] <sustrik_>	mato: i do
| [Monday 01 November 2010] [12:02:55] <pieterh>	64 sockets is not realistic, period
| [Monday 01 November 2010] [12:03:05] <pieterh>	you are both wrong, then
| [Monday 01 November 2010] [12:03:14] <sustrik_>	pieterh: try putting it into windows.hpp, that should work ok
| [Monday 01 November 2010] [12:03:20] <pieterh>	any application that mixes tcp and 0mq must in any case define a FD_SETSIZE
| [Monday 01 November 2010] [12:03:23] <pieterh>	externally
| [Monday 01 November 2010] [12:03:26] <pieterh>	in its project file
| [Monday 01 November 2010] [12:03:39] <pieterh>	this applies to any library that wraps select()
| [Monday 01 November 2010] [12:03:55] <pieterh>	sustrik: nope, windows.hpp is not used by select.cpp for instance
| [Monday 01 November 2010] [12:04:18] <sustrik_>	it should
| [Monday 01 November 2010] [12:04:22] <pieterh>	yeah, it should
| [Monday 01 November 2010] [12:04:29] <pieterh>	hence my original question about the code structure
| [Monday 01 November 2010] [12:04:41] <pieterh>	the platform code shouldn't be spread out like that IMO
| [Monday 01 November 2010] [12:04:52] <sustrik_>	historic reasons
| [Monday 01 November 2010] [12:04:58] <pieterh>	sorry, poor excuse :-)
| [Monday 01 November 2010] [12:05:06] <sustrik_>	well, fix it then
| [Monday 01 November 2010] [12:05:08] <mato>	exactly
| [Monday 01 November 2010] [12:05:12] <mato>	stop bitching about it
| [Monday 01 November 2010] [12:05:14] <mato>	and fix it
| [Monday 01 November 2010] [12:05:21] <pieterh>	that's all I was asking for
| [Monday 01 November 2010] [12:05:39] <mato>	all i'm saying, and sustrik is agreeing, is don't change FD_SETSIZE in zmq.h
| [Monday 01 November 2010] [12:05:46] <mato>	and all of this *can* be done without that
| [Monday 01 November 2010] [12:05:56] <pieterh>	i'm curious to see how you will do that, mato
| [Monday 01 November 2010] [12:06:21] <mato>	?
| [Monday 01 November 2010] [12:06:27] <pieterh>	since zmq.h includes winsock.h
| [Monday 01 November 2010] [12:06:34] <pieterh>	well, since you know best, I step back
| [Monday 01 November 2010] [12:06:45] <mato>	yes, so you make sure FD_SETSIZE is defined before zmq.h is included in the relevant places
| [Monday 01 November 2010] [12:07:05] <pieterh>	that IMO makes the code dirtier and I won't do that, sorry
| [Monday 01 November 2010] [12:07:16] <pieterh>	zmq.h is the system-wide header file
| [Monday 01 November 2010] [12:07:23] <sustrik_>	afaiu, each compilation unit has to have a consistent value of FD_SETSIZE
| [Monday 01 November 2010] [12:07:28] <mato>	it's not the syste-wide header file
| [Monday 01 November 2010] [12:07:37] <mato>	it's the exported API header file
| [Monday 01 November 2010] [12:07:41] <sustrik_>	but there's no requirement that different compilation units have to have the same value
| [Monday 01 November 2010] [12:07:47] <pieterh>	then it should absolutely not call winsock.h
| [Monday 01 November 2010] [12:07:58] <pieterh>	because today it effectively sets FD_SETSIZE to 64
| [Monday 01 November 2010] [12:08:00] <pieterh>	don't you get this?
| [Monday 01 November 2010] [12:08:12] <pieterh>	zmq.h already makes a mess for any app
| [Monday 01 November 2010] [12:08:18] <mato>	*that* is an entirely different problem
| [Monday 01 November 2010] [12:08:29] <pieterh>	?
| [Monday 01 November 2010] [12:08:51] <mato>	the reason it's included winsock.h is...
| [Monday 01 November 2010] [12:09:09] <mato>	that the zmq_pollitem_t definition needs a type for "OS sockets"
| [Monday 01 November 2010] [12:09:19] <mato>	so it needs access to SOCKET
| [Monday 01 November 2010] [12:09:29] <sustrik_>	yeah, that's a really annoying problem
| [Monday 01 November 2010] [12:09:37] <pieterh>	it sets FD_SETSIZE to 64
| [Monday 01 November 2010] [12:09:41] <sustrik_>	in reality SOCKET is void*
| [Monday 01 November 2010] [12:09:52] <pieterh>	that is a serious fault
| [Monday 01 November 2010] [12:09:58] <pieterh>	i'm proposing to make it a less serious faulyt
| [Monday 01 November 2010] [12:09:59] <pieterh>	*fault
| [Monday 01 November 2010] [12:10:12] <mato>	no you're not
| [Monday 01 November 2010] [12:10:25] <sustrik_>	what about using void* instead of SOCKET
| [Monday 01 November 2010] [12:10:37] <mato>	well, would that work?
| [Monday 01 November 2010] [12:10:45] <sustrik_>	it's not nice but all the other alternatives are even worse
| [Monday 01 November 2010] [12:10:49] <pieterh>	"zmq.h should not magically go and change the app's FD_SETSIZE":
| [Monday 01 November 2010] [12:10:57] <pieterh>	but that's what it does today
| [Monday 01 November 2010] [12:11:00] <sustrik_>	i think if holds for all win platforms
| [Monday 01 November 2010] [12:11:06] <sustrik_>	hard to check though
| [Monday 01 November 2010] [12:11:14] <mato>	well, there's an easy way to check actually
| [Monday 01 November 2010] [12:11:16] <pieterh>	look, there are several problems here
| [Monday 01 November 2010] [12:11:22] <sustrik_>	mato: how?
| [Monday 01 November 2010] [12:11:24] <pieterh>	- windows code is spread out through multiple header files
| [Monday 01 November 2010] [12:11:32] <mato>	sustrik_: in zmq_init, assert (sizeof (SOCKET) == sizeof (void *))
| [Monday 01 November 2010] [12:11:35] <pieterh>	- select() is used with bogus limit of 64
| [Monday 01 November 2010] [12:11:43] <sustrik_>	:)
| [Monday 01 November 2010] [12:11:47] <mato>	sustrik_: that would do for starters...
| [Monday 01 November 2010] [12:11:59] <sustrik_>	ok, that solves the problem, no?
| [Monday 01 November 2010] [12:12:10] <mato>	it would seem so, yes
| [Monday 01 November 2010] [12:12:17] <pieterh>	yes, that solves zmq.h
| [Monday 01 November 2010] [12:12:49] <sustrik_>	when we have that
| [Monday 01 November 2010] [12:12:57] <pieterh>	if zmq.h no longer whacks FD_SETSIZE then it can be safely set per source file where needed
| [Monday 01 November 2010] [12:13:00] <mato>	sustrik_: in fact, you can add a compile-time dummy check
| [Monday 01 November 2010] [12:13:04] <mato>	sustrik_: even better
| [Monday 01 November 2010] [12:13:17] <sustrik_>	good
| [Monday 01 November 2010] [12:13:19] <mato>	sustrik_: SOCKET foo; void *bar; bar = foo
| [Monday 01 November 2010] [12:13:23] <mato>	sustrik_: or something like that
| [Monday 01 November 2010] [12:13:42] <sustrik_>	ok, however, let's do this after 2.1.0 release
| [Monday 01 November 2010] [12:14:06] <sustrik_>	it can break 0mq on some win systems (if we are wrong about void*)
| [Monday 01 November 2010] [12:14:15] <mato>	2.1.0 is development
| [Monday 01 November 2010] [12:14:20] <mato>	it shoudn't matter too much
| [Monday 01 November 2010] [12:14:21] <sustrik_>	thus it would be good to have one functional dev release
| [Monday 01 November 2010] [12:14:36] <mato>	up to you
| [Monday 01 November 2010] [12:14:51] <mato>	anyway, looks like we have a sensible solution
| [Monday 01 November 2010] [12:14:57] 	 * mato gets back to the signaler
| [Monday 01 November 2010] [12:15:18] <sustrik_>	pieter: you can fix it on a topic branch
| [Monday 01 November 2010] [12:15:30] <sustrik_>	we can merge it in after 2.1.0 is out
| [Monday 01 November 2010] [12:17:21] <pieterh>	sustrik_, sure
| [Monday 01 November 2010] [12:17:32] <pieterh>	I submit a patch, do what you like with it :-)
| [Monday 01 November 2010] [12:20:01] <pieterh>	please tell me when you've removed the winsock.h call from zmq.h, then I'll make the change
| [Monday 01 November 2010] [12:23:38] <mato>	sustrik_: fd_t is the canonical type used internally for sockets, right?
| [Monday 01 November 2010] [12:23:50] <sustrik_>	yes
| [Monday 01 November 2010] [12:23:50] <mato>	sustrik_: i.e. it's SOCKET on windows and int everywhere else
| [Monday 01 November 2010] [12:29:53] <sustrik_>	mato: in zmq.h we are using _WIN32 to find out whether we are on windows or somewhere else
| [Monday 01 November 2010] [12:30:12] <sustrik_>	does that meen windows.h has to be included prior to zmq.h?
| [Monday 01 November 2010] [12:30:27] <mato>	sustrik_: _WIN32 should be defined by the compiler
| [Monday 01 November 2010] [12:30:33] <sustrik_>	ok
| [Monday 01 November 2010] [12:30:44] <sustrik_>	what abour win64 btw?
| [Monday 01 November 2010] [12:30:49] <mato>	i hope so anyway, otherwise it's totally braindead
| [Monday 01 November 2010] [12:30:57] <mato>	_WIN32 just means "Win32 API"
| [Monday 01 November 2010] [12:31:02] <sustrik_>	i see
| [Monday 01 November 2010] [12:31:04] <mato>	irrelevant to x64 target
| [Monday 01 November 2010] [12:35:09] <sustrik_>	ok, i've checked it, MSVC does define _WIN32
| [Monday 01 November 2010] [12:35:12] <sustrik_>	good
| [Monday 01 November 2010] [12:35:27] <sustrik_>	hopefully, MinGW does the same thing
| [Monday 01 November 2010] [12:35:33] <mato>	it must
| [Monday 01 November 2010] [12:41:07] <sustrik_>	i'm checking what SOCKET actually is :(
| [Monday 01 November 2010] [12:41:17] <mato>	oh dear ... :-)
| [Monday 01 November 2010] [12:41:46] <sustrik_>	if _WIN64 is defined
| [Monday 01 November 2010] [12:42:13] <sustrik_>	it's uinsigned __int64
| [Monday 01 November 2010] [12:42:18] <sustrik_>	otherwise it's
| [Monday 01 November 2010] [12:42:38] <sustrik_>	__w64 unsigned int
| [Monday 01 November 2010] [12:42:44] <sustrik_>	whatever that means
| [Monday 01 November 2010] [12:48:35] <pieterh>	sustrik_, __w64 just means "this integer can be a pointer, safely"
| [Monday 01 November 2010] [12:48:59] <pieterh>	__w64 unsigned int on a 64-bit Windows box is the same as __int64
| [Monday 01 November 2010] [12:49:22] <pieterh>	'unsigned __int64', sorry
| [Monday 01 November 2010] [13:16:51] <mato>	sustrik_: event_t::reset () should also be restarted automagically on EINTR in signaler_t::recv() ?
| [Monday 01 November 2010] [13:17:30] <mato>	sustrik_: or should it just drop out with EINTR?
| [Monday 01 November 2010] [13:19:23] <sustrik_>	mato: if it's hard you can drop it
| [Monday 01 November 2010] [13:19:35] <mato>	sustrik_: it's not hard, i'm asking what it should do...
| [Monday 01 November 2010] [13:19:58] <mato>	sustrik_: what does "set" and "reset" mean, exactly?
| [Monday 01 November 2010] [13:20:04] <mato>	sustrik_: semantically...
| [Monday 01 November 2010] [13:21:30] <mato>	sustrik_: bah, /me is confused...
| [Monday 01 November 2010] [13:23:22] <mato>	sustrik_: i think i need to look at the signaler code together with you, otherwise i'll get it wrong
| [Monday 01 November 2010] [13:24:02] <mato>	sustrik_: anyway, i do have a nicely refactored event.hpp/event.cpp that tries to minimize duplication
| [Monday 01 November 2010] [13:25:03] <mato>	sustrik_: what needs to be protected by the mutex? queue and signaled or just queue?
| [Monday 01 November 2010] [13:51:56] <CIA-21>	zeromq2: 03Martin Lucina 07wip-signaler * rf78cb39 10/ (8 files in 3 dirs): 
| [Monday 01 November 2010] [13:51:56] <CIA-21>	zeromq2: WIP version of new signaler_t/event_t
| [Monday 01 November 2010] [13:51:56] <CIA-21>	zeromq2: Signed-off-by: Martin Lucina <mato@kotelna.sk> - http://bit.ly/9BPDCp
| [Monday 01 November 2010] [13:52:40] <Guthur>	sustrik: Thanks for the comments
| [Monday 01 November 2010] [13:53:07] <Guthur>	unfortunately C# doesn't support friends, I had thought of that
| [Monday 01 November 2010] [13:54:22] <Guthur>	And I didn't realise about spaces vs tabs
| [Monday 01 November 2010] [13:54:46] <sustrik_>	it makes the code ugly when your editor is set differently
| [Monday 01 November 2010] [13:55:05] <Guthur>	No problem
| [Monday 01 November 2010] [13:55:09] <Guthur>	I'll use spaces
| [Monday 01 November 2010] [13:55:10] <sustrik_>	anyway, if there are no friends, it probably have to stay as is
| [Monday 01 November 2010] [13:55:44] <Guthur>	The reason for  Queue methods was really to just improve the interface slightly
| [Monday 01 November 2010] [13:56:04] <Guthur>	but I can understand wanting to reflect the underlying API as much as possible
| [Monday 01 November 2010] [13:56:41] <Guthur>	Queue, Forwarder, and Streamer methods* 
| [Monday 01 November 2010] [13:57:59] <sustrik_>	yes
| [Monday 01 November 2010] [13:58:09] <sustrik_>	also, it's easier to tweak constants
| [Monday 01 November 2010] [13:58:15] <sustrik_>	than tweaking functions
| [Monday 01 November 2010] [13:58:24] <sustrik_>	in case anything changes in the future
| [Monday 01 November 2010] [13:58:33] <Guthur>	Reasonable enough, I'll change to reflect your suggestion
| [Monday 01 November 2010] [13:59:33] <sustrik_>	btw, the clrzmq project is kind of orphaned, do you want to help with it?
| [Monday 01 November 2010] [14:00:02] <sustrik_>	how it can be done is you'll get write access to the repo
| [Monday 01 November 2010] [14:00:48] <sustrik_>	if it is rather one-off patch, then send the patch to the mailing list
| [Monday 01 November 2010] [14:01:22] <Guthur>	sustrik_, Sure no problem
| [Monday 01 November 2010] [14:02:02] <Guthur>	is Jeffrey no longer involved?
| [Monday 01 November 2010] [14:04:37] <sustrik_>	haven't heard anything about clrzmq for quite a long time
| [Monday 01 November 2010] [14:04:49] <sustrik_>	but maybe i've just missed it?
| [Monday 01 November 2010] [14:05:56] <sustrik_>	last update aug, 30
| [Monday 01 November 2010] [14:06:24] <Guthur>	Has there been many interface changes to zmq since then?
| [Monday 01 November 2010] [14:06:32] <Guthur>	or is it mostly under the hood
| [Monday 01 November 2010] [14:06:39] <sustrik_>	it's under the hood
| [Monday 01 November 2010] [14:06:44] <sustrik_>	some new socket options
| [Monday 01 November 2010] [14:07:12] <Guthur>	I'll try to work through the examples and add the missing ones
| [Monday 01 November 2010] [14:07:24] <Guthur>	Good way to find any missing features I would imagine
| [Monday 01 November 2010] [14:07:27] <sustrik_>	just have a look at zmq.h
| [Monday 01 November 2010] [14:07:41] <Guthur>	that would also work, hehe
| [Monday 01 November 2010] [14:08:05] <sustrik_>	for the master branch there are these new options:
| [Monday 01 November 2010] [14:08:06] <sustrik_>	#define ZMQ_FD 14
| [Monday 01 November 2010] [14:08:06] <sustrik_>	#define ZMQ_EVENTS 15
| [Monday 01 November 2010] [14:08:07] <sustrik_>	#define ZMQ_TYPE 16
| [Monday 01 November 2010] [14:08:07] <sustrik_>	#define ZMQ_LINGER 17
| [Monday 01 November 2010] [14:08:07] <sustrik_>	#define ZMQ_RECONNECT_IVL 18
| [Monday 01 November 2010] [14:08:08] <sustrik_>	#define ZMQ_BACKLOG 19
| [Monday 01 November 2010] [14:08:43] <sustrik_>	first two are irrelevant from clrzmq's point of view
| [Monday 01 November 2010] [14:08:52] <sustrik_>	that leaves us with 4 new options
| [Monday 01 November 2010] [14:10:39] <Guthur>	what about ZMQ_RCVMORE
| [Monday 01 November 2010] [14:11:08] <sustrik_>	it's not there?
| [Monday 01 November 2010] [14:11:22] <Guthur>	not in what I cloned
| [Monday 01 November 2010] [14:11:33] <Guthur>	let me double check github
| [Monday 01 November 2010] [14:11:59] <sustrik_>	what's your name on github?
| [Monday 01 November 2010] [14:12:22] <Guthur>	Guthur, though I notice it gives my real name in the commits
| [Monday 01 November 2010] [14:12:38] <Guthur>	Its not in the clrzmq
| [Monday 01 November 2010] [14:12:42] <Guthur>	ZMQ_RCVMORE that is
| [Monday 01 November 2010] [14:12:54] <sustrik_>	ok, you have commit access to clrzmq
| [Monday 01 November 2010] [14:13:00] <sustrik_>	be carefull not to break it
| [Monday 01 November 2010] [14:13:09] <sustrik_>	let me check...
| [Monday 01 November 2010] [14:13:17] <mato>	sustrik_: should i be disabling interrupt coalescing only for RX or also for TX?
| [Monday 01 November 2010] [14:13:18] <toni_>	hi there. I am using zmq with python. The docs of pyzmq only cover sockets. Does anybody know where I can find more information about pyzmq?
| [Monday 01 November 2010] [14:13:55] <sustrik_>	Guthur: there's no getsockopt function at all :(
| [Monday 01 November 2010] [14:14:05] <sustrik_>	mato: both
| [Monday 01 November 2010] [14:14:26] <Guthur>	sustrik_: Definitely needs some work then
| [Monday 01 November 2010] [14:14:52] <sustrik_>	toni_: what do you mean?
| [Monday 01 November 2010] [14:14:58] <Guthur>	I'll try to bring it up to current
| [Monday 01 November 2010] [14:15:08] <sustrik_>	Guther: great!
| [Monday 01 November 2010] [14:16:14] <toni_>	sustrik_: I downloaded the pyzmq. Building the docs with sphinx I only get some info about the methods of the socket object. I need a more detailed documentation of the python api
| [Monday 01 November 2010] [14:16:52] <sustrik_>	socket object presumably _is_ python api
| [Monday 01 November 2010] [14:18:17] <mato>	sustrik_: hmm, i don't entirely trust this switch
| [Monday 01 November 2010] [14:18:39] <mato>	sustrik_: but the results I see *appear* to show that I get ~60us latency with the old code, and ~78us with the new cose
| [Monday 01 November 2010] [14:18:42] <mato>	*code
| [Monday 01 November 2010] [14:18:52] <sustrik_>	uhm
| [Monday 01 November 2010] [14:19:03] <sustrik_>	ok, we'll need some optimisation
| [Monday 01 November 2010] [14:19:06] <mato>	sustrik_: throughput is weird, it seemed to fluctuate but now appears stablew
| [Monday 01 November 2010] [14:19:18] <sustrik_>	throughput is a weird metric
| [Monday 01 November 2010] [14:19:20] <mato>	I guess ideally I should test w/o the switch, no?
| [Monday 01 November 2010] [14:19:29] <sustrik_>	fluctuating almost by definition
| [Monday 01 November 2010] [14:19:54] <sustrik_>	ideally, but normally switch is not the bottleneck
| [Monday 01 November 2010] [14:20:16] <mato>	well, it's only 100 EUR worth of switch so it won't be *that* great
| [Monday 01 November 2010] [14:20:28] <mato>	i can test tomorrow with a direct link, not now...
| [Monday 01 November 2010] [14:20:36] <sustrik_>	i don't think it's needed
| [Monday 01 November 2010] [14:20:43] <sustrik_>	the latency test is relevant
| [Monday 01 November 2010] [14:20:51] <sustrik_>	18us delta is too much
| [Monday 01 November 2010] [14:20:56] <mato>	ok, well that consistently shows the same result
| [Monday 01 November 2010] [14:21:00] <sustrik_>	we have to optimise
| [Monday 01 November 2010] [14:21:17] <mato>	well, let's sit down and look at it together tomorrow
| [Monday 01 November 2010] [14:21:21] <sustrik_>	ok
| [Monday 01 November 2010] [14:21:24] <mato>	now, beer?
| [Monday 01 November 2010] [14:21:45] <sustrik_>	allegedly, there's some klezmer-tango concert in nuspirit club
| [Monday 01 November 2010] [14:22:03] <mato>	ah, yes, someone did mention something the other day
| [Monday 01 November 2010] [14:22:06] <mato>	i forget who
| [Monday 01 November 2010] [14:22:15] <sustrik_>	your cousin?
| [Monday 01 November 2010] [14:22:15] <Guthur>	sustrik_: By the looks of it someone imported the setsockopt twice instead of doing getsockopt
| [Monday 01 November 2010] [14:22:22] <mato>	dunno
| [Monday 01 November 2010] [14:22:37] <sustrik_>	Guthur: quite possible
| [Monday 01 November 2010] [14:22:46] <sustrik_>	as I said, the project is kind of orphaned
| [Monday 01 November 2010] [14:23:05] <sustrik_>	looks like .net devs have not much love for open source
| [Monday 01 November 2010] [14:23:55] <Guthur>	yeah that tends to be the case
| [Monday 01 November 2010] [14:24:18] <Guthur>	I would have thought mono might be reversing the trend
| [Monday 01 November 2010] [14:24:40] <Guthur>	I'm only interested in it because I am paid to be, hehe
| [Monday 01 November 2010] [14:25:51] <sustrik_>	i'm afraid that's the case with most people using the .net binding
| [Monday 01 November 2010] [15:27:16] <PythonMQ>	hello, does anyone knows where can I find a compative version of pyzmq for old Python 2.4?
| [Monday 01 November 2010] [15:28:30] <PythonMQ>	when I try to create an extension for Python 2.4, it asks for .nET 1.1 SDK, Vs 2003, etc... which I dont have
| [Monday 01 November 2010] [16:32:00] <mikko>	good evening
| [Monday 01 November 2010] [17:18:04] <sustrik_>	travlr: hi, are you there by chance?
| [Monday 01 November 2010] [17:39:24] <Guthur>	sustrik_, when setting the identity through setsockopt is it string length + 1?
| [Monday 01 November 2010] [17:39:47] <Guthur>	for the optvallen
| [Monday 01 November 2010] [17:40:20] <mikko>	Guthur: no need for +1 as you give the length
| [Monday 01 November 2010] [17:41:01] <mikko>	as far as i remember it doesnt matter as long as it's consistent
| [Monday 01 November 2010] [17:41:22] <Guthur>	oh ok, its just unless I did that it was corrupting the last char
| [Monday 01 November 2010] [17:41:46] <Guthur>	but it could be something wrong with  the C# marshal  code
| [Monday 01 November 2010] [17:42:47] <sustrik_>	i think mikko is right
| [Monday 01 November 2010] [17:42:59] <sustrik_>	the identity is a binary blob, not a string
| [Monday 01 November 2010] [17:43:23] <sustrik_>	if it corrupts the last byte, it's a bug
| [Monday 01 November 2010] [17:44:59] <Guthur>	ok, I'll investigate a little
| [Monday 01 November 2010] [18:53:49] <Guthur>	sustrik_, should I do some checking so that people don't do silly things like set an affinity of -1
| [Tuesday 02 November 2010] [03:12:26] <hellophp>	hi
| [Tuesday 02 November 2010] [03:14:29] <hellophp>	chat
| [Tuesday 02 November 2010] [03:14:31] <hellophp>	kk
| [Tuesday 02 November 2010] [03:14:32] <hellophp>	test
| [Tuesday 02 November 2010] [04:13:08] <nettok>	is there something like "getpeername" for zeromq sockets?
| [Tuesday 02 November 2010] [04:13:35] <guido_g>	no
| [Tuesday 02 November 2010] [04:13:44] <nettok>	ok thanks
| [Tuesday 02 November 2010] [07:40:16] <Ogedei>	so zmq_send seems to clear my msg struct's data -- yet the docs don't talk about it, and some examples in the guide seem to assume it doesn't
| [Tuesday 02 November 2010] [07:40:24] <mikko>	hi
| [Tuesday 02 November 2010] [07:41:16] <Ogedei>	the question then, is: what happens to a msg struct when it is passed to zmq_send?
| [Tuesday 02 November 2010] [07:43:32] <sustrik>	it's cleared
| [Tuesday 02 November 2010] [07:43:43] <sustrik>	which examples in the guide assume it's not?
| [Tuesday 02 November 2010] [07:45:19] <Ogedei>	ah, found it (you cannot send the same message twice). yet, the topic_msg in an example in the guide seems to be reused
| [Tuesday 02 November 2010] [07:45:35] <Ogedei>	hah
| [Tuesday 02 November 2010] [07:45:41] <Ogedei>	ah, that's an example of broken code
| [Tuesday 02 November 2010] [07:45:50] <Ogedei>	a big red flashing warning would be good
| [Tuesday 02 November 2010] [07:46:56] <pieterh>	Ogedei, :-) Just saw that myself
| [Tuesday 02 November 2010] [07:47:03] <pieterh>	It does say: "Note than when you have passed a message to zmq_send(3), MQ will clear the message, i.e. set the size to zero. You cannot send the same message twice, and you cannot access the message data after sending it."
| [Tuesday 02 November 2010] [07:47:06] <pieterh>	but somewhat later
| [Tuesday 02 November 2010] [07:47:19] <Ogedei>	so, can I re-initialize my msg struct and send it again, or should I close it and make a new one?
| [Tuesday 02 November 2010] [07:47:29] <pieterh>	whatever is neater for your code
| [Tuesday 02 November 2010] [07:47:44] <sustrik>	there's also zmq_msg_copy function
| [Tuesday 02 November 2010] [07:48:13] <Ogedei>	doing msg_init on a zero-length, but unclosed message won't leak memory, right?
| [Tuesday 02 November 2010] [07:48:15] <pieterh>	that's if you want to send the identical message to multiple sockets or more than once to the same socket
| [Tuesday 02 November 2010] [07:48:23] <pieterh>	Ogedei, it's safe
| [Tuesday 02 November 2010] [07:48:26] <Ogedei>	what if it is not zero-length? will it be magically closed?
| [Tuesday 02 November 2010] [07:48:31] <pieterh>	yes
| [Tuesday 02 November 2010] [07:48:34] <Ogedei>	awesome
| [Tuesday 02 November 2010] [07:48:59] <pieterh>	indeed it is :-)
| [Tuesday 02 November 2010] [07:49:20] <sustrik>	wait a sec, magically closed, what?
| [Tuesday 02 November 2010] [07:49:49] <Ogedei>	whether msg-init (and friends) will close their argument, if necessary
| [Tuesday 02 November 2010] [07:49:50] <Ogedei>	actually
| [Tuesday 02 November 2010] [07:49:55] <pieterh>	sustrik: question was, if you do zmq_msg_init on an existing message will it close the old message or not
| [Tuesday 02 November 2010] [07:49:57] <Ogedei>	how could they do that? it might be raw memory
| [Tuesday 02 November 2010] [07:50:07] <sustrik>	exactly
| [Tuesday 02 November 2010] [07:50:10] <sustrik>	they don't
| [Tuesday 02 November 2010] [07:50:18] <pieterh>	what if there's a free function provided?
| [Tuesday 02 November 2010] [07:50:36] <sustrik>	it's called when message is zmq_close'd
| [Tuesday 02 November 2010] [07:50:46] <sustrik>	zmq_msg_close'd
| [Tuesday 02 November 2010] [07:50:48] <pieterh>	and if you re-init the message it'll leak?
| [Tuesday 02 November 2010] [07:50:52] <sustrik>	yes
| [Tuesday 02 November 2010] [07:50:57] <pieterh>	Ogedei, sorry, I was optimistic
| [Tuesday 02 November 2010] [07:50:57] <Ogedei>	I guess I'll take care to close my messages then
| [Tuesday 02 November 2010] [07:50:58] <sustrik>	as any other C structure
| [Tuesday 02 November 2010] [07:51:26] <pieterh>	sustrik: C structures don't really behave anything like this
| [Tuesday 02 November 2010] [07:51:46] <sustrik>	struct {char *a; char *b};
| [Tuesday 02 November 2010] [07:51:54] <pieterh>	structures don't have constructors
| [Tuesday 02 November 2010] [07:51:54] <sustrik>	when are the strings deallocated?
| [Tuesday 02 November 2010] [07:52:12] <sustrik>	yes, you need an initialisation and deinitialisation functions
| [Tuesday 02 November 2010] [07:52:22] <sustrik>	that's what zmq_msg_init and zmq_msg_close are
| [Tuesday 02 November 2010] [07:52:36] <pieterh>	any particular reason you _don't_ call close when re-initializing a message?
| [Tuesday 02 November 2010] [07:52:44] <pieterh>	i assume close is idempotent
| [Tuesday 02 November 2010] [07:52:57] <sustrik>	because you have no idea whether you are re-initialising
| [Tuesday 02 November 2010] [07:53:01] <pieterh>	and the msg api does have callbacks for deallocators
| [Tuesday 02 November 2010] [07:53:24] <Ogedei>	you can't just follow the pointers in there -- might be uninitialized raw memory
| [Tuesday 02 November 2010] [07:53:25] <pieterh>	ah, it could just be random data... 
| [Tuesday 02 November 2010] [07:53:36] <sustrik>	yes
| [Tuesday 02 November 2010] [07:53:43] <Ogedei>	anyway, did anyone ever get anywhere with a ruby wrapper? I'm writting a wrapper for (the also green-threaded) Allegro Common Lisp
| [Tuesday 02 November 2010] [07:53:48] <pieterh>	because you're not constructing the message, it's just on the stack
| [Tuesday 02 November 2010] [07:54:09] <pieterh>	hmm...
| [Tuesday 02 November 2010] [07:54:13] <Ogedei>	there were some discouraging messages on the list
| [Tuesday 02 November 2010] [07:54:15] <sustrik>	right, there may be garbage inside
| [Tuesday 02 November 2010] [07:54:29] <sustrik>	what's wrong with the ruby wrapper?
| [Tuesday 02 November 2010] [07:54:46] <Ogedei>	there's this issue with blocking APIs and green threads
| [Tuesday 02 November 2010] [07:54:52] <pieterh>	Ogedei, what list ? :-)
| [Tuesday 02 November 2010] [07:54:59] <Ogedei>	lemme search
| [Tuesday 02 November 2010] [07:55:59] <sustrik>	i would guess it's about the fact that ruby, being green-threaded, cannot use blocking calls
| [Tuesday 02 November 2010] [07:56:18] <sustrik>	if so, it's a problem with ruby rather than with 0mq
| [Tuesday 02 November 2010] [07:56:26] <sustrik>	you can still use non-blocking calls
| [Tuesday 02 November 2010] [07:56:55] <Ogedei>	yeah, but then you can say good-bye to responsiveness (that's an exaggeration of course)
| [Tuesday 02 November 2010] [07:57:34] <sustrik>	yes, unfortunately, it's a ruby issue
| [Tuesday 02 November 2010] [07:57:41] <sustrik>	there's little i can do about it
| [Tuesday 02 November 2010] [07:58:29] <sustrik>	green-threads are simply not good for high-perf scenarios
| [Tuesday 02 November 2010] [07:58:55] <sustrik>	anyway, that python guys are doing, afaiu, is that they launch several instances of python interpreter
| [Tuesday 02 November 2010] [07:59:05] <sustrik>	each running exactly one green thread
| [Tuesday 02 November 2010] [07:59:14] <Ogedei>	i have a trick with companion C threads and a pipe that works reasonably well, but yeah, it's awkward
| [Tuesday 02 November 2010] [07:59:14] <sustrik>	which means it can use blocking calls
| [Tuesday 02 November 2010] [07:59:29] <sustrik>	then they use 0mq to send messages between the instances
| [Tuesday 02 November 2010] [08:00:50] <sustrik>	i think no trick would help: either you use non-blocking calls, thus loosing performance or you use blocking calls thus eventually blocking other green threads :(
| [Tuesday 02 November 2010] [08:05:18] <Ogedei>	well, no, in my case, i have a thread written in C which does the blocking, and the Lisp runtime is listening on a pipe for events, and thus gets notified when the C thread has done its work. more indirect, but no polling is involved
| [Tuesday 02 November 2010] [08:10:13] <sustrik>	ah, you can do that with 0mq as well
| [Tuesday 02 November 2010] [08:10:23] <sustrik>	you can poll on sockets
| [Tuesday 02 November 2010] [08:12:14] <sustrik>	in a separate C thread
| [Tuesday 02 November 2010] [08:12:35] <sustrik>	however, the problem is how to notify ruby
| [Tuesday 02 November 2010] [08:12:47] <sustrik>	you are back to the same problem
| [Tuesday 02 November 2010] [08:12:59] <sustrik>	ruby can either check for new events, thus loosing performance
| [Tuesday 02 November 2010] [08:13:15] <sustrik>	or block waiting for them, thus blocking other green-threads
| [Tuesday 02 November 2010] [08:37:50] <CIA-20>	zeromq2: 03Martin Sustrik 07master * rde93f63 10/ configure.in : 
| [Tuesday 02 November 2010] [08:37:50] <CIA-20>	zeromq2: crypto library is needed on HP-UX to generate UUIDs
| [Tuesday 02 November 2010] [08:37:50] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/bUi6DJ
| [Tuesday 02 November 2010] [08:37:56] <Guthur>	Ogedei, It might be good if you extended the current CL binding with some read time conditionals for ACL
| [Tuesday 02 November 2010] [08:38:12] <mato>	sustrik: shouldn't that have gone onto maint also?
| [Tuesday 02 November 2010] [08:38:13] <Guthur>	if possible...
| [Tuesday 02 November 2010] [08:38:21] <mato>	sustrik: (that == HP-UX -lcrypto)
| [Tuesday 02 November 2010] [08:40:38] <sustrik>	mato: it's probably broken anyway
| [Tuesday 02 November 2010] [08:40:44] <mato>	sustrik: why so?
| [Tuesday 02 November 2010] [08:41:05] <sustrik>	what i mean, there are issues compiling it, right?
| [Tuesday 02 November 2010] [08:41:14] <sustrik>	so people are presumably not using it
| [Tuesday 02 November 2010] [08:41:26] <sustrik>	so, let them rather start with 2.1
| [Tuesday 02 November 2010] [08:41:40] <mato>	sustrik: as you wish
| [Tuesday 02 November 2010] [08:41:44] <sustrik>	instead of using 2.0 and then having to upgrade to 2.1 in a short time
| [Tuesday 02 November 2010] [08:42:15] <mato>	sustrik: for the OPEN_MAX thing, just add in a define defining it to _POSIX_OPEN_MAX if it's not there
| [Tuesday 02 November 2010] [08:42:32] <sustrik>	nope, the macros have differnet semantics
| [Tuesday 02 November 2010] [08:42:42] <mato>	they do?
| [Tuesday 02 November 2010] [08:42:42] <sustrik>	check POSIX
| [Tuesday 02 November 2010] [08:42:54] <sustrik>	{OPEN_MAX}
| [Tuesday 02 November 2010] [08:42:54] <sustrik>	    Maximum number of files that one process can have open at any one time.
| [Tuesday 02 November 2010] [08:42:54] <sustrik>	    Minimum Acceptable Value: {_POSIX_OPEN_MAX}
| [Tuesday 02 November 2010] [08:44:01] <mato>	sustrik: hmm, well, then it's a bug in HP-UX
| [Tuesday 02 November 2010] [08:44:11] <mato>	sustrik: or they need to find out what the correct value to use is
| [Tuesday 02 November 2010] [08:44:11] <sustrik>	not even that"
| [Tuesday 02 November 2010] [08:44:20] <sustrik>	POSIX says:
| [Tuesday 02 November 2010] [08:44:21] <sustrik>	"A definition of one of the symbolic names in the following list shall be omitted from <limits.h> on specific implementations where the corresponding value is equal to or greater than the stated minimum, but is unspecified.
| [Tuesday 02 November 2010] [08:44:21] <sustrik>	This indetermination might depend on the amount of available memory space on a specific instance of a specific implementation. The actual value supported by a specific instance shall be provided by the sysconf() function."
| [Tuesday 02 November 2010] [08:44:36] <mato>	sustrik: sure, usual POSIX ambiguity
| [Tuesday 02 November 2010] [08:44:49] <sustrik>	i would do it in following way:
| [Tuesday 02 November 2010] [08:44:53] <mato>	sustrik: what I mean is someone at HP has to say what value should go in there on HP-UX
| [Tuesday 02 November 2010] [08:44:55] <sustrik>	on Solaris use OPEN_MAX-1
| [Tuesday 02 November 2010] [08:45:10] <sustrik>	on other paltforms use our constand defined in config.hpp
| [Tuesday 02 November 2010] [08:45:22] <sustrik>	"max_io_events"
| [Tuesday 02 November 2010] [08:45:33] <mato>	sustrik: not a great idea; /dev/poll is platform-specific anyway
| [Tuesday 02 November 2010] [08:45:43] <mato>	sustrik: so that platform-specific value should be determined
| [Tuesday 02 November 2010] [08:45:57] <sustrik>	that's what i've proposed
| [Tuesday 02 November 2010] [08:46:13] <DerGuteMoritz>	is the Ruby green thread blocking discussion from earlier still current?
| [Tuesday 02 November 2010] [08:46:20] <sustrik>	looks like solaris has this limit of "at most OPEN_MAX"
| [Tuesday 02 November 2010] [08:46:29] <sustrik>	hp-ux doesn't seem to have the limit
| [Tuesday 02 November 2010] [08:46:39] <sustrik>	anyway, i'll ask brett to test it
| [Tuesday 02 November 2010] [08:47:03] <sustrik>	DerGuteMoritz: yes, nothing have changed in the meantime :)
| [Tuesday 02 November 2010] [08:47:03] <mato>	ah, right, you're saying that HP-UX has no limit
| [Tuesday 02 November 2010] [08:47:05] <mato>	that's possiblew
| [Tuesday 02 November 2010] [08:48:12] <mato>	bah, I can't seem to find a copy of the /dev/poll (poll(7d)) manpage for HP-UX on the net anywhere
| [Tuesday 02 November 2010] [08:48:17] <mato>	sustrik: anyhow, check with brett
| [Tuesday 02 November 2010] [08:48:23] <mato>	sustrik: and/or get him to ask their devs
| [Tuesday 02 November 2010] [08:51:18] <DerGuteMoritz>	I don't know what Ruby provides something like that but Chicken's green thread scheduler provides a hook to wait for i/o on a file descriptor without blocking other threads. I use it successfully with ZMQ_FD
| [Tuesday 02 November 2010] [08:51:34] <DerGuteMoritz>	works with 2.1 only then, of course
| [Tuesday 02 November 2010] [08:52:12] <sustrik>	DerGuteMoritz: maybe Ruby can do the same thing
| [Tuesday 02 November 2010] [08:52:21] <DerGuteMoritz>	mayhaps!
| [Tuesday 02 November 2010] [08:52:39] <sustrik>	it's up to Ruby binding maintainers though
| [Tuesday 02 November 2010] [08:52:45] 	 * sustrik has no idea how ruby works
| [Tuesday 02 November 2010] [08:53:00] <mato>	sustrik: ok, so, event.set() and event.reset() should never return EINTR, right?
| [Tuesday 02 November 2010] [08:53:06] <mato>	sustrik: only event.wait() should do so
| [Tuesday 02 November 2010] [08:53:20] <DerGuteMoritz>	yeah :-)
| [Tuesday 02 November 2010] [08:53:28] <sustrik>	mato: it can be that way
| [Tuesday 02 November 2010] [08:53:29] <DerGuteMoritz>	just thought I'd mention it :-)
| [Tuesday 02 November 2010] [08:53:31] <mato>	sustrik: the other two should just silently restart the call since it *must* succeed
| [Tuesday 02 November 2010] [08:53:46] <sustrik>	the whole EINTR thing is a heurstic anyway
| [Tuesday 02 November 2010] [08:53:54] <mato>	ok, i'll go with this approach for now
| [Tuesday 02 November 2010] [08:53:57] <sustrik>	ok
| [Tuesday 02 November 2010] [08:53:58] <mato>	and we'll see what happens
| [Tuesday 02 November 2010] [09:07:16] <mikko>	mato: http://webcache.googleusercontent.com/search?q=cache:XwnPSWMLfJkJ:docs.hp.com/en/B3921-90010/poll.7.html+hp-ux+dev/poll&cd=1&hl=en&ct=clnk&client=firefox-a 
| [Tuesday 02 November 2010] [09:07:20] <mikko>	is that the one?
| [Tuesday 02 November 2010] [09:10:02] <mikko>	ah
| [Tuesday 02 November 2010] [09:10:03] <mikko>	http://h20000.www2.hp.com/bc/docs/support/SupportManual/c02263385/c02263385.pdf
| [Tuesday 02 November 2010] [09:10:16] <mikko>	poll(7) as pdf
| [Tuesday 02 November 2010] [09:11:42] <mato>	mikko: hey, thanks! yeah, that's it
| [Tuesday 02 November 2010] [09:12:27] <mikko>	mato: http://h20000.www2.hp.com/bizsupport/TechSupport/CoreRedirect.jsp?redirectReason=DocIndexPDF&prodSeriesId=4256918&targetPage=http%3A%2F%2Fbizsupport2.austin.hp.com%2Fbc%2Fdocs%2Fsupport%2FSupportManual%2Fc02456334%2Fc02456334.pdf