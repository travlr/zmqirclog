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
| [Tuesday 02 November 2010] [09:13:17] <mato>	sustrik: over and above that of EMFILE/ENFILE obviously
| [Tuesday 02 November 2010] [09:21:42] <sustrik>	mato, mikko: ack
| [Tuesday 02 November 2010] [09:29:23] <CIA-20>	zeromq2: 03Martin Sustrik 07master * rd4a4106 10/ src/devpoll.cpp : 
| [Tuesday 02 November 2010] [09:29:23] <CIA-20>	zeromq2: HP-UX has no OPEN_MAX defined
| [Tuesday 02 November 2010] [09:29:23] <CIA-20>	zeromq2: devpoll_t used this constant to determine how many events to
| [Tuesday 02 November 2010] [09:29:23] <CIA-20>	zeromq2: retrieve from the poller in one go. The implementation was
| [Tuesday 02 November 2010] [09:29:23] <CIA-20>	zeromq2: changed not to depend on this constant.
| [Tuesday 02 November 2010] [09:29:23] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/bYvpwB
| [Tuesday 02 November 2010] [09:50:21] <mato>	sustrik: ok, so i found that problem, just a simple mistake in my code
| [Tuesday 02 November 2010] [09:50:27] <mato>	sustrik: one code path was reading twice...
| [Tuesday 02 November 2010] [09:50:36] <mato>	sustrik: now i have a different problem, i think
| [Tuesday 02 November 2010] [09:50:44] <mato>	sustrik: which has to do with the event semantics
| [Tuesday 02 November 2010] [09:51:35] <mato>	sustrik: what i see now is a hang on context termination...
| [Tuesday 02 November 2010] [09:54:00] <sustrik>	re
| [Tuesday 02 November 2010] [09:54:19] <sustrik>	what specifically?
| [Tuesday 02 November 2010] [09:57:54] <mato>	sustrik: i think what i'm seeing is that the i/o threads are not getting the event signaled when it should be
| [Tuesday 02 November 2010] [09:57:59] <mato>	sustrik: ... this is not clear ...
| [Tuesday 02 November 2010] [09:58:29] <mato>	sustrik: if the event is signaled only when ypipe_t flush() returns false, won't that result in missed events?
| [Tuesday 02 November 2010] [09:58:47] <mato>	sustrik: it's not clear to me how ypipe_t "knows" that the reader is asleep/polling
| [Tuesday 02 November 2010] [10:02:02] <sustrik>	when reader tries to get a command
| [Tuesday 02 November 2010] [10:02:10] <sustrik>	and there is no command available
| [Tuesday 02 November 2010] [10:02:21] <sustrik>	an atomic variable is set to null
| [Tuesday 02 November 2010] [10:02:54] <sustrik>	when writer writes a command and finds out that the atomic variable is set to null
| [Tuesday 02 November 2010] [10:03:02] <sustrik>	it notifies the writer by returning false
| [Tuesday 02 November 2010] [10:08:06] <mato>	sustrik: hmm, might the problem be because there is a case where the caller of the signaller does not process *all* commands?
| [Tuesday 02 November 2010] [10:09:28] <mato>	sustrik: my trivial debugging seems to show that the signaler is written to, but it doesn't set the event, presumably because the writer thinks the reader is still alive
| [Tuesday 02 November 2010] [10:09:38] <mato>	sustrik: which could happen if the reader does not read *all* commands
| [Tuesday 02 November 2010] [10:09:42] <mato>	sustrik: correct?
| [Tuesday 02 November 2010] [10:13:15] <sustrik>	yes
| [Tuesday 02 November 2010] [10:13:29] 	 * mato is trying to find a case like that in the code, but i can't
| [Tuesday 02 November 2010] [10:13:42] <mato>	but i'm probably missing something
| [Tuesday 02 November 2010] [10:28:29] <mato>	sustrik: ok, event.set() in the signaler constructor is a neat trick
| [Tuesday 02 November 2010] [10:28:34] <mato>	sustrik: things almost work
| [Tuesday 02 November 2010] [10:28:44] <sustrik>	almost?
| [Tuesday 02 November 2010] [10:28:54] <mato>	test_shutdown_stress fails rather interestingly
| [Tuesday 02 November 2010] [10:29:15] <mato>	due to ~mutex_t() from ~signaler_t() trying to destroy a mutex that is locked... :-)
| [Tuesday 02 November 2010] [10:29:26] <mato>	so someone is still trying to send to that signaler...
| [Tuesday 02 November 2010] [10:29:40] <mato>	this might be related to that other problem reported on the ML
| [Tuesday 02 November 2010] [10:30:41] <sustrik>	interesting
| [Tuesday 02 November 2010] [10:30:56] <sustrik>	can you push to the github
| [Tuesday 02 November 2010] [10:31:02] <sustrik>	so that i can check that
| [Tuesday 02 November 2010] [10:31:04] <sustrik>	?
| [Tuesday 02 November 2010] [10:31:25] <mato>	guess so, d'you want it with my debug code which prints various bits about what the signaler is doing?
| [Tuesday 02 November 2010] [10:32:16] <mato>	sustrik: ?
| [Tuesday 02 November 2010] [10:33:08] <sustrik>	probably not
| [Tuesday 02 November 2010] [10:33:21] <mato>	hmm, ok give me a moment to stash it away
| [Tuesday 02 November 2010] [10:33:21] <sustrik>	with shutdown stress that it would be a lot of printfs
| [Tuesday 02 November 2010] [10:33:40] <mato>	doesn't really matter, the offending sequence aborts anyway
| [Tuesday 02 November 2010] [10:33:43] <mato>	but ok, i'll take it out
| [Tuesday 02 November 2010] [10:42:15] <CIA-20>	zeromq2: 03Martin Lucina 07wip-signaler * rabf6d73 10/ (4 files): 
| [Tuesday 02 November 2010] [10:42:15] <CIA-20>	zeromq2: Move signaled into event_t as atomic counter
| [Tuesday 02 November 2010] [10:42:15] <CIA-20>	zeromq2: Moved signaled from signaler_t into event_t and made event_t::set() and
| [Tuesday 02 November 2010] [10:42:15] <CIA-20>	zeromq2: event_t::reset() methods idempotent.
| [Tuesday 02 November 2010] [10:42:15] <CIA-20>	zeromq2: Made event_t::wait() handle EINTR, except for eventfd implementation (for now).
| [Tuesday 02 November 2010] [10:42:16] <CIA-20>	zeromq2: Signed-off-by: Martin Lucina <mato@kotelna.sk> - http://bit.ly/bNpvjo
| [Tuesday 02 November 2010] [10:42:16] <CIA-20>	zeromq2: 03Martin Lucina 07wip-signaler * r3356bd2 10/ (4 files): 
| [Tuesday 02 November 2010] [10:42:17] <CIA-20>	zeromq2: WIP: Make signaler use ypipe_t for queueing
| [Tuesday 02 November 2010] [10:42:17] <CIA-20>	zeromq2: Signed-off-by: Martin Lucina <mato@kotelna.sk> - http://bit.ly/8ZMJLw
| [Tuesday 02 November 2010] [10:42:36] <mato>	sustrik: ok, try it out
| [Tuesday 02 November 2010] [10:42:41] <sustrik>	thx
| [Tuesday 02 November 2010] [10:42:42] <mato>	sustrik: there are actually two problems
| [Tuesday 02 November 2010] [10:43:03] <mato>	sustrik: you will get asserts from the other tests on queue.read(), so it looks like i'm losing events somewhere, will check that
| [Tuesday 02 November 2010] [10:43:13] <mato>	sustrik: suggest you just look at what test_shutdown_stress is doing
| [Tuesday 02 November 2010] [10:43:33] <mato>	sustrik: oh, and i've not tested the eventfd implementation, so it might not work at all (it definitely does not process EINTR)
| [Tuesday 02 November 2010] [10:43:46] <mato>	i'll look at the problem with events getting lost
| [Tuesday 02 November 2010] [10:45:13] <sustrik>	ok
| [Tuesday 02 November 2010] [10:51:57] <mato>	sustrik: ok, my fault with the event problem; atomic_counter is not ideal since I actually need atomic *set*
| [Tuesday 02 November 2010] [10:52:18] <mato>	sustrik: sorry, i mean with the problem with losing events
| [Tuesday 02 November 2010] [10:52:22] <sustrik>	ah
| [Tuesday 02 November 2010] [10:52:45] <mato>	i'm using add and sub, i thought they can't happen multiple times, but it seems they can
| [Tuesday 02 November 2010] [10:52:50] <mato>	so i really need set
| [Tuesday 02 November 2010] [10:53:07] <sustrik>	there's some old code using lock;xchg
| [Tuesday 02 November 2010] [10:53:11] <sustrik>	let me find it
| [Tuesday 02 November 2010] [10:53:58] <mato>	sustrik: i'll make it work, don't worry about it
| [Tuesday 02 November 2010] [10:54:04] <sustrik>	ok
| [Tuesday 02 November 2010] [10:54:07] <mato>	sustrik: i can just make the set() method of atomic_counter work
| [Tuesday 02 November 2010] [10:54:12] <mato>	sustrik: work atomically that is
| [Tuesday 02 November 2010] [11:09:37] <travlr>	sustrik: hey martin, just noticed your message, something i can help you with?
| [Tuesday 02 November 2010] [11:10:04] <sustrik>	i've noticed that your online documentation is not linked from the website
| [Tuesday 02 November 2010] [11:10:06] <sustrik>	or is it?
| [Tuesday 02 November 2010] [11:10:42] <travlr>	i think its on the "source" page at the end of the intro paragraph
| [Tuesday 02 November 2010] [11:11:28] <sustrik>	ah, ok, i see
| [Tuesday 02 November 2010] [11:11:45] <sustrik>	anyway, i'm wiriting an architecture overview, so i'll link it from there as well
| [Tuesday 02 November 2010] [11:12:59] <travlr>	cool, if you want to eventually convert the sources to using doxygen style comments let me know.
| [Tuesday 02 November 2010] [11:13:29] <mato>	sustrik: um, the eventfd code is completely bogus, sorry
| [Tuesday 02 November 2010] [11:13:47] <mato>	sustrik: i'll fix it later, am trying to figure out what i'm doing wrong right now
| [Tuesday 02 November 2010] [11:14:08] <sustrik>	ok
| [Tuesday 02 November 2010] [12:10:50] <sustrik>	mato: still there?
| [Tuesday 02 November 2010] [12:11:21] <sustrik>	i think i've found the problem with shutdown stress test
| [Tuesday 02 November 2010] [12:11:29] <mato>	sustrik: yes, i'm fighting with the event stuff
| [Tuesday 02 November 2010] [12:11:45] <mato>	sustrik: it's complete black magic, i don't understand what i'm doing wrong with the synchronization
| [Tuesday 02 November 2010] [12:12:15] <sustrik>	shutdown stress test ->
| [Tuesday 02 November 2010] [12:12:26] <sustrik>	the sender sends a command
| [Tuesday 02 November 2010] [12:12:50] <sustrik>	before it gets chance to unlock the mutex
| [Tuesday 02 November 2010] [12:13:00] <sustrik>	the receiving thread reads the command
| [Tuesday 02 November 2010] [12:13:13] <sustrik>	processing the command causes destruction of the object
| [Tuesday 02 November 2010] [12:13:18] <sustrik>	and here we are
| [Tuesday 02 November 2010] [12:13:21] <sustrik>	EBUSY
| [Tuesday 02 November 2010] [12:13:25] <mato>	right, that'd make sense...
| [Tuesday 02 November 2010] [12:14:00] <sustrik>	i've added sync.lock(); sync.unlock(); into the desctructor of signaler_t
| [Tuesday 02 November 2010] [12:14:11] <sustrik>	so that it waits till the  mutex is released
| [Tuesday 02 November 2010] [12:14:16] <sustrik>	and it seems to work now
| [Tuesday 02 November 2010] [12:14:27] <mato>	what if a writer locks it again in the mean time?
| [Tuesday 02 November 2010] [12:14:44] <mato>	i.e. after the sync.unlock() in the destructor, but before the actual destruction?
| [Tuesday 02 November 2010] [12:17:39] <sustrik>	there should be no more commands for an object after it shuts down
| [Tuesday 02 November 2010] [12:17:46] <sustrik>	that's why it counts term_acks
| [Tuesday 02 November 2010] [12:18:11] <mato>	ok
| [Tuesday 02 November 2010] [12:18:18] <sustrik>	will you add the code?
| [Tuesday 02 November 2010] [12:18:21] <mato>	yes
| [Tuesday 02 November 2010] [12:18:27] <sustrik>	ok
| [Tuesday 02 November 2010] [12:18:27] <mato>	i have a bigger problem
| [Tuesday 02 November 2010] [12:18:34] 	 * sustrik is listening
| [Tuesday 02 November 2010] [12:18:44] <mato>	which is that there's something wrong with how i'm synchronizing the signaled variable
| [Tuesday 02 November 2010] [12:18:52] <mato>	and i don't understand what it is
| [Tuesday 02 November 2010] [12:19:03] <mato>	i've changed the code to use CAS
| [Tuesday 02 November 2010] [12:19:27] <mato>	but i still get stuff like coming out of wait() it fails with an assertion that signaled is zero
| [Tuesday 02 November 2010] [12:19:31] <mato>	where it should be one
| [Tuesday 02 November 2010] [12:19:43] <sustrik>	a mutli core box?
| [Tuesday 02 November 2010] [12:19:46] <mato>	yes
| [Tuesday 02 November 2010] [12:20:16] <sustrik>	orgering of CAS and send/recv is ok?
| [Tuesday 02 November 2010] [12:20:26] <sustrik>	ordering*
| [Tuesday 02 November 2010] [12:20:27] <mato>	CAS is done first
| [Tuesday 02 November 2010] [12:20:34] <sustrik>	in both cases
| [Tuesday 02 November 2010] [12:20:35] <sustrik>	?
| [Tuesday 02 November 2010] [12:20:38] <mato>	yes
| [Tuesday 02 November 2010] [12:20:43] <sustrik>	wait a sec
| [Tuesday 02 November 2010] [12:20:46] 	 * sustrik is thinking
| [Tuesday 02 November 2010] [12:21:27] <mato>	hmm, i just realised i had extra left-over code in there
| [Tuesday 02 November 2010] [12:21:51] <mato>	but it still doesn't work
| [Tuesday 02 November 2010] [12:22:19] <mato>	sustrik: in event.set() i have 
| [Tuesday 02 November 2010] [12:22:24] <mato>	    if (signaled.cas (0, 1) == 1)
| [Tuesday 02 November 2010] [12:22:24] <mato>	        return;
| [Tuesday 02 November 2010] [12:22:31] <mato>	and then send
| [Tuesday 02 November 2010] [12:22:51] <mato>	after the send i assert that it's still 1
| [Tuesday 02 November 2010] [12:23:06] <mato>	which fails, presumably because the reader has since re-set it
| [Tuesday 02 November 2010] [12:23:43] <sustrik>	that's ok, no?
| [Tuesday 02 November 2010] [12:23:51] <mato>	that's fine
| [Tuesday 02 November 2010] [12:23:55] <mato>	in fact, i just removed that assert
| [Tuesday 02 November 2010] [12:24:02] <mato>	but the weird one is
| [Tuesday 02 November 2010] [12:24:13] <mato>	after wait() i get signaled = 0
| [Tuesday 02 November 2010] [12:24:30] <sustrik>	how does the wait code look like?
| [Tuesday 02 November 2010] [12:24:38] <mato>	assert signaled == 0
| [Tuesday 02 November 2010] [12:24:43] <mato>	recv
| [Tuesday 02 November 2010] [12:24:48] <mato>	return -1 if EINTR
| [Tuesday 02 November 2010] [12:24:52] <mato>	assert signaled == 1
| [Tuesday 02 November 2010] [12:24:56] <mato>	that's all
| [Tuesday 02 November 2010] [12:25:54] <mato>	it's obviously a synchronization problem since it doesn't always happen at the same "place" e.g. when running test_reqrep_tcp
| [Tuesday 02 November 2010] [12:26:14] <sustrik>	the first assert is bogus
| [Tuesday 02 November 2010] [12:26:22] <mato>	yes, i took it out
| [Tuesday 02 November 2010] [12:26:32] <sustrik>	the second one fails?
| [Tuesday 02 November 2010] [12:26:44] <mato>	sorry, which first assert
| [Tuesday 02 November 2010] [12:26:52] <sustrik>	assert signaled == 0
| [Tuesday 02 November 2010] [12:26:53] <mato>	you mean signaled == 0 at start of wait?
| [Tuesday 02 November 2010] [12:26:56] <sustrik>	yes
| [Tuesday 02 November 2010] [12:26:57] <mato>	ah, right, i can take that out
| [Tuesday 02 November 2010] [12:27:12] <mato>	but it's the 2nd one that's failing
| [Tuesday 02 November 2010] [12:28:26] <sustrik>	signaled ihow do you test the signaled variable?
| [Tuesday 02 November 2010] [12:28:30] <sustrik>	exactly?
| [Tuesday 02 November 2010] [12:28:40] <mato>	just a normal get()
| [Tuesday 02 November 2010] [12:28:45] <mato>	shouldn't matter on x86
| [Tuesday 02 November 2010] [12:28:56] <sustrik>	right
| [Tuesday 02 November 2010] [12:31:47] <sustrik>	it looks are there are some leftover bytes in the socketpair
| [Tuesday 02 November 2010] [12:31:59] <mato>	why would that be?
| [Tuesday 02 November 2010] [12:31:59] <sustrik>	i cannot think of any other reason why this would happen
| [Tuesday 02 November 2010] [12:32:09] <sustrik>	dunno
| [Tuesday 02 November 2010] [12:32:25] <mato>	yes, but why would signaled=0 indicate leftover bytes in the socketpair?
| [Tuesday 02 November 2010] [12:32:29] <sustrik>	can you psuh the code, so that i can have a look at it?
| [Tuesday 02 November 2010] [12:33:06] <sustrik>	because wait will return even though the sender haven't sent anything
| [Tuesday 02 November 2010] [12:33:26] <sustrik>	and thus it haven't set the flag to 1
| [Tuesday 02 November 2010] [12:34:02] <sustrik>	so, imo, it looks like the sender is sending signal to receiver twice
| [Tuesday 02 November 2010] [12:34:11] <sustrik>	even though receiver was stuck only once
| [Tuesday 02 November 2010] [12:34:46] <mato>	sustrik: sure, but the cas() in event.set() should protect it from running more than once...
| [Tuesday 02 November 2010] [12:35:05] <sustrik>	it's hard to reason about without seeing the code
| [Tuesday 02 November 2010] [12:36:08] <sustrik>	i think i know what the problem is
| [Tuesday 02 November 2010] [12:36:12] <mato>	?
| [Tuesday 02 November 2010] [12:36:37] <sustrik>	the reader doesn't do read&reset as an atomic unit locked by mutex
| [Tuesday 02 November 2010] [12:36:53] <sustrik>	so the cas on the sender side can happen between the two
| [Tuesday 02 November 2010] [12:37:14] <sustrik>	 maybe
| [Tuesday 02 November 2010] [12:37:18] <sustrik>	i need to see the code
| [Tuesday 02 November 2010] [12:37:33] <mato>	i'll email it to you, i don't want to pollute the main git with WIP stuff like this
| [Tuesday 02 November 2010] [12:37:38] <sustrik>	ok, just send it
| [Tuesday 02 November 2010] [12:39:11] <mato>	sent
| [Tuesday 02 November 2010] [12:39:34] <sustrik>	thx
| [Tuesday 02 November 2010] [12:47:54] <jdroid->	this might be naive... but what is the zeromq response to someone who says, "I need a broker?"
| [Tuesday 02 November 2010] [12:48:19] <sustrik>	use a device
| [Tuesday 02 November 2010] [12:48:47] <sustrik>	mato: i think what you need to do is this:
| [Tuesday 02 November 2010] [12:48:52] <jdroid->	mind elabroating? does zmq recommend certain devices? how do they work? 
| [Tuesday 02 November 2010] [12:49:23] <sustrik>	move the CAS in reset *after* the recv
| [Tuesday 02 November 2010] [12:50:19] <mikko>	jdroid-: http://zguide.zeromq.org/chapter:all#toc29
| [Tuesday 02 November 2010] [12:50:20] <sustrik>	jdroid-: there are several devices shipped with 0mq itself (queue, forwarder, streamer)
| [Tuesday 02 November 2010] [12:50:35] <sustrik>	but you can build new ones by hand, it's easy
| [Tuesday 02 November 2010] [12:50:37] <jdroid->	ohh.. weird. i thought you meant hardware
| [Tuesday 02 November 2010] [12:51:12] <mato>	sustrik: hmm, ok, but at the same time reset() must be idempotent
| [Tuesday 02 November 2010] [12:51:18] <sustrik>	does it?
| [Tuesday 02 November 2010] [12:51:31] <mato>	sustrik: so we should not do the recv() if signaled is 1...
| [Tuesday 02 November 2010] [12:51:34] <jdroid->	sometimes people suggest that zeromq isn't actually a queue. eo these devices make that so then?
| [Tuesday 02 November 2010] [12:52:12] <sustrik>	mato: you mean 0?
| [Tuesday 02 November 2010] [12:52:15] <mato>	sustrik: yes
| [Tuesday 02 November 2010] [12:52:36] <sustrik>	that should be guaranteed by semantics of ypipe i would say
| [Tuesday 02 November 2010] [12:53:20] <sustrik>	jdroid-: it's not a queue, it's a toolkit to build queueing systems
| [Tuesday 02 November 2010] [12:53:57] <mato>	sustrik: no, that doesn't help
| [Tuesday 02 November 2010] [12:54:06] <mato>	sustrik: the problem is more complex than that it seems
| [Tuesday 02 November 2010] [12:54:14] <jdroid->	sustrik: i see. are there any projects that could help me understand what's involved with building a queue in zmq?
| [Tuesday 02 November 2010] [12:54:43] <sustrik>	mato: what have you done?
| [Tuesday 02 November 2010] [12:54:49] <mato>	sustrik: moved the CAS
| [Tuesday 02 November 2010] [12:54:58] <mato>	sustrik: still fails on the assert coming out of wait()
| [Tuesday 02 November 2010] [12:55:09] <sustrik>	jdroid: read the guide, that's the best way to understand how the whole thing works
| [Tuesday 02 November 2010] [12:55:24] <sustrik>	mato:  same assert?
| [Tuesday 02 November 2010] [12:55:30] <mato>	sustrik: yes
| [Tuesday 02 November 2010] [12:55:45] <jdroid->	sustrik: fair. 
| [Tuesday 02 November 2010] [12:58:35] <sustrik>	mato: bleh, we'll need to use the mutex on recv side as well
| [Tuesday 02 November 2010] [12:58:57] <sustrik>	there's no other way to make the socketpair and the flag behave as an atomic object
| [Tuesday 02 November 2010] [12:59:15] <sustrik>	so, try this:
| [Tuesday 02 November 2010] [12:59:20] <sustrik>	forget about atomic ops
| [Tuesday 02 November 2010] [12:59:30] <sustrik>	simply make signaled a bool
| [Tuesday 02 November 2010] [12:59:44] <sustrik>	and set/reset it from inside of the critical section
| [Tuesday 02 November 2010] [12:59:58] <sustrik>	the same one you use to send/recv on the sockepair
| [Tuesday 02 November 2010] [14:27:48] <idefine>	is there documentation for scaling to multiple machines?
| [Tuesday 02 November 2010] [14:35:56] <cremes>	idefine: not sure what you are asking for; have you looked at the "tcp" and "pgm" transports?
| [Tuesday 02 November 2010] [14:42:14] <stephank>	Bindings related question, because a couple of us node.js folks are working on this. We're not really following the binding guidelines, because node.js' socket API isn't traditional either. Multi-part messages were just implemented as `sock.send(part1, part2);` and I was wondering if we were missing important use-cases.
| [Tuesday 02 November 2010] [14:42:40] <stephank>	For example, would it make sense to do any significant (possibly async) work between submitting message parts, or the like?
| [Tuesday 02 November 2010] [14:43:38] <stephank>	Or is multi-part's intention really only to submit logically separate parts to a REQ, like say HTTP headers and body separate?
| [Tuesday 02 November 2010] [14:52:31] <cremes>	stephank: i think there are probably a few cases where submitting message parts async would be useful
| [Tuesday 02 November 2010] [14:52:52] <cremes>	imagine a scenario where each part has different computational requirements, for example
| [Tuesday 02 November 2010] [14:53:19] <cremes>	that being said, i don't think the message is transmitted until all parts are "sent" via the api
| [Tuesday 02 November 2010] [14:53:25] <pieterh>	stephank, multi-part's intention is to provide an easy way to subframe a message
| [Tuesday 02 November 2010] [14:53:30] <cremes>	so from that perspective, you aren't saving any time
| [Tuesday 02 November 2010] [14:53:35] <pieterh>	e.g. to create routing envelopes
| [Tuesday 02 November 2010] [14:53:41] <pieterh>	(see chapter 3 of the Guide)
| [Tuesday 02 November 2010] [14:53:53] <pieterh>	and to allow zero-copy on subframes, independently
| [Tuesday 02 November 2010] [14:54:08] <pieterh>	i.e. write a message envelope from one buffer and a message body from another, without copy
| [Tuesday 02 November 2010] [14:54:45] <pieterh>	there are no use cases I've seen where apps do real work in between sending or receiving message parts
| [Tuesday 02 November 2010] [14:55:35] <pieterh>	you cannot sensibly do any logic (loops, conditional) between parts of a single message
| [Tuesday 02 November 2010] [14:56:00] <pieterh>	maybe in some cases, e.g. using the contents of a header to know how many parts to read
| [Tuesday 02 November 2010] [14:56:05] <pieterh>	hth
| [Tuesday 02 November 2010] [14:56:50] <stephank>	Good points. So, would it make sense to then say, leave the queueing to the user?
| [Tuesday 02 November 2010] [14:57:16] <pieterh>	queuing of message parts?
| [Tuesday 02 November 2010] [14:57:30] <pieterh>	the best model I've found is (a) build message from parts (b) send it
| [Tuesday 02 November 2010] [14:57:44] <pieterh>	and (c) read all message parts into one structure
| [Tuesday 02 November 2010] [14:57:47] <stephank>	That's essentially what MQ does while you are submitting, right?
| [Tuesday 02 November 2010] [14:57:54] <pieterh>	sure
| [Tuesday 02 November 2010] [14:58:13] <pieterh>	you cannot interleave message parts from different messages
| [Tuesday 02 November 2010] [14:58:49] <pieterh>	I'd suggest either keeping the semantics of 'send part + flag to indicate final'
| [Tuesday 02 November 2010] [14:59:09] <pieterh>	or else providing a two step 'construct multipart message' and 'send message' semantic
| [Tuesday 02 November 2010] [14:59:44] <pieterh>	actually sock.send (part1, part2, part3) looks pretty decent
| [Tuesday 02 November 2010] [15:00:00] <pieterh>	but it's not orthogonal with sock.recv
| [Tuesday 02 November 2010] [15:00:03] <stephank>	I think I might be missing something. The only thing I can think of that's missing in an API that demands all parts in a single function call is that there's no access to MQ's queueing that's happening in the background.
| [Tuesday 02 November 2010] [15:00:19] <pieterh>	'all parts
| [Tuesday 02 November 2010] [15:00:27] <pieterh>	'all parts' is an open ended list?
| [Tuesday 02 November 2010] [15:00:49] <stephank>	open ended?
| [Tuesday 02 November 2010] [15:01:05] <pieterh>	sorry, I'm not familiar with JS syntax here
| [Tuesday 02 November 2010] [15:01:13] <pieterh>	can you specify a variable number of arguments?
| [Tuesday 02 November 2010] [15:02:31] <stephank>	Yes, javascript is actually very loose when it comes to function arguments. Node.js is an entirely async environment, and the way it is implemented now is to send multi-part messages using "send(part1, part2, ...);" and receive using a handler that might look like "function(part1, part2, ...) { ... }"
| [Tuesday 02 November 2010] [15:03:03] <pieterh>	so send will work fine
| [Tuesday 02 November 2010] [15:03:14] <pieterh>	but recv will be difficult
| [Tuesday 02 November 2010] [15:03:24] <stephank>	But in JS, a function could potentially be defined as "function() { ... }", but still access it's arguments using a special "arguments" array. So even if the receiver does not know the number of parts ahead, it can still inspect them.
| [Tuesday 02 November 2010] [15:03:27] <pieterh>	since you do not know in advance how many parts you will get
| [Tuesday 02 November 2010] [15:03:45] <pieterh>	you really need to receive into a single structure
| [Tuesday 02 November 2010] [15:03:57] <pieterh>	an array of parts, for example
| [Tuesday 02 November 2010] [15:04:07] <pieterh>	and then you'd naturally send from the same structure
| [Tuesday 02 November 2010] [15:04:21] <pieterh>	so that you recv and send the same data types
| [Tuesday 02 November 2010] [15:04:30] <stephank>	Yes, that's what's happening in the current implementation. It simply builds a javascript array as it's receiving parts, and only calls the handler at the very end.
| [Tuesday 02 November 2010] [15:05:02] <pieterh>	what's the 'handler' and is is 'receiving' parts from the caller or the socket?
| [Tuesday 02 November 2010] [15:05:07] <pieterh>	unclear, sorry
| [Tuesday 02 November 2010] [15:06:01] <stephank>	No problem. :) The handler is the function that will be called from the event loop on the receiving end. Receiving parts was meant as receiving from a socket.
| [Tuesday 02 November 2010] [15:06:08] <pieterh>	ack
| [Tuesday 02 November 2010] [15:06:32] <pieterh>	so it passes an array to the handler
| [Tuesday 02 November 2010] [15:06:43] <stephank>	exactly. :)
| [Tuesday 02 November 2010] [15:06:48] <pieterh>	and the handler can send the same array back out to another socket
| [Tuesday 02 November 2010] [15:07:07] <stephank>	It can, yes
| [Tuesday 02 November 2010] [15:07:09] <pieterh>	try, for fun, implementing some of the examples in the guide,
| [Tuesday 02 November 2010] [15:07:21] <pieterh>	that will help you understand the semantics
| [Tuesday 02 November 2010] [15:07:32] <stephank>	That's a good plan. :)
| [Tuesday 02 November 2010] [15:07:48] <stephank>	We actually lack a decent test suite atm. This is all early work.
| [Tuesday 02 November 2010] [15:08:01] <stephank>	(and it depends on unstable versions of both MQ and node.js)
| [Tuesday 02 November 2010] [15:08:03] <pieterh>	the examples form a decent test of the API syntax
| [Tuesday 02 November 2010] [15:08:29] <pieterh>	especially when you get to more sophisticated apps from ch2 and ch3
| [Tuesday 02 November 2010] [15:08:43] <pieterh>	even in C they need abstractions like the zmsg class
| [Tuesday 02 November 2010] [15:09:33] <Guthur>	are bindings generally avoiding providing high level abstractions of the C API?
| [Tuesday 02 November 2010] [15:09:42] <stephank>	I'll have a closer look soon. Writing these bindings was actually my way of learning the API.
| [Tuesday 02 November 2010] [15:10:07] <pieterh>	Guthur, that's up to binding authors... I suspect some of the high level abstractions will get reused
| [Tuesday 02 November 2010] [15:10:37] <stephank>	pieterh: Thanks for thinking a long. Much appreciated. :)
| [Tuesday 02 November 2010] [15:10:40] <Guthur>	ok, so there is some leeway for binding authors
| [Tuesday 02 November 2010] [15:10:48] <stephank>	and cremes ;)
| [Tuesday 02 November 2010] [15:10:59] <pieterh>	Guthur, yes, and they already do that, especially for send/recv which are very low level in C
| [Tuesday 02 November 2010] [15:11:02] <pieterh>	stephank, np
| [Tuesday 02 November 2010] [15:13:07] <Guthur>	pieterh, Ok, it's just that I have adopted the C# binding and would like to provide a few higher level abstractions
| [Tuesday 02 November 2010] [15:27:29] <pieterh>	Guthur, I think it's worth trying to make abstractions other people can/will reuse
| [Tuesday 02 November 2010] [15:27:44] <pieterh>	which means writing some analysis upfront and publishing that
| [Tuesday 02 November 2010] [15:28:23] <pieterh>	for example I'm interested in building up the abstraction layer in C, being ZFL
| [Tuesday 02 November 2010] [15:59:20] <Guthur>	pieterh, too be honest I thinking mostly of some accessors for sockopts
| [Tuesday 02 November 2010] [15:59:55] <Guthur>	After that I will do work through the examples more and see if anything else comes to me
| [Tuesday 02 November 2010] [16:17:08] <pieterh>	Guthur, sounds good
| [Tuesday 02 November 2010] [16:17:28] <pieterh>	I think the Java binding also does that
| [Tuesday 02 November 2010] [16:55:06] <cremes>	stephank: if you're a node.js guy, you might want to check out zmqmachine (github) which is my 0mq Ruby reactor
| [Tuesday 02 November 2010] [16:55:28] <cremes>	stephank: i only mention it because i read long ago that node.js was influenced by eventmachine
| [Tuesday 02 November 2010] [17:38:58] <idefine>	j #jira
| [Tuesday 02 November 2010] [17:42:34] <stephank>	cremes: Oh, wouldn't know, but sounds possible.
| [Tuesday 02 November 2010] [17:42:49] <stephank>	cremes: I'm looking at Req#send_messages, and I believe we're on the same page there. :)
| [Tuesday 02 November 2010] [17:45:21] <stephank>	I'm wondering if it's worthwhile to do, but it'd definitely be neater if we had a direct binding, and implemented all the js and node-js magic on top of that in js itself.
| [Tuesday 02 November 2010] [17:45:57] <stephank>	Right now, a lot of that magic is in C++, which may be cause of some mysterious stability issues
| [Tuesday 02 November 2010] [17:47:09] <stephank>	Probably is worthwhile :)
| [Tuesday 02 November 2010] [17:47:18] <jhawk28>	hello all
| [Tuesday 02 November 2010] [17:47:28] <stephank>	hi
| [Tuesday 02 November 2010] [17:56:24] <Guthur>	is there any clrzmq users around?
| [Tuesday 02 November 2010] [18:13:15] <jhawk28>	Guthur: sorry - mostly jave for me
| [Tuesday 02 November 2010] [18:22:10] <Guthur>	maybe the zmq mailing list to see if any users fall out of the wood work
| [Tuesday 02 November 2010] [18:23:08] <Guthur>	I'd like to make a raft of changes to the binding but would rather some feedback from users before committing them
| [Tuesday 02 November 2010] [18:23:34] <Guthur>	They are not backwards compatible which makes it more difficult
| [Tuesday 02 November 2010] [20:23:03] <sustrik>	Guthur: making backward incompatble changes is a guaranteed way to piss someone of
| [Tuesday 02 November 2010] [20:23:27] <sustrik>	either add new apis to the existing ones
| [Tuesday 02 November 2010] [20:23:50] <sustrik>	or create a new fork of the binding
| [Tuesday 02 November 2010] [20:24:43] <Guthur>	I was going to just place it on my fork
| [Tuesday 02 November 2010] [20:27:03] <Guthur>	I basically brought it more inline with what I feel is C# coding standard, ie. using namespace
| [Tuesday 02 November 2010] [20:28:00] <Guthur>	a small bug to iron out before I push though
| [Tuesday 02 November 2010] [20:35:27] <Guthur>	sustrik, For the identity option is it only going to be read by the app that created it?
| [Tuesday 02 November 2010] [20:35:45] <Guthur>	and there for to I only have to make sure I obey my own convention?
| [Tuesday 02 November 2010] [20:35:52] <Guthur>	therefore*
| [Tuesday 02 November 2010] [20:51:51] <Guthur>	sustrik, Would the zmq mailing list be a decent call for trying to find some current clrzmq users? 
| [Wednesday 03 November 2010] [01:20:30] <Dylan_Hsu>	hello
| [Wednesday 03 November 2010] [07:56:28] <BooTheHamster>	Hi. I got freeze when call zmq_send() with a socket ZMP_PUSH witch binded on "tcp://*:18001".
| [Wednesday 03 November 2010] [07:56:59] <BooTheHamster>	zmq_send() called with flag set to zero
| [Wednesday 03 November 2010] [07:57:01] <pieterh>	BooTheHamster, does it happen each time?
| [Wednesday 03 November 2010] [07:57:43] <BooTheHamster>	It happen when I try send in first time.
| [Wednesday 03 November 2010] [07:58:17] <BooTheHamster>	Create socket, then bind it and then make send.
| [Wednesday 03 November 2010] [07:58:33] <pieterh>	What version of 0MQ are you using?
| [Wednesday 03 November 2010] [07:58:50] <BooTheHamster>	2.1 from git
| [Wednesday 03 November 2010] [07:59:16] <pieterh>	Are you sure it's blocking in zmq_send and not in zmq_term?
| [Wednesday 03 November 2010] [07:59:48] <BooTheHamster>	Yes
| [Wednesday 03 November 2010] [08:00:58] <pieterh>	Could you post a simple test case?
| [Wednesday 03 November 2010] [08:01:00] <pieterh>	thanks
| [Wednesday 03 November 2010] [08:01:18] <pieterh>	i.e. in a pastebin or gist.github.com
| [Wednesday 03 November 2010] [08:04:37] <BooTheHamster>	I try
| [Wednesday 03 November 2010] [08:17:07] <BooTheHamster>	http://pastebin.com/mDmazfVu
| [Wednesday 03 November 2010] [08:17:24] <BooTheHamster>	I test on Windows, MSVC2005 build
| [Wednesday 03 November 2010] [08:19:37] <BooTheHamster>	It's freeze in int zmq::socket_base_t::send (::zmq_msg_t *msg_, int flags_)
| [Wednesday 03 November 2010] [08:20:26] <BooTheHamster>	xsend in this fucntion return -1
| [Wednesday 03 November 2010] [08:20:51] <BooTheHamster>	    //  Oops, we couldn't send the message. Wait for the next
| [Wednesday 03 November 2010] [08:20:51] <BooTheHamster>	    //  command, process it and try to send the message again.
| [Wednesday 03 November 2010] [08:20:51] <BooTheHamster>	    while (rc != 0) {
| [Wednesday 03 November 2010] [08:20:51] <BooTheHamster>	        if (errno != EAGAIN)
| [Wednesday 03 November 2010] [08:20:51] <BooTheHamster>	            return -1;
| [Wednesday 03 November 2010] [08:20:52] <BooTheHamster>	>>>> here >>>       if (unlikely (process_commands (true, false) != 0))
| [Wednesday 03 November 2010] [08:23:19] <BooTheHamster>	I forget to tell - no clients connected
| [Wednesday 03 November 2010] [08:30:02] <pieterh>	BooTheHamster, this looks like a bug to me
| [Wednesday 03 November 2010] [08:30:10] <pieterh>	could you report it to the zeromq-dev list?
| [Wednesday 03 November 2010] [08:31:04] <pieterh>	send should queue the message and return at once
| [Wednesday 03 November 2010] [08:32:56] <BooTheHamster>	My English very bad :(
| [Wednesday 03 November 2010] [08:33:38] <BooTheHamster>	But I try
| [Wednesday 03 November 2010] [08:47:20] <BooTheHamster>	Maybe I use wrong combination? Socket with ZMQ_PUSH type, bind operation and send?
| [Wednesday 03 November 2010] [08:49:41] <guido_g>	do you have a PULL socket connected?
| [Wednesday 03 November 2010] [08:50:17] <BooTheHamster>	no
| [Wednesday 03 November 2010] [08:50:28] <guido_g>	if not, send might wait until at least one connection has been made
| [Wednesday 03 November 2010] [08:51:30] <guido_g>	http://api.zeromq.org/zmq_socket.html  <- see under Pipeline pattern
| [Wednesday 03 November 2010] [08:54:25] <BooTheHamster>	I undestand. I wrong in first place :). Thanx, guido_g
| [Wednesday 03 November 2010] [08:55:04] <guido_g>	just let a client connect before sending the message
| [Wednesday 03 November 2010] [08:55:12] <guido_g>	see the guide for examples
| [Wednesday 03 November 2010] [08:55:24] <BooTheHamster>	No. I need PUB/SUB pair
| [Wednesday 03 November 2010] [08:55:46] <BooTheHamster>	If no clients connected I need drop data ...
| [Wednesday 03 November 2010] [08:55:59] <guido_g>	still, read the guide for a basic understanding of how it should be done
| [Wednesday 03 November 2010] [08:56:48] <guido_g>	pub/sub and push/pull are completely different things and not interchangable
| [Wednesday 03 November 2010] [08:56:52] <guido_g>	so be careful
| [Wednesday 03 November 2010] [08:57:43] <BooTheHamster>	I use PUSH/PULL in another part of my app, and forget that connection is established.
| [Wednesday 03 November 2010] [08:58:20] <BooTheHamster>	I have second question. The 0MQ sockets is thread safe?
| [Wednesday 03 November 2010] [08:59:55] <guido_g>	no
| [Wednesday 03 November 2010] [09:00:21] <guido_g>	please read the guide, it'll explain most of the questions you might have
| [Wednesday 03 November 2010] [09:04:09] <BooTheHamster>	guido_g: many thanx
| [Wednesday 03 November 2010] [12:41:41] <Guthur>	should there not be an xml file provided for the device tests (zmq_forwarder etc)?
| [Wednesday 03 November 2010] [13:56:56] <Guthur>	what is the rational behind including local_lat etc?
| [Wednesday 03 November 2010] [14:08:12] <cremes>	Guthur: those are examples that 1) show basic usage of the library, and 2) offer a way to benchmark the library on your system
| [Wednesday 03 November 2010] [14:31:04] <Guthur>	cremes: Ok cheers, just wondering
| [Wednesday 03 November 2010] [14:31:48] <Guthur>	I personally used the guide and associated demos as my learning guide
| [Wednesday 03 November 2010] [15:53:01] <mleonb>	How do I get gcc to link with zmq.h on os x
| [Wednesday 03 November 2010] [15:59:49] <xraid>	mleonb: i used g++ -Wall -I/usr/local/include -L/usr/local/lib main.cpp -lzmq -o main
| [Wednesday 03 November 2010] [16:00:12] <xraid>	or g++ `pkg-config --libs --cflags libzmq` -o client client.cpp
| [Wednesday 03 November 2010] [17:13:05] <Guthur>	how does a noblock recv throwing an exception when there is no resource sound like in terms of an binding?
| [Wednesday 03 November 2010] [17:14:03] <Guthur>	The user would of course most like choose to continue execution when it appropriate
| [Wednesday 03 November 2010] [17:14:58] <mikko>	php-zmq does that
| [Wednesday 03 November 2010] [17:16:30] <Guthur>	I felt it was better than trying to catch the special EAGAIN case in the recv and doing something different
| [Wednesday 03 November 2010] [17:17:15] <Guthur>	It at least exposes it to the user so they can take special action if so desired
| [Wednesday 03 November 2010] [18:49:06] <Guthur>	Could/should I mention the revise C# binding I have been working on on the C# binding page http://www.zeromq.org/bindings:clr 
| [Wednesday 03 November 2010] [20:24:23] <Guthur>	what is the reason IPC doesn't work on windows?
| [Wednesday 03 November 2010] [20:36:10] <Guthur>	oh nevermind I found the reason
| [Thursday 04 November 2010] [00:19:06] <andrewvc>	anyone know when the planned release date for ZMQ_FD is?
| [Thursday 04 November 2010] [04:43:24] <sustrik>	Guthur: hi
| [Thursday 04 November 2010] [04:43:32] <sustrik>	i haven't been around yesterday
| [Thursday 04 November 2010] [04:43:49] <sustrik>	how it's going? do you need any help from me?
| [Thursday 04 November 2010] [04:44:36] <Guthur>	sustrik: Hi sustrik, no I think everything is good at the moment
| [Thursday 04 November 2010] [04:44:52] <sustrik>	goodo
| [Thursday 04 November 2010] [04:45:19] <Guthur>	cheers
| [Thursday 04 November 2010] [04:45:48] <Guthur>	I was really hoping some clrzmq users would come out of the woodwork though, to try and get some perspective
| [Thursday 04 November 2010] [04:48:12] <sustrik>	it's hard to get win community to participatre
| [Thursday 04 November 2010] [04:48:21] <sustrik>	that's my feeling, at least
| [Thursday 04 November 2010] [04:50:03] <Guthur>	It's a shame really.
| [Thursday 04 November 2010] [04:50:41] <sustrik>	there are 28 watchers on the project
| [Thursday 04 November 2010] [04:50:51] <sustrik>	you can try to speak to them directly
| [Thursday 04 November 2010] [04:51:00] <sustrik>	but maybe it's not even worth of it
| [Thursday 04 November 2010] [04:51:32] <Guthur>	I am working through the guide examples at the moment, just coded the "Divide and Conquer" one this morning, I'll test it once I get home from work, and continue with the others.
| [Thursday 04 November 2010] [04:51:54] <sustrik>	Guthur: that's nice, please send the samples to the mailing list
| [Thursday 04 November 2010] [04:52:02] <sustrik>	pieter will add them to the guide
| [Thursday 04 November 2010] [04:53:22] <Guthur>	It's both a good way for me to explore more of 0MQ and good as a test.
| [Thursday 04 November 2010] [04:53:53] <Guthur>	I'm developing on Windows VM though, so IPC isn't available
| [Thursday 04 November 2010] [04:54:29] <Guthur>	I've been too lazy to try and get it work on linux with Mono yet
| [Thursday 04 November 2010] [04:56:56] <sustrik>	Guthur: no much point
| [Thursday 04 November 2010] [04:57:07] <sustrik>	Win is a primary target for .net
| [Thursday 04 November 2010] [04:57:21] <sustrik>	mono is kind of minor platform
| [Thursday 04 November 2010] [04:57:57] <sustrik>	in any case there are mono builds in the daily builds, so you can at least see whether it compiles with mono
| [Thursday 04 November 2010] [05:03:13] <CIA-20>	zeromq2: 03Martin Sustrik 07master * rb90e621 10/ src/devpoll.cpp : 
| [Thursday 04 November 2010] [05:03:13] <CIA-20>	zeromq2: minor typo fixed
| [Thursday 04 November 2010] [05:03:13] <CIA-20>	zeromq2: Devpoll polling mechanism used ZMQ_HAVE_SOLRIS instead of
| [Thursday 04 November 2010] [05:03:13] <CIA-20>	zeromq2: ZMQ_HAVE_SOLARIS in one case. Fixed.
| [Thursday 04 November 2010] [05:03:13] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/cfKtNR
| [Thursday 04 November 2010] [05:04:22] <Guthur>	I'll maybe give it a try when I've finished the example dev work
| [Thursday 04 November 2010] [05:04:47] <Guthur>	mostly for my own curiosity 
| [Thursday 04 November 2010] [05:41:23] <mikko>	good morning
| [Thursday 04 November 2010] [06:00:00] <sustrik>	mornin'
| [Thursday 04 November 2010] [06:01:01] <pieterh>	mikko: hi :-)
| [Thursday 04 November 2010] [06:13:22] <mikko>	hmm, zeromq perl seems to have occasional failures against maint
| [Thursday 04 November 2010] [06:13:33] <mikko>	how close is the master being released as alpha or beta?
| [Thursday 04 November 2010] [06:26:07] <sustrik>	mikko: the idea was to release it shortly
| [Thursday 04 November 2010] [06:26:18] <sustrik>	what's the problem with perl bindings?
| [Thursday 04 November 2010] [06:26:29] <sustrik>	the daily build looks to be ok
| [Thursday 04 November 2010] [06:28:47] <DerGuteMoritz>	hmm shouldn't the sleep hack be unecessary as of 2.1?
| [Thursday 04 November 2010] [06:28:55] <DerGuteMoritz>	unnecessary even
| [Thursday 04 November 2010] [06:29:17] <DerGuteMoritz>	I mean between binding/connecting and sending messages
| [Thursday 04 November 2010] [06:31:41] <sustrik>	i think it was never needed
| [Thursday 04 November 2010] [06:32:17] <sustrik>	the only thing that changed for 2.1 is that you don't have to sleep before terminating the program
| [Thursday 04 November 2010] [06:32:28] <DerGuteMoritz>	ah okay
| [Thursday 04 November 2010] [06:32:33] <DerGuteMoritz>	then there must be a problem in my code
| [Thursday 04 November 2010] [06:32:36] <DerGuteMoritz>	thanks!
| [Thursday 04 November 2010] [06:33:42] <mikko>	sustrik: i had to cancel build #59
| [Thursday 04 November 2010] [06:33:46] <mikko>	as it got stuck
| [Thursday 04 November 2010] [06:34:09] <sustrik>	in a test, i suppose?
| [Thursday 04 November 2010] [06:34:13] <mikko>	yes
| [Thursday 04 November 2010] [06:34:46] <sustrik>	then either there's bug in 2.1 or there's a bug in the test
| [Thursday 04 November 2010] [06:35:16] <sustrik>	in any case, 2.1 will be released as development version
| [Thursday 04 November 2010] [06:35:19] <sustrik>	not stable version
| [Thursday 04 November 2010] [06:35:50] <sustrik>	thus some bugs are acceptable
| [Thursday 04 November 2010] [06:35:58] <sustrik>	we'll fix them as we go
| [Thursday 04 November 2010] [06:39:03] <mato>	sustrik: ping
| [Thursday 04 November 2010] [06:39:09] <psino>	have functions like socket.unbind(spec) and socket.disconnect(spec) been considered/discussed somewhere?
| [Thursday 04 November 2010] [06:39:14] <mato>	sustrik: hi
| [Thursday 04 November 2010] [06:39:22] <mato>	sustrik: so, i have the auto-resizing signaler
| [Thursday 04 November 2010] [06:39:25] <mato>	sustrik: it seems to work
| [Thursday 04 November 2010] [06:39:30] <sustrik>	mato: great
| [Thursday 04 November 2010] [06:39:47] <mato>	sustrik: i've also carefully refactored all the platform-dependent messy bits as much as i can
| [Thursday 04 November 2010] [06:39:48] <sustrik>	psino: they were discussed on the ML couple of times
| [Thursday 04 November 2010] [06:40:01] <sustrik>	good, are you going to post a patch?
| [Thursday 04 November 2010] [06:40:05] <mato>	sustrik: so IMO it's probably suitable for review and inclusion into master
| [Thursday 04 November 2010] [06:40:11] <mato>	sustrik: yes, right after i test on windoze
| [Thursday 04 November 2010] [06:40:12] <sustrik>	ack
| [Thursday 04 November 2010] [06:40:22] <mato>	sustrik: note that on windows i've not bothered with the auto-resizing for now
| [Thursday 04 November 2010] [06:40:31] <sustrik>	sure
| [Thursday 04 November 2010] [06:40:33] <mato>	sustrik: also
| [Thursday 04 November 2010] [06:40:41] <sustrik>	maybe just put a TODO comment there
| [Thursday 04 November 2010] [06:40:46] <mato>	sustrik: there is one
| [Thursday 04 November 2010] [06:41:01] <mato>	sustrik: one other thing; i've inverted some of the logic regarding blocking/non-blocking mode
| [Thursday 04 November 2010] [06:41:10] <sustrik>	?
| [Thursday 04 November 2010] [06:41:28] <mato>	sustrik: i guess my question is; which call path of signaler::recv() should be more optimal (less syscalls)
| [Thursday 04 November 2010] [06:41:39] <mato>	sustrik: the one where block=false or the one where block=true
| [Thursday 04 November 2010] [06:41:57] <mato>	sustrik: but this only affects windoze and platforms w/o MSG_DONTWAIT (AIX, HPUX)
| [Thursday 04 November 2010] [06:42:05] <sustrik>	yes
| [Thursday 04 November 2010] [06:42:09] <sustrik>	let me think
| [Thursday 04 November 2010] [06:42:10] <mato>	sustrik: so not critical; you can review my changes
| [Thursday 04 November 2010] [06:42:25] <mato>	sustrik: once i post the patch; it's easier when you have the code in front of you
| [Thursday 04 November 2010] [06:42:39] <mato>	sustrik: IMO the block=0 path should be optimal
| [Thursday 04 November 2010] [06:42:40] <sustrik>	non-blocking should be faster imo
| [Thursday 04 November 2010] [06:42:46] <mato>	sustrik: why?
| [Thursday 04 November 2010] [06:43:02] <sustrik>	because you do blocking call only if there's nothing to process anyway
| [Thursday 04 November 2010] [06:43:04] <mato>	sustrik: block=0 is used in the actual processing loops in the io/thread and socket_base_t
| [Thursday 04 November 2010] [06:43:14] <mato>	sustrik: um, sorry, block=1
| [Thursday 04 November 2010] [06:43:19] <sustrik>	is it
| [Thursday 04 November 2010] [06:43:22] <mato>	yes
| [Thursday 04 November 2010] [06:43:22] <sustrik>	let me see
| [Thursday 04 November 2010] [06:44:12] <sustrik>	io_thread.cpp: int rc = signaler.recv (&cmd, false);
| [Thursday 04 November 2010] [06:44:21] <mato>	yeah, you're right
| [Thursday 04 November 2010] [06:44:52] <mato>	same in socket_base.cpp the final "Process all commands" loop also uses non-blocking
| [Thursday 04 November 2010] [06:44:58] <mato>	ok
| [Thursday 04 November 2010] [06:45:07] <mato>	so the non-blocking path should be faster
| [Thursday 04 November 2010] [06:45:11] <mato>	i'll do it that way then
| [Thursday 04 November 2010] [06:45:15] <sustrik>	ok
| [Thursday 04 November 2010] [06:45:44] <sustrik>	btw, what do you think of the proposed FD_SETSIZE patch?
| [Thursday 04 November 2010] [06:45:50] <sustrik>	would it work?
| [Thursday 04 November 2010] [06:46:02] <mato>	i've not been reading the ML, sorry
| [Thursday 04 November 2010] [06:46:13] <mato>	i'll look at it after I get this patch in shape
| [Thursday 04 November 2010] [06:46:15] <sustrik>	in short my suggestion is:
| [Thursday 04 November 2010] [06:46:24] <sustrik>	add FD_SETSIZE 1024 to select.cpp
| [Thursday 04 November 2010] [06:46:33] <sustrik>	thus it won't affect anything else
| [Thursday 04 November 2010] [06:46:41] <sustrik>	single line change
| [Thursday 04 November 2010] [06:47:09] <mato>	it'd need to be there and in zmq.cpp for zmq_poll
| [Thursday 04 November 2010] [06:47:20] <mato>	well, it makes the situation better
| [Thursday 04 November 2010] [06:47:25] <sustrik>	later on
| [Thursday 04 November 2010] [06:47:26] <mato>	but doesn't solve the zmq.h problem
| [Thursday 04 November 2010] [06:47:32] <sustrik>	zmq_poll is not that critical
| [Thursday 04 November 2010] [06:47:37] <mato>	true
| [Thursday 04 November 2010] [06:47:44] <mato>	but it still doesn't solve the zmq.h problem
| [Thursday 04 November 2010] [06:47:59] <sustrik>	not including winsock you mean?
| [Thursday 04 November 2010] [06:48:09] <mato>	and you'd need to be sure that select.cpp defines FD_SETSIZE *before* including anything that might include winsock.h
| [Thursday 04 November 2010] [06:48:12] <mato>	yes
| [Thursday 04 November 2010] [06:48:17] <sustrik>	i do
| [Thursday 04 November 2010] [06:48:30] <sustrik>	the zmq.h problem is probably insolvable
| [Thursday 04 November 2010] [06:48:40] <sustrik>	SOCKET seems to be platform-dependent
| [Thursday 04 November 2010] [06:48:55] <mato>	ok, but the types you looked at all seemed to be castable to int, no?
| [Thursday 04 November 2010] [06:49:11] <sustrik>	maybe __int64
| [Thursday 04 November 2010] [06:49:14] <sustrik>	so something
| [Thursday 04 November 2010] [06:49:20] <sustrik>	or something
| [Thursday 04 November 2010] [06:49:29] <mato>	dunno
| [Thursday 04 November 2010] [06:49:38] <sustrik>	however, i am not sure where win headers come from
| [Thursday 04 November 2010] [06:49:43] <sustrik>	is it part of win sdk?
| [Thursday 04 November 2010] [06:49:49] <mato>	depends
| [Thursday 04 November 2010] [06:49:56] <mato>	:-)
| [Thursday 04 November 2010] [06:50:02] <sustrik>	is it possible that there are different headers for different systems
| [Thursday 04 November 2010] [06:50:04] <sustrik>	etc.
| [Thursday 04 November 2010] [06:50:12] <mato>	god only knows
| [Thursday 04 November 2010] [06:50:16] <sustrik>	it looks like going to way is mad
| [Thursday 04 November 2010] [06:50:42] <mato>	we'll see
| [Thursday 04 November 2010] [06:50:50] <mato>	ok, i need to get back to this code
| [Thursday 04 November 2010] [06:50:58] <mato>	will reply to your patch on the ML
| [Thursday 04 November 2010] [06:51:01] <mato>	after...
| [Thursday 04 November 2010] [06:51:01] <sustrik>	ok
| [Thursday 04 November 2010] [07:43:55] <pieterh>	sustrik: wrt to that patch
| [Thursday 04 November 2010] [07:44:07] <pieterh>	- select.cpp calls select.hpp which has redundant definitions
| [Thursday 04 November 2010] [07:44:18] <pieterh>	- you must only define FD_SETSIZE if it's not been set externally
| [Thursday 04 November 2010] [07:45:11] <pieterh>	further, it's kind of pathological to insist that we can't set FD_SETSIZE in zmq.h and then include winsock2.h in that same file
| [Thursday 04 November 2010] [07:49:25] <sustrik>	pieterh: select.o is an internal compilation unit
| [Thursday 04 November 2010] [07:49:32] <sustrik>	it has nothing to do with what user sets
| [Thursday 04 November 2010] [07:49:43] <sustrik>	it's compiled when library is compiled
| [Thursday 04 November 2010] [07:49:49] <sustrik>	not when client app is compiled
| [Thursday 04 November 2010] [07:51:24] <pieterh>	i don't think you really understand
| [Thursday 04 November 2010] [07:51:50] <sustrik>	?
| [Thursday 04 November 2010] [07:51:52] <pieterh>	when you compile a C/C++ source file, you can define symbols externally
| [Thursday 04 November 2010] [07:52:00] <pieterh>	on the command line, or in the Windows project file
| [Thursday 04 November 2010] [07:52:02] <pieterh>	right?
| [Thursday 04 November 2010] [07:52:11] <sustrik>	yes
| [Thursday 04 November 2010] [07:52:23] <pieterh>	if you are building 0MQ for a server style scenario
| [Thursday 04 November 2010] [07:52:36] <pieterh>	you will set -DFD_SETSIZE=16000
| [Thursday 04 November 2010] [07:52:40] <sustrik>	ok, i see
| [Thursday 04 November 2010] [07:52:42] <pieterh>	winsock2.h will respect this
| [Thursday 04 November 2010] [07:52:44] <pieterh>	ok?
| [Thursday 04 November 2010] [07:52:49] <pieterh>	you cannot simply override that
| [Thursday 04 November 2010] [07:52:50] <sustrik>	we have all compile time settings in config.hpp
| [Thursday 04 November 2010] [07:52:57] <sustrik>	probably it should go there as well
| [Thursday 04 November 2010] [07:53:03] <pieterh>	no
| [Thursday 04 November 2010] [07:53:13] <pieterh>	you must do the conditional setting just before including winsock2.h
| [Thursday 04 November 2010] [07:53:26] <mato>	pieterh: are you seriously suggesting that 0MQ on Windows in it's current state using select() makes any sense at all to run with FD_SETSIZE=16000 ?
| [Thursday 04 November 2010] [07:53:42] <pieterh>	mato: considering that 0MQ encourages lots of connections, yes
| [Thursday 04 November 2010] [07:53:47] <pieterh>	especially if I'm testing stuff
| [Thursday 04 November 2010] [07:53:50] <pieterh>	it's an example
| [Thursday 04 November 2010] [07:53:55] <pieterh>	1024 is definitely too small
| [Thursday 04 November 2010] [07:54:00] <mato>	pieterh: It's *broken*
| [Thursday 04 November 2010] [07:54:02] <pieterh>	we hit this problem with Xitami quite regularly
| [Thursday 04 November 2010] [07:54:03] <mato>	pieterh: make IOCP work
| [Thursday 04 November 2010] [07:54:17] <pieterh>	that's not the point, really, and not an answer here
| [Thursday 04 November 2010] [07:54:25] <mato>	pieterh: you *cannot* expect any sane performance out of a select() loop with 16k descriptors in it
| [Thursday 04 November 2010] [07:54:35] <pieterh>	making this work fairly well is _trivial_ and I'm really kind of amused by the debate
| [Thursday 04 November 2010] [07:54:42] <pieterh>	16k is an example, mat
| [Thursday 04 November 2010] [07:54:43] <pieterh>	mato
| [Thursday 04 November 2010] [07:54:45] <pieterh>	an example
| [Thursday 04 November 2010] [07:54:52] <pieterh>	it could be 4k or 8k
| [Thursday 04 November 2010] [07:55:14] <sustrik>	mato: there has to be a compile time setting for the value
| [Thursday 04 November 2010] [07:55:25] <pieterh>	you (a) cannot leave the 64 default
| [Thursday 04 November 2010] [07:55:34] <pieterh>	(b) you cannot say "make IOCP work" as an answer
| [Thursday 04 November 2010] [07:55:39] <mato>	sustrik: do we have a user who *needs* >1024 connections on windows right now?
| [Thursday 04 November 2010] [07:55:40] <pieterh>	(c) cannot FORCE 1024 as a value
| [Thursday 04 November 2010] [07:55:51] <sustrik>	i don't care what the default is
| [Thursday 04 November 2010] [07:55:53] <mato>	sustrik: if not, then I'm not into random "examples"
| [Thursday 04 November 2010] [07:55:59] <pieterh>	it's rather inane to even discuss this
| [Thursday 04 November 2010] [07:56:00] <sustrik>	the point is that it should be configurable
| [Thursday 04 November 2010] [07:56:04] <pieterh>	if the user has set a value externally, respect that
| [Thursday 04 November 2010] [07:56:15] <pieterh>	it is not the library's job to override that
| [Thursday 04 November 2010] [07:56:24] <sustrik>	the question is where to set it
| [Thursday 04 November 2010] [07:56:26] <mato>	sustrik: then if it's to be configurable, just use #ifndef FD_SETSIZE in your current patch
| [Thursday 04 November 2010] [07:56:32] <pieterh>	well, precisely
| [Thursday 04 November 2010] [07:56:41] <pieterh>	and sustrik: you set it just before including winsock2.h
| [Thursday 04 November 2010] [07:56:48] <mato>	sustrik: it's a broken windows API, if someone wants to override it then they should just -DFD_SETSIZE manually
| [Thursday 04 November 2010] [07:56:51] <sustrik>	why not have all the compile-time options at the same place?
| [Thursday 04 November 2010] [07:56:55] <pieterh>	there is no other safe place, especially given the rather tortuous structures in the code
| [Thursday 04 November 2010] [07:57:01] <mato>	sustrik: because this is one stupid broken windows API
| [Thursday 04 November 2010] [07:57:02] <sustrik>	config.hpp
| [Thursday 04 November 2010] [07:57:19] <sustrik>	:
| [Thursday 04 November 2010] [07:57:27] <sustrik>	   fd_setsize = 1024
| [Thursday 04 November 2010] [07:57:28] <mato>	sustrik: and it's broken because including winsock.h has stupid side-effects
| [Thursday 04 November 2010] [07:57:33] <sustrik>	then, in select.cpp
| [Thursday 04 November 2010] [07:57:44] <sustrik>	#define FD_SETSIZE fd_setsize
| [Thursday 04 November 2010] [07:57:50] <pieterh>	sustrik: that's fine but it's cream on the cake
| [Thursday 04 November 2010] [07:57:52] <mato>	sustrik: it's a macro, config.hpp does not have macros in it
| [Thursday 04 November 2010] [07:58:01] <sustrik>	see abover
| [Thursday 04 November 2010] [07:58:10] <mato>	see what?
| [Thursday 04 November 2010] [07:58:15] <pieterh>	plus, it's system dependent
| [Thursday 04 November 2010] [07:58:24] <pieterh>	do you want to pollute config.hpp with win32 stuff?
| [Thursday 04 November 2010] [07:58:33] <pieterh>	it should really go into windows.hpp
| [Thursday 04 November 2010] [07:58:37] <mato>	sustrik: just change your patch to only redefine FD_SETSIZE in select.cpp if it's not already set
| [Thursday 04 November 2010] [07:58:48] <mato>	sustrik: i think that will make pieter happy
| [Thursday 04 November 2010] [07:58:53] <sustrik>	config.hpp are all some kind of wierd tuning options
| [Thursday 04 November 2010] [07:58:58] <pieterh>	mato: well, that's the patch I already submitted
| [Thursday 04 November 2010] [07:59:39] <sustrik>	i mean: why having some compile time options set in config.hpp
| [Thursday 04 November 2010] [07:59:41] <mato>	pieterh: i'm happy with anything as long as zmq.h doesn't muck with the value more than is neccessary
| [Thursday 04 November 2010] [07:59:47] <sustrik>	and others passed as -Dwhatever
| [Thursday 04 November 2010] [07:59:52] <pieterh>	mato: zmq.h ALREADY mucks up that value
| [Thursday 04 November 2010] [07:59:59] <pieterh>	and it's entirely orthogonal to this thread
| [Thursday 04 November 2010] [08:00:00] <mato>	pieterh: can you solve that problem? no...
| [Thursday 04 November 2010] [08:00:08] <pieterh>	mato: yes, of course
| [Thursday 04 November 2010] [08:00:15] <pieterh>	you should not be including winsock2.h in zmq.h
| [Thursday 04 November 2010] [08:00:24] <pieterh>	since all you want is to grab an integer typedef afaics
| [Thursday 04 November 2010] [08:00:28] <mato>	pieterh: i'm interested to see how you implement that...
| [Thursday 04 November 2010] [08:00:28] <pieterh>	but it's a separate thread
| [Thursday 04 November 2010] [08:00:33] <pieterh>	sure, sure
| [Thursday 04 November 2010] [08:00:45] <pieterh>	not my problem, mato
| [Thursday 04 November 2010] [08:01:04] <mato>	pieterh: you don't have a problem at all AFAICS; even now you can just -DFD_SETSIZE=whatever
| [Thursday 04 November 2010] [08:01:08] <pieterh>	as I recall you were the one insisting loudly that zmq.h could not touch the app's setting for FD_SETSIZE
| [Thursday 04 November 2010] [08:01:13] <pieterh>	i am not concerned with that at all
| [Thursday 04 November 2010] [08:01:27] <mato>	pieterh: so, even now you can -DFD_SETSIZE=something....
| [Thursday 04 November 2010] [08:01:33] <pieterh>	however, I do want to remove that FAQ entry justifying a broken default for select(
| [Thursday 04 November 2010] [08:01:33] <mato>	pieterh: and it will all work
| [Thursday 04 November 2010] [08:01:47] <pieterh>	mato: broken by default, right?
| [Thursday 04 November 2010] [08:01:51] <pieterh>	excellent software design
| [Thursday 04 November 2010] [08:01:55] <pieterh>	excuse me, I have better things to do
| [Thursday 04 November 2010] [08:01:57] <pieterh>	toodeloo
| [Thursday 04 November 2010] [08:02:11] <sustrik>	ok, what default are we going to use?
| [Thursday 04 November 2010] [08:02:12] <sustrik>	1024?
| [Thursday 04 November 2010] [08:02:14] <sustrik>	64?
| [Thursday 04 November 2010] [08:02:16] <sustrik>	256?
| [Thursday 04 November 2010] [08:02:35] <mato>	1024 is probably safe enough
| [Thursday 04 November 2010] [08:02:40] <sustrik>	ok
| [Thursday 04 November 2010] [08:02:49] <mato>	anything above 1024 and you don't want to be using select() anyway
| [Thursday 04 November 2010] [08:03:02] <sustrik>	not that you have an option :)
| [Thursday 04 November 2010] [08:03:13] <sustrik>	i think there's poll in win7 btw
| [Thursday 04 November 2010] [08:03:17] <mato>	no, but if someone does run into that on windows and complains, then we know we have a user
| [Thursday 04 November 2010] [08:03:25] <mato>	who needs performance with more connections
| [Thursday 04 November 2010] [08:03:39] <mato>	at the moment, the only person who has complained AFAIK is pieter
| [Thursday 04 November 2010] [08:06:51] <sustrik>	http://msdn.microsoft.com/en-us/library/ms741669%28v=VS.85%29.aspx
| [Thursday 04 November 2010] [08:07:24] <sustrik>	looks like for vista and win7 there's a way to avoid select altogrther
| [Thursday 04 November 2010] [08:08:34] <mato>	sustrik: right, that would be nice... at least as a partial fix
| [Thursday 04 November 2010] [08:08:51] <mato>	sustrik: even poll gets slow with lots of sockets, but the only alternative there on windows is IOCP
| [Thursday 04 November 2010] [08:09:52] <sustrik>	but is has no FD_SETSIZE :)
| [Thursday 04 November 2010] [08:10:01] <mato>	yes, sure
| [Thursday 04 November 2010] [08:14:09] <CIA-20>	zeromq2: 03Martin Sustrik 07master * r2246689 10/ src/select.cpp : 
| [Thursday 04 November 2010] [08:14:09] <CIA-20>	zeromq2: FD_SETSIZE for internal polling defaults to 1024
| [Thursday 04 November 2010] [08:14:09] <CIA-20>	zeromq2: If, when compiling 0MQ you don't set FD_SETSIZE,
| [Thursday 04 November 2010] [08:14:09] <CIA-20>	zeromq2: it defaults to 1024 rather than to 64.
| [Thursday 04 November 2010] [08:14:09] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/aq7TfT
| [Thursday 04 November 2010] [08:14:23] <sustrik>	pieterh: ok, it's there
| [Thursday 04 November 2010] [08:14:30] <sustrik>	can you give it a try?
| [Thursday 04 November 2010] [08:14:39] <mato>	sustrik: he's not online
| [Thursday 04 November 2010] [08:14:54] <sustrik>	anyway, it's there
| [Thursday 04 November 2010] [09:51:59] <sustrik>	pieterh: can you check whether the patch works as expected?
| [Thursday 04 November 2010] [09:52:25] <pieterh>	sustrik: ack, will do
| [Thursday 04 November 2010] [09:52:30] <sustrik>	thx
| [Thursday 04 November 2010] [10:14:54] <mato>	sustrik: did you take a look at my signaler patch?
| [Thursday 04 November 2010] [10:15:19] <sustrik>	i'm heading towards it
| [Thursday 04 November 2010] [10:15:19] <mato>	sustrik: IMO it's safe to apply to master
| [Thursday 04 November 2010] [10:15:21] <mato>	thx
| [Thursday 04 November 2010] [10:15:31] <sustrik>	will getr there in 15 mins
| [Thursday 04 November 2010] [10:16:07] <mato>	incidentally, the patch moves a lot of things around, so it's best to look at the code after you apply it
| [Thursday 04 November 2010] [10:16:37] <sustrik>	yes, i've already gave it a look
| [Thursday 04 November 2010] [10:16:42] <sustrik>	and decided to apply it first :)
| [Thursday 04 November 2010] [10:23:26] <Guthur>	is there a roadmap or timeframe for 2.1?
| [Thursday 04 November 2010] [10:23:48] <mato>	Guthur: Yes, "Soon"
| [Thursday 04 November 2010] [10:24:12] <mato>	Guthur: the main thing missing is a proper documentation update & review of the reference manual, and I'm busy with client work :-(
| [Thursday 04 November 2010] [10:24:24] <Guthur>	'Ready when its Ready'
| [Thursday 04 November 2010] [10:24:26] <mato>	Yes.
| [Thursday 04 November 2010] [10:25:39] <Guthur>	Does the documentation require many changes?
| [Thursday 04 November 2010] [10:25:59] <mato>	Not really but I need a free day to read through it systematically.
| [Thursday 04 November 2010] [10:26:02] <Guthur>	I unfortunately have not been following developments so could not really offer much help there
| [Thursday 04 November 2010] [10:26:40] <sustrik>	Guthur: does it matter to you?
| [Thursday 04 November 2010] [10:26:49] <mato>	Well, you can help by starting to use the current Git master if you're not already doing so, and yell if anything is broken.
| [Thursday 04 November 2010] [10:26:50] <sustrik>	the code is available on gitbub
| [Thursday 04 November 2010] [10:26:55] <sustrik>	do make dist
| [Thursday 04 November 2010] [10:26:59] <Guthur>	not particularly to be honest
| [Thursday 04 November 2010] [10:26:59] <sustrik>	and you have a package
| [Thursday 04 November 2010] [10:27:22] <Guthur>	I just like to see 0MQ moving forward
| [Thursday 04 November 2010] [10:29:12] <sustrik>	so do i :)
| [Thursday 04 November 2010] [10:30:16] <Guthur>	I may actually be able to bring 0MQ into a project at work, and it would be nice if a release version of 2.1 was the baseline, just because it is so imminent
| [Thursday 04 November 2010] [10:31:05] <sustrik>	well, start with what's on master right now, then switch to official 2.1.0 when it is released
| [Thursday 04 November 2010] [10:31:10] <sustrik>	no changes are planned
| [Thursday 04 November 2010] [10:31:15] <sustrik>	that would break you app
| [Thursday 04 November 2010] [10:31:31] <sustrik>	your apps
| [Thursday 04 November 2010] [10:32:10] <Guthur>	sounds good, it's only tentatively planned at the moment, but here's hoping
| [Thursday 04 November 2010] [10:38:52] <mato>	sustrik: I just tested the FD_SETSIZE patch you applied
| [Thursday 04 November 2010] [10:39:16] <mato>	sustrik: and (this is very strange), for me it seems to break every application; local_thr just exits.
| [Thursday 04 November 2010] [10:39:22] <mato>	sustrik: Same for my applications.
| [Thursday 04 November 2010] [10:39:36] <mato>	sustrik: If I take out the FD_SETSIZE definition of 1024 then it all works again.
| [Thursday 04 November 2010] [10:39:50] <mato>	pieterh: Did you test that patch?!
| [Thursday 04 November 2010] [11:01:24] <andrewvc_>	cremes: you around?
| [Thursday 04 November 2010] [11:01:42] <cremes>	andrewvc_: yep, what's up?
| [Thursday 04 November 2010] [11:01:50] <andrewvc_>	yo
| [Thursday 04 November 2010] [11:02:06] <andrewvc_>	just did a little work on ZMQ_FD and ZMQ_EVENTS for ffi-rzmq last night
| [Thursday 04 November 2010] [11:02:24] <cremes>	ah, most excellent! that was on my to-do list as soon as it was released
| [Thursday 04 November 2010] [11:02:38] <andrewvc_>	yeah, it seems to work well enough from master
| [Thursday 04 November 2010] [11:02:42] <andrewvc_>	was going to see about maybe making an eventmachine backend option for zmqmachine
| [Thursday 04 November 2010] [11:02:53] <cremes>	i like that idea
| [Thursday 04 November 2010] [11:03:16] <cremes>	did you need some help with the new 2.1 stuff or are you prepping a pull request?
| [Thursday 04 November 2010] [11:03:23] <andrewvc_>	hmmm
| [Thursday 04 November 2010] [11:03:32] <andrewvc_>	well, I wrote a very minimal test case
| [Thursday 04 November 2010] [11:03:38] <andrewvc_>	they both seem to work
| [Thursday 04 November 2010] [11:03:53] <andrewvc_>	It's probably good to go, I mean, I just needed to add the right constants and types in
| [Thursday 04 November 2010] [11:04:40] <sustrik>	mato: yuck
| [Thursday 04 November 2010] [11:05:12] <sustrik>	any idea what the problem is?
| [Thursday 04 November 2010] [11:05:24] <andrewvc_>	https://github.com/andrewvc/ffi-rzmq/commit/4b306b00e26f0c8a0b46b0531c14d1c873d2ddb5#diff-2
| [Thursday 04 November 2010] [11:05:27] <andrewvc_>	that enough coverage
| [Thursday 04 November 2010] [11:05:57] <mato>	sustrik: I wrote an email. I don't know, some Windoze crap
| [Thursday 04 November 2010] [11:06:23] <mato>	sustrik: ultimately it doesn't work, and allowing anyone to strong-arm you into applying something like this untested is bad.
| [Thursday 04 November 2010] [11:07:04] <sustrik>	mato: how can in possibly require same value for while libzmq?
| [Thursday 04 November 2010] [11:07:18] <mato>	sustrik: cannot parse the above sentence :-)
| [Thursday 04 November 2010] [11:07:22] <mato>	sustrik: i'll call you....
| [Thursday 04 November 2010] [11:07:26] <sustrik>	ack
| [Thursday 04 November 2010] [11:07:35] <cremes>	andrewvc_: yeah, looks good. i didn't think adding support would be very challenging and you just proved it
| [Thursday 04 November 2010] [11:07:35] <andrewvc_>	I did play around with actually, I have some more specs I can write..
| [Thursday 04 November 2010] [11:07:47] <cremes>	if you have more specs, the more the merrier
| [Thursday 04 November 2010] [11:08:00] <andrewvc_>	hehe, yeah lemme just put em in, will take a couple minutes
| [Thursday 04 November 2010] [11:08:18] <cremes>	andrewvc_: do you know if all of the example programs continue to work with 2.1?
| [Thursday 04 November 2010] [11:11:37] <CIA-20>	zeromq2: 03Martin Sustrik 07master * r756f7df 10/ src/select.cpp : 
| [Thursday 04 November 2010] [11:11:37] <CIA-20>	zeromq2: Previous FD_STSIZE patch reverted.
| [Thursday 04 November 2010] [11:11:37] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/deoB7b
| [Thursday 04 November 2010] [11:12:04] <mato>	sustrik: thanks.
| [Thursday 04 November 2010] [11:12:13] <sustrik>	np
| [Thursday 04 November 2010] [11:12:33] <mato>	sustrik: let the ML know also if you can
| [Thursday 04 November 2010] [11:12:58] <sustrik>	i'm in process of doing so
| [Thursday 04 November 2010] [11:14:45] <sustrik>	mato: aha
| [Thursday 04 November 2010] [11:14:58] <sustrik>	it looks like FD_SETSIZE affects the whole socket subsystem
| [Thursday 04 November 2010] [11:15:29] <sustrik>	"The maximum number of sockets that a Windows Sockets application can use is determined at compile time by the manifest constant FD_SETSIZE."
| [Thursday 04 November 2010] [11:15:56] <sustrik>	"If an application is designed to be capable of working with more than 64 sockets, the implementor should define the manifest FD_SETSIZE in every source file before including Winsock2.h."
| [Thursday 04 November 2010] [11:16:18] <sustrik>	which, afaiu means that the libzmq and client app has to have same FD_SETSIZE
| [Thursday 04 November 2010] [11:18:36] <mato>	sustrik: guess so, in which case lets just leave things as they are for now
| [Thursday 04 November 2010] [11:19:02] <mato>	sustrik: since the only obvious way to do that is for a developer to add -DFD_SETSIZE=1024 for all their libraries and applications
| [Thursday 04 November 2010] [11:19:23] <pieterh>	well, mato, the obvious way is to define a sane FD_SETSIZE and allow the developer to override it
| [Thursday 04 November 2010] [11:19:34] <pieterh>	you keep forgetting somehow that zmq.h now defines FD_SETSIZE to 64
| [Thursday 04 November 2010] [11:19:40] <mato>	pieterh: NO IT DOESN'T
| [Thursday 04 November 2010] [11:19:43] <pieterh>	yes, it does
| [Thursday 04 November 2010] [11:19:49] <pieterh>	how are you missing this
| [Thursday 04 November 2010] [11:19:51] <mato>	pieterh: please show me the #define
| [Thursday 04 November 2010] [11:19:58] <mato>	pieterh: in zmq.h
| [Thursday 04 November 2010] [11:19:59] <pieterh>	it includes winsock2.h, right?
| [Thursday 04 November 2010] [11:20:02] <pieterh>	that does it
| [Thursday 04 November 2010] [11:20:11] <pieterh>	if you're not getting that, it explains a lot
| [Thursday 04 November 2010] [11:20:13] <mato>	so what, that's not our fault, and it doesn't stop the developer from overriding it
| [Thursday 04 November 2010] [11:20:19] <pieterh>	so what?
| [Thursday 04 November 2010] [11:20:26] <pieterh>	it means it defines FD_SETSIZE
| [Thursday 04 November 2010] [11:20:34] <pieterh>	YES IT DOES, in your language
| [Thursday 04 November 2010] [11:20:39] <sustrik>	guys, stop it
| [Thursday 04 November 2010] [11:20:41] <mato>	pieterh: why can't you just define FD_SETSIZE yourself?
| [Thursday 04 November 2010] [11:20:53] <mato>	pieterh: and I resent you strong-arming sustrik into applying an untested patch
| [Thursday 04 November 2010] [11:20:56] <pieterh>	I would like to define it before every include of winsock2.h
| [Thursday 04 November 2010] [11:20:58] <sustrik>	the win docs says the FD_SETSIZE has to be same for the whole app
| [Thursday 04 November 2010] [11:21:05] <sustrik>	we are not going to solve that
| [Thursday 04 November 2010] [11:21:17] <sustrik>	it's out of scope of 0mq
| [Thursday 04 November 2010] [11:21:22] <pieterh>	mato: I did say, clearly, I was going to test that this weekend
| [Thursday 04 November 2010] [11:21:30] <pieterh>	the patch was not for sustrik, but for people to play with
| [Thursday 04 November 2010] [11:21:41] <pieterh>	i fail to see why this is so hard
| [Thursday 04 November 2010] [11:21:44] <mato>	it's still a cosmetic change
| [Thursday 04 November 2010] [11:21:48] <pieterh>	so is everything
| [Thursday 04 November 2010] [11:21:55] <pieterh>	that's a meaningless response
| [Thursday 04 November 2010] [11:22:08] <pieterh>	why do you refuse to add that code into zmq.h?
| [Thursday 04 November 2010] [11:22:15] <pieterh>	that's just confusing to me
| [Thursday 04 November 2010] [11:22:31] <mato>	because we don't even know if it'll work correctly
| [Thursday 04 November 2010] [11:22:33] <pieterh>	this should be a 5-minute change
| [Thursday 04 November 2010] [11:22:35] <mato>	you saw what martin's change did
| [Thursday 04 November 2010] [11:22:38] <pieterh>	sweet lord
| [Thursday 04 November 2010] [11:22:40] <mato>	the impact is unknown
| [Thursday 04 November 2010] [11:22:45] <pieterh>	martin took half of my patch
| [Thursday 04 November 2010] [11:22:55] <pieterh>	and furthermore it's trivial to test once you accept that we can make that change
| [Thursday 04 November 2010] [11:23:20] <mato>	why the hell should i accept any change that's not been tested and has weird side effects is not obvious to me
| [Thursday 04 November 2010] [11:23:28] <pieterh>	that is not what I'm requesting
| [Thursday 04 November 2010] [11:23:38] <pieterh>	i'm requesting you do not boycott a change to zmq.h
| [Thursday 04 November 2010] [11:23:53] <pieterh>	that is the sticking point, because that demand makes this fix impossible afaics
| [Thursday 04 November 2010] [11:23:59] <pieterh>	yet your demand makes no sense whatsoever
| [Thursday 04 November 2010] [11:25:14] <mato>	my demand is there to protect the user who may be mixing zmq/non-zmq socket code
| [Thursday 04 November 2010] [11:25:25] <pieterh>	you are, sorry, speaking out of your hat now
| [Thursday 04 November 2010] [11:25:41] <pieterh>	by including winsock2.h you are already messing with the user
| [Thursday 04 November 2010] [11:26:02] <mato>	but I don't have any other choice
| [Thursday 04 November 2010] [11:26:05] <mato>	at the moment
| [Thursday 04 November 2010] [11:26:15] <pieterh>	then you accept that zmq.h defines the limit as 64
| [Thursday 04 November 2010] [11:26:35] <mato>	if I then change something else which as we can see is an invasive *system default*, that is making the problem worse
| [Thursday 04 November 2010] [11:26:47] <pieterh>	? what
| [Thursday 04 November 2010] [11:27:01] <pieterh>	the only problem here is that apps will hit a stupidly low limit
| [Thursday 04 November 2010] [11:27:12] <pieterh>	it is not a *system default*
| [Thursday 04 November 2010] [11:27:17] <pieterh>	where do you get that notion from?
| [Thursday 04 November 2010] [11:27:19] <mato>	ABI default then
| [Thursday 04 November 2010] [11:27:29] <pieterh>	no, it's a hard-coded default in winsock2.h
| [Thursday 04 November 2010] [11:27:30] <mato>	where? from winsock2.h :-)
| [Thursday 04 November 2010] [11:27:32] <pieterh>	yes
| [Thursday 04 November 2010] [11:27:35] <pieterh>	just that one file
| [Thursday 04 November 2010] [11:27:47] <pieterh>	the ABI has no actual limit (or it's much higher)
| [Thursday 04 November 2010] [11:27:56] <mato>	except that as you can see from martin's patch, it does seem to have strange ABI side effects
| [Thursday 04 November 2010] [11:28:09] <pieterh>	it literally says, and you can check, #ifndef FD_SETSIZE / #define FD_SETSIZE 64...
| [Thursday 04 November 2010] [11:28:14] <mato>	if it really did effect *just* the file winsock2.h was included into, then Martin's patch would have worked
| [Thursday 04 November 2010] [11:28:18] <pieterh>	that's because martin's patch was broken
| [Thursday 04 November 2010] [11:28:22] <mato>	how so?
| [Thursday 04 November 2010] [11:28:29] <pieterh>	it was not what I proposed
| [Thursday 04 November 2010] [11:28:32] <pieterh>	i changed select.hpp
| [Thursday 04 November 2010] [11:28:33] <mato>	lol
| [Thursday 04 November 2010] [11:28:35] <pieterh>	he changed select.cpp
| [Thursday 04 November 2010] [11:28:38] <pieterh>	ok, lok
| [Thursday 04 November 2010] [11:28:41] <pieterh>	lol
| [Thursday 04 November 2010] [11:28:58] <sustrik>	guys, please, read what msdn says
| [Thursday 04 November 2010] [11:29:01] <andrewvc_>	cremes: well, I'm glad I started writing extra specs
| [Thursday 04 November 2010] [11:29:11] <sustrik>	all the compilation units in app have to have same FD_SETSIZE
| [Thursday 04 November 2010] [11:29:17] <pieterh>	sustrik: I've written and maintained windows servers for years
| [Thursday 04 November 2010] [11:29:18] <sustrik>	all the libs
| [Thursday 04 November 2010] [11:29:21] <sustrik>	the client app
| [Thursday 04 November 2010] [11:29:22] <pieterh>	yes, all the libs
| [Thursday 04 November 2010] [11:29:24] <mato>	sustrik: I did, but you'll have to convince Pieter and his years of experience with redefining FD_SETSIZE for years
| [Thursday 04 November 2010] [11:29:24] <andrewvc_>	not sure if this is an issue, but if I call IO.new on the FDs, the spec suite fails after a while, 'too many open files'
| [Thursday 04 November 2010] [11:29:25] <sustrik>	etc.
| [Thursday 04 November 2010] [11:29:46] <pieterh>	sustrik, and now 0MQ *imposes* a value of 64, that's it
| [Thursday 04 November 2010] [11:29:52] <pieterh>	unless you override externally
| [Thursday 04 November 2010] [11:30:04] <pieterh>	I'm suggesting we impose a value of 1024, unless you override externally
| [Thursday 04 November 2010] [11:30:04] <sustrik>	sure
| [Thursday 04 November 2010] [11:30:09] <pieterh>	it is simple, obvious, and easy
| [Thursday 04 November 2010] [11:30:18] <sustrik>	you'll have to do that for all the existing libraries
| [Thursday 04 November 2010] [11:30:19] <pieterh>	the only problem is "you may not touch zmq.h" which is a bogus demand
| [Thursday 04 November 2010] [11:30:30] <sustrik>	it's world-wide default, basically
| [Thursday 04 November 2010] [11:30:36] <mato>	sustrik: bingo
| [Thursday 04 November 2010] [11:30:38] <cremes>	andrewvc_: IO.new? where would you use that?
| [Thursday 04 November 2010] [11:30:50] <sustrik>	because any lib
| [Thursday 04 November 2010] [11:30:55] <pieterh>	sustrik: how many other libraries, exactly, does a 0MQ use, which do selects?
| [Thursday 04 November 2010] [11:31:00] <sustrik>	that doesn't redefine it, uses 64
| [Thursday 04 November 2010] [11:31:15] <sustrik>	i mean the libraries client application uses
| [Thursday 04 November 2010] [11:31:24] <andrewvc_>	I was doing I was trying to see if the FD was valid with: #lambda { IO.new(@fd).close }.should_not raise_exception(Errno::EBADF)
| [Thursday 04 November 2010] [11:31:27] <pieterh>	so, when a library like APR uses FD_SETSIZE 2048, they are insane?
| [Thursday 04 November 2010] [11:31:28] <andrewvc_>	is that a bad idea?
| [Thursday 04 November 2010] [11:31:41] <sustrik>	yes
| [Thursday 04 November 2010] [11:31:48] <cremes>	andrewvc_: probably... i don't think the returned FD is a *real* FD
| [Thursday 04 November 2010] [11:32:04] <sustrik>	it you link your app with apr and 0mq at the same time it'll crash :(
| [Thursday 04 November 2010] [11:32:05] <cremes>	i *think* it is a synthetic FD created by the library
| [Thursday 04 November 2010] [11:32:13] <cremes>	but i'm not certain
| [Thursday 04 November 2010] [11:32:24] <andrewvc_>	ahhh, hmm, well it worked in a minimal script I wrote
| [Thursday 04 November 2010] [11:32:25] <DerGuteMoritz>	is that ZMQ_FD?
| [Thursday 04 November 2010] [11:32:25] <pieterh>	sustrik: no, at that point you are doing weird stuff and you can learn to -DFD_SETSIZE=whatever
| [Thursday 04 November 2010] [11:32:34] <andrewvc_>	lemme double check that
| [Thursday 04 November 2010] [11:32:36] <pieterh>	it's not about protecting people who do weird stuff
| [Thursday 04 November 2010] [11:32:40] <pieterh>	it's about making the defaults work sanely
| [Thursday 04 November 2010] [11:33:08] <sustrik>	it's a glabal default, sorry, no way for 0mq to fix it
| [Thursday 04 November 2010] [11:33:12] <pieterh>	from my quick scan, Boost also sets this
| [Thursday 04 November 2010] [11:33:33] <sustrik>	same problem
| [Thursday 04 November 2010] [11:33:45] <pieterh>	oh sweet lord
| [Thursday 04 November 2010] [11:33:59] <pieterh>	ok, guys, your superior windows experience trumps mine
| [Thursday 04 November 2010] [11:34:02] <pieterh>	i give up, thanks
| [Thursday 04 November 2010] [11:34:04] <sustrik>	what i think is what happens in technical terms
| [Thursday 04 November 2010] [11:34:09] <pieterh>	it's ok, sustrik
| [Thursday 04 November 2010] [11:34:18] <pieterh>	there is no point in this
| [Thursday 04 November 2010] [11:34:33] <pieterh>	this is what FAQs are for
| [Thursday 04 November 2010] [11:34:44] <sustrik>	is that WSA subsystem is initialised with value of FD_SETSIZE that's defined in the compilation unit that invokes it
| [Thursday 04 November 2010] [11:34:56] <sustrik>	but -- WSA can be initialised multiple times
| [Thursday 04 November 2010] [11:35:05] <sustrik>	so the later calls are just ignored
| [Thursday 04 November 2010] [11:35:07] <andrewvc_>	cremes: check this out https://gist.github.com/662632
| [Thursday 04 November 2010] [11:35:11] <mato>	sustrik: interestingly, APR seems to define FD_SETSIZE only in the source file that uses select()
| [Thursday 04 November 2010] [11:35:14] <sustrik>	it's insane design
| [Thursday 04 November 2010] [11:35:26] <andrewvc_>	so, that doesn't error, and it does seem to validate the FD as being real
| [Thursday 04 November 2010] [11:35:44] <sustrik>	mato: well, i would rather stick to what MS says
| [Thursday 04 November 2010] [11:35:44] <cremes>	andrewvc_: pastie the results; i haven't pulled those changes yet so i can't run it
| [Thursday 04 November 2010] [11:35:46] <mato>	sustrik: so presumably, there is some way that can be made to work, but we don't know what it is, and we're not going to find out by arguing about this under pressure
| [Thursday 04 November 2010] [11:35:57] <sustrik>	otherwise it can break with systems we haven't tested with
| [Thursday 04 November 2010] [11:35:59] <mato>	sustrik: I agree.
| [Thursday 04 November 2010] [11:36:01] <andrewvc_>	ah, oh yes, well basically it does give you an IO
| [Thursday 04 November 2010] [11:36:13] <pieterh>	mato: if you would like to prove me wrong, properly, try the actual patch I sent, not Martin's version
| [Thursday 04 November 2010] [11:36:15] <andrewvc_>	the spec runs, but after it gets through 90% of the specs jruby crashes
| [Thursday 04 November 2010] [11:36:37] <cremes>	andrewvc_: does it work under mri or rubinius?
| [Thursday 04 November 2010] [11:36:43] <DerGuteMoritz>	andrewvc_: and if you remove the test you mentioned above it works?
| [Thursday 04 November 2010] [11:36:55] <mato>	pieterh: the thing is, you are making me do extra work in order to accept a change I really don't care for.
| [Thursday 04 November 2010] [11:37:01] <andrewvc_>	actually it doesn't work in jruby
| [Thursday 04 November 2010] [11:37:02] <mato>	pieterh: so no. you do that work. produce test results.
| [Thursday 04 November 2010] [11:37:03] <andrewvc_>	works in MRI
| [Thursday 04 November 2010] [11:37:06] <pieterh>	mato: then don't test a patch I did not make and complain to me...
| [Thursday 04 November 2010] [11:37:07] <mato>	pieterh: prove it doesn't break anything.
| [Thursday 04 November 2010] [11:37:08] <DerGuteMoritz>	that ruby binding looks pretty low level
| [Thursday 04 November 2010] [11:37:10] <andrewvc_>	rubinius, lemme check
| [Thursday 04 November 2010] [11:37:18] <pieterh>	I already said I would test my patch, when I submitted it
| [Thursday 04 November 2010] [11:37:24] <pieterh>	it was there for people to play with
| [Thursday 04 November 2010] [11:37:28] <andrewvc_>	this is the FFI binding
| [Thursday 04 November 2010] [11:37:47] <DerGuteMoritz>	andrewvc_: looks like an fd leak somewhere
| [Thursday 04 November 2010] [11:38:20] <pieterh>	cremes, andrewvc_, DerGuteMoritz will you guys stop doing real work and let us argue in peace???
| [Thursday 04 November 2010] [11:38:21] <mato>	ok, enough. If someone produces a tested patch which gets consensus and review from other Windows developers, then it can be applied.
| [Thursday 04 November 2010] [11:38:28] <DerGuteMoritz>	pieterh: :-D
| [Thursday 04 November 2010] [11:38:30] <andrewvc_>	lol
| [Thursday 04 November 2010] [11:38:48] <andrewvc_>	well, it only creates one FD per socket type, so shouldn't be that many FDs
| [Thursday 04 November 2010] [11:38:56] <andrewvc_>	jruby doesn't like that gist I sent
| [Thursday 04 November 2010] [11:38:57] <pieterh>	mato: and you allow me to fix zmq.h too without setting random "I will not accepts"?
| [Thursday 04 November 2010] [11:38:57] <DerGuteMoritz>	andrewvc_: maybe the jruby gc is not as eager as the other implementations'
| [Thursday 04 November 2010] [11:38:58] <andrewvc_>	MRI and RBX do
| [Thursday 04 November 2010] [11:39:12] <DerGuteMoritz>	I see
| [Thursday 04 November 2010] [11:39:13] <andrewvc_>	but only jruby runs the full spec suite
| [Thursday 04 November 2010] [11:39:13] <mato>	pieterh: *If and only if* you can prove it does not break an existing application.
| [Thursday 04 November 2010] [11:39:19] <mato>	pieterh: *prove*
| [Thursday 04 November 2010] [11:39:24] <DerGuteMoritz>	andrewvc_: and the error on that gist is too many fds?
| [Thursday 04 November 2010] [11:39:28] <pieterh>	i am supposed to prove the non-existence of god as well?
| [Thursday 04 November 2010] [11:39:31] <andrewvc_>	no, no error on the gist
| [Thursday 04 November 2010] [11:39:34] <andrewvc_>	jruby hangs
| [Thursday 04 November 2010] [11:39:38] <andrewvc_>	rubinius and MRI work
| [Thursday 04 November 2010] [11:39:43] <DerGuteMoritz>	interesting
| [Thursday 04 November 2010] [11:39:43] <mato>	pieterh: yes, since you're arguing about damn cosmetics
| [Thursday 04 November 2010] [11:39:48] 	 * pieterh wonders how to disprove a negative...
| [Thursday 04 November 2010] [11:39:49] <cremes>	pieterh: :)
| [Thursday 04 November 2010] [11:40:01] <pieterh>	ah, /me knows the answer
| [Thursday 04 November 2010] [11:40:16] <DerGuteMoritz>	andrewvc_: at what point does jruby hang?
| [Thursday 04 November 2010] [11:40:46] <pieterh>	mato: does this burden of proof apply to all patches or only mine?
| [Thursday 04 November 2010] [11:40:49] <andrewvc_>	lemme 
| [Thursday 04 November 2010] [11:40:57] <cremes>	andrewvc_: if it's a reproducible hang, we can probably get the jruby guys to lend a hand
| [Thursday 04 November 2010] [11:41:08] <cremes>	particularly if the other runtimes don't
| [Thursday 04 November 2010] [11:41:16] <pieterh>	and could you please document it so that I know what rules I need to follow?
| [Thursday 04 November 2010] [11:41:30] <mato>	pieterh: dunno. since you're insisting so much, and sustrik and myself are both against, then it seems to apply.
| [Thursday 04 November 2010] [11:41:31] <pieterh>	"mato said on irc" is not particularly good
| [Thursday 04 November 2010] [11:41:39] <pieterh>	not good enough, mato
| [Thursday 04 November 2010] [11:41:42] <pieterh>	rules are documented
| [Thursday 04 November 2010] [11:41:46] <pieterh>	and they apply to everyone
| [Thursday 04 November 2010] [11:42:01] <pieterh>	otherwise it's just shrieking in the chatroom
| [Thursday 04 November 2010] [11:42:06] <mato>	you're really enjoying this, right
| [Thursday 04 November 2010] [11:42:11] <pieterh>	not really
| [Thursday 04 November 2010] [11:42:16] <mato>	then let's just leave it
| [Thursday 04 November 2010] [11:42:18] <andrewvc_>	hangs on getsockopt(ZMQ::FD)
| [Thursday 04 November 2010] [11:42:19] <pieterh>	i'd rather get constructive feedback and solve this problem
| [Thursday 04 November 2010] [11:42:34] <andrewvc_>	I did most of my work in MRI 1.9
| [Thursday 04 November 2010] [11:42:36] <mato>	you're not listening to any feedback against your change
| [Thursday 04 November 2010] [11:42:40] <mato>	by two of the core developers
| [Thursday 04 November 2010] [11:42:43] <andrewvc_>	and rbx
| [Thursday 04 November 2010] [11:42:47] <mato>	against your proposed *untested* change
| [Thursday 04 November 2010] [11:42:51] <pieterh>	you did not try my change, mato
| [Thursday 04 November 2010] [11:43:02] <pieterh>	yes, untested, I do sincerely apologise
| [Thursday 04 November 2010] [11:43:10] <andrewvc_>	any ideas why it would hang?
| [Thursday 04 November 2010] [11:43:19] <mato>	yes, I'm sorry, I tested a different change becuase that went into the trunk
| [Thursday 04 November 2010] [11:43:27] <pieterh>	yes, not my change
| [Thursday 04 November 2010] [11:43:34] <mato>	but this whole situation just happened because you keep insisting
| [Thursday 04 November 2010] [11:43:38] <cremes>	andrewvc_: i have no idea... it could be an FFI bug, a JRuby bug, a 0mq bug or a JVM bug
| [Thursday 04 November 2010] [11:43:42] <DerGuteMoritz>	andrewvc_: what version of zmq is that with?
| [Thursday 04 November 2010] [11:43:49] <andrewvc_>	I pulled master last night
| [Thursday 04 November 2010] [11:43:54] <DerGuteMoritz>	hm okay
| [Thursday 04 November 2010] [11:44:01] <pieterh>	i will keep insisting, mato, when there are design flaws that aren't properly addressed
| [Thursday 04 November 2010] [11:44:04] <pieterh>	sorry
| [Thursday 04 November 2010] [11:44:10] <DerGuteMoritz>	then what cremes said :-)
| [Thursday 04 November 2010] [11:44:16] <andrewvc_>	lol
| [Thursday 04 November 2010] [11:44:22] <andrewvc_>	well, if it works in rbx and 1.9.2
| [Thursday 04 November 2010] [11:44:33] <DerGuteMoritz>	yeah then it's probably some java/jruby thing
| [Thursday 04 November 2010] [11:44:39] <andrewvc_>	it sounds like a jruby bug, maybe I'll bother them. I really need to get the full spec suite to run in rbx though
| [Thursday 04 November 2010] [11:44:53] <andrewvc_>	rbx and mri hang somewhere in the socket specs, and never finish
| [Thursday 04 November 2010] [11:45:09] <cremes>	andrewvc_: i'll take a look at that this weekend
| [Thursday 04 November 2010] [11:45:12] <cremes>	no time today
| [Thursday 04 November 2010] [11:45:43] <andrewvc_>	cool, i'll take a look myself right now
| [Thursday 04 November 2010] [11:46:04] <DerGuteMoritz>	good luck with that!
| [Thursday 04 November 2010] [11:46:21] <DerGuteMoritz>	I have a question
| [Thursday 04 November 2010] [11:46:28] <DerGuteMoritz>	is there an upper limit for message size?
| [Thursday 04 November 2010] [11:46:39] <DerGuteMoritz>	or why would I want to use multi-part messages?
| [Thursday 04 November 2010] [11:47:05] <DerGuteMoritz>	I mean since they are queued in memory until they are complete and then sent in one fell swoop, I might as well just send one big message, no?
| [Thursday 04 November 2010] [11:47:27] <sustrik>	zero-copy
| [Thursday 04 November 2010] [11:47:45] <DerGuteMoritz>	hmmm how so?
| [Thursday 04 November 2010] [11:47:50] <sustrik>	if you have 2 memory blocks you want to send as a single atomic unit
| [Thursday 04 November 2010] [11:47:58] <DerGuteMoritz>	ah, I see
| [Thursday 04 November 2010] [11:48:00] <sustrik>	and don't want to copy them into a single buffer
| [Thursday 04 November 2010] [11:48:11] <DerGuteMoritz>	ok that makes sense, thanks
| [Thursday 04 November 2010] [11:48:34] <DerGuteMoritz>	there is no "streaming" support of sorts right?
| [Thursday 04 November 2010] [11:49:36] <DerGuteMoritz>	oh, I just noticed zmq_streamer
| [Thursday 04 November 2010] [11:50:18] <sustrik>	it's just a device that works with PUSH/PULL sockets
| [Thursday 04 November 2010] [11:52:08] <DerGuteMoritz>	I see
| [Thursday 04 November 2010] [11:52:14] <DerGuteMoritz>	I didn't read up on devices yet
| [Thursday 04 November 2010] [11:52:16] <DerGuteMoritz>	WILL DO
| [Thursday 04 November 2010] [12:03:48] <sustrik>	pieterh: you still there?
| [Thursday 04 November 2010] [12:08:34] <pieterh>	sustrik: yes
| [Thursday 04 November 2010] [12:08:43] <sustrik>	i've checked the windows header files and at least the version i have seems to indicate that FD_SETSIZE can be defined on compilation-unit level
| [Thursday 04 November 2010] [12:08:45] <pieterh>	i was writing a long and detailed email about FD_SETSIZE
| [Thursday 04 November 2010] [12:08:48] <pieterh>	yes, of course
| [Thursday 04 November 2010] [12:08:51] <pieterh>	bleh
| [Thursday 04 November 2010] [12:09:03] <pieterh>	please just read winsock.h
| [Thursday 04 November 2010] [12:09:06] <pieterh>	that will help you a lot
| [Thursday 04 November 2010] [12:09:07] <sustrik>	i did
| [Thursday 04 November 2010] [12:09:14] <pieterh>	and it's pretty clear, right?
| [Thursday 04 November 2010] [12:09:18] <sustrik>	still, MSDN suggests otherwise (app-level scope)
| [Thursday 04 November 2010] [12:09:20] <mato>	sustrik: i read the headers too, that doesn't explain why your patch crashes though...
| [Thursday 04 November 2010] [12:09:23] <pieterh>	fd_set typedef and four FD_ macros
| [Thursday 04 November 2010] [12:09:31] <pieterh>	yes, because zmq.cpp doesn't do it right
| [Thursday 04 November 2010] [12:09:49] <sustrik>	so the question is, whether there are no strange Win platforms that actually require FD_SETSIZE set of app level
| [Thursday 04 November 2010] [12:09:50] <pieterh>	where does zmq.cpp get its FD_ macros from?
| [Thursday 04 November 2010] [12:09:56] <pieterh>	?
| [Thursday 04 November 2010] [12:10:00] <sustrik>	i've checked only on WinXP
| [Thursday 04 November 2010] [12:10:00] <pieterh>	what's that question?
| [Thursday 04 November 2010] [12:10:12] <sustrik>	does it apply to other Win versions as well?
| [Thursday 04 November 2010] [12:10:14] <pieterh>	please... this is purely a C structure issue
| [Thursday 04 November 2010] [12:10:25] <pieterh>	it is 100% orthogonal to the Windows version and OS
| [Thursday 04 November 2010] [12:10:30] <sustrik>	are there same C structures on other Win platforms?
| [Thursday 04 November 2010] [12:10:30] <pieterh>	it could apply to Linux as well
| [Thursday 04 November 2010] [12:10:58] <pieterh>	the winsock interface comes with the C compiler
| [Thursday 04 November 2010] [12:11:00] <mato>	pieterh: right, so you are sure winsock select() is implemented identically on Windows XP, 2003, Vista, and 2008?
| [Thursday 04 November 2010] [12:11:01] <pieterh>	not the OS
| [Thursday 04 November 2010] [12:11:11] <sustrik>	is that so?
| [Thursday 04 November 2010] [12:11:15] <pieterh>	mato: yes, of course, it's the POSIX select with some weird error codes
| [Thursday 04 November 2010] [12:11:29] <sustrik>	no platform specific code there?
| [Thursday 04 November 2010] [12:11:30] <pieterh>	the FD_SETSIZE is purely about fd_set and the FD_ macros
| [Thursday 04 November 2010] [12:11:34] <pieterh>	...
| [Thursday 04 November 2010] [12:11:40] <mato>	sustrik: no, the headers come from the compiler vendor, and/or microsoft
| [Thursday 04 November 2010] [12:11:50] <mato>	sustrik: that depends on which compiler and/or which SDK version you are using
| [Thursday 04 November 2010] [12:11:56] <pieterh>	take another compiler, it might not even have the FD_SETSIZE thing
| [Thursday 04 November 2010] [12:12:04] <sustrik>	it's POSIX
| [Thursday 04 November 2010] [12:12:05] <pieterh>	this is a MSVC / winsock hangover
| [Thursday 04 November 2010] [12:12:13] <sustrik>	iirc
| [Thursday 04 November 2010] [12:12:22] <pieterh>	yes, it's posix, I mean the low low default
| [Thursday 04 November 2010] [12:12:24] <pieterh>	sorry
| [Thursday 04 November 2010] [12:12:48] <mato>	pieterh: if it's a compiler hangover, why would MSDN document this as part of the Windows API...
| [Thursday 04 November 2010] [12:12:51] <pieterh>	i assume it came from the days when MSFT wanted Windows to only serve as a workstation
| [Thursday 04 November 2010] [12:12:59] <pieterh>	mato: ?
| [Thursday 04 November 2010] [12:13:15] <pieterh>	winsock is a library
| [Thursday 04 November 2010] [12:13:28] <mato>	provided as part of the OS
| [Thursday 04 November 2010] [12:13:28] <pieterh>	it is actually a standard agreed on by multiple vendors
| [Thursday 04 November 2010] [12:13:32] <mato>	used to be
| [Thursday 04 November 2010] [12:13:48] <pieterh>	the point is that the OS implements select()
| [Thursday 04 November 2010] [12:13:54] <pieterh>	not fd_set, FD_SET, FD_CLR, etc
| [Thursday 04 November 2010] [12:13:57] <pieterh>	ja?
| [Thursday 04 November 2010] [12:14:03] <mato>	but winsock.dll is provided as part of the OS; as sustrik mentioned eariler, for example Vista and above have a WSAPoll() which has no fd_setsize limit
| [Thursday 04 November 2010] [12:14:03] <sustrik>	so, MSDN kind of implies the setting may be app wide, but APR uses it in a way that suggests it's ok to assume comiletion-unit scope
| [Thursday 04 November 2010] [12:14:04] <pieterh>	FD_SETSIZE is _irrelevant_ for the OS
| [Thursday 04 November 2010] [12:14:23] <pieterh>	select() has no limit on the fd_setsize
| [Thursday 04 November 2010] [12:14:23] <mato>	then why does sustrik's patch crash?
| [Thursday 04 November 2010] [12:14:26] <pieterh>	sigh
| [Thursday 04 November 2010] [12:14:33] <sustrik>	mato: it's a bug in the patch
| [Thursday 04 November 2010] [12:14:38] <pieterh>	because zmq.cpp uses winsock2.h from zmq.h
| [Thursday 04 November 2010] [12:14:38] <mato>	sustrik: which is?
| [Thursday 04 November 2010] [12:14:44] <sustrik>	there's fd_set in select.hpp
| [Thursday 04 November 2010] [12:14:48] <sustrik>	i've missed that
| [Thursday 04 November 2010] [12:14:51] <pieterh>	you can't use FD_SET without setting this correctly
| [Thursday 04 November 2010] [12:15:04] <pieterh>	you must have a consistent typedef + macros
| [Thursday 04 November 2010] [12:15:06] <mato>	sustrik: AH, now we're getting somewhere
| [Thursday 04 November 2010] [12:15:18] <sustrik>	yes, so pieter may be actually right
| [Thursday 04 November 2010] [12:15:30] <pieterh>	it is a compile time array size issue
| [Thursday 04 November 2010] [12:15:31] <sustrik>	the only question is the strange wording in MSDN
| [Thursday 04 November 2010] [12:15:39] <pieterh>	you need a consistent typedef and macro set
| [Thursday 04 November 2010] [12:15:43] <sustrik>	but that may be just lousy work on the documentation
| [Thursday 04 November 2010] [12:15:58] <pieterh>	it becomes very hard when you have 4 copies of kind of not the same but similar code
| [Thursday 04 November 2010] [12:16:07] <pieterh>	_that_ is the only real issue
| [Thursday 04 November 2010] [12:16:44] <pieterh>	if you mix APR and 0MQ, they will both happily define their own typedefs and use them sanely
| [Thursday 04 November 2010] [12:16:48] <pieterh>	there is no insanity
| [Thursday 04 November 2010] [12:17:07] <pieterh>	only, the system API should really not be exporting winsock.h IMO
| [Thursday 04 November 2010] [12:17:08] <mato>	sustrik: ah, i see, select.hpp uses fd_set
| [Thursday 04 November 2010] [12:17:11] <pieterh>	yes
| [Thursday 04 November 2010] [12:17:12] <sustrik>	:)
| [Thursday 04 November 2010] [12:17:15] <pieterh>	yes
| [Thursday 04 November 2010] [12:17:28] <mato>	sustrik: so the problem was, some other inclusion of select.hpp was clashing with the value in select.cpp
| [Thursday 04 November 2010] [12:17:37] <sustrik>	yes
| [Thursday 04 November 2010] [12:17:40] <mato>	sustrik: except, that's problematic, because the include chain is a mess
| [Thursday 04 November 2010] [12:17:41] <pieterh>	yes
| [Thursday 04 November 2010] [12:17:48] <pieterh>	that is why my patch fixed that part of the include chain
| [Thursday 04 November 2010] [12:17:57] <mato>	sustrik: which is what i hit the last time i looked at this
| [Thursday 04 November 2010] [12:18:02] <pieterh>	just remove the rubbish from select.cpp and allow select.hpp to do the work
| [Thursday 04 November 2010] [12:18:12] <pieterh>	in any case
| [Thursday 04 November 2010] [12:18:13] <mato>	pieterh: yes, but with the further side-effect of setting FD_SETSIZE to 1024 
| [Thursday 04 November 2010] [12:18:18] <mato>	pieterh: in zmq.h
| [Thursday 04 November 2010] [12:18:31] <pieterh>	does zmq.h include select.hpp?
| [Thursday 04 November 2010] [12:18:33] <Guthur>	I didn't really follow the FD_SETSIZE  conv fully, but can you not just use the makefile approach that MS recommend
| [Thursday 04 November 2010] [12:18:33] <sustrik>	i'll do some changes to isolate select.hpp from the rest of the system
| [Thursday 04 November 2010] [12:18:47] <mato>	pieterh: no, the problem is... random bits of zmq may include select.hpp
| [Thursday 04 November 2010] [12:19:00] <sustrik>	so that the value set there doesn't incidentally infect other compilation units
| [Thursday 04 November 2010] [12:19:04] <pieterh>	yes, they do, but it's mostly poller.cpp afaics
| [Thursday 04 November 2010] [12:19:14] <pieterh>	plus there are only two places we do FD_ manipulation
| [Thursday 04 November 2010] [12:19:18] <pieterh>	and that's all we care about in fact
| [Thursday 04 November 2010] [12:19:33] <pieterh>	select.cpp and zmq.cpp
| [Thursday 04 November 2010] [12:19:36] <pieterh>	afaics that's it
| [Thursday 04 November 2010] [12:19:38] <mato>	pieterh: well, the problem is any user of select.hpp would have to ensure it's included before anything else that includes winsock.h, which includes zmq.h
| [Thursday 04 November 2010] [12:19:56] <pieterh>	i think zmq.h may not include winsock.h
| [Thursday 04 November 2010] [12:20:08] <pieterh>	because as you've pointed out before that hurts apps that use 0MQ
| [Thursday 04 November 2010] [12:20:21] <pieterh>	Guthur, I think it's about making things work sanely by default
| [Thursday 04 November 2010] [12:20:31] <mato>	pieterh: sustrik: of course, this whole problem goes away if we just accept that users define FD_SETSIZE by default.
| [Thursday 04 November 2010] [12:20:36] <pieterh>	having to define constants in the makefiles makes it all more delicate
| [Thursday 04 November 2010] [12:20:56] <mato>	pieterh: sure, but defining the constant in Makefiles/externally appears to be Win32 best practice.
| [Thursday 04 November 2010] [12:21:06] <pieterh>	uhm, it's defeatism
| [Thursday 04 November 2010] [12:21:09] <mato>	pieterh: and I don't see why we should expend effort on changing that.
| [Thursday 04 November 2010] [12:21:10] <pieterh>	on the part of Win32
| [Thursday 04 November 2010] [12:21:24] <mato>	yes, but our job is not to go fixing Win32
| [Thursday 04 November 2010] [12:21:28] <Guthur>	but if you use the makefile approach surely, when the user builds a 0MQ lib it will be sane
| [Thursday 04 November 2010] [12:21:41] <mato>	Guthur: that is true, but pieterh does not like said approach.
| [Thursday 04 November 2010] [12:21:45] <Guthur>	if they want to include it as source then they can worry about it
| [Thursday 04 November 2010] [12:21:45] <pieterh>	hang on
| [Thursday 04 November 2010] [12:21:47] <mato>	Guthur: and that's all this is about
| [Thursday 04 November 2010] [12:21:52] <pieterh>	i'm not against us changing the makefile
| [Thursday 04 November 2010] [12:22:03] <pieterh>	I'm against the FAQ entry that says "we deliver broken code but here's how to fix it"
| [Thursday 04 November 2010] [12:22:19] <mato>	pieterh: but it'll still break at 1024
| [Thursday 04 November 2010] [12:22:25] <mato>	pieterh: it's not our fault...
| [Thursday 04 November 2010] [12:22:28] <pieterh>	that is much less broken
| [Thursday 04 November 2010] [12:22:31] <sustrik>	the faq should stay there just in case
| [Thursday 04 November 2010] [12:22:37] <Guthur>	I'd have to agree with mato and sustrik on this point, though I have certainly the most limited experience
| [Thursday 04 November 2010] [12:22:53] <pieterh>	if a patch to the MSVC makefile is possible, that works fine for me
| [Thursday 04 November 2010] [12:22:54] <pieterh>	i don
| [Thursday 04 November 2010] [12:23:18] <pieterh>	i don't have any particular incentive to change the 0MQ source code (though this header file stuff is a mess IMO)
| [Thursday 04 November 2010] [12:23:39] <pieterh>	what I do care about is that people downloading and building our software get stuff that's reasonably tuned
| [Thursday 04 November 2010] [12:23:57] <mato>	pieterh: yes, a patch to the MSVC project is possible
| [Thursday 04 November 2010] [12:24:05] <Guthur>	I like that idea
| [Thursday 04 November 2010] [12:24:14] <mato>	sustrik: why don't we just do that for now and let this whole thing sleep?
| [Thursday 04 November 2010] [12:24:15] <pieterh>	it's frankly embarrassing to see bugs that I fixed in 1997 reappear today
| [Thursday 04 November 2010] [12:24:20] <pieterh>	sure, that works for me
| [Thursday 04 November 2010] [12:24:42] <pieterh>	Guthur, thanks for the suggestion
| [Thursday 04 November 2010] [12:24:45] <sustrik>	mato: i think it's a good idea to increse the default
| [Thursday 04 November 2010] [12:25:01] <mato>	sustrik: so, add /DFD_SETSIZE=1024 to the build opts in the MSVC project file
| [Thursday 04 November 2010] [12:25:04] <mato>	sustrik: problem solved
| [Thursday 04 November 2010] [12:25:14] <mato>	sustrik: and/or stick a note in the build docs/faq
| [Thursday 04 November 2010] [12:25:16] <mato>	sustrik: done.
| [Thursday 04 November 2010] [12:25:17] <pieterh>	sustrik, do you understand why changing the makefile has the same effect as defining before including winsock.h?
| [Thursday 04 November 2010] [12:25:31] <sustrik>	yes
| [Thursday 04 November 2010] [12:25:44] <mato>	pieterh: with the exception of the zmq.h issue it does have the same effect
| [Thursday 04 November 2010] [12:25:58] <pieterh>	what is the zmq.h issue, mato?
| [Thursday 04 November 2010] [12:26:07] <mato>	not again
| [Thursday 04 November 2010] [12:26:12] <sustrik>	i think there's no problem with zmq.h
| [Thursday 04 November 2010] [12:26:14] <pieterh>	sorry, I just don't understand
| [Thursday 04 November 2010] [12:26:20] <sustrik>	it doesn't use FD_SETSIZE
| [Thursday 04 November 2010] [12:26:30] <pieterh>	defining in the makefile is equivalent to setting in all 4 places in the code
| [Thursday 04 November 2010] [12:26:32] <pieterh>	including zmq.h
| [Thursday 04 November 2010] [12:26:40] <mato>	not the app makefile
| [Thursday 04 November 2010] [12:26:43] <mato>	that's the point
| [Thursday 04 November 2010] [12:26:49] <sustrik>	but when zmq.h is included from the client app
| [Thursday 04 November 2010] [12:27:00] <sustrik>	the client's value of FD_SETSIZE applies
| [Thursday 04 November 2010] [12:27:09] <pieterh>	sure, or else 64, it doesn't matter
| [Thursday 04 November 2010] [12:27:10] <sustrik>	and given that there's no FD_SET in zmq.h
| [Thursday 04 November 2010] [12:27:14] <sustrik>	it doesn't matter
| [Thursday 04 November 2010] [12:27:16] <mato>	yes
| [Thursday 04 November 2010] [12:27:17] <pieterh>	it doesn't matter
| [Thursday 04 November 2010] [12:27:22] <pieterh>	ok, agreed
| [Thursday 04 November 2010] [12:27:25] <sustrik>	fine
| [Thursday 04 November 2010] [12:27:28] <sustrik>	i'll fix it
| [Thursday 04 November 2010] [12:27:33] <pieterh>	:-) thanks
| [Thursday 04 November 2010] [12:27:36] <mato>	test please :-)
| [Thursday 04 November 2010] [12:27:45] <sustrik>	yeah
| [Thursday 04 November 2010] [12:27:55] <pieterh>	I'd suggest 2048, as per APR and other serious libraries
| [Thursday 04 November 2010] [12:28:03] <mato>	pieterh: APR uses 1024, I checked
| [Thursday 04 November 2010] [12:28:11] <mato>	pieterh: I love it how you make these statements.
| [Thursday 04 November 2010] [12:28:20] 	 * pieterh read the code about 30 minutes ago
| [Thursday 04 November 2010] [12:28:26] <pieterh>	hang on...
| [Thursday 04 November 2010] [12:28:28] <pieterh>	It does not actually matter because it's a memory allocation issue
| [Thursday 04 November 2010] [12:28:31] <sustrik>	different versions?
| [Thursday 04 November 2010] [12:28:36] <pieterh>	the actual socket limit is an OS issue
| [Thursday 04 November 2010] [12:28:41] 	 * mato read the latest SVN
| [Thursday 04 November 2010] [12:28:45] <pieterh>	this is purely a memory vs. godamnitbroke issue
| [Thursday 04 November 2010] [12:28:49] <sustrik>	it matters performance wise
| [Thursday 04 November 2010] [12:28:51] <mato>	anyway, anything above 1024 sucks for performance
| [Thursday 04 November 2010] [12:28:53] <pieterh>	nope
| [Thursday 04 November 2010] [12:28:57] <pieterh>	does it?
| [Thursday 04 November 2010] [12:29:01] <sustrik>	yes
| [Thursday 04 November 2010] [12:29:02] <sustrik>	so we should choose some sane value
| [Thursday 04 November 2010] [12:29:08] <sustrik>	big enough to work well
| [Thursday 04 November 2010] [12:29:12] <mato>	if you actually use more than 1024 sockets in a select loop, that sucks
| [Thursday 04 November 2010] [12:29:16] <sustrik>	but small enough not to require lot of copying
| [Thursday 04 November 2010] [12:29:27] <mato>	64? :-)
| [Thursday 04 November 2010] [12:29:37] <sustrik>	that's historical limit
| [Thursday 04 November 2010] [12:29:47] <sustrik>	the internet grew bigger in the meantime :)
| [Thursday 04 November 2010] [12:29:51] <pieterh>	do the macros actually loop over the whole FD_SETSIZE value?
| [Thursday 04 November 2010] [12:30:04] <sustrik>	nope
| [Thursday 04 November 2010] [12:30:11] <sustrik>	but the whole array is copied around
| [Thursday 04 November 2010] [12:30:18] <pieterh>	sustrik: MSFT expressly limited the capacity of 'workstations'
| [Thursday 04 November 2010] [12:30:29] <pieterh>	where is it copied around?
| [Thursday 04 November 2010] [12:30:29] <sustrik>	to 64?
| [Thursday 04 November 2010] [12:30:35] <pieterh>	yes, but even lower
| [Thursday 04 November 2010] [12:30:41] <pieterh>	16 sockets iirc
| [Thursday 04 November 2010] [12:30:46] <sustrik>	the request for events fdset is overwritten by results
| [Thursday 04 November 2010] [12:30:53] <pieterh>	right
| [Thursday 04 November 2010] [12:31:02] <sustrik>	so you have to copy the values into the aray each time
| [Thursday 04 November 2010] [12:31:16] <pieterh>	but it only copies the actual values
| [Thursday 04 November 2010] [12:31:26] <mato>	sustrik: i guess with all this arguing you've not reviewed my signaler patch yet?
| [Thursday 04 November 2010] [12:31:29] 	 * pieterh must be wrong
| [Thursday 04 November 2010] [12:31:36] <sustrik>	1024 is ok imo
| [Thursday 04 November 2010] [12:31:36] <pieterh>	mato: ack
| [Thursday 04 November 2010] [12:31:43] <sustrik>	mato: sorry :(
| [Thursday 04 November 2010] [12:31:52] <sustrik>	i have if half-reviewed
| [Thursday 04 November 2010] [12:32:02] <pieterh>	mato: you need two independent reviewers and regression test of minimum of 64 or 1024 applications
| [Thursday 04 November 2010] [12:32:19] <sustrik>	actually, he has :)
| [Thursday 04 November 2010] [12:34:18] <mato>	yeah, sure, 1024 applications? no problem :-)
| [Thursday 04 November 2010] [12:34:22] <mato>	that's what it's for :-)
| [Thursday 04 November 2010] [12:36:05] <mato>	sustrik: well, let me know soonish if you're going to accept it or not, i have dependencies on my end.
| [Thursday 04 November 2010] [12:36:17] <sustrik>	wait a sec
| [Thursday 04 November 2010] [12:37:58] <sustrik>	mato: is it wise to grow the buffer exponentially?
| [Thursday 04 November 2010] [12:39:44] <sustrik>	also, given that we have resizable buffers right, now would it be good to start with some smaller buffer size?
| [Thursday 04 November 2010] [12:40:16] <mato>	sustrik: well, for 1), the OS seems to grow the actual buffer in pretty big chunks
| [Thursday 04 November 2010] [12:40:31] <mato>	sustrik: for 2) i'm not sure about the latency of the grow operation
| [Thursday 04 November 2010] [12:40:43] <mato>	sustrik: so IMO it'd be better to stick with the OS default
| [Thursday 04 November 2010] [12:40:51] <mato>	sustrik: and grow the buffer if needed.
| [Thursday 04 November 2010] [12:41:31] <sustrik>	what about the increment being equal to OS default buffer size?
| [Thursday 04 November 2010] [12:41:55] <mato>	can do if you'd prefer that, i have no opinion
| [Thursday 04 November 2010] [12:42:12] <mato>	it does mean an extra getsockopt call in the constructor to get the default size, etc.
| [Thursday 04 November 2010] [12:42:31] <sustrik>	sure but you can do that once only
| [Thursday 04 November 2010] [12:42:40] <sustrik>	if (default == -1) {
| [Thursday 04 November 2010] [12:42:49] <sustrik>	default = getsockopt (...);
| [Thursday 04 November 2010] [12:42:50] <sustrik>	}
| [Thursday 04 November 2010] [12:43:45] <sustrik>	anyway, it's not urgent
| [Thursday 04 November 2010] [12:43:52] <sustrik>	i can commit this code
| [Thursday 04 November 2010] [12:44:01] <sustrik>	and we can optimise it later on
| [Thursday 04 November 2010] [12:46:50] <mato>	sustrik: ok, great
| [Thursday 04 November 2010] [12:46:59] <sustrik>	fine
| [Thursday 04 November 2010] [12:47:04] <mato>	sustrik: i also refactored all the platform-dependent stuff, you happy with that?
| [Thursday 04 November 2010] [12:47:12] <sustrik>	yes, looks ok
| [Thursday 04 November 2010] [12:47:16] <sustrik>	i haven't tested it
| [Thursday 04 November 2010] [12:47:22] <mato>	sustrik: i have
| [Thursday 04 November 2010] [12:47:23] <sustrik>	but i trust you
| [Thursday 04 November 2010] [12:48:37] <mato>	sustrik: i wrote in the commit log; have tested both the MSG_DONTWAIT and POSIX codepath, and the Win32 version
| [Thursday 04 November 2010] [12:48:50] <mato>	sustrik: I've not actually tested on HP-UX or AIX obviously, but the code works
| [Thursday 04 November 2010] [12:49:03] <sustrik>	ok
| [Thursday 04 November 2010] [12:49:05] <mato>	sustrik: and the OpenVMS version might not work at all
| [Thursday 04 November 2010] [12:49:12] <sustrik>	yep, i seen that
| [Thursday 04 November 2010] [12:49:23] <sustrik>	little we can do about that
| [Thursday 04 November 2010] [12:55:28] <CIA-20>	zeromq2: 03Martin Lucina 07master * r1b39bcd 10/ (src/config.hpp src/signaler.cpp src/signaler.hpp): (log message trimmed)
| [Thursday 04 November 2010] [12:55:28] <CIA-20>	zeromq2: Automatically resize signalling socket buffer if full
| [Thursday 04 November 2010] [12:55:28] <CIA-20>	zeromq2: If the socketpair used by signaler_t fills up, this can lead to deadlock.
| [Thursday 04 November 2010] [12:55:28] <CIA-20>	zeromq2: This patch provides partial resolution by attempting to resize SO_SNDBUF on
| [Thursday 04 November 2010] [12:55:28] <CIA-20>	zeromq2: the writer side, and if that fails we shall at least assert rather than
| [Thursday 04 November 2010] [12:55:28] <CIA-20>	zeromq2: hang.
| [Thursday 04 November 2010] [12:55:29] <CIA-20>	zeromq2: I've also refactored the signaler_t code to make the platform-dependent
| [Thursday 04 November 2010] [13:01:32] <mato>	sustrik: thanks for that!
| [Thursday 04 November 2010] [13:01:49] <sustrik>	you are welcome
| [Thursday 04 November 2010] [13:11:23] <mikko>	master sun studio build failed
| [Thursday 04 November 2010] [13:15:21] <mato>	mikko: interesting
| [Thursday 04 November 2010] [13:15:27] <mato>	mikko: i've also seen this randomly
| [Thursday 04 November 2010] [13:15:37] <mato>	mikko: my change to the signaler isn't really relevant here
| [Thursday 04 November 2010] [13:16:28] <mato>	mikko: can you kick the build just to see if it fails every time
| [Thursday 04 November 2010] [13:16:30] <mato>	mikko: ?
| [Thursday 04 November 2010] [13:17:05] <mikko>	mato: sure
| [Thursday 04 November 2010] [13:17:18] <mikko>	building
| [Thursday 04 November 2010] [13:17:28] <mato>	maybe i changed something subtly in timing
| [Thursday 04 November 2010] [13:17:34] <mato>	it's possible 
| [Thursday 04 November 2010] [13:18:39] <pieterh>	cyal folks
| [Thursday 04 November 2010] [13:19:05] <mikko>	see you
| [Thursday 04 November 2010] [13:19:31] <mato>	cya
| [Thursday 04 November 2010] [13:21:06] <mikko>	passes now
| [Thursday 04 November 2010] [13:21:11] <mikko>	seems intermittent
| [Thursday 04 November 2010] [13:21:31] <mato>	yes, will need to be looked into
| [Thursday 04 November 2010] [13:21:39] <mato>	i'd suspect some termination issue
| [Thursday 04 November 2010] [15:45:07] <sustrik>	mikko, mato: i think it's related to the problem reported by Christian Gudrian on the ML
| [Thursday 04 November 2010] [15:45:20] <sustrik>	pyzmq seems to fail as well...
| [Thursday 04 November 2010] [16:21:57] <CIA-20>	zeromq2: 03Jacob Rideout 07master * r0ada4f8 10/ (doc/zmq_getsockopt.txt doc/zmq_setsockopt.txt): 
| [Thursday 04 November 2010] [16:21:58] <CIA-20>	zeromq2: Fix documentation typos
| [Thursday 04 November 2010] [16:21:58] <CIA-20>	zeromq2: Signed-off-by: Jacob Rideout <jacob.rideout@returnpath.net> - http://bit.ly/a1CmmQ
| [Thursday 04 November 2010] [16:23:37] <CIA-20>	zeromq2: 03Martin Sustrik 07master * r623a9c9 10/ AUTHORS : 
| [Thursday 04 November 2010] [16:23:37] <CIA-20>	zeromq2: Jacob Rideout added to the AUTGORS file.
| [Thursday 04 November 2010] [16:23:37] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/bt6MSf
| [Thursday 04 November 2010] [18:49:42] <Guthur>	Why is there a standard socket in the pollitem?
| [Thursday 04 November 2010] [18:50:48] <cremes>	Guthur: because you can use it to poll a standard socket as well as a 0mq socket
| [Thursday 04 November 2010] [18:51:18] <Guthur>	What is the rational for providing that?
| [Thursday 04 November 2010] [18:51:34] <Guthur>	I thought ZMQ aimed to abstract away from raw sockets?
| [Thursday 04 November 2010] [18:52:48] <Guthur>	The complexity is compounded a little by the fact it's platform dependant as well
| [Thursday 04 November 2010] [18:53:14] <cremes>	Guthur: the rationale is so that you can mix standard and 0mq sockets via the same api
| [Thursday 04 November 2010] [18:53:23] <cremes>	if you need to understand it better than that, ask sustrik 
| [Thursday 04 November 2010] [18:53:33] <Guthur>	I'm working on a binding and I am feeling now that I have to worry about the platform
| [Thursday 04 November 2010] [18:54:01] <Guthur>	Everything else has been pretty easy up until this one
| [Thursday 04 November 2010] [21:06:27] <teruokun>	Hello
| [Thursday 04 November 2010] [21:08:10] <teruokun>	I'm very new to using 0MQ and was trying to see if it would work for a project I'm working on
| [Thursday 04 November 2010] [21:09:26] <teruokun>	I have a master than needs to keep track of a bunch of slaves
| [Thursday 04 November 2010] [21:10:30] <teruokun>	multiple slaves will exist per server and they are meant to be more-or-less autonomous
| [Thursday 04 November 2010] [21:11:15] <teruokun>	what they depend on the master for are orders (NEW data, kill yourself, etc.)
| [Thursday 04 November 2010] [21:11:56] <teruokun>	but they have to be able to respond back to the master
| [Thursday 04 November 2010] [21:14:22] <teruokun>	I'm attempting having an incoming 'upstream' channel for the master to receive communications on and a pubsub relationship for the master to send out orders
| [Thursday 04 November 2010] [21:15:16] <teruokun>	However, I'm ending up with some 'address in use' issues for the server itself
| [Thursday 04 November 2010] [21:16:10] <teruokun>	for instance, if the master has to be shut down temporarily and brought back up, occasionally (but not predictably), it will not be able to bind it's addresses
| [Thursday 04 November 2010] [21:16:40] <teruokun>	anyone have any ideas what I'm doing wrong?
| [Thursday 04 November 2010] [22:36:36] <Guthur>	sustrik, ping
| [Thursday 04 November 2010] [22:44:47] <Guthur>	oh nvm, I got it sorted
| [Friday 05 November 2010] [00:36:26] <andrewvc_>	cremes: I found the cause of the MRI and RBX hangs running the spec suite, repeatedly creating contexts was the issue
| [Friday 05 November 2010] [05:12:17] <mikko>	pyzmq builds seem to be failing against master and maint branches of 0MQ
| [Friday 05 November 2010] [05:22:51] <sustrik>	mikko: yes, i've seen that
| [Friday 05 November 2010] [05:23:05] <sustrik>	morning
| [Friday 05 November 2010] [05:23:09] <mikko>	morning
| [Friday 05 November 2010] [05:23:43] <sustrik>	btw, i'm in london on 9th and 10th
| [Friday 05 November 2010] [05:23:52] <mikko>	this month?
| [Friday 05 November 2010] [05:23:55] <sustrik>	yes
| [Friday 05 November 2010] [05:23:59] <sustrik>	next week
| [Friday 05 November 2010] [05:24:11] <mikko>	my calendar looks pretty empty this far
| [Friday 05 November 2010] [05:24:39] <sustrik>	if you want to have a beer in the evening
| [Friday 05 November 2010] [05:24:39] <mikko>	maybe we could finally be in the same place at the same time
| [Friday 05 November 2010] [05:24:45] <sustrik>	right
| [Friday 05 November 2010] [05:24:49] <mikko>	all i've done this far is recommended meeting places 
| [Friday 05 November 2010] [05:24:54] <sustrik>	:)
| [Friday 05 November 2010] [05:25:16] <mikko>	are you working for a customer?
| [Friday 05 November 2010] [05:25:20] <sustrik>	yes
| [Friday 05 November 2010] [05:25:27] <mikko>	do you know whereabouts in london?
| [Friday 05 November 2010] [05:25:35] <sustrik>	southwark
| [Friday 05 November 2010] [05:25:51] <sustrik>	i'll be online till so we can arrange it then
| [Friday 05 November 2010] [05:25:58] <mikko>	sure
| [Friday 05 November 2010] [05:26:04] <mikko>	i'm close to tottenham court road
| [Friday 05 November 2010] [05:26:11] <mikko>	so going down to waterloo is pretty easy
| [Friday 05 November 2010] [05:26:45] <Guthur>	Is there an active maintainer for pyzmq?
| [Friday 05 November 2010] [05:27:02] <sustrik>	or the other way round, we can have a diner in soho
| [Friday 05 November 2010] [05:27:13] <sustrik>	Guthur: yes
| [Friday 05 November 2010] [05:27:29] <sustrik>	it's Brian Granger and MinRK
| [Friday 05 November 2010] [05:27:46] <mikko>	sustrik: there is a nice pub pretty close there http://www.doggettscoatandbadge.co.uk/
| [Friday 05 November 2010] [05:27:58] <mikko>	it's north from southwark, riverside
| [Friday 05 November 2010] [05:28:02] <mikko>	but let's see closer
| [Friday 05 November 2010] [05:28:14] <mikko>	especially if there are others coming as well
| [Friday 05 November 2010] [05:28:31] <sustrik>	dunno, i haven't arranged anything yet
| [Friday 05 November 2010] [05:29:17] <mikko>	Jon Dyte is in london iirc
| [Friday 05 November 2010] [05:29:19] <mikko>	and a few others
| [Friday 05 November 2010] [05:29:28] <sustrik>	yep
| [Friday 05 November 2010] [05:30:21] <Guthur>	sustrik: How important do you feel the raw socket support in PollItem is? I implemented polling in the clrzmq last night, but not sure how to support raw sockets.
| [Friday 05 November 2010] [05:30:38] <sustrik>	well, support what you can
| [Friday 05 November 2010] [05:30:47] <sustrik>	other features can be added later on
| [Friday 05 November 2010] [05:31:07] <sustrik>	the raw sockets support is useful when integrating 0mq sockets into events loop
| [Friday 05 November 2010] [05:31:26] <sustrik>	so say you have an application that uses raw sockets
| [Friday 05 November 2010] [05:31:36] <sustrik>	and want to use 0mq for particular job
| [Friday 05 November 2010] [05:31:36] <Guthur>	I could probably get it working on windows platform, but cross platform would be a bit of a pain
| [Friday 05 November 2010] [05:31:57] <sustrik>	just ignore it then
| [Friday 05 November 2010] [05:32:11] <sustrik>	you don't have to support everything
| [Friday 05 November 2010] [05:32:42] <Guthur>	I was pretty please to get polling going last night anyway
| [Friday 05 November 2010] [05:33:03] <Guthur>	It even uses C# event handler delegates, hehe
| [Friday 05 November 2010] [05:35:02] <sustrik>	so you are basically ready?
| [Friday 05 November 2010] [05:35:11] <sustrik>	announce it then and let's see
| [Friday 05 November 2010] [05:35:25] <sustrik>	whether C#-friendly API attracts more .net devs
| [Friday 05 November 2010] [05:36:45] <Guthur>	I'd like to take the weekend to finish off the guide examples
| [Friday 05 November 2010] [05:37:36] <sustrik>	ack
| [Friday 05 November 2010] [05:38:05] <Guthur>	I'm about half through them now., just completed the second divide and conquer with the kill signal.
| [Friday 05 November 2010] [05:38:42] <Guthur>	well a bit less than half way, but close
| [Friday 05 November 2010] [06:37:43] <mikko>	symbol lookup error: /usr/local/lib/libzmq.so.0: undefined symbol: _ZN3zmq15zmq_connecter_tC1EPNS_11io_thread_tEPNS_9session_tERKNS_9options_tEPKcS9_
| [Friday 05 November 2010] [06:37:49] <mikko>	this is slightly strange error
| [Friday 05 November 2010] [06:38:46] <mikko>	ZERMQ2
| [Friday 05 November 2010] [06:38:51] <mikko>	typo in my autoconf
| [Friday 05 November 2010] [11:40:31] <CIA-20>	zeromq2: 03Martin Sustrik 07master * r9cfdb44 10/ (28 files): 
| [Friday 05 November 2010] [11:40:31] <CIA-20>	zeromq2: slots renamed to tids
| [Friday 05 November 2010] [11:40:31] <CIA-20>	zeromq2: Threads were so far identified by integers called 'slots'.
| [Friday 05 November 2010] [11:40:31] <CIA-20>	zeromq2: This patch renames them to more comprehensible 'tid's (thread IDs).
| [Friday 05 November 2010] [11:40:31] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/d3zXQD
| [Friday 05 November 2010] [12:04:34] <mato>	sustrik: yo
| [Friday 05 November 2010] [12:15:14] <cremes>	sustrik: why not just write 'thread_id' instead of 'tid'? are saving those few characters that important when it reduces comprehension?
| [Friday 05 November 2010] [12:15:58] <mato>	cremes: i'm guessing sustrik likes his compressed variable names :-) but fair point...
| [Friday 05 November 2010] [12:17:00] <cremes>	mato: it took me years to break that habit but i'm glad i did; i no longer fear long variable names!
| [Friday 05 November 2010] [12:17:13] <cremes>	and coming back to review old code is *so* much easier then
| [Friday 05 November 2010] [12:17:47] <mato>	cremes: i agree
| [Friday 05 November 2010] [12:17:54] <mato>	cremes: submit a patch :-)
| [Friday 05 November 2010] [12:17:59] <cremes>	:)
| [Friday 05 November 2010] [12:18:04] <mato>	seriously
| [Friday 05 November 2010] [12:18:14] <mato>	[PATCH] Uncompress variable names
| [Friday 05 November 2010] [12:18:15] <mato>	:-)
| [Friday 05 November 2010] [12:18:34] <kyuss>	Hello. I'm trying to run basic REQ/REP example in C from the guide. It works fine on Debian, but zmq_connect hangs on Fedora 8. How can I debug it?
| [Friday 05 November 2010] [12:18:35] <cremes>	perhaps i will... search and replace are pretty quick these days
| [Friday 05 November 2010] [12:18:43] <mato>	You can do it trivially by taking sustrik's commit and running sed over it :-)
| [Friday 05 November 2010] [12:18:49] <cremes>	ha
| [Friday 05 November 2010] [12:19:16] <cremes>	kyuss: let me take a quick look here...
| [Friday 05 November 2010] [12:19:58] <cremes>	kyuss: do you have a link to the specific code you used from the guide? there are lots of examples...
| [Friday 05 November 2010] [12:20:11] <kyuss>	one sec
| [Friday 05 November 2010] [12:20:44] <kyuss>	cremes: server http://pastebin.com/5Hy8dzWU
| [Friday 05 November 2010] [12:21:04] <cremes>	ok
| [Friday 05 November 2010] [12:21:11] <kyuss>	cremes: client http://pastebin.com/C8AERFSk
| [Friday 05 November 2010] [12:21:25] <cremes>	step 1, replace the asterisk in the call to zmq_bind with 127.0.0.1
| [Friday 05 November 2010] [12:21:42] <cremes>	it's more portable (i.e. that syntax doesn't work on windows from my experience)
| [Friday 05 November 2010] [12:22:48] <cremes>	try it again with that small change
| [Friday 05 November 2010] [12:23:10] <cremes>	also, be sure that you are starting the server before starting the client
| [Friday 05 November 2010] [12:23:37] <mato>	cremes: "*" doesn't work on windows? It just binds to INADDR_ANY
| [Friday 05 November 2010] [12:23:44] <mato>	cremes: if it really doesn't work, that's a bug...
| [Friday 05 November 2010] [12:24:00] <kyuss>	cremes: I have changed asterisk to 127.0.0.1. I have run server, then client in gdb and it hangs on zmq_connect again.
| [Friday 05 November 2010] [12:24:03] <cremes>	mato: perhaps it is fixed in later releases but it definitely didn't work in 2.0.8
| [Friday 05 November 2010] [12:24:19] <kyuss>	cremes: I tried with 2.0.10 and 2.0.8
| [Friday 05 November 2010] [12:24:33] <cremes>	kyuss: check to see if any other processes are using port 5555 via netstat
| [Friday 05 November 2010] [12:26:28] <cremes>	kyuss: also, in the client code change localhost to 127.0.0.1
| [Friday 05 November 2010] [12:27:51] <kyuss>	cremes: I did that, no change. And there is nothing on 5555 execept server (when I run it)
| [Friday 05 November 2010] [12:28:11] <cremes>	well, that doesn't make any sense to me then
| [Friday 05 November 2010] [12:28:27] <mato>	cremes: '*' definitely works with 2.1 master, ergo also 2.0.10 since that did not change
| [Friday 05 November 2010] [12:28:33] <mato>	cremes: just tried it on win2k3
| [Friday 05 November 2010] [12:28:34] <cremes>	mato: good to know
| [Friday 05 November 2010] [12:28:46] <cremes>	i'll need it for win7 sometime soon...
| [Friday 05 November 2010] [12:28:57] <cremes>	we need to get 0mq building under mingw cleanly
| [Friday 05 November 2010] [12:29:02] <mato>	cremes: there's no reason why it shouldn't, it doesn't do anything special (just uses INADDR_ANY for the unerlying bind call)
| [Friday 05 November 2010] [12:29:27] <mato>	cremes: patches welcome :-) 2.0.x used to cross-compile OK from Linux to Windows using MinGW
| [Friday 05 November 2010] [12:29:32] <cremes>	kyuss: exact same code runs ok on debian but fails on fedora?
| [Friday 05 November 2010] [12:29:35] <mato>	cremes: no idea about an actual build *on* Windows
| [Friday 05 November 2010] [12:29:48] <kyuss>	cremes: yes sir
| [Friday 05 November 2010] [12:30:02] <cremes>	mato: roger that
| [Friday 05 November 2010] [12:30:22] <cremes>	kyuss: do any of the examples work on fedora?
| [Friday 05 November 2010] [12:30:42] <cremes>	try running some of the code provided in the 'perf' subdir
| [Friday 05 November 2010] [12:30:45] <mato>	cremes: I'd get him to try local_thr and remote_thr
| [Friday 05 November 2010] [12:30:48] <mato>	precisely :-)
| [Friday 05 November 2010] [12:30:49] <cremes>	like local_lat & remote_lat
| [Friday 05 November 2010] [12:31:38] <kyuss>	cremes: No. I try basic one because my previous code with queue device was not working as well (but works fine on debian).
| [Friday 05 November 2010] [12:32:42] <cremes>	kyuss: so none of the 0mq code examples work on fedora, right?
| [Friday 05 November 2010] [12:32:51] <kyuss>	cremes: I have installed uuid-dev from source  (e2fsprogs), then 2.0.10 from source
| [Friday 05 November 2010] [12:33:01] <kyuss>	cremes: That's right
| [Friday 05 November 2010] [12:33:35] <cremes>	kyuss: i dont' know what to do to help; 0mq works fine on my osx and archlinux boxes and clearly it works ok on your debian box
| [Friday 05 November 2010] [12:33:41] <cremes>	i don't know why fedora is failing
| [Friday 05 November 2010] [12:34:13] <cremes>	i think you're going to have to dig a bit deeper; see where the hang happens via gdb or use strace
| [Friday 05 November 2010] [12:34:32] <kyuss>	cremes: Ok. Thanks. Maybe I will try on more recent version of Fedora
| [Friday 05 November 2010] [12:42:42] <CIA-20>	zeromq2: 03Martin Sustrik 07master * r9da84a5 10/ (14 files in 3 dirs): 
| [Friday 05 November 2010] [12:42:42] <CIA-20>	zeromq2: signaler renamed to mailbox
| [Friday 05 November 2010] [12:42:42] <CIA-20>	zeromq2: For historical reasons queue to transfer commands between
| [Friday 05 November 2010] [12:42:42] <CIA-20>	zeromq2: threads was called 'signaler'. Given that it was used to
| [Friday 05 November 2010] [12:42:42] <CIA-20>	zeromq2: pass commands rather than signals it was renamed to 'mailbox',
| [Friday 05 November 2010] [12:42:42] <CIA-20>	zeromq2: see Erlang mailboxes.
| [Friday 05 November 2010] [12:42:43] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/alBcFR
| [Friday 05 November 2010] [12:45:29] <sustrik>	cremes: it's modeled after POSIX pid (process id)
| [Friday 05 November 2010] [12:45:55] <mato>	sustrik: is there some reason why you added whitespace (blank lines) before comments in *some* functions of the (now) mailbox, but not others?
| [Friday 05 November 2010] [12:46:13] <sustrik>	i've missed some?
| [Friday 05 November 2010] [12:46:15] <sustrik>	ugh
| [Friday 05 November 2010] [12:46:27] <mato>	sustrik: is this part of coding style?
| [Friday 05 November 2010] [12:46:30] <sustrik>	yes
| [Friday 05 November 2010] [12:46:33] <mato>	sustrik: blank line before any comment?
| [Friday 05 November 2010] [12:46:48] <sustrik>	the structure is: block of code preceded by a comment
| [Friday 05 November 2010] [12:46:52] <mato>	sustrik: you ignored the win32 implementation at least
| [Friday 05 November 2010] [12:46:56] <sustrik>	separated by blank line
| [Friday 05 November 2010] [12:47:14] <sustrik>	sorry?
| [Friday 05 November 2010] [12:47:22] <mato>	sustrik: the problem is, you end up with stuff like this:
| [Friday 05 November 2010] [12:47:28] <mato>	   if (block_) {
| [Friday 05 November 2010] [12:47:28] <mato>	        // Set the reader to blocking mode.
| [Friday 05 November 2010] [12:47:28] <mato>	        int flags = fcntl (r, F_GETFL, 0);
| [Friday 05 November 2010] [12:47:29] <mato>	        errno_assert (flags >= 0);
| [Friday 05 November 2010] [12:47:29] <mato>	        int rc = fcntl (r, F_SETFL, flags & ~O_NONBLOCK);
| [Friday 05 November 2010] [12:47:31] <mato>	        errno_assert (rc == 0);
| [Friday 05 November 2010] [12:47:33] <mato>	    }um
| [Friday 05 November 2010] [12:47:36] <mato>	um
| [Friday 05 November 2010] [12:47:41] <mato>	with a blank line after the if(block_) {
| [Friday 05 November 2010] [12:47:56] <sustrik>	yeah, the commet should be before the if
| [Friday 05 November 2010] [12:48:02] <mato>	well, then do it properly :-)
| [Friday 05 November 2010] [12:48:27] <sustrik>	i should
| [Friday 05 November 2010] [12:48:29] <sustrik>	:|
| [Friday 05 November 2010] [12:48:35] <mato>	i mean do it properly or not at all
| [Friday 05 November 2010] [12:48:55] <mato>	and/or you should have complained when I posted my patch
| [Friday 05 November 2010] [12:49:02] <mato>	anyway, no big deal
| [Friday 05 November 2010] [12:49:08] <sustrik>	yes, i'll fix it
| [Friday 05 November 2010] [12:49:32] <mato>	it's just those orphaned if statments make no sense
| [Friday 05 November 2010] [12:49:42] <sustrik>	yes
| [Friday 05 November 2010] [12:49:43] <sustrik>	i find comment+block coding style more comprehensible
| [Friday 05 November 2010] [12:49:49] <sustrik>	but it should be done properly
| [Friday 05 November 2010] [12:50:03] <mato>	as i said, in future complain to the submitter
| [Friday 05 November 2010] [12:50:11] <sustrik>	ok
| [Friday 05 November 2010] [12:51:02] <mato>	oh, incidentally I added stuff like // !something in #else blocks
| [Friday 05 November 2010] [12:51:12] <mato>	i think it would be nice to arrive at a convention for that
| [Friday 05 November 2010] [12:51:27] <sustrik>	sure, feel free to propose one
| [Friday 05 November 2010] [12:51:35] <mato>	since with stuff like the signa^H^H^H^H^Hmailbox code, it's good to be able to see what the #else means
| [Friday 05 November 2010] [12:51:39] <mato>	right?
| [Friday 05 November 2010] [12:51:56] <sustrik>	howeve i would like to avoid something like this:
| [Friday 05 November 2010] [12:51:56] <mato>	especially if the #if is somewhere 5 pages up
| [Friday 05 November 2010] [12:51:58] <sustrik>	if (X)
| [Friday 05 November 2010] [12:52:01] <sustrik>	    y = 1;
| [Friday 05 November 2010] [12:52:04] <sustrik>	else // !X
| [Friday 05 November 2010] [12:52:08] <sustrik>	   y = 2;
| [Friday 05 November 2010] [12:52:16] <mato>	i would only do it if the block is big
| [Friday 05 November 2010] [12:52:20] <mato>	for some definition of big
| [Friday 05 November 2010] [12:52:21] <sustrik>	yes
| [Friday 05 November 2010] [12:52:45] <sustrik>	on the other hand it creates some management burden
| [Friday 05 November 2010] [12:52:56] <sustrik>	if the if part is changed and else part ignored
| [Friday 05 November 2010] [12:53:05] <sustrik>	you'll end up with inconsitent comments
| [Friday 05 November 2010] [12:53:06] <mato>	review, refuse to accept
| [Friday 05 November 2010] [12:53:22] <mato>	if it becomes part of the coding style, enforce it
| [Friday 05 November 2010] [12:53:46] <sustrik>	then the burden is on me, as maintainer :)
| [Friday 05 November 2010] [12:53:49] <mato>	it does make code with platform-dependent ifdefs *much* easier to follow
| [Friday 05 November 2010] [12:54:05] <mato>	sustrik: as the maintiner, you should be reading each patch anyway :-)
| [Friday 05 November 2010] [12:54:10] <sustrik>	actually, yes, #ifdefs are mess
| [Friday 05 November 2010] [12:54:11] <mato>	sustrik: so there is no "extra" burden
| [Friday 05 November 2010] [12:54:29] <sustrik>	mato: the point is that the offending comment is not part of the patch
| [Friday 05 November 2010] [12:54:41] <sustrik>	so i would have to check the original code aside of the patch
| [Friday 05 November 2010] [12:55:04] <mato>	sustrik: dunno.
| [Friday 05 November 2010] [12:55:21] <sustrik>	what i say is: easy to get wrong
| [Friday 05 November 2010] [12:55:27] <sustrik>	if wrong, it has no value
| [Friday 05 November 2010] [12:55:55] <mato>	true
| [Friday 05 November 2010] [13:03:56] <sustrik>	thinking about the coding style wrt comments
| [Friday 05 November 2010] [13:04:33] <sustrik>	i believe it forces developer to separate body of function in small "sub-functions"
| [Friday 05 November 2010] [13:04:42] <sustrik>	with clear semantics
| [Friday 05 November 2010] [13:04:59] <sustrik>	if i can't think of a comment to place on top of the block of code
| [Friday 05 November 2010] [13:05:12] <sustrik>	it's probably mixing several issues
| [Friday 05 November 2010] [13:05:23] <sustrik>	and shoud be cleaned up anyway
| [Friday 05 November 2010] [13:05:42] 	 * sustrik should mention that in coding style doc...
| [Friday 05 November 2010] [13:06:09] <mato>	sustrik: sure, the comments inside the block body in my case should go above the if, i guess
| [Friday 05 November 2010] [13:06:26] <mato>	 //  If ...., we do special foo.
| [Friday 05 November 2010] [13:06:34] <sustrik>	right
| [Friday 05 November 2010] [13:06:34] <mato>	etc
| [Friday 05 November 2010] [13:08:13] <sustrik>	actually, it is documented:
| [Friday 05 November 2010] [13:08:14] <sustrik>	# Code should be broken to small pieces (couple of lines each), every piece doing one simple task.
| [Friday 05 November 2010] [13:08:14] <sustrik>	# Each piece should be preceded by a comment explaining what is its intent.
| [Friday 05 November 2010] [13:08:14] <sustrik>	# Each code piece should be followed by a blank line.
| [Friday 05 November 2010] [13:08:20] <sustrik>	good
| [Friday 05 November 2010] [13:28:54] <shales>	I'm confused about message envelopes and routing with XREP socket. Is the following true? If both XREQ and REP sockets connect to an XREP socket, then the XREP socket has to the type of the socket on the other end so that that it knows when the delimeter after the address in a multipart message is necessary
| [Friday 05 November 2010] [13:29:28] <shales>	meant to say "then the XREP socket has to _know_ the type"
| [Friday 05 November 2010] [14:06:09] <cremes>	shales: make sure your multi-part messages all follow the same rules if you are going to mix XREQ and REQ sockets on the same XREP endpoint
| [Friday 05 November 2010] [14:06:32] <cremes>	then the XREP doesn't *need* to know anything; all sockets are managing the message parts the same way
| [Friday 05 November 2010] [14:06:46] <cremes>	i.e. *always* use the null part as a delimiter
| [Friday 05 November 2010] [14:08:51] <cremes>	shales: read this... i wrote it a while ago when i was having the same issues:  http://www.zeromq.org/tutorials:xreq-and-xrep
| [Friday 05 November 2010] [16:09:59] <Guthur>	when does the RECVMORE get set, before calling Recv or afte
| [Friday 05 November 2010] [16:10:14] <Guthur>	after*
| [Friday 05 November 2010] [16:10:59] <Guthur>	Does one have to call the Recv to find out there is a multipart message
| [Friday 05 November 2010] [16:14:16] <shales>	cremes: thanks! that makes sense. I see what I was doing wrong now
| [Friday 05 November 2010] [16:24:02] <twomashi>	helloo
| [Friday 05 November 2010] [16:24:05] <twomashi>	I have a question
| [Friday 05 November 2010] [16:24:57] <twomashi>	My understanding is that creating a zeromq context creates a thread in your application which allows socket operations to run asynchronously
| [Friday 05 November 2010] [16:25:49] <cremes>	twomashi: correct so far...
| [Friday 05 November 2010] [16:25:54] <twomashi>	Assuming thats right, if I fork my application, does that thread keep running in 2 separate processes?
| [Friday 05 November 2010] [16:26:45] <twomashi>	It seems like I can't fork, because if I do I'll have one set of redundant background operations
| [Friday 05 November 2010] [16:26:57] <cremes>	hmmm.... does fork also copy all threads or does it just copy the main?
| [Friday 05 November 2010] [16:27:07] <cremes>	so i guess it's a question of the semantics of fork
| [Friday 05 November 2010] [16:27:12] <twomashi>	I suppose it copies all of them,
| [Friday 05 November 2010] [16:27:22] <cremes>	but assuming fork copies everything, i'd say that's a really bad idea :)
| [Friday 05 November 2010] [16:27:27] <twomashi>	Rght
| [Friday 05 November 2010] [16:27:29] <twomashi>	Right*
| [Friday 05 November 2010] [16:27:30] <cremes>	don't fork
| [Friday 05 November 2010] [16:27:34] <twomashi>	sort of a zeromq "gotcha"
| [Friday 05 November 2010] [16:27:45] <cremes>	perhaps
| [Friday 05 November 2010] [16:28:05] <cremes>	you might want to ask this question on the ML too; not everyone who can answer this question is awake right now
| [Friday 05 November 2010] [16:28:08] <twomashi>	yep, fork duplicates threads too.
| [Friday 05 November 2010] [16:28:42] <twomashi>	Yea, could do. I'm going to test this as a theory of why my app isnt working right tho
| [Friday 05 November 2010] [16:28:43] <twomashi>	thanks
| [Friday 05 November 2010] [16:33:13] <cremes>	np
| [Friday 05 November 2010] [16:55:52] <Guthur>	Hehe, it's cool that CL is one of the most consistent language bindings providing examples from the guide
| [Friday 05 November 2010] [17:35:55] <takeda>	Hey guys, how hard is it to add a new protocol to 0MQ?
| [Friday 05 November 2010] [17:38:42] <twomashi>	you mean like make it speak http?
| [Friday 05 November 2010] [17:39:08] <takeda>	well particularly I'm thinking http://www.ccnx.org/
| [Friday 05 November 2010] [17:39:36] <takeda>	and use bindings
| [Friday 05 November 2010] [17:40:05] <takeda>	the protocol is more like request response, though it doesn't guarantee delivery
| [Friday 05 November 2010] [17:40:31] <twomashi>	no idea
| [Friday 05 November 2010] [17:44:27] <takeda>	ok
| [Friday 05 November 2010] [17:44:51] <takeda>	I just want to know if it's a waste of time or not
| [Friday 05 November 2010] [17:45:10] <twomashi>	i dont really understand the fundamental issues
| [Friday 05 November 2010] [17:45:24] <twomashi>	im sure there are others that do
| [Friday 05 November 2010] [17:46:20] <Guthur>	From there own description it seems a little early for that protocol
| [Friday 05 November 2010] [17:46:24] <Guthur>	Very much in the realms of research
| [Friday 05 November 2010] [17:48:36] <takeda>	yeah, that's why I'm thinkinking to implement it myself only things that I would need in order to use the 0MQ bindings in other languages. The protocol is still research and I'm prototyping an application that would use it
| [Friday 05 November 2010] [17:49:24] <twomashi>	0mq supports different transports so I guess they have an abstraction for that
| [Friday 05 November 2010] [17:49:30] <twomashi>	socket, ipc, memory..
| [Friday 05 November 2010] [17:50:33] <takeda>	yeah... the interface is clean, and also if I would need to use other ways it is consistent way of communicating :)
| [Saturday 06 November 2010] [03:02:48] <CIA-20>	zeromq2: 03Martin Sustrik 07master * rc021702 10/ src/mailbox.cpp : 
| [Saturday 06 November 2010] [03:02:48] <CIA-20>	zeromq2: Coding style cleanup in mailbox.cpp
| [Saturday 06 November 2010] [03:02:48] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/9TFok1
| [Saturday 06 November 2010] [05:07:21] <sustrik>	takeda: hi
| [Saturday 06 November 2010] [05:08:08] <sustrik>	you can add new transports but the interface for a transport is not particularly clean
| [Saturday 06 November 2010] [05:08:25] <sustrik>	i would like to clean it up and document it
| [Saturday 06 November 2010] [05:08:42] <sustrik>	so that people can add thier own transports as needed
| [Saturday 06 November 2010] [06:05:03] <xraid>	how do i read and send to a raw socket from zmq ? preferbly a ipc://
| [Saturday 06 November 2010] [06:22:15] <sustrik>	what raw socket?
| [Saturday 06 November 2010] [06:22:19] <sustrik>	BSD socket you mean?
| [Saturday 06 November 2010] [06:27:17] <xraid>	yes a unix:path socket
| [Saturday 06 November 2010] [06:46:48] <sustrik>	BSD sockets have nothing to do with 0mq
| [Saturday 06 November 2010] [06:46:56] <sustrik>	use standard BSD socket API
| [Saturday 06 November 2010] [06:47:36] <dv_>	hi
| [Saturday 06 November 2010] [06:47:47] <dv_>	can I use the same zeromq context in two threads?
| [Saturday 06 November 2010] [06:48:18] <xraid>	sustric whats the -- cremes	Guthur: because you can use it to poll a standard socket as well as a 0mq socket
| [Saturday 06 November 2010] [06:48:39] <xraid>	PollItem ?
| [Saturday 06 November 2010] [06:52:38] <dv_>	hi. according to the docs, I can create one context and use it in more than one thread
| [Saturday 06 November 2010] [06:52:59] <dv_>	but is there something I should know about tring to create a publisher in one thread and a subscriber in another?
| [Saturday 06 November 2010] [06:53:11] <dv_>	I am trying to create a chat program using pub-sub and multicasting
| [Saturday 06 November 2010] [06:53:13] <dv_>	(epgm)
| [Saturday 06 November 2010] [06:53:43] <dv_>	previously I used two contexts, one in each thread, this didnt work.
| [Saturday 06 November 2010] [06:54:50] <dv_>	i dont need synchronization - it doesnt make sense, anyway, since every chatter is a publisher -and- a subscriber
| [Saturday 06 November 2010] [07:36:45] <sustrik>	dv_: the context issue is irrelevant
| [Saturday 06 November 2010] [07:37:10] <sustrik>	try starting with tcp transport
| [Saturday 06 November 2010] [07:37:26] <sustrik>	when it works switch to epgm
| [Saturday 06 November 2010] [07:38:32] <sustrik>	xraid: you've asked about send and recv -- use send(2) and recv(2) for those
| [Saturday 06 November 2010] [07:38:42] <sustrik>	polling is a different issue
| [Saturday 06 November 2010] [07:38:56] <sustrik>	as you may want to combine raw sockets and 0mq sockets
| [Saturday 06 November 2010] [07:40:10] <dv_>	hm
| [Saturday 06 November 2010] [07:40:12] <dv_>	well it works now
| [Saturday 06 November 2010] [07:40:21] <dv_>	with tcp, it is set up immediately
| [Saturday 06 November 2010] [07:40:29] <dv_>	but with epgm, connecting takes about 3 seconds
| [Saturday 06 November 2010] [07:41:00] <dv_>	multicast rate is set to 10000
| [Saturday 06 November 2010] [08:39:14] <dv_>	is epgm broken in zeromq?
| [Saturday 06 November 2010] [08:39:59] <dv_>	when I put a sleep(1) before the connect() call in the receiver , i get an "Invalid argument" error
| [Saturday 06 November 2010] [09:00:24] <dv_>	uh, it gets weirder. apparently, this is related to gcc. I build zeromq with -O0 and everything works just fine... ?!?!?
| [Saturday 06 November 2010] [09:12:28] <mikko>	dv_: are you using master or maint?
| [Saturday 06 November 2010] [09:16:25] <dv_>	zeromq 2.0.10
| [Saturday 06 November 2010] [09:16:29] <dv_>	nothing from git
| [Saturday 06 November 2010] [09:16:51] <dv_>	no something is very wrong. I recompile the app twice, no changes to the code at all.
| [Saturday 06 November 2010] [09:17:04] <dv_>	first time : "invalid argument", second time it works
| [Saturday 06 November 2010] [09:20:30] <dv_>	hmm. is this maybe a race condition? when I step through the connect function, it works. when I dont step, it fails.
| [Saturday 06 November 2010] [09:20:36] <dv_>	(stepping with gdb i mean)
| [Saturday 06 November 2010] [09:24:47] <mikko>	which version of gcc?
| [Saturday 06 November 2010] [09:24:51] <mikko>	sounds a bit odd indeed
| [Saturday 06 November 2010] [09:24:58] <mikko>	have you got reproducable test case?
| [Saturday 06 November 2010] [09:25:09] <dv_>	here, I reduced this to this code: http://codepad.org/SJbVtKcR
| [Saturday 06 November 2010] [09:25:16] <dv_>	this code sometimes succeeds
| [Saturday 06 November 2010] [09:25:32] <mikko>	testing
| [Saturday 06 November 2010] [09:25:34] <mikko>	sec
| [Saturday 06 November 2010] [09:25:36] <dv_>	and sometimes I get    terminate called after throwing an instance of 'zmq::error_t'  what():  Invalid argument
| [Saturday 06 November 2010] [09:25:47] <dv_>	built with   g++-4.4 -Wextra -Wall -std=c++0x -pedantic -o epgm_test epgm_test.cpp -lzmq
| [Saturday 06 November 2010] [09:26:20] <mikko>	need to build with pgm
| [Saturday 06 November 2010] [09:26:23] <mikko>	second
| [Saturday 06 November 2010] [09:26:47] <dv_>	okay. it also happens with fewer flags btw. : g++-4.4 -o epgm_test epgm_test.cpp -lzmq
| [Saturday 06 November 2010] [09:27:16] <mikko>	im testing with git trunk
| [Saturday 06 November 2010] [09:27:23] <mikko>	havent used maint in quite a while
| [Saturday 06 November 2010] [09:27:47] <dv_>	oh, you might want to adjust the URL
| [Saturday 06 November 2010] [09:27:51] <dv_>	I use eth1
| [Saturday 06 November 2010] [09:29:56] <mikko>	https://gist.github.com/53169bc3388ce17e18bd
| [Saturday 06 November 2010] [09:30:13] <mikko>	this is with trunk
| [Saturday 06 November 2010] [09:30:29] <dv_>	yes. now try with -O0
| [Saturday 06 November 2010] [09:30:32] <dv_>	then with -O2
| [Saturday 06 November 2010] [09:30:42] <mikko>	no wait
| [Saturday 06 November 2010] [09:30:51] <mikko>	https://gist.github.com/0c25c16d0f678e81a905
| [Saturday 06 November 2010] [09:30:52] <mikko>	look
| [Saturday 06 November 2010] [09:30:57] <mikko>	it died after a while
| [Saturday 06 November 2010] [09:31:13] <dv_>	uh, never had that
| [Saturday 06 November 2010] [09:31:26] <mikko>	i think i've seen this before
| [Saturday 06 November 2010] [09:31:38] <Ghpu_>	hello
| [Saturday 06 November 2010] [09:31:40] <dv_>	did you set your app to sleep?
| [Saturday 06 November 2010] [09:31:42] <mikko>	same thing with -O0
| [Saturday 06 November 2010] [09:31:49] <dv_>	because, my code exits immediately
| [Saturday 06 November 2010] [09:31:49] <mikko>	no, it's blocking
| [Saturday 06 November 2010] [09:31:56] <dv_>	hmm it does not block here
| [Saturday 06 November 2010] [09:32:06] <dv_>	see why I suspect that something's wrong about epgm ?
| [Saturday 06 November 2010] [09:32:07] <mikko>	different semantics in trunk
| [Saturday 06 November 2010] [09:32:25] <mikko>	possibly
| [Saturday 06 November 2010] [09:32:38] <mikko>	let's see where it's blocking
| [Saturday 06 November 2010] [09:33:03] <mikko>	https://gist.github.com/0c25c16d0f678e81a905#comments
| [Saturday 06 November 2010] [09:34:38] <Ghpu_>	I've just succeeded in having a working version of ZeroMQ 2.1 from trunk ported to the Android platform \o/
| [Saturday 06 November 2010] [09:34:48] <mikko>	Ghpu_: nice!
| [Saturday 06 November 2010] [09:34:57] <Ghpu_>	It required to rebuild the libuuid first
| [Saturday 06 November 2010] [09:35:06] <dv_>	hmm.
| [Saturday 06 November 2010] [09:35:07] <Ghpu_>	and comment out some POSIX optimizations
| [Saturday 06 November 2010] [09:35:25] <dv_>	it seems to me as if multicast connect works *sometimes*
| [Saturday 06 November 2010] [09:35:28] <dv_>	and sometimes it doesnt
| [Saturday 06 November 2010] [09:35:44] <Ghpu_>	i made a package temporarily available on ghislain.putois.free.fr/azmq.tar.bz2 if someone is interested 
| [Saturday 06 November 2010] [09:36:34] <dv_>	i'll try out trunk
| [Saturday 06 November 2010] [09:36:36] <Ghpu_>	it required to use an unofficial ndk, which supports full stdc++ and
| [Saturday 06 November 2010] [09:36:44] <Ghpu_>	stl
| [Saturday 06 November 2010] [09:36:54] <Ghpu_>	but I think it's worth it 
| [Saturday 06 November 2010] [09:39:02] <dv_>	oh now this is interesting. trunk uses a much more recent version of openpgm.
| [Saturday 06 November 2010] [09:39:30] <mikko>	dv_: yes, as far as i know there is going to be openpgm related testing soon
| [Saturday 06 November 2010] [09:39:36] <mikko>	to iron out any bugs
| [Saturday 06 November 2010] [09:40:06] <mikko>	Ghpu_: this sounds like an interesting project
| [Saturday 06 November 2010] [09:40:57] <dv_>	hmm. doesnt seem to happen anymore.
| [Saturday 06 November 2010] [09:41:00] <Ghpu_>	Well, I got it to talk properly between the emulator and a host program on my desktop computer
| [Saturday 06 November 2010] [09:41:17] <mikko>	Ghpu_: is this 'easy' to cross-compile?
| [Saturday 06 November 2010] [09:41:19] <Ghpu_>	I will put a small page on my website to host it for now
| [Saturday 06 November 2010] [09:41:20] <dv_>	oh but I got your assertion, mikko
| [Saturday 06 November 2010] [09:41:37] <dv_>	so trade one bug for another? :)
| [Saturday 06 November 2010] [09:41:37] <Ghpu_>	well, my package is a copy of the needed file with a compile script
| [Saturday 06 November 2010] [09:41:39] <mikko>	dv_: i think it would be good to make a test case out of this
| [Saturday 06 November 2010] [09:41:53] <dv_>	yes, unfortunately it doesnt seem to be deterministic
| [Saturday 06 November 2010] [09:41:56] <dv_>	as in "run it 1000 times"
| [Saturday 06 November 2010] [09:42:02] <Ghpu_>	but the files are slightly modified from the trunk, and the  directory structure is different
| [Saturday 06 November 2010] [09:42:13] <Ghpu_>	so I don't see an easy integration now
| [Saturday 06 November 2010] [09:42:29] <mikko>	Ghpu_: does the directory structure need to be different?
| [Saturday 06 November 2010] [09:42:31] <Ghpu_>	but the overall cross-compilation should be easy 
| [Saturday 06 November 2010] [09:42:42] <Ghpu_>	well, the cross-compilator expects a specific structure
| [Saturday 06 November 2010] [09:42:44] <mikko>	Ghpu_: it would be good if this could be automated so i can add a daily build for it
| [Saturday 06 November 2010] [09:42:54] <Ghpu_>	as far as i know
| [Saturday 06 November 2010] [09:42:55] <mikko>	http://build.valokuva.org/
| [Saturday 06 November 2010] [09:43:17] <Ghpu_>	I still need more time to make a proper diff/patch to the zmq files
| [Saturday 06 November 2010] [09:43:35] <Ghpu_>	this is only my first working step
| [Saturday 06 November 2010] [09:43:41] <mikko>	Ghpu_: do you see this as something that could be cleanly added to upstream?
| [Saturday 06 November 2010] [09:43:49] <Ghpu_>	I'm afraid not
| [Saturday 06 November 2010] [09:44:03] <Ghpu_>	(or not easily for now)
| [Saturday 06 November 2010] [09:44:36] <mikko>	ok
| [Saturday 06 November 2010] [09:44:54] <Ghpu_>	just to let know that it can work 
| [Saturday 06 November 2010] [09:45:23] <mikko>	that is really good news
| [Saturday 06 November 2010] [09:45:24] <dv_>	yes, seems very much like a race condition. perhaps I can look into it a bit more
| [Saturday 06 November 2010] [09:45:36] <mikko>	dv_: that would be great
| [Saturday 06 November 2010] [09:46:12] <dv_>	gotta go now, however. thanks for the help guys, i'll keep you posted.
| [Saturday 06 November 2010] [11:04:24] <Guthur>	Oh, does Swap need to be set after binding  a socket?
| [Saturday 06 November 2010] [11:07:36] <Guthur>	actually is that the case for all options?
| [Saturday 06 November 2010] [11:08:13] <Guthur>	If I set HWM and SWAP before binding for the durable PubSub it doesn't seem to work as expected, is that par for the course?
| [Saturday 06 November 2010] [15:38:45] <shales>	is there a recommended way of setting the file permissions and group of the unix domain socket when binding an IPC socket?
| [Saturday 06 November 2010] [15:39:46] <shales>	should I set the umask and setguid before calling bind? does the underlying call to bind happen before 0mq's bind returns or at some later time?
| [Saturday 06 November 2010] [15:43:34] <shales>	come to think of it, how does 0mq work when an IPC socket connects to a unix domain socket whose file is left over from a previous run and the sever endpoint hasn't called bind yet? I think the server side would have to unlink the file before it can bind again, and 0mq seems to do this automatically, but how do the sockets that connect know to reconnect to the new unix domain socket?
| [Saturday 06 November 2010] [16:10:04] <shales>	ah, I guess after the server closes, the connect will just fail even if the unix socket domain file still exists
| [Saturday 06 November 2010] [16:10:19] <shales>	and 0mq will do its reconnecting
| [Saturday 06 November 2010] [17:14:47] <Guthur>	I am getting an assert fail (line 60 xrep.cpp), while trying to run my version of LRUQueue
| [Saturday 06 November 2010] [17:15:33] <Guthur>	I am using INPROC instead of IPC, due to Win platform; this shouldn't make a difference, correct?
| [Saturday 06 November 2010] [17:31:47] <dv_>	hi
| [Saturday 06 November 2010] [17:32:20] <dv_>	mikko, I narrowed the bug to code inside openpgm - the parse_interface() function
| [Saturday 06 November 2010] [17:32:50] <dv_>	it tries to find a multicast capable interface out of the list I gave it, and it seems that the one I give is sometimes multicast capable, sometimes it isn't
| [Saturday 06 November 2010] [17:42:10] <Guthur>	Oh the assert fail is sorted, it was an issue with my implementation of z_set_id
| [Saturday 06 November 2010] [17:42:39] <Guthur>	it wasn't being random enough
| [Saturday 06 November 2010] [17:51:05] <dv_>	got it - the assert is gone now
| [Saturday 06 November 2010] [17:51:08] <dv_>	but I am not sure why
| [Saturday 06 November 2010] [17:51:09] <dv_>	:)
| [Saturday 06 November 2010] [17:51:57] <mattl_>	I have a valgrind zmq issue. 
| [Saturday 06 November 2010] [17:52:08] <mattl_>	is this the right forum to ask it in?
| [Saturday 06 November 2010] [17:52:47] <dv_>	yes, but I guess you have more luck in the mailing list
| [Saturday 06 November 2010] [17:53:50] <mattl_>	sure. no prob. I will also ask it to the list. But I think my problem is pretty basic. I can't seem to get my test app to recv anything under valgrind
| [Saturday 06 November 2010] [17:54:32] <mattl_>	I am using the test_taskworker.c example app and running it under valgrind and it no longer receives any info
| [Saturday 06 November 2010] [18:06:43] <dv_>	alright, posted the issue to the mailing list
| [Saturday 06 November 2010] [18:07:15] <dv_>	seems to me the openpgm guys wanted to put a little intelligence in their interface checking code, intelligence that goes haywire.
| [Saturday 06 November 2010] [18:07:29] <dv_>	mattl_: without valgrind it always works?
| [Saturday 06 November 2010] [18:13:00] <mattl_>	dv_ I feel quite silly now. Just put the sleep() back into the sender, right after the send, and it works now. 
| [Saturday 06 November 2010] [18:13:11] <mattl_>	thanks for the moral support
| [Saturday 06 November 2010] [18:13:15] <mattl_>	durf..
| [Saturday 06 November 2010] [18:15:42] <dv_>	:)
| [Saturday 06 November 2010] [18:15:51] <dv_>	uh, wait
| [Saturday 06 November 2010] [18:15:56] <dv_>	sleep() after the sender?
| [Saturday 06 November 2010] [18:16:24] <dv_>	sounds like you are masking a race condition or something
| [Sunday 07 November 2010] [06:00:57] <Ghpu_>	hello
| [Sunday 07 November 2010] [12:34:00] <Guthur>	anyone any thoughts on what the minimum Framework requirement should be for CLRZMQ
| [Sunday 07 November 2010] [13:39:43] <mikko>	Guthur: i would imagine it doesn't need much
| [Sunday 07 November 2010] [13:39:45] <mikko>	2.0 ?
| [Sunday 07 November 2010] [13:39:57] <mikko>	but i have to say im not a .NET guy
| [Sunday 07 November 2010] [13:45:51] <Guthur>	I use a few niceties for 4.0
| [Sunday 07 November 2010] [13:46:37] <Guthur>	I could probably bring it too 2.0 compliance though
| [Sunday 07 November 2010] [14:30:15] <cea>	Hi, I'm totally new to zmq :) I'm using python with the python bindings and it works great. Except how do I test of connection is successfull? like socket.isOpen or someting like that?
| [Sunday 07 November 2010] [14:30:37] <cea>	I can't get python to give an error if the connection is not successfull
| [Sunday 07 November 2010] [14:31:25] <cea>	like
| [Sunday 07 November 2010] [14:31:30] <cea>	    connection = socket.connect('tcp://127.0.0.1:5555')
| [Sunday 07 November 2010] [14:31:34] <cea>	print connection
| [Sunday 07 November 2010] [14:31:38] <cea>	gives me "None"
| [Sunday 07 November 2010] [14:34:31] <cea>	I could be alone in here :)
| [Sunday 07 November 2010] [14:53:10] <cea>	yep alone :)
| [Sunday 07 November 2010] [15:29:56] <gandhijee>	hey, i asked this before i think, but anyone know what the oldest version of gcc that compile zeroMQ might be?
| [Sunday 07 November 2010] [17:04:09] <cea>	does anybody here have 2 sec for a quick zeromq python question?
| [Sunday 07 November 2010] [17:04:49] <psino>	cea: you're probably better off just asking the question
| [Sunday 07 November 2010] [17:04:55] <cea>	hehe sure :)
| [Sunday 07 November 2010] [17:05:10] <cea>	dosn't socket.revc have a timeout?
| [Sunday 07 November 2010] [17:05:28] <Guthur>	if no one can answer here then the mailing list would be a good bet
| [Sunday 07 November 2010] [17:05:38] <cea>	thanks Guthur
| [Sunday 07 November 2010] [17:06:21] <psino>	cea: you should take a look at zmq.Poller
| [Sunday 07 November 2010] [17:06:38] <cea>	is it working for the python binding?
| [Sunday 07 November 2010] [17:06:42] <cea>	can't find any examples on this
| [Sunday 07 November 2010] [17:07:55] <cea>	I can't find anything about polling in any of the python examples
| [Sunday 07 November 2010] [17:08:47] <Guthur>	cea, it seems to
| [Sunday 07 November 2010] [17:08:53] <Guthur>	ioloop.py
| [Sunday 07 November 2010] [17:09:42] <Guthur>	I've not used the python binding though so can not testify to its readiness for use
| [Sunday 07 November 2010] [17:10:13] <cea>	okay, thnaks, found it :) I will have a look - thanks for pointing me in the right direction!!
| [Sunday 07 November 2010] [17:10:17] <cea>	(thanks)
| [Sunday 07 November 2010] [17:10:51] <Guthur>	you're welcome
| [Sunday 07 November 2010] [19:09:35] <Guthur>	0MQ does work on x86-64, correct?
| [Sunday 07 November 2010] [19:09:44] <Guthur>	polling in particualr
| [Sunday 07 November 2010] [19:09:47] <Guthur>	particular*
| [Sunday 07 November 2010] [19:31:49] <Guthur>	oh got it sorted
| [Sunday 07 November 2010] [19:32:06] <Guthur>	SOCKET changes size depending on x86 x86-64
| [Sunday 07 November 2010] [19:32:22] <Guthur>	Is fd always and int on *nix
| [Sunday 07 November 2010] [19:32:51] <Guthur>	this is in the zmq_pollitem_t struct
| [Sunday 07 November 2010] [19:35:49] <Guthur>	oh it is, how bothersome
| [Monday 08 November 2010] [03:08:58] <euk>	hi all
| [Monday 08 November 2010] [03:09:52] <euk>	can anyone advise on unlimited memory growth with zmq? 
| [Monday 08 November 2010] [03:10:22] <guido_g>	see HWM socket option and read the guide
| [Monday 08 November 2010] [03:10:24] <euk>	when just sending and receiving a large set (millions) of small messages
| [Monday 08 November 2010] [03:10:44] <euk>	thank you
| [Monday 08 November 2010] [03:20:05] <euk>	another question - i'm getting tcp throughput higher than ipc (linux, small messages). is that normal? cpu utilization is higher on tcp (so every message takes more cpu), still throughput is somehow higher
| [Monday 08 November 2010] [04:49:03] <Guthur>	sustrik: Do you think it would be worth making a clrzmq2 repo
| [Monday 08 November 2010] [06:12:00] <sustrik>	Guthur: yes, you can't just drop the existing codebase
| [Monday 08 November 2010] [06:16:27] <Guthur>	Yeah that's fair enough
| [Monday 08 November 2010] [06:17:00] <mikko>	mornin'
| [Monday 08 November 2010] [06:17:29] <sustrik>	mikko: morning
| [Monday 08 November 2010] [06:17:33] <Guthur>	Just felt it might be better to make the distinction clear, and especially considering it can not ever go into the master due to the compatibility issue
| [Monday 08 November 2010] [06:18:01] <mikko>	what is the biggest compatibility break?
| [Monday 08 November 2010] [06:19:48] <Guthur>	mikko: Most of it to be honest
| [Monday 08 November 2010] [06:19:56] <Guthur>	I used namespaces for one
| [Monday 08 November 2010] [06:20:14] <Guthur>	Also changed the constants to enums
| [Monday 08 November 2010] [06:21:25] <sustrik>	mikko: what about tomorrow, fance have a beer in the evening?
| [Monday 08 November 2010] [06:21:30] <mikko>	sustrik: sure
| [Monday 08 November 2010] [06:21:34] <mikko>	it's a storm in london
| [Monday 08 November 2010] [06:21:38] <mikko>	so take an umbrella
| [Monday 08 November 2010] [06:22:27] <mato>	hi guys
| [Monday 08 November 2010] [06:22:33] <sustrik>	i was already told about the storm in london by the girl behind the counter in the local supermarket here :)
| [Monday 08 November 2010] [06:22:44] <sustrik>	mato: hi
| [Monday 08 November 2010] [06:22:47] <Guthur>	Recv also just now just returns the message, its null if there is no message, this removes the need for an out parameter,
| [Monday 08 November 2010] [06:22:51] <mato>	sustrik: i've replied to the mailbox problem, can you check if my reasoning is correct?
| [Monday 08 November 2010] [06:22:56] <sustrik>	mikko: 7pm or so?
| [Monday 08 November 2010] [06:23:08] <sustrik>	let me see
| [Monday 08 November 2010] [06:23:16] <mikko>	sustrik: 7pm in Doggett's Coat & Badge ?
| [Monday 08 November 2010] [06:23:31] <mikko>	is that fine or do you want to eat something nicer?
| [Monday 08 November 2010] [06:23:41] <sustrik>	i am ok with that
| [Monday 08 November 2010] [06:23:57] <sustrik>	can you drop a notice to the mailing list in case someone would like to join us?
| [Monday 08 November 2010] [06:24:15] <mikko>	yeah, i'm just thinking if there was a nicer place to eat
| [Monday 08 November 2010] [06:24:22] <mikko>	at 7pm people are going to be hungry
| [Monday 08 November 2010] [06:24:29] <sustrik>	mikko: it's up to you
| [Monday 08 November 2010] [06:24:39] <sustrik>	i am not familiar with london too much
| [Monday 08 November 2010] [06:25:03] <mikko>	what kind of food do you like?
| [Monday 08 November 2010] [06:25:28] <sustrik>	all kinds :)
| [Monday 08 November 2010] [06:28:11] <sustrik>	mato: yes, the reasoning seems correct
| [Monday 08 November 2010] [06:28:25] <mato>	sustrik: ok, i'll whip up a patch and get chuck to test it
| [Monday 08 November 2010] [06:28:26] <sustrik>	however, keep in mind that by writing a command in two chunks
| [Monday 08 November 2010] [06:28:38] <sustrik>	you can recv it in 2 chunks as well
| [Monday 08 November 2010] [06:28:48] <sustrik>	so the recv part has to be changed as well
| [Monday 08 November 2010] [06:28:58] <mato>	hmm
| [Monday 08 November 2010] [06:33:57] <mikko>	sustrik: where are you staying ?
| [Monday 08 November 2010] [06:34:47] <sustrik>	southwark
| [Monday 08 November 2010] [06:34:55] <sustrik>	but choose any place you like
| [Monday 08 November 2010] [06:35:02] <mikko>	http://www.doggettscoatandbadge.co.uk/
| [Monday 08 November 2010] [06:35:05] <mikko>	it's easy
| [Monday 08 November 2010] [06:35:41] <sustrik>	yep, that's 2 mins from my hotel
| [Monday 08 November 2010] [06:38:14] <mato>	sustrik: the recv() side could in theory use MSG_WAITALL
| [Monday 08 November 2010] [06:38:41] <mato>	sustrik: I can try that and give it to chuck to test
| [Monday 08 November 2010] [06:39:00] <mato>	sustrik: there's also the problem that if recv() gets EINTR, it *may* get some bytes...
| [Monday 08 November 2010] [06:39:08] <mikko>	sustrik: sent
| [Monday 08 November 2010] [06:39:12] <mato>	sustrik: which sucks, I'm not sure how to solve that...
| [Monday 08 November 2010] [06:39:19] <sustrik>	mikko: thx
| [Monday 08 November 2010] [06:39:23] <mikko>	should've written Martin S. as there are many martins
| [Monday 08 November 2010] [06:39:23] <sustrik>	see you tomorrow
| [Monday 08 November 2010] [06:39:24] <mikko>	:)
| [Monday 08 November 2010] [06:39:38] <sustrik>	mato: EINTR?
| [Monday 08 November 2010] [06:39:51] <mato>	sustrik: yes, what?
| [Monday 08 November 2010] [06:39:55] <sustrik>	how would the API report that kind of thing?
| [Monday 08 November 2010] [06:40:03] <mato>	sustrik: it already does report EINTR
| [Monday 08 November 2010] [06:40:06] <sustrik>	nbytes == 3 && errno = EITNR?
| [Monday 08 November 2010] [06:40:12] <mato>	oh, that, right
| [Monday 08 November 2010] [06:40:32] <mato>	sustrik: sorry, you're right, i was reading the recvmsg docs
| [Monday 08 November 2010] [06:41:07] <sustrik>	as for the WAITALL wouldn't it work only for blocking recv?
| [Monday 08 November 2010] [06:42:12] <sustrik>	is there a way to combine WAITALL and NONBLOCK?
| [Monday 08 November 2010] [06:43:16] <mato>	unclear
| [Monday 08 November 2010] [06:43:21] <mato>	hang on, reading various threads
| [Monday 08 November 2010] [06:43:39] <mato>	sustrik: the most reliable way to do it would be to use a datagram socket instead of a stream socket
| [Monday 08 November 2010] [06:43:53] <mato>	sustrik: datagram sockets guarantee that the send/recv is atomic
| [Monday 08 November 2010] [06:43:59] <sustrik>	mato: is it possible with socketpair?
| [Monday 08 November 2010] [06:44:42] <mato>	sustrik: yes, you just ask for AF_UNIX, SOCK_DGRAM
| [Monday 08 November 2010] [06:45:13] 	 * sustrik wonders how does that fill SNDBUF
| [Monday 08 November 2010] [06:45:18] <mato>	?
| [Monday 08 November 2010] [06:45:24] <mato>	What do you mean?
| [Monday 08 November 2010] [06:45:24] <sustrik>	MTU per packet?
| [Monday 08 November 2010] [06:45:38] <mato>	?
| [Monday 08 November 2010] [06:45:49] <sustrik>	if you send command, which was 1 byte
| [Monday 08 November 2010] [06:45:59] <sustrik>	how much of the buffer will be used
| [Monday 08 November 2010] [06:46:02] <sustrik>	1 byte
| [Monday 08 November 2010] [06:46:04] <sustrik>	?
| [Monday 08 November 2010] [06:46:10] <sustrik>	MTU bytes?
| [Monday 08 November 2010] [06:46:15] <mato>	No idea
| [Monday 08 November 2010] [06:46:19] <mato>	System-dependent
| [Monday 08 November 2010] [06:46:50] <sustrik>	it can make the problem even worse
| [Monday 08 November 2010] [06:46:53] <sustrik>	in any case, you should be able to read the command using at most 2 recv calls
| [Monday 08 November 2010] [06:47:05] <sustrik>	given that you write it using at most 2 sends
| [Monday 08 November 2010] [06:47:28] <mato>	guess so
| [Monday 08 November 2010] [06:47:42] <sustrik>	assert (PIPE_BUF < sizeof (command_t)) guarantees that
| [Monday 08 November 2010] [06:47:51] <sustrik>	>=
| [Monday 08 November 2010] [06:48:07] <mato>	I kind of doubt PIPE_BUF has much to do with AF_UNIX sockets
| [Monday 08 November 2010] [06:49:28] <sustrik>	what does it apply to then?
| [Monday 08 November 2010] [06:49:32] <sustrik>	mkfifo?
| [Monday 08 November 2010] [06:49:35] <mato>	sustrik: pipes
| [Monday 08 November 2010] [06:49:37] <mato>	sustrik: yeah
| [Monday 08 November 2010] [06:49:46] <sustrik>	btw, why aren't we using pipes?
| [Monday 08 November 2010] [06:50:19] <mato>	UNIX sockets are better these days IMO
| [Monday 08 November 2010] [06:50:29] <mato>	also you don't have to invent funky naming schemes
| [Monday 08 November 2010] [06:50:30] <mato>	etc etc
| [Monday 08 November 2010] [06:50:40] <mato>	since socketpair nicely gives you an anonymous pair
| [Monday 08 November 2010] [06:51:01] <sustrik>	ok
| [Monday 08 November 2010] [06:51:04] <mato>	sustrik: also, pipes have some fixed buffer sized
| [Monday 08 November 2010] [06:51:09] <mato>	sustrik: not resizable
| [Monday 08 November 2010] [06:51:39] <sustrik>	i was just thinking about the fact that what we need is unidirectional pipe
| [Monday 08 November 2010] [06:51:49] <sustrik>	the other direction is unused
| [Monday 08 November 2010] [06:52:01] <mato>	too bad :-)
| [Monday 08 November 2010] [06:52:14] <mato>	use it for something :-)
| [Monday 08 November 2010] [06:52:19] <mato>	if it bothers you :-)
| [Monday 08 November 2010] [06:52:29] <sustrik>	maybe we can at least shrink the buffer for that direction?
| [Monday 08 November 2010] [06:52:58] <mato>	maybe
| [Monday 08 November 2010] [07:29:34] <Guthur>	sustrik: Can someone create a zeromq / clrzmq2 repo?
| [Monday 08 November 2010] [07:30:04] <sustrik>	yup, wait a sec
| [Monday 08 November 2010] [07:31:02] <Guthur>	I'm at work at the moment but when I get home I can move the code to it and update the clrzmq page accordingly
| [Monday 08 November 2010] [07:32:38] <Guthur>	I'm off for lunch back in a bit
| [Monday 08 November 2010] [07:33:26] <mato>	sustrik: I occasionally get this from test_shutdown_stress:
| [Monday 08 November 2010] [07:33:33] <mato>	Socket operation on non-socket
| [Monday 08 November 2010] [07:33:33] <mato>	nbytes != -1 (tcp_socket.cpp:197)
| [Monday 08 November 2010] [07:33:33] <mato>	/bin/sh: line 4: 32321 Aborted                 (core dumped) ${dir}$tst
| [Monday 08 November 2010] [07:33:33] <mato>	FAIL: test_shutdown_stress
| [Monday 08 November 2010] [07:34:36] <sustrik>	mato: yes, the problem was reported already
| [Monday 08 November 2010] [07:40:51] <mato>	sustrik: ok, well, I have a preliminary patch for the mailbox retry stuff, sent to the ML
| [Monday 08 November 2010] [07:41:45] <sustrik>	mato: thanks
| [Monday 08 November 2010] [07:46:48] <dv_>	what would be the recommended way to implement a messaging without a response?
| [Monday 08 November 2010] [07:47:01] <dv_>	i have two nodes A and B, and they communicate asynchronously,
| [Monday 08 November 2010] [07:47:13] <dv_>	there are no "requests" and subsequent "responses", only events
| [Monday 08 November 2010] [07:48:06] <dv_>	i could open two req-rep connections between the two, so that both are requesters, and simply not use the response (or send some dummy response)
| [Monday 08 November 2010] [07:48:10] <dv_>	but that sounds wasteful
| [Monday 08 November 2010] [07:48:19] <dv_>	any suggestions?
| [Monday 08 November 2010] [07:48:43] <sustrik>	Guthur: done
| [Monday 08 November 2010] [07:49:44] <sustrik>	dv_: you have to think about scaling to get it right
| [Monday 08 November 2010] [07:49:55] <sustrik>	are there going to be multiple A's in the future?
| [Monday 08 November 2010] [07:50:00] <sustrik>	or multiple B's?
| [Monday 08 November 2010] [07:50:16] <sustrik>	if so, how are the messages to be dispatched to the multiple instances?
| [Monday 08 November 2010] [07:50:25] <sustrik>	each message to each instance?
| [Monday 08 November 2010] [07:50:29] <sustrik>	if so, use PUB/SUB
| [Monday 08 November 2010] [07:50:46] <sustrik>	if you want to load-balance messages between instances
| [Monday 08 November 2010] [07:50:51] <sustrik>	use PUSH/PULL
| [Monday 08 November 2010] [07:51:16] <dv_>	no they would be peers
| [Monday 08 November 2010] [07:51:58] <dv_>	there is a pair pattern, but it is marked as experimental
| [Monday 08 November 2010] [07:52:15] <dv_>	if multiple A's/B's were the case, i would use pub/sub, yes
| [Monday 08 November 2010] [07:52:32] <dv_>	hmm. you know, I could also use it for two nodes only.
| [Monday 08 November 2010] [07:52:44] <dv_>	but can multiple publishers exist with an IPC connection?
| [Monday 08 November 2010] [07:53:15] <sustrik>	you can have multiple pubs pushing messages to a single SUB for example
| [Monday 08 November 2010] [07:54:00] <dv_>	in fact, can i have multiple publishers with any kind of connection?
| [Monday 08 November 2010] [07:54:11] <sustrik>	yes
| [Monday 08 November 2010] [07:54:27] <dv_>	cool
| [Monday 08 November 2010] [07:55:10] <dv_>	i have an audio playback process here that is controlled by the frontend, and the playback process can send events, such as "song finished", "song metadata scanned" ..
| [Monday 08 November 2010] [07:55:19] <dv_>	i think i'll use pub-sub here
| [Monday 08 November 2010] [07:56:36] <dv_>	but does the IPC mechanism scale linearly with the amount of publishers/subscribers? for example, with tcp, since it is strictly point-to-point, i have a situation where every node has connections to all the other nodes, right?
| [Monday 08 November 2010] [08:08:39] <sustrik>	right, same with ipc
| [Monday 08 November 2010] [08:10:39] <dv_>	something like multicast for ipc would rock. but i guess this is far from trivial. not just in zeromq, but speaking generally
| [Monday 08 November 2010] [08:11:28] <sustrik>	the whole multicast thing is a complex thing
| [Monday 08 November 2010] [08:11:46] <sustrik>	for ipc to prevent copying the message you would have to have it stored in shmem
| [Monday 08 November 2010] [08:11:49] <dv_>	i noticed. i stumbled upon weird bugs that i have yet to replicate with the openpgm tools.
| [Monday 08 November 2010] [08:11:57] <sustrik>	however, allocating shmem is an expensive operation
| [Monday 08 November 2010] [08:12:02] <sustrik>	so it's not that easy
| [Monday 08 November 2010] [08:12:07] <dv_>	to think of that in ipc ...
| [Monday 08 November 2010] [08:12:10] <dv_>	yes i see
| [Monday 08 November 2010] [08:13:38] <dv_>	oh one other thing, when I use pub/sub with multicast (epgm),
| [Monday 08 November 2010] [08:13:51] <dv_>	and I turn set mcast_loop to 0 in the publisher socket,
| [Monday 08 November 2010] [08:14:22] <dv_>	the receiver doesnt get anything anymore - but i've only tried it out with receiver and sender running on the same host so far
| [Monday 08 November 2010] [08:15:07] <dv_>	if I understand this correctly, mcast_loop 0 means that only messages sent between hosts will pass through? i found that part of the manual a bit confusing
| [Monday 08 November 2010] [08:15:29] <dv_>	(thats my last question btw. :) )
| [Monday 08 November 2010] [08:15:38] <sustrik>	dv_: yes, that's how it works
| [Monday 08 November 2010] [08:15:50] <sustrik>	multicast over loopback is a terrible hack
| [Monday 08 November 2010] [08:16:00] <sustrik>	that is better not to use at all
| [Monday 08 November 2010] [08:16:10] <dv_>	hmm. i wonder if the bugs i noticed stem from this
| [Monday 08 November 2010] [08:16:25] <dv_>	i will use IPC for nodes on the same host then
| [Monday 08 November 2010] [08:16:49] <sustrik>	quite possibly, anyway turning mcast_loop to off means you won't get the messages on the same host
| [Monday 08 November 2010] [08:17:13] <dv_>	i dont know if you follow the mailing list much, the bug I mentioned was an assert that happened randomly
| [Monday 08 November 2010] [08:17:30] <dv_>	openpgm sometimes thinks there is no multicast capable NIC
| [Monday 08 November 2010] [08:17:40] <sustrik>	i'm following the list, but i have little knowledge of openpgm
| [Monday 08 November 2010] [08:17:47] <dv_>	overriding internal openpgm checks made it work all the time
| [Monday 08 November 2010] [08:17:51] <dv_>	but it felt ... wrong.
| [Monday 08 November 2010] [08:18:02] <sustrik>	steve mccoy should comment on that
| [Monday 08 November 2010] [08:18:10] <dv_>	he did. i just mention it
| [Monday 08 November 2010] [08:18:15] <dv_>	hmm i'll tell him about the same host
| [Monday 08 November 2010] [08:18:43] <dv_>	or no, hold on. it already happened when I was just creating a publisher socket
| [Monday 08 November 2010] [08:19:18] <dv_>	but maybe turning off mcast_loop first does help ... i'll try it out this afternoon. thanks for the suggestions.
| [Monday 08 November 2010] [08:21:33] <cremes>	mato: any chance you can send me that mailbox patch as a gist? i get "fatal: corrupt patch at line 6" if i copy/paste it into a file for application
| [Monday 08 November 2010] [08:22:34] <mato>	i'll email it to you directly
| [Monday 08 November 2010] [08:22:47] <mato>	cremes: what's your email address?
| [Monday 08 November 2010] [08:23:58] <mato>	cremes: I sent it to the email you use on the ML.
| [Monday 08 November 2010] [08:26:27] <cremes>	mato: perfect; applied it but now get another assertion
| [Monday 08 November 2010] [08:26:28] <cremes>	Assertion failed: nbytes == want_nbytes (mailbox.cpp:213)
| [Monday 08 November 2010] [08:27:33] <mato>	cremes: Hmm, well, that's precisely what shouldn't happen
| [Monday 08 November 2010] [08:28:18] <mato>	cremes: Either you send me your code and I'll try and reproduce it here, or insert some printf's in the various code paths in send() yourself and try and figure out the actual sequence of syscalls
| [Monday 08 November 2010] [08:28:41] <cremes>	if you have ruby 1.9.2 on your system, i can send you the code
| [Monday 08 November 2010] [08:28:42] <mato>	it's possible OSX is behaving funny when the socket SNDBUF is resized
| [Monday 08 November 2010] [08:29:07] <cremes>	otherwise, suggest what details you want printed out and i'll modify the 0mq source locally
| [Monday 08 November 2010] [08:29:10] <mato>	cremes: no i don't, sorry... I have some oldish snapshot of 1.9.1
| [Monday 08 November 2010] [08:29:15] <cremes>	ok
| [Monday 08 November 2010] [08:29:29] <cremes>	before modifying the source, i'll try this on my archlinux box
| [Monday 08 November 2010] [08:29:35] <mato>	cremes: that's a good idea
| [Monday 08 November 2010] [08:29:37] <cremes>	let's see if linux blows up too
| [Monday 08 November 2010] [08:31:43] <mato>	lunch. bbl
| [Monday 08 November 2010] [08:35:05] <cremes>	mato: when i run the *unpatched* master on linux against my code example, i get a different assertion
| [Monday 08 November 2010] [08:35:06] <cremes>	Assertion failed: new_sndbuf > old_sndbuf (mailbox.cpp:182)
| [Monday 08 November 2010] [08:35:13] <cremes>	let me try it with the patch...
| [Monday 08 November 2010] [08:35:26] <mato>	cremes: that means you hit the system SNDBUF max
| [Monday 08 November 2010] [08:35:36] <mato>	cremes: set the net.core.wmem_max sysctl to something high
| [Monday 08 November 2010] [08:35:43] <mato>	cremes: and it'll go away
| [Monday 08 November 2010] [08:36:34] <cremes>	ko
| [Monday 08 November 2010] [09:39:49] <cremes>	ok, so after boosting net.core.wmem_max i am now getting a socket error "too many open files" when i allocate 508 REQ sockets
| [Monday 08 November 2010] [09:40:15] <cremes>	according to ulimit -n, i set the file descriptor max to 250_000 and i still get that
| [Monday 08 November 2010] [09:40:28] <cremes>	this is on archlinux, kernel 2.6.35
| [Monday 08 November 2010] [09:41:51] <cremes>	same behavior with *and* without mato's patch
| [Monday 08 November 2010] [09:55:33] <pieterh>	cremes, cat /proc/sys/fs/file-max
| [Monday 08 November 2010] [09:55:38] <pieterh>	what does it give you?
| [Monday 08 November 2010] [09:56:10] <mato>	cremes: for ulimit -n you'll have to run that as root, then from that *same* root shell run your code
| [Monday 08 November 2010] [09:56:22] <mato>	cremes: since it's inherited to child processes, it is not a system setting
| [Monday 08 November 2010] [09:56:33] <mato>	my patch doesn't change anything wrt number of open files
| [Monday 08 November 2010] [09:56:40] <cremes>	pieterh: results in 1201177
| [Monday 08 November 2010] [09:56:42] <pieterh>	This is from the Confluence wiki
| [Monday 08 November 2010] [09:56:44] <pieterh>	Run the command sysctl -a. If this is less than 200000, increase the number of file handles by editing /etc/sysctl.conf and changing the property fs.file-max to 200000. If there isn't a value set already for this property, you need to add the line fs.file-max=200000.
| [Monday 08 November 2010] [09:56:44] <pieterh>	Then run sysctl -p to apply your changes to your system.
| [Monday 08 November 2010] [09:56:50] <cremes>	mato: i logged in a fresh shell after making the change
| [Monday 08 November 2010] [09:56:59] <mato>	cremes: yes, but that won't work
| [Monday 08 November 2010] [09:57:10] <pieterh>	cremes: seems high enough, how about 'sysctl -a'?
| [Monday 08 November 2010] [09:57:37] <mato>	cremes: verify with ulimit -a in the shell that you're running your code in that the setting has actually taken effect
| [Monday 08 November 2010] [09:57:56] <mato>	cremes: anyway, this is beside the point of my patch, so you're running into some macosx weirdness there
| [Monday 08 November 2010] [09:57:58] <cremes>	mato: it tells me 250000 for open files
| [Monday 08 November 2010] [09:58:07] <cremes>	this is on linux
| [Monday 08 November 2010] [09:58:12] <pieterh>	archlinux
| [Monday 08 November 2010] [09:58:16] <mato>	cremes: and you're still running out of open files?
| [Monday 08 November 2010] [09:58:19] <cremes>	yep
| [Monday 08 November 2010] [09:58:25] <mato>	cremes: then your code is the problem, sorry :-)
| [Monday 08 November 2010] [09:58:30] <cremes>	ha
| [Monday 08 November 2010] [09:58:39] <pieterh>	cremes: do you have a simple test case I can try?
| [Monday 08 November 2010] [09:58:41] <mato>	as in, the number of open files is not infinite :-)
| [Monday 08 November 2010] [09:59:15] <cremes>	pieterh: results of sysctl -a .... https://gist.github.com/667772
| [Monday 08 November 2010] [09:59:18] <mato>	cremes: anyhow, the interesting case is the failure you're getting on macosx, let me know when you have time to put some printfs in the mailbox code
| [Monday 08 November 2010] [09:59:36] <cremes>	mato: i have time now; give me suggestions on what is important and i'll print it out
| [Monday 08 November 2010] [09:59:46] <pieterh>	cremes, fs.file-max = 1201177
| [Monday 08 November 2010] [09:59:46] <pieterh>	fs.nr_open = 1048576
| [Monday 08 November 2010] [09:59:57] <cremes>	pieterh: if you have ruby 1.9.2 then i can give you a relatively simple test case
| [Monday 08 November 2010] [10:00:06] <pieterh>	derp
| [Monday 08 November 2010] [10:00:13] <mato>	cremes: print nbytes after the 1st do loop in send() (after line 163)
| [Monday 08 November 2010] [10:00:24] <cremes>	mato: prepatched or postpatch?
| [Monday 08 November 2010] [10:00:28] <mato>	cremes: patched
| [Monday 08 November 2010] [10:00:46] <mato>	cremes: then, print old_sndbuf, new_sndbuf after the assert on line 184
| [Monday 08 November 2010] [10:01:20] <mato>	cremes: and print retry_nbytes after the 2nd do loop in send(), i.e. after line 202
| [Monday 08 November 2010] [10:01:36] <mato>	cremes: that should give us an idea of what is going on...
| [Monday 08 November 2010] [10:02:19] <mato>	cremes: oh, and each thing that you print...
| [Monday 08 November 2010] [10:02:31] <mato>	cremes: print also the this pointer as %p, (void *)this
| [Monday 08 November 2010] [10:02:40] <mato>	cremes: so that it's obvious which printf belongs to which instance
| [Monday 08 November 2010] [10:07:15] <pieterh>	cremes, how about trying a simple program to test your Linux file handle limit... 
| [Monday 08 November 2010] [10:07:15] <pieterh>	https://gist.github.com/667779
| [Monday 08 November 2010] [10:09:20] <pieterh>	i can create over 8M sockets on my linux box
| [Monday 08 November 2010] [10:10:49] <cremes>	pieterh: where is zfl.h at?
| [Monday 08 November 2010] [10:11:49] <mikko>	cremes: github/zeromq/zfl
| [Monday 08 November 2010] [10:13:57] <pieterh>	cremes: sorry, just use zmq.h it'll work too
| [Monday 08 November 2010] [10:14:08] 	 * pieterh goes to fix that
| [Monday 08 November 2010] [10:14:49] <pieterh>	cremes, ok, fixed it
| [Monday 08 November 2010] [10:14:54] <cremes>	pieterh: give me the line to compile it please... i tried "gcc test.c" but it's bitching about implicit declaration of 'printf'
| [Monday 08 November 2010] [10:15:04] <pieterh>	ack, take my fixed version
| [Monday 08 November 2010] [10:15:12] <pieterh>	gcc -o testit testit.c
| [Monday 08 November 2010] [10:15:25] <pieterh>	don't call c programs 'test' cause 'test' is a built-in shell command
| [Monday 08 November 2010] [10:15:48] <pieterh>	gcc -o testit -lzmq testit.c
| [Monday 08 November 2010] [10:15:53] <mato>	pieterh: your program will fall over in zmq sooner than it can print the number of sockets it managed to create
| [Monday 08 November 2010] [10:16:01] <pieterh>	mato: doesn't seem to
| [Monday 08 November 2010] [10:16:03] <mato>	pieterh: becuase of the mailbox failing to get a socket
| [Monday 08 November 2010] [10:16:21] <mato>	pieterh: well, in master anyway
| [Monday 08 November 2010] [10:16:34] <pieterh>	perhaps in master, yes... i was just trying in 2.0.10
| [Monday 08 November 2010] [10:16:38] 	 * pieterh retries in master
| [Monday 08 November 2010] [10:16:42] <mato>	2.0.10 is much different
| [Monday 08 November 2010] [10:16:57] <mato>	in fact, in 2.1 even if it did not fall over, it would produce a different number
| [Monday 08 November 2010] [10:17:03] <pieterh>	hey: :-)
| [Monday 08 November 2010] [10:17:09] <pieterh>	"too many open files"
| [Monday 08 November 2010] [10:17:24] <pieterh>	not even a clean return, just internal failure
| [Monday 08 November 2010] [10:17:26] <pieterh>	neato
| [Monday 08 November 2010] [10:17:27] <mato>	2.0.10 has completely different signalling mechanisms
| [Monday 08 November 2010] [10:17:39] <cremes>	pieterh: aha!
| [Monday 08 November 2010] [10:17:44] <pieterh>	Too many open files
| [Monday 08 November 2010] [10:17:44] <pieterh>	rc == 0 (mailbox.cpp:374)
| [Monday 08 November 2010] [10:17:44] <pieterh>	Aborted (core dumped)
| [Monday 08 November 2010] [10:17:52] <cremes>	maybe i'm not so crazy after all...? :)
| [Monday 08 November 2010] [10:18:00] <pieterh>	cremes: i can't make a test program for that :-)
| [Monday 08 November 2010] [10:18:08] <cremes>	too bad...
| [Monday 08 November 2010] [10:18:24] <pieterh>	let me see how quickly it dies...
| [Monday 08 November 2010] [10:18:41] <mato>	with the default limit of 1024 it'll die somewhere around 512
| [Monday 08 November 2010] [10:18:57] <mato>	actually, probably not
| [Monday 08 November 2010] [10:19:04] <pieterh>	cremes!
| [Monday 08 November 2010] [10:19:05] <mato>	it'll die at 1024/3 roughly i'd guess
| [Monday 08 November 2010] [10:19:06] <pieterh>	hey!
| [Monday 08 November 2010] [10:19:09] <pieterh>	it dies at 508
| [Monday 08 November 2010] [10:19:22] <mato>	yup
| [Monday 08 November 2010] [10:19:32] <pieterh>	wow... from >8M to 508... that is quite a step backwards
| [Monday 08 November 2010] [10:19:49] <pieterh>	ok, mato, where's that default limit of 1K?
| [Monday 08 November 2010] [10:19:59] <cremes>	pieterh: 508 is what i see too
| [Monday 08 November 2010] [10:20:11] <mato>	hang on guys, there are several things going on here
| [Monday 08 November 2010] [10:20:13] <pieterh>	net.core.wmem_max.. right?
| [Monday 08 November 2010] [10:20:16] <mato>	no
| [Monday 08 November 2010] [10:20:22] <mato>	that's part of it
| [Monday 08 November 2010] [10:20:38] <mato>	allow me to explain
| [Monday 08 November 2010] [10:20:44] <pieterh>	shoot 
| [Monday 08 November 2010] [10:21:04] <mato>	in 2.0.x, there is one signalling socketpair (what is called mailbox in 2.1) per *application thread*
| [Monday 08 November 2010] [10:21:25] <mato>	hence, creating a 0mq socket does not use up an actual file descriptor
| [Monday 08 November 2010] [10:21:35] <pieterh>	ah, neat
| [Monday 08 November 2010] [10:21:47] <mato>	now, in 2.1 the situation is entirely different
| [Monday 08 November 2010] [10:21:57] <mato>	each 0mq socket created == 1 mailbox
| [Monday 08 November 2010] [10:22:11] <mato>	2 file descriptors
| [Monday 08 November 2010] [10:22:30] <mato>	hence, if the default limit is 1024, you'll die at <512
| [Monday 08 November 2010] [10:22:32] <pieterh>	sure... 
| [Monday 08 November 2010] [10:22:43] <pieterh>	now we have a trivial reproducible case on a default linux box
| [Monday 08 November 2010] [10:22:48] <pieterh>	how do I raise that limit?
| [Monday 08 November 2010] [10:22:54] <cremes>	guys, what is the printf format code for printing ssize_t?
| [Monday 08 November 2010] [10:22:58] <pieterh>	%d
| [Monday 08 November 2010] [10:23:06] <mato>	cremes: use %d and cast it to int
| [Monday 08 November 2010] [10:23:07] <cremes>	archlinux bitches at me about that
| [Monday 08 November 2010] [10:23:11] <pieterh>	%u maybe
| [Monday 08 November 2010] [10:23:12] <cremes>	ah, ok, it will fit
| [Monday 08 November 2010] [10:23:14] <mato>	cremes: there is no printf format for ssize_t
| [Monday 08 November 2010] [10:23:27] <mato>	now, as to raising the limit
| [Monday 08 November 2010] [10:23:31] <mato>	there are two limits
| [Monday 08 November 2010] [10:23:46] <mato>	1. the system maximum, which is the sysctl pieter already mentioned
| [Monday 08 November 2010] [10:23:53] <mato>	normally you don't need to touch that
| [Monday 08 November 2010] [10:24:26] <mato>	2. your distribution will have some $mechanism for setting a default RLIMIT_NOFILE on login, usually to 1024
| [Monday 08 November 2010] [10:24:38] <mato>	if you want to raise that, either figure out where the setting for $mechanism is
| [Monday 08 November 2010] [10:24:40] <mato>	or
| [Monday 08 November 2010] [10:24:48] <mato>	1. (as user) $ su root
| [Monday 08 November 2010] [10:24:58] <mato>	2. (as root) # ulimit -n 8192
| [Monday 08 November 2010] [10:25:09] <mato>	3. (still as that root) # su user
| [Monday 08 November 2010] [10:25:14] <mato>	4. run your app
| [Monday 08 November 2010] [10:25:37] <mato>	you need to follow those 4 exact steps otherwise the raised rlimit setting will not propagate to your app
| [Monday 08 November 2010] [10:25:43] <mato>	if you open a new shell, it won't work
| [Monday 08 November 2010] [10:25:48] <mato>	is this clear?
| [Monday 08 November 2010] [10:26:06] 	 * pieterh is trying it, will report back asap
| [Monday 08 November 2010] [10:27:13] <pieterh>	mato: having raised the ulimit to 8192 (or any large number), the test program now exits cleanly
| [Monday 08 November 2010] [10:27:25] <pieterh>	and reports: "This system allows up to 511 sockets"
| [Monday 08 November 2010] [10:27:38] <mato>	pieterh: yes, now there is a third limit also
| [Monday 08 November 2010] [10:27:46] <cremes>	mato: results from running my test program on OSX and archlinux with the printf statements
| [Monday 08 November 2010] [10:27:49] <cremes>	https://gist.github.com/667811
| [Monday 08 November 2010] [10:27:53] <mato>	pieterh: compile time setting in 0MQ src/config.hpp
| [Monday 08 November 2010] [10:28:03] <mato>	pieterh: which happens to be set to 512
| [Monday 08 November 2010] [10:28:51] <pieterh>	was this limit introduced in 2.1.0?
| [Monday 08 November 2010] [10:29:16] <pieterh>	i assume it must have been, since previously I could open 8M sockets
| [Monday 08 November 2010] [10:29:22] <mato>	pieterh: presumably
| [Monday 08 November 2010] [10:29:48] <pieterh>	well, ok I can confirm what you've explained
| [Monday 08 November 2010] [10:30:18] <pieterh>	though the max-sockets option seems 1 off
| [Monday 08 November 2010] [10:30:27] <mato>	pieterh: dunno, that is sustrik's work
| [Monday 08 November 2010] [10:30:28] <pieterh>	- setting it to 8000 allows me to create 7999 sockets
| [Monday 08 November 2010] [10:30:53] <mato>	it's allocating resources of some kind up front, otherwise it wouldn't be a compile-time option
| [Monday 08 November 2010] [10:31:07] <mato>	cremes: ok, that output is strange
| [Monday 08 November 2010] [10:31:31] <mato>	cremes: note that the old_sndbuf/new_sndbuf values for the failing mailbox look completely bogus
| [Monday 08 November 2010] [10:31:40] <mato>	32? 16? wtf...
| [Monday 08 November 2010] [10:31:54] <cremes>	mato: are you looking at the osx or arch output?
| [Monday 08 November 2010] [10:32:17] <mato>	oh, right, sorry
| [Monday 08 November 2010] [10:32:39] <mato>	bah, let me save those gists to a file
| [Monday 08 November 2010] [10:33:32] <cremes>	i think on linux i am hitting the 512 socket limit
| [Monday 08 November 2010] [10:33:37] <cremes>	on osx, it fails long before
| [Monday 08 November 2010] [10:35:05] <mato>	cremes: hmm, the output is a bit mixed up due to stdout/stderr mixing
| [Monday 08 November 2010] [10:35:18] <cremes>	mato: yes, want me to separate them?
| [Monday 08 November 2010] [10:35:22] <mato>	cremes: are you printing the retry_nbytes case?
| [Monday 08 November 2010] [10:35:27] <mato>	cremes: i can't find it anywhere...
| [Monday 08 November 2010] [10:35:42] <mato>	cremes: just use fprintf (stderr, ...) for everything, it'll work fine
| [Monday 08 November 2010] [10:35:47] <cremes>	mato: no, you didn't mention that as being interesting
| [Monday 08 November 2010] [10:35:56] <mato>	cremes: oh, sorry, i did, you must have missed it
| [Monday 08 November 2010] [10:36:36] <mato>	16:01 < mato> cremes: and print retry_nbytes after the 2nd do loop in send(), i.e. after  line 202
| [Monday 08 November 2010] [10:36:53] <mato>	cremes: can you try that please? and set it all to use stderr?
| [Monday 08 November 2010] [10:37:04] <cremes>	ok, i'll add that one... sorry for the mixup
| [Monday 08 November 2010] [10:51:19] <cremes>	mato: osx results... https://gist.github.com/3892c9fcb0f5493f6ae8
| [Monday 08 November 2010] [10:53:51] <pieterh>	cremes, I've reported the issue https://github.com/zeromq/zeromq2/issues/issue/113
| [Monday 08 November 2010] [10:54:36] <cremes>	pieterh: thank you
| [Monday 08 November 2010] [10:58:22] <pieterh>	I'm pretty sure the limit of ~512 sockets will trip up a few existing apps
| [Monday 08 November 2010] [10:58:42] <cremes>	pieterh: i changed that limit to 10k on my linux box, reran the test and it passed
| [Monday 08 November 2010] [10:58:47] <pieterh>	yes, indeed
| [Monday 08 November 2010] [10:58:57] <cremes>	i did the same change on osx and it still fails in the same spot, same error :(
| [Monday 08 November 2010] [10:59:06] <cremes>	must be some funky osx-ism
| [Monday 08 November 2010] [10:59:14] <pieterh>	different techniques for setting per-user limits
| [Monday 08 November 2010] [10:59:26] <pieterh>	its BSD-4.3 heritage or something
| [Monday 08 November 2010] [10:59:37] <cremes>	pieterh: i bumped file descriptors per process to 25k a long time ago for mongodb on this box
| [Monday 08 November 2010] [11:00:12] <mato>	pieterh: max_sockets directly affects the number of mailbox slots
| [Monday 08 November 2010] [11:00:23] <mato>	pieterh: so the limit is set intentionally low 
| [Monday 08 November 2010] [11:00:39] <zmq_help>	hi folks - i'm trying to get zeromq ruby bindings working on Ubuntu 10.10
| [Monday 08 November 2010] [11:00:46] <pieterh>	mato: you mean as in reducing pre-allocated memory size?
| [Monday 08 November 2010] [11:00:53] <mato>	pieterh: yes
| [Monday 08 November 2010] [11:00:57] <pieterh>	is there another performance reason?
| [Monday 08 November 2010] [11:00:58] <cremes>	zmq_help: which bindings? the zmq gem or ffi-rzmq?
| [Monday 08 November 2010] [11:01:04] <pieterh>	data copying etc?
| [Monday 08 November 2010] [11:01:12] <mato>	pieterh: possibly, read the code :-)
| [Monday 08 November 2010] [11:01:13] <zmq_help>	I installed zmq
| [Monday 08 November 2010] [11:01:25] <zmq_help>	I installed zmq ruby gem
| [Monday 08 November 2010] [11:01:32] <mato>	pieterh: but in any case, the standard untuned Linux limit is 1024 fds
| [Monday 08 November 2010] [11:01:32] <cremes>	zmq_help: ok; so what seems to be the problem?
| [Monday 08 November 2010] [11:01:41] <mato>	pieterh: so there's no point in changing the default of max_sockets
| [Monday 08 November 2010] [11:01:52] <mato>	pieterh: since it'll fall over anyway
| [Monday 08 November 2010] [11:01:53] <pieterh>	mato: IMO there is
| [Monday 08 November 2010] [11:01:59] <pieterh>	it'll fall over with a normal system error
| [Monday 08 November 2010] [11:02:06] <pieterh>	that can be fixed without recompilation
| [Monday 08 November 2010] [11:02:25] <pieterh>	modifying code to change a limit is not acceptable for many processes
| [Monday 08 November 2010] [11:02:29] <pieterh>	it means requalification
| [Monday 08 November 2010] [11:02:34] <pieterh>	we've discussed this previously
| [Monday 08 November 2010] [11:02:44] <pieterh>	imagine 'large bank'
| [Monday 08 November 2010] [11:03:03] <mato>	pieterh: large bank should test damn well for such limits...
| [Monday 08 November 2010] [11:03:04] <zmq_help>	cremes: when I enter 'require "zmq"' I get this error message
| [Monday 08 November 2010] [11:03:06] <zmq_help>	LoadError: libzmq.so.0: cannot open shared object file: No such file or directory - /usr/lib/ruby/gems/1.8/gems/zmq-2.0.9/lib/zmq.so
| [Monday 08 November 2010] [11:03:15] <pieterh>	mato: that's not the point
| [Monday 08 November 2010] [11:03:30] <pieterh>	point is tuning the sw at compile time is sub-optimal
| [Monday 08 November 2010] [11:03:40] <zmq_help>	cremes: but I can see that the zmq.so file is there, and readable
| [Monday 08 November 2010] [11:03:42] <pieterh>	and it can be done better unless there is an actual cost in having a larger limit
| [Monday 08 November 2010] [11:03:57] <pieterh>	anyhow, issue is noted
| [Monday 08 November 2010] [11:04:00] <mato>	pieterh: well, don't forget there are many audiences, embedded, etc etc..
| [Monday 08 November 2010] [11:04:00] <cremes>	zmq_help: did you install the 0mq library? the gem does not include it
| [Monday 08 November 2010] [11:04:13] <cremes>	also, make sure you run ldconfig after installing the 0mq lib
| [Monday 08 November 2010] [11:04:19] <mato>	pieterh: and the limit only affects # of sockets, not # connections obviously
| [Monday 08 November 2010] [11:04:20] <cremes>	so that linux picks it up
| [Monday 08 November 2010] [11:04:28] <mato>	anyway, noted.
| [Monday 08 November 2010] [11:04:31] <pieterh>	mato: I'd suggest embedded systems are less 'typical'
| [Monday 08 November 2010] [11:04:43] <zmq_help>	cremes - yes I installed everything - i'll try the ldconfig trick now...
| [Monday 08 November 2010] [11:04:45] <pieterh>	plus 0MQ encourages use of many sockets
| [Monday 08 November 2010] [11:04:56] <mato>	it does? :-)
| [Monday 08 November 2010] [11:05:00] <pieterh>	yes
| [Monday 08 November 2010] [11:05:13] <pieterh>	typically one for each flow
| [Monday 08 November 2010] [11:05:31] <cremes>	pieterh: agreed... i sometimes need thousands for just that reason
| [Monday 08 November 2010] [11:05:31] <pieterh>	and if you want any custom routing that means several sockets per peer
| [Monday 08 November 2010] [11:05:35] <zmq_help>	cremes: THANKS!  the ldconfig trick did the job
| [Monday 08 November 2010] [11:05:37] <pieterh>	as you well know, mato :-)
| [Monday 08 November 2010] [11:05:50] <cremes>	zmq_help: remember to help someone else in channel when you get a chance ;)
| [Monday 08 November 2010] [11:06:03] <zmq_help>	:-) will do thanks
| [Monday 08 November 2010] [11:06:33] <zmq_help>	cremes: where should I give documentation feedback re: the ldconfig trick ??
| [Monday 08 November 2010] [11:06:35] <cremes>	pieterh: does imatix have an osx box for testing?
| [Monday 08 November 2010] [11:06:46] <cremes>	zmq_help: that trick is listed in the FAQ i think
| [Monday 08 November 2010] [11:06:48] <pieterh>	cremes: yes, sure
| [Monday 08 November 2010] [11:06:52] <pieterh>	try this: sudo echo limit maxfiles 1000000 1000000 > /etc/launchd.conf
| [Monday 08 November 2010] [11:06:58] <cremes>	otherwise, feel free to join the wiki and modify it on your own
| [Monday 08 November 2010] [11:07:00] <zmq_help>	cremes: ok thanks - 
| [Monday 08 November 2010] [11:07:14] <pieterh>	and then launchctl limit maxfiles 1000000 1000000
| [Monday 08 November 2010] [11:07:38] <cremes>	pieterh: i did that when i bumped my limits to 25k... here are the current contents:  limit maxfiles 25000 100000
| [Monday 08 November 2010] [11:07:40] <pieterh>	cremes, I'm just googling random pages for ""too many open files" OSX"
| [Monday 08 November 2010] [11:07:44] <pieterh>	hmm
| [Monday 08 November 2010] [11:07:54] <cremes>	ulimit -a agrees that it is 25k
| [Monday 08 November 2010] [11:08:01] <pieterh>	and you tuned 0MQ to 10k sockets?
| [Monday 08 November 2010] [11:08:04] <cremes>	yes
| [Monday 08 November 2010] [11:08:08] <pieterh>	and you still get an abort at 508 sockets?
| [Monday 08 November 2010] [11:09:14] <pieterh>	cremes, see http://artur.hefczyc.net/node/27
| [Monday 08 November 2010] [11:09:23] <mato>	cremes: hmph, those sndbuf numbers from osx make no sense
| [Monday 08 November 2010] [11:09:39] <mato>	cremes: if it really was 16/32 bytes, it'd fall over immediately
| [Monday 08 November 2010] [11:10:36] <mato>	cremes: i'd need access to an OSX box to figure out what is going on
| [Monday 08 November 2010] [11:10:53] <cremes>	mato: i can give you an account on mine if you'd like
| [Monday 08 November 2010] [11:10:53] <pieterh>	mato: I can bring you my MacBook when I manage to make it to BA
| [Monday 08 November 2010] [11:11:25] <mato>	cremes: that would be great, but honestly i don't have time this week to look at it seriously
| [Monday 08 November 2010] [11:11:51] <cremes>	mato: ok
| [Monday 08 November 2010] [11:12:01] <mato>	cremes: upcoming deadlines, too much to do, sorry...
| [Monday 08 November 2010] [11:12:12] <cremes>	i understand... no worries
| [Monday 08 November 2010] [11:15:35] <twomashi1>	How can I process all outstanding messages in a socket and stop recieving new ones?
| [Monday 08 November 2010] [11:19:00] <guido_g>	you can't
| [Monday 08 November 2010] [11:20:18] <guido_g>	you can receive all messages in a loop, but you can't tell the mq socket to stop accepting more/new messages
| [Monday 08 November 2010] [11:23:51] <Steve-o>	twomashi1: what is the logical requirement from this scenario?  clean FT fail over?
| [Monday 08 November 2010] [11:29:32] <twomashi1>	Steve-o: Removing a worker from a worker pool 
| [Monday 08 November 2010] [11:30:17] <Guthur>	Does 0MQ aim to provide more devices in the future?
| [Monday 08 November 2010] [11:34:30] <mikko>	Guthur: i would imagine that if certain devices are used in large amount of projects they could be incorporated into the core
| [Monday 08 November 2010] [11:34:43] <mikko>	but not sure whether adding new devices is the biggest priority
| [Monday 08 November 2010] [11:35:37] <mikko>	Guthur: are there specific devices that you are after?
| [Monday 08 November 2010] [11:36:45] <Guthur>	mikko: Not really just interested is all, if I could find examples of what would be beneficial I would maybe even have a stab at implementing
| [Monday 08 November 2010] [11:41:55] <twomashi1>	guido_g: I wanted to have a worker which would process n messages and then die
| [Monday 08 November 2010] [11:42:11] <twomashi1>	but it sounds like theres no way to stop the worker recieving more messages
| [Monday 08 November 2010] [11:42:25] <guido_g>	as i already said
| [Monday 08 November 2010] [11:42:42] <twomashi1>	so this pattern wont work
| [Monday 08 November 2010] [11:42:44] <twomashi1>	thanks
| [Monday 08 November 2010] [11:47:29] <Steve-o>	twomashi1: I think there are few implementations of worker pools already, e.g. http://kfsone.wordpress.com/2010/07/21/asyncworker-parallelism-with-zeromq/
| [Monday 08 November 2010] [11:51:03] <guido_g>	doesn't handle the dynamic shutdown of one worker though
| [Monday 08 November 2010] [12:04:50] <ngerakines>	sup
| [Monday 08 November 2010] [12:17:53] <cremes>	found the trick for osx... it has some sysctl settings that it shares with freebsd
| [Monday 08 November 2010] [12:18:11] <cremes>	for localhost/loopback connections, there are separate send/recv buffers allocated
| [Monday 08 November 2010] [12:18:13] <cremes>	net.local.stream.sendspace=82320
| [Monday 08 November 2010] [12:18:14] <cremes>	net.local.stream.recvspace=82320
| [Monday 08 November 2010] [12:18:19] <cremes>	or whatever value you want
| [Monday 08 November 2010] [12:18:25] <cremes>	i'll add this to the FAQ
| [Monday 08 November 2010] [12:18:53] <mato>	cremes: so upping those values makes the code work for you?
| [Monday 08 November 2010] [12:19:17] <mato>	cremes: that would imply that at least for some sockets, the default on OSX is ridiculously low
| [Monday 08 November 2010] [12:19:17] <cremes>	yes, because it avoids the recovery code that tries to adjust SO_SNDBUF
| [Monday 08 November 2010] [12:19:28] <mato>	the thing is, the recovery code works
| [Monday 08 November 2010] [12:19:40] <mato>	as long as the OS comes back with a sane sndbuf in the getsockopt
| [Monday 08 November 2010] [12:19:44] <cremes>	i believe you, but SO_SNDBUF isn't returning the right vals
| [Monday 08 November 2010] [12:19:48] <cremes>	and i don't know why
| [Monday 08 November 2010] [12:20:02] <cremes>	maybe it is returning kbytes instead of bytes
| [Monday 08 November 2010] [12:20:04] <mato>	that is indeed what it looks like
| [Monday 08 November 2010] [12:20:25] <mato>	cremes: could you please somehow summarize what we've found and reply to the thread on the ML so that we don't lose it?
| [Monday 08 November 2010] [12:20:32] <cremes>	absolutely
| [Monday 08 November 2010] [12:21:01] <mato>	cremes: it's plausible that even just setting a large-ish value at mailbox socketpair creation time would make the problem go away
| [Monday 08 November 2010] [12:21:08] <mato>	needs more investigation...
| [Monday 08 November 2010] [12:21:28] <cremes>	right... i'll respond to the ML with a few details; i'll also update pieter's issue
| [Monday 08 November 2010] [12:21:46] <mato>	thx
| [Monday 08 November 2010] [12:49:05] <cremes>	hmmm, what would you guess is happening if i get "Too many open files: rc == 0 (mailbox.cpp:431)" ?
| [Monday 08 November 2010] [12:49:32] <cremes>	this is with the patched mailbox.cpp
| [Monday 08 November 2010] [12:51:50] <mato>	precisely what it says :)
| [Monday 08 November 2010] [12:52:07] <cremes>	heh
| [Monday 08 November 2010] [12:53:00] <cremes>	i must not have raised my limits high enough and now i'm running out of another resource
| [Monday 08 November 2010] [13:10:01] <ngerakines>	hey folks, I've got a c++ app that uses zmq with threads and I'm not sure about the proper way of doing something in particular:
| [Monday 08 November 2010] [13:10:57] <ngerakines>	for these threads, they bind to a given socket and wait for incoming messages, however when I want to shutdown these threads I'm not finding through the docs the best way to my socket_in.recv/1 to stop blocking on input
| [Monday 08 November 2010] [13:11:10] <ngerakines>	how should I go about this?
| [Monday 08 November 2010] [13:12:32] <twomashi1>	ngerakines: i have the same issue
| [Monday 08 November 2010] [13:13:05] <twomashi1>	im told theres no way to get zmq to stop recieving messages so you can process outstanding ones
| [Monday 08 November 2010] [13:13:37] <nettok>	ngerakines: I would like to know about that too
| [Monday 08 November 2010] [13:15:58] <nettok>	ngerakines: maybe registering a signal handler and then trigger the signal from another thread or process, something like that?
| [Monday 08 November 2010] [13:16:24] <ngerakines>	hmm
| [Monday 08 November 2010] [13:16:47] <nettok>	Or making read non-blocking
| [Monday 08 November 2010] [13:16:49] <twomashi1>	oh wait... sorry different issue
| [Monday 08 November 2010] [13:16:56] <twomashi1>	use poll?
| [Monday 08 November 2010] [13:17:03] <ngerakines>	yeah, looking into poll
| [Monday 08 November 2010] [13:18:53] <guido_g>	ngerakines: simply send a quit message (can be of length 0)
| [Monday 08 November 2010] [13:19:29] <ngerakines>	ok, was looking for a way to effectively halt all zmq communication once stop was initiated, but thanks
| [Monday 08 November 2010] [13:20:00] <guido_g>	then just terminate the context
| [Monday 08 November 2010] [13:20:22] <guido_g>	that will close all mq sockets and stop all mq related activities
| [Monday 08 November 2010] [13:22:30] <nettok>	guido_g: thanks!
| [Monday 08 November 2010] [13:23:29] <ngerakines>	guido_g: and in cases where i've got a pub/sub client, use poll?
| [Monday 08 November 2010] [13:24:05] <guido_g>	ngerakines: can't follow you, sorry
| [Monday 08 November 2010] [13:24:33] <ngerakines>	I've got a pub/sub subscriber with a run-loop that uses socket_t.recv(..)
| [Monday 08 November 2010] [13:24:41] <guido_g>	so?
| [Monday 08 November 2010] [13:24:46] <ngerakines>	instead of recv, should I be using poll to close out cleanly?
| [Monday 08 November 2010] [13:24:53] <guido_g>	why?
| [Monday 08 November 2010] [13:25:12] <ngerakines>	Is there a way to send it a kill message like above given that it isn't binding?
| [Monday 08 November 2010] [13:25:58] <guido_g>	wht isn't binding? w/o a bound socket you can't receive any messages
| [Monday 08 November 2010] [13:26:38] <guido_g>	so if you have a sub socket, it'll just receive the message
| [Monday 08 November 2010] [13:27:10] <ngerakines>	because it is creating a socket with ZMQ_SUB ?
| [Monday 08 November 2010] [13:27:25] <ngerakines>	with connect ?
| [Monday 08 November 2010] [13:27:38] <ngerakines>	socket_t.connect(...) as opposed to socket_t.bind(...)
| [Monday 08 November 2010] [13:28:32] <guido_g>	there is no difference between the connect side and the bind side in this case
| [Monday 08 November 2010] [13:28:52] <guido_g>	this is for sure mentioned in the guide somewhere
| [Monday 08 November 2010] [13:56:32] <gandhijee>	hey guys, is there an ubuntu/debian package of zeromq anywhere?
| [Monday 08 November 2010] [13:56:41] <pieterh>	gandhijee, I believe there is, somewhere
| [Monday 08 November 2010] [13:57:03] <gandhijee>	happen to have an idea where somewhere might be?
| [Monday 08 November 2010] [13:57:10] <pieterh>	Do a google for "debian package zeromq"
| [Monday 08 November 2010] [13:57:25] <pieterh>	http://packages.debian.org/source/sid/zeromq
| [Monday 08 November 2010] [13:58:12] <twomashi1>	pieterh: do you know how a process using zeromq could stop recieving messages and process it's outstanding messages? (say to remove itself from a worker pool)
| [Monday 08 November 2010] [13:58:46] <gandhijee>	yeah i had found that one, its 2.0.6, the other machines are all on 2.10
| [Monday 08 November 2010] [13:58:50] <pieterh>	twomashi1, let me think about it... I just got back and am reading the traffic here
| [Monday 08 November 2010] [13:59:00] <twomashi1>	ok cool
| [Monday 08 November 2010] [13:59:01] <twomashi1>	thanks
| [Monday 08 November 2010] [13:59:07] <pieterh>	gandhijee, right... but it's pretty simple to build from source anyhow
| [Monday 08 November 2010] [13:59:12] <gandhijee>	i don't want to have to deal with any issues because 1 is newer than the other
| [Monday 08 November 2010] [13:59:31] <gandhijee>	yeah, but i wanted to be lazy and not build the .deb
| [Monday 08 November 2010] [13:59:44] <gandhijee>	i have to put it on 3 more machines, 1 x86_64 and 2 atoms
| [Monday 08 November 2010] [13:59:50] <pieterh>	gandhijee, download tarball, build, it's really simple
| [Monday 08 November 2010] [14:00:26] <gandhijee>	yes i know, like i said, i wanted to be lazy and not build the deb, because i have to get it to 3 more machines,
| [Monday 08 November 2010] [14:00:35] <pieterh>	you can make a simple script that does it from wget to 'sudo make install; ldconfig'
| [Monday 08 November 2010] [14:00:43] <gandhijee>	building the deb is just a cpl extra steps
| [Monday 08 November 2010] [14:00:48] <pieterh>	sure
| [Monday 08 November 2010] [14:01:04] <pieterh>	being lazy is good if you use that to create something
| [Monday 08 November 2010] [14:01:12] <pieterh>	if it's just to avoid work... well... :-)
| [Monday 08 November 2010] [14:01:31] <pieterh>	twomashi1, can you provide more background info?
| [Monday 08 November 2010] [14:01:52] <pieterh>	do you want flow control?
| [Monday 08 November 2010] [14:03:43] <twomashi1>	pieterh: I want to use a pool of PHP workers to process data, this is existing PHP code adapted to read messages from a ZMQ socket. I dont want them to live indefinitely because PHP is prone to memory leakes, so they must exit after processing n requests. Zeromq will fetch more messages than I need tho, so I want some way to stop ZMQ prefetching messages and process the messages already in memory.
| [Monday 08 November 2010] [14:04:01] <pieterh>	right...
| [Monday 08 November 2010] [14:04:14] <pieterh>	I can think of a few ways
| [Monday 08 November 2010] [14:04:27] <pieterh>	here is the most brutal
| [Monday 08 November 2010] [14:04:42] <pieterh>	you batch the messages together, using multipart and some delimiters
| [Monday 08 November 2010] [14:05:00] <pieterh>	so that you actually send your whole batch, say 100 messages, as one 0MQ message
| [Monday 08 November 2010] [14:05:09] <pieterh>	you then use the LRU routing technique from the Guide ch3
| [Monday 08 November 2010] [14:05:17] <pieterh>	where the worker signals 'ready' and then gets a job
| [Monday 08 November 2010] [14:05:36] <pieterh>	when the worker has processed its job it just terminates
| [Monday 08 November 2010] [14:05:44] <pieterh>	it won't signal 'ready' again, so won't get another batch
| [Monday 08 November 2010] [14:05:54] <pieterh>	you control the batch size explicitly at the sender side
| [Monday 08 November 2010] [14:06:01] <twomashi1>	ah, with LRU the worker must signal to get a job?
| [Monday 08 November 2010] [14:06:01] <pieterh>	now the problems with this:
| [Monday 08 November 2010] [14:06:04] <pieterh>	yes
| [Monday 08 November 2010] [14:06:10] <pieterh>	it's a nice model except it's chatty
| [Monday 08 November 2010] [14:06:22] <twomashi1>	chatty is fine, it must be safe. 
| [Monday 08 November 2010] [14:06:26] <pieterh>	so if you have many small jobs the to and fro will cost too much
| [Monday 08 November 2010] [14:06:37] <pieterh>	well, study the lruqueue example
| [Monday 08 November 2010] [14:06:48] <pieterh>	you can probably use that as a device in front of your existing client/s
| [Monday 08 November 2010] [14:06:56] <pieterh>	with some small mods it'll do what you want
| [Monday 08 November 2010] [14:07:04] <twomashi1>	that could work because the job server will be on the same machine.
| [Monday 08 November 2010] [14:07:07] <pieterh>	sure
| [Monday 08 November 2010] [14:07:12] <twomashi1>	so I dont think chatty is an issue
| [Monday 08 November 2010] [14:07:29] <pieterh>	so use the LRU device and then in the workers, die after doing X jobs
| [Monday 08 November 2010] [14:07:37] <pieterh>	put $5 in the can on the way out :-)
| [Monday 08 November 2010] [14:07:48] <twomashi1>	hehe
| [Monday 08 November 2010] [14:08:27] <twomashi1>	Ok, and do you think that in some future there will be a way to support this usage case by instructing the context to stop recieving for a socket, or something like that?
| [Monday 08 November 2010] [14:08:41] <pieterh>	well...
| [Monday 08 November 2010] [14:08:52] <pieterh>	i don't think it has to be built in
| [Monday 08 November 2010] [14:08:58] <twomashi1>	i imagine that if it doesnt go against the goals and policies of the project it could happen, if someone put the time in.
| [Monday 08 November 2010] [14:08:58] <pieterh>	it works very nicely at the level it's at now
| [Monday 08 November 2010] [14:09:22] <pieterh>	to answer that in technical detail...
| [Monday 08 November 2010] [14:09:34] <pieterh>	if you want to regulate how much the sender sends
| [Monday 08 November 2010] [14:09:42] <pieterh>	then you must send information back explicitly to synchronize it
| [Monday 08 November 2010] [14:10:09] <pieterh>	you could call this an ack windw
| [Monday 08 November 2010] [14:10:13] <pieterh>	ack window
| [Monday 08 November 2010] [14:10:23] <pieterh>	it only makes sense in an asynchronous request-reply model
| [Monday 08 November 2010] [14:10:40] <pieterh>	so yes, it *might* be added to the XREP socket
| [Monday 08 November 2010] [14:11:08] <twomashi1>	I see what you mean... the effect can be reproduced using the currently available facilities
| [Monday 08 November 2010] [14:11:49] <twomashi1>	thanks for your help!
| [Monday 08 November 2010] [14:18:41] <cremes>	OSX sysctl is very odd... see my update on the ML
| [Monday 08 November 2010] [14:22:36] <mato>	gandhijee: there is a Debian package of ZeroMQ 2.0.10, I maintain it
| [Monday 08 November 2010] [14:22:42] <mato>	gandhijee: it's in Debian unstable
| [Monday 08 November 2010] [14:22:46] <gandhijee>	sweet!!
| [Monday 08 November 2010] [15:25:38] <gandhijee>	how do i have zeromq listen on a spec interface?
| [Monday 08 November 2010] [15:25:54] <gandhijee>	right now i have 2 in the machine that is a client, and it doesn't seem to get messages over the netowrk for some reason
| [Monday 08 November 2010] [15:45:57] <Guthur>	gandhijee, Spec Interface?
| [Monday 08 November 2010] [15:46:11] <Guthur>	maybe you want to check out IO polling
| [Monday 08 November 2010] [15:46:16] <gandhijee>	its ok i figured it out
| [Monday 08 November 2010] [15:46:29] <gandhijee>	it was something super silly, its been a long day
| [Monday 08 November 2010] [15:46:53] <Guthur>	hehe no bother, we all have those days
| [Monday 08 November 2010] [16:11:43] <Ben__>	hi all - I have a question about using sockets from different threads in C++. I'm on the latest code from the git repository master branch. The scenario is that I've created a socket in one thread, but I use it from another thread. Only one thread ever uses the socket at a time. I thought this was possible with the latest code, but I am not seeing any messages come into my test receiver on the other end.
| [Monday 08 November 2010] [16:12:31] <Ben__>	another question - my test receiver is written in Python and is on 2.0.8. Do I need to upgrade this to 2.1 as well in order to get it to work?
| [Monday 08 November 2010] [16:15:32] <ngerakines>	from my experience its a bad idea and leads to unexpected results
| [Monday 08 November 2010] [16:15:46] <Ben__>	which part? mixing zmq versions or migrated between threads?
| [Monday 08 November 2010] [16:15:47] <ngerakines>	I think the docs say in bold that sockets should never be shared across threads
| [Monday 08 November 2010] [16:15:54] <Ben__>	it does for 2.0
| [Monday 08 November 2010] [16:16:01] <Ben__>	but in 2.1 there is a statement saying that this is now legal
| [Monday 08 November 2010] [16:16:11] <Ben__>	I know it isn't released yet - I'm doing this out of git
| [Monday 08 November 2010] [16:16:21] <Ben__>	it may just be that it isn't ready
| [Monday 08 November 2010] [16:16:36] <ngerakines>	I don't know then, sorry
| [Monday 08 November 2010] [16:23:20] <Guthur>	is there really a need for the wuserver example to be binding to ipc
| [Monday 08 November 2010] [16:23:38] <Guthur>	It's not used, and it just makes the example incompatible with windows
| [Monday 08 November 2010] [16:25:54] <Ben__>	if anyone is curious about my earlier question - moving my test client to 2.1 from 2.0.8 did indeed fix the problem.
| [Monday 08 November 2010] [17:03:53] <mikko>	sustrik: how do i recognise you?
| [Monday 08 November 2010] [17:04:10] <sustrik>	mikko: i've sent you my number
| [Monday 08 November 2010] [17:04:14] <sustrik>	have you got it?
| [Monday 08 November 2010] [17:04:32] <mikko>	yes
| [Monday 08 November 2010] [17:04:50] <sustrik>	let me find some picture...
| [Monday 08 November 2010] [17:05:06] <mikko>	http://farm4.static.flickr.com/3297/3626630182_006c6ba2c0.jpg
| [Monday 08 November 2010] [17:05:08] <mikko>	thats me
| [Monday 08 November 2010] [17:05:15] <mikko>	i dont have the beard anymore, just the moustache
| [Monday 08 November 2010] [17:05:27] <sustrik>	that's me:
| [Monday 08 November 2010] [17:05:28] <sustrik>	http://www.facebook.com/#!/photo.php?fbid=1403475059607&set=t.1233485121
| [Monday 08 November 2010] [17:05:33] <sustrik>	guy with the tuba
| [Monday 08 November 2010] [17:05:38] <mikko>	ok
| [Monday 08 November 2010] [17:06:17] <mikko>	and it's not that large pub
| [Monday 08 November 2010] [17:06:47] <sustrik>	ok
| [Monday 08 November 2010] [17:07:06] <sustrik>	ah, jon dyte mentioned he's going to arrive
| [Monday 08 November 2010] [17:19:01] <pieterh>	sustrik: you take a tube to all 0MQ meetups?
| [Monday 08 November 2010] [17:19:07] <pieterh>	*tuba
| [Monday 08 November 2010] [17:19:12] <pieterh>	sorry, it's been a long day :-)
| [Monday 08 November 2010] [17:38:47] <lestrrat>	is fd_t only available in C++ land? (for getsockopt( ... ZMQ_FD ))
| [Monday 08 November 2010] [17:51:28] <Guthur>	sustrik, I pushed the clrzmq2 code to the repo
| [Monday 08 November 2010] [17:53:29] <Guthur>	I kept the same .NET assembly name, but bumped the version up to 2.0.0.0
| [Monday 08 November 2010] [17:53:29] <Guthur>	It's easy for people to set there required version in MSVC, and MonoDevelop
| [Monday 08 November 2010] [17:53:29] <Guthur>	their*
| [Monday 08 November 2010] [19:04:27] Notice	-NickServ- This nickname is registered. Please choose a different nickname, or identify via /msg NickServ identify <password>.
| [Monday 08 November 2010] [19:04:27] Notice	-NickServ- You are now identified for travlr.
| [Monday 08 November 2010] [19:04:27] CTCP	Received Version request from frigg.
| [Monday 08 November 2010] [22:03:32] <Led_Zeppelin>	hello.
| [Monday 08 November 2010] [22:03:43] <Led_Zeppelin>	Is it possible to have a UDP socket with 0mq?
| [Monday 08 November 2010] [22:14:00] <gandhijee>	hey, what would the socket be to only send msgs to a server?
| [Monday 08 November 2010] [22:14:18] <gandhijee>	and i guess the server would have to open in rec only mode?
| [Tuesday 09 November 2010] [03:49:43] <mikko>	gandhijee: PUSH/PULL, PUB/SUB
| [Tuesday 09 November 2010] [04:12:55] <mrshpot>	hi
| [Tuesday 09 November 2010] [04:13:17] <mrshpot>	is it OK to pass sockets between threads in ZeroMQ 2.1.0-git?
| [Tuesday 09 November 2010] [04:16:06] <Guthur>	mrshpot: AFAIK sharing sockets between threads is not supported
| [Tuesday 09 November 2010] [04:16:56] <mrshpot>	thanks
| [Tuesday 09 November 2010] [04:17:09] <guido_g>	in 2.1.x you can move a socket from one thread to another
| [Tuesday 09 November 2010] [04:17:20] <Guthur>	oh, sorry my bad
| [Tuesday 09 November 2010] [04:17:29] <guido_g>	*shared* use of a socket is still not supported
| [Tuesday 09 November 2010] [04:17:55] <mrshpot>	I want to have two threads: one that is receiving, and another one that is sending
| [Tuesday 09 November 2010] [04:18:09] <mrshpot>	so I can't do that
| [Tuesday 09 November 2010] [04:18:22] <guido_g>	right
| [Tuesday 09 November 2010] [04:18:38] <mrshpot>	thank you :)
| [Tuesday 09 November 2010] [04:18:39] <guido_g>	stupid idea anyway, because mq uses one io thread itself
| [Tuesday 09 November 2010] [04:19:37] <mikko>	mrshpot: what kind of situation would you use that design for?
| [Tuesday 09 November 2010] [04:19:44] <mikko>	one thread receiving and one sending
| [Tuesday 09 November 2010] [04:19:54] <mikko>	on same socket that is
| [Tuesday 09 November 2010] [04:20:18] <mrshpot>	there is a worker performing a two-step computation
| [Tuesday 09 November 2010] [04:20:45] <mrshpot>	and a "receive; calculate; send" pattern makes it stay idle for quite a time
| [Tuesday 09 November 2010] [04:21:20] <mrshpot>	it would be more efficient to have a request queue and a response queue
| [Tuesday 09 November 2010] [04:21:33] <mikko>	why don't you do recv/send in one thread and use inproc to hand work to worker threads?
| [Tuesday 09 November 2010] [04:22:49] <guido_g>	receive / calculate / send doesn't sound like the thread has not enough to do
| [Tuesday 09 November 2010] [04:23:16] <guido_g>	the sending is very fast, because it _simply_ pushes the data to the io thread internally
| [Tuesday 09 November 2010] [04:23:44] <guido_g>	so after sending thread would get the next message quite fast
| [Tuesday 09 November 2010] [04:24:35] <mrshpot>	I guess I'll go with single-threaded send/recv, then
| [Tuesday 09 November 2010] [04:24:52] <guido_g>	right
| [Tuesday 09 November 2010] [04:25:10] <guido_g>	allways *try* the simple things first
| [Tuesday 09 November 2010] [04:25:20] <mrshpot>	:-)
| [Tuesday 09 November 2010] [05:13:57] <Guthur>	sustrik, are you maintain the erlang binding?
| [Tuesday 09 November 2010] [06:11:02] <pieterh>	Guthur, the maintainer should be mentioned on the binding page
| [Tuesday 09 November 2010] [06:11:38] <pieterh>	Serge Aleynikov and Dhammika Pathirana, it says
| [Tuesday 09 November 2010] [07:02:36] <Guthur>	pieterh: Ah ok, cheers
| [Tuesday 09 November 2010] [08:54:13] <Guthur>	is ZFL at an early stage of development?
| [Tuesday 09 November 2010] [08:54:39] <Guthur>	It doesn't seem to be very well advertised
| [Tuesday 09 November 2010] [08:57:13] <Tester>	hey guys, I want to build a tcp server with 0mq, that would connect to non-0mq clients
| [Tuesday 09 November 2010] [08:57:39] <Tester>	is there any problem combining 0mq and non-0mq sockets?
| [Tuesday 09 November 2010] [08:57:47] <mikko>	Tester: would your clients speak 0mq wire protocol?
| [Tuesday 09 November 2010] [08:57:58] <Tester>	no
| [Tuesday 09 November 2010] [08:58:06] <Tester>	plain tcp
| [Tuesday 09 November 2010] [08:58:07] <mikko>	then they couldn't really talk with 0mq
| [Tuesday 09 November 2010] [08:59:01] <Tester>	I have control over hte server, not the clients... that's the problem
| [Tuesday 09 November 2010] [08:59:07] <mikko>	as zeromq has a wire protocol for frames
| [Tuesday 09 November 2010] [08:59:45] <Tester>	I see
| [Tuesday 09 November 2010] [08:59:49] <guido_g>	there is no problem in using os level sockets in parallel w/ mq sockets
| [Tuesday 09 November 2010] [09:00:45] <guido_g>	you can even use them in the same event loop because mq poll can handle normal (os level) sockets
| [Tuesday 09 November 2010] [09:01:33] <guido_g>	so your clients can connect via tcp using their protocol and you can use mq sockets for inter-server communication
| [Tuesday 09 November 2010] [09:03:09] <Tester>	I see. My intention was to communicate directly to the clientes
| [Tuesday 09 November 2010] [09:03:13] <Tester>	thanks guys
| [Tuesday 09 November 2010] [09:03:35] <guido_g>	then the clients need to use mq as well, as mikko said
| [Tuesday 09 November 2010] [11:06:55] <Steve-o>	so who has any experience with IOCP?
| [Tuesday 09 November 2010] [11:10:31] <mikko>	Steve-o: i am getting build errors (with ICC) when building zeromq2 --with-pgm
| [Tuesday 09 November 2010] [11:10:39] <Steve-o>	The only best practices I can find is setting SO_SNDBUF to 0 and queuing up multiple sends, but for receive you must not set SO_RCVBUF to zero and you only need one pending recv
| [Tuesday 09 November 2010] [11:11:00] <Steve-o>	mikko:  ok, I think I sent a list of required changes to the list already?
| [Tuesday 09 November 2010] [11:11:14] <mikko>	Steve-o: i might've missed that
| [Tuesday 09 November 2010] [11:11:19] <mikko>	let me see
| [Tuesday 09 November 2010] [11:11:52] <Steve-o>	There's no Autoconf for PGM so it only has support for Linux & MinGW32
| [Tuesday 09 November 2010] [11:12:24] <Steve-o>	you want the changes listed in the intelc build environment here, http://code.google.com/p/openpgm/source/browse/trunk/openpgm/pgm/SConstruct.097.intelc
| [Tuesday 09 November 2010] [11:13:29] <mikko>	i think the build env itself works ok
| [Tuesday 09 November 2010] [11:13:48] <mikko>	i keep getting error on line for (unsigned i; ...
| [Tuesday 09 November 2010] [11:14:03] <mikko>	unsigned i = 0
| [Tuesday 09 November 2010] [11:14:25] <mikko>	i thought that is legal in C++ but not in C
| [Tuesday 09 November 2010] [11:14:41] <Steve-o>	legal for C99
| [Tuesday 09 November 2010] [11:14:58] <Steve-o>	hence you need -std=c99 flag
| [Tuesday 09 November 2010] [11:16:16] <Steve-o>	I think you only need to add the flags -std=c99 -D_XOPEN_SOURCE=600 -D_BSD_SOURCE -gcc-version=420
| [Tuesday 09 November 2010] [11:16:45] <Steve-o>	I'm off house hunting be back later.
| [Tuesday 09 November 2010] [11:17:22] <mikko>	-std=gnu99 at the moment
| [Tuesday 09 November 2010] [11:17:42] <mikko>	seems like icc barfs with -std=gnu99 but works with -std=c99
| [Tuesday 09 November 2010] [13:29:47] <Steve-o>	mikko: also of note is that icc yields worse performance than gcc for PGM, so ideally you build nodist-libpgm with gcc and the rest of zeromq with icc
| [Tuesday 09 November 2010] [14:05:31] <mikko>	steve, havent got so fine-grained daily builds yet
| [Tuesday 09 November 2010] [14:06:22] <mikko>	but think im gonna ahck at this at some point
| [Tuesday 09 November 2010] [14:07:52] <Steve-o>	I wish there were better solutions but some platforms I cannot reliably detect features programmatically.
| [Tuesday 09 November 2010] [14:08:03] <zomg>	mikko: out of curiosity, you using zmq with PHP or something else?
| [Tuesday 09 November 2010] [16:16:10] <Guthur>	clrzmq2 actually works on linux out of the box
| [Tuesday 09 November 2010] [16:16:16] <Guthur>	I'm well chuffed
| [Tuesday 09 November 2010] [17:58:48] <mcr19>	what is the preferred site to upload sample code for reference on zeromq-dev?
| [Tuesday 09 November 2010] [18:26:54] <kisielk>	mcr19: probably github?
| [Tuesday 09 November 2010] [19:02:47] <Guest37325>	Hi all. I am having trouble installing pyzmq on windows. When running setup.py install I get error: Cython-generated file 'zmq\core\constants.c' not found. Any ideas?
| [Tuesday 09 November 2010] [19:10:13] <Guthur>	Guest37325, If you don't get an answer here you could try the mailing list
| [Wednesday 10 November 2010] [03:38:24] <kyuss>	Morning.
| [Wednesday 10 November 2010] [04:32:02] <mikko>	morning
| [Wednesday 10 November 2010] [04:49:13] <mikko>	zomg: to answer your question from yesterday, mainly with C
| [Wednesday 10 November 2010] [06:47:25] <vini>	hello
| [Wednesday 10 November 2010] [06:48:02] <vini>	Anyone had problems with Windows Server 2008? (not R2)
| [Wednesday 10 November 2010] [06:48:55] <vini>	The ZeroMQ for me is very slow
| [Wednesday 10 November 2010] [11:43:02] <dv_>	hello
| [Wednesday 10 November 2010] [11:43:27] <dv_>	can i use pub/sub with multiple subscribers and ipc?
| [Wednesday 10 November 2010] [11:44:04] <dv_>	I tried to bind to the ipc address twice, but it doesnt work as expected
| [Wednesday 10 November 2010] [11:45:09] <guido_g>	what does "it doesnt work as expected" mean?
| [Wednesday 10 November 2010] [11:45:26] <dv_>	well, if I start the program twice, the two instances dont get messages from each other
| [Wednesday 10 November 2010] [11:45:35] <dv_>	only from themselves
| [Wednesday 10 November 2010] [11:45:43] <dv_>	as if I was using inproc instead of ipc
| [Wednesday 10 November 2010] [11:46:36] <guido_g>	put the programs and their paramters in a paste-bin, please
| [Wednesday 10 November 2010] [11:48:10] <dv_>	oh hold on
| [Wednesday 10 November 2010] [11:48:12] <dv_>	i just noticed
| [Wednesday 10 November 2010] [11:48:24] <guido_g>	yes?
| [Wednesday 10 November 2010] [11:48:25] <dv_>	I bind to the same address twice
| [Wednesday 10 November 2010] [11:48:41] <dv_>	doesnt work with tcp of course, and I presume it wont work with ipc either, right?
| [Wednesday 10 November 2010] [11:49:22] <guido_g>	good question
| [Wednesday 10 November 2010] [11:54:02] <guido_g>	yeah, 2 binds are not allowed it seems
| [Wednesday 10 November 2010] [12:05:27] <dv_>	ok, so i was trying to write a chat program, just to test out zeromq
| [Wednesday 10 November 2010] [12:05:34] <dv_>	using pub-sub
| [Wednesday 10 November 2010] [12:05:52] <dv_>	multicasting for inter-host communication, and ipc for chat programs that run on the same host
| [Wednesday 10 November 2010] [12:06:12] <dv_>	would you also use epgm for chatting between hosts and ipc for chats in the same host?
| [Wednesday 10 November 2010] [12:11:10] <guido_g>	depends on the use-case
| [Wednesday 10 November 2010] [12:13:16] <dv_>	hm. i am tring to do this serverless.
| [Wednesday 10 November 2010] [12:14:25] <dv_>	guido_g: what other info is necessary?
| [Wednesday 10 November 2010] [12:14:41] <guido_g>	for what?
| [Wednesday 10 November 2010] [12:14:46] <dv_>	<guido_g> depends on the use-case
| [Wednesday 10 November 2010] [12:14:50] <guido_g>	yes
| [Wednesday 10 November 2010] [12:14:52] <dv_>	isnt what I write a use case?
| [Wednesday 10 November 2010] [12:15:02] <guido_g>	no really
| [Wednesday 10 November 2010] [12:15:04] <guido_g>	*not
| [Wednesday 10 November 2010] [12:18:34] <guido_g>	youc could simply use epgm for all participants, i can't see a benefit in using ipc here
| [Wednesday 10 November 2010] [12:18:56] <dv_>	you cant use epgm for communicating on the same host
| [Wednesday 10 November 2010] [12:19:09] <dv_>	well, you can, but IIRC it requires the multicast loopback hack,
| [Wednesday 10 November 2010] [12:19:13] <dv_>	which is strongly discouraged
| [Wednesday 10 November 2010] [12:19:37] <guido_g>	hack? it's a socket option
| [Wednesday 10 November 2010] [12:21:06] <dv_>	i had a discussion about this yesterday I think
| [Wednesday 10 November 2010] [12:21:09] <guido_g>	or what do you mean?
| [Wednesday 10 November 2010] [12:21:34] <dv_>	it is recommendeed to set ZMQ_MCAST_LOOP to 0,
| [Wednesday 10 November 2010] [12:21:35] <guido_g>	do you men the loopback network device?
| [Wednesday 10 November 2010] [12:22:18] <dv_>	oh hold on.
| [Wednesday 10 November 2010] [12:22:37] <dv_>	i might have a logical error here.
| [Wednesday 10 November 2010] [12:22:47] <guido_g>	"Leaving multicast loopback enabled when it is not required can have a negative impact on performance." <- from the docs
| [Wednesday 10 November 2010] [12:22:47] <dv_>	i'll try something, just a sec
| [Wednesday 10 November 2010] [12:23:01] <guido_g>	scho' recht :)
| [Wednesday 10 November 2010] [12:23:07] <pieterh>	dv_ for a chat program you really don't care too much about performance
| [Wednesday 10 November 2010] [12:23:22] <pieterh>	my advice would be to start simple
| [Wednesday 10 November 2010] [12:23:28] <pieterh>	pub sub over tcp, period
| [Wednesday 10 November 2010] [12:23:58] <pieterh>	and use a server :-)
| [Wednesday 10 November 2010] [12:24:09] <pieterh>	it is significantly simpler than using multicast
| [Wednesday 10 November 2010] [12:24:31] <pieterh>	further, any real 0MQ application does end up using servers (devices, minibrokers, etc)
| [Wednesday 10 November 2010] [12:24:48] <pieterh>	so it's worth exploring how that works, it's a big part of "testing 0MQ"
| [Wednesday 10 November 2010] [12:29:01] <mikko>	howdy
| [Wednesday 10 November 2010] [12:32:26] <dv_>	pieterh: already noticed. i just find multicasting appealing for nodes that communicate with each other
| [Wednesday 10 November 2010] [12:32:38] <dv_>	pieterh: but maybe i'll try that, yeah.
| [Wednesday 10 November 2010] [12:32:49] <pieterh>	mikko, howdy
| [Wednesday 10 November 2010] [12:33:09] <pieterh>	dv_, I'd recommend only doing multicast once you've grokked the unicast patterns
| [Wednesday 10 November 2010] [12:33:18] <kisielk>	pieterh: sorry about not mailing the list for that patch, it was late night and I didn't think of it :)
| [Wednesday 10 November 2010] [12:33:20] <dv_>	pieterh: its not just performance, its also resilience - a server is a single point of failure, something i have to fight at work with
| [Wednesday 10 November 2010] [12:33:48] <dv_>	pieterh: so this chat thing is also a learning experience, ultimately i would use this also for discovery
| [Wednesday 10 November 2010] [12:33:53] <pieterh>	dv_, sure, there are solutions to that, usually making redundant devices
| [Wednesday 10 November 2010] [12:34:13] <dv_>	pieterh: this is what we do, and it is nontrivial
| [Wednesday 10 November 2010] [12:34:35] <pieterh>	dv_, indeed, reliability is always hard work
| [Wednesday 10 November 2010] [12:34:46] <pieterh>	multicast can help in some cases
| [Wednesday 10 November 2010] [12:35:12] <pieterh>	but the real answer is to make simpler pieces that are much less likely to crash
| [Wednesday 10 November 2010] [12:35:49] <Guthur>	pieterh, Did you get my second batch of clrzmq2 examples sent to the ML?
| [Wednesday 10 November 2010] [12:36:03] <pieterh>	Guthur, yup, I did
| [Wednesday 10 November 2010] [12:36:07] <pieterh>	didn't I confirm, sorry...
| [Wednesday 10 November 2010] [12:36:21] <pieterh>	btw getting a tarball is actually a lot easier than git pull requests...
| [Wednesday 10 November 2010] [12:36:29] <dv_>	it is?
| [Wednesday 10 November 2010] [12:36:32] <pieterh>	yeah
| [Wednesday 10 November 2010] [12:36:56] <dv_>	oh, for patches you mean
| [Wednesday 10 November 2010] [12:37:10] <pieterh>	i sometimes get git merges go inexplicably weird and then I'm left with a mess
| [Wednesday 10 November 2010] [12:37:15] <Guthur>	pieterh, Oh sorry I see the confirmation now
| [Wednesday 10 November 2010] [12:37:18] <Guthur>	my bad
| [Wednesday 10 November 2010] [12:37:22] <pieterh>	np :-)
| [Wednesday 10 November 2010] [12:37:27] <pieterh>	it's good to double check
| [Wednesday 10 November 2010] [12:37:56] <Guthur>	I never had them on git so it was easier for me
| [Wednesday 10 November 2010] [12:38:31] <pieterh>	ok, I need to leave... if anyone ever needs my attention here on irc just ping me at ph@imatix.com and I'll try to come on
| [Wednesday 10 November 2010] [12:38:55] <Guthur>	bye pieterh 
| [Wednesday 10 November 2010] [12:39:01] <pieterh>	bye Guthur 
| [Wednesday 10 November 2010] [18:10:25] <Led_Zeppelin>	is there a way to do kernel bypass? 
| [Wednesday 10 November 2010] [18:25:38] <igrigorik>	hey all.. question: if i'm using upstream/downstream sockets.. is there any way to actually limit the number of messages in flight? as in, blocking semantics on downstream until some messages are consumed on upstream?
| [Wednesday 10 November 2010] [18:27:49] <igrigorik>	my understanding is that HWM should allow me to control this, but it doesn't appear to be doing the trick 
| [Wednesday 10 November 2010] [18:33:48] <Guthur>	igrigorik, HWM marker is a point where messages went to be sent will start to get dropped
| [Wednesday 10 November 2010] [18:33:58] <Guthur>	went/about
| [Wednesday 10 November 2010] [18:34:20] <Guthur>	It does not limit the number of messages in flight
| [Wednesday 10 November 2010] [18:34:31] <igrigorik>	right, ok.. so its just the sender's buffer
| [Wednesday 10 November 2010] [18:34:40] <Guthur>	igrigorik, yep
| [Wednesday 10 November 2010] [18:34:58] <Guthur>	more or less, from my understanding
| [Wednesday 10 November 2010] [18:34:58] <igrigorik>	so there is no way for me to actually "control" the number of inflight packets, easily, at least
| [Wednesday 10 November 2010] [18:35:10] <Guthur>	I think you would have to engineer that
| [Wednesday 10 November 2010] [18:35:19] <Guthur>	some sort of ack signal
| [Wednesday 10 November 2010] [18:38:34] <igrigorik>	right, ugh :-)
| [Wednesday 10 November 2010] [18:39:12] <Guthur>	Maybe a more experience user can come along and offer a simple solution
| [Wednesday 10 November 2010] [18:39:27] <Guthur>	I'm rather green when it comes to 0MQ
| [Wednesday 10 November 2010] [18:40:18] <igrigorik>	that makes the two of us :)
| [Wednesday 10 November 2010] [18:40:38] <igrigorik>	if there was a simple solution for this.. that would make my life much simler
| [Wednesday 10 November 2010] [18:40:40] <igrigorik>	*simpler
| [Wednesday 10 November 2010] [18:40:43] <Guthur>	hehe, well at least it would be good practice to develop some sort of ack signal
| [Wednesday 10 November 2010] [18:41:54] <Guthur>	The sender will stop when the count reaches your make amount in flight, and the count is decrement each time the sender receives and acknowledgement of receipt
| [Wednesday 10 November 2010] [18:42:09] <Guthur>	Its actually only a few lines of code in ZMQ
| [Wednesday 10 November 2010] [18:42:18] <Guthur>	in/with
| [Wednesday 10 November 2010] [18:42:48] <Guthur>	what language?
| [Wednesday 10 November 2010] [18:44:34] <igrigorik>	ruby.. but this stuff can get tricky
| [Wednesday 10 November 2010] [18:45:07] <igrigorik>	i guess you can have a separate control channel which can monitor the flow
| [Wednesday 10 November 2010] [18:45:29] <igrigorik>	but if you have a device in the middle (multiple consumers for example, and multiple producers).. oi
| [Wednesday 10 November 2010] [18:45:36] <igrigorik>	hmm
| [Wednesday 10 November 2010] [18:45:50] <igrigorik>	maybe i'm making it more complicated than it should be
| [Wednesday 10 November 2010] [18:46:01] <igrigorik>	(usually the case :-))
| [Wednesday 10 November 2010] [18:46:10] <Guthur>	igrigorik, Will you can use the IDs 
| [Wednesday 10 November 2010] [18:46:29] <Guthur>	of the sockets that sent the messages
| [Wednesday 10 November 2010] [18:47:16] <igrigorik>	in the pub-sub case, yeah, that would work I think
| [Wednesday 10 November 2010] [18:47:32] <Guthur>	If I didn't have to go to bed soon I'd actually be tempted to implement something for the fun, hehe
| [Wednesday 10 November 2010] [18:51:16] <Guthur>	ok, time for sleep, enjoy your hacking igrigorik 
| [Wednesday 10 November 2010] [18:51:23] <igrigorik>	thanks :)
| [Wednesday 10 November 2010] [20:29:44] <mi>	hi
| [Wednesday 10 November 2010] [20:30:25] <Guest62320>	hi
| [Thursday 11 November 2010] [05:49:26] <mikko>	morning
| [Thursday 11 November 2010] [06:19:47] <pieterh>	mikko: g'afternoon
| [Thursday 11 November 2010] [08:00:39] <Guthur>	pieterh, Is ZFL to become more visible on the ZeroMQ website when it reachs a greater maturity?
| [Thursday 11 November 2010] [08:01:13] <Guthur>	It's just that I never noticed it until I was added to it on github
| [Thursday 11 November 2010] [08:01:23] <Guthur>	it's not very visible
| [Thursday 11 November 2010] [09:32:22] Notice	-NickServ- travlr_ is not a registered nickname.
| [Thursday 11 November 2010] [09:32:22] CTCP	Received Version request from frigg.
| [Thursday 11 November 2010] [10:31:13] <pieterh>	Guthur, sorry, just got back to my PC
| [Thursday 11 November 2010] [10:31:32] <pieterh>	ZFL is still a bit of a work in progress
| [Thursday 11 November 2010] [10:45:29] <Guthur>	pieterH: No bother, I've started porting some of it to CLR
| [Thursday 11 November 2010] [10:45:44] <Guthur>	Looking at the config stuff specifically
| [Thursday 11 November 2010] [10:49:22] <pieterh>	hmm, the config stuff needs refactored
| [Thursday 11 November 2010] [10:49:29] <pieterh>	it does two different things
| [Thursday 11 November 2010] [10:49:41] <pieterh>	i need to pull part out into zfl_device or somesuch
| [Thursday 11 November 2010] [10:50:02] <pieterh>	or maybe call it zfl_context
| [Thursday 11 November 2010] [10:50:50] <Guthur>	no problem, I only got as far as doing the tree stuff
| [Thursday 11 November 2010] [10:51:47] <Guthur>	I'll keep an eye on changes to config
| [Thursday 11 November 2010] [10:54:56] <Guthur>	need to go now, back later
| [Thursday 11 November 2010] [11:27:43] <Steve-o>	News at 11, IOCP doesn't help much with UDP
| [Thursday 11 November 2010] [11:29:11] <Steve-o>	I got a 10% performance boost, whilst looking for a 250% increase to match Linux.
| [Thursday 11 November 2010] [12:39:55] 435	travlr_ travlr #gentoo-qt Cannot change nickname while banned on channel
| [Thursday 11 November 2010] [12:40:05] <Guthur>	pieterh, Sorry I was on a webclient and lost the history from the ZMF discussion earlier...
| [Thursday 11 November 2010] [12:40:20] <Guthur>	did you say that Context will probably get removed?
| [Thursday 11 November 2010] [12:59:55] <pieterh>	Guthur, I want to refactor the class
| [Thursday 11 November 2010] [13:00:01] <pieterh>	it does two different things, reallt
| [Thursday 11 November 2010] [13:00:04] <pieterh>	*really
| [Thursday 11 November 2010] [13:02:51] <Guthur>	should it just be dealing with information regarding the service?
| [Thursday 11 November 2010] [13:03:14] <pieterh>	i'd like one class that just loads config data into a tree and provides methods to access the tree
| [Thursday 11 November 2010] [13:03:22] <pieterh>	so we can use that for any random configuration scenario
| [Thursday 11 November 2010] [13:03:35] <pieterh>	and then a second class that uses this to create / configure a service and sockets
| [Thursday 11 November 2010] [13:03:52] <Guthur>	ok, makes sense
| [Thursday 11 November 2010] [13:04:14] <Guthur>	Config info, and then some sort of initiator class
| [Thursday 11 November 2010] [13:05:51] <pieterh>	yeah
| [Thursday 11 November 2010] [13:06:09] <Guthur>	I'll keep an eye out for your refactors
| [Thursday 11 November 2010] [13:06:17] <Guthur>	I might explore some options myself
| [Thursday 11 November 2010] [13:07:04] <pieterh>	it'd be fun to see how close you can map the API in C#
| [Thursday 11 November 2010] [13:07:09] <pieterh>	that's your idea, right?
| [Thursday 11 November 2010] [13:07:37] <Guthur>	Yep
| [Thursday 11 November 2010] [13:07:45] <pieterh>	nice
| [Thursday 11 November 2010] [13:07:52] <Guthur>	It's not too bad
| [Thursday 11 November 2010] [13:08:08] <Guthur>	Of course I don't have to explicitly pass a this pointer, hehe
| [Thursday 11 November 2010] [13:08:18] <Guthur>	this/self
| [Thursday 11 November 2010] [13:08:20] <pieterh>	it's a miracle the horse dances at all...
| [Thursday 11 November 2010] [13:09:03] <pieterh>	meaning, it's fun to be able to get some kind of nice class model in C
| [Thursday 11 November 2010] [13:10:18] <Guthur>	yeah I'd imagine. I find difficulty in giving up my high level constructs to be honest.
| [Thursday 11 November 2010] [13:10:26] <Guthur>	I'm a little lazy, hehe
| [Thursday 11 November 2010] [13:11:01] <Guthur>	Common Lisp would be my preferred choice of tool, but someone beat me to that one...
| [Thursday 11 November 2010] [13:11:14] <Guthur>	CL seems to be one of the most mature bindings
| [Thursday 11 November 2010] [13:11:26] <Guthur>	Has all the guide examples as well
| [Thursday 11 November 2010] [13:15:27] <DanielHolth>	so cool
| [Thursday 11 November 2010] [13:45:07] <jhawk28>	can anyone educate me on the value of a statically build lib for zeromq on windows?
| [Thursday 11 November 2010] [13:59:49] <Guthur>	jhawk28: What makes you think it has value?
| [Thursday 11 November 2010] [14:00:36] <jhawk28>	Im hoping that it allows it to run under any environment
| [Thursday 11 November 2010] [14:01:40] <Guthur>	Maybe, but surely you should just let the system get the dependency?
| [Thursday 11 November 2010] [14:01:50] <Guthur>	if you talking about non-windows
| [Thursday 11 November 2010] [14:02:39] <jhawk28>	talking about windows
| [Thursday 11 November 2010] [14:04:15] <Guthur>	Maybe then, I just like building it separate and using the .so or .dll
| [Thursday 11 November 2010] [17:38:49] <Guthur>	Is there any situation where you would want to be using more than one context
| [Thursday 11 November 2010] [17:57:14] <mikko>	Guthur: if you have multiple libraries using zeromq2
| [Thursday 11 November 2010] [17:57:23] <mikko>	Guthur: and you want them to be independent
| [Thursday 11 November 2010] [17:57:30] <mikko>	that's one situation i can think of
| [Thursday 11 November 2010] [17:58:15] <Guthur>	ok, just checking I wasn't missing something
| [Thursday 11 November 2010] [17:58:18] <Guthur>	cheers
| [Thursday 11 November 2010] [20:09:41] <mikko>	g'evening
| [Friday 12 November 2010] [05:51:24] <kobus>	Anybody else using MinGW when building 0mq?
| [Friday 12 November 2010] [05:52:31] <mikko>	that was hasted
| [Friday 12 November 2010] [05:55:59] <kobus>	I'm trying to build zeromq 2.0.10 on Windows with MinGW (gcc 4.4.0)
| [Friday 12 November 2010] [05:57:02] <kobus>	But I get an error ISO C++ does not support long long
| [Friday 12 November 2010] [05:58:02] <kobus>	If I write a test app that defines a variable as long long, it works, and the size is 8 bytes (from sizeof)
| [Friday 12 November 2010] [05:58:34] <kobus>	Any ideas?
| [Friday 12 November 2010] [06:00:24] <mikko>	kobus: can you show the build log?
| [Friday 12 November 2010] [06:00:31] <mikko>	or output
| [Friday 12 November 2010] [06:00:48] <mikko>	and do you compile your test app with same flags?
| [Friday 12 November 2010] [06:01:54] <kobus>	http://pastebin.com/uMTyvS2J
| [Friday 12 November 2010] [06:02:05] <mikko>	kobus: compile your test program with -Werror -pedantic
| [Friday 12 November 2010] [06:02:36] <mikko>	hmm
| [Friday 12 November 2010] [06:02:57] <mikko>	can you test whether the same is present in github master?
| [Friday 12 November 2010] [06:03:12] <mikko>	https://github.com/zeromq/zeromq2
| [Friday 12 November 2010] [06:05:04] <kobus>	Sorry I'm not familiar with github, just trying to figure out how to get the code...
| [Friday 12 November 2010] [06:05:31] <mikko>	https://github.com/zeromq/zeromq2/tarball/master
| [Friday 12 November 2010] [06:07:59] <mikko>	probably
| [Friday 12 November 2010] [06:08:00] <mikko>	hmm
| [Friday 12 November 2010] [06:08:20] <mikko>	https://gist.github.com/45ab703ecc45263e3be9
| [Friday 12 November 2010] [06:08:23] <mikko>	it's this block
| [Friday 12 November 2010] [06:08:35] <mikko>	i assume __int64 is defined as long long
| [Friday 12 November 2010] [06:13:24] <kobus>	Sorry, I'm trying to build github master. Do I use the configure script from the other source?
| [Friday 12 November 2010] [06:14:49] <mikko>	you don't have autotools on win i guess?
| [Friday 12 November 2010] [06:16:42] <Everton>	Hi
| [Friday 12 November 2010] [06:16:45] <mikko>	hi
| [Friday 12 November 2010] [06:17:00] <Everton>	somo one could help me to install zmq in windows 7?
| [Friday 12 November 2010] [06:17:24] <mikko>	Everton: are you looking to use a specific binding?
| [Friday 12 November 2010] [06:17:31] <mikko>	or just the libraries themselves?
| [Friday 12 November 2010] [06:17:53] <Everton>	yes, mikko...
| [Friday 12 November 2010] [06:18:02] <Everton>	I am looking for java
| [Friday 12 November 2010] [06:18:32] <mikko>	the easiest way is to get visual studio express and build the binaries
| [Friday 12 November 2010] [06:18:40] <mikko>	i might have binaries somewhere
| [Friday 12 November 2010] [06:19:02] <Everton>	I downloaded the Visual C++ 2010
| [Friday 12 November 2010] [06:19:11] <mikko>	have you installed it?
| [Friday 12 November 2010] [06:19:30] <Everton>	but the problem was that I can not compile
| [Friday 12 November 2010] [06:19:39] <Everton>	I intalled the Visual
| [Friday 12 November 2010] [06:20:30] <mikko>	have you download zeromq2?
| [Friday 12 November 2010] [06:20:53] <Everton>	zeromq2??
| [Friday 12 November 2010] [06:21:16] <Everton>	The zmq that is in the first page?
| [Friday 12 November 2010] [06:21:21] <mikko>	http://www.zeromq.org/intro:get-the-software
| [Friday 12 November 2010] [06:21:43] <mikko>	there are build instructions for windows as well
| [Friday 12 November 2010] [06:22:04] <Everton>	yes, I have download this already
| [Friday 12 November 2010] [06:22:37] <Everton>	and make the step-by-step to install on Windows
| [Friday 12 November 2010] [06:23:44] <mikko>	what seems to be the problem?
| [Friday 12 November 2010] [06:24:21] <Everton>	when I "build solucion" on Visual, it create to files in the folder lib: libzmq.dll and libzmq
| [Friday 12 November 2010] [06:24:58] <Everton>	so I deploy the to file on the folder c:/windows/system32
| [Friday 12 November 2010] [06:25:23] <Everton>	but how can I bind to java
| [Friday 12 November 2010] [06:26:08] <mikko>	https://github.com/zeromq/jzmq
| [Friday 12 November 2010] [06:26:50] <kobus>	Mikko: I use MSYS, with the version 2.0.10 I ran ./configure and then make
| [Friday 12 November 2010] [06:27:18] <Everton>	it is just to Linux or to Windows too??
| [Friday 12 November 2010] [06:27:29] <Everton>	what is MSYS?
| [Friday 12 November 2010] [06:28:46] <kobus>	"a component of MinGW known as MSYS (Minimal SYStem) provides win32 ports of a lightweight Unix-like shell environment"
| [Friday 12 November 2010] [06:28:46] <Guthur>	Everton: http://www.mingw.org/wiki/MSYS
| [Friday 12 November 2010] [06:29:06] <mikko>	kobus: i'l check as soon as i get mingw build environment running
| [Friday 12 November 2010] [06:29:59] <kobus>	mikko: thanks, will try to get the githubcode to build
| [Friday 12 November 2010] [06:31:05] <Everton>	for what it is used?
| [Friday 12 November 2010] [06:31:15] <mikko>	kobus: you need to run autogen.sh
| [Friday 12 November 2010] [06:32:03] <Everton>	mikko, I need to run autogen.sh too?
| [Friday 12 November 2010] [06:32:19] <kobus>	mikko: autogen.sh: error: could not find pkg-config.  pkg-config is required to run autogen.sh
| [Friday 12 November 2010] [06:32:37] <kobus>	mikko: sorry, I feel very stupid today...
| [Friday 12 November 2010] [06:32:45] <Guthur>	Everton: You are using MS toolchain and don't need to follow the other conversation
| [Friday 12 November 2010] [06:34:28] <Everton>	So I just hava to open the the jzmq in the Visual and run "build solucion"?
| [Friday 12 November 2010] [06:35:24] <mikko>	Everton: there is build folder in jzmq
| [Friday 12 November 2010] [06:35:32] <mikko>	open it and build 
| [Friday 12 November 2010] [06:35:46] <Everton>	I will try now...
| [Friday 12 November 2010] [06:45:25] <Everton_>	what I have to do to use javac in windows?
| [Friday 12 November 2010] [06:46:43] <Everton_>	I set the enviroment variable JAVA_HOME=C:\Program Files\Java\jdk1.6.0_23
| [Friday 12 November 2010] [06:54:21] <mikko>	kobus: how do i run autogen.sh under windows?
| [Friday 12 November 2010] [07:00:11] <kobus>	mikko: Sorry went for a coffee. I use the MSYS shell, so just as you would in Unix: ./autogen.sh 
| [Friday 12 November 2010] [07:03:33] <kobus>	mikko: I use Qt SDK and Qt Creator as IDE, which uses MinGW. I can also use the MS compiler, but I try to use the same compiler on Linux and Windows
| [Friday 12 November 2010] [07:12:26] <mikko>	autogen just refuses to run on mingq
| [Friday 12 November 2010] [07:12:29] <mikko>	mingw*
| [Friday 12 November 2010] [07:23:57] <Everton>	Hi, I try to comile the jzmq
| [Friday 12 November 2010] [07:24:03] <Everton>	but it returns Error	1	error C1083: Cannot open include file: 'zmq.h': No such file or directory	c:\users\everton\desktop\zeromq-jzmq-5a221a5\src\util.cpp	22	1	jzmq 
| [Friday 12 November 2010] [07:24:16] <Everton>	could some one help me?
| [Friday 12 November 2010] [07:24:29] <mikko>	Everton: open solution preferences
| [Friday 12 November 2010] [07:24:34] <mikko>	there should be additional include paths
| [Friday 12 November 2010] [07:24:49] <mikko>	add the path to zmq.h (which is where you have zeromq2/includes'
| [Friday 12 November 2010] [07:27:20] <Everton>	where is solucion preferences?
| [Friday 12 November 2010] [07:29:34] <mikko>	http://social.msdn.microsoft.com/Forums/en/vcgeneral/thread/a494abb8-3561-4ebe-9eb0-6f644a679862
| [Friday 12 November 2010] [07:39:04] <Everton>	great...
| [Friday 12 November 2010] [07:39:17] <Everton>	now is appearing
| [Friday 12 November 2010] [07:39:33] <Everton>	that jni.h can not found
| [Friday 12 November 2010] [07:39:38] <Everton>	where is it?
| [Friday 12 November 2010] [07:51:23] <mikko>	jdk
| [Friday 12 November 2010] [07:55:48] <kobus>	mikko: where does the configure script in the released version of zeromq come from, was it generated on Linux?
| [Friday 12 November 2010] [07:56:58] <Everton>	thanks...
| [Friday 12 November 2010] [07:57:27] <Everton>	The new error, now is: Error	3	error LNK1104: cannot open file 'libzmq.lib'	C:\Users\Everton\Desktop\zeromq-jzmq-5a221a5\builds\msvc\jzmq\LINK	jzmq 
| [Friday 12 November 2010] [07:57:46] <Everton>	I have this file (libzmq.lib) 
| [Friday 12 November 2010] [07:58:07] <Everton>	in the folder windows\system32
| [Friday 12 November 2010] [07:58:32] <Everton>	but I dont know where I indicade the path?
| [Friday 12 November 2010] [07:58:37] <mikko>	kobus: i reckon so
| [Friday 12 November 2010] [08:00:58] <kobus>	I hate Windows
| [Friday 12 November 2010] [08:08:33] <Everton>	sorry, in fact i have libzmq.dll and not .lib
| [Friday 12 November 2010] [08:08:53] <Everton>	where can I find the lib and where should I put this?
| [Friday 12 November 2010] [08:16:39] <mikko>	the lib should be under the zeromq2 directories
| [Friday 12 November 2010] [08:16:45] <mikko>	and you can add additional library paths
| [Friday 12 November 2010] [08:16:50] <mikko>	just like you added additional include paths
| [Friday 12 November 2010] [08:19:12] <Everton>	could be the dll? or need to be .lib??
| [Friday 12 November 2010] [08:21:39] <mikko>	needs lib
| [Friday 12 November 2010] [08:22:41] <Everton>	I download the lib or it is create when I compile the zmq2?
| [Friday 12 November 2010] [08:25:17] <mikko>	it is created when you compile
| [Friday 12 November 2010] [08:25:56] <mikko>	it should be in zeromq2\lib
| [Friday 12 November 2010] [08:26:15] <Everton>	where I include an .obj file?
| [Friday 12 November 2010] [08:26:21] <mikko>	sorry?
| [Friday 12 November 2010] [08:26:39] <Everton>	I think I do not compile the zmq2 right
| [Friday 12 November 2010] [08:26:52] <Everton>	so I do again and appear:
| [Friday 12 November 2010] [08:27:02] <Everton>	Error	3	error LNK2019: unresolved external symbol __imp__zmq_device referenced in function "void __cdecl zmq::device(int,void *,void *)" (?device@zmq@@YAXHPAX0@Z)	C:\Users\Everton\Desktop\zeromq-2.0.10\builds\msvc\zmq_streamer\zmq_streamer.obj	zmq_streamer 
| [Friday 12 November 2010] [08:27:40] <Everton>	so I think I need to LINK zmq_streamer.obj, right?
| [Friday 12 November 2010] [08:27:45] <Guthur>	why can't the dll be used?
| [Friday 12 November 2010] [08:28:17] <Everton>	I dont know...
| [Friday 12 November 2010] [08:28:27] <mikko>	Guthur: afaik in windows you use import libraries for linking
| [Friday 12 November 2010] [08:28:31] <mikko>	(.lib files)
| [Friday 12 November 2010] [08:28:42] <mikko>	but i am not an expert of that platform
| [Friday 12 November 2010] [08:29:01] <Guthur>	neither here, but I think the jzmq can use the dll
| [Friday 12 November 2010] [08:29:13] <Guthur>	I'm pretty sure I did when I built it
| [Friday 12 November 2010] [08:29:44] <mikko>	.dll is for the runtime
| [Friday 12 November 2010] [08:29:49] <mikko>	and .lib is for linking
| [Friday 12 November 2010] [08:30:06] <Guthur>	But you should be able to dynamicly link
| [Friday 12 November 2010] [08:30:10] <Guthur>	thats what dll is for
| [Friday 12 November 2010] [08:30:16] <Guthur>	dynamic link library
| [Friday 12 November 2010] [08:31:05] <mikko>	Linking to dynamic libraries is usually handled by linking to an import library when building or linking to create an executable file. The created executable then contains an import address table (IAT) by which all DLL function calls are referenced (each referenced DLL function contains its own entry in the IAT). At run-time, the IAT is filled with appropriate addresses that point directly to a function in the separately-loaded DLL.
| [Friday 12 November 2010] [08:31:12] <mikko>	that is from http://en.wikipedia.org/wiki/Dynamic-link_library
| [Friday 12 November 2010] [08:31:30] <Everton>	however, where could I LINK the zmq_streamer.obj
| [Friday 12 November 2010] [08:32:03] <Guthur>	I'm not at home at he moment unfortunately, need my tools to check, hehe
| [Friday 12 November 2010] [08:32:26] <Everton>	hehe
| [Friday 12 November 2010] [08:32:32] <Everton>	alrigth
| [Friday 12 November 2010] [08:32:39] <Everton>	mikko, you know?
| [Friday 12 November 2010] [08:32:59] <mikko>	Everton: try cleaning the solution and rebuilding
| [Friday 12 November 2010] [08:33:08] <mikko>	the msvc templates should work out of the box
| [Friday 12 November 2010] [08:33:24] <Everton>	I have some Options here:Executable directories
| [Friday 12 November 2010] [08:33:29] <Everton>	Include directories
| [Friday 12 November 2010] [08:33:37] <Everton>	Reference directories
| [Friday 12 November 2010] [08:33:41] <mikko>	you shouldn't edit the options on the libzmq build
| [Friday 12 November 2010] [08:33:46] <mikko>	there should be no need to do that
| [Friday 12 November 2010] [08:33:49] <Everton>	Library directories
| [Friday 12 November 2010] [08:34:15] <Everton>	really?
| [Friday 12 November 2010] [08:34:21] <mikko>	yes
| [Friday 12 November 2010] [08:34:31] <Everton>	I already hava set the include directories
| [Friday 12 November 2010] [08:34:33] <mikko>	only on jzmq as that needs to know where libzmq is located in
| [Friday 12 November 2010] [08:35:04] <Everton>	but my zmq  cant compile
| [Friday 12 November 2010] [08:36:22] <mikko>	have you edited the zmq solution settings?
| [Friday 12 November 2010] [08:36:47] <Everton>	no
| [Friday 12 November 2010] [08:36:53] <Everton>	where?
| [Friday 12 November 2010] [08:38:12] <mikko>	where what?
| [Friday 12 November 2010] [08:38:29] <CIA-20>	zeromq2: 03Marc Rossi 07maint * rf7123de 10/ (AUTHORS src/socket_base.cpp): 
| [Friday 12 November 2010] [08:38:29] <CIA-20>	zeromq2: Fix socket_t::recv() hang scenario where initial call to process_commands() eats signal
| [Friday 12 November 2010] [08:38:29] <CIA-20>	zeromq2: Added block boolean var to second process_commands() invocation for blocking sockets
| [Friday 12 November 2010] [08:38:29] <CIA-20>	zeromq2: instead of always using true. This prevents the process_commands() call from hanging
| [Friday 12 November 2010] [08:38:29] <CIA-20>	zeromq2: when a message is received with an empty queue after the call to xrecv() but
| [Friday 12 November 2010] [08:38:29] <CIA-20>	zeromq2: prior to the initial call to process_commands() invoked when ++ticks == inbound_poll_rate.
| [Friday 12 November 2010] [08:38:30] <CIA-20>	zeromq2: Signed-off-by: Marc Rossi <mrossi19@gmail.com> - http://bit.ly/cMWLFe
| [Friday 12 November 2010] [08:38:53] <Everton>	In 10 minutes I come back, my teachear needs to close the class, so I will go home... 10 minutes I come back
| [Friday 12 November 2010] [08:39:01] <mikko>	ok
| [Friday 12 November 2010] [08:47:03] <CIA-20>	zeromq2: 03Marc Rossi 07master * rf7123de 10/ (AUTHORS src/socket_base.cpp): 
| [Friday 12 November 2010] [08:47:03] <CIA-20>	zeromq2: Fix socket_t::recv() hang scenario where initial call to process_commands() eats signal
| [Friday 12 November 2010] [08:47:03] <CIA-20>	zeromq2: Added block boolean var to second process_commands() invocation for blocking sockets
| [Friday 12 November 2010] [08:47:03] <CIA-20>	zeromq2: instead of always using true. This prevents the process_commands() call from hanging
| [Friday 12 November 2010] [08:47:03] <CIA-20>	zeromq2: when a message is received with an empty queue after the call to xrecv() but
| [Friday 12 November 2010] [08:47:03] <CIA-20>	zeromq2: prior to the initial call to process_commands() invoked when ++ticks == inbound_poll_rate.
| [Friday 12 November 2010] [08:47:04] <CIA-20>	zeromq2: Signed-off-by: Marc Rossi <mrossi19@gmail.com> - http://bit.ly/cMWLFe
| [Friday 12 November 2010] [08:47:05] <CIA-20>	zeromq2: 03Martin Sustrik 07master * r8abe673 10/ (AUTHORS src/socket_base.cpp): 
| [Friday 12 November 2010] [08:47:05] <CIA-20>	zeromq2: Merge branch 'maint'
| [Friday 12 November 2010] [08:47:06] <CIA-20>	zeromq2: * maint:
| [Friday 12 November 2010] [08:47:06] <CIA-20>	zeromq2:  Fix socket_t::recv() hang scenario where initial call to process_commands() eats signal
| [Friday 12 November 2010] [08:47:07] <CIA-20>	zeromq2: Conflicts:
| [Friday 12 November 2010] [08:47:07] <CIA-20>	zeromq2:  src/socket_base.cpp - http://bit.ly/aituhH
| [Friday 12 November 2010] [08:56:21] <Everton>	Hi, Im back
| [Friday 12 November 2010] [08:56:47] <Everton>	mikko, I download the link that you pass me...
| [Friday 12 November 2010] [08:57:20] <mikko>	Everton: which one of them?
| [Friday 12 November 2010] [08:57:29] <mikko>	the package for windows?
| [Friday 12 November 2010] [08:58:44] <Everton>	you pass to me the link:
| [Friday 12 November 2010] [08:58:46] <Everton>	https://github.com/zeromq/zeromq2/commit/f7123de9434a96794e6a7cd83b398ceb18c9de8b
| [Friday 12 November 2010] [08:58:59] <Everton>	is this for windows?
| [Friday 12 November 2010] [08:59:49] <mikko>	Everton: i haven't passed that link to you
| [Friday 12 November 2010] [08:59:53] <mikko>	im quite positive
| [Friday 12 November 2010] [09:00:17] <Everton>	so ok...
| [Friday 12 November 2010] [09:00:22] <Everton>	and now? 
| [Friday 12 November 2010] [09:01:36] <mikko>	just download the package, follow the instructions
| [Friday 12 November 2010] [09:01:43] <mikko>	didnt you get it built already?
| [Friday 12 November 2010] [09:01:49] <mikko>	i gotta go to a meeting, back in a whil
| [Friday 12 November 2010] [09:01:50] <mikko>	e
| [Friday 12 November 2010] [09:03:44] <sustrik>	hi mikko!
| [Friday 12 November 2010] [09:03:48] <Everton>	ok
| [Friday 12 November 2010] [09:04:00] <sustrik>	the patch you've sent, is it for maint or master?
| [Friday 12 November 2010] [09:32:56] <Everton>	Mikko, I compille the zmq2, without errors
| [Friday 12 November 2010] [09:33:16] <Everton>	but it doesnt create the lib
| [Friday 12 November 2010] [10:59:18] <mikko>	sustrik: master
| [Friday 12 November 2010] [11:01:32] <mikko>	sustrik: found another issue
| [Friday 12 November 2010] [11:08:04] <sustrik>	mikko: what issue?
| [Friday 12 November 2010] [11:09:37] <mikko>	mingw32 builds
| [Friday 12 November 2010] [11:09:59] <mikko>	the issue is with __int64 offset = _lseeki64 (fd, write_buf_start_addr, SEEK_SET);
| [Friday 12 November 2010] [11:10:02] <mikko>	it seems
| [Friday 12 November 2010] [11:10:10] <mikko>	__int64 being defined as 'long long'
| [Friday 12 November 2010] [11:10:30] <mikko>	and C++ -pedantic -Werror complains about ISO C++ 1998 doesn't have long long type
| [Friday 12 November 2010] [11:10:33] <mikko>	and errors out
| [Friday 12 November 2010] [11:10:34] <Steve-o>	the "-Wno-long-long" issue again?
| [Friday 12 November 2010] [11:10:40] <mikko>	Steve-o: different one
| [Friday 12 November 2010] [11:10:44] <sustrik>	presumably
| [Friday 12 November 2010] [11:10:47] <Steve-o>	this has been on the list twice before
| [Friday 12 November 2010] [11:10:56] <mikko>	Steve-o: for mingw32 ?
| [Friday 12 November 2010] [11:11:08] <Steve-o>	pass, certainly something with int64
| [Friday 12 November 2010] [11:11:29] <sustrik>	what's the problem exactly?
| [Friday 12 November 2010] [11:11:35] <mikko>	yeah, on windows __int64 looks like to be 'long long'
| [Friday 12 November 2010] [11:11:47] <mikko>	sustrik: http://pastebin.com/uMTyvS2J
| [Friday 12 November 2010] [11:11:49] <sustrik>	win being incompaible with ISO C++?
| [Friday 12 November 2010] [11:11:50] <mikko>	the problem is that 
| [Friday 12 November 2010] [11:11:52] <Steve-o>	C++ 2003 doesn't support int64
| [Friday 12 November 2010] [11:12:05] <mikko>	with maint version
| [Friday 12 November 2010] [11:12:07] <Steve-o>	but all the compilers do
| [Friday 12 November 2010] [11:12:29] <mikko>	but the issue comes from -Werror -pedantic 
| [Friday 12 November 2010] [11:12:39] <mikko>	as this causes a warning and fails the build
| [Friday 12 November 2010] [11:13:26] <Steve-o>	which is why ZMQ includes "-Wno-long-long" for PGM as I use int64 & uint64 everywhere
| [Friday 12 November 2010] [11:13:39] <mikko>	but isnt pgm compiled as C?
| [Friday 12 November 2010] [11:13:46] <Steve-o>	but you link with C++
| [Friday 12 November 2010] [11:13:58] <Steve-o>	as in pgm_socket.cpp, etc
| [Friday 12 November 2010] [11:14:24] <mikko>	but if it's extern C linkage does the long long issue still creep in?
| [Friday 12 November 2010] [11:14:55] <Steve-o>	data structures include long longs, such as timestamps
| [Friday 12 November 2010] [11:15:19] <sustrik>	i see
| [Friday 12 November 2010] [11:16:30] <sustrik>	so, given 0MQ uses -Wno-long-long option
| [Friday 12 November 2010] [11:16:36] <sustrik>	why do we see the error?
| [Friday 12 November 2010] [11:16:57] <Steve-o>	I think it's only for the PGM compile part, for the rest of the code it's not pulled in
| [Friday 12 November 2010] [11:17:04] <mikko>	sustrik: it uses it if PGM ext is enabled
| [Friday 12 November 2010] [11:17:32] <sustrik>	for the whole build?
| [Friday 12 November 2010] [11:18:18] <Steve-o>	Does this also happen with MinGw-w64?  They are finally fixing a lot of these issues.
| [Friday 12 November 2010] [11:18:29] <sustrik>	looking at the pasted error, it has nothing to do with openpgm
| [Friday 12 November 2010] [11:18:34] <Steve-o>	LIBZMQ_EXTRA_CXXFLAGS="${LIBZMQ_EXTRA_CXXFLAGS} -Wno-long-long "
| [Friday 12 November 2010] [11:18:40] <sustrik>	it's in msg_store_t
| [Friday 12 November 2010] [11:19:29] <mikko>	Steve-o: mingw64 is not regarded in any way 
| [Friday 12 November 2010] [11:20:00] <mikko>	i could take a couple of iterations on the autoconf stuff
| [Friday 12 November 2010] [11:20:10] <mikko>	i started already by splitting some stuff into macros
| [Friday 12 November 2010] [11:20:13] <Steve-o>	mikko: I'm following progress as they are definitely breaking stuff compared with MinGW32
| [Friday 12 November 2010] [11:20:47] <mikko>	https://github.com/zeromq/zeromq2/blob/master/configure.in#L187
| [Friday 12 November 2010] [11:20:50] <mikko>	currently we do that
| [Friday 12 November 2010] [11:21:38] <sustrik>	so, the above problem looks IMO like this:
| [Friday 12 November 2010] [11:21:54] <sustrik>	the line in question uses __int64
| [Friday 12 November 2010] [11:22:05] <sustrik>	which in not a long long on MSVC
| [Friday 12 November 2010] [11:22:12] <sustrik>	rather an intrinsic type
| [Friday 12 November 2010] [11:22:25] <sustrik>	however, it looks like mingw just typedefs it to long long
| [Friday 12 November 2010] [11:22:32] <sustrik>	which causes the warning
| [Friday 12 November 2010] [11:23:15] <sustrik>	a question: do we have a POSIX-y stdint.h when compiling with MinGW?
| [Friday 12 November 2010] [11:23:39] <sustrik>	if so, we can use int64_t instead of __int64
| [Friday 12 November 2010] [11:23:54] <Steve-o>	is MinGW's stdint broken then?
| [Friday 12 November 2010] [11:24:03] <mikko>	we got stdint.hpp 
| [Friday 12 November 2010] [11:24:10] <mikko>	let me run a build
| [Friday 12 November 2010] [11:24:15] <sustrik>	the line in question looks like this:
| [Friday 12 November 2010] [11:24:15] <mikko>	it should report during configure
| [Friday 12 November 2010] [11:24:21] <sustrik>	__int64 offset = _lseeki64 (fd, pos, SEEK_SET);
| [Friday 12 November 2010] [11:24:30] <sustrik>	which works ok with MSVC
| [Friday 12 November 2010] [11:24:38] <sustrik>	but not with mingw afaiu
| [Friday 12 November 2010] [11:24:40] <mikko>	but is MSVC pedantic?
| [Friday 12 November 2010] [11:24:58] <sustrik>	msvc doesn't have the notion of pedantic afaik
| [Friday 12 November 2010] [11:25:06] <Steve-o>	tends to be more pedantic in x64 mode
| [Friday 12 November 2010] [11:25:24] <sustrik>	in any case the problem exists only for mingw
| [Friday 12 November 2010] [11:25:44] <sustrik>	so maybe just chaning this line:
| [Friday 12 November 2010] [11:25:51] <sustrik>	#ifdef ZMQ_HAVE_WINDOWS
| [Friday 12 November 2010] [11:25:51] <sustrik>	        __int64 offset = _lseeki64 (fd, pos, SEEK_SET);
| [Friday 12 November 2010] [11:25:51] <sustrik>	#else
| [Friday 12 November 2010] [11:25:53] <sustrik>	into:
| [Friday 12 November 2010] [11:25:53] <mikko>	possibly cygwin as well (?)
| [Friday 12 November 2010] [11:26:02] <sustrik>	#idfed _MSC_VER
| [Friday 12 November 2010] [11:26:05] <sustrik>	etc.
| [Friday 12 November 2010] [11:26:09] <sustrik>	would help
| [Friday 12 November 2010] [11:26:11] <sustrik>	no?
| [Friday 12 November 2010] [11:27:21] <Steve-o>	FYI it looks like MinGW-w64 actually fixes this problem,
| [Friday 12 November 2010] [11:27:49] <sustrik>	Steve-o: ack
| [Friday 12 November 2010] [11:29:04] <mikko>	should we check for "mingw" rather than "mingw32" ?
| [Friday 12 November 2010] [11:31:14] <Steve-o>	mingw32 is the old name many distros still use, it renamed for x64 support
| [Friday 12 November 2010] [11:32:11] <sustrik>	mikko, Steve-o: btw, what about the mikko's patch on the mailing list?
| [Friday 12 November 2010] [11:32:16] <sustrik>	should i apply it?
| [Friday 12 November 2010] [11:32:59] <Steve-o>	Isn't Mato still looking after autoconf?
| [Friday 12 November 2010] [11:33:07] <sustrik>	he should
| [Friday 12 November 2010] [11:33:19] <sustrik>	bet he's rather busy right now
| [Friday 12 November 2010] [11:33:24] <sustrik>	but
| [Friday 12 November 2010] [11:33:47] <Steve-o>	I was also wondering if ZMQ works on any platform without a c99 compiler
| [Friday 12 November 2010] [11:33:59] <Steve-o>	otherwise go for it
| [Friday 12 November 2010] [11:34:13] <sustrik>	no idea
| [Friday 12 November 2010] [11:34:18] <sustrik>	but it's unlikely imo
| [Friday 12 November 2010] [11:34:34] <mikko>	Steve-o: it's only for C compiler
| [Friday 12 November 2010] [11:34:39] <mikko>	which is used just for PGM
| [Friday 12 November 2010] [11:34:48] <mikko>	C++ compiler for rest of the zeromq
| [Friday 12 November 2010] [11:34:55] <Steve-o>	Would configure fail though if no c99 existed?
| [Friday 12 November 2010] [11:34:57] <sustrik>	right, i think it should be safe
| [Friday 12 November 2010] [11:35:14] <mikko>	Steve-o: let me check the macro
| [Friday 12 November 2010] [11:35:19] <sustrik>	if you are on very exotic platform it's not likely you'll be able to compile the whole thing anyway
| [Friday 12 November 2010] [11:35:25] <Steve-o>	:)
| [Friday 12 November 2010] [11:36:10] <mikko>	it might be possible to move AC_PROG_CC_C99 inside the PGM checks
| [Friday 12 November 2010] [11:36:25] <mikko>	i reckon it might be a bit cleaner to break down the build a bit 
| [Friday 12 November 2010] [11:37:43] <mikko>	Steve-o: After calling this macro you can check whether the C compiler has been set to accept C99; if not, the shell variable ac_cv_prog_cc_c99 is set to no. 
| [Friday 12 November 2010] [11:38:09] <Steve-o>	ok, no problem then
| [Friday 12 November 2010] [11:38:14] <mikko>	so additionally there should be a check inside PGM ext saying that things will fail due to lack of c99 compiler
| [Friday 12 November 2010] [11:40:53] <Steve-o>	ok, just tried to build a master snapshot with x86_64-w64-mingw32-g++ and it crapped out on void zmq::swap_t::fill_buf(char*, int64_t), it is looking for C++ 98 not even 2003, odd.
| [Friday 12 November 2010] [11:42:19] <mikko>	which g++ does it ship with?
| [Friday 12 November 2010] [11:42:48] <Steve-o>	This is 4.4.1-1a, I think they're a bit ahead now
| [Friday 12 November 2010] [11:42:53] <mikko>	mine is 4.5.0
| [Friday 12 November 2010] [11:43:20] <Steve-o>	I think I was trying to match whatever GLib team were using
| [Friday 12 November 2010] [11:44:07] <mikko>	there seems to be just AC_PROG_CXX macro for autoconf
| [Friday 12 November 2010] [11:46:17] <Steve-o>	Ubuntu 10.10 ships with 4.4.4 I'm guessing as the w64 package is tagged with a repo number
| [Friday 12 November 2010] [11:47:14] <sustrik>	Steve-o, mikko: if you reach any conclusion about the patch, please let me know via the ML
| [Friday 12 November 2010] [11:49:15] <Everton>	mikko, are you there?
| [Friday 12 November 2010] [11:49:35] <Steve-o>	mikko: I would just add the -Wno-long-long to any MinGW compiler until they fix it.
| [Friday 12 November 2010] [11:50:37] <mikko>	Everton: yes
| [Friday 12 November 2010] [11:50:52] <mikko>	Steve-o: ok
| [Friday 12 November 2010] [11:51:07] <mikko>	Steve-o: are you ok with the patch on the ML?
| [Friday 12 November 2010] [11:51:15] <mikko>	that's a good start as we get builds to succeed
| [Friday 12 November 2010] [11:51:37] <mikko>	i'm refactoring the autoconf parts a bit to try to make it a bit clearer what affects what
| [Friday 12 November 2010] [11:51:54] <Steve-o>	Sure, go for it.  ICC does attempt to mask as GCC as that has the wider code base
| [Friday 12 November 2010] [11:52:20] <Steve-o>	Nothing more retarded than adding a new compiler that is broken with all existing code
| [Friday 12 November 2010] [11:53:07] <Everton>	I can not make build until..
| [Friday 12 November 2010] [11:53:18] <Everton>	could you help me again?
| [Friday 12 November 2010] [11:54:58] <Everton>	in fact, I download again tha package for windows, and retry to build with Visual, in that time, it compile, but was not genereting the lib
| [Friday 12 November 2010] [11:55:56] <Steve-o>	Everton: errors?
| [Friday 12 November 2010] [11:56:14] <Everton>	no...
| [Friday 12 November 2010] [11:56:15] <Everton>	========== Rebuild All: 8 succeeded, 0 failed, 0 skipped ==========
| [Friday 12 November 2010] [11:56:33] <Everton>	I recive this output
| [Friday 12 November 2010] [11:57:16] <Steve-o>	Are you looking in the lib/bin directory?
| [Friday 12 November 2010] [11:59:22] <Steve-o>	I found master a bit odd, libzmq.dll is built inside lib and you need to copy to bin to run the examples.
| [Friday 12 November 2010] [11:59:41] <Everton>	I was tring in the windows... where this folder stay?
| [Friday 12 November 2010] [12:00:03] <Everton>	I download the zipfile in the desktop
| [Friday 12 November 2010] [12:01:26] <Steve-o>	easiest way is to place libzmq.dll wherever your ZMQ executable resides
| [Friday 12 November 2010] [12:02:09] <Steve-o>	extract and build into c:\zeromq or something easy to manage
| [Friday 12 November 2010] [12:02:58] <Everton>	I will do that now...
| [Friday 12 November 2010] [12:03:02] <Everton>	one moment...
| [Friday 12 November 2010] [12:10:59] <Everton>	All rigth
| [Friday 12 November 2010] [12:12:05] <Everton>	I have extract and build in C:/zeromq-2.1.10
| [Friday 12 November 2010] [12:12:51] <Steve-o>	open up the solution, build, and you should see C:/zeromq-2.1.10/lib/libzmq.dll
| [Friday 12 November 2010] [12:13:31] <Everton>	all rigth
| [Friday 12 November 2010] [12:13:35] <Everton>	I see that
| [Friday 12 November 2010] [12:14:15] <Steve-o>	copy into C:/zeromq-2.1.10/bin if you want to run the examples in there
| [Friday 12 November 2010] [12:16:44] <Everton>	could I copy to c:/windows/system32?
| [Friday 12 November 2010] [12:16:55] <Everton>	to run in any where?
| [Friday 12 November 2010] [12:19:24] <Steve-o>	that should work, but you will have to manage versioning
| [Friday 12 November 2010] [12:21:05] <Everton>	ok....soh lets try the easy way first
| [Friday 12 November 2010] [12:21:06] <Steve-o>	I think you can use PATH as equivalent of LD_LIBRARY_PATH on Windows, so you could alternatively add C:/zeromq-2.1.10/lib to the system PATH instead
| [Friday 12 November 2010] [12:21:40] <Everton>	I copyed the dll to folder zeromq-2.1.10/bin
| [Friday 12 November 2010] [12:21:48] <Everton>	and now?
| [Friday 12 November 2010] [12:22:23] <Steve-o>	add C:/zeromq-2.1.10/bin to the PATH environment variable?
| [Friday 12 November 2010] [12:24:34] <Everton>	all rigth...
| [Friday 12 November 2010] [12:27:45] <Everton>	and now?
| [Friday 12 November 2010] [12:28:14] <Steve-o>	aside of a reboot, you can run zmq apps anywhere.
| [Friday 12 November 2010] [12:28:44] <Steve-o>	anything else you are looking to do?
| [Friday 12 November 2010] [12:30:07] <Everton>	well, I could run a project i java now?
| [Friday 12 November 2010] [12:30:21] <Everton>	because this is my objective..
| [Friday 12 November 2010] [12:30:40] <Steve-o>	so you are looking to build the java binding
| [Friday 12 November 2010] [12:30:43] <Steve-o>	ok
| [Friday 12 November 2010] [12:31:28] <Steve-o>	i'll have a look, honestly no idea though
| [Friday 12 November 2010] [12:34:09] <Everton>	you know where the libzmq.lib stay?
| [Friday 12 November 2010] [12:34:10] <Steve-o>	I guess you follow the instructions here, http://www.zeromq.org/bindings:java
| [Friday 12 November 2010] [12:34:34] <Steve-o>	there is no static library
| [Friday 12 November 2010] [12:34:37] <Steve-o>	only dynamic library
| [Friday 12 November 2010] [12:35:00] <Everton>	I folow, but to build this binding I need of this lib
| [Friday 12 November 2010] [12:35:04] <Everton>	:/
| [Friday 12 November 2010] [12:35:09] <Steve-o>	hence the java command ends looking like this:  java -Djava.library.path=c:\zeromq-2.1.10\bin -classpath c:\zeromq-2.1.10\java;.
| [Friday 12 November 2010] [12:36:52] <Steve-o>	oh ok, this line, AdditionalDependencies="libzmq.lib"
| [Friday 12 November 2010] [12:39:39] <Everton>	where is this line?
| [Friday 12 November 2010] [12:41:18] <Steve-o>	in the jmq project file
| [Friday 12 November 2010] [12:41:41] <Steve-o>	i mean jzmq project file
| [Friday 12 November 2010] [12:43:06] <Everton>	wait...
| [Friday 12 November 2010] [12:43:43] <Steve-o>	Looks like you need help from Gonzalo, I have no idea how to build the binding.
| [Friday 12 November 2010] [12:45:10] <Everton>	Who is Gonzalo?
| [Friday 12 November 2010] [12:46:02] <Steve-o>	He's on the mailing list, it looks like he works on the Java binding
| [Friday 12 November 2010] [12:46:18] <Everton>	where is the folder of jmq project file
| [Friday 12 November 2010] [12:46:46] <Steve-o>	I'm looking here, https://github.com/zeromq/jzmq/blob/master/builds/msvc/jzmq/jzmq.vcproj
| [Friday 12 November 2010] [12:47:49] <Everton>	How could I talk with Gonzalo?
| [Friday 12 November 2010] [12:48:35] <Steve-o>	post on the mailing list and ask for help building the Java binding for ZeroMQ master on Windows
| [Friday 12 November 2010] [12:48:51] <Steve-o>	then anyone can help you out
| [Friday 12 November 2010] [12:50:51] <Everton>	what is the email of mailing list?
| [Friday 12 November 2010] [12:51:17] <Steve-o>	http://www.zeromq.org/docs:mailing-lists
| [Friday 12 November 2010] [12:51:39] <Steve-o>	you probably have to subscribe first in order to send, http://lists.zeromq.org/mailman/listinfo/zeromq-dev
| [Friday 12 November 2010] [13:05:15] <Everton>	thanks steve
| [Friday 12 November 2010] [13:06:12] <Everton>	any one know where libzmq.lib is? or have it to send me??
| [Friday 12 November 2010] [13:18:39] <janak>	Hello guys, I am having an issue with PUBSUB weather example. I modified this example a bit to send and receive messages continuously. I am using one publisher and multiple subscriber to run this test. Once publisher stops and comes back online after 3 - 4 minutes, the memory usage of the publisher keeps on increasing. I am using C language for this. 
| [Friday 12 November 2010] [13:20:57] <Steve-o>	Everton: checking an old build from master I see libzmq.lib also in the lib directory, it should be sitting next to libzmq.dll
| [Friday 12 November 2010] [13:25:32] <Everton>	Are you saying to donload an old version?
| [Friday 12 November 2010] [13:26:57] <Steve-o>	I have an archive of an old build from master and it had the lib file in it, so you should have one together with the dll
| [Friday 12 November 2010] [13:27:16] <Steve-o>	Do you have extensions disabled in File Explorer?
| [Friday 12 November 2010] [13:34:45] <Guthur>	I think you should be able to change the additional dependencies in the linker options to a dll
| [Friday 12 November 2010] [13:34:53] <Guthur>	in jzmq project
| [Friday 12 November 2010] [13:35:02] <Guthur>	I'm just about to test it now
| [Friday 12 November 2010] [13:35:13] <Guthur>	waiting for slow C++ compilers...
| [Friday 12 November 2010] [13:35:45] <Everton>	Do you have extensions disabled in File Explorer?? I do not understand...
| [Friday 12 November 2010] [13:36:12] <Everton>	could you send me your archive?
| [Friday 12 November 2010] [13:36:16] <Guthur>	oh maybe not, sorry, ignore my previous
| [Friday 12 November 2010] [13:36:26] <Steve-o>	extensions like .lib and .dll are hidden by default in Windows, you need to reconfigure Explorer to show them
| [Friday 12 November 2010] [13:36:31] <Everton>	rsrsr
| [Friday 12 November 2010] [13:36:44] <Everton>	my is hidden
| [Friday 12 November 2010] [13:36:52] <Everton>	why? it is important?
| [Friday 12 November 2010] [13:37:33] <Steve-o>	unless by some magical circumstance it is hiding the .lib file you are looking for
| [Friday 12 November 2010] [13:38:13] <Guthur>	I don't think it is, because zeromq by default outputs a dll
| [Friday 12 November 2010] [13:38:42] <Guthur>	I'm not sure why jzmq is suddenly looking for a lib, I didn't have this trouble a month or so ago
| [Friday 12 November 2010] [13:38:43] <Everton>	yes, 
| [Friday 12 November 2010] [13:38:48] <Steve-o>	but MSVC can create a shim .lib that loads the dll for you
| [Friday 12 November 2010] [13:39:09] <Everton>	I have the dll
| [Friday 12 November 2010] [13:39:13] <Steve-o>	it's not actually a static version of the zmq library, that was discussed on the list recently, not so straight forward
| [Friday 12 November 2010] [13:39:55] <Guthur>	Steve-o, Is this some special requirement of JNI?
| [Friday 12 November 2010] [13:40:44] <Steve-o>	normally you create a mini stub JNI library that interfaces your class/jar library with the real binary library
| [Friday 12 November 2010] [13:41:45] <Steve-o>	as in you cannot just interface with any library like you can with VB.net
| [Friday 12 November 2010] [13:43:25] <Guthur>	It kind reinforces my opinion that Windows is a crappy dev environment
| [Friday 12 November 2010] [13:43:35] <Guthur>	though it's probably not windows fault
| [Friday 12 November 2010] [13:44:15] <Steve-o>	it's Java, same issue on Unix
| [Friday 12 November 2010] [13:46:31] <Steve-o>	Everton: are you downloading the source zip from github?
| [Friday 12 November 2010] [13:49:14] <Everton>	yes
| [Friday 12 November 2010] [13:49:49] <Everton>	I download the a version of september now of jzmq qnd will try again
| [Friday 12 November 2010] [13:51:02] <cremes>	janak: did anyone answer your pub/sub question?
| [Friday 12 November 2010] [13:51:29] <Steve-o>	This is why iMatix have subcriptions for Windows binary packages, a lot of hoops to jump through :-)
| [Friday 12 November 2010] [13:52:58] <janak>	cremes: Nope I am still waiting for answer
| [Friday 12 November 2010] [13:53:48] <cremes>	janak: did you get the original, unmodified example to work properly?
| [Friday 12 November 2010] [13:53:59] <Everton>	I try and it does not work
| [Friday 12 November 2010] [13:54:34] <janak>	cremes: yes because publisher process ends after sending 1000 packets
| [Friday 12 November 2010] [13:54:52] <janak>	I only added while(1) around the sending component by publisher
| [Friday 12 November 2010] [13:55:14] <Everton>	I found a file on net libzmq.lib, so I downloaded and deploy in the folder c:/zeromq2.1.10/lib
| [Friday 12 November 2010] [13:55:35] <Everton>	so now I was reciving other error:
| [Friday 12 November 2010] [13:55:41] <cremes>	janak: please pastie/gist the publisher code you are running
| [Friday 12 November 2010] [13:55:46] <janak>	cremes: #include "zhelpers.h"  int main () {     //  Prepare our context and publisher     void *context = zmq_init (1);     void *publisher = zmq_socket (context, ZMQ_PUB);     zmq_bind (publisher, "tcp://*:5556");     zmq_bind (publisher, "ipc://weather.ipc");      //  Initialize random number generator     srandom ((unsigned) time (NULL));     while (1) {         //  Get values that will fool the boss         int zipcode, temperature
| [Friday 12 November 2010] [13:55:55] <Everton>	Socket.obj
| [Friday 12 November 2010] [13:55:56] <cremes>	janak: use pastie.org or gist.github.com
| [Friday 12 November 2010] [13:56:08] <cremes>	pasting into the channel is not a good idea
| [Friday 12 November 2010] [13:56:30] <janak>	cremes: #include "zhelpers.h"  int main () {     //  Prepare our context and publisher     void *context = zmq_init (1);     void *publisher = zmq_socket (context, ZMQ_PUB);     zmq_bind (publisher, "tcp://*:5556");     zmq_bind (publisher, "ipc://weather.ipc");      //  Initialize random number generator     srandom ((unsigned) time (NULL));     while (1) {         //  Get values that will fool the boss         int zipcode, temperature
| [Friday 12 November 2010] [13:56:58] <cremes>	janak: don't do that; i can't read the code
| [Friday 12 November 2010] [13:57:05] <janak>	cremes:https://gist.github.com/674511
| [Friday 12 November 2010] [13:57:05] <cremes>	use pastie.org or gist.github.com
| [Friday 12 November 2010] [13:57:06] <janak>	sorry for that
| [Friday 12 November 2010] [13:58:54] <cremes>	janak: i just compared that code to what is in the guide; it's exactly the same
| [Friday 12 November 2010] [13:59:09] <janak>	it only has while(1) loop around the s_send
| [Friday 12 November 2010] [13:59:12] <janak>	thats all I added 
| [Friday 12 November 2010] [13:59:37] <cremes>	ok
| [Friday 12 November 2010] [14:01:17] <janak>	cremes: I have to rush for meeting I should be back in 30 minutes. Please feel free to contact me at janak_raja@yahoo.com. Thanks for your help
| [Friday 12 November 2010] [14:02:03] <Everton>	I have this obj, but it cant find
| [Friday 12 November 2010] [14:03:11] <cremes>	janak: for one, make sure you capture the return code from s_send and check for a non-zero value
| [Friday 12 November 2010] [14:03:21] <cremes>	it's possible it is failing but you are ignoring the error
| [Friday 12 November 2010] [14:04:10] <cremes>	also, it looks like the client exits after it receives 100 messages
| [Friday 12 November 2010] [14:04:37] <cremes>	if that's the case, then the PUB socket *should* drop the packets since there are no listeners
| [Friday 12 November 2010] [14:04:45] <janak>	yes I also modified client to accept it continuously 
| [Friday 12 November 2010] [14:04:53] <cremes>	but it sounds like it is queueing them up in memory (up to HWM which is infinite by default)
| [Friday 12 November 2010] [14:04:57] <cremes>	ah, ok
| [Friday 12 November 2010] [14:05:12] <cremes>	so make sure the return codes are all non-zero for the send/recv operations
| [Friday 12 November 2010] [14:05:30] <janak>	https://gist.github.com/674518
| [Friday 12 November 2010] [14:05:33] <cremes>	you might also want to modify the publisher to use a HWM (high water mark)
| [Friday 12 November 2010] [14:06:12] <janak>	one thing I dont understand is this only happens when I have multiple subscribers
| [Friday 12 November 2010] [14:06:52] <cremes>	odd... you should be able to connect dozens/hundreds/thousands of subscribers to the same publisher
| [Friday 12 November 2010] [14:07:10] <cremes>	when you have 1+ subscribers, do any of them receive any messages?
| [Friday 12 November 2010] [14:07:59] <janak>	yes initially when everything is running all of them do receive messages, when I stop publisher / wait for 2 - 3 minutes / start publisher only 1 of the subscriber gets the packets
| [Friday 12 November 2010] [14:08:26] <cremes>	oh oh oh... i see the problem
| [Friday 12 November 2010] [14:08:43] <cremes>	the publisher is "binding" to the endpoint while the subscribers "connect" to it
| [Friday 12 November 2010] [14:08:57] <cremes>	you can't shut down the publisher and then restart it and expect things to reconnect
| [Friday 12 November 2010] [14:09:09] <cremes>	whoever "binds" must be started *first*
| [Friday 12 November 2010] [14:09:28] <cremes>	if you need to have your publisher start/stop like this, put a FORWARDER device in the middle
| [Friday 12 November 2010] [14:09:45] <janak>	hmm interesting
| [Friday 12 November 2010] [14:09:57] <cremes>	does that make sense or did i just talk over your head?
| [Friday 12 November 2010] [14:10:11] <Everton>	some one have the file jzmq.dll??
| [Friday 12 November 2010] [14:10:11] <janak>	I think it went over :) 
| [Friday 12 November 2010] [14:10:28] <cremes>	janak: ha, ok :)
| [Friday 12 November 2010] [14:10:30] <cremes>	let's try again
| [Friday 12 November 2010] [14:10:46] <janak>	in real production scenario what happens if publisher goes down for some reason and comes back online 
| [Friday 12 November 2010] [14:10:52] <cremes>	the publisher *creates* the endpoint by binding to it; so the publisher OWNS that endpoint
| [Friday 12 November 2010] [14:10:53] <janak>	ok 
| [Friday 12 November 2010] [14:11:05] <cremes>	if you shutdown the publisher, then the endpoint becomes invalid
| [Friday 12 November 2010] [14:11:35] <janak>	ok 
| [Friday 12 November 2010] [14:11:36] <cremes>	restarting the publisher creates a *new* endpoint at the same location, but the subscribers are still connected to the old, invalid one
| [Friday 12 November 2010] [14:11:45] <cremes>	you would need to restart the subscribers
| [Friday 12 November 2010] [14:11:58] <cremes>	now, to answer your question about production, the fix is to use a FORWARDER device
| [Friday 12 November 2010] [14:12:19] <janak>	ok 
| [Friday 12 November 2010] [14:12:21] <cremes>	the forwarder device binds (creates!) two endpoints that you can think of as incoming and outgoing
| [Friday 12 November 2010] [14:12:39] <cremes>	the publisher *connects* to the incoming endpoint while the subscribers *connect* to the outgoing endpoint
| [Friday 12 November 2010] [14:13:01] <cremes>	when you shutdown your publisher, the endpoint remains valid *because* the forwarder created it via bind
| [Friday 12 November 2010] [14:13:04] <janak>	do I get any error on subscriber s_recv call if publisher went down ? 
| [Friday 12 November 2010] [14:13:15] <cremes>	janak: i don't think so
| [Friday 12 November 2010] [14:13:24] <cremes>	it will just block forever
| [Friday 12 November 2010] [14:13:42] <janak>	in that case how do I trigger the restart of subscriber based on publisher went down ? 
| [Friday 12 November 2010] [14:14:22] <cremes>	janak: you do *not* need to restart the subscriber if you use a forwarder device
| [Friday 12 November 2010] [14:14:39] <cremes>	the endpoints will all remain valid because the forwarder created them and we are assuming it has stayed up
| [Friday 12 November 2010] [14:16:00] <cremes>	look up "forwarder" in the guide and read through its use-case
| [Friday 12 November 2010] [14:16:40] <janak>	ok .. is there a way to notify subscriber for publisher restart ? 
| [Friday 12 November 2010] [14:17:59] <cremes>	janak: yes, via another set of sockets specific to that information flow
| [Friday 12 November 2010] [14:18:07] <janak>	ok .. that makes sense
| [Friday 12 November 2010] [14:18:55] <janak>	I thought that when I use PUBSUB socket if publisher restarts, all the subscriber will get notified and they will do reconnect 
| [Friday 12 November 2010] [14:19:18] <cremes>	janak: where did you get that idea?
| [Friday 12 November 2010] [14:19:19] <janak>	but I guess I can implement that mechanism on a separate set of sockets
| [Friday 12 November 2010] [14:22:45] <janak>	cremes: this answers that why one of my subscriber is not getting the messages. But why did publisher keep these messages in memory, when publisher restarts and gets new endpoints, why does it keep the messages in queue for one of the subscriber ? 
| [Friday 12 November 2010] [14:24:18] <cremes>	janak: read the section on PUB sockets here: http://api.zeromq.org/zmq_socket.html
| [Friday 12 November 2010] [14:24:30] <cremes>	it doesn't start dropping packets until you hit the HWM
| [Friday 12 November 2010] [14:24:42] <cremes>	by default the HWM is infinite so it will use all available RAM
| [Friday 12 November 2010] [14:24:58] <cremes>	if you want it to drop packets sooner instead of queueing, set HWM to a lower value
| [Friday 12 November 2010] [14:25:26] <janak>	great thanks for your help cremes this helps me in understanding it much better thanks
| [Friday 12 November 2010] [14:25:34] <cremes>	you are welcome
| [Friday 12 November 2010] [16:23:18] <mikko>	hmm
| [Friday 12 November 2010] [16:23:37] <mikko>	Steve-o: do you know why flags passed to pgm build are called "LIBZMQ_EXTRA_CXXFLAGS"
| [Friday 12 November 2010] [16:24:01] <mikko>	shouldnt they go in CFLAGS rather than CXXFLAGS
| [Friday 12 November 2010] [16:24:07] <Steve-o>	no idea
| [Friday 12 November 2010] [16:24:34] <Steve-o>	I believe they are additional flags for building 0mq and not libpgm
| [Friday 12 November 2010] [16:24:42] <Steve-o>	i.e. the -Wno-long-long
| [Friday 12 November 2010] [16:24:50] <Steve-o>	I don't need it with c99
| [Friday 12 November 2010] [16:25:06] <Steve-o>	0mq needs it to build with pgm
| [Friday 12 November 2010] [16:25:51] <mikko>	i added icc -strict-ansi flag
| [Friday 12 November 2010] [16:25:57] <mikko>	pgm doesn't build with it
| [Friday 12 November 2010] [16:26:20] <mikko>	https://gist.github.com/d105eac0be53049b800b
| [Friday 12 November 2010] [16:26:55] <Steve-o>	lol, why doesn't ICC like asm ?
| [Friday 12 November 2010] [16:27:24] <Steve-o>	I'm not sticking random underscores in front till it works
| [Friday 12 November 2010] [16:28:06] <Steve-o>	I know with GCC that std=c99 doesn't work you must use std=gnu99 because strict ANSI is too annoying
| [Friday 12 November 2010] [16:28:35] <mikko>	i assume it expects __asm__
| [Friday 12 November 2010] [16:28:47] <Steve-o>	that's retarded
| [Friday 12 November 2010] [16:29:32] <Steve-o>	Easier to use -Dasm=__asm__  to workaround that
| [Friday 12 November 2010] [16:29:35] <mikko>	http://www.slac.stanford.edu/comp/unix/package/intel_tools/icc/mergedProjects/intref_cls/linux/intref_data_align_ma_ia_linux_ia.htm
| [Friday 12 November 2010] [16:31:02] <Steve-o>	Microsoft likes underscores too much, that's nothing new
| [Friday 12 November 2010] [16:31:31] <Steve-o>	if you continue down that road you also see problems with volatile
| [Friday 12 November 2010] [16:32:48] <Steve-o>	when using the gcc compatibility flags does it like asm?
| [Friday 12 November 2010] [16:32:56] <mikko>	LIBZMQ_EXTRA_CXXFLAGS="${LIBZMQ_EXTRA_CXXFLAGS} -strict-ansi -Dasm=__asm__ "
| [Friday 12 November 2010] [16:32:59] <mikko>	this builds ok
| [Friday 12 November 2010] [16:33:45] <Steve-o>	does -gcc-version=420 change interpretation of "asm"?
| [Friday 12 November 2010] [16:34:57] <mikko>	i can check that in a min
| [Friday 12 November 2010] [16:35:20] <mikko>	hmm, i wonder what happens if i turn off gcc emulation on icc
| [Friday 12 November 2010] [16:35:27] <mikko>	i think by default it tries to be gcc compliant
| [Friday 12 November 2010] [16:36:15] <Steve-o>	the __asm__ is about being compatible with MSVC
| [Friday 12 November 2010] [16:38:26] <Steve-o>	anything with an underscore prefix is compiler specific
| [Friday 12 November 2010] [16:38:53] <Steve-o>	Ooh, __inline is the other one I hate
| [Friday 12 November 2010] [16:40:30] <Steve-o>	I catch that one in the headers, include/pgm/types.h
| [Friday 12 November 2010] [16:50:33] <mikko>	-gcc-version=420 doesnt help
| [Friday 12 November 2010] [16:50:55] <Steve-o>	oh well, 
| [Friday 12 November 2010] [16:51:42] <Steve-o>	you have the workaround with the preprocessor
| [Friday 12 November 2010] [16:51:55] <mikko>	yep, adding that
| [Friday 12 November 2010] [16:52:27] <mikko>	../foreign/openpgm/libpgm-5.0.91~dfsg/openpgm/pgm/net.c(84): warning #191: type qualifier is meaningless on cast type
| [Friday 12 November 2010] [16:52:38] <mikko>	a couple of warnings as well it seem
| [Friday 12 November 2010] [16:52:40] <mikko>	s
| [Friday 12 November 2010] [16:52:55] <Steve-o>	oodles of warnings, I have a list of exceptions in my build environment
| [Friday 12 November 2010] [16:55:09] <Steve-o>	here's my list from before, http://www.mail-archive.com/zeromq-dev@lists.zeromq.org/msg05162.html
| [Friday 12 November 2010] [16:55:41] <Steve-o>	including description of why I ignore them
| [Friday 12 November 2010] [16:56:31] <Steve-o>	two are bugs in the compiler as they are C++2003 warnings
| [Friday 12 November 2010] [16:58:55] <Steve-o>	shout if you think any are valid
| [Friday 12 November 2010] [17:01:11] <Steve-o>	the net.c(84) is for portability, at least one compiler needs it
| [Saturday 13 November 2010] [07:33:43] <mikko>	morning
| [Saturday 13 November 2010] [07:33:51] <mikko>	mato: are you there?
| [Saturday 13 November 2010] [07:58:48] <Guthur>	Is there a way to safe way to stop a ZMQ device
| [Saturday 13 November 2010] [07:59:03] <Guthur>	s/a safe way
| [Saturday 13 November 2010] [07:59:03] <mikko>	what do you mean by safe?
| [Saturday 13 November 2010] [07:59:12] <mikko>	you could send kill signal
| [Saturday 13 November 2010] [07:59:31] <Guthur>	Preferably not that way, hehe
| [Saturday 13 November 2010] [08:00:02] <Guthur>	say I have a program using a device, but want to stop the device and rebind the endpoints
| [Saturday 13 November 2010] [08:00:20] <mikko>	what happens if you send HUP?
| [Saturday 13 November 2010] [08:00:27] <mikko>	if you just want to rebind
| [Saturday 13 November 2010] [08:01:13] <Guthur>	So in the actual program would I just kill the thread it's running on and start again?
| [Saturday 13 November 2010] [08:01:33] <mikko>	i don't know whether there is a clean way
| [Saturday 13 November 2010] [08:02:41] <Guthur>	Do you feel it would be useful, or am I verging towards over-engineering?
| [Saturday 13 November 2010] [08:05:11] <Guthur>	I suppose its more a specialized device
| [Saturday 13 November 2010] [08:05:40] <Guthur>	It would probably require a kill signal socket to offer the cleanest approach
| [Saturday 13 November 2010] [10:16:45] <sustrik>	Guthur: the devices is an area where 0MQ can expand in different ways
| [Saturday 13 November 2010] [10:16:55] <sustrik>	you may add all kinds of features
| [Saturday 13 November 2010] [10:16:59] <sustrik>	stop signal
| [Saturday 13 November 2010] [10:17:05] <sustrik>	monitoring
| [Saturday 13 November 2010] [10:17:24] <sustrik>	dynamic configuration of sockets
| [Saturday 13 November 2010] [10:17:26] <sustrik>	etc.
| [Saturday 13 November 2010] [10:17:27] <Guthur>	sustrik, Do you see 0MQ p
| [Saturday 13 November 2010] [10:17:31] <Guthur>	oops ignore that
| [Saturday 13 November 2010] [10:17:40] <Guthur>	got a little trigger happy
| [Saturday 13 November 2010] [10:18:19] <Guthur>	sustrik, Do you see a 0MQ device project starting at some point, or would it just be left to the users?
| [Saturday 13 November 2010] [10:18:33] <Guthur>	Or would it go into the main 0MQ project
| [Saturday 13 November 2010] [10:18:48] <sustrik>	Guthur: i would say that in the future the devices should be separated from 0mq core
| [Saturday 13 November 2010] [10:19:07] <Guthur>	I would have to agree
| [Saturday 13 November 2010] [10:19:09] <sustrik>	same way as network switches and routers are different from clinet TCP/IP stack
| [Saturday 13 November 2010] [10:19:23] <Guthur>	I see to many projects grow well beyond their initial scope
| [Saturday 13 November 2010] [10:19:39] <Guthur>	feature creep is a real danger with projects
| [Saturday 13 November 2010] [10:19:58] <sustrik>	the thing with devices is that I think there is a lot of space for market segmentation
| [Saturday 13 November 2010] [10:20:14] <sustrik>	from very simple devices like the ones now in the core
| [Saturday 13 November 2010] [10:20:22] <sustrik>	to complex enterprise-grade servers
| [Saturday 13 November 2010] [10:21:05] <sustrik>	but yes, the short-term goal is to keep the feature creep to minimum
| [Saturday 13 November 2010] [10:23:45] <mikko>	sustrik: i got fairly massive patch for the builds
| [Saturday 13 November 2010] [10:23:53] <mikko>	i wonder what would be the best way to do this
| [Saturday 13 November 2010] [10:24:02] <mikko>	maybe if mato has time to review the changes at some point?
| [Saturday 13 November 2010] [10:24:40] <mikko>	https://gist.github.com/51b70e52d845fd64a91a
| [Saturday 13 November 2010] [10:24:46] <mikko>	gotta run ->
| [Saturday 13 November 2010] [10:24:51] <sustrik>	mikko: thx
| [Saturday 13 November 2010] [10:24:55] <sustrik>	i'll poke mato
| [Saturday 13 November 2010] [10:25:08] <sustrik>	but he's finishing some deadline right now afaik
| [Saturday 13 November 2010] [10:25:54] <sustrik>	mikko: why not send the patch to the ML?
| [Saturday 13 November 2010] [10:28:46] <Guthur>	sustrik, Do you don't think that such simplistic devices that have been added to 0MQ are of limited worth with the main OMQ lib 
| [Saturday 13 November 2010] [10:29:31] <sustrik>	yes
| [Saturday 13 November 2010] [10:29:45] <sustrik>	they are they just as examples
| [Saturday 13 November 2010] [10:29:49] <Guthur>	s/don't/not
| [Saturday 13 November 2010] [10:30:06] <sustrik>	presumably, they will be removed in 3.0
| [Saturday 13 November 2010] [10:30:10] <Steve-o>	mikko:  how are you finding Sun ONE also requires __asm__?  Is that also a strict mode?
| [Saturday 13 November 2010] [10:30:22] <sustrik>	by that time we'll have some sane devices outside of 0mq core imo
| [Saturday 13 November 2010] [10:30:36] <Guthur>	sustrik, ack
| [Saturday 13 November 2010] [10:36:54] <mikko>	Steve-o: yes, strict mode
| [Saturday 13 November 2010] [10:37:06] <mikko>	Steve-o: apparently "for ANSI C applications use __asm__"
| [Saturday 13 November 2010] [10:37:16] <mikko>	can't remember where i read that
| [Saturday 13 November 2010] [10:37:27] <Steve-o>	I'm checking their blogs and they use "asm" everywhere, ugh
| [Saturday 13 November 2010] [10:37:49] <mikko>	"If you are writing a header file that will be included in ANSI C programs, use '__asm__' instead of 'asm' and '__volatile__' instead of 'volatile'."
| [Saturday 13 November 2010] [10:37:52] <mikko>	http://mspgcc.sourceforge.net/manual/c1308.html
| [Saturday 13 November 2010] [10:38:52] <Steve-o>	The volatile comment is out of date
| [Saturday 13 November 2010] [10:38:57] <mikko>	yes
| [Saturday 13 November 2010] [10:39:15] <mikko>	__asm__ seems to be the way in ICC and Sun Studio
| [Saturday 13 November 2010] [10:39:22] <mikko>	asm or __asm__ in gcc
| [Saturday 13 November 2010] [10:39:40] <Steve-o>	meh, as long as there is a workaround, useful to note it in  patch though
| [Saturday 13 November 2010] [10:40:13] <Steve-o>	from the link you had yesterday there seems to be three forms, __asm, __asm__, and asm
| [Saturday 13 November 2010] [10:40:20] <mikko>	yeah
| [Saturday 13 November 2010] [10:40:31] <mikko>	interesting enough i can't get ICC to support 'asm'
| [Saturday 13 November 2010] [10:41:02] <mikko>	and sun studio still complains about:
| [Saturday 13 November 2010] [10:41:04] <mikko>	"../foreign/openpgm/libpgm-5.0.91~dfsg/openpgm/pgm/include/pgm/atomic.h", line 46: warning: "__asm__" is an extension of ANSI C
| [Saturday 13 November 2010] [10:41:11] <mikko>	which i guess is fair
| [Saturday 13 November 2010] [10:41:14] <Steve-o>	that's probably why I'm checking for __GNUC__
| [Saturday 13 November 2010] [10:42:09] <Steve-o>	Intel don't provide any custom intrinsics so they're not really helping
| [Saturday 13 November 2010] [10:43:14] <mikko>	"asm" keyword works in ICC unless -strict-ansi is used
| [Saturday 13 November 2010] [10:45:22] <Steve-o>	I'll try updating upstream with it, I've been looking for -pedantic equivalents
| [Saturday 13 November 2010] [10:45:44] <Steve-o>	thanks
| [Saturday 13 November 2010] [10:46:27] <mikko>	np
| [Saturday 13 November 2010] [12:09:49] <CIA-20>	zeromq2: 03Martin Sustrik 07maint * rffcb0ba 10/ (AUTHORS configure.in src/zmq.cpp): 
| [Saturday 13 November 2010] [12:09:50] <CIA-20>	zeromq2: Couple of patches for AIX build
| [Saturday 13 November 2010] [12:09:50] <CIA-20>	zeromq2: - RAND_bytes function resides in crypto library
| [Saturday 13 November 2010] [12:09:50] <CIA-20>	zeromq2: - pollfd on AIX used 'reqevents' instead of events and 'retnevents'
| [Saturday 13 November 2010] [12:09:50] <CIA-20>	zeromq2:  instead of 'revents'
| [Saturday 13 November 2010] [12:09:50] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/bTf46m
| [Saturday 13 November 2010] [12:22:02] <CIA-20>	zeromq2: 03Martin Sustrik 07master * rffcb0ba 10/ (AUTHORS configure.in src/zmq.cpp): 
| [Saturday 13 November 2010] [12:22:02] <CIA-20>	zeromq2: Couple of patches for AIX build
| [Saturday 13 November 2010] [12:22:02] <CIA-20>	zeromq2: - RAND_bytes function resides in crypto library
| [Saturday 13 November 2010] [12:22:02] <CIA-20>	zeromq2: - pollfd on AIX used 'reqevents' instead of events and 'retnevents'
| [Saturday 13 November 2010] [12:22:02] <CIA-20>	zeromq2:  instead of 'revents'
| [Saturday 13 November 2010] [12:22:03] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/bTf46m
| [Saturday 13 November 2010] [12:22:03] <CIA-20>	zeromq2: 03Martin Sustrik 07master * rf77c8ca 10/ (AUTHORS configure.in src/zmq.cpp): 
| [Saturday 13 November 2010] [12:22:04] <CIA-20>	zeromq2: Merge branch 'maint'
| [Saturday 13 November 2010] [12:22:04] <CIA-20>	zeromq2: * maint:
| [Saturday 13 November 2010] [12:22:05] <CIA-20>	zeromq2:  Couple of patches for AIX build - http://bit.ly/d6kEuw
| [Saturday 13 November 2010] [12:53:47] <Guthur>	Is publisher side filtering being looked at currently? http://www.zeromq.org/topics:new-topics
| [Saturday 13 November 2010] [12:54:41] <Guthur>	I am actually specifically interested in the scenario mentioned in the white paper, ie. serving up Forex data
| [Saturday 13 November 2010] [13:08:47] <mikko>	Guthur: it's being discussed
| [Saturday 13 November 2010] [13:08:55] <mikko>	but it's a complicated matter
| [Saturday 13 November 2010] [13:09:53] <Guthur>	mikko, Is there any consensus one what the solution might be?
| [Saturday 13 November 2010] [13:29:30] <mikko>	Guthur: not that i know of
| [Saturday 13 November 2010] [13:31:14] <Guthur>	mikko: ok, cheers
| [Saturday 13 November 2010] [13:31:50] <Guthur>	I'll probably try to engineer some device for my own needs
| [Saturday 13 November 2010] [13:38:13] <mikko>	the problematic thing is forwarding the subscriptions
| [Saturday 13 November 2010] [13:38:26] <mikko>	and especially when there are intermediates
| [Saturday 13 November 2010] [18:33:21] <Guthur>	Has anyone else been checking out ZFL and in particular the ZPL ?
| [Saturday 13 November 2010] [18:34:06] <Guthur>	https://github.com/zeromq/zfl  http://rfc.zeromq.org/spec:4
| [Saturday 13 November 2010] [19:42:11] <Guthur>	umm, is there some reason why streamer and forwarder are identical
| [Saturday 13 November 2010] [19:42:55] <Guthur>	just to remind the user to use the appropriate end point types?
| [Sunday 14 November 2010] [05:24:13] <Guthur>	Is it just me or are the z_msg decode and encode functions miss-named?
| [Sunday 14 November 2010] [05:25:14] <Guthur>	encode to me seems like it should be taking a string and encoding it and decode taking a byte stream and returning the string
| [Sunday 14 November 2010] [05:25:41] <mato>	sustrik: are you there?
| [Sunday 14 November 2010] [05:26:28] <Guthur>	not to mention that the comment block is the same for each function which just adds to the confusion
| [Sunday 14 November 2010] [05:27:01] <mato>	Guthur: raise an issue somewhere (issue tracker? zmq ML) with Pieter Hintjens, ZFL is his project
| [Sunday 14 November 2010] [05:27:17] <Guthur>	it's part of the guide as well
| [Sunday 14 November 2010] [05:27:28] <mato>	that's his project too :-)
| [Sunday 14 November 2010] [05:27:34] <Guthur>	hehe, ok
| [Sunday 14 November 2010] [05:27:56] <mato>	I would have preferred that the guide use plain ZMQ and not push any other layers, but it's up to Pieter...
| [Sunday 14 November 2010] [05:28:10] <mato>	I suggest you take that up with him, on the ZMQ mailing list
| [Sunday 14 November 2010] [05:28:27] <Guthur>	Most of the guide is plain ZMQ to be fair
| [Sunday 14 November 2010] [05:28:39] <Guthur>	it's just the last advanced example section
| [Sunday 14 November 2010] [05:28:52] <Guthur>	which is fair enough IMHO
| [Sunday 14 November 2010] [05:29:28] <Guthur>	Even then it doesn't use anything that is not shown in the example
| [Sunday 14 November 2010] [05:29:39] <Guthur>	ZFL is not required as far as I am aware
| [Sunday 14 November 2010] [05:29:52] <Guthur>	though I have not actually completed the last few examples
| [Sunday 14 November 2010] [05:30:54] <Guthur>	I personally think the guide is a great introduction to ZMQ
| [Sunday 14 November 2010] [05:37:22] <Guthur>	There could be more examples from the bindings though.
| [Sunday 14 November 2010] [05:37:44] <Guthur>	I think Java is probably quite a glaring omission, considering how popular it is
| [Sunday 14 November 2010] [05:45:11] <keffo>	I like the new site, much better!
| [Sunday 14 November 2010] [09:25:14] <keffo>	./local_thr.exe tcp://127.0.0.1:1234 10000 10000
| [Sunday 14 November 2010] [09:25:14] <keffo>	Your average throughput is 28732 [msg/s]
| [Sunday 14 November 2010] [09:25:14] <keffo>	Your average throughput is 2298 [Mb/s]
| [Sunday 14 November 2010] [09:25:24] <keffo>	vrom vrom
| [Sunday 14 November 2010] [09:28:50] <keffo>	10 byte msg size: Your average throughput is 3179966 [msg/s]
| [Sunday 14 November 2010] [09:28:50] <keffo>	Your average throughput is 254 [Mb/s]
| [Sunday 14 November 2010] [11:00:06] <Guthur>	keffo...
| [Sunday 14 November 2010] [11:00:06] <Guthur>	Your average throughput is 28854 [msg/s]
| [Sunday 14 November 2010] [11:00:07] <Guthur>	Your average throughput is 2308 [Mb/s]
| [Sunday 14 November 2010] [11:00:23] <Guthur>	that's the CLR binding
| [Sunday 14 November 2010] [11:00:55] <Guthur>	though totally meaningless of course, hehe
| [Sunday 14 November 2010] [11:12:00] <keffo>	it is yeah
| [Sunday 14 November 2010] [11:12:10] <keffo>	meaningless?
| [Sunday 14 November 2010] [11:16:58] <Guthur>	yep
| [Sunday 14 November 2010] [11:17:08] <Guthur>	I should run C version though
| [Sunday 14 November 2010] [11:17:25] <keffo>	this was debug build in an ubuntu VM
| [Sunday 14 November 2010] [11:17:30] <Guthur>	I am personally interested in comparing the performance of the clrzmq binding
| [Sunday 14 November 2010] [11:17:46] <keffo>	it was the clr binding
| [Sunday 14 November 2010] [11:17:51] <Guthur>	yep
| [Sunday 14 November 2010] [11:18:19] <keffo>	oh you mean the fact that it's a binding rather than pure C that is meaningless? Yeah, I agree
| [Sunday 14 November 2010] [11:18:43] <Guthur>	umm nope not really, I meant comparing mine to your figures
| [Sunday 14 November 2010] [11:18:45] <keffo>	(debug/release was equally meaningless)
| [Sunday 14 November 2010] [11:19:18] <Guthur>	different computers obviously to not make for a good comparison
| [Sunday 14 November 2010] [11:19:23] <Guthur>	to/do
| [Sunday 14 November 2010] [11:20:50] <Guthur>	it would be nice to see if there was much overhead in going through the CLR interop
| [Sunday 14 November 2010] [11:21:37] <Guthur>	Wouldn't make me want to develop a significantly complex application in C even if there was but it would be nice to knpw
| [Sunday 14 November 2010] [11:21:40] <Guthur>	know*
| [Sunday 14 November 2010] [11:24:33] <keffo>	probably insignificant
| [Monday 15 November 2010] [03:11:56] <pieterh>	hi folks
| [Monday 15 November 2010] [03:15:17] <travlr>	mornin'
| [Monday 15 November 2010] [03:54:51] <sustrik>	travlr: hi, you there?
| [Monday 15 November 2010] [04:00:40] <travlr>	hi martin
| [Monday 15 November 2010] [04:04:29] <travlr>	sustrik, ^^
| [Monday 15 November 2010] [04:05:02] <sustrik>	hi
| [Monday 15 November 2010] [04:05:10] <sustrik>	you are keeping irc log, right?
| [Monday 15 November 2010] [04:05:29] <travlr>	yes, i was just thinking about that... posting archive
| [Monday 15 November 2010] [04:05:56] <sustrik>	is there any way to see it online?
| [Monday 15 November 2010] [04:06:16] <travlr>	sure. let see what i can do.
| [Monday 15 November 2010] [04:06:28] <sustrik>	travlr: that would be great
| [Monday 15 November 2010] [04:06:59] <travlr>	ok, let put a little into it then right now :)
| [Monday 15 November 2010] [06:50:21] <toni_>	Hi there, just tried to install zmq on ubuntu 10.04. When executing sudo make install I get make[2]: *** [libzmq_la-app_thread.lo] Error 1. Does anyone have an idea how to solve this?
| [Monday 15 November 2010] [06:52:33] <mikko>	toni_: can you paste a few lines up from there to gist.github.com
| [Monday 15 November 2010] [06:52:46] <mikko>	toni_: that line alone doesn't tell much
| [Monday 15 November 2010] [06:53:08] <toni_>	mikko: okay, thanks I ll do this. Just did not want to spam the channel :-)
| [Monday 15 November 2010] [06:54:54] <toni_>	mikko: https://gist.github.com/700285
| [Monday 15 November 2010] [06:57:30] <toni_>	I am a C newbie, actually never build an compiled a c programm before.... just want to use the python bindings... 
| [Monday 15 November 2010] [06:58:23] <mikko>	toni_: and configure ran successfully?
| [Monday 15 November 2010] [06:59:29] <toni_>	mikko: yes, looks like it ran successfully...
| [Monday 15 November 2010] [07:00:16] <mikko>	have you got libstdc++6 package installed?
| [Monday 15 November 2010] [07:01:14] <Guthur>	is configure not checking for dependencies?
| [Monday 15 November 2010] [07:01:29] <toni_>	mikko: yes, the newest version
| [Monday 15 November 2010] [07:01:44] <mikko>	Guthur: it is
| [Monday 15 November 2010] [07:01:58] <mikko>	Guthur: not sure where this build failure comes from
| [Monday 15 November 2010] [07:02:28] <Guthur>	toni_: what distro are you using?
| [Monday 15 November 2010] [07:02:30] <mikko>	looks like there might be some package missing
| [Monday 15 November 2010] [07:03:38] <toni_>	mikko: I have ubuntu 10.0.4
| [Monday 15 November 2010] [07:04:13] <Guthur>	toni_ did you download with git?
| [Monday 15 November 2010] [07:05:05] <toni_>	yes, downloaded zeromq-2.0.10.tar.gz from github
| [Monday 15 November 2010] [07:05:25] <Guthur>	and which branch are you on?
| [Monday 15 November 2010] [07:05:38] <mikko>	2.0.10 would be maint
| [Monday 15 November 2010] [07:06:27] <Guthur>	oh oops sorry I missed the tarball bit
| [Monday 15 November 2010] [07:06:47] <Guthur>	I seen yes and immediately assumed he cloned
| [Monday 15 November 2010] [07:07:37] <toni_>	mikko: what do you mean by "... would be maint"?
| [Monday 15 November 2010] [07:09:39] <toni_>	I also installed libtool, autoconf, automake
| [Monday 15 November 2010] [07:11:27] <Guthur>	toni_: So your exact steps were...
| [Monday 15 November 2010] [07:11:29] <mikko>	toni_: to be fair i am not sure why this error happens. 
| [Monday 15 November 2010] [07:11:31] <Guthur>	./autoconf
| [Monday 15 November 2010] [07:11:34] <Guthur>	./configure
| [Monday 15 November 2010] [07:11:38] <Guthur>	make
| [Monday 15 November 2010] [07:11:40] <mikko>	./autogen.sh probably
| [Monday 15 November 2010] [07:12:05] <Guthur>	mikko, yep sorry my bad
| [Monday 15 November 2010] [07:12:45] <toni_>	my exact steps were:   ./configure, sudo make install
| [Monday 15 November 2010] [07:12:54] <mikko>	toni_: have you got libstdc++6 dev package installed?
| [Monday 15 November 2010] [07:13:03] <Guthur>	that would never have worked
| [Monday 15 November 2010] [07:13:13] <mikko>	although i would expect configure to fail if the build fails so fundamentally
| [Monday 15 November 2010] [07:13:29] <Guthur>	you never generated the configure file
| [Monday 15 November 2010] [07:13:32] <mikko>	Guthur: i think dist packages are distributed via github as well
| [Monday 15 November 2010] [07:13:44] <Guthur>	I didn't see one for ubuntu
| [Monday 15 November 2010] [07:13:59] <Guthur>	I didn't look very hard though
| [Monday 15 November 2010] [07:14:01] <mikko>	Guthur: https://github.com/zeromq/zeromq2/downloads
| [Monday 15 November 2010] [07:14:10] <mikko>	v2.0.10.zip  This is release 2.0.10
| [Monday 15 November 2010] [07:14:18] <Guthur>	i just download there now and followed those three steps
| [Monday 15 November 2010] [07:14:21] <Guthur>	worked fined
| [Monday 15 November 2010] [07:14:27] <mikko>	are you on ubuntu?
| [Monday 15 November 2010] [07:14:31] <Guthur>	yep
| [Monday 15 November 2010] [07:14:42] <mikko>	yes, the release there doesn't ship with configure
| [Monday 15 November 2010] [07:15:45] <Guthur>	I would recommend the process I followed, simply because it worked, hehe
| [Monday 15 November 2010] [07:15:46] <toni_>	mikko: when I do sudo apt-get install libstdc++6, I get libstdc++6 is already the newest version
| [Monday 15 November 2010] [07:15:57] <mikko>	toni_: i mean the -dev package
| [Monday 15 November 2010] [07:16:10] <toni_>	oops, so I ll try it
| [Monday 15 November 2010] [07:19:48] <toni_>	mikko: getting "Couldn't find package libstdc++6-dev" when trying to install it with -dev postfix. (sorry, I just changed couple of months from win to linux)
| [Monday 15 November 2010] [07:21:20] <Guthur>	toni_: You usually need the -dev version of packages when building software on linux
| [Monday 15 November 2010] [07:22:03] <Guthur>	You should be able to see it in synaptic
| [Monday 15 November 2010] [07:22:24] <mikko>	toni_: try libstdc++6-4.4-dev
| [Monday 15 November 2010] [07:23:16] <mikko>	also if you build a lot of stuff 'build-essential' package is a good base for certain dependencies
| [Monday 15 November 2010] [07:23:58] <toni_>	mikko: yes the dev package seems to be installed: libstdc++6-4.4-dev is already the newest version.
| [Monday 15 November 2010] [07:24:52] <toni_>	build-essential I also installed
| [Monday 15 November 2010] [07:25:53] <toni_>	so my exact steps were: downloaded zmq from github, ran ./configure and then sudo make install which produced the error
| [Monday 15 November 2010] [07:26:47] <mikko>	toni_: if you download from github the steps should be
| [Monday 15 November 2010] [07:27:02] <mikko>	./autogen.sh && ./configure && make && make check
| [Monday 15 November 2010] [07:27:15] <mikko>	if all those success you should be ok to make install
| [Monday 15 November 2010] [07:28:40] <toni_>	mikko: okay :-) I finally got it
| [Monday 15 November 2010] [07:28:53] <toni_>	I just ran ./configure once again
| [Monday 15 November 2010] [07:29:08] <toni_>	an looks like it had been installed properly
| [Monday 15 November 2010] [07:29:18] <toni_>	Thank you very much for your help!!!
| [Monday 15 November 2010] [07:29:31] <mikko>	good st
| [Monday 15 November 2010] [07:29:38] <mikko>	strange error before
| [Monday 15 November 2010] [07:31:43] <toni_>	yes, strange one. Especially as I never compiled a C program before... so back to my beloved python :-)
| [Monday 15 November 2010] [07:31:54] <toni_>	Thanks 
| [Monday 15 November 2010] [09:42:40] <travlr>	sustrik: martin today is a bit tight for me. i'll get those logs hosted asap though.
| [Monday 15 November 2010] [09:45:16] <sustrik>	travlr: sure, no haste
| [Monday 15 November 2010] [11:02:02] <CIA-20>	zeromq2: 03Mikko Koppanen 07master * rda3327c 10/ (acinclude.m4 configure.in src/Makefile.am): 
| [Monday 15 November 2010] [11:02:02] <CIA-20>	zeromq2: Build refactoring
| [Monday 15 November 2010] [11:02:02] <CIA-20>	zeromq2: Signed-off-by: Mikko Koppanen <mkoppanen@php.net> - http://bit.ly/cBusWt
| [Monday 15 November 2010] [11:26:50] <frtewq>	hi
| [Monday 15 November 2010] [11:27:08] <mikko>	hi
| [Monday 15 November 2010] [11:27:24] <frtewq>	how r u?
| [Monday 15 November 2010] [14:08:59] <mikko>	sustrik: there?
| [Monday 15 November 2010] [14:09:05] <mikko>	all master builds succeed now
| [Monday 15 November 2010] [14:09:08] <mikko>	\o/
| [Monday 15 November 2010] [14:09:20] <mikko>	the patch you applied incorporates the previous smaller patch
| [Monday 15 November 2010] [14:09:25] <mikko>	at least my email says it does
| [Monday 15 November 2010] [14:13:26] <sustrik>	mikko: great
| [Monday 15 November 2010] [14:13:34] <sustrik>	what about the maint
| [Monday 15 November 2010] [14:13:35] <sustrik>	?
| [Monday 15 November 2010] [14:14:25] <sustrik>	maybe switching the failing configurations off?
| [Monday 15 November 2010] [14:14:40] <mikko>	yes
| [Monday 15 November 2010] [14:14:45] <mikko>	will do after dinner
| [Monday 15 November 2010] [14:14:47] <mikko>	brb
| [Monday 15 November 2010] [14:38:01] <mikko>	done
| [Monday 15 November 2010] [14:38:06] <mikko>	maint builds now without pgm
| [Monday 15 November 2010] [14:51:15] <mikko>	should build fine in the 5 am build
| [Monday 15 November 2010] [15:30:57] <mikko>	sustrik: sent
| [Monday 15 November 2010] [15:35:41] <sustrik>	mikko: repled :)
| [Monday 15 November 2010] [15:35:44] <sustrik>	replied
| [Monday 15 November 2010] [18:35:53] <Guthur>	is www.zeromq.org down
| [Tuesday 16 November 2010] [02:40:04] <pieterh>	hi folks
| [Tuesday 16 November 2010] [03:43:16] <15SAA31ZJ>	Does anybody have an idea how to switch of strict ansi 98 checking?
| [Tuesday 16 November 2010] [03:47:29] <15SAA31ZJ>	I checked the makefile for the dialect flags, but there aren't any
| [Tuesday 16 November 2010] [03:57:21] <sustrik>	15SAA31ZJ: i think you can get rid of it by turning the -Werror flag off
| [Tuesday 16 November 2010] [03:57:29] <sustrik>	it will still be reported
| [Tuesday 16 November 2010] [03:57:37] <sustrik>	but not treated as error anymore
| [Tuesday 16 November 2010] [04:00:16] <15SAA31ZJ>	Sorry, I was looking for std=c90 flag, but I now see the std=c99 flag, wiil remove that
| [Tuesday 16 November 2010] [04:01:36] <15SAA31ZJ>	Aargh, I still get the msg_store.cpp:253: error: ISO C++ 1998 does not support 'long long' error
| [Tuesday 16 November 2010] [04:10:03] <sustrik>	try the -Werror thing
| [Tuesday 16 November 2010] [04:11:39] <mikko>	15SAA31ZJ: is this with 2.1.0?
| [Tuesday 16 November 2010] [04:11:51] <mikko>	15SAA31ZJ: and are you building on mingw32?
| [Tuesday 16 November 2010] [04:13:49] <sustrik>	mikko: yes, he does
| [Tuesday 16 November 2010] [04:14:14] <15SAA31ZJ>	2.0.1, yes I'm building on mingw
| [Tuesday 16 November 2010] [04:15:55] <mikko>	hmm, we should allow turning werror off outside the build
| [Tuesday 16 November 2010] [04:16:15] <mikko>	rather than having to modify the configure.in and rebuilding configure
| [Tuesday 16 November 2010] [04:16:33] <sustrik>	we can turn it of only for mingw, no?
| [Tuesday 16 November 2010] [04:17:04] <sustrik>	the less manual configuration is needed the better imo
| [Tuesday 16 November 2010] [04:17:37] <mikko>	yes, we can turn it off
| [Tuesday 16 November 2010] [04:21:12] <mikko>	sustrik: this is the thing with __int64 being defined as long long in mingw32
| [Tuesday 16 November 2010] [04:21:55] <sustrik>	mikko: yes
| [Tuesday 16 November 2010] [04:22:08] <sustrik>	see issue 66 in bug tracker
| [Tuesday 16 November 2010] [04:27:11] <mikko>	can we not add mingw32 flag -Wno-long-long ?
| [Tuesday 16 November 2010] [04:27:27] <mikko>	i need to get my mingw32 running
| [Tuesday 16 November 2010] [04:28:07] <mikko>	and also add mingw32 build for the daily builds
| [Tuesday 16 November 2010] [04:42:43] <sustrik>	mikko: won't you need a win box for that?
| [Tuesday 16 November 2010] [04:43:23] <mikko>	sustrik: i can cross compile on linux
| [Tuesday 16 November 2010] [04:44:35] <sustrik>	ah
| [Tuesday 16 November 2010] [04:44:46] 	 * sustrik is a build noobie
| [Tuesday 16 November 2010] [04:46:52] <15SAA31ZJ>	I can define a long long var and it builds fine with the same mingw. Why am I getting this problem with zeromq?
| [Tuesday 16 November 2010] [04:47:28] <mikko>	15SAA31ZJ: -Werror -pedantic
| [Tuesday 16 November 2010] [04:47:43] <mikko>	if you add those to your test build it should fail
| [Tuesday 16 November 2010] [04:47:48] <mikko>	assuming you compile with g++
| [Tuesday 16 November 2010] [04:48:37] <15SAA31ZJ>	Ok, I removed -Werror from the makefile and I'm still get the error. Will strip -pedantic as well
| [Tuesday 16 November 2010] [04:49:24] <15SAA31ZJ>	Makes no difference
| [Tuesday 16 November 2010] [04:50:18] <mikko>	15SAA31ZJ: make sure that it's removed from all makefiles
| [Tuesday 16 November 2010] [04:52:36] <15SAA31ZJ>	Makefile.am, Makefile.in?
| [Tuesday 16 November 2010] [04:53:03] <mikko>	15SAA31ZJ: are you using dist package or git checkout?
| [Tuesday 16 November 2010] [04:55:13] <mikko>	sustrik: mingw32 is now in daily builds for master
| [Tuesday 16 November 2010] [04:55:28] <mikko>	i'll make a patch to fix the build
| [Tuesday 16 November 2010] [04:55:42] <sustrik>	mikko: thanks!
| [Tuesday 16 November 2010] [04:56:29] <15SAA31ZJ>	mikko: Thanks!
| [Tuesday 16 November 2010] [04:57:40] <mikko>	i think the cleanest fix is to define -Wno-long-long for mingw32
| [Tuesday 16 November 2010] [05:02:49] <w00t__>	hello
| [Tuesday 16 November 2010] [05:02:56] <sustrik>	hi
| [Tuesday 16 November 2010] [05:03:23] <w00t__>	ah, webchat... my employer will frown upon this:\
| [Tuesday 16 November 2010] [05:40:09] <15SAA31ZJ>	I don't want to sound more stupid than usual, but why does the compiler complain about a feature that is not part of the C++98 standard if the option to specify that compliance has to be checked has not been specified?
| [Tuesday 16 November 2010] [05:41:03] <mikko>	15SAA31ZJ: mingw32 complains because -pedantic is set
| [Tuesday 16 November 2010] [05:41:17] <mikko>	15SAA31ZJ: and -Werror converts the warning to error
| [Tuesday 16 November 2010] [05:41:45] <mikko>	15SAA31ZJ: i think i got a working fix for master branch
| [Tuesday 16 November 2010] [05:41:45] <15SAA31ZJ>	I understand that, but -std=c++98 has not been set...
| [Tuesday 16 November 2010] [05:41:54] <omarkj>	/join #CouchDB
| [Tuesday 16 November 2010] [05:41:54] <mikko>	15SAA31ZJ: -pedantic is
| [Tuesday 16 November 2010] [05:42:01] <omarkj>	Ups..Sorry about that.
| [Tuesday 16 November 2010] [05:42:10] <mikko>	15SAA31ZJ: it defaults to c++98 compliance
| [Tuesday 16 November 2010] [05:43:55] <mikko>	15SAA31ZJ: if you want to test the patch, take a checkout of git master and apply https://gist.github.com/28a725c30a6d0110e407
| [Tuesday 16 November 2010] [05:44:00] <mikko>	i gotta run for a minute
| [Tuesday 16 November 2010] [05:44:45] <15SAA31ZJ>	mikko: Ok, so c++98 is the default. This is still GCC, so why does this only affect mingw?
| [Tuesday 16 November 2010] [05:47:17] <mikko>	15SAA31ZJ: because mingw32 defines __int64_t as long long
| [Tuesday 16 November 2010] [05:48:10] <15SAA31ZJ>	mikko: which isn't valid?
| [Tuesday 16 November 2010] [05:48:25] <mikko>	15SAA31ZJ: not for pedantic c++98 compliance
| [Tuesday 16 November 2010] [05:48:45] <mikko>	it's valid for C but not for C++
| [Tuesday 16 November 2010] [05:48:57] <15SAA31ZJ>	mikko: Ok, thanks!
| [Tuesday 16 November 2010] [07:28:01] <15SAA31ZJ>	mikko: Sorry for being difficult, but I still don't know how to fix my mingw build...\
| [Tuesday 16 November 2010] [07:29:18] <sustrik>	the patch doesn't help?
| [Tuesday 16 November 2010] [07:29:40] <sustrik>	what error are you getting now?
| [Tuesday 16 November 2010] [07:29:53] <mato>	sustrik: hi
| [Tuesday 16 November 2010] [07:29:58] <sustrik>	mato: hi
| [Tuesday 16 November 2010] [07:30:06] <mato>	guys, master on mingw is broken in other ways
| [Tuesday 16 November 2010] [07:30:16] <mato>	due to __declspec stuff
| [Tuesday 16 November 2010] [07:30:30] <mato>	I went through this on Sunday, will fix it properly today or tomorrow
| [Tuesday 16 November 2010] [07:30:52] <mato>	for the __int64 issue all that needs to be done is that mingw builds use -Wno-long-long
| [Tuesday 16 November 2010] [07:31:00] <mato>	I'll make a separate patch for that shortly
| [Tuesday 16 November 2010] [07:31:35] <sustrik>	ok
| [Tuesday 16 November 2010] [07:32:02] <15SAA31ZJ>	mikko released a patch, which looks like it patches the configure script. Which I don't seem to have when I get the git master.
| [Tuesday 16 November 2010] [07:32:07] <mikko>	mato: i got it to build (didnt test running)
| [Tuesday 16 November 2010] [07:32:27] <mikko>	mato: and while cross compiling i still had weird failure -Wno-long-long
| [Tuesday 16 November 2010] [07:32:37] <mikko>	had to werror=no
| [Tuesday 16 November 2010] [07:32:48] <mato>	mikko: we can go through it in a bit and sort things out
| [Tuesday 16 November 2010] [07:33:15] <mikko>	cool
| [Tuesday 16 November 2010] [07:33:24] <mikko>	i got a few other build related patches as well
| [Tuesday 16 November 2010] [07:34:56] <mikko>	http://valokuva.org/~mikko/b/
| [Tuesday 16 November 2010] [07:35:01] <mikko>	got a bit carried away
| [Tuesday 16 November 2010] [07:35:09] <mikko>	lunch time, bbl
| [Tuesday 16 November 2010] [08:04:13] <CIA-20>	zeromq2: 03Martin Sustrik 07maint * r152c64f 10/ builds/msvc/libzmq/libzmq.vcproj : 
| [Tuesday 16 November 2010] [08:04:14] <CIA-20>	zeromq2: FD_SETSIZE defaults to 1024 in MSVC build
| [Tuesday 16 November 2010] [08:04:14] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/bcchqf
| [Tuesday 16 November 2010] [08:08:43] <15SAA31ZJ>	At the end of a build on mingw I get this:
| [Tuesday 16 November 2010] [08:08:45] <15SAA31ZJ>	make[2]: *** [libzmq_la-zmq.lo] Error 1
| [Tuesday 16 November 2010] [08:08:45] <15SAA31ZJ>	make[2]: Leaving directory `/c/Projects/zeromq-2.0.10/src'
| [Tuesday 16 November 2010] [08:08:45] <15SAA31ZJ>	make[1]: *** [all] Error 2
| [Tuesday 16 November 2010] [08:08:45] <15SAA31ZJ>	make[1]: Leaving directory `/c/Projects/zeromq-2.0.10/src'
| [Tuesday 16 November 2010] [08:08:45] <15SAA31ZJ>	make: *** [all-recursive] Error 1
| [Tuesday 16 November 2010] [08:08:57] <15SAA31ZJ>	What does that mean?
| [Tuesday 16 November 2010] [08:09:51] <mato>	15SAA31ZJ: It's the ZMQ_EXPORT stuff that's broken
| [Tuesday 16 November 2010] [08:10:08] <mato>	15SAA31ZJ: I will fix that, but not immediately (reinstalling Windows VM, etc etc)
| [Tuesday 16 November 2010] [08:10:50] <15SAA31ZJ>	mato: Ok, is that the _declspec issue... Thanks
| [Tuesday 16 November 2010] [08:10:58] <mato>	15SAA31ZJ: yes.
| [Tuesday 16 November 2010] [08:11:27] <mato>	15SAA31ZJ: although I thought it only affected master, but if 2.0.10 is failing that way for you then I guess it affects both.
| [Tuesday 16 November 2010] [08:13:02] <mato>	15SAA31ZJ: IIRC a quick but suboptimal fix is to edit the definition of ZMQ_EXPORT in include/zmq.h and include/zmq_util.h
| [Tuesday 16 November 2010] [08:13:07] <mato>	Where you have:
| [Tuesday 16 November 2010] [08:13:11] <mato>	#   if defined DLL_EXPORT
| [Tuesday 16 November 2010] [08:13:12] <mato>	#       define ZMQ_EXPORT __declspec(dllexport)
| [Tuesday 16 November 2010] [08:13:12] <mato>	#   else
| [Tuesday 16 November 2010] [08:13:12] <mato>	#       define ZMQ_EXPORT __declspec(dllimport)
| [Tuesday 16 November 2010] [08:13:12] <mato>	#   endif
| [Tuesday 16 November 2010] [08:13:25] <mato>	Change the #else to just define ZMQ_EXPORT to nothing
| [Tuesday 16 November 2010] [08:13:43] <mato>	that might work, if not optimally
| [Tuesday 16 November 2010] [08:14:18] <mato>	but it needs to be fixed properly
| [Tuesday 16 November 2010] [08:14:43] <CIA-20>	zeromq2: 03Martin Sustrik 07master * rbd0ecf4 10/ builds/msvc/libzmq/libzmq.vcproj : 
| [Tuesday 16 November 2010] [08:14:43] <CIA-20>	zeromq2: FD_SETSIZE defaults to 1024 in MSVC build
| [Tuesday 16 November 2010] [08:14:43] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/bYT47b
| [Tuesday 16 November 2010] [08:32:25] <mikko>	back
| [Tuesday 16 November 2010] [08:39:52] <15SAA31ZJ>	mato: Thanks, I will try
| [Tuesday 16 November 2010] [08:48:12] <mato>	mikko: i'm in the middle of reinstalling my windows vm... once that's done i can start looking at mingw
| [Tuesday 16 November 2010] [08:49:45] <mikko>	mato: cool, ill fix some ws issues on the patches
| [Tuesday 16 November 2010] [09:06:53] <mikko>	mato: http://valokuva.org/~mikko/b/
| [Tuesday 16 November 2010] [09:06:54] <mikko>	there
| [Tuesday 16 November 2010] [09:07:01] <mikko>	reformatted the whitespace errors
| [Tuesday 16 November 2010] [09:07:22] <mikko>	and changed the mingw32 build to do no-long-long
| [Tuesday 16 November 2010] [09:08:05] <mato>	will take a look shortly thx
| [Tuesday 16 November 2010] [09:26:16] <mato>	T3dshw00
| [Tuesday 16 November 2010] [09:26:23] <mato>	oops
| [Tuesday 16 November 2010] [09:37:12] <15SAA31ZJ>	mato: I changed the definition of ZMQ_EXPORT, but I'm still getting the build errors
| [Tuesday 16 November 2010] [09:39:27] <15SAA31ZJ>	mato: Oops, looks like I didn't save zmq.h. Rebuilding now
| [Tuesday 16 November 2010] [09:40:58] <15SAA31ZJ>	mato: No, still same errors!
| [Tuesday 16 November 2010] [09:45:43] <mato>	15SAA31ZJ: Sorry, maybe that's not the whole solution. it was just what I roughly remembered how I made it work on Sunday
| [Tuesday 16 November 2010] [09:45:55] <mato>	15SAA31ZJ: I've almost got Windows and all the bits installed, will look into it
| [Tuesday 16 November 2010] [09:46:26] <15SAA31ZJ>	mato: Ok, thanks
| [Tuesday 16 November 2010] [10:07:15] <mato>	mikko: ok, you still here?
| [Tuesday 16 November 2010] [10:10:13] <mikko>	mato: yes
| [Tuesday 16 November 2010] [10:10:19] <mikko>	installing centos 
| [Tuesday 16 November 2010] [10:10:39] <mato>	mikko: looking quickly over your patches, have yet to actually test them
| [Tuesday 16 November 2010] [10:10:56] <mato>	mikko: 0001-0005 looks fine, I'm not sure of any added value in 0006
| [Tuesday 16 November 2010] [10:11:04] <mato>	mikko: (moving the PGM stuff into a macro)
| [Tuesday 16 November 2010] [10:11:11] <mato>	mikko: that just hides it...
| [Tuesday 16 November 2010] [10:11:37] <mato>	mikko: also, re 0004 - removing LIBZMQ_EXTRA_...
| [Tuesday 16 November 2010] [10:11:39] <mikko>	mato: it's not mandatory if you don't see value
| [Tuesday 16 November 2010] [10:11:54] <mikko>	the LIBZMQ_EXTRA_LDFLAGS is not used anywhere
| [Tuesday 16 November 2010] [10:12:08] <mikko>	LIBZMQ_EXTRA_CXXFLAGS is/was used for CFLAGS as well
| [Tuesday 16 November 2010] [10:12:46] <mato>	mikko: sure, but the EXTRA_XXXFLAGS are there for a reason; when building the perf tests, self tests, devices, etc. you do not need or want to build with all the extra stuff that goes into the EXTRA_XXXFLAGS
| [Tuesday 16 November 2010] [10:13:04] <mikko>	EXTRA_CXXFLAGS gets appended after CPPFLAGS?
| [Tuesday 16 November 2010] [10:13:08] <mato>	mikko: the EXTRA flags are there so that we can separate this stuff
| [Tuesday 16 November 2010] [10:13:18] <mikko>	because that would prevent user from overriding CPPFLAGS for the build
| [Tuesday 16 November 2010] [10:14:11] <mato>	that's true
| [Tuesday 16 November 2010] [10:14:48] <mikko>	but i guess it's two-sided sword
| [Tuesday 16 November 2010] [10:14:49] <mato>	but i'd still like to somehow separate the build flags required for libzmq vs. the build flags required for everything else
| [Tuesday 16 November 2010] [10:15:17] <mikko>	i can look into that maybe
| [Tuesday 16 November 2010] [10:15:28] <mikko>	i would like user to be able to override flags with CFLAGS and CPPFLAGS
| [Tuesday 16 November 2010] [10:16:02] <mikko>	maybe something like not reset the EXTRA_ flags in the beginning of build ?
| [Tuesday 16 November 2010] [10:16:09] <mikko>	i can look into it
| [Tuesday 16 November 2010] [10:16:12] <mato>	possibly
| [Tuesday 16 November 2010] [10:16:55] <mikko>	0005 is just handy when hacking the builds
| [Tuesday 16 November 2010] [10:17:07] <mato>	how so?
| [Tuesday 16 November 2010] [10:17:22] <mikko>	if i got xmlto and asciidoc it always builds the docs
| [Tuesday 16 November 2010] [10:17:29] <mikko>	which takes a lot more time on my small vm
| [Tuesday 16 November 2010] [10:17:34] <mato>	oh, that, yes, sorry
| [Tuesday 16 November 2010] [10:17:36] <mato>	0005 is fine
| [Tuesday 16 November 2010] [10:18:04] <mikko>	let's keep the PGM where it is if you find it cleaner
| [Tuesday 16 November 2010] [10:18:20] <mikko>	but the small part: -if test "x$gnu_compilers" = "xyes" -a "x$pgm_ext" = "xno"; then
| [Tuesday 16 November 2010] [10:18:44] <mikko>	i think it's clearer if there is pedantic=no werror=no inside the pgm build
| [Tuesday 16 November 2010] [10:19:08] <mikko>	as those flags are already checked below
| [Tuesday 16 November 2010] [10:19:31] <mato>	i'm not sure if some obscure platform doesn't need werror=no pedantic=no even for a non-PGM build
| [Tuesday 16 November 2010] [10:20:00] <mikko>	mato: i agree with that
| [Tuesday 16 November 2010] [10:20:19] <mato>	sorry, it's been a while since i looked at all that stuff
| [Tuesday 16 November 2010] [10:20:39] <mikko>	currently the condition at the end is:
| [Tuesday 16 November 2010] [10:20:40] <mikko>	if test "x$gnu_compilers" = "xyes" -a "x$pgm_ext" = "xno"; then
| [Tuesday 16 November 2010] [10:20:40] 	 * mato needs to swap in context "auto-kung-fu" :-)
| [Tuesday 16 November 2010] [10:21:00] <mikko>	i think we could just set werror="no" and pedantic="no" if pgm is selected
| [Tuesday 16 November 2010] [10:21:06] <mikko>	and remove  -a "x$pgm_ext" = "xno"
| [Tuesday 16 November 2010] [10:21:18] <mato>	oh, right, sure
| [Tuesday 16 November 2010] [10:21:21] <mato>	yes, that makes sense
| [Tuesday 16 November 2010] [10:21:40] <mikko>	so it's aligned with the rest of the build
| [Tuesday 16 November 2010] [10:22:06] <mikko>	brb
| [Tuesday 16 November 2010] [11:27:17] <mikko>	mm
| [Tuesday 16 November 2010] [11:27:26] <mikko>	mato: seen this before /usr/bin/ld: .libs/libzmq_la-txwi.o: relocation R_X86_64_PC32 against `pgm_rs_create' can not be used when making a shared object; recompile with -fPIC
| [Tuesday 16 November 2010] [11:27:46] <mikko>	i got that if i try to build on centos 5.5 x86_64 from release 2.0.10
| [Tuesday 16 November 2010] [11:28:06] <mikko>	if i get maint from github and generate cofnigure on the machine things seem to work fine
| [Tuesday 16 November 2010] [11:28:32] <mato>	mikko: oh, yeah, old and known issue
| [Tuesday 16 November 2010] [11:28:44] <mato>	mikko: there's some ancient thread on the ML about it
| [Tuesday 16 November 2010] [11:29:03] <mato>	mikko: I forget exactly what the details are, but I think it boils down to a RHAT gcc bug
| [Tuesday 16 November 2010] [11:29:17] <mato>	anyhow, I have windows + mingw and friends installed now
| [Tuesday 16 November 2010] [11:29:38] <mato>	probably won't do much more with it today, tomorrow I'll look at fixing the ZMQ_EXPORT stuff which is breaking the mingw build
| [Tuesday 16 November 2010] [11:30:16] <mato>	mikko: You actually managed to build 'master' with mingw on Windows, or was that just a cross-build?
| [Tuesday 16 November 2010] [11:30:45] <mikko>	mato: cross-compile
| [Tuesday 16 November 2010] [11:30:55] <mikko>	where does it fail?
| [Tuesday 16 November 2010] [11:31:03] <mato>	it's complicated
| [Tuesday 16 November 2010] [11:31:06] <mato>	what happens is
| [Tuesday 16 November 2010] [11:31:34] <mato>	on master you get a mysterious "Error 1" when libtool tries to build deps for zmq.o
| [Tuesday 16 November 2010] [11:31:53] <mikko>	i had that
| [Tuesday 16 November 2010] [11:31:57] <mato>	if you run the actual command by hand and discard the >/dev/null libtool is doing you get the actual error
| [Tuesday 16 November 2010] [11:32:07] <mikko>	changing to werror="no" on mingw32 sorted that issue
| [Tuesday 16 November 2010] [11:32:21] <mato>	hmm, interesting
| [Tuesday 16 November 2010] [11:32:30] <mato>	I guess I didn't realise it was just a warning
| [Tuesday 16 November 2010] [11:32:35] <mikko>	i got the build just stopping without visible error message
| [Tuesday 16 November 2010] [11:32:46] <mato>	yes, let me dig up the actual error
| [Tuesday 16 November 2010] [11:32:46] <mikko>	i changed to werror="no" and it build
| [Tuesday 16 November 2010] [11:32:50] <mikko>	s/build/built/
| [Tuesday 16 November 2010] [11:33:28] <mikko>	i didn't get the error out even when i ran the command without 2>&1 in the src/ dir
| [Tuesday 16 November 2010] [11:33:56] <mato>	you can get it
| [Tuesday 16 November 2010] [11:34:23] <mato>	here's the actual error:
| [Tuesday 16 November 2010] [11:34:26] <mato>	$ g++ -DHAVE_CONFIG_H -I. -Werror -pedantic -Wall -Wno-long-long -D_REENTRANT -
| [Tuesday 16 November 2010] [11:34:26] <mato>	D_THREAD_SAFE -g -O2 -MT libzmq_la-zmq.lo -MD -MP -MF .deps/libzmq_la-zmq.Tpo -
| [Tuesday 16 November 2010] [11:34:27] <mato>	c zmq.cpp -o libzmq_la-zmq.o
| [Tuesday 16 November 2010] [11:34:27] <mato>	cc1plus.exe: warnings being treated as errors
| [Tuesday 16 November 2010] [11:34:27] <mato>	zmq.cpp: In function 'void zmq_version(int*, int*, int*)':
| [Tuesday 16 November 2010] [11:34:29] <mato>	zmq.cpp:63:6: error: 'void zmq_version(int*, int*, int*)' redeclared without dll
| [Tuesday 16 November 2010] [11:34:32] <mato>	import attribute: previous dllimport ignored
| [Tuesday 16 November 2010] [11:34:54] <mato>	i'm not quite sure what is happening here
| [Tuesday 16 November 2010] [11:35:37] <mikko>	signature / implementation defined with different attributes?
| [Tuesday 16 November 2010] [11:35:50] <mato>	well, here's the way it *should* work on windows:
| [Tuesday 16 November 2010] [11:36:08] <mato>	If you're building libzmq as a DLL, DLL_EXPORT is defined (libtool does that, and so does the MSVC project)
| [Tuesday 16 November 2010] [11:36:27] <mato>	then, when you include zmq.h, ZMQ_EXPORT gets defined as __declspec(dllexport)
| [Tuesday 16 November 2010] [11:36:33] <mato>	this is all fine
| [Tuesday 16 November 2010] [11:36:55] <mato>	for windows *users* of the API, DLL_EXPORT is not defined, and ZMQ_EXPORT gets defined as __declspec(dllimport)
| [Tuesday 16 November 2010] [11:37:11] <mato>	but libtool is doing something funny (I presume that step is dependency generation)
| [Tuesday 16 November 2010] [11:37:17] <mato>	and it breaks
| [Tuesday 16 November 2010] [11:37:48] <mikko>	i presume i can reproduce this using my cross compile
| [Tuesday 16 November 2010] [11:37:53] <mikko>	and removing the werror 
| [Tuesday 16 November 2010] [11:37:55] <mikko>	let's see
| [Tuesday 16 November 2010] [11:38:05] <mato>	I'd assume so
| [Tuesday 16 November 2010] [11:39:50] <mikko>	daily builds have mingw32 build now as well
| [Tuesday 16 November 2010] [11:39:53] <mikko>	cross compile
| [Tuesday 16 November 2010] [11:40:04] <mato>	oh, great 
| [Tuesday 16 November 2010] [11:41:47] <mikko>	https://gist.github.com/ea5b88352f61c26758b2
| [Tuesday 16 November 2010] [11:41:53] <mikko>	this is the first thing that goes south
| [Tuesday 16 November 2010] [11:42:04] <mikko>	adding the no-long-long patch
| [Tuesday 16 November 2010] [11:47:31] <mikko>	mato: https://gist.github.com/ea5b88352f61c26758b2#comments
| [Tuesday 16 November 2010] [11:47:39] <mikko>	that is what the cross compilation gives
| [Tuesday 16 November 2010] [11:48:04] <mato>	yup, thats what i see
| [Tuesday 16 November 2010] [11:48:12] <mato>	the question is, what to do about it
| [Tuesday 16 November 2010] [11:48:24] <mato>	turning off -Werror is not a fix, it just hides the problem
| [Tuesday 16 November 2010] [11:49:08] <mikko>	yes, that is correct
| [Tuesday 16 November 2010] [11:49:34] <mato>	d'you know much about libtool internals?
| [Tuesday 16 November 2010] [11:49:51] <mato>	I don't entirely understand what the aim of that compilation actually is
| [Tuesday 16 November 2010] [11:49:53] <mikko>	the signature is not defined with ZMQ_EXPORT
| [Tuesday 16 November 2010] [11:49:57] <mikko>	ermm
| [Tuesday 16 November 2010] [11:50:02] <mikko>	the implementation
| [Tuesday 16 November 2010] [11:50:11] <mikko>	does it need to match in both?
| [Tuesday 16 November 2010] [11:51:01] <mato>	see here:\
| [Tuesday 16 November 2010] [11:51:15] <mato>	http://msdn.microsoft.com/en-us/library/9h658af8%28v=VS.80%29.aspx
| [Tuesday 16 November 2010] [11:51:20] <mato>	http://msdn.microsoft.com/en-us/library/a90k134d%28VS.80%29.aspx
| [Tuesday 16 November 2010] [11:53:46] <mato>	mikko: note that all of this also needs to be done on POSIX platforms; we've just been ignoring it until now
| [Tuesday 16 November 2010] [11:54:04] <mato>	what I want to do on other platforms is build with -fvisibility=hidden
| [Tuesday 16 November 2010] [11:54:31] <mato>	and then define ZMQ_EXPORT for the libzmq shared build to set the per-function visibility to default
| [Tuesday 16 November 2010] [11:56:50] <mato>	mikko: anyway, i'll have to go soon; will you be around tomorrow?
| [Tuesday 16 November 2010] [11:57:44] <mikko>	mato: yes, most probably will be
| [Tuesday 16 November 2010] [11:58:05] <mikko>	ill tinker with mingw32 build
| [Tuesday 16 November 2010] [11:58:29] <mato>	ok, let me know by email if you figure out anything, otherwise i'll continue tomorrow and get it working...
| [Tuesday 16 November 2010] [11:59:43] <mikko>	sure
| [Tuesday 16 November 2010] [11:59:54] <mikko>	talk to you tomorrow
| [Tuesday 16 November 2010] [12:00:16] <mato>	ack; i'm still here, but leaving in 1/2 an hour
| [Tuesday 16 November 2010] [12:35:09] <mikko>	mato: i got it to build
| [Tuesday 16 November 2010] [12:42:13] <mikko>	but not yet there
| [Tuesday 16 November 2010] [15:54:11] <oink>	Hello zmq people. Small question for you: I'm trying to write a 'friendly' cpp class that uses zmq, and find that there are asserts that make this difficult.
| [Tuesday 16 November 2010] [15:55:36] <oink>	e.g. rc = socket.recv(&msg)   ... has a nice rc for errors, but if (stupidly) binding to a non existent host, then kaboom!
| [Tuesday 16 November 2010] [15:56:46] <oink>	in this case the assert in the zmq_connecter_t constructor, and is correctly noticing that the host does not exist
| [Tuesday 16 November 2010] [15:58:16] <mikko>	mato: i think i nailed it (at least partially)
| [Tuesday 16 November 2010] [15:59:17] <oink>	It seems that an application developer is required to ultra-validate any input before sending into zmq - although acceptable, it seems a shame to repeat the validation
| [Tuesday 16 November 2010] [15:59:37] <mikko>	oink: i think 0MQ is moving away from asserts one by one
| [Tuesday 16 November 2010] [16:00:26] <mikko>	i remember seeing discussion about this
| [Tuesday 16 November 2010] [16:00:37] <oink>	thanks, that is comforting to know
| [Tuesday 16 November 2010] [16:17:18] <dcadenas>	hi guys, I'm an zeromq newbie, can anyone tell me if it lets me see the content of each message without consuming it? I think that other alternatives like rabbitmq don't let doing that
| [Tuesday 16 November 2010] [16:17:55] <mikko>	dcadenas: you need to consume the message to see the contents
| [Tuesday 16 November 2010] [16:17:57] <cremes>	dcadenas: no, there is no "peek"
| [Tuesday 16 November 2010] [16:18:04] <dcadenas>	ah ok thanks
| [Tuesday 16 November 2010] [23:52:50] <pen>	hey
| [Wednesday 17 November 2010] [04:32:38] <kobus>	Hi
| [Wednesday 17 November 2010] [04:33:15] <kobus>	I downloaded the git master just now. Has the mingw fixes been incorporated yet?
| [Wednesday 17 November 2010] [04:36:00] <kobus>	And the git master does not contain a configure script and I can't run autogen.sh
| [Wednesday 17 November 2010] [04:36:30] <sustrik>	kobus: no, the mingw fixes are not yet there
| [Wednesday 17 November 2010] [04:36:40] <sustrik>	mato's going to work on that today, afaik
| [Wednesday 17 November 2010] [04:37:46] <kobus>	sustrik: Ok, I'm running out of time on a concept demonstrator. I will have to move on to another messaging lib. Any suggestions :-(
| [Wednesday 17 November 2010] [04:41:23] <sustrik>	depends on what you need
| [Wednesday 17 November 2010] [04:44:25] <kobus>	sustrik: I want a distributed notification mechanism with apps subscribing to specific notifications and also generate notifications
| [Wednesday 17 November 2010] [04:52:55] <mikko>	kobus: i can give you fix to test
| [Wednesday 17 November 2010] [04:55:48] <kobus>	mikko: Great
| [Wednesday 17 November 2010] [04:56:26] <mikko>	http://valokuva.org/~mikko/zeromq-2.1.0-mingw32.zip
| [Wednesday 17 November 2010] [04:56:33] <mikko>	fresh from the oven
| [Wednesday 17 November 2010] [04:56:50] <mikko>	when you link against the generated DLL define LIBZMQ_DLL_IMPORT 
| [Wednesday 17 November 2010] [04:57:19] <mikko>	i haven't yet tested this on windows, only cross compilation build
| [Wednesday 17 November 2010] [05:01:03] <kobus>	mikko: I will try it. Thanks!
| [Wednesday 17 November 2010] [05:01:10] <mikko>	let me know how it goes
| [Wednesday 17 November 2010] [05:06:09] <mato>	back
| [Wednesday 17 November 2010] [05:08:56] <mikko>	mato: did you see my email?
| [Wednesday 17 November 2010] [05:09:04] <mato>	mikko: yes, going to look at it
| [Wednesday 17 November 2010] [05:09:47] <mikko>	mato: either we define a new define in our build saying "LIBZMQ_BUILDING" or let user define a constant when they link
| [Wednesday 17 November 2010] [05:10:10] <mikko>	because the static library build mingw32 does ends up using dllimport 
| [Wednesday 17 November 2010] [05:10:32] <mikko>	which is not correct afaik. i understood that dllimport should be used when the DLL is linked against
| [Wednesday 17 November 2010] [05:10:45] <mato>	correct
| [Wednesday 17 November 2010] [05:11:21] <mikko>	but in the current code we end up using dllimport for static build
| [Wednesday 17 November 2010] [05:11:30] <mikko>	because DLL_EXPORT is not defined for static build
| [Wednesday 17 November 2010] [05:11:34] <mikko>	(no pic)
| [Wednesday 17 November 2010] [05:11:42] <mato>	do we care about the static library on win32 at all?
| [Wednesday 17 November 2010] [05:12:04] <mikko>	mingw32 static library on win32 can only be used with ming32 binaries
| [Wednesday 17 November 2010] [05:12:08] <mato>	precisely
| [Wednesday 17 November 2010] [05:12:16] <mato>	which really is a minority use case
| [Wednesday 17 November 2010] [05:12:17] <mikko>	we could use AC_DISABLE_STATIC
| [Wednesday 17 November 2010] [05:12:28] <mato>	99% of windows developers just want a DLL they can link with
| [Wednesday 17 November 2010] [05:12:34] <mato>	the other 1% can go figure it out themselves
| [Wednesday 17 November 2010] [05:13:11] <mikko>	this probably affects cygwin build as well
| [Wednesday 17 November 2010] [05:13:38] <mato>	that is such a minority inside a minority that i really don't care too much, at least not right now
| [Wednesday 17 November 2010] [05:13:56] <mikko>	are we right to assume that if DLL_EXPORT is not defined we are linking against a dll? I think not
| [Wednesday 17 November 2010] [05:14:08] <mikko>	as you might compile statically using MSVC 
| [Wednesday 17 November 2010] [05:14:21] <mato>	the MSVC project defines DLL_EXPORT
| [Wednesday 17 November 2010] [05:14:31] <mato>	the thing is, we can't solve all of these cases elegantly
| [Wednesday 17 November 2010] [05:14:37] <mato>	so let's solve the "joe user" case
| [Wednesday 17 November 2010] [05:14:42] <mikko>	that is true
| [Wednesday 17 November 2010] [05:14:51] <mato>	which is, zmq being built as a DLL, application linking against a DLL
| [Wednesday 17 November 2010] [05:14:55] <mikko>	disable static build for cygwin and mingw32
| [Wednesday 17 November 2010] [05:15:01] <mato>	yes
| [Wednesday 17 November 2010] [05:15:15] <mato>	and we don't ship MSVC static build projects either so that is not an issue right now
| [Wednesday 17 November 2010] [05:15:24] <mikko>	i think AC_DISABLE_STATIC needs to be called before AC_PROG_LIBTOOL
| [Wednesday 17 November 2010] [05:15:40] <mikko>	i can produce a patch for this if you like
| [Wednesday 17 November 2010] [05:15:47] <mato>	we need to do two things.
| [Wednesday 17 November 2010] [05:15:51] <mato>	1. AC_DISABLE_STATIC
| [Wednesday 17 November 2010] [05:16:08] <mato>	2. test if the user force-enabled static and stop with an error
| [Wednesday 17 November 2010] [05:16:24] <mato>	telling them outright that static builds are not supported
| [Wednesday 17 November 2010] [05:17:46] <mato>	mikko: well, i can try and make a patch, i have native mingw on win2k3 working now
| [Wednesday 17 November 2010] [05:18:13] <mato>	so we're agreed that the best approach is to disable static builds entirely?
| [Wednesday 17 November 2010] [05:19:10] <mato>	mikko: or you make the patch, since you've already got that patch series in progress, and i'll test it
| [Wednesday 17 November 2010] [05:19:13] <mato>	up to you
| [Wednesday 17 November 2010] [05:19:25] <mikko>	mato: i can do the patch
| [Wednesday 17 November 2010] [05:19:55] <mato>	ok. let me know when it's ready and i'll test it
| [Wednesday 17 November 2010] [05:20:15] <mato>	so there should be no need to change the definition of ZMQ_EXPORT?
| [Wednesday 17 November 2010] [05:25:16] <mikko>	no need
| [Wednesday 17 November 2010] [05:25:26] <mikko>	if we assume that link is against dll
| [Wednesday 17 November 2010] [05:25:40] <mato>	ok, good
| [Wednesday 17 November 2010] [05:25:53] <mato>	sustrik: you following this at all?
| [Wednesday 17 November 2010] [05:26:20] <sustrik>	slightly
| [Wednesday 17 November 2010] [05:26:30] <mikko>	mato: found a possible autoconf annoyance on the way
| [Wednesday 17 November 2010] [05:26:38] <sustrik>	i don't understand it much
| [Wednesday 17 November 2010] [05:26:47] <mato>	sustrik: the outcome is, we want to disable static library builds for Mingw
| [Wednesday 17 November 2010] [05:26:57] <mato>	sustrik: because it's impossible to support them elegantly
| [Wednesday 17 November 2010] [05:27:15] <mato>	sustrik: our assumption is that 99% of windows developers only ever want a DLL anyway
| [Wednesday 17 November 2010] [05:27:26] <sustrik>	sure, nobody uses static libs on win today anyway
| [Wednesday 17 November 2010] [05:27:27] <mato>	mikko: what's that?
| [Wednesday 17 November 2010] [05:27:34] <mato>	sustrik: ok, so we'll officially disallow that
| [Wednesday 17 November 2010] [05:27:39] <sustrik>	ok
| [Wednesday 17 November 2010] [05:27:41] <mato>	sustrik: since the alternative is not worth the effort
| [Wednesday 17 November 2010] [05:31:52] <mikko>	mato: AC_DISABLE_STATIC doesn't play nice in a conditional
| [Wednesday 17 November 2010] [05:33:34] <mato>	mikko: ah, as in inside an if statement?
| [Wednesday 17 November 2010] [05:33:58] <sustrik>	Guthur: hi, there's an email at ML that looks like related to clrzmq2
| [Wednesday 17 November 2010] [05:34:12] <sustrik>	"System.AccessViolationException with multiple	subscriptions"
| [Wednesday 17 November 2010] [05:34:43] <Guthur>	sustrik, cheers, I didn't get to check my emails this morning, I will check it out
| [Wednesday 17 November 2010] [05:35:45] <sustrik>	thx
| [Wednesday 17 November 2010] [05:36:01] <mikko>	mato: yes
| [Wednesday 17 November 2010] [05:38:58] <mato>	mikko: this seems to suggest it at least sort of works:
| [Wednesday 17 November 2010] [05:39:00] <mato>	http://www.mail-archive.com/libtool-patches@gnu.org/msg02686.html
| [Wednesday 17 November 2010] [05:40:37] <Guthur>	sustrik, Not the most descriptive ticket ever, hehe
| [Wednesday 17 November 2010] [05:40:44] <mikko>	mato: saw that
| [Wednesday 17 November 2010] [05:41:15] <sustrik>	Guthur: yeah, i'm not even sure it's clrzmq2
| [Wednesday 17 November 2010] [05:41:17] <mikko>	mato: i'll send you what i got
| [Wednesday 17 November 2010] [05:41:24] <mikko>	mato: in theory this should work
| [Wednesday 17 November 2010] [05:41:33] <mikko>	but it disables static build for everything
| [Wednesday 17 November 2010] [05:42:01] <Guthur>	sustrik, I'm at work at the moment so I may have to wait until I get home before getting very far with it
| [Wednesday 17 November 2010] [05:42:18] <Guthur>	I can't post to the ML from here
| [Wednesday 17 November 2010] [05:42:29] <sustrik>	Guthur: sure, no haste
| [Wednesday 17 November 2010] [05:43:01] <mikko>	mato: looks like i need AC_ENABLE_STATIC for the non cygwin/mingw32 branch
| [Wednesday 17 November 2010] [05:43:26] <mato>	mikko: :-(, ok but how does that interact with what the user asks for on the command line?
| [Wednesday 17 November 2010] [05:43:59] <mikko>	mato: command line overrides that
| [Wednesday 17 November 2010] [05:46:48] <mato>	mikko: my main concern is that at least some people on *NIX like to build with --disable-shared, e.g. when developing
| [Wednesday 17 November 2010] [05:47:17] <mato>	anyway, we can try all the sane combinations and see what happens
| [Wednesday 17 November 2010] [05:50:00] <sustrik>	mato, mikko: --disable-shared should work on *nix
| [Wednesday 17 November 2010] [05:50:08] <sustrik>	debugging without it is a pain
| [Wednesday 17 November 2010] [05:50:31] <mato>	sustrik: yes, yes, of course, by "some people" I meant precisely you :-)
| [Wednesday 17 November 2010] [05:50:35] <sustrik>	:)
| [Wednesday 17 November 2010] [05:52:02] <mikko>	mato: https://gist.github.com/486c939595caf56a50e5
| [Wednesday 17 November 2010] [05:52:07] <mikko>	slightly weird at the moment
| [Wednesday 17 November 2010] [05:52:11] <mikko>	but seems to work
| [Wednesday 17 November 2010] [05:52:16] <mikko>	just need to clean up a bit
| [Wednesday 17 November 2010] [05:55:28] <mato>	ok, am going to test
| [Wednesday 17 November 2010] [05:56:23] <sustrik>	mikko, mato: i've sent the proposal to make mikko a maintainer
| [Wednesday 17 November 2010] [05:56:43] <sustrik>	if nobody objects, we'll move on with it
| [Wednesday 17 November 2010] [06:00:05] <mato>	mikko: you're missing a "test" on line 56
| [Wednesday 17 November 2010] [06:00:17] <mato>	mikko: it should read "if test "x$enable..."
| [Wednesday 17 November 2010] [06:03:13] <mikko>	mato: that part is a bit shady anyway
| [Wednesday 17 November 2010] [06:03:16] <mikko>	if you look carefully
| [Wednesday 17 November 2010] [06:03:33] <mikko>	it checks enable_static and errors out before AC_PROG_LIBTOOL has been called
| [Wednesday 17 November 2010] [06:03:39] <mikko>	not very logical
| [Wednesday 17 November 2010] [06:07:30] <mato>	mikko: yes, i'm just inspecting the configure output
| [Wednesday 17 November 2010] [06:07:49] <mato>	mikko: it doesn't look entirely happy
| [Wednesday 17 November 2010] [06:08:04] <kobus>	mikko: Thanks, look like it builds ok. I just get an error: g++.exe: C:/msys/1.0/mingw/lib/gcc/mingw32/4.4.0/libstdc++.dll.a: No such file or directory. My MSYS has been configured to use a MinGW in the Qt SDK. So, I have to figure out why it is looking there
| [Wednesday 17 November 2010] [06:08:19] <mikko>	mato: https://gist.github.com/4ee2182fff0fae1b60d9 this is the second iteration
| [Wednesday 17 November 2010] [06:08:26] <mikko>	mato: possibly a bit cleaner
| [Wednesday 17 November 2010] [06:09:16] <mato>	yes
| [Wednesday 17 November 2010] [06:09:20] <mato>	i'll try that
| [Wednesday 17 November 2010] [06:09:22] <mikko>	"whether to build static libraries" doesnt say "no"
| [Wednesday 17 November 2010] [06:09:26] <mikko>	it just leaves blank
| [Wednesday 17 November 2010] [06:09:34] <mato>	that's fine
| [Wednesday 17 November 2010] [06:12:40] <mikko>	autoconf is such a hack
| [Wednesday 17 November 2010] [06:14:08] <mato>	mikko: the 2nd iteration is much better, I no longer get weird errors from configure during it's operation
| [Wednesday 17 November 2010] [06:14:31] <mato>	mikko: so it seems you moved the libtool initialization "early" enough to make it work correctly
| [Wednesday 17 November 2010] [06:15:19] <mato>	ok, works on Linux with and without --disable-shared, going to check on windows
| [Wednesday 17 November 2010] [06:22:11] <kobus>	mikko: My mingw doesn't even have  a libstdc++.dll.a
| [Wednesday 17 November 2010] [06:22:31] <mikko>	hmm
| [Wednesday 17 November 2010] [06:22:37] <mikko>	kobus: do you have libstdc++.dll ?
| [Wednesday 17 November 2010] [06:26:48] <kobus>	mikko: In the mingw bin dir I have libstdc++-6.dll...
| [Wednesday 17 November 2010] [06:27:48] <mikko>	kobus: i can only talk for cross-compile
| [Wednesday 17 November 2010] [06:27:52] <mikko>	mato: does it build?
| [Wednesday 17 November 2010] [06:28:07] <mato>	mikko: building now
| [Wednesday 17 November 2010] [06:30:01] <kobus>	mikko: Strnage that gcc wants libstdc++.dll.a, I have a linstdc++-6.dll and libstdc++.a
| [Wednesday 17 November 2010] [06:30:38] <mikko>	i wonder if it does have anything to do with the qt sdk
| [Wednesday 17 November 2010] [06:30:46] <mikko>	kobus: try building --disable-static
| [Wednesday 17 November 2010] [06:30:55] <mikko>	kobus: thats what the newer revisions of the patches do
| [Wednesday 17 November 2010] [06:31:27] <kobus>	mikko: should I get the latest git master
| [Wednesday 17 November 2010] [06:32:24] <mikko>	kobus: it's gonna take a few moments to get there. mato is testing the build on windows now
| [Wednesday 17 November 2010] [06:32:41] <mikko>	kobus: so if you wait until the build finishes we should know whether the fixes work
| [Wednesday 17 November 2010] [06:34:15] <mato>	mikko: ok, it builds, and make check works apart from inproc and ipc
| [Wednesday 17 November 2010] [06:34:36] <mato>	sustrik: win32 does not do "inproc" ?
| [Wednesday 17 November 2010] [06:34:45] <mato>	sustrik: i thought only "ipc" was unsupported
| [Wednesday 17 November 2010] [06:35:12] <sustrik>	it does
| [Wednesday 17 November 2010] [06:35:18] <sustrik>	why do you think so?
| [Wednesday 17 November 2010] [06:35:40] <mato>	oh, it's only the reqrep test that's failing
| [Wednesday 17 November 2010] [06:35:41] <mato>	interesting
| [Wednesday 17 November 2010] [06:36:03] <mato>	terminate called after throwing an instance of 'zmq::error_t' what():  Protocol not supported
| [Wednesday 17 November 2010] [06:36:07] <mato>	This application has requested the Runtime to terminate it in an unusual way.
| [Wednesday 17 November 2010] [06:36:09] <mato>	Please contact the application's support team for more information.
| [Wednesday 17 November 2010] [06:36:12] <mato>	FAIL: test_reqrep_ipc.exe
| [Wednesday 17 November 2010] [06:36:21] <mato>	sustrik: possibly a portability issue. those tests have not been checked on windows at all
| [Wednesday 17 November 2010] [06:36:26] <mato>	something to check eventually...
| [Wednesday 17 November 2010] [06:36:42] <mato>	./c
| [Wednesday 17 November 2010] [06:37:05] <sustrik>	ok
| [Wednesday 17 November 2010] [06:40:48] <Guthur>	sustrik, I tried 16 subscribing processes on my box here, using clrzmq2, no exception
| [Wednesday 17 November 2010] [06:41:07] <sustrik>	Guthur: sure, just say so
| [Wednesday 17 November 2010] [06:41:31] <Guthur>	Once I get home, I'll reply on the ML
| [Wednesday 17 November 2010] [06:41:52] <sustrik>	you don't have to do other prople's homework, just let them know you are paying attention
| [Wednesday 17 November 2010] [06:43:30] <Guthur>	sustrik: ack
| [Wednesday 17 November 2010] [06:47:01] <mato>	mikko: ok, all seems to work, i checked that on mingw --disable-shared / --enable-static behave as expected (i.e. fail)
| [Wednesday 17 November 2010] [06:48:15] <kobus>	mato: So can I use --disable-static?
| [Wednesday 17 November 2010] [06:49:56] <mato>	kobus: I'd suggest you want until these fixes we're working on land on master.
| [Wednesday 17 November 2010] [06:50:06] <mato>	kobus: *wait
| [Wednesday 17 November 2010] [06:50:09] <mikko>	mato: happy with the patch?
| [Wednesday 17 November 2010] [06:50:35] <mato>	mikko: yes, the question now is, we should probably get this into maint as well as master, right?
| [Wednesday 17 November 2010] [06:50:53] <mato>	mikko: since 2.0.10 will have the same problems
| [Wednesday 17 November 2010] [06:52:29] <mato>	mikko: so, shall we take your patches from yesterday, #1,#2,#3,#5 plus this patch, and apply all to maint and master?
| [Wednesday 17 November 2010] [06:53:02] <mato>	there doesn't appear to be anything specific to master in any of those patches AFAICT, let me try and apply them to maint now...
| [Wednesday 17 November 2010] [06:53:49] <mikko>	mato: are all of them relevant to maint as well?
| [Wednesday 17 November 2010] [06:53:55] <mikko>	like removing the stdint substs etc
| [Wednesday 17 November 2010] [06:54:02] <mato>	mikko: probably, checking now
| [Wednesday 17 November 2010] [06:55:08] <mato>	mikko: hmm, actually they'd have to be re-done for maint
| [Wednesday 17 November 2010] [06:55:17] <mato>	mikko: stuff has changed
| [Wednesday 17 November 2010] [06:55:21] <mikko>	mato: line numbers wont match etc
| [Wednesday 17 November 2010] [06:55:34] <mato>	sustrik: do we want to fix mingw in maint at all?
| [Wednesday 17 November 2010] [06:55:37] <mikko>	mato: i don't know whether we even should do these for maint
| [Wednesday 17 November 2010] [06:55:38] <mato>	sustrik: is it worth it?
| [Wednesday 17 November 2010] [06:55:45] <mato>	mikko: yeah
| [Wednesday 17 November 2010] [06:55:54] <mato>	mikko: i'd be inclined to leave maint as is
| [Wednesday 17 November 2010] [06:56:18] <mikko>	mato: i agree
| [Wednesday 17 November 2010] [06:56:27] <mato>	ok
| [Wednesday 17 November 2010] [06:56:30] <mikko>	it also adds pressure to get 2.1.x beta / alpha out
| [Wednesday 17 November 2010] [06:56:33] <mikko>	which is a good thing
| [Wednesday 17 November 2010] [06:56:33] <mato>	yes
| [Wednesday 17 November 2010] [06:56:54] <mato>	i finally have time to get through the bits i have pending, so that will happen soon
| [Wednesday 17 November 2010] [06:57:15] <mato>	only thing pending from my side is documentation review and DSO symbol visibility
| [Wednesday 17 November 2010] [06:57:31] <mato>	the latter implies we can finally start numbering the DLL/SO ABI versions properly
| [Wednesday 17 November 2010] [06:57:42] <mato>	so master would be (I guess) libzmq.so.1
| [Wednesday 17 November 2010] [06:59:35] <sustrik>	+1
| [Wednesday 17 November 2010] [06:59:43] <sustrik>	let people move to 2.1
| [Wednesday 17 November 2010] [06:59:48] <mato>	ok
| [Wednesday 17 November 2010] [07:23:21] <mikko>	mato: http://valokuva.org/~mikko/b/
| [Wednesday 17 November 2010] [07:23:25] <mikko>	happy with those going to ML?
| [Wednesday 17 November 2010] [07:23:31] <mikko>	will send after lunch
| [Wednesday 17 November 2010] [07:52:15] <mato>	mikko: yes, happy, just when you send them, please expand the commit messages a bit
| [Wednesday 17 November 2010] [07:52:25] <mato>	mikko: "MinGW32 build fixes" is not very descriptive
| [Wednesday 17 November 2010] [07:52:42] <mato>	mikko: otherwise, it's all good
| [Wednesday 17 November 2010] [07:52:45] <mato>	mikko: thanks!
| [Wednesday 17 November 2010] [08:01:27] <mato>	i have to go, bbl maybe
| [Wednesday 17 November 2010] [08:30:43] <Guthur>	pieterh: In zmsg.c  the comments for encode and decode in zmsg.c are little confusing
| [Wednesday 17 November 2010] [08:31:10] <Guthur>	they are both the same yet obviously one is from string -> byte and the other byte -> string
| [Wednesday 17 November 2010] [08:31:20] <pieterh>	Guthur, feel free to send me a patch...
| [Wednesday 17 November 2010] [08:31:45] <pieterh>	I don't have my pc here, mobile phone only
| [Wednesday 17 November 2010] [08:32:29] <pieterh>	That code is also in zfl now, zfl_msg class
| [Wednesday 17 November 2010] [08:33:10] <Guthur>	pieterh, ok I'll try to get something sent later this evening
| [Wednesday 17 November 2010] [08:33:41] <pieterh>	Nice :)
| [Wednesday 17 November 2010] [08:34:41] <Guthur>	pieterh: Also, in regards to ZPL, do you see it only being used for device configuration? or should there be some support for arbitrary connections as well?
| [Wednesday 17 November 2010] [08:35:45] <pieterh>	I'd like to use zpl as a general config format, and layer device configs on top of that
| [Wednesday 17 November 2010] [08:36:13] <Guthur>	ok, it's just that the examples only really showed context and device
| [Wednesday 17 November 2010] [08:36:36] <pieterh>	It's confused now, two problems solved together
| [Wednesday 17 November 2010] [08:36:56] <Guthur>	in regards to device creation I was thinking some sort of factory pattern might be nice, to remove the creation away from the config class
| [Wednesday 17 November 2010] [08:37:10] <pieterh>	It came out of device configuration but we're starting to use it more widely
| [Wednesday 17 November 2010] [08:37:26] <pieterh>	Yes, a factory pattern
| [Wednesday 17 November 2010] [08:37:44] <Guthur>	I have a prototype working in C# for the current devices (queue, forwarder, and streamer)
| [Wednesday 17 November 2010] [08:37:48] <pieterh>	zfl_device or somesuch
| [Wednesday 17 November 2010] [08:38:26] <pieterh>	See also the zdevices project where I hope to collect example devices in random languages
| [Wednesday 17 November 2010] [08:38:53] <Guthur>	oh, I'll check that out
| [Wednesday 17 November 2010] [08:39:32] <pieterh>	It should probably move to the ZeroMQ organisation on github
| [Wednesday 17 November 2010] [08:40:58] <Guthur>	yeah it would make sense
| [Wednesday 17 November 2010] [08:41:27] <Guthur>	I don't think devices should really have been including in the main 0MQ lib
| [Wednesday 17 November 2010] [08:41:33] <Guthur>	included*
| [Wednesday 17 November 2010] [08:41:51] <Guthur>	but on the other side are worth having around
| [Wednesday 17 November 2010] [09:07:48] <Guthur>	pieterh: I can put my implementation of device creation on github if you would be interested in having a look
| [Wednesday 17 November 2010] [09:08:20] <Guthur>	Even if you are not familiar with C# you should be able to understand it
| [Wednesday 17 November 2010] [09:09:13] <pieterh>	Ah, for sure, sharing code is always good... do use the list, many people are interested in devices imo
| [Wednesday 17 November 2010] [09:11:17] <mikko>	howdy pieterh 
| [Wednesday 17 November 2010] [09:11:34] <pieterh>	Hi mikko!
| [Wednesday 17 November 2010] [09:12:18] <mikko>	hows tricks?
| [Wednesday 17 November 2010] [09:15:01] <pieterh>	Ah, well enough... 
| [Wednesday 17 November 2010] [09:15:30] <pieterh>	Kind of laid up for a while, but have my trusty Android
| [Wednesday 17 November 2010] [09:15:43] <CIA-20>	zeromq2: 03Mikko Koppanen 07master * r3dbd5d5 10/ (configure.in tests/Makefile.am): 
| [Wednesday 17 November 2010] [09:15:43] <CIA-20>	zeromq2: Fix mingw32 build
| [Wednesday 17 November 2010] [09:15:43] <CIA-20>	zeromq2: MinGW32 defines __int64_t as long long, which causes the build to fail
| [Wednesday 17 November 2010] [09:15:43] <CIA-20>	zeromq2: unless -Wno-long-long is used. In addition the shutdown_stress test
| [Wednesday 17 November 2010] [09:15:43] <CIA-20>	zeromq2: isn't currently compatible with Win.
| [Wednesday 17 November 2010] [09:15:44] <CIA-20>	zeromq2: Signed-off-by: Mikko Koppanen <mkoppanen@php.net> - http://bit.ly/9wYVtY
| [Wednesday 17 November 2010] [09:15:45] <CIA-20>	zeromq2: 03Mikko Koppanen 07master * r9255952 10/ (acinclude.m4 configure.in): 
| [Wednesday 17 November 2010] [09:15:45] <CIA-20>	zeromq2: MinGW32 build fixes
| [Wednesday 17 November 2010] [09:15:46] <CIA-20>	zeromq2: After long discussions in IRC we came to conclusion that there is no
| [Wednesday 17 November 2010] [09:15:46] <CIA-20>	zeromq2: elegant way to handle static builds with MinGW32. This patch sets
| [Wednesday 17 November 2010] [09:15:47] <CIA-20>	zeromq2: AC_DISABLE_STATIC by default on MinGW32 and Cygwin
| [Wednesday 17 November 2010] [09:15:47] <CIA-20>	zeromq2: Signed-off-by: Mikko Koppanen <mkoppanen@php.net> - http://bit.ly/bNNMmI
| [Wednesday 17 November 2010] [09:15:48] <CIA-20>	zeromq2: 03Mikko Koppanen 07master * rb83d0a1 10/ (configure.in src/Makefile.am): 
| [Wednesday 17 November 2010] [09:15:48] <CIA-20>	zeromq2: Remove unnecessary conditional
| [Wednesday 17 November 2010] [09:15:58] <pieterh>	Mato is working on a 2.1 I hear, that'll be nice to see
| [Wednesday 17 November 2010] [09:16:25] <CIA-20>	zeromq2: Remove unneeded substitutions
| [Wednesday 17 November 2010] [09:16:25] <CIA-20>	zeromq2: Couldn't find a place where these substs were actually used
| [Wednesday 17 November 2010] [09:16:25] <CIA-20>	zeromq2: Signed-off-by: Mikko Koppanen <mkoppanen@php.net> - http://bit.ly/arqYuu
| [Wednesday 17 November 2010] [09:16:25] <CIA-20>	zeromq2: 03Mikko Koppanen 07master * r72a7b93 10/ acinclude.m4 : 
| [Wednesday 17 November 2010] [09:16:26] <CIA-20>	zeromq2: Allow building without documentation.
| [Wednesday 17 November 2010] [09:16:26] <CIA-20>	zeromq2: Allows building without documentation even if asciidoc and xmlto are
| [Wednesday 17 November 2010] [09:16:27] <CIA-20>	zeromq2: installed. This eases up working with the build system because doc
| [Wednesday 17 November 2010] [09:16:27] <CIA-20>	zeromq2: generation take quite a while on repeated builds.
| [Wednesday 17 November 2010] [09:16:28] <CIA-20>	zeromq2: Signed-off-by: Mikko Koppanen <mkoppanen@php.net> - http://bit.ly/cik80A
| [Wednesday 17 November 2010] [10:10:08] <toni_>	hey there. I want to send a msg from an XREP to a REQ socket. The message came from a further XREP socket and therefore still has the envelope of the original sender. So I append another envelope containing the address of the REQ socket. So, the message the REQ socket receives contains one envelope. It seems that REQ socket require msgs without any envelopes. So I guess I have to store the envelope information as part of the payload. P
| [Wednesday 17 November 2010] [10:12:14] <toni_>	fyi I get an "Assertion failed: zmq_msg_size (msg_) == 0" in case the incoming message at the REQ socket contains an envelope
| [Wednesday 17 November 2010] [10:12:37] <guido_g>	there is a whole chapter in the guide about routing
| [Wednesday 17 November 2010] [10:13:07] <guido_g>	the address stack is delimited by a 0 sized message part, this is hardcoded
| [Wednesday 17 November 2010] [10:15:03] <toni_>	okay, the message contains this 0 sized part. But is it illegal to have an envelope prepended when the message is received by the REQ socket?
| [Wednesday 17 November 2010] [10:17:09] <guido_g>	obviously your address stack isn't valid
| [Wednesday 17 November 2010] [10:18:36] <guido_g>	http://zguide.zeromq.org/chapter:all#toc42 <- check this first, i'd say
| [Wednesday 17 November 2010] [10:35:10] <toni_>	I read the guide and this chapter. So my problem is, when poping the envelope and passing this to the XREP: [req_sock_addr, '', data] it works. In case the message looks like this: [req_socket_addr, client_addr, '', data] it is received by the REQ socket, but I am getting this error. So my question is if a REQ sockets does not allow envelopes when it receives a message. 
| [Wednesday 17 November 2010] [10:36:45] <sustrik>	toni_: req socket expects only the backtrace stack delimiter (i.e. empty message part) to be present in the reply aside of its actual content
| [Wednesday 17 November 2010] [10:37:26] <toni_>	sustrik: ah okay, so I have to pack the "client_addr" as part of the payload
| [Wednesday 17 November 2010] [10:37:40] <toni_>	thanks
| [Wednesday 17 November 2010] [10:37:45] <sustrik>	np
| [Wednesday 17 November 2010] [10:55:13] <mikko>	heyo
| [Wednesday 17 November 2010] [10:55:25] <mikko>	now when sustrik applied my patches it looks like my git tree locally is clean
| [Wednesday 17 November 2010] [10:55:31] <mikko>	no diffs and nothing to commit
| [Wednesday 17 November 2010] [10:55:47] <mikko>	still git status shows Your branch is ahead of 'origin/master' by 6 commits.
| [Wednesday 17 November 2010] [10:56:02] <mikko>	how do i reset the state without git remote rm origin and readd?
| [Wednesday 17 November 2010] [11:01:31] <mikko>	git reset --hard origin/master probably
| [Wednesday 17 November 2010] [11:17:04] <kobus>	mikko: Has the mingw issues now been resolved? If so, how should I get the new code?
| [Wednesday 17 November 2010] [11:20:03] <mikko>	kobus: please try the master
| [Wednesday 17 November 2010] [11:20:16] <mikko>	kobus: it works for mato's clean mingw32 environment
| [Wednesday 17 November 2010] [11:20:23] <mikko>	kobus: can't say anything about the QT mingw
| [Wednesday 17 November 2010] [11:21:31] <mikko>	kobus: for master you need to run ./autogen.sh. if that is not possible in your env i can wrap you a dist package
| [Wednesday 17 November 2010] [11:22:02] <kobus>	mikko: It is just mingw installed under the Qt SDK dir. I installed MSYS and configured it to use the mingw by added the dir in /etc/fstab
| [Wednesday 17 November 2010] [11:23:30] <kobus>	mikko: If I run ./autogen.sh I get: autogen.sh: error: could not find pkg-config.  pkg-config is required to run autogen.sh.
| [Wednesday 17 November 2010] [11:23:45] <mikko>	kobus: i can do you a dist package if you want
| [Wednesday 17 November 2010] [11:24:47] <kobus>	mikko: I would appreciate it. Thanks for your effort! You are "a scholar and a gentleman" :-)
| [Wednesday 17 November 2010] [11:25:52] <kobus>	mikko: BTW just checking, you run autogen on Linux...
| [Wednesday 17 November 2010] [11:29:24] <mikko>	kobus: yes
| [Wednesday 17 November 2010] [11:29:38] <mikko>	you can run it on windows as well but you need to install pkg-config
| [Wednesday 17 November 2010] [11:29:44] <mikko>	which comes with hefty dependencies
| [Wednesday 17 November 2010] [11:29:46] <mikko>	like glib etc
| [Wednesday 17 November 2010] [11:31:05] <kobus>	mikko: So autogen generates the configure script? Based on what "inputs"?
| [Wednesday 17 November 2010] [11:32:54] <mikko>	kobus: try http://valokuva.org/~mikko/zeromq-2.1.0.zip
| [Wednesday 17 November 2010] [11:33:16] <mikko>	kobus: yes, autogen runs all the required tools to generate configure
| [Wednesday 17 November 2010] [11:33:17] <kobus>	mikko: Thanks, wil try...
| [Wednesday 17 November 2010] [11:33:22] <mikko>	autoreconf etc
| [Wednesday 17 November 2010] [11:39:23] <kobus>	mikko: Well it still gives the libstdc++.dll.a error. 
| [Wednesday 17 November 2010] [11:40:15] <mikko>	whats the exact error message again?
| [Wednesday 17 November 2010] [11:40:39] <kobus>	mikko: g++.exe: C:/msys/1.0/mingw/lib/gcc/mingw32/4.4.0/libstdc++.dll.a: No such file or directory
| [Wednesday 17 November 2010] [11:41:48] <mikko>	kobus: http://old.nabble.com/libstdc%2B%2B.dll.a%3A-No-such-file-or-directory%28gcc-4.4.0%29-td27186916.html
| [Wednesday 17 November 2010] [11:41:54] <mikko>	similar error
| [Wednesday 17 November 2010] [11:42:40] <mikko>	kobus: http://trac.osgeo.org/geos/ticket/282 this suggests a mingw bug
| [Wednesday 17 November 2010] [11:45:35] <mikko>	kobus: not sure if my tests are with same mingw version
| [Wednesday 17 November 2010] [11:49:52] <kobus>	mikko: I quickly try to switch a different mingw, but it didn't work. But I will try it with a later version at home. The wife sent an SMS
| [Wednesday 17 November 2010] [11:50:09] <mikko>	kobus: i can try on windows later today
| [Wednesday 17 November 2010] [11:50:18] <mikko>	need to do a couple of things first
| [Wednesday 17 November 2010] [11:50:45] <kobus>	mikko: Thanks again for your help and effort. I will chat again later today or tomorrow
| [Wednesday 17 November 2010] [11:51:13] <mikko>	cool
| [Wednesday 17 November 2010] [11:51:16] <mikko>	talk to you later
| [Wednesday 17 November 2010] [11:51:30] <kobus>	Ciao!
| [Wednesday 17 November 2010] [12:08:36] <mikko>	mingw32 succeeded on faily builds
| [Wednesday 17 November 2010] [12:10:06] <sustrik>	nice
| [Wednesday 17 November 2010] [12:11:02] <mikko>	still a couple of fixes coming
| [Wednesday 17 November 2010] [12:11:08] <mikko>	but the build looks pretty good now
| [Wednesday 17 November 2010] [12:11:29] <sustrik>	yep, only couple on bindings failing
| [Wednesday 17 November 2010] [12:11:35] <sustrik>	the core looks ok
| [Wednesday 17 November 2010] [12:12:19] <mikko>	well, it gives this: libtoolize: Remember to add `LT_INIT' to configure.in.
| [Wednesday 17 November 2010] [12:12:29] <mikko>	which i assume because AC_PROG_LIBTOOL is called from a macro
| [Wednesday 17 November 2010] [12:12:44] <mikko>	but i got a fix for that and a couple of other things done this evening
| [Wednesday 17 November 2010] [12:12:59] <sustrik>	good, just post them to the list and i'll apply them
| [Wednesday 17 November 2010] [12:13:42] <mikko>	test_close (zmq.tests.test_socket.TestSocket) ... Assertion failed: !pgm_supported () (zmq.cpp:245)
| [Wednesday 17 November 2010] [12:13:50] <mikko>	pyzmq error test failure message
| [Wednesday 17 November 2010] [12:14:08] <sustrik>	seen that
| [Wednesday 17 November 2010] [12:14:37] <sustrik>	that's maint?
| [Wednesday 17 November 2010] [12:14:47] <sustrik>	yes
| [Wednesday 17 November 2010] [12:14:53] <mikko>	yes
| [Wednesday 17 November 2010] [12:15:28] <sustrik>	aha, the test in question opens two contexts
| [Wednesday 17 November 2010] [12:15:39] <sustrik>	which in turn initialises OpenPGM twice
| [Wednesday 17 November 2010] [12:15:49] <sustrik>	which fails with old version of OpenPGM
| [Wednesday 17 November 2010] [12:16:08] <sustrik>	solved in OpenPGM/5 which is included in master
| [Wednesday 17 November 2010] [13:13:55] <bgranger>	minrk1: hi
| [Wednesday 17 November 2010] [13:27:12] <s0undt3ch>	hello ppl
| [Wednesday 17 November 2010] [13:27:32] <s0undt3ch>	I've built pyzmq using --inplace, however when running tests I'm getting
| [Wednesday 17 November 2010] [13:27:36] <cremes>	interesting new project for building complex 0mq devices:
| [Wednesday 17 November 2010] [13:27:37] <cremes>	http://www.igvita.com/2010/11/17/routing-with-ruby-zeromq-devices/
| [Wednesday 17 November 2010] [13:27:55] <s0undt3ch>	http://paste.pocoo.org/show/292687/
| [Wednesday 17 November 2010] [13:28:34] <bgranger>	s0undt3ch:  where are you running the tests from?
| [Wednesday 17 November 2010] [13:29:02] <bgranger>	What platform are you on?
| [Wednesday 17 November 2010] [13:29:12] <s0undt3ch>	linux
| [Wednesday 17 November 2010] [13:29:22] <bgranger>	Did you build zeormq with pgm support?
| [Wednesday 17 November 2010] [13:29:27] <s0undt3ch>	bgranger: from where I've built it
| [Wednesday 17 November 2010] [13:29:39] <s0undt3ch>	zeromq is from my distro, ubuntu
| [Wednesday 17 November 2010] [13:29:59] <bgranger>	Version?
| [Wednesday 17 November 2010] [13:30:03] <s0undt3ch>	dunno if they build it or not with pgm
| [Wednesday 17 November 2010] [13:30:04] <s0undt3ch>	hmm
| [Wednesday 17 November 2010] [13:30:29] <s0undt3ch>	2.0.10
| [Wednesday 17 November 2010] [13:31:40] <s0undt3ch>	hmm pyzmq 2.0.9
| [Wednesday 17 November 2010] [13:31:47] <s0undt3ch>	problem?
| [Wednesday 17 November 2010] [13:32:13] <bgranger>	Can you try it with 2.0.10.  But this is an odd error that I have not seen before.  We just released 2.0.10 pyzmq yesterday.
| [Wednesday 17 November 2010] [13:32:30] <s0undt3ch>	hmm
| [Wednesday 17 November 2010] [13:32:43] <s0undt3ch>	updating git
| [Wednesday 17 November 2010] [13:33:16] <s0undt3ch>	now I can't build pyzmq
| [Wednesday 17 November 2010] [13:33:34] <s0undt3ch>	http://paste.pocoo.org/show/292692/
| [Wednesday 17 November 2010] [13:35:43] <s0undt3ch>	what's up with it?
| [Wednesday 17 November 2010] [13:38:34] <bgranger>	You just grabbed pyzmq master, which is not tracking 2.1.  You need to grab our atual 2.0.10 release from here:
| [Wednesday 17 November 2010] [13:39:12] <bgranger>	https://github.com/zeromq/pyzmq/downloads
| [Wednesday 17 November 2010] [13:41:11] <bgranger>	Or if you want to follow the de branch for 2.0.x you can grab the 2.0.x branch.
| [Wednesday 17 November 2010] [13:45:10] <s0undt3ch>	Graterle Commu
| [Wednesday 17 November 2010] [13:45:20] <s0undt3ch>	opps sorry
| [Wednesday 17 November 2010] [13:45:35] <s0undt3ch>	bgranger: ah, ok
| [Wednesday 17 November 2010] [13:50:29] <bgranger>	Hi:  we hare having an issue with pgm enabled zeromq and the pyzmq test suite.
| [Wednesday 17 November 2010] [13:50:51] <bgranger>	We don't use pgm in the test suite at all, but we are seeing a failure like this:
| [Wednesday 17 November 2010] [13:51:06] <bgranger>	Assertion failed: !pgm_supported () (zmq.cpp:240)
| [Wednesday 17 November 2010] [13:51:25] <minrk>	which happens in zmq_init()
| [Wednesday 17 November 2010] [13:51:34] <bgranger>	Are there limitations about how many contexts you can have per process if pgm is enabled.
| [Wednesday 17 November 2010] [13:51:44] <bgranger>	Yes, as Min said, it is zmq_init() that is failling.
| [Wednesday 17 November 2010] [14:00:19] <minrk>	    zmq_assert (!pgm_supported ());
| [Wednesday 17 November 2010] [14:00:19] <minrk>	    int rc = pgm_init (&pgm_error);
| [Wednesday 17 November 2010] [14:01:37] <minrk>	zmq_init() contains:
| [Wednesday 17 November 2010] [14:01:37] <minrk>	 zmq_assert (!pgm_supported ());
| [Wednesday 17 November 2010] [14:01:37] <minrk>	 ...
| [Wednesday 17 November 2010] [14:01:37] <minrk>	 int rc = pgm_init (&pgm_error);
| [Wednesday 17 November 2010] [14:01:38] <minrk>	which seems to suggest that zmq_init can only be called once if you have PGM.
| [Wednesday 17 November 2010] [14:01:39] <minrk>	Is this correct?
| [Wednesday 17 November 2010] [14:03:50] <minrk>	If that's true, we need a way to check at runtime whether PGM is being used. Is there such a method?
| [Wednesday 17 November 2010] [14:05:32] <bgranger>	But I think the the assert should not assert.  If pgm is already init'd, just pass?
| [Wednesday 17 November 2010] [14:05:40] <bgranger>	sustrik:  are you around?
| [Wednesday 17 November 2010] [14:06:39] <minrk>	comments at the assert:
| [Wednesday 17 November 2010] [14:06:39] <minrk>	    //  Unfortunately, OpenPGM doesn't support refcounted init/shutdown, thus,
| [Wednesday 17 November 2010] [14:06:40] <minrk>	    //  let's fail if it was initialised beforehand.
| [Wednesday 17 November 2010] [14:06:44] <bgranger>	I would think that the pgm_supported assert should be turned into a flag that zeromq sets to track if it has called pgm_init
| [Wednesday 17 November 2010] [14:06:55] <bgranger>	Only assert is someone else has called pmg_init beforehand.
| [Wednesday 17 November 2010] [14:16:53] <sustrik>	re
| [Wednesday 17 November 2010] [14:17:16] <sustrik>	bgranger: well, it's a problem with OpenPGM
| [Wednesday 17 November 2010] [14:17:22] <bgranger>	OK
| [Wednesday 17 November 2010] [14:17:26] <sustrik>	it uses a global state
| [Wednesday 17 November 2010] [14:17:29] <sustrik>	0MQ does not
| [Wednesday 17 November 2010] [14:17:40] <sustrik>	(all the global state is in contexts)
| [Wednesday 17 November 2010] [14:17:54] <sustrik>	so creating 2 contexts creates a problem with OpenPGM
| [Wednesday 17 November 2010] [14:18:05] <bgranger>	OK, so that is a known problem.
| [Wednesday 17 November 2010] [14:18:11] <sustrik>	in new version it was solved by adding reference counting to pgm_init
| [Wednesday 17 November 2010] [14:18:23] <sustrik>	yes, it's a known problem
| [Wednesday 17 November 2010] [14:18:29] <bgranger>	Is there a simple way we can determine if pgm is used, so pyzmq doesn't assert here.
| [Wednesday 17 November 2010] [14:18:36] <bgranger>	Or should be just wait for the new pgm.
| [Wednesday 17 November 2010] [14:18:49] <sustrik>	there's a new pgm with 2.1
| [Wednesday 17 November 2010] [14:19:01] <bgranger>	OK
| [Wednesday 17 November 2010] [14:19:10] <bgranger>	So this is only a 2.0 issue.
| [Wednesday 17 November 2010] [14:19:14] <sustrik>	yes
| [Wednesday 17 November 2010] [14:19:26] <sustrik>	it's kind of dirty
| [Wednesday 17 November 2010] [14:19:32] <sustrik>	but that's the way it is
| [Wednesday 17 November 2010] [14:19:38] <sustrik>	"solved in next version"
| [Wednesday 17 November 2010] [14:19:39] <sustrik>	shrug
| [Wednesday 17 November 2010] [14:19:39] <minrk>	it's still important to be able to check if 0MQ was built with PGM, how do we check that?
| [Wednesday 17 November 2010] [14:19:46] <sustrik>	hm
| [Wednesday 17 November 2010] [14:20:05] <sustrik>	even before creating a context?
| [Wednesday 17 November 2010] [14:20:21] <sustrik>	i don't think there's a way to find out
| [Wednesday 17 November 2010] [14:20:29] <minrk>	is there a way after creating one?
| [Wednesday 17 November 2010] [14:20:42] <sustrik>	trying to open a PGM endpoint :)
| [Wednesday 17 November 2010] [14:20:48] <sustrik>	if you get EPROTONOTSUP
| [Wednesday 17 November 2010] [14:20:53] <sustrik>	there's no PGM :)
| [Wednesday 17 November 2010] [14:21:10] <sustrik>	is it a problem?
| [Wednesday 17 November 2010] [14:21:26] <sustrik>	can't we do with "known problem, solved in next version"?
| [Wednesday 17 November 2010] [14:21:42] <minrk>	well, the pyzmq test suite fails, because one of the test categories creates multiple contexts
| [Wednesday 17 November 2010] [14:22:03] <sustrik>	yep, seen that
| [Wednesday 17 November 2010] [14:22:10] <sustrik>	if it really matters
| [Wednesday 17 November 2010] [14:22:27] <minrk>	And if we can check, we can skip the invalid tests as known failures
| [Wednesday 17 November 2010] [14:22:37] <sustrik>	in theory the refcounting code from newer versions of openpgm can be backported to old version
| [Wednesday 17 November 2010] [14:22:50] <bgranger>	Which is a problem because pgm is built on ubuntu by default, so the test suite will always fail there.
| [Wednesday 17 November 2010] [14:22:59] <sustrik>	is it?
| [Wednesday 17 November 2010] [14:23:10] <sustrik>	i am using ubuntu
| [Wednesday 17 November 2010] [14:23:21] <sustrik>	and i have to say ./configure --with-pgm
| [Wednesday 17 November 2010] [14:23:25] <sustrik>	to get pgm compiled
| [Wednesday 17 November 2010] [14:23:40] <sustrik>	or you mean mikko's auto builds?
| [Wednesday 17 November 2010] [14:24:09] <minrk>	I think he means the prebuilt package, yes
| [Wednesday 17 November 2010] [14:24:22] <minrk>	it does not build against pgm from source by default
| [Wednesday 17 November 2010] [14:25:00] <sustrik>	ok guys, if you believe it's a problem, please complain on the mailing list
| [Wednesday 17 November 2010] [14:25:10] <sustrik>	it's up to Steve McCoy to backport the fix
| [Wednesday 17 November 2010] [14:25:21] <minrk>	okay
| [Wednesday 17 November 2010] [14:26:14] <bgranger>	But I guess we can just try to use the pgm transport and set a flag in our test suite.  Not pretty though.   I would be tempted to simply let this go for now...
| [Wednesday 17 November 2010] [14:27:09] <minrk>	bgranger: if I just change the MQ test to use Processes instead of Threads, it would work
| [Wednesday 17 November 2010] [14:28:21] <bgranger>	Is that the only place we create a second Context in the test suite?
| [Wednesday 17 November 2010] [14:28:35] <bgranger>	If so I am fine with that.
| [Wednesday 17 November 2010] [14:28:38] <minrk>	it's a matter of one word in the test
| [Wednesday 17 November 2010] [14:28:48] <minrk>	I'm not 100% sure, but possibly
| [Wednesday 17 November 2010] [14:31:07] <bgranger>	OK, lets try that in 2.0.x
| [Wednesday 17 November 2010] [14:31:13] <minrk>	okay
| [Wednesday 17 November 2010] [14:31:28] <bgranger>	Unless you want to try to put out a 2.0.10 fix
| [Wednesday 17 November 2010] [14:31:47] <minrk>	In general, since this means that PGM introduces a pretty significant difference in what you are allowed to do, there should probably be a runtime-accessible ZMQ_HAS_PGM flag or something.
| [Wednesday 17 November 2010] [14:31:57] <minrk>	I'll put it in 2.0.x
| [Wednesday 17 November 2010] [14:32:33] <bgranger>	Yes, I agree (in zeromq).
| [Wednesday 17 November 2010] [14:32:51] <bgranger>	I think there is something like that, but it is not in the header file.
| [Wednesday 17 November 2010] [14:33:17] <minrk>	there's a macro used at compile time, but I don't think it's available at runtime
| [Wednesday 17 November 2010] [14:33:48] <bgranger>	Right
| [Wednesday 17 November 2010] [14:48:57] <s0undt3ch>	sorry ppl, how do I checkout a specific branch with git? I need to pull 2.0.x
| [Wednesday 17 November 2010] [14:50:51] <s0undt3ch>	solved
| [Wednesday 17 November 2010] [14:50:58] <Guthur>	mikko, What is the build website tracking?
| [Wednesday 17 November 2010] [14:51:10] <Guthur>	mikko, Can we get clrzmq2 added?
| [Wednesday 17 November 2010] [14:51:44] <s0undt3ch>	bgranger: still have the same issues with the 2.0.x branch
| [Wednesday 17 November 2010] [14:51:49] <s0undt3ch>	ie, the assertion error
| [Wednesday 17 November 2010] [14:52:13] <minrk>	That's because I haven't pushed the fix yet
| [Wednesday 17 November 2010] [14:53:10] <s0undt3ch>	ah, ok minrk. So there's a fix for this already?
| [Wednesday 17 November 2010] [14:53:22] <minrk>	well, workaround is more accurate
| [Wednesday 17 November 2010] [14:53:57] <minrk>	did you see the earlier discussion on this (~45 minutes ago here)?
| [Wednesday 17 November 2010] [14:54:00] <bgranger>	But pyzmq itself is working fine, the bug only affects situations where you create 2 contexts in the same process.
| [Wednesday 17 November 2010] [14:54:02] <s0undt3ch>	if it stops complainging and just works ;)
| [Wednesday 17 November 2010] [14:54:24] <s0undt3ch>	minrk: I was away, just read it now
| [Wednesday 17 November 2010] [14:54:31] <minrk>	ZeroMQ built with PGM can't have multiple contexts in one process, and some tests do that
| [Wednesday 17 November 2010] [14:54:59] <s0undt3ch>	bgranger: ah, my app did create more than one context
| [Wednesday 17 November 2010] [14:55:11] <s0undt3ch>	well, test script is more like it
| [Wednesday 17 November 2010] [14:55:23] <minrk>	that's a zeromq issue, not a pyzmq issue
| [Wednesday 17 November 2010] [14:55:58] <minrk>	If you want more than one context, you may not use PGM and 2.0.x
| [Wednesday 17 November 2010] [14:56:26] <s0undt3ch>	minrk: I probably won't need more than one context. At least for now
| [Wednesday 17 November 2010] [14:56:45] <minrk>	okay
| [Wednesday 17 November 2010] [14:57:05] <minrk>	I understand it's no longer a problem with 0MQ 2.1
| [Wednesday 17 November 2010] [15:02:45] <sustrik>	context is meant to be a singleton
| [Wednesday 17 November 2010] [15:02:55] <sustrik>	no point in creating multiple contexts
| [Wednesday 17 November 2010] [15:03:25] <sustrik>	(except for test purposes)
| [Wednesday 17 November 2010] [15:03:45] <minrk>	RIght, and it's tests that are failing
| [Wednesday 17 November 2010] [15:04:01] <sustrik>	yes, it makes sense there
| [Wednesday 17 November 2010] [15:04:09] <minrk>	will it still raise the assertion if I create the second context after closing the first?
| [Wednesday 17 November 2010] [15:04:13] <sustrik>	i was responding to <s0undt3ch>
| [Wednesday 17 November 2010] [15:04:21] <minrk>	sure
| [Wednesday 17 November 2010] [15:04:28] <sustrik>	minrk: it should not
| [Wednesday 17 November 2010] [15:04:33] <minrk>	okay
| [Wednesday 17 November 2010] [15:16:46] <bgranger>	minrk:  
| [Wednesday 17 November 2010] [15:16:54] <minrk>	yes
| [Wednesday 17 November 2010] [15:17:12] <bgranger>	I am testing 2.1dev, have you changed EINTR to KeyboardInterrupt like we talked about...
| [Wednesday 17 November 2010] [15:17:21] <bgranger>	It seems to work that way...
| [Wednesday 17 November 2010] [15:17:32] <minrk>	ok, good
| [Wednesday 17 November 2010] [15:17:47] <bgranger>	Works super well!
| [Wednesday 17 November 2010] [15:19:15] <bgranger>	But I don't see the commit where you fixed this...
| [Wednesday 17 November 2010] [15:19:23] <minrk>	fixed what?
| [Wednesday 17 November 2010] [15:19:26] <bgranger>	Or did you do nothing?
| [Wednesday 17 November 2010] [15:19:34] <minrk>	I haven't pushed anything today
| [Wednesday 17 November 2010] [15:19:51] <bgranger>	I thought we would manually have to catch EINTR and raise KeyboardInterrupt.
| [Wednesday 17 November 2010] [15:19:59] <bgranger>	But it looks like it "just works"
| [Wednesday 17 November 2010] [15:20:09] <bgranger>	I think I understand what is going on...
| [Wednesday 17 November 2010] [15:20:41] <bgranger>	When you do ctrl-C, Python puts the KeyboardInterrupt on a queue to be handled when the interpreter is free.
| [Wednesday 17 November 2010] [15:21:04] <bgranger>	zeromq raises ENITR, and that allows the Python interpreter to actually raise the KeyboardInterrupt
| [Wednesday 17 November 2010] [15:21:16] <bgranger>	But the EINTR itself is silenced.
| [Wednesday 17 November 2010] [15:21:19] <minrk>	so we don't actually have to handle it at all?
| [Wednesday 17 November 2010] [15:21:23] <bgranger>	Right
| [Wednesday 17 November 2010] [15:21:25] <minrk>	very nice
| [Wednesday 17 November 2010] [15:21:48] <bgranger>	Yes,  It worries me a little that the EINTR just sort of vanishes, but as long as it does so in a nice way, it is fine.
| [Wednesday 17 November 2010] [15:22:27] <bgranger>	I think the key is that both python and zeromq see the signal.
| [Wednesday 17 November 2010] [15:22:42] <bgranger>	But the test suite passes for 2.1 just fine.
| [Wednesday 17 November 2010] [15:23:01] <bgranger>	Which is huge.
| [Wednesday 17 November 2010] [15:23:49] <bgranger>	And FD and EVENTS seem to work fine.
| [Wednesday 17 November 2010] [15:24:21] <bgranger>	This will make it easier to integrate zmq sockets into Twisted.
| [Wednesday 17 November 2010] [15:24:32] <minrk>	ok, good
| [Wednesday 17 November 2010] [15:25:23] <minrk>	I didn't know enough about the new options to write good tests, but I did test that they are at least the right values, which we wouldn't get if we used uint64 like the others.
| [Wednesday 17 November 2010] [15:25:40] <bgranger>	That is fine.  
| [Wednesday 17 November 2010] [15:26:37] <bgranger>	minrk: back to #ipython...
| [Wednesday 17 November 2010] [15:26:43] <minrk>	okay
| [Wednesday 17 November 2010] [15:29:09] <Guthur>	hehe, I was wondering what #ipython was
| [Wednesday 17 November 2010] [15:35:21] <minrk>	mikko: Is it possible to stop building pyzmq-master against zeromq-maint? pyzmq-master now depends on zeromq 2.1. We have a '2.0.x' branch that is the equivalent of zeromq's 'maint'
| [Wednesday 17 November 2010] [15:35:57] <mikko>	minrk: sure
| [Wednesday 17 November 2010] [15:36:00] <mikko>	i can disable the build
| [Wednesday 17 November 2010] [15:36:25] <minrk>	thanks
| [Wednesday 17 November 2010] [15:36:39] <minrk>	If you want pyzmq+zeromq-maint, you should use pyzmq-2.0.x
| [Wednesday 17 November 2010] [15:36:53] <mikko>	is it a different branch?
| [Wednesday 17 November 2010] [15:37:05] <minrk>	yes, the branch is actually called '2.0.x'
| [Wednesday 17 November 2010] [15:37:55] <mikko>	the build is now pyzmq-2.0.x_ZeroMQ2-maint_GCC 
| [Wednesday 17 November 2010] [15:38:02] <mikko>	and the branch it builds from is 2.0.x
| [Wednesday 17 November 2010] [15:38:06] <minrk>	perfect, thanks!
| [Wednesday 17 November 2010] [15:38:21] <mikko>	building now as a test
| [Wednesday 17 November 2010] [15:39:10] <mikko>	minrk: builds, the tests still fail for that branch as well
| [Wednesday 17 November 2010] [15:39:31] <minrk>	Ah, sorry, I was actually just in the process of pushing a possible fix
| [Wednesday 17 November 2010] [15:41:07] <minrk>	It's a pgm issue in the test suite, but at least the target is right, so once I fix the bug, it will work
| [Wednesday 17 November 2010] [15:41:53] <minrk>	pyzmq-master would never build against zeromq-maint, until zeromq-maint is 2.1 though
| [Wednesday 17 November 2010] [15:42:11] <mikko>	ok
| [Wednesday 17 November 2010] [15:42:18] <mikko>	hopefully the builds are now sorted
| [Wednesday 17 November 2010] [15:42:34] <mikko>	i can add you an account if you want to configure pyzmq builds further
| [Wednesday 17 November 2010] [15:42:47] <minrk>	oh, sure
| [Wednesday 17 November 2010] [15:42:49] <mikko>	email notifications or such
| [Wednesday 17 November 2010] [15:42:51] <mikko>	sec
| [Wednesday 17 November 2010] [15:42:55] <minrk>	That would be great
| [Wednesday 17 November 2010] [15:43:24] <mikko>	minrk: see query for user / pass
| [Wednesday 17 November 2010] [15:43:30] <mikko>	oh wait
| [Wednesday 17 November 2010] [15:43:34] <mikko>	i need to add permissions as well
| [Wednesday 17 November 2010] [15:44:46] <mikko>	now if you try with the details
| [Wednesday 17 November 2010] [15:44:52] <mikko>	you should be able to login / edit builds
| [Wednesday 17 November 2010] [15:45:32] <minrk>	great, thanks
| [Wednesday 17 November 2010] [16:10:44] <Guthur>	mikko: did you see my message about clrzmq2 earlier
| [Wednesday 17 November 2010] [16:20:58] <mikko>	Guthur: nope
| [Wednesday 17 November 2010] [16:21:00] <mikko>	missed that one
| [Wednesday 17 November 2010] [16:21:04] <mikko>	what was it about?
| [Wednesday 17 November 2010] [16:21:28] <Guthur>	It was about how we would go about adding clrzmq2 to the build system
| [Wednesday 17 November 2010] [16:21:51] <mikko>	give me url to the repo and instructions how to build and i can add it
| [Wednesday 17 November 2010] [16:22:19] <mikko>	does it build in mono?
| [Wednesday 17 November 2010] [16:22:21] <Guthur>	it has a 4 build configurations in the solution
| [Wednesday 17 November 2010] [16:22:28] <Guthur>	mikko yep
| [Wednesday 17 November 2010] [16:22:36] <mikko>	current clrzmq uses "xbuild clrzmq.sln"
| [Wednesday 17 November 2010] [16:23:17] <Guthur>	it has POSIX/WIN-Debug/Release
| [Wednesday 17 November 2010] [16:23:31] <Guthur>	and can target x86  or x64
| [Wednesday 17 November 2010] [16:23:55] <mikko>	is the repo under zeromq organisation?
| [Wednesday 17 November 2010] [16:24:00] <Guthur>	yep
| [Wednesday 17 November 2010] [16:24:07] <Guthur>	2 secs i will get the link
| [Wednesday 17 November 2010] [16:24:11] <mikko>	ok, let me try to build it
| [Wednesday 17 November 2010] [16:24:38] <Guthur>	https://github.com/zeromq/clrzmq2
| [Wednesday 17 November 2010] [16:25:03] <Guthur>	I would definitely be appreciative of feedback on the build process
| [Wednesday 17 November 2010] [16:26:22] <mikko>	/usr/lib/mono/3.5/Microsoft.Common.targets:  warning : TargetFrameworkVersion 'v4.0' not supported by this toolset (ToolsVersion: 4.0).
| [Wednesday 17 November 2010] [16:26:51] <Guthur>	oh darn, that should be defaulting to 2.0
| [Wednesday 17 November 2010] [16:27:01] <Guthur>	MSVS changed it
| [Wednesday 17 November 2010] [16:27:04] <mikko>	 /usr/lib/mono/3.5/Microsoft.CSharp.targets: error : Error executing tool '/usr/bin/dmcs': ApplicationName='/usr/bin/dmcs', CommandLine='/noconfig @/tmp/tmp6f5fdb71.tmp', CurrentDirectory='/tmp/clrzmq2/clrzmq'
| [Wednesday 17 November 2010] [16:27:08] <mikko>	getting that as well
| [Wednesday 17 November 2010] [16:27:27] <Guthur>	oh that's new
| [Wednesday 17 November 2010] [16:27:43] <Guthur>	let me try here, the solution most have got changed by MSVS
| [Wednesday 17 November 2010] [16:27:56] <Guthur>	It's a challenge to juggle the two
| [Wednesday 17 November 2010] [16:28:40] <Guthur>	sorry mikko, give me a couple of minutes here 
| [Wednesday 17 November 2010] [16:29:42] <Guthur>	The problem is now that if I change it with Mono it will probably be troublesome for MSVS 
| [Wednesday 17 November 2010] [16:30:11] <mikko>	sure
| [Wednesday 17 November 2010] [16:31:39] <Guthur>	ok give me a bit longer and I will see if I can make the changes in MSVS so that it works for Mono
| [Wednesday 17 November 2010] [16:31:47] <Guthur>	just need to fire up the VM
| [Wednesday 17 November 2010] [16:32:20] <Guthur>	the framework one is easy
| [Wednesday 17 November 2010] [16:32:36] <Guthur>	the other one may is stranger
| [Wednesday 17 November 2010] [16:32:40] <mikko>	how do i build with xbuild ?
| [Wednesday 17 November 2010] [16:32:48] <mikko>	xbuild /target:??,??
| [Wednesday 17 November 2010] [16:32:49] <Guthur>	not sure, never used that before
| [Wednesday 17 November 2010] [16:33:01] <Guthur>	I can investigate though
| [Wednesday 17 November 2010] [16:33:18] <Guthur>	i was using monodeveloper
| [Wednesday 17 November 2010] [16:33:30] <Guthur>	monodevelop even
| [Wednesday 17 November 2010] [16:33:39] <mikko>	i think xbuild is the build tool from that
| [Wednesday 17 November 2010] [16:35:08] <Guthur>	must be separate, I don't have it install even though i have monodevelop
| [Wednesday 17 November 2010] [16:35:47] <mikko>	comes in mono-xbuild package
| [Wednesday 17 November 2010] [16:36:05] <mikko>	xbuild is Mono's implementation of msbuild
| [Wednesday 17 November 2010] [16:41:01] <Guthur>	no probs, i've got it now
| [Wednesday 17 November 2010] [16:41:12] <Guthur>	i'll see if I can get it working
| [Wednesday 17 November 2010] [16:41:48] <mikko>	mdtool build --configuration:'POSIX_RELEASE|x86'
| [Wednesday 17 November 2010] [16:41:52] <mikko>	that builds it
| [Wednesday 17 November 2010] [16:41:56] <mikko>	ill add the build now
| [Wednesday 17 November 2010] [16:43:29] <Guthur>	Did you change the framework?
| [Wednesday 17 November 2010] [16:43:55] <Guthur>	I've just changed the framework of all the projects to 2.0
| [Wednesday 17 November 2010] [16:44:00] <Guthur>	about to push the changes
| [Wednesday 17 November 2010] [16:45:38] <mikko>	when i run this
| [Wednesday 17 November 2010] [16:45:38] <mikko>	mdtool build --configuration:'POSIX_RELEASE|x86' clrzmq.sln 
| [Wednesday 17 November 2010] [16:45:45] <mikko>	it seems to output that it's building
| [Wednesday 17 November 2010] [16:45:57] <mikko>	but i can't find any build artifacts
| [Wednesday 17 November 2010] [16:46:59] <Guthur>	ok
| [Wednesday 17 November 2010] [16:47:10] <Guthur>	I will admit I have been using debug more than release
| [Wednesday 17 November 2010] [16:48:49] <mikko>	i should get a .dll out of the build process, right?
| [Wednesday 17 November 2010] [16:48:55] <Guthur>	yep
| [Wednesday 17 November 2010] [16:48:58] <Guthur>	just checking now
| [Wednesday 17 November 2010] [16:49:12] <mikko>	can you try building with either xbuild or mdtool?
| [Wednesday 17 November 2010] [16:49:17] <Guthur>	i'm using now
| [Wednesday 17 November 2010] [16:49:40] <Guthur>	it's in release folder for me
| [Wednesday 17 November 2010] [16:49:52] <Guthur>	clrzmq/bin/release
| [Wednesday 17 November 2010] [16:50:14] <mikko>	whats your mdtool line?
| [Wednesday 17 November 2010] [16:50:26] <Guthur>	I copied directly from you
| [Wednesday 17 November 2010] [16:50:32] <Guthur>	mdtool build --configuration:'POSIX_RELEASE|x86'
| [Wednesday 17 November 2010] [16:51:48] <mikko>	nothing here
| [Wednesday 17 November 2010] [16:51:59] <Guthur>	umm, let me push something first, ok
| [Wednesday 17 November 2010] [16:52:20] <mikko>	sure
| [Wednesday 17 November 2010] [16:52:44] <Guthur>	I want to change it to /bin/Debug for one thing
| [Wednesday 17 November 2010] [16:53:08] <Guthur>	it seems to always want to create that directory no matter what I set the output directory to
| [Wednesday 17 November 2010] [16:53:43] <Guthur>	so it now it ends up with /debug and /Debug, even though the output only goes to /debug
| [Wednesday 17 November 2010] [16:55:52] <mikko>	dmcs command is mono's preview implementation of framework 4.0
| [Wednesday 17 November 2010] [16:56:03] <mikko>	because the requirement is 4.0 xbuild tries to invoke it
| [Wednesday 17 November 2010] [16:56:10] <mikko>	and i don't have it installed
| [Wednesday 17 November 2010] [17:01:08] <Guthur>	clrzmq2 targets 2.0 and above
| [Wednesday 17 November 2010] [17:01:42] <Guthur>	It would be nice to have some of the sugar with 4.0 but it's probably better to support the wider install base
| [Wednesday 17 November 2010] [17:01:47] <mikko>	Guthur: sed -i s/v4.0/v2.0/ */*.csproj
| [Wednesday 17 November 2010] [17:01:50] <mikko>	and it builds
| [Wednesday 17 November 2010] [17:02:02] <Guthur>	I have change it back to 2.0
| [Wednesday 17 November 2010] [17:02:02] <mikko>	xbuild /property:Configuration=POSIX_RELEASE /property:Platform=x86
| [Wednesday 17 November 2010] [17:02:08] <mikko>	that is the xbuild line
| [Wednesday 17 November 2010] [17:02:20] <Guthur>	MSVS decided it knew best and changed it to 2.0 when I converted the solution
| [Wednesday 17 November 2010] [17:02:24] <Guthur>	2.0/4.0
| [Wednesday 17 November 2010] [17:03:18] <Guthur>	I want to see if I can suppress the 3 warnings then I will push
| [Wednesday 17 November 2010] [17:07:32] <mikko>	in any case it's added here http://build.valokuva.org/job/clrzmq2-master_ZeroMQ2-master_xbuild/
| [Wednesday 17 November 2010] [17:07:41] <mikko>	it should build in 5am GMT daily build
| [Wednesday 17 November 2010] [17:12:10] <Guthur>	I'm just about to push
| [Wednesday 17 November 2010] [17:12:28] <Guthur>	mikko, one thing does mdtool, generate app.config?
| [Wednesday 17 November 2010] [17:13:56] <Guthur>	nvm, I think it is fine
| [Wednesday 17 November 2010] [17:13:58] <Guthur>	pushing
| [Wednesday 17 November 2010] [17:15:21] <Guthur>	pushed
| [Wednesday 17 November 2010] [17:15:48] <Guthur>	Sorry it wasn't as streamed lined as it could have been
| [Wednesday 17 November 2010] [17:16:01] <Guthur>	but many thanks for testing, much appreciated
| [Wednesday 17 November 2010] [17:16:38] <Guthur>	sorting out all this build issues proofs way more challenging and fiddly than the actual coding, hehe
| [Wednesday 17 November 2010] [17:16:57] <mikko>	still fails
| [Wednesday 17 November 2010] [17:17:02] <mikko>	i'll look into it in a min
| [Wednesday 17 November 2010] [17:17:07] <mikko>	need to iron a shirt for tomorrow
| [Wednesday 17 November 2010] [17:17:12] <Guthur>	no problem
| [Wednesday 17 November 2010] [17:20:33] <Guthur>	umm it throws errors yet it generates the dll
| [Wednesday 17 November 2010] [17:22:30] <Guthur>	ah i think it is something to do with the test projects
| [Wednesday 17 November 2010] [17:23:37] <Guthur>	mikko, do the test projects need to be built?
| [Wednesday 17 November 2010] [17:24:32] <Guthur>	oh I see the problem
| [Wednesday 17 November 2010] [17:24:36] <Guthur>	oops, my bad
| [Wednesday 17 November 2010] [17:24:47] <Guthur>	those app.config file were being tracked
| [Wednesday 17 November 2010] [17:26:36] <Guthur>	mikko: could you pull again, and try to build
| [Wednesday 17 November 2010] [17:26:46] <Guthur>	once you shirt is ironed of course, hehe
| [Wednesday 17 November 2010] [17:26:51] <Guthur>	your*
| [Wednesday 17 November 2010] [17:27:36] <mikko>	built 
| [Wednesday 17 November 2010] [17:27:45] <Guthur>	cool
| [Wednesday 17 November 2010] [17:27:46] <mikko>	** (local_lat/bin/Debug/local_lat.exe:2844): WARNING **: Shutting down finalizer thread timed out.
| [Wednesday 17 November 2010] [17:27:52] <mikko>	in test program
| [Wednesday 17 November 2010] [17:28:00] <Guthur>	umm
| [Wednesday 17 November 2010] [17:28:03] <mikko>	am i running the test programs correctly?
| [Wednesday 17 November 2010] [17:28:10] <mikko>	i've no idea what those bins do
| [Wednesday 17 November 2010] [17:28:12] <mikko>	(never had)
| [Wednesday 17 November 2010] [17:28:22] <Guthur>	they are not thoroughly tested to be honest
| [Wednesday 17 November 2010] [17:28:49] <mikko>	http://build.valokuva.org/job/clrzmq2-master_ZeroMQ2-master_xbuild/4/console
| [Wednesday 17 November 2010] [17:28:54] <Guthur>	_thr
| [Wednesday 17 November 2010] [17:28:56] <Guthur>	was working
| [Wednesday 17 November 2010] [17:29:46] <Guthur>	I'll see if I can pin it down
| [Wednesday 17 November 2010] [17:32:57] <Guthur>	Sounds a little like the GC isn't cleaning up something
| [Wednesday 17 November 2010] [17:33:26] <Guthur>	I probably should call Dispose on Socket and Context Explicitly
| [Wednesday 17 November 2010] [17:34:39] <mikko>	am i running the test programs correctly?
| [Wednesday 17 November 2010] [17:44:19] <Guthur>	Yeah, it seems fine
| [Wednesday 17 November 2010] [17:44:29] <Guthur>	It would probably throw some error otherwise
| [Wednesday 17 November 2010] [17:44:37] <Guthur>	I think its the dispose process
| [Wednesday 17 November 2010] [17:44:44] <Guthur>	I am going to investigate
| [Wednesday 17 November 2010] [17:45:43] <mikko>	maybe socket is not disposed when it comes to disposing context?
| [Wednesday 17 November 2010] [17:45:47] <Guthur>	clrzmq2 inherited the dispose code from clrzmq and think it might be broken
| [Wednesday 17 November 2010] [17:47:01] <mikko>	i've seen this warning with clrzmq as well
| [Wednesday 17 November 2010] [17:47:09] <mikko>	this wasnt a problem before 2.1.x branch
| [Wednesday 17 November 2010] [17:47:23] <Guthur>	ok, this is worth checking out
| [Wednesday 17 November 2010] [17:47:36] <Guthur>	Give me a while to get to the bottom of it
| [Wednesday 17 November 2010] [17:47:50] <Guthur>	going to do some research on Dispose
| [Wednesday 17 November 2010] [17:48:24] <mikko>	ure, no hurry
| [Wednesday 17 November 2010] [17:48:30] <mikko>	the build is now added in any case
| [Wednesday 17 November 2010] [17:54:46] <Guthur>	ok the base code is fine, just the test programs are bogus
| [Wednesday 17 November 2010] [17:55:00] <Guthur>	they should explicitly dispose
| [Wednesday 17 November 2010] [17:55:06] <Guthur>	I'll fix those now
| [Wednesday 17 November 2010] [17:56:14] <mikko>	cool
| [Wednesday 17 November 2010] [18:01:44] <mikko>	i'm off to bed
| [Wednesday 17 November 2010] [18:01:47] <mikko>	see you tomorrow
| [Wednesday 17 November 2010] [18:04:35] <Guthur>	ok, thanks mikko 
| [Thursday 18 November 2010] [04:10:39] <vegaicm>	Question: is it possible for an application to have multiple I/O threads (and therefore multiple zmq sockets) binding on the same TCP port? What I want to achieve is something similar to the classic spawning a limited number of threads for each new accepted connection. Considering the architecture of zeromq this seems not possible, but having this option may increase throughput.
| [Thursday 18 November 2010] [04:13:17] <guido_g>	first, io-threads are mq internal things and it is unlikely that you'll ever need more than one
| [Thursday 18 November 2010] [04:13:55] <guido_g>	second, some worker pool examples are shown in the guide
| [Thursday 18 November 2010] [04:15:13] <guido_g>	you can create forwarder reading incomming messages and distributing them to the workers with a few lines of code, again see the guide for examples
| [Thursday 18 November 2010] [04:16:40] <vegaicm>	guido_g: I tried the simple hello work multithread , but I am not really impressed by its performance. Because all the messages pass though one devices I see it as a bottleneck. I was thinking to create more devices on different ports, but this not really what I was looking for: all the devices on the same port
| [Thursday 18 November 2010] [04:17:36] <guido_g>	you're going through this port anyway on os level, so i can't see any problem
| [Thursday 18 November 2010] [04:18:34] <Guthur>	vegaicm: If you look at the device code there is actually not much there
| [Thursday 18 November 2010] [04:18:47] <Guthur>	it just receives a message and passes it on
| [Thursday 18 November 2010] [04:19:33] <Guthur>	If that becomes a bottleneck I'd hazard that things have become too granular and you are not doing enough in your worker threads
| [Thursday 18 November 2010] [04:21:08] <guido_g>	w/o a more or less detailed description of the work to do and the message frequency all one can do is to guess
| [Thursday 18 November 2010] [04:22:29] <vegaicm>	guido_g, Guthur : what I meant is that with a zmq device I have 1 thread processing all the communication though a TCP socket. While if I can have more then 1 threads managing tcp/ip communication I can hare more throughput. Give me a minute and I will try to describe what I am comparing, but Guthur you are right: the worker threads aren't doing much ... details coming now
| [Thursday 18 November 2010] [04:23:28] <guido_g>	vegaicm: read the guide, it explains what you can do in various simple examples, really
| [Thursday 18 November 2010] [04:25:42] <vegaicm>	I created a simple application using standard socket programming. This application spawn 1 thread for each incoming connection and process client requests. What the application does is to get a key=>value from the client and write a it in a hash table with the proper mutex handling. I can reach 360k SET/sec .  With zmq using 1 device and 10 workers that do absolutely nothing I can't go beyond the 45k messages/sec
| [Thursday 18 November 2010] [04:26:22] <vegaicm>	guido_g: I will check the guide again, maybe I missed something in there. Thanks.
| [Thursday 18 November 2010] [04:26:34] <guido_g>	http://zguide.zeromq.org/chapter:all#toc33
| [Thursday 18 November 2010] [04:27:24] <vegaicm>	guido_g: I read it, and tried that code. It doesn't meet my expectation :-/
| [Thursday 18 November 2010] [04:27:40] <vegaicm>	"You cannot use sockets except in the thread that created them."
| [Thursday 18 November 2010] [04:27:45] <guido_g>	so?
| [Thursday 18 November 2010] [04:28:11] <vegaicm>	it is a bottleneck for me
| [Thursday 18 November 2010] [04:28:22] <guido_g>	sure
| [Thursday 18 November 2010] [04:30:49] <vegaicm>	I can create multiple ZMQ_REQ sockets and multiple workers pool, but this would mean I have to bind on multiple TCP ports
| [Thursday 18 November 2010] [04:31:19] <guido_g>	sounds fishy, but hey...
| [Thursday 18 November 2010] [04:31:59] <Guthur>	vegaicm: are you using inproc connections at the worker end of the device?
| [Thursday 18 November 2010] [04:32:56] <vegaicm>	correct, is fishy , especially for the client . Unless the client itself is a multithread application that connects to multiple socket.
| [Thursday 18 November 2010] [04:33:24] <vegaicm>	Guthur: yes, inproc between workers. tcp only for client-server comunication
| [Thursday 18 November 2010] [04:43:18] <Guthur>	guido_g: Does that performance hit sound right? I'd imagine that there would be some overhead but that seems like quite a bit.
| [Thursday 18 November 2010] [04:45:50] <guido_g>	depends on the implementation i'd say
| [Thursday 18 November 2010] [04:46:27] <guido_g>	but mq is not a "one size fits all" thing
| [Thursday 18 November 2010] [04:56:32] <vegaicm>	Guthur, guido_g : this is a *vague* idea of what I mean: http://pastebin.com/BWcT62GK . On 127.0.0.1 and with TCP,  1 client - 1 server I have 100k/4.485 = 22.3k messages processed per second.  If I have 10 clients and 10 servers, the messages processed are 100k x 10 / 6.379 (the slower client) = 156.8k messages per second. If I increase the number of clients/servers the figures go even better.
| [Thursday 18 November 2010] [05:03:16] <guido_g>	and what you're showing?
| [Thursday 18 November 2010] [05:08:41] <vegaicm>	guido_g: look this: http://pastebin.com/GXbDiS9F . I start 10 clients that connect to a multithread server that has 10 workers . 10 clients -> 1 MT server = 41.8k msg/sec .   10 clients -> 10 server = 156.8k msg/sec .    Where is the bottleneck? I doubt it is in inproc, but in the tcp socket
| [Thursday 18 November 2010] [05:10:06] <guido_g>	again, what do you want to show? 
| [Thursday 18 November 2010] [05:10:51] <vegaicm>	I want to show that there is a bottleneck in having just 1 threads processing messages from a tcp port
| [Thursday 18 November 2010] [05:11:57] <guido_g>	this is something widely known, but ok
| [Thursday 18 November 2010] [05:13:01] <vegaicm>	guido_g: ok :) Then , what I am adding too is that having multiple threads on the same tcp port can increase performance a lot.
| [Thursday 18 November 2010] [05:14:06] <guido_g>	threads on a port?
| [Thursday 18 November 2010] [05:15:29] <vegaicm>	yep . With standard socket programming this is possible and quite easy. For example you can have the main process binded on the socket and waiting for connection. For each connection spawns a threads.
| [Thursday 18 November 2010] [05:15:47] <vegaicm>	but by design I think this is impossible in zeromq
| [Thursday 18 November 2010] [05:16:02] <guido_g>	it's outright stupid
| [Thursday 18 November 2010] [05:16:55] <guido_g>	given the fact that a single server can process thousands of ongoing connections
| [Thursday 18 November 2010] [05:17:37] <guido_g>	this is why queueing and a worker pool is used
| [Thursday 18 November 2010] [05:21:37] <vegaicm>	what if I am ok to have hundreds/thousands of threads. As I was saying, I have a prototype of an application that spawn 1000 threads and processes requests from 1000 clients at a very good speed, 360k requests/sec . And it isn't just a "hello world" where the workers do nothing, but it actually process some few GB of data
| [Thursday 18 November 2010] [05:22:01] <vegaicm>	and I would love to reach the same performance using zeromq , if possible
| [Thursday 18 November 2010] [05:22:12] 	 * guido_g gives up
| [Thursday 18 November 2010] [05:22:48] <vegaicm>	thanks :D
| [Thursday 18 November 2010] [05:42:12] <pieterh>	hi vegaicm 
| [Thursday 18 November 2010] [05:42:56] <pieterh>	would you like to discuss high performance server architectures?
| [Thursday 18 November 2010] [05:43:31] <vegaicm>	hi pieterh . Sure
| [Thursday 18 November 2010] [05:43:49] <pieterh>	first of all, what is the work your threads are doing?
| [Thursday 18 November 2010] [05:45:31] <vegaicm>	right now the worker threads in zeromq they just send the "world" string back to the client, nothing more. But my future idea is to use the workers to process data in a key=>value storage
| [Thursday 18 November 2010] [05:46:02] <pieterh>	your basic architecture depends on the kinds of work you are doing
| [Thursday 18 November 2010] [05:46:06] <pieterh>	i will explain
| [Thursday 18 November 2010] [05:46:21] <pieterh>	some tasks are totally independent, e.g. "here is a data set, compute me some stuff on it"
| [Thursday 18 November 2010] [05:46:42] <pieterh>	some tasks are highly interdependent, e.g. "get me something from a database"
| [Thursday 18 November 2010] [05:47:02] <pieterh>	in the first case, you can create a highly concurrent (parallel) architecture
| [Thursday 18 November 2010] [05:47:20] <pieterh>	in the second case that is fairly pointless and you can use a more serial architecture
| [Thursday 18 November 2010] [05:47:28] <pieterh>	ack?
| [Thursday 18 November 2010] [05:47:33] <vegaicm>	ack so far
| [Thursday 18 November 2010] [05:48:06] <pieterh>	now you need to get requests from clients and transfer them to your workers as rapidly as you can
| [Thursday 18 November 2010] [05:48:22] <pieterh>	workers can be processes, threads, or whatever
| [Thursday 18 November 2010] [05:48:32] <pieterh>	there are many strategies for doing this
| [Thursday 18 November 2010] [05:48:49] <pieterh>	indeed, starting a thread for each client is one option.  Some architectures start a process for each client.
| [Thursday 18 November 2010] [05:48:56] <pieterh>	on Linux, a process, a thread, it's much the same
| [Thursday 18 November 2010] [05:49:18] <pieterh>	both are fairly heavy mechanisms
| [Thursday 18 November 2010] [05:49:37] <vegaicm>	ack on all this too
| [Thursday 18 November 2010] [05:49:40] <pieterh>	ack?
| [Thursday 18 November 2010] [05:50:00] <vegaicm>	yep
| [Thursday 18 November 2010] [05:50:02] <pieterh>	so in general when you come to ask for architecture advice, do not explain your solutions
| [Thursday 18 November 2010] [05:50:14] <pieterh>	but rather explain your problems and then collect possible solutions
| [Thursday 18 November 2010] [05:50:51] <pieterh>	now I'll explain the very fastest possible model for getting stuff off a network and to workers
| [Thursday 18 November 2010] [05:51:12] <vegaicm>	ok, I am following you
| [Thursday 18 November 2010] [05:51:15] <pieterh>	first of all, you have one thread per network device
| [Thursday 18 November 2010] [05:51:27] <pieterh>	so that data can flow without interrupts
| [Thursday 18 November 2010] [05:51:32] <pieterh>	second, you have one thread per worker
| [Thursday 18 November 2010] [05:51:42] <pieterh>	so that tasks can execute without interrupts
| [Thursday 18 November 2010] [05:51:54] <pieterh>	third, you connect these two sets of threads using lock-free queues
| [Thursday 18 November 2010] [05:52:00] <pieterh>	so that messages can flow without interrupts
| [Thursday 18 November 2010] [05:52:20] <CIA-20>	zeromq2: 03Mikko Koppanen 07master * r945c931 10/ (acinclude.m4 configure.in): 
| [Thursday 18 November 2010] [05:52:21] <CIA-20>	zeromq2: Run autoupdate on the configure.in
| [Thursday 18 November 2010] [05:52:21] <CIA-20>	zeromq2: I ran autoupdate on the configure.in, which generated most of the
| [Thursday 18 November 2010] [05:52:21] <CIA-20>	zeromq2: patch attached. There is also a small manual fix in which removes the
| [Thursday 18 November 2010] [05:52:21] <CIA-20>	zeromq2: warning "Remember to add LT_INIT to configure.in" which I assume is
| [Thursday 18 November 2010] [05:52:21] <CIA-20>	zeromq2: because AC_PROG_LIBTOOL was called inside a macro.
| [Thursday 18 November 2010] [05:52:21] <CIA-20>	zeromq2: Signed-off-by: Mikko Koppanen <mkoppanen@php.net> - http://bit.ly/ciuque
| [Thursday 18 November 2010] [05:52:40] <pieterh>	the single greatest slow down in a concurrent / multithread architecture is when threads are swapped in and out, or locked, or waiting
| [Thursday 18 November 2010] [05:53:05] <pieterh>	ideally, thus, you end up with exactly 1 thread per CPU, running full speed without any locks
| [Thursday 18 November 2010] [05:53:07] <pieterh>	ack?
| [Thursday 18 November 2010] [05:53:22] <vegaicm>	I am following you 100% so far
| [Thursday 18 November 2010] [05:53:41] <pieterh>	you understand that this is very different than "one thread per client", which will result in chaotic use of the CPU cores
| [Thursday 18 November 2010] [05:53:53] <pieterh>	now here is the difficulty
| [Thursday 18 November 2010] [05:54:14] <pieterh>	creating these three layers that i described (i/o, workers, queues) is very very hard
| [Thursday 18 November 2010] [05:54:26] <pieterh>	that is why practically no projects do this
| [Thursday 18 November 2010] [05:54:32] <pieterh>	and so, people use techniques like you described
| [Thursday 18 November 2010] [05:54:48] <pieterh>	happily, we made zeromq for you
| [Thursday 18 November 2010] [05:54:53] <pieterh>	and it does exactly this
| [Thursday 18 November 2010] [05:55:28] <pieterh>	by design zeromq does not let you create one thread per client because it would be silly
| [Thursday 18 November 2010] [05:55:45] <pieterh>	what you do want control over
| [Thursday 18 November 2010] [05:55:50] <pieterh>	is the threading model for your workers
| [Thursday 18 November 2010] [05:56:15] <pieterh>	which is what zeromq gives you... you decide exactly how to architect your workers across one or more boxes
| [Thursday 18 November 2010] [05:57:00] <pieterh>	if you need to, you can start more than 1 I/O thread
| [Thursday 18 November 2010] [05:57:24] <pieterh>	does this all make sense?
| [Thursday 18 November 2010] [05:57:57] <vegaicm>	the 1 I/O seems to be my current limitation, because I have multiple TCP circuit handles by a single I/O thread. Is this correct?
| [Thursday 18 November 2010] [05:58:18] <pieterh>	note that 1 I/O thread can handle a _lot_ of messages per second
| [Thursday 18 November 2010] [05:58:29] <pieterh>	like several million
| [Thursday 18 November 2010] [05:58:43] <vegaicm>	on TCP ?
| [Thursday 18 November 2010] [05:58:48] <pieterh>	most of what you think you know about performance is, unfortunately, wrong
| [Thursday 18 November 2010] [05:58:49] <pieterh>	yes
| [Thursday 18 November 2010] [05:59:43] <pieterh>	you can monitor your system, under load, and test with more I/O threads
| [Thursday 18 November 2010] [05:59:50] <pieterh>	that is useful if you have more NICs
| [Thursday 18 November 2010] [06:00:48] <vegaicm>	pieterh: how can I test the maximum number of msgs/sec a I/O thread can process over TCP ?
| [Thursday 18 November 2010] [06:01:08] <pieterh>	use the performance test tools provided with zeromq
| [Thursday 18 November 2010] [06:01:17] <pieterh>	vegaicm, have you read the Guide?
| [Thursday 18 November 2010] [06:02:53] <vegaicm>	pieterh: tbh only the first two chapters. The multi-thread approach is what I was interested and I wanted to test it before going further
| [Thursday 18 November 2010] [06:04:45] <pieterh>	with zeromq you have to abandon your view of a server as a big thing with many clients
| [Thursday 18 November 2010] [06:04:55] <pieterh>	think instead of a cluster of servers
| [Thursday 18 November 2010] [06:05:03] <pieterh>	no central bottlenecks
| [Thursday 18 November 2010] [06:08:56] <pieterh>	vegaicm, I need to go, I hope this has helped you
| [Thursday 18 November 2010] [06:09:12] <vegaicm>	a cluster of servers is my aim. And inter-servers communications is what I need fast. This is why I was thinking to multiple I/O threads that manage persistent connections between clients and servers and between servers. So actually I don't want an unlimited number of I/O threads spawned on demands, but a limited (and almost predefined) but high number of connections.
| [Thursday 18 November 2010] [06:09:44] <vegaicm>	pieterh: thanks a lot for your time, I will continue the read of the guide, maybe later on there will be something more relevant for the problem I have. Thanks again
| [Thursday 18 November 2010] [06:09:57] <pieterh>	kindly, don't try to do 0MQ's work, it's not constructive
| [Thursday 18 November 2010] [06:10:34] <vegaicm>	ack :)
| [Thursday 18 November 2010] [06:11:08] <pieterh>	as well as reading the guide, make your own simple examples
| [Thursday 18 November 2010] [06:11:25] <pieterh>	and when you find _real_, not _imagined_ performance issues, let's talk again
| [Thursday 18 November 2010] [06:11:56] <vegaicm>	pieterh: will do that. Thanks.
| [Thursday 18 November 2010] [07:48:52] <mikko>	good morning
| [Thursday 18 November 2010] [07:49:38] <Guthur>	morning mikko
| [Thursday 18 November 2010] [07:49:46] <Guthur>	cheers for the help last night
| [Thursday 18 November 2010] [07:50:10] <Guthur>	Hopefully the test applications should execute without exceptions now
| [Thursday 18 November 2010] [07:55:07] <mikko>	Guthur: haven't checked this morning
| [Thursday 18 November 2010] [07:55:26] <mikko>	no warnings no
| [Thursday 18 November 2010] [07:55:28] <mikko>	w
| [Thursday 18 November 2010] [08:13:41] <Guthur>	mikko, cool
| [Thursday 18 November 2010] [09:56:14] <mikko>	sustrik: icc build: nbytes != -1 (tcp_socket.cpp:197)
| [Thursday 18 November 2010] [10:02:49] <sustrik>	mikko: we have to find out what's the errno at theat point...
| [Thursday 18 November 2010] [10:03:24] <sustrik>	it should be reported to stderr
| [Thursday 18 November 2010] [10:03:27] <sustrik>	let me look
| [Thursday 18 November 2010] [10:04:10] <mikko>	/bin/bash: line 5:  8278 Aborted                 ${dir}$tst
| [Thursday 18 November 2010] [10:04:19] <mikko>	Bad file descriptor
| [Thursday 18 November 2010] [10:04:20] <sustrik>	Bad File Descriptor
| [Thursday 18 November 2010] [10:04:29] <mikko>	maybe it's a race condition
| [Thursday 18 November 2010] [10:04:35] <sustrik>	yes
| [Thursday 18 November 2010] [10:04:38] <mikko>	as multiple builds might try to bind to same things
| [Thursday 18 November 2010] [10:04:43] <sustrik>	maybe one of the problems already reported on the ML
| [Thursday 18 November 2010] [10:05:09] <sustrik>	mikko: all builds go to the same directory?
| [Thursday 18 November 2010] [10:05:58] <mikko>	sustrik: nope
| [Thursday 18 November 2010] [10:06:11] <mikko>	sustrik: but they might try to bind at the same time
| [Thursday 18 November 2010] [10:06:12] <sustrik>	good
| [Thursday 18 November 2010] [10:06:17] <mikko>	if you have concurrent builds
| [Thursday 18 November 2010] [10:06:24] <sustrik>	aha
| [Thursday 18 November 2010] [10:06:24] <mikko>	only GCC builds do 'make install'
| [Thursday 18 November 2010] [10:06:26] <sustrik>	true
| [Thursday 18 November 2010] [10:06:43] <sustrik>	anyway, this is a different problem
| [Thursday 18 November 2010] [10:06:47] <sustrik>	a buf in 0mq itself
| [Thursday 18 November 2010] [10:06:50] <sustrik>	bug
| [Thursday 18 November 2010] [10:07:05] <mikko>	non icc specific?
| [Thursday 18 November 2010] [10:07:43] <sustrik>	i don't think so
| [Thursday 18 November 2010] [10:08:13] <sustrik>	it looks like we are trying to use a file desctiptor that we've already closed
| [Thursday 18 November 2010] [11:52:35] <mikko>	sustrik: there?
| [Thursday 18 November 2010] [22:02:39] <gancient>	hi all, i am trying to install python bindings for zeromq and it installs fine, but while importing i get the following error
| [Thursday 18 November 2010] [22:03:41] <gancient>	ImportError: cannot import name initthreads
| [Thursday 18 November 2010] [22:03:55] <gancient>	what does , build "in place" mean ?
| [Thursday 18 November 2010] [22:06:59] <nettok>	gancient: you ran "ldconfig" after installing zeromq lib?
| [Thursday 18 November 2010] [22:14:07] <gancient>	nettok: yes
| [Thursday 18 November 2010] [22:14:35] <gancient>	nettok: what is "build in place" it is necessary for running the pyzeromq test suite
| [Thursday 18 November 2010] [22:17:48] <fowlduck>	ah, a crapton of people
| [Thursday 18 November 2010] [22:18:07] <fowlduck>	so, how are people using zeromq in the wild?
| [Thursday 18 November 2010] [22:18:33] <fowlduck>	i'm just trying to wrap my head around how i could use it
| [Thursday 18 November 2010] [22:18:47] <fowlduck>	particularly for using it to queue long-running jobs
| [Thursday 18 November 2010] [22:18:54] <nettok>	I might be wrong but I think that is running "python setup.py build"
| [Thursday 18 November 2010] [22:19:45] <nettok>	did you copied setup.cfg.template -> setup.cfg
| [Thursday 18 November 2010] [22:20:07] <nettok>	I don't know what else could be
| [Thursday 18 November 2010] [22:20:43] <gancient>	nettok: i just closed the terminal and started back, and the import error mysteriously goes away !
| [Thursday 18 November 2010] [22:21:05] <gancient>	nettok: now no error with "import zmq" 
| [Thursday 18 November 2010] [22:21:38] <nettok>	gancient: :)
| [Thursday 18 November 2010] [22:22:30] <gancient>	nettok: any idea why this might have happened ?
| [Thursday 18 November 2010] [23:12:28] <nettok_>	why there isn't a "disconnect" in zmq sockets?
| [Thursday 18 November 2010] [23:56:23] <nettok_>	How do I disconnect a socket from a single endpoint without closing the socket?
| [Friday 19 November 2010] [00:13:20] <cremes>	nettok_: you can't
| [Friday 19 November 2010] [00:14:38] <nettok_>	cremes: well, that sucks
| [Friday 19 November 2010] [00:20:06] <nettok_>	I guess i'll have to sacrifice auto load-balancing and have one socket per pusher
| [Friday 19 November 2010] [02:53:15] <travlr>	sustrik: morning. are you around?
| [Friday 19 November 2010] [02:55:12] <sustrik>	travlr: hi
| [Friday 19 November 2010] [02:55:14] <sustrik>	morning
| [Friday 19 November 2010] [02:55:50] <travlr>	well, it took me a couple more days. it's been a busy week.
| [Friday 19 November 2010] [02:55:52] <travlr>	but
| [Friday 19 November 2010] [02:56:06] <travlr>	heres the first go of it http://travlr.github.com/zmqirclog/
| [Friday 19 November 2010] [02:57:29] <sustrik>	wow
| [Friday 19 November 2010] [02:57:32] <sustrik>	great
| [Friday 19 November 2010] [02:57:40] <travlr>	still needs some work
| [Friday 19 November 2010] [02:57:40] <sustrik>	can i link it from the website?
| [Friday 19 November 2010] [02:57:44] <travlr>	sure
| [Friday 19 November 2010] [02:58:28] <travlr>	this is in raw form... should i remove some of the noise like 'joins' and 'quits'?
| [Friday 19 November 2010] [02:59:53] <sustrik>	done
| [Friday 19 November 2010] [03:00:19] <sustrik>	travlr: i would keep it in such a form as to minimise work on uploading new archives
| [Friday 19 November 2010] [03:00:50] <travlr>	well its pretty easy actually. I'm already parsing lines.
| [Friday 19 November 2010] [03:01:16] <sustrik>	it's up to you then
| [Friday 19 November 2010] [03:01:35] <travlr>	ok then. cleaner is nicer... no?
| [Friday 19 November 2010] [03:02:26] <sustrik>	sure :)
| [Friday 19 November 2010] [03:02:48] <travlr>	next, when i find some time, is to rebuild the zmqircd
| [Friday 19 November 2010] [03:03:05] <travlr>	its broken being single threaded
| [Friday 19 November 2010] [03:03:38] <sustrik>	it tends to quit
| [Friday 19 November 2010] [03:03:42] <sustrik>	when commits are done
| [Friday 19 November 2010] [03:03:45] <travlr>	yup
| [Friday 19 November 2010] [03:04:00] <travlr>	i'll get to sometime soon
| [Friday 19 November 2010] [03:04:58] <travlr>	btw, this is a manual upload for now, because building with sphinx is in efficient... i may use something else... so...
| [Friday 19 November 2010] [03:05:15] <travlr>	i'll upload on sporatic occasion for now.
| [Friday 19 November 2010] [03:05:24] <sustrik>	sure
| [Friday 19 November 2010] [03:05:37] <sustrik>	understood, manual upload sucks
| [Friday 19 November 2010] [03:06:01] <travlr>	no.. its automated, but its not on a cron yet
| [Friday 19 November 2010] [03:06:31] <travlr>	it takes 5 solid minutes to build each time and 90% proc power
| [Friday 19 November 2010] [03:06:49] <travlr>	it's not smart enough to only build the new page
| [Friday 19 November 2010] [03:08:35] <travlr>	ok, gotta go for now.. have a nice day
| [Friday 19 November 2010] [03:08:35] <sustrik>	i see
| [Friday 19 November 2010] [03:08:39] <sustrik>	see you
| [Friday 19 November 2010] [03:11:53] <CIA-20>	zeromq2: 03Mikko Koppanen 07master * redf7c18 10/ (acinclude.m4 configure.in): (log message trimmed)
| [Friday 19 November 2010] [03:11:53] <CIA-20>	zeromq2: Add a check that the compiler actually works.
| [Friday 19 November 2010] [03:11:53] <CIA-20>	zeromq2: The patch tests that the C and C++ compilers actually exist
| [Friday 19 November 2010] [03:11:53] <CIA-20>	zeromq2: and work. autoconf seems to default to 'g++' when C++ compiler is not
| [Friday 19 November 2010] [03:11:53] <CIA-20>	zeromq2: found, which causes the following error (when the compiler isn't
| [Friday 19 November 2010] [03:11:54] <CIA-20>	zeromq2: there):
| [Friday 19 November 2010] [03:11:55] <CIA-20>	zeromq2: checking for uuid_generate in -luuid... no
| [Friday 19 November 2010] [06:36:37] <CIA-20>	zeromq2: 03Martin Sustrik 07master * rac40680 10/ src/object.cpp : 
| [Friday 19 November 2010] [06:36:38] <CIA-20>	zeromq2: Problem with blob_t initialisation fixed.
| [Friday 19 November 2010] [06:36:38] <CIA-20>	zeromq2: HP's version of STL doesn't allow for initialisation of basic_string
| [Friday 19 November 2010] [06:36:38] <CIA-20>	zeromq2: (blob_t) using NULL pointer, while SGI's implementation is OK with
| [Friday 19 November 2010] [06:36:38] <CIA-20>	zeromq2: that. Fixed.
| [Friday 19 November 2010] [06:36:38] <CIA-20>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/d5OV4Y
| [Friday 19 November 2010] [17:10:54] <nettok>	Is it possible to force dropping of the queued messages in an XREQ socket?
| [Friday 19 November 2010] [17:12:39] <TomHome>	noob question : what's the difference between rabbitmq and zeromq ?
| [Friday 19 November 2010] [17:15:10] <cremes>	nettok: yes, by closing the socket; all unsent messages will be dropped
| [Friday 19 November 2010] [17:15:33] <nettok>	cremes: thank you
| [Friday 19 November 2010] [17:15:45] <cremes>	TomHome: i think your best bet is to google for that answer; it's been covered a bunch by folks far more glib than i
| [Friday 19 November 2010] [17:17:07] <travlr>	you might also want to scan the new zeromq irc logs i put up this morning...
| [Friday 19 November 2010] [17:17:29] <travlr>	http://travlr.github.com/zmqirclog/
| [Friday 19 November 2010] [17:18:32] <travlr>	cremes: i think that you mentioned that you might have some logs of this channel... do you still have them?
| [Friday 19 November 2010] [17:22:09] <cremes>	travlr: i do; do you want them?
| [Friday 19 November 2010] [17:22:26] <cremes>	if so, give me a date range
| [Friday 19 November 2010] [17:23:19] <travlr>	at the moment, i know i need around the last few days of June to around July 14
| [Friday 19 November 2010] [17:23:58] <travlr>	i'm not sure if that is the biggest gap i have or not.
| [Friday 19 November 2010] [17:24:24] <travlr>	there are various days and hours missing though.... i have to go through it yet
| [Friday 19 November 2010] [17:25:00] <cremes>	ok... the logs i have are via a mac app called colloquy and are in a weird xml format
| [Friday 19 November 2010] [17:25:07] <cremes>	they'll likely need conversion to be useful
| [Friday 19 November 2010] [17:25:34] <travlr>	that's ok.. can you upload them somewhere.. maybe github?
| [Friday 19 November 2010] [17:27:14] <cremes>	travlr: sure
| [Friday 19 November 2010] [17:27:20] <travlr>	thanks :)
| [Friday 19 November 2010] [17:28:07] <cremes>	i'll aim to do it tomorrow... i'm about to cut out now for the day
| [Friday 19 November 2010] [17:28:32] <travlr>	sure thing... no hurry.. 
| [Friday 19 November 2010] [17:41:19] <mikko>	travlr: http://valokuva.org/~mikko/zeromq.log
| [Friday 19 November 2010] [17:41:27] <mikko>	thats roughly from Wed Mar 31 20:29:51 2010
| [Friday 19 November 2010] [17:41:32] <mikko>	there might be some gaps
| [Friday 19 November 2010] [17:41:45] <travlr>	mikko, thank you
| [Friday 19 November 2010] [17:44:54] <doug>	huh, how can i tell if a message i get on a zmq socket has come from someone i've seen before?
| [Friday 19 November 2010] [17:46:04] <travlr>	pretty much by including something for that in your app's message layer
| [Friday 19 November 2010] [17:47:05] <doug>	ouch
| [Friday 19 November 2010] [17:47:11] <doug>	gonna make authentication a little difficult.
| [Friday 19 November 2010] [17:47:50] <travlr>	there has been recent discussions about authentication here and on the mail list. 
| [Friday 19 November 2010] [17:48:10] <doug>	i read a little bit of that on the list, know when it was discussed here?
| [Friday 19 November 2010] [17:48:21] <travlr>	the idea is to keep zmq fundamentally light and fast
| [Friday 19 November 2010] [17:48:35] <doug>	always nice.
| [Friday 19 November 2010] [17:48:41] <doug>	i gotta client to serve, tho.
| [Friday 19 November 2010] [17:49:10] <doug>	figured zmq might be a great choice based on the plug that's it's used for financial messaging.
| [Friday 19 November 2010] [17:49:34] <travlr>	i here ya... i use it for financial too... check the irc log search engine.. see the url above
| [Friday 19 November 2010] [17:50:05] <travlr>	and the mail list archives are linked on the website
| [Friday 19 November 2010] [17:50:56] <doug>	i've already gone through hits on "authentication" from the list archives
| [Friday 19 November 2010] [17:51:07] <travlr>	not enough info?
| [Friday 19 November 2010] [17:51:30] <travlr>	check for 'security' too.
| [Friday 19 November 2010] [17:52:51] <travlr>	remember that zmq is not necessarily 'internet' capable in itself
| [Friday 19 November 2010] [17:53:07] <travlr>	security wise...
| [Friday 19 November 2010] [17:55:35] <doug>	yes, of course.
| [Friday 19 November 2010] [17:55:43] <doug>	looks like xrep sockets would at least give me identity info.
| [Friday 19 November 2010] [17:56:42] <travlr>	i guess. i still have to involve myself more with the intracacies
| [Friday 19 November 2010] [17:57:17] <travlr>	i'm about to dig into zmq deeper now
| [Friday 19 November 2010] [17:58:18] <travlr>	pieter did a really nice job with the guide, i guess there is enough now for me to dig in 'deeper'
| [Friday 19 November 2010] [17:59:23] Away	You are now marked as being away.
| [Friday 19 November 2010] [18:03:41] <doug>	yup.  would be nice to have some history on the specific situations zmq was evolved to solve
| [Friday 19 November 2010] [18:17:07] <doug>	it's sort of like a subset of mpi, without a lot of the support infrastructure
| [Friday 19 November 2010] [18:17:17] <doug>	which i imagine makes it easier to deal with in a lot of ways
| [Friday 19 November 2010] [18:17:23] <doug>	a little less capable tho
| [Friday 19 November 2010] [18:19:54] <Guthur>	ZMQ seems to be more the foundation about which domain specific infrastructure solutions can be built
| [Friday 19 November 2010] [18:20:23] <Guthur>	I feel it help avoid ZMQ trying to many things badly and not many well
| [Friday 19 November 2010] [18:20:47] <doug>	i'm not sure what your first sentence actually means, guther.
| [Friday 19 November 2010] [18:21:51] <Guthur>	i.e. some other project will build that missing infrastructure you mentioned on top of ZMQ
| [Friday 19 November 2010] [18:22:46] <Guthur>	and so the vision of ZMQ will not get convoluted be some application specific requirements
| [Friday 19 November 2010] [18:23:53] <doug>	i'd guess that zmq is already the product of application specific requirements
| [Friday 19 November 2010] [18:25:01] <Guthur>	really, what application would that be
| [Friday 19 November 2010] [18:25:04] <doug>	knowing more about its history would help be to determine if my own application will benefit greatly from what zmq can solve.
| [Friday 19 November 2010] [18:26:29] <Guthur>	seems quite a generic message passing abstraction to me
| [Friday 19 November 2010] [18:26:48] <Guthur>	allowing a decent variety of transport protocols as well
| [Friday 19 November 2010] [18:26:50] <doug>	i don't know the specific application, but i did read about openamq not being quite what imatix wanted or needed
| [Friday 19 November 2010] [18:26:57] <doug>	for some scalable financial application
| [Friday 19 November 2010] [18:28:35] <Guthur>	But there is nothing in the API that ties it to the financial application domain
| [Friday 19 November 2010] [18:29:33] <doug>	why would there be?
| [Friday 19 November 2010] [18:29:38] <doug>	> From 2004-2007 iMatix built a new messaging protocol (AMQP) for JPMorganChase, implemented this as a software product (OpenAMQ), and helped JPMorganChase migrate their largest investment bank trading system off a legacy middleware and onto OpenAMQ.
| [Friday 19 November 2010] [18:30:29] <doug>	that might be handy for me, as my client is also (part of) that same company.
| [Friday 19 November 2010] [18:30:36] <doug>	unless they had some terrible experience with it.
| [Friday 19 November 2010] [18:31:30] <doug>	this makes sense, 0mq seems geared toward homogeneous networks with large consumer counts and a need for minimal delay
| [Friday 19 November 2010] [18:33:35] <doug>	and smaller messages.
| [Friday 19 November 2010] [18:38:48] <Guthur>	I'm sort of a similar situation, part of a financial company (investment banking) and I'd like to work ZMQ into a refactor of our application
| [Friday 19 November 2010] [18:39:55] <Guthur>	the applications architecture is a bit pants at the moment
| [Friday 19 November 2010] [18:40:08] <doug>	why would zmq make sense?
| [Friday 19 November 2010] [18:40:38] <Guthur>	well it has a lot of subsystems which at the minute are all using HTTP as the transport mechanism
| [Friday 19 November 2010] [18:40:52] <Guthur>	for some bizarre reason
| [Friday 19 November 2010] [18:41:04] <doug>	probably not so bizarre if you dig for the rationale.
| [Friday 19 November 2010] [18:41:32] <Guthur>	I can understand the customer facing connection being HTTP 
| [Friday 19 November 2010] [18:41:44] <Guthur>	HTTPS actually
| [Friday 19 November 2010] [18:42:08] <Guthur>	but internally I can't really see why the need for extra stack layer
| [Friday 19 November 2010] [18:42:19] <doug>	there's lots of existing feature-rich libraries that use http for the transport.
| [Friday 19 November 2010] [18:42:59] <doug>	and plenty of managers who are probably happy knowing that such a well-known and standard protocol is in use under the hood.
| [Friday 19 November 2010] [18:43:29] <Guthur>	wrong people being the decision about implementation if you ask me
| [Friday 19 November 2010] [18:43:48] <Guthur>	managers that is
| [Friday 19 November 2010] [18:44:56] <Guthur>	HTTP get shoehorned into doing things it was never designed to do
| [Friday 19 November 2010] [18:45:29] <doug>	eh, if it works well enough..
| [Friday 19 November 2010] [18:47:47] <Guthur>	we do quite a bit of data streaming in this application, with long polling
| [Friday 19 November 2010] [18:48:17] <Guthur>	and it goes through quite a few layers all using HTTP
| [Friday 19 November 2010] [18:48:33] <Guthur>	it just not very scalable in my opinion
| [Friday 19 November 2010] [18:49:39] <doug>	what's the bottleneck?
| [Friday 19 November 2010] [18:50:15] <Guthur>	To be honest I haven't been on the team long enough to get a complete handle on the situation
| [Friday 19 November 2010] [18:50:48] <Guthur>	but from discussions with more senior members it does sound like its the comms on the wire
| [Friday 19 November 2010] [18:51:06] <doug>	i'd find it hard to make a decision without some serious understanding of how that plays out.
| [Friday 19 November 2010] [18:51:39] <Guthur>	well none is being made to be honest
| [Friday 19 November 2010] [18:51:58] <Guthur>	I have one part of it to port from a Java JMS to C#
| [Friday 19 November 2010] [18:52:09] <Guthur>	and I'd like to use ZMQ there if possible
| [Friday 19 November 2010] [18:52:52] <doug>	if i were you, i'd worry about having my decision be viewed as bizarre by the next guy who gets stuck with the result.
| [Friday 19 November 2010] [18:53:34] <Guthur>	Not sure how ZMQ is bizarre
| [Friday 19 November 2010] [18:53:41] <Guthur>	to me using HTTP is bizarre
| [Friday 19 November 2010] [18:54:11] <doug>	any protocol, library, or tool choice is going to be bizarre for a large number of applications.
| [Friday 19 November 2010] [18:54:23] Away	You are no longer marked as being away.
| [Friday 19 November 2010] [18:54:48] <doug>	i'm pretty sure it's not going to be a great choice for what i'm doing.
| [Friday 19 November 2010] [18:54:58] <Guthur>	well this particular part of the application will be getting alot of spot price data
| [Friday 19 November 2010] [18:55:06] <Guthur>	and publishing it
| [Friday 19 November 2010] [18:55:20] <doug>	that sounds closer suited to zmq than my stuff
| [Friday 19 November 2010] [18:55:56] <doug>	which involves finding unknown network endpoints, authenticating them, and providing them 500K-5M chunks of data.
| [Friday 19 November 2010] [18:56:08] <doug>	with distributed locking.
| [Friday 19 November 2010] [18:56:35] <doug>	and may cross political boundaries.
| [Friday 19 November 2010] [18:56:58] <Guthur>	You can poll plain sockets actually
| [Friday 19 November 2010] [18:57:01] <Guthur>	with ZMQ
| [Friday 19 November 2010] [18:57:17] <travlr>	doug, take a look at what i'm working on. this all started with the need for  high frequency trading: http://prodatalab.wikidot.com/
| [Friday 19 November 2010] [18:57:51] <travlr>	that's a tempory page. i'm starting to build a community for it now.
| [Friday 19 November 2010] [18:57:56] <doug>	yeah, i can poll plain sockets without zmq as well.
| [Friday 19 November 2010] [18:58:19] <Guthur>	doug, I think you missed my point
| [Friday 19 November 2010] [18:58:58] <Guthur>	If you had to cross political boundaries, I assume you meant to places where there is no ZMQ, that might facilitate it, which is what I meant
| [Friday 19 November 2010] [18:59:04] <doug>	sounds cool, travlr.  i look forward to hearing about the first release.
| [Friday 19 November 2010] [18:59:47] <doug>	there'd be zmq on both ends, but there's a strong need for authentication and authorization in that case
| [Friday 19 November 2010] [19:00:27] <doug>	the need for identity seeming to nullify the benefit i'd otherwise realize via zmq.
| [Friday 19 November 2010] [19:01:04] <doug>	i think my app is better modeled as a collection of pairs, instead of a pub/sub app.
| [Friday 19 November 2010] [19:01:27] <doug>	with more shared state than pub/sub generally implies.
| [Friday 19 November 2010] [19:02:05] <travlr>	you probably need multiple zmq channels.. each for their own purposes
| [Friday 19 November 2010] [19:02:46] <doug>	yeah, i'm not sure how to abstract the purposes while still getting benefit out of zmq.
| [Friday 19 November 2010] [19:03:34] <travlr>	abstraction of 'purpose' is exactly what is fundamental to prodatalab
| [Friday 19 November 2010] [19:04:36] <travlr>	just consider a buffer that has a description attached to it.. 
| [Friday 19 November 2010] [19:15:41] <travlr>	doug, i just your discussion with Guther, a couple of things to mention..
| [Friday 19 November 2010] [19:16:19] <travlr>	zmq 'message' is just a blob of binary data on top of tcp or other transport layer
| [Friday 19 November 2010] [19:16:41] <travlr>	each message can be any size you want it to be
| [Friday 19 November 2010] [19:16:46] <travlr>	also..
| [Friday 19 November 2010] [19:18:01] <travlr>	zmq (in itself) is currently only designed for intranet purposes, there is no mechanism as of yet for internet boundries
| [Friday 19 November 2010] [19:18:39] <travlr>	here is where you might use zmq_poll() to interface with a normal BSD stlyle socket
| [Friday 19 November 2010] [19:19:16] <travlr>	on the edge... and use some other application layer for point to point on the internet
| [Friday 19 November 2010] [19:19:56] <travlr>	or use zmq over the internet and provide your own security mechanism on top of it
| [Friday 19 November 2010] [19:20:43] <travlr>	this is what the recent discussions have been about.. as well as _maybe_ incorporating some security features into the zmq infrastructure.
| [Friday 19 November 2010] [19:21:33] <travlr>	security == latency.. so careful consideration is being tossed about
| [Friday 19 November 2010] [19:31:51] <travlr>	huh. i thought i got my layers mixed up.. tcp-network and i meant transport not application over internet. sometimes i think/type to fase :P
| [Friday 19 November 2010] [19:32:22] <travlr>	see.. s/fast/fase/ .. lol
| [Friday 19 November 2010] [19:48:00] <nettok>	I can't connect to the zeromq log, the endpoint is "inproc://log" right?
| [Friday 19 November 2010] [19:49:42] <travlr>	is there a 'log' device? that's news to me.
| [Friday 19 November 2010] [19:50:09] <travlr>	where's that hosted?
| [Friday 19 November 2010] [19:51:30] <nettok>	travlr: I read it in the mailing list, it's supposed to be in 2.1 trunk http://blog.gmane.org/gmane.network.zeromq.devel/month=20100901
| [Friday 19 November 2010] [19:52:45] <travlr>	nice.. i'll check it out. thanks
| [Saturday 20 November 2010] [00:43:18] <lantins>	hey guys; is PUSH ment to still block when I've got a HWM set and used ZMQ::NOBLOCK when sending?
| [Saturday 20 November 2010] [01:16:37] <lantins>	i think the answers no, and im doing summets wrong
| [Saturday 20 November 2010] [03:08:25] <lantins>	yup, something in a thread was causing the global vm lock (in ruby)
| [Saturday 20 November 2010] [05:06:23] <mikko>	lestrrat: hi
| [Saturday 20 November 2010] [05:06:51] <mikko>	lestrrat: the perl builds are currently failing
| [Saturday 20 November 2010] [05:07:50] <lestrrat>	goodie 
| [Saturday 20 November 2010] [05:08:03] <lestrrat>	I haven't changed a line of code :/
| [Saturday 20 November 2010] [05:08:05] <lestrrat>	oh well
| [Saturday 20 November 2010] [05:10:00] <mikko>	lestrrat: it's been failing for a long time
| [Saturday 20 November 2010] [05:10:13] <mikko>	i got all the modules installed but it says that i don't have the needed modules
| [Saturday 20 November 2010] [05:10:15] <lestrrat>	after the last fix?
| [Saturday 20 November 2010] [05:10:17] <mikko>	and it says im missing ''
| [Saturday 20 November 2010] [05:10:19] <lestrrat>	oh.
| [Saturday 20 November 2010] [05:10:31] <mikko>	http://build.valokuva.org/job/ZeroMQPerl-master_ZeroMQ2-master_GCC/128/console
| [Saturday 20 November 2010] [05:10:33] <mikko>	see the output
| [Saturday 20 November 2010] [05:10:53] <mikko>	last success was Nov 8
| [Saturday 20 November 2010] [05:11:37] <lestrrat>	The message is bad, but I think you'r missing Module::Install::TestTarget
| [Saturday 20 November 2010] [05:12:02] <lestrrat>	you know what, why don't I write a build script
| [Saturday 20 November 2010] [05:12:14] <lestrrat>	I'll do all the module installation there.
| [Saturday 20 November 2010] [05:12:24] <lestrrat>	so you don't have to worry about it
| [Saturday 20 November 2010] [05:13:51] <mikko>	installed the module and rebuilding
| [Saturday 20 November 2010] [05:14:47] <mikko>	succeeds
| [Saturday 20 November 2010] [05:15:00] <lestrrat>	how often do these tests run? is the trigger a new zmq commit?
| [Saturday 20 November 2010] [05:15:25] <mikko>	5am and 5pm on GMT
| [Saturday 20 November 2010] [05:15:53] <lestrrat>	k. 
| [Saturday 20 November 2010] [05:17:26] <mikko>	should i disable the build against zeromq maint for perl?
| [Saturday 20 November 2010] [05:17:32] <mikko>	it seems that several tests are failing
| [Saturday 20 November 2010] [05:21:44] <lestrrat>	grr
| [Saturday 20 November 2010] [05:21:57] <lestrrat>	sure go ahead
| [Saturday 20 November 2010] [05:22:16] <lestrrat>	I won't be able to get everything done for a few days
| [Saturday 20 November 2010] [05:24:56] <sustrik>	morning
| [Saturday 20 November 2010] [05:25:10] <sustrik>	well, people can use master instead of main if they need perl
| [Saturday 20 November 2010] [06:04:23] <lestrrat>	mikko: no hurries, but could you try running autobuild/run.sh in hudson?  (use the proper ZMQ_H env et al when you run this script: i.e.  ZMQ_H=/path/to/zmq.h ./autobuild/run.sh)
| [Saturday 20 November 2010] [06:04:29] <lestrrat>	this should solve the dependency issues in the future
| [Saturday 20 November 2010] [06:04:51] <mikko>	ok, ill give a go
| [Saturday 20 November 2010] [06:07:47] <mikko>	lestrrat: http://build.valokuva.org/job/ZeroMQPerl-master_ZeroMQ2-master_GCC/130/console
| [Saturday 20 November 2010] [06:07:51] <mikko>	building there
| [Saturday 20 November 2010] [06:10:19] <lestrrat>	seems like it worked :)
| [Saturday 20 November 2010] [06:10:20] <lestrrat>	coolness
| [Saturday 20 November 2010] [06:33:04] <clkao>	lestrrat!
| [Saturday 20 November 2010] [06:36:52] <mikko>	all the builds that are expected succeed are now succeeding
| [Saturday 20 November 2010] [06:36:56] <mikko>	thats a good thing
| [Saturday 20 November 2010] [06:37:05] <mikko>	lestrrat: do you want emails for build failures in perl bindings?
| [Saturday 20 November 2010] [06:39:43] <lestrrat>	hi clkao :)
| [Saturday 20 November 2010] [06:39:52] <lestrrat>	yeah, I think that would be good
| [Saturday 20 November 2010] [06:39:56] <lestrrat>	> re: emails
| [Saturday 20 November 2010] [06:40:42] <mikko>	lestrrat: can you give me an email in which to send them?
| [Saturday 20 November 2010] [06:41:00] <lestrrat>	lestrrat@gmail.com
| [Saturday 20 November 2010] [06:41:17] <mikko>	added
| [Saturday 20 November 2010] [06:42:58] <lestrrat>	thanks!
| [Saturday 20 November 2010] [07:34:39] <Guthur>	when does the logs get updated?
| [Saturday 20 November 2010] [07:42:40] <lantins>	i can't figure out what the hell's going on here...
| [Saturday 20 November 2010] [07:43:56] <lantins>	I'm forking some workers, 4 of them, when there doing something like sleep() they seem to get a message, then start sleeping. now when i swap the sleep() out with a http request, it only seems to send the request once I've PUSH'ed 4 messages
| [Saturday 20 November 2010] [07:44:44] <lantins>	tried swapping out the http stuff a couple of times, so either they all have the same issue. or I'm not doing somthing right with zmq
| [Saturday 20 November 2010] [07:44:57] <lantins>	any ideas?
| [Saturday 20 November 2010] [08:09:09] <travlr>	Guthur: hi. I haven't put the log updater app on a cron yet. I'll have that done in a day or two.
| [Saturday 20 November 2010] [08:11:38] <travlr>	lantins: do you have a chunk of code you can post on gist or pastebin or something?
| [Saturday 20 November 2010] [08:13:16] <travlr>	lantins: are you using zmq_poll() for the http stuff.. are interfacing with a bsd socket for the http stuff or is this all pure zmq?
| [Saturday 20 November 2010] [08:15:30] <lantins>	travlr: i can gist the code, its a total hack at the moment though mind =)
| [Saturday 20 November 2010] [08:16:01] <travlr>	sure..
| [Saturday 20 November 2010] [08:16:38] <lantins>	travlr: not using zmq_poll. got ruby eventmachine dealing with sockets, that PUSH' to a buffer, that does some things, then PUSH' to the 'workers'. there sending http requests out
| [Saturday 20 November 2010] [08:16:44] <lantins>	i'll stick it up in a sec
| [Saturday 20 November 2010] [08:17:59] <travlr>	well if your using ruby i'm not familiar with it
| [Saturday 20 November 2010] [08:20:37] <travlr>	Guthur: I just uploaded the changes. it'll take a few minutes (maybe) for github servers to host them.
| [Saturday 20 November 2010] [08:22:15] <lantins>	tried to remove some of the gruff. i started off trying to do this all in threads, but ended up pulling it out into seperate processes to test
| [Saturday 20 November 2010] [08:22:18] <lantins>	travlr: https://gist.github.com/fff5bf54b84e784610a0
| [Saturday 20 November 2010] [08:23:10] <lantins>	buffer_thread.rb, http_workers.rb and socket_server.rb would be the 3 'components'
| [Saturday 20 November 2010] [08:24:39] <travlr>	sorry i can't get a grip that easily on the ruby stuff. don't have time right now to dig into it deeper.
| [Saturday 20 November 2010] [08:25:02] <lantins>	travlr: no worries
| [Saturday 20 November 2010] [08:25:35] <lantins>	i've a feeling its a threading issue or something other then zmq tbh
| [Saturday 20 November 2010] [08:26:26] <travlr>	yeah i doubt its zmq itself. it has a small learning curve but i don't know how it works at all with eventmachine.
| [Saturday 20 November 2010] [08:27:14] <travlr>	i
| [Saturday 20 November 2010] [08:27:37] <lantins>	how it is in the gist, the side im having issues with isn't running inside EM at all
| [Saturday 20 November 2010] [08:28:04] <lantins>	im gonna fire up the workers as individual processes rather then threads, if the problem goes away... its threading problems
| [Saturday 20 November 2010] [08:28:27] <travlr>	yeah processes will probably easier from the start
| [Saturday 20 November 2010] [08:28:58] <travlr>	are there ruby examples on the zmq website... use those to start with.
| [Saturday 20 November 2010] [08:37:09] <lantins>	yup works perfect when im not threading
| [Saturday 20 November 2010] [08:37:20] <travlr>	cool
| [Saturday 20 November 2010] [08:37:51] <travlr>	were you using the inproc protocol for the thread communication?
| [Saturday 20 November 2010] [08:37:59] <lantins>	i was to begin with
| [Saturday 20 November 2010] [08:38:03] <lantins>	then moved to ipc
| [Saturday 20 November 2010] [08:38:27] <travlr>	ipc for process, inproc for threads right?
| [Saturday 20 November 2010] [08:38:52] <lantins>	yeah
| [Saturday 20 November 2010] [08:39:20] <lantins>	worked fine if i was just calling sleep() in the thread, must be something to do with Net::HTTP and threading
| [Saturday 20 November 2010] [08:40:13] <lantins>	to be fair, at the moment I'm forking for every 'message'. so just forking once for however many workers I need would work much better i'm hoping
| [Saturday 20 November 2010] [08:40:21] <lantins>	or just fire them up seperately
| [Saturday 20 November 2010] [08:40:44] <travlr>	yeah play around with your use case
| [Saturday 20 November 2010] [08:41:09] <lantins>	this is very much throw away code =)
| [Saturday 20 November 2010] [08:41:14] <travlr>	ya
| [Saturday 20 November 2010] [08:41:33] <lantins>	was lotta fun until i hit this threading issue, then atleast 4 hours of my time just seemed to go AWOL!
| [Saturday 20 November 2010] [08:41:42] <travlr>	have you worked with examples yet
| [Saturday 20 November 2010] [08:41:51] <travlr>	on the website
| [Saturday 20 November 2010] [08:42:09] <lantins>	spent the best part of a day going through the epic guide
| [Saturday 20 November 2010] [08:42:28] <lantins>	still keep going back to it... like i said... EPIC!
| [Saturday 20 November 2010] [08:43:10] <travlr>	yeah i'm still working on intricacies.. but pieter did a really nice job
| [Saturday 20 November 2010] [08:43:12] <lantins>	props to the people who wrote that, its been a good insight into this 'messaging' lark =)
| [Saturday 20 November 2010] [08:43:22] <travlr>	pieter h
| [Saturday 20 November 2010] [08:44:03] <travlr>	hes good at that stuff. i'm a good doc advocate, big time
| [Saturday 20 November 2010] [08:44:05] <lantins>	think thats the guy who has epic long blog posts too heh
| [Saturday 20 November 2010] [08:44:29] <travlr>	he is the man.. lol
| [Saturday 20 November 2010] [08:44:51] <lantins>	yeah, i like how its got humour throughout, given there is so much content
| [Saturday 20 November 2010] [08:45:30] <travlr>	i'm more of a just the facts kinda guy myself... give me a good succinct outline any time.
| [Saturday 20 November 2010] [08:46:12] <travlr>	with plenty of hyper cross-links
| [Saturday 20 November 2010] [08:46:29] <lantins>	not having played with messaging stuff before, its good for getting going
| [Saturday 20 November 2010] [08:46:41] <travlr>	ya
| [Saturday 20 November 2010] [08:46:59] <lantins>	ruby ffi code comments have been very useful to get the context moved over from C to Ruby
| [Saturday 20 November 2010] [08:47:34] <travlr>	zmq is a blessing imo, especially for what i'm using it for.
| [Saturday 20 November 2010] [08:48:34] <travlr>	yeah, i haven't played with ruby at all yet
| [Saturday 20 November 2010] [08:48:59] <lantins>	i think its gonna be very useful for us, initial benchmarks with this toy code look much nicer then anything were currently getting
| [Saturday 20 November 2010] [08:49:10] <travlr>	yup
| [Saturday 20 November 2010] [08:49:17] <lantins>	what language you using zmq with mostely?
| [Saturday 20 November 2010] [08:49:25] <travlr>	c c++ and python
| [Saturday 20 November 2010] [08:49:33] <lantins>	=)
| [Saturday 20 November 2010] [08:49:45] <travlr>	c++ through qt mostly... i like qt alot
| [Saturday 20 November 2010] [08:50:22] <travlr>	especially now that someone recently mashed up zmq with qt 
| [Saturday 20 November 2010] [08:50:28] <travlr>	zeromqt
| [Saturday 20 November 2010] [08:50:31] <lantins>	im pondering down the line, if it all looks a good fit... about implementing some of this in C, the rest can stay ruby though
| [Saturday 20 November 2010] [08:50:40] <travlr>	sure
| [Saturday 20 November 2010] [08:50:41] <lantins>	yeah i seen that on the labs page
| [Saturday 20 November 2010] [08:51:01] <travlr>	i'm playing with it right now... nice
| [Saturday 20 November 2010] [08:51:13] <lantins>	:)
| [Saturday 20 November 2010] [08:52:19] <lantins>	obj-c I'd like to get around to playing with at some point
| [Saturday 20 November 2010] [08:52:48] <travlr>	sure, i'm not a apple guy so i don't see where else it's used much
| [Saturday 20 November 2010] [08:54:02] <travlr>	what are you going to be using zmq for
| [Saturday 20 November 2010] [08:54:08] <lantins>	although, right now I'm pondering how to better 'route' these PUSH/PULL messages, rather then fair-routing? but i guess this is where you start building 'device' like stuff to wire that kinda thing up?
| [Saturday 20 November 2010] [08:54:44] <lantins>	at the moment, I've got a couple bits of software that are part of a 'system'. they talk to one another via json/http
| [Saturday 20 November 2010] [08:54:58] <lantins>	we also push out lots of data to customers via json/http
| [Saturday 20 November 2010] [08:55:14] <lantins>	so, im looking to remove some of the http stuff in our backend
| [Saturday 20 November 2010] [08:55:24] <travlr>	high speed data or just a "normal" system?
| [Saturday 20 November 2010] [08:55:57] <lantins>	the current system does work, but it could be made simpler
| [Saturday 20 November 2010] [08:56:09] <lantins>	we got seconds to play with =)
| [Saturday 20 November 2010] [08:56:26] <travlr>	cool
| [Saturday 20 November 2010] [08:56:41] <travlr>	so your crossing internet boundries?
| [Saturday 20 November 2010] [08:57:10] <lantins>	a little bit of the system is, and the part where we talk to customer servers
| [Saturday 20 November 2010] [08:57:17] <lantins>	but the rest is internal on the lan
| [Saturday 20 November 2010] [08:57:51] <lantins>	were dealing with vehicle tracking/diagnostics data
| [Saturday 20 November 2010] [08:58:08] <travlr>	oh cool. that sounds very interesting
| [Saturday 20 November 2010] [08:58:11] <lantins>	most vehicles update between 60sec and 5mins
| [Saturday 20 November 2010] [08:58:20] <travlr>	very cool.
| [Saturday 20 November 2010] [08:58:31] <lantins>	so if it takes 30sec to move through the system it doesn't really matter
| [Saturday 20 November 2010] [08:58:54] <travlr>	what kind of 'tracking/diagnostics'
| [Saturday 20 November 2010] [08:59:06] <lantins>	oh all kinds =)
| [Saturday 20 November 2010] [08:59:19] <lantins>	we design/build the hardware our self
| [Saturday 20 November 2010] [08:59:24] <travlr>	are you doing embeddable stuff too
| [Saturday 20 November 2010] [08:59:32] <travlr>	well that kills that quest
| [Saturday 20 November 2010] [08:59:33] <travlr>	ion
| [Saturday 20 November 2010] [08:59:44] <travlr>	i'm learning that stuff too
| [Saturday 20 November 2010] [08:59:47] <lantins>	we have gear with 4 CANBus channels on them, so anything you can get on the vehicle ECU's we can get in real time
| [Saturday 20 November 2010] [09:00:01] <travlr>	yes yes.... 
| [Saturday 20 November 2010] [09:00:03] <lantins>	heh
| [Saturday 20 November 2010] [09:00:34] <travlr>	electronics is cool shit, imo
| [Saturday 20 November 2010] [09:00:47] <travlr>	i wish i more time to play with it
| [Saturday 20 November 2010] [09:00:48] <lantins>	I'm _not_ smart enough to be one of the guys building the hardware, but it has given me the chance to learn about it all.. and ask questions from people much smarter then me
| [Saturday 20 November 2010] [09:01:01] <travlr>	very cool
| [Saturday 20 November 2010] [09:01:06] <lantins>	i just shovel data and make web apps with it lol
| [Saturday 20 November 2010] [09:01:27] <travlr>	sensor systems are also really cool
| [Saturday 20 November 2010] [09:01:46] <lantins>	AVR chips are very good to play around with
| [Saturday 20 November 2010] [09:01:56] <travlr>	avr.... awesome!
| [Saturday 20 November 2010] [09:02:09] <travlr>	linux32 embedded
| [Saturday 20 November 2010] [09:02:49] <travlr>	i want to play with all that stuff real bad.. no time right now
| [Saturday 20 November 2010] [09:02:50] <lantins>	was gifted a development AVR board that runs linux form work, with two ethernet's!
| [Saturday 20 November 2010] [09:02:56] <lantins>	not got around to toying with that yet :/
| [Saturday 20 November 2010] [09:03:40] <travlr>	to start with, i want to build my programmer.. but that's a chicken and egg dilema.. huh.. lol
| [Saturday 20 November 2010] [09:03:42] <lantins>	I'll be able to buzz people into the flat without leaving my computer once I get around to soldering my first 'official' electronics project! via bluetooth!
| [Saturday 20 November 2010] [09:04:21] <travlr>	what electronics supplier would you use?
| [Saturday 20 November 2010] [09:04:31] <lantins>	not quite got the BT cracked yet, and I need to get work to mount it for me... when i seen the 9 price, i didn't pay any attention to the fact it was bloody surface mount!
| [Saturday 20 November 2010] [09:04:55] <lantins>	not sure where you are? I'm in the UK
| [Saturday 20 November 2010] [09:05:09] <travlr>	surface mount is very tricky for a beginner i would imaging
| [Saturday 20 November 2010] [09:05:15] <travlr>	in usa
| [Saturday 20 November 2010] [09:05:23] <lantins>	farnell.com is where I've got all my stuff from
| [Saturday 20 November 2010] [09:05:30] <travlr>	that's uk?
| [Saturday 20 November 2010] [09:05:35] <lantins>	US too
| [Saturday 20 November 2010] [09:05:50] <lantins>	they have _Everything_ on that site
| [Saturday 20 November 2010] [09:05:50] <travlr>	i'll check it out.. 
| [Saturday 20 November 2010] [09:05:56] <lantins>	if you got a part number, you can find it
| [Saturday 20 November 2010] [09:06:17] <travlr>	is it more for hobbiests... are they fast on delivery?
| [Saturday 20 November 2010] [09:06:27] <lantins>	now, the problem is when you don't have a part number and have to go through everything to figure out if the component does what you want it to!
| [Saturday 20 November 2010] [09:07:18] <lantins>	they are a big company, not really aimed at hobbiests, you do kinda have to know what to start looking for
| [Saturday 20 November 2010] [09:07:29] <travlr>	fast delivery?
| [Saturday 20 November 2010] [09:07:32] <lantins>	not that I really do, but its the only place I've found where I got options
| [Saturday 20 November 2010] [09:07:35] <lantins>	yeah super fast for me
| [Saturday 20 November 2010] [09:07:42] <lantins>	can't comment about the states though
| [Saturday 20 November 2010] [09:07:54] <travlr>	thats good...  small orders ok?
| [Saturday 20 November 2010] [09:07:59] <travlr>	projects/
| [Saturday 20 November 2010] [09:08:07] <lantins>	yeah have been for me
| [Saturday 20 November 2010] [09:08:10] <travlr>	good
| [Saturday 20 November 2010] [09:08:17] <lantins>	what i did was this:
| [Saturday 20 November 2010] [09:08:30] <lantins>	http://cdn.shopify.com/s/files/1/0038/9582/files/RBBB_Instructions_06.pdf?1260749296
| [Saturday 20 November 2010] [09:08:53] <lantins>	that's a real nice document about making an Arduino clone
| [Saturday 20 November 2010] [09:09:41] <lantins>	I looked at the components needed to build a handful, then prospected into some other 'usual' sized components
| [Saturday 20 November 2010] [09:10:04] <travlr>	there's a lot of great info out on the web
| [Saturday 20 November 2010] [09:10:14] <travlr>	that proj looks great
| [Saturday 20 November 2010] [09:10:21] <travlr>	i wish i had the time
| [Saturday 20 November 2010] [09:10:44] <travlr>	i love teaching myself shit
| [Saturday 20 November 2010] [09:10:44] <lantins>	they use a Resonator in that design, I opted for a crystal
| [Saturday 20 November 2010] [09:10:56] <lantins>	yeah
| [Saturday 20 November 2010] [09:10:59] <lantins>	i know the feeling
| [Saturday 20 November 2010] [09:11:12] <travlr>	yeah crystal.. mmmm gooooood.
| [Saturday 20 November 2010] [09:11:15] <travlr>	lol
| [Saturday 20 November 2010] [09:11:26] <lantins>	i have to say, i sunk a good week or so getting going with all this stuff, and I know I still know naff all about it
| [Saturday 20 November 2010] [09:11:42] <travlr>	i've studied a shit load
| [Saturday 20 November 2010] [09:12:03] <travlr>	i have four tv's opened up in my 'project' room
| [Saturday 20 November 2010] [09:12:03] <lantins>	yeah crystal's smalled cooler then Resonators ;-) (crystal were the better option from what I descovered anyhow)
| [Saturday 20 November 2010] [09:12:06] <travlr>	need caps
| [Saturday 20 November 2010] [09:12:19] <lantins>	lol
| [Saturday 20 November 2010] [09:12:21] <travlr>	radio shack sucks for parts
| [Saturday 20 November 2010] [09:12:30] <travlr>	i haven't ordered them yet
| [Saturday 20 November 2010] [09:12:30] <lantins>	my problem is when I keep blowing shit up
| [Saturday 20 November 2010] [09:12:39] <travlr>	_lol_
| [Saturday 20 November 2010] [09:12:52] <lantins>	"ah fuck that cost 4 and I've run out of them!!!!"
| [Saturday 20 November 2010] [09:13:05] <travlr>	lol
| [Saturday 20 November 2010] [09:13:19] <travlr>	damn, i want to play
| [Saturday 20 November 2010] [09:13:20] <lantins>	i think the smell of burning electronics is part of the learning process
| [Saturday 20 November 2010] [09:13:27] <travlr>	yup!
| [Saturday 20 November 2010] [09:13:36] <lantins>	hell man i managed to keep that stuff at bay for ages and now you've got me all thinking about it!
| [Saturday 20 November 2010] [09:13:52] <travlr>	i repeat.. i want to play
| [Saturday 20 November 2010] [09:13:57] <travlr>	no time
| [Saturday 20 November 2010] [09:13:58] <lantins>	I got real work to be doing lol
| [Saturday 20 November 2010] [09:14:09] <travlr>	speaking of which
| [Saturday 20 November 2010] [09:14:13] <travlr>	gotta go
| [Saturday 20 November 2010] [09:14:19] <lantins>	any free time has been spent with iOS/iPad development
| [Saturday 20 November 2010] [09:14:26] <lantins>	take it easy travlr
| [Saturday 20 November 2010] [09:14:31] <lantins>	catch you later =)
| [Saturday 20 November 2010] [09:14:35] <travlr>	see ya
| [Saturday 20 November 2010] [10:06:21] <Guthur>	travlr, Cheers for the heads up on the logs
| [Saturday 20 November 2010] [10:09:26] <travlr>	sure
| [Saturday 20 November 2010] [11:06:13] <bfrog>	is there a sane way to get queues to work with an existing "reactor" like libevent or whatever?
| [Saturday 20 November 2010] [11:07:03] <bfrog>	I mean, whats the point of sockets if you can't do event driven programming :-P
| [Saturday 20 November 2010] [11:08:43] <travlr>	bfrog, existing reactor... sure... libevent, i think i remember that that's been done. did you check the mail list and irc archives?
| [Saturday 20 November 2010] [11:09:50] <bfrog>	no, I looked on the website
| [Saturday 20 November 2010] [11:09:53] <travlr>	there's a nice mashup with qt signal and slots if you do qt
| [Saturday 20 November 2010] [11:10:57] <travlr>	the mail list is easily found on the website, here's the irc log: http://travlr.github.com/zmqirclog/
| [Saturday 20 November 2010] [11:14:43] <mikko>	bfrog: https://github.com/zeromq/zeromq2/blob/master/doc/zmq_getsockopt.txt#L255
| [Saturday 20 November 2010] [11:28:57] <bfrog>	I see it, thanks
| [Saturday 20 November 2010] [11:29:24] <mikko>	bfrog: and zmq provides it own polling mechnism as well
| [Saturday 20 November 2010] [11:29:32] <mikko>	so you are not really enforced to use external event loop
| [Saturday 20 November 2010] [11:30:56] <bfrog>	I get that
| [Saturday 20 November 2010] [11:31:01] <bfrog>	but thats again, really limiting
| [Saturday 20 November 2010] [11:31:12] <bfrog>	well not again, but yeah, thats faily limiting if I can't use my own
| [Saturday 20 November 2010] [11:42:33] <bfrog>	it doesn't look like I can just provide callbacks for when messages are available, call this function sort of thing?
| [Saturday 20 November 2010] [12:25:03] <Guthur>	bfrog you could easily build it ontop of polling
| [Saturday 20 November 2010] [12:25:58] <Guthur>	clrzmq2 uses event delegates for polling 
| [Saturday 20 November 2010] [12:27:58] <bfrog>	I don't want to poll, I like my callbacks and selects() :-(
| [Saturday 20 November 2010] [12:31:32] <mikko>	bfrog: the zmq_poll is an abstraction over different polling methods such as epoll and select
| [Saturday 20 November 2010] [12:31:46] <mikko>	adding callbacks to that is a couple of lines of code
| [Saturday 20 November 2010] [12:32:04] <mikko>	but if you want to use an external event loop just use ZMQ_FD sockopt
| [Saturday 20 November 2010] [12:32:26] <bfrog>	but I might not have the whole message in the queue then?
| [Saturday 20 November 2010] [12:32:56] <mikko>	not necessarily
| [Saturday 20 November 2010] [12:33:04] <bfrog>	right, so the recv may still block
| [Saturday 20 November 2010] [12:33:11] <mikko>	you can use ZMQ_EVENTS to check that
| [Saturday 20 November 2010] [12:33:35] <mikko>	https://github.com/zeromq/zeromq2/blob/master/doc/zmq_getsockopt.txt#L272
| [Saturday 20 November 2010] [12:42:20] <bfrog>	what if I get a partial message, then I'm constantly looping on ZMQ_EVENTS, how would I break that?
| [Saturday 20 November 2010] [12:42:52] <bfrog>	I can't touch the fd itself, can I tell zeromq to just give up somehow?
| [Saturday 20 November 2010] [12:46:14] <Guthur>	you can just stop calling poll, and that's it surely
| [Saturday 20 November 2010] [12:46:45] <Guthur>	The example code just immediately timeouts, you might want something slightly different
| [Saturday 20 November 2010] [13:14:09] <cremes>	bfrog: you are *guaranteed* to have a whole message; there is no such thing in 0mq as a partial message
| [Saturday 20 November 2010] [13:14:22] <cremes>	therefore, no worries about it blocking
| [Saturday 20 November 2010] [13:14:40] <cremes>	if you are still concerned, pass the NO_BLOCK flag to your send or receive and go on your merry way
| [Saturday 20 November 2010] [13:17:01] <cremes>	lantins: you may also be interested in looking at zmqmachine which is essentially eventmachine for 0mq sockets; find it on github
| [Saturday 20 November 2010] [13:22:20] <mikko>	cremes: if you poll on ZMQ_FD you could have false positives
| [Saturday 20 November 2010] [13:22:37] <mikko>	you need to check for ZMQ_EVENTS for the socket as well if you want to make sure that you dont block
| [Saturday 20 November 2010] [13:23:14] <cremes>	mikko: right; so what's the problem? it's a pretty clear 2-step process
| [Saturday 20 November 2010] [13:23:31] <cremes>	alternately, try to send/recv with NO_BLOCK and check for EAGAIN
| [Saturday 20 November 2010] [13:23:50] <cremes>	either way, there is no concern about blocking
| [Saturday 20 November 2010] [13:25:27] <mikko>	no problem there
| [Saturday 20 November 2010] [13:25:47] <mikko>	just wanted to indicate that a 'positive' on polling on ZMQ_FD doesn't mean that you can recv()
| [Saturday 20 November 2010] [13:25:59] <cremes>	ah, i see
| [Saturday 20 November 2010] [13:26:11] <cremes>	i agree with that
| [Saturday 20 November 2010] [13:26:29] <cremes>	hopefully bfrog reads through this at some point and this answers his/her question
| [Saturday 20 November 2010] [13:26:36] <bfrog>	yeah it does
| [Saturday 20 November 2010] [13:26:41] <cremes>	great
| [Saturday 20 November 2010] [13:27:15] <cremes>	bfrog: fyi, the FD & EVENTS opts were added *specifically* to allow for 0mq socket integration with other event loops
| [Saturday 20 November 2010] [13:27:29] <cremes>	if you find a case where they are inadequate, please speak up
| [Saturday 20 November 2010] [14:26:36] <rgl>	hi
| [Sunday 21 November 2010] [05:14:35] <mikko>	sustrik: http://build.valokuva.org/job/ZeroMQ2-core-master_SunStudio/70/console
| [Sunday 21 November 2010] [05:14:45] <mikko>	this time with sun studio
| [Sunday 21 November 2010] [05:14:56] <sustrik>	mikko: let me see
| [Sunday 21 November 2010] [05:15:55] <sustrik>	still the same bug
| [Sunday 21 November 2010] [05:16:43] <sustrik>	dhammika seems to understand what's going on
| [Sunday 21 November 2010] [05:16:51] 	 * sustrik is struggling to make sense of it
| [Sunday 21 November 2010] [05:39:10] <mikko>	sustrik: it's a lot harder to reproduce with debug build
| [Sunday 21 November 2010] [05:51:10] <sustrik>	ack
| [Sunday 21 November 2010] [05:58:33] <mikko>	https://gist.github.com/6d2c9eb0b3efc2afd9a8
| [Sunday 21 November 2010] [05:58:38] <mikko>	backtrace with symbols
| [Sunday 21 November 2010] [05:59:20] <mikko>	the crash is in #0  zmq::object_t::get_tid (this=0xb1c088c8) at object.cpp:47
| [Sunday 21 November 2010] [06:09:32] <sustrik>	mikko: that's maint?
| [Sunday 21 November 2010] [06:10:02] <sustrik>	nope, it's master
| [Sunday 21 November 2010] [06:11:24] <mikko>	master
| [Sunday 21 November 2010] [06:11:52] <mikko>	ran while [ 1 = 1 ]; do ./test_shutdown_stress ; echo "x"; done until it crashed
| [Sunday 21 November 2010] [06:13:18] <sustrik>	hm, looks like some kind of stack overwrite
| [Sunday 21 November 2010] [06:13:35] <sustrik>	the error actually emerges in the test program, not 0mq core...
| [Sunday 21 November 2010] [06:14:12] <sustrik>	strange
| [Sunday 21 November 2010] [06:17:29] <sustrik>	hm, cannot reproduce on my box
| [Sunday 21 November 2010] [06:20:04] <mikko>	takes anything between 10 to 100 runs here
| [Sunday 21 November 2010] [06:20:08] <mikko>	until it crahes
| [Sunday 21 November 2010] [06:29:17] <sustrik>	on my box it runs ~30 times
| [Sunday 21 November 2010] [06:29:27] <sustrik>	then the test slows down considerably
| [Sunday 21 November 2010] [06:29:45] <sustrik>	(too much open sockets?)
| [Sunday 21 November 2010] [06:29:52] <sustrik>	anyway, it doesn't fail
| [Sunday 21 November 2010] [06:35:41] <sustrik>	mikko: can you possibly check the patch proposed in my last email?
| [Sunday 21 November 2010] [06:36:32] <sustrik>	it's probably a different problem, but there's a chance that it's actually a different manifestation of the same bug...
| [Sunday 21 November 2010] [06:37:34] <sustrik>	just add the two lines into zmq_engine.cpp
| [Sunday 21 November 2010] [06:42:24] <mikko>	line 155?
| [Sunday 21 November 2010] [06:48:10] <sustrik>	mikko: yes
| [Sunday 21 November 2010] [06:49:25] <mikko>	*** glibc detected *** /tmp/zeromq2/tests/.libs/lt-test_shutdown_stress: corrupted double-linked list: 0xb0b058c8 ***
| [Sunday 21 November 2010] [06:49:30] <mikko>	after ~50 runs
| [Sunday 21 November 2010] [06:50:34] <mikko>	https://gist.github.com/0707e21ec88f54822fd3
| [Sunday 21 November 2010] [06:50:35] <mikko>	bt
| [Sunday 21 November 2010] [06:50:45] <mikko>	let me do thread apply all bt
| [Sunday 21 November 2010] [06:51:16] <mikko>	https://gist.github.com/a87f11557fee4c7617aa
| [Sunday 21 November 2010] [06:52:50] <sustrik>	hm, probably the same problem
| [Sunday 21 November 2010] [07:21:22] <rgl>	are there any plans to properly support a 64 bit build on windows?
| [Sunday 21 November 2010] [07:26:00] <Guthur>	rgl: what happens with a 64bit build?
| [Sunday 21 November 2010] [07:26:13] <Guthur>	I tried it briefly and it seemed ok?
| [Sunday 21 November 2010] [07:26:55] <rgl>	Guthur, windows uses a different model for 64-bit than common linuxes; eg. on windows a long is not 64 bit.
| [Sunday 21 November 2010] [07:27:53] <rgl>	Guthur, which means that some code on ZMQ does not correctly build (well, it build, but with warnings that do not seem ok to ignore)
| [Sunday 21 November 2010] [07:28:28] <Guthur>	ok, seems fair enough, I didn't really test or watch thoroughly the build
| [Sunday 21 November 2010] [07:29:04] <mikko>	rgl: are you building with mingw or msvc?
| [Sunday 21 November 2010] [07:29:07] <rgl>	the C data model on windows is LLP64 but on linux its LP64
| [Sunday 21 November 2010] [07:29:33] <rgl>	mikko, it does not matter. mingw uses the normal windows data model.
| [Sunday 21 November 2010] [07:29:44] <mikko>	rgl: it seems to be a bit different
| [Sunday 21 November 2010] [07:29:45] <rgl>	mikko, but, I'm using msvc *G*
| [Sunday 21 November 2010] [07:29:54] <mikko>	__int64_t is defined as long long on mingw32
| [Sunday 21 November 2010] [07:30:34] <rgl>	lemme put the msvc compiler logs somewhere.
| [Sunday 21 November 2010] [07:30:38] <mikko>	rgl: i thought zeromq uses fixed size ints everywhere
| [Sunday 21 November 2010] [07:31:17] <Guthur>	I know in some of my builds i see warnings about casting size_t to unsigned int
| [Sunday 21 November 2010] [07:31:45] <Guthur>	not directly related, more in reply to the fixed size ints
| [Sunday 21 November 2010] [07:32:19] <mikko>	Guthur: is that zeromq core or binding code?
| [Sunday 21 November 2010] [07:32:27] <mikko>	i think i need to do MSVC build at some point
| [Sunday 21 November 2010] [07:32:28] <Guthur>	mikko, core
| [Sunday 21 November 2010] [07:34:07] <rgl>	http://pastie.org/pastes/1315022/text
| [Sunday 21 November 2010] [07:35:12] <mikko>	rgl: can you try the same build with master?
| [Sunday 21 November 2010] [07:35:33] <rgl>	I can. I just have to get the repo.
| [Sunday 21 November 2010] [07:40:44] <rgl>	its more-or-less the same http://pastie.org/pastes/1315029/text
| [Sunday 21 November 2010] [07:51:06] <Guthur>	lot's of size_t conversions
| [Sunday 21 November 2010] [07:51:35] <Guthur>	size_t is very troublesome, especially for bindings
| [Sunday 21 November 2010] [08:00:49] <rgl>	can we safely ignore them?
| [Sunday 21 November 2010] [08:21:47] <mikko>	size_t to int isn't really a safe conversion
| [Sunday 21 November 2010] [08:22:36] <mikko>	it would require bounds checking
| [Sunday 21 November 2010] [08:23:23] <mikko>	not sure why the array index isn't size_t there
| [Sunday 21 November 2010] [08:24:14] <mikko>	most of those looks pretty safe casts
| [Sunday 21 November 2010] [08:37:17] <rgl>	humm tried to run remote_thr.exe tcp://127.0.0.1:56789 3000 1234567 and it completly spiked the memory usage to 4G *G*
| [Sunday 21 November 2010] [08:37:48] <rgl>	is this supposed to happen when no watermark is set on the socket?
| [Sunday 21 November 2010] [10:46:26] <Guthur>	Is size_t really a requirement?
| [Sunday 21 November 2010] [10:46:55] <Guthur>	It's very bothersome for bindings like said, because it is hard to be sure what size it really is
| [Sunday 21 November 2010] [10:47:20] <Guthur>	primitive or explicit types are easier
| [Sunday 21 November 2010] [10:57:41] <sustrik>	Guthur: checked POSIX SO_SNDBUF which is kind of similar
| [Sunday 21 November 2010] [10:57:57] <sustrik>	and it is indeed "int" rather than "size_t"
| [Sunday 21 November 2010] [10:58:11] <sustrik>	on the other hand, int is not a fixed-size interger either
| [Sunday 21 November 2010] [11:42:43] <sustrik>	rgl: yes, it's supposed to happen
| [Sunday 21 November 2010] [12:45:16] <Guthur>	sustrik, I have a bad feeling my attempts at cross platform (x86/-64) support with clrzmq2 are possibly not going to stand up, needs more testing really 
| [Sunday 21 November 2010] [13:04:15] <sustrik>	Guthur: sure, that's how it goes with cross-platform support
| [Sunday 21 November 2010] [13:04:34] <sustrik>	in most cases you cannot do all the work yourself
| [Sunday 21 November 2010] [13:04:58] <sustrik>	you have to rely on people who actually own and understand the OSes in question
| [Sunday 21 November 2010] [13:05:50] <Guthur>	I'll certainly be keeping an eye out for feedback
| [Sunday 21 November 2010] [13:27:02] <rgl>	Guthur, I have one request. Maybe it does not make much sense, but It would be great to choose (at runtime) the version of libzmq do use, say, if the os is 32-bit. use the 32-version, otherwise use the 64 bit version.
| [Sunday 21 November 2010] [13:28:20] <Guthur>	well as far as clrzmq2 goes, I have used preprocessor directives
| [Sunday 21 November 2010] [13:29:01] <Guthur>	It would not be impossible to do it at runtime, not sure of benefits though
| [Sunday 21 November 2010] [13:31:18] <rgl>	just more convinient. you just need to drop both versions of the native library and the whole application will work on either 32 or 64 bit.
| [Sunday 21 November 2010] [13:38:13] <Guthur>	Might as well drop both clrzmq.dll as well then though
| [Sunday 21 November 2010] [13:38:45] <Guthur>	and then have the application decide
| [Sunday 21 November 2010] [13:39:29] <Guthur>	that's not generally the approach of Linux, you tend to have either discrete packages or build from source
| [Sunday 21 November 2010] [13:40:41] <Guthur>	rgl: Reasonable enough thought, just in imho it's something that should be delegated to the application provider
| [Sunday 21 November 2010] [13:41:50] <rgl>	ah yes. indeed. it could be delegated to the app. point taken :D
| [Sunday 21 November 2010] [15:33:20] <mikko>	mato: is there a reason why on HP UX the CPPFLAGS are overriden completely?
| [Sunday 21 November 2010] [15:33:22] <mikko>	CPPFLAGS="-D_POSIX_C_SOURCE=200112L"
| [Sunday 21 November 2010] [16:57:25] Notice	-ChanServ- [#qt] Here are the rules for #qt: (1) Don't just join, ask, and quit - stay around and answer questions yourself! (2) Be patient, people may not see your question right away.
| [Sunday 21 November 2010] [21:58:44] <Steve-o>	that was Linux to FreeBSD though, I'm just testing Linux to Linux to see if the graph changes
| [Sunday 21 November 2010] [22:02:28] <Steve-o>	the goal is to find out if anything special is causing Windows performance to be ass
| [Sunday 21 November 2010] [22:06:57] <doug>	what are you measuring?
| [Sunday 21 November 2010] [22:07:20] <doug>	and what makes you think it might be in your critical path?
| [Sunday 21 November 2010] [22:08:18] <Steve-o>	I send a packet from one host to another, which then sends it back, I'm measuring the latency from the first second to the last receive
| [Sunday 21 November 2010] [22:08:51] <Steve-o>	I'm trying to rule out all controllable issues that can affect the critical path
| [Sunday 21 November 2010] [22:10:20] <Steve-o>	performance testing is always overly subject to errors in the testing method and framework
| [Sunday 21 November 2010] [22:11:35] <Steve-o>	you always get developers complaining they cannot achieve reported performance figures, etc
| [Monday 22 November 2010] [03:13:23] <sustrik>	mikko: yes
| [Monday 22 November 2010] [03:13:36] <sustrik>	HP-UX is broken in this respect
| [Monday 22 November 2010] [03:14:52] <sustrik>	IIRC
| [Monday 22 November 2010] [03:14:56] <sustrik>	mato may know more
| [Monday 22 November 2010] [04:10:17] <demmonoid_>	Hi. I'm trying to use Erlang 0mq plugin on Mac OS X, but the build fails. It seems that the C driver needs to be built as a bundle rather than a dynamic library.
| [Monday 22 November 2010] [04:10:37] <demmonoid_>	The problem is that all 0mq libraries are built as dynamic libraries as well
| [Monday 22 November 2010] [04:10:49] <demmonoid_>	Is there a way to work this out?
| [Monday 22 November 2010] [04:16:06] <sustrik>	demmonoid_: there are some OSX related issues in the bug tracker
| [Monday 22 November 2010] [04:16:11] <sustrik>	have a look there
| [Monday 22 November 2010] [04:20:35] <demmonoid_>	sustrik, yes, I saw them but they are like 3 months old and with no response...
| [Monday 22 November 2010] [04:21:11] <demmonoid_>	To be more exact, one of them is still with no response, just that I described here...
| [Monday 22 November 2010] [04:22:04] <sustrik>	well, you can try to fix the problem yourself then
| [Monday 22 November 2010] [04:26:34] <demmonoid_>	That's what I've tried to do but it looks like 0mq doesn't work when it's libraries are just build with -bundle instead of -dynamiclib :)
| [Monday 22 November 2010] [04:26:53] <demmonoid_>	*its libraries
| [Monday 22 November 2010] [04:32:48] <mikko>	sustrik: but that deletes the -g -O2 flags as well
| [Monday 22 November 2010] [04:33:50] <sustrik>	mikko: probably a bug
| [Monday 22 November 2010] [04:34:08] <sustrik>	i have no idea about how the build system works though
| [Monday 22 November 2010] [04:35:36] <sustrik>	demmonoid_: what exactly is the problem, does if fail? what's the error?
| [Monday 22 November 2010] [04:35:52] <mikko>	sustrik: i got a couple patches coming soonish
| [Monday 22 November 2010] [04:36:00] <sustrik>	mikko: ok
| [Monday 22 November 2010] [04:36:03] <mikko>	sustrik: is there a reason why i cant send pull requests in github?
| [Monday 22 November 2010] [04:36:10] <mikko>	would make the development flow a bit more fluent
| [Monday 22 November 2010] [04:36:20] <sustrik>	matter of process
| [Monday 22 November 2010] [04:36:32] <sustrik>	we should do it in a well defined way
| [Monday 22 November 2010] [04:36:47] <sustrik>	pull requests are problematic for people on exotic platforms
| [Monday 22 November 2010] [04:37:05] <mikko>	why is that?
| [Monday 22 November 2010] [04:37:08] <sustrik>	NO GIT
| [Monday 22 November 2010] [04:37:11] <mikko>	if they come through github
| [Monday 22 November 2010] [04:37:12] <sustrik>	no git
| [Monday 22 November 2010] [04:37:23] <sustrik>	you need git client though
| [Monday 22 November 2010] [04:37:34] <mikko>	you need a git client to format-patch as well
| [Monday 22 November 2010] [04:37:48] <sustrik>	all you need is diff
| [Monday 22 November 2010] [04:38:01] <sustrik>	patches don't have to be strictly formatted
| [Monday 22 November 2010] [04:38:13] <sustrik>	just and diff and a sign-off
| [Monday 22 November 2010] [04:43:59] <demmonoid_>	sustrik, it gives the error "i686-apple-darwin10-g++-4.2.1: -compatibility_version only allowed with -dynamiclib" upon build
| [Monday 22 November 2010] [04:46:40] <demmonoid_>	I removed this flag from libtool, as well as install_name which is also incompatible with -bundle
| [Monday 22 November 2010] [04:46:49] <demmonoid_>	Will see if this works
| [Monday 22 November 2010] [04:46:59] <mikko>	demmonoid_: osx build for erlzmq is broken?
| [Monday 22 November 2010] [04:47:22] <demmonoid_>	Yes, it is
| [Monday 22 November 2010] [04:47:47] <demmonoid_>	Looks like it's broken for OS X for a long time...
| [Monday 22 November 2010] [04:48:03] <demmonoid_>	At least for Snow Leopard
| [Monday 22 November 2010] [05:02:07] <demmonoid_>	So, I rebuilt 0mq with -bundle, edited erlzmq's configs so it will compile with -bundle instead of -dynamiclib, but I still get the same error: "i686-apple-darwin10-g++-4.2.1: -bundle not allowed with -dynamiclib"
| [Monday 22 November 2010] [05:02:32] <demmonoid_>	It appears that zeromq libs were built with -dynamiclib anyway
| [Monday 22 November 2010] [05:03:22] <mikko>	sustrik: i added --enable-debug flag to builds
| [Monday 22 November 2010] [05:03:32] <mikko>	sustrik: do you think something like this is useful?
| [Monday 22 November 2010] [05:06:50] <mikko>	as currently it's not possible to really set debug flags
| [Monday 22 November 2010] [05:07:00] <mikko>	-O2 will be in the build line in any case
| [Monday 22 November 2010] [05:07:23] <sustrik>	what I do is:
| [Monday 22 November 2010] [05:07:32] <sustrik>	export CXXFLAGS="-g -O0"
| [Monday 22 November 2010] [05:07:46] <sustrik>	./configure --disable-shared
| [Monday 22 November 2010] [05:07:59] <mikko>	you need to do CPPFLAGS and CFLAGS as well, if building with pgm
| [Monday 22 November 2010] [05:08:05] <sustrik>	right
| [Monday 22 November 2010] [05:08:11] <mikko>	for normal user maybe ./configure --enable-debug might be easier
| [Monday 22 November 2010] [05:08:30] <sustrik>	right, you want to merge all three into s single flag
| [Monday 22 November 2010] [05:08:32] <sustrik>	1. -g
| [Monday 22 November 2010] [05:08:35] <sustrik>	2. -O0
| [Monday 22 November 2010] [05:08:42] <sustrik>	3. --disable-shared
| [Monday 22 November 2010] [05:09:22] <mikko>	i will look into adding --disable-shared as well
| [Monday 22 November 2010] [05:09:29] <sustrik>	it helps
| [Monday 22 November 2010] [05:09:38] <mikko>	the problem is that i am not 100% convinced if this is really needed
| [Monday 22 November 2010] [05:09:51] <mikko>	as for example with sun studio the debug flag is -g0
| [Monday 22 November 2010] [05:09:51] <sustrik>	as if it's not set, the tests are built with a different name
| [Monday 22 November 2010] [05:10:04] <sustrik>	and then there's a wrapper script to launch them
| [Monday 22 November 2010] [05:10:16] <sustrik>	thus launching it within bebugger
| [Monday 22 November 2010] [05:10:22] <sustrik>	actually debugs the shell
| [Monday 22 November 2010] [05:10:28] <sustrik>	not the test program
| [Monday 22 November 2010] [05:10:42] <sustrik>	mikko: i would appreciate it
| [Monday 22 November 2010] [05:10:57] <sustrik>	it saves some time when debuging
| [Monday 22 November 2010] [05:12:51] <mikko>	sustrik: ok, will add