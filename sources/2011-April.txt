===============
2011-April
===============

| [Friday 01 April 2011] [03:50:39] <guido_g>	pieterh: do you plan to specify the "rounds" at the meeting a little more?
| [Friday 01 April 2011] [03:51:18] <pieterh>	guido_g: sure, do you have any suggestions?
| [Friday 01 April 2011] [03:51:35] <guido_g>	not really
| [Friday 01 April 2011] [03:51:57] <guido_g>	some vague ideas
| [Friday 01 April 2011] [03:52:08] <pieterh>	I was thinking barcamp style, but maybe some tracks would help people
| [Friday 01 April 2011] [03:52:19] <pieterh>	morning: 0MQ
| [Friday 01 April 2011] [03:52:22] <pieterh>	afternoon: more 0MQ
| [Friday 01 April 2011] [03:52:28] <pieterh>	evening: less 0MQ
| [Friday 01 April 2011] [03:52:41] <guido_g>	mostly on the "get the most knowledge out of these guys w/o missing a beer"
| [Friday 01 April 2011] [03:52:50] <pieterh>	very late evening: intense beer-fueled hacking session on 0MQ/4.0
| [Friday 01 April 2011] [03:52:58] <pieterh>	next morning: wtf?
| [Friday 01 April 2011] [03:53:29] <guido_g>	i do not intent to think of the next morning before the meeting
| [Friday 01 April 2011] [03:53:42] <pieterh>	we basically have from 9am until 10pm in a nice location with limitless refreshments
| [Friday 01 April 2011] [03:54:02] <guido_g>	ok
| [Friday 01 April 2011] [03:54:52] <guido_g>	i think the details depend on who is at the meeting
| [Friday 01 April 2011] [03:55:34] <pieterh>	yep, pretty much
| [Friday 01 April 2011] [03:55:42] <guido_g>	for example, i'm not that much interested in the build system but want to hear about "real world" problems/solutions wrt. brokerless messaging
| [Friday 01 April 2011] [03:56:20] <pieterh>	you *don't* care about the new autotools option for recursive directory thunking?
| [Friday 01 April 2011] [03:56:27] <pieterh>	some people...
| [Friday 01 April 2011] [03:56:34] <guido_g>	the what?
| [Friday 01 April 2011] [03:56:49] <guido_g>	i mean, i do have an autotools book
| [Friday 01 April 2011] [03:57:04] 	 * pieterh was going to put up a big sign on the 0MQ website...
| [Friday 01 April 2011] [03:57:07] <guido_g>	the only book with really thick dust on it
| [Friday 01 April 2011] [03:57:13] <pieterh>	"0MQ merges with Websphere"
| [Friday 01 April 2011] [23:10:44] <seangrove>	Hey all, I've been through most of the guide, but happy if someone can point me out how to handle async stuff with 0mq in ruby?
| [Friday 01 April 2011] [23:12:52] <seangrove>	Ah, I think I misunderstood, there's no callback pattern
| [Friday 01 April 2011] [23:16:41] <seangrove>	I think the main problem now is that I can't get my program to quit without using ctrl+c
| [Friday 01 April 2011] [23:17:44] <fatpelt_laptop>	evenin all!  just found you through a friend and we are currently playing around with the library.  am i understanding this right that zmq_bind() can't take an ipv6 address?
| [Friday 01 April 2011] [23:44:01] <seangrove>	Hmm, seems like zeromq and rails don't go together
| [Saturday 02 April 2011] [00:17:15] <fatpelt_laptop>	ah found it.  tcp_listener.cpp has v4 hardcoded in it :(
| [Saturday 02 April 2011] [00:18:08] <fatpelt_laptop>	er.. i mean ip.cpp:resolve_ip_interface() (missed a breakpoint there)
| [Saturday 02 April 2011] [01:06:45] <sustrik>	fatpelt_laptop: there was ipv6 support once
| [Saturday 02 April 2011] [01:07:00] <sustrik>	but it collided with ipv4 in some cases
| [Saturday 02 April 2011] [01:07:07] <sustrik>	thus it was taken out
| [Saturday 02 April 2011] [01:07:18] <sustrik>	do you need ipv6 specifically?
| [Saturday 02 April 2011] [01:08:17] <fatpelt_laptop>	sustrik: we are looking at possibly using zmq in our app (www.bongo-project.org).  i'd like v6 yes.  is it required?  technically no
| [Saturday 02 April 2011] [01:08:38] <fatpelt_laptop>	right now we have our own threading and network io model
| [Saturday 02 April 2011] [01:09:06] <sustrik>	it would be nice is someone would look at the ipv6 code
| [Saturday 02 April 2011] [01:09:14] <sustrik>	as i said, it used to be there
| [Saturday 02 April 2011] [01:09:21] <sustrik>	but had to be disabled
| [Saturday 02 April 2011] [01:09:35] <sustrik>	so if there's a real user, the things can be presumably sorted out
| [Saturday 02 April 2011] [01:10:32] <fatpelt_laptop>	hmm.  do you know exactly how it collided?
| [Saturday 02 April 2011] [01:10:47] <fatpelt_laptop>	seems straightforward to modify that cpp file to support v6
| [Saturday 02 April 2011] [01:11:07] <sustrik>	iirc the problem was with dual stack
| [Saturday 02 April 2011] [01:11:31] <fatpelt_laptop>	one other question, (i'm not too far down the guide yet), could we tie gnutls in here?
| [Saturday 02 April 2011] [01:11:36] <sustrik>	in short, in some cases 0mq was using ipv6 interface where in fact user wanted to use ipv4 one
| [Saturday 02 April 2011] [01:12:01] <sustrik>	i think the problem was in how interface names were resolved
| [Saturday 02 April 2011] [01:12:24] <fatpelt_laptop>	hmm.  isn't that an issue for the ipv6 preference?  http://linux.die.net/man/5/gai.conf
| [Saturday 02 April 2011] [01:12:36] <fatpelt_laptop>	ah, but...
| [Saturday 02 April 2011] [01:12:46] <sustrik>	dunno. people reported "0mq not working"
| [Saturday 02 April 2011] [01:13:05] <fatpelt_laptop>	if you were to say, bind to <interfacename> the loop in resolve_nic (or whatever that func was) might return the v6 nic first
| [Saturday 02 April 2011] [01:13:18] <sustrik>	yes, i think that was the problem
| [Saturday 02 April 2011] [01:13:19] <fatpelt_laptop>	i'll bet that was the issue
| [Saturday 02 April 2011] [01:13:42] <sustrik>	any idea about how to solve it?
| [Saturday 02 April 2011] [01:14:44] <sustrik>	if so, i would send a suggestion to the mailing list, where other folks with ipv6 experience can comment
| [Saturday 02 April 2011] [01:14:58] <fatpelt_laptop>	i grok'd the code fully there.... so this might be wrong.  either modify the code to pass in the address family or create a tcp6:// 
| [Saturday 02 April 2011] [01:14:58] <sustrik>	that way the ipv6 stuff could be solved pretty quickly
| [Saturday 02 April 2011] [01:15:21] <sustrik>	no opaque way to deal with that?
| [Saturday 02 April 2011] [01:15:21] <fatpelt_laptop>	er.. that should be i haven't grok'd the code
| [Saturday 02 April 2011] [01:15:55] <sustrik>	the code isn't that importatnt, the question is rather "how it SHOULD work?"
| [Saturday 02 April 2011] [01:16:00] <fatpelt_laptop>	i don't see how you could do that.  gai.conf only applies to getaddrinfo() which isn't used here (unless the user added a host entry with their nic name)
| [Saturday 02 April 2011] [01:16:35] <sustrik>	can you possibly comment on that on the mailing list?
| [Saturday 02 April 2011] [01:16:50] <sustrik>	i would like to see the issue discussed
| [Saturday 02 April 2011] [01:16:57] <fatpelt_laptop>	hmm.  wait...
| [Saturday 02 April 2011] [01:17:09] <fatpelt_laptop>	oh hai.
| [Saturday 02 April 2011] [01:17:14] 	 * sustrik just returned from ietf meeting, been listening to ipv6 rants for days :)
| [Saturday 02 April 2011] [01:18:11] <fatpelt_laptop>	ip.cpp:149 has == AF_INET.  what if that was changed to addr_.ai_family
| [Saturday 02 April 2011] [01:18:51] <sustrik>	let me see
| [Saturday 02 April 2011] [01:18:52] <fatpelt_laptop>	my failing here is that i've got *very* limited exp with this on other platforms so i dunno if that works everywhere.  perhaps i'll try patching it
| [Saturday 02 April 2011] [01:20:02] <fatpelt_laptop>	ah that won't work
| [Saturday 02 April 2011] [01:20:08] <sustrik>	the problem is that family is not passed to zmq_connect or zmq_bind
| [Saturday 02 April 2011] [01:20:24] <sustrik>	so it has to be either deduced or specified explicitly
| [Saturday 02 April 2011] [01:20:40] <sustrik>	i don't know whether the former is feasible
| [Saturday 02 April 2011] [01:21:02] <fatpelt_laptop>	yeah, i'm not sure it can either
| [Saturday 02 April 2011] [01:21:19] <sustrik>	that's why discussion of the issue would be good
| [Saturday 02 April 2011] [01:21:25] <sustrik>	before doing any implementation work
| [Saturday 02 April 2011] [01:21:28] <fatpelt_laptop>	so i take it then that there a a lot of people use the interface name over an ip or anything
| [Saturday 02 April 2011] [01:21:41] <sustrik>	i think so
| [Saturday 02 April 2011] [01:21:47] <sustrik>	haven't done any survey though
| [Saturday 02 April 2011] [01:22:47] <fatpelt_laptop>	sometimes i wish that c supported cool default params on function calls....
| [Saturday 02 April 2011] [01:22:54] <sustrik>	maybe just enhancing the iface name would do?
| [Saturday 02 April 2011] [01:23:04] <sustrik>	tcp://eth0/6:5555
| [Saturday 02 April 2011] [01:23:27] <fatpelt_laptop>	can we guarantee that an interface name can't have a / in it?
| [Saturday 02 April 2011] [01:23:33] <sustrik>	no idea
| [Saturday 02 April 2011] [01:24:08] <sustrik>	fwiw i am not sure whether we can guarantee there's no : in the iface name
| [Saturday 02 April 2011] [01:24:26] <fatpelt_laptop>	old school secondary ips on linux had :
| [Saturday 02 April 2011] [01:24:52] <sustrik>	which would break in the current implementation...
| [Saturday 02 April 2011] [01:25:17] <sustrik>	however, the parsing can be changed
| [Saturday 02 April 2011] [01:25:31] <sustrik>	"find *last* colon in the connection string"
| [Saturday 02 April 2011] [01:25:45] <sustrik>	and "find last slash before the last colon"
| [Saturday 02 April 2011] [01:25:59] <fatpelt_laptop>	http://slexy.org/view/s2VJpj41lr
| [Saturday 02 April 2011] [01:26:38] <sustrik>	ack
| [Saturday 02 April 2011] [01:26:40] <fatpelt_laptop>	internal/2 did not work.  should posted that command as well
| [Saturday 02 April 2011] [01:27:35] <sustrik>	anyway, if you are interested in ipv6 functionality, just post a note on the mailing list and see whether people catch on
| [Saturday 02 April 2011] [01:28:12] <sustrik>	as for tls, there were some people speaking about it, but nodoby implemented it afaik yet
| [Saturday 02 April 2011] [01:29:32] <fatpelt_laptop>	so far in my reading seems like that one is a bit hairy in the current code
| [Saturday 02 April 2011] [01:29:48] <sustrik>	tls?
| [Saturday 02 April 2011] [01:29:56] <fatpelt_laptop>	yeah
| [Saturday 02 April 2011] [01:30:04] <sustrik>	what's the API?
| [Saturday 02 April 2011] [01:30:12] <fatpelt_laptop>	we are currently using gnutls
| [Saturday 02 April 2011] [01:30:15] <sustrik>	standard BSD sockets?
| [Saturday 02 April 2011] [01:30:16] <fatpelt_laptop>	but openssl supports it too
| [Saturday 02 April 2011] [01:30:41] <fatpelt_laptop>	basically in gnutls you create a crypto context and bind an FD to it
| [Saturday 02 April 2011] [01:30:54] <fatpelt_laptop>	then call gnutls_record_recv() (if i remember that function call correctly)
| [Saturday 02 April 2011] [01:31:14] <fatpelt_laptop>	and currently we have to keep track if tls is enabled so we call that over the normal recv()
| [Saturday 02 April 2011] [01:31:38] <sustrik>	ok, then is should not be that complex
| [Saturday 02 April 2011] [01:31:59] <fatpelt_laptop>	well we'd have to change tcp_socket_t::read() 
| [Saturday 02 April 2011] [01:32:10] <fatpelt_laptop>	or have a tls_socket_t class
| [Saturday 02 April 2011] [01:32:20] <sustrik>	or a flag
| [Saturday 02 April 2011] [01:32:26] <sustrik>	implementing 0mq over unix domain sockets was kind of similar
| [Saturday 02 April 2011] [01:32:37] <sustrik>	i recall someone have done it in matter of days
| [Saturday 02 April 2011] [01:33:04] <fatpelt_laptop>	how many devs are there on 0mq ?
| [Saturday 02 April 2011] [01:33:21] <sustrik>	it's a community project
| [Saturday 02 April 2011] [01:33:28] <fatpelt_laptop>	yeah
| [Saturday 02 April 2011] [01:33:36] <fatpelt_laptop>	just curious as to how many active devs were around
| [Saturday 02 April 2011] [01:33:46] <sustrik>	authors file lists 59
| [Saturday 02 April 2011] [01:33:53] <fatpelt_laptop>	(bongo we've only got two for the c code)
| [Saturday 02 April 2011] [01:33:55] <sustrik>	but not of them are active of course
| [Saturday 02 April 2011] [01:33:57] <fatpelt_laptop>	which makes it hard
| [Saturday 02 April 2011] [01:34:27] <sustrik>	i would really recommend discussing it on the mailing list
| [Saturday 02 April 2011] [01:34:34] <sustrik>	you may spark interest in the question
| [Saturday 02 April 2011] [01:34:43] <sustrik>	and someone else may implement it :)
| [Saturday 02 April 2011] [01:34:49] <fatpelt_laptop>	hehe 
| [Saturday 02 April 2011] [01:35:12] <fatpelt_laptop>	i was looking at adding it to our socket library
| [Saturday 02 April 2011] [01:35:25] <fatpelt_laptop>	but if we go with 0mq that'll all go away i believe
| [Saturday 02 April 2011] [01:36:06] <sustrik>	presumably
| [Saturday 02 April 2011] [01:36:37] <sustrik>	additional benefit being is that the community will maintain your code afterwards
| [Saturday 02 April 2011] [01:37:19] <fatpelt_laptop>	another benefit, i'll have to brush off my cpp.  it's been a long while
| [Saturday 02 April 2011] [01:37:38] <sustrik>	:)
| [Saturday 02 April 2011] [01:42:02] <fatpelt_laptop>	i'll read the guide then i'll likely post to -dev
| [Saturday 02 April 2011] [01:42:18] <fatpelt_laptop>	but i'd like to get my terminology *semi* right first....
| [Saturday 02 April 2011] [01:49:18] 	 * fatpelt_laptop steps away
| [Saturday 02 April 2011] [01:49:39] <sustrik>	see you
| [Saturday 02 April 2011] [02:05:10] <CIA-22>	zeromq2: 03Martin Sustrik 07pre30 * r54830ac 10/ (builds/msvc/libzmq/libzmq.vcproj builds/msvc/msvc.sln): 
| [Saturday 02 April 2011] [02:05:10] <CIA-22>	zeromq2: MSVC build system updated to match 3.0 changes
| [Saturday 02 April 2011] [02:05:11] <CIA-22>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/enBrlt
| [Saturday 02 April 2011] [02:51:48] <CIA-22>	zeromq2: 03Martin Sustrik 07pre30 * r85c2a84 10/ (5 files in 4 dirs): 
| [Saturday 02 April 2011] [02:51:48] <CIA-22>	zeromq2: inproc perf tests now work on Windows
| [Saturday 02 April 2011] [02:51:48] <CIA-22>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/ePx6EE
| [Saturday 02 April 2011] [03:24:16] <CIA-22>	zeromq2: 03Pieter Hintjens 07pre30 * r3e65522 10/ src/thread.cpp : 
| [Saturday 02 April 2011] [03:24:16] <CIA-22>	zeromq2: Fixed memory leak with threads on win32
| [Saturday 02 April 2011] [03:24:16] <CIA-22>	zeromq2: Signed-off-by: Pieter Hintjens <ph@imatix.com> - http://bit.ly/fnU3WV
| [Saturday 02 April 2011] [03:27:06] <sustrik>	mikko: hi
| [Saturday 02 April 2011] [03:27:09] <sustrik>	are you there?
| [Saturday 02 April 2011] [05:13:02] <pieterh>	sustrik: hi
| [Saturday 02 April 2011] [08:49:11] <cremes>	seangrove: what do you mean about rails and 0mq? if you have errors you should pastie them or
| [Saturday 02 April 2011] [08:49:13] <cremes>	open a ticket
| [Saturday 02 April 2011] [12:03:18] <mikko>	sustrik: am now
| [Saturday 02 April 2011] [12:05:23] <sustrik>	mikko: hi
| [Saturday 02 April 2011] [12:05:30] <sustrik>	what about doing the reanme?
| [Saturday 02 April 2011] [12:05:35] <sustrik>	rename*
| [Saturday 02 April 2011] [12:05:44] <mikko>	you wanna do it today or tomorrow?
| [Saturday 02 April 2011] [12:05:54] <sustrik>	up to you
| [Saturday 02 April 2011] [12:05:58] <sustrik>	i am free both days
| [Saturday 02 April 2011] [12:06:39] <mikko>	do we know everything we need to update during the rename?
| [Saturday 02 April 2011] [12:06:58] <sustrik>	my idea is:
| [Saturday 02 April 2011] [12:07:05] <sustrik>	1. i raname the repo
| [Saturday 02 April 2011] [12:07:15] <sustrik>	2. you fix the build system
| [Saturday 02 April 2011] [12:07:20] <sustrik>	3. i fix the website
| [Saturday 02 April 2011] [12:07:44] <sustrik>	there's still peter alexander's doxygen thing, but he haven't commented
| [Saturday 02 April 2011] [12:07:52] <sustrik>	so i would just ignore it for now
| [Saturday 02 April 2011] [12:08:14] <pieterh>	sustrik: mikko: I'd really recommend alerting the list beforehand
| [Saturday 02 April 2011] [12:08:28] <sustrik>	rather than afterwards?
| [Saturday 02 April 2011] [12:08:37] <pieterh>	well, there are other people affected, so yes
| [Saturday 02 April 2011] [12:08:45] <sustrik>	ok
| [Saturday 02 April 2011] [12:09:03] <pieterh>	I'd recommend tomorrow morning early, gives us time to patch everything up
| [Saturday 02 April 2011] [12:09:25] <pieterh>	but please announce a time in advance...
| [Saturday 02 April 2011] [12:09:43] <sustrik>	what exactly needs to be patched?
| [Saturday 02 April 2011] [12:09:53] <sustrik>	i mean aside of build system and the site
| [Saturday 02 April 2011] [12:09:58] <pieterh>	for one thing, there are several links on the zeromq.org site
| [Saturday 02 April 2011] [12:10:17] <sustrik>	yeah, i change that
| [Saturday 02 April 2011] [12:10:31] 	 * pieterh scratches head... well, maybe that's it
| [Saturday 02 April 2011] [12:10:45] <mikko>	build system should be just "sed -i 's~git://github.com/zeromq/zeromq2.git~git://github.com/zeromq/libzmq.git~g' */config.xml" and restart
| [Saturday 02 April 2011] [12:10:55] <mikko>	but let me put backups running just in case
| [Saturday 02 April 2011] [12:10:57] <pieterh>	sustrik: your commits today, will you send me the ones I can downstream?
| [Saturday 02 April 2011] [12:11:10] <pieterh>	& those last night
| [Saturday 02 April 2011] [12:11:13] <sustrik>	pieterh: yes
| [Saturday 02 April 2011] [12:11:20] <sustrik>	when i get them to the trunk
| [Saturday 02 April 2011] [12:11:24] <sustrik>	i.e. after the reanme
| [Saturday 02 April 2011] [12:11:27] <sustrik>	rename*
| [Saturday 02 April 2011] [12:11:30] <pieterh>	thanks... note also we can put new stuff into 2.2, even if not fully tested
| [Saturday 02 April 2011] [12:11:36] <sustrik>	ok
| [Saturday 02 April 2011] [12:11:55] <sustrik>	mikko: ping me when you want me to rename the repo
| [Saturday 02 April 2011] [12:12:08] <pieterh>	sustrik: I'll make a list of all pages I can find with the git URI
| [Saturday 02 April 2011] [12:12:16] <sustrik>	3 of them
| [Saturday 02 April 2011] [12:13:20] <sustrik>	pieterh: you may want to check all those extra sites of yours
| [Saturday 02 April 2011] [12:13:50] <pieterh>	sustrik: yes, indeed
| [Saturday 02 April 2011] [12:14:41] <mikko>	sustrik: can we do it after the builds finish?
| [Saturday 02 April 2011] [12:14:43] <pieterh>	lol, wikidot's search functionality actually does work...
| [Saturday 02 April 2011] [12:14:47] <mikko>	the 17:00 builds just started
| [Saturday 02 April 2011] [12:15:09] <mikko>	in about two hours?
| [Saturday 02 April 2011] [12:15:39] <pieterh>	sustrik: http://www.wikidot.com/search:all/a/pf/q/zeromq2 :-)
| [Saturday 02 April 2011] [12:16:19] <pieterh>	mikko: is it a good idea to make this change in the evening? people are more active than in the morning
| [Saturday 02 April 2011] [12:17:06] <mikko>	i'm flexible
| [Saturday 02 April 2011] [12:17:29] <mikko>	has anyone asked if github can redirect?
| [Saturday 02 April 2011] [12:17:41] <pieterh>	they don't
| [Saturday 02 April 2011] [12:18:01] <sustrik>	pieterh: it's saturday evening, nobody cares imo
| [Saturday 02 April 2011] [12:18:02] <pieterh>	well, I'm sure they could, but they explicitly say "we don't do redirects" when you do a  rename
| [Saturday 02 April 2011] [12:18:17] <pieterh>	sustrik: saturday afternoon in the USA...
| [Saturday 02 April 2011] [12:18:24] <sustrik>	spring...
| [Saturday 02 April 2011] [12:18:32] <pieterh>	hmm, true
| [Saturday 02 April 2011] [12:18:33] <sustrik>	people outside, jogging
| [Saturday 02 April 2011] [12:18:38] <pieterh>	geeks? jogging?
| [Saturday 02 April 2011] [12:18:47] <sustrik>	ehm
| [Saturday 02 April 2011] [12:18:56] <sustrik>	being outside then
| [Saturday 02 April 2011] [12:19:04] <pieterh>	you mean where there's wifi?
| [Saturday 02 April 2011] [12:19:04] <sustrik>	that should do
| [Saturday 02 April 2011] [12:19:16] 	 * pieterh is deeply confused
| [Saturday 02 April 2011] [12:19:23] <pieterh>	why would anyone go outside?
| [Saturday 02 April 2011] [12:19:51] <sustrik>	isn't in spring in bxl?
| [Saturday 02 April 2011] [12:20:00] <sustrik>	here it's like 20`C
| [Saturday 02 April 2011] [12:20:02] <sustrik>	sunny
| [Saturday 02 April 2011] [12:20:26] 	 * sustrik been working in the garden in the morning
| [Saturday 02 April 2011] [12:20:26] <pieterh>	the sun makes it hard to read my notebook screen...
| [Saturday 02 April 2011] [12:20:39] <sustrik>	anyway, let's do it
| [Saturday 02 April 2011] [12:20:41] <pieterh>	well, Sunday and Saturday are both off-peak, it's moot
| [Saturday 02 April 2011] [12:20:59] <pieterh>	I'd just recommend emailing the list in advance so people can't complain they weren't warned
| [Saturday 02 April 2011] [12:21:03] <pieterh>	maintenance should be scheduled
| [Saturday 02 April 2011] [12:23:13] <sustrik>	mikko: done
| [Saturday 02 April 2011] [12:23:16] <sustrik>	here you go
| [Saturday 02 April 2011] [12:23:32] <mikko>	ok
| [Saturday 02 April 2011] [12:25:56] <mikko>	builds updated, reloading config now
| [Saturday 02 April 2011] [12:28:49] <pieterh>	sigh... sustrik: that sucks, sorry
| [Saturday 02 April 2011] [12:29:01] <sustrik>	?
| [Saturday 02 April 2011] [12:29:33] <pieterh>	you agreed a few days ago to warn the list
| [Saturday 02 April 2011] [12:29:46] <sustrik>	i did
| [Saturday 02 April 2011] [12:30:00] <pieterh>	in advance
| [Saturday 02 April 2011] [12:30:40] 	 * pieterh sighs...
| [Saturday 02 April 2011] [12:32:36] <sustrik>	ok, website changed
| [Saturday 02 April 2011] [12:38:42] <sustrik>	nice, even github network graph seems to work
| [Saturday 02 April 2011] [12:45:57] <sustrik>	freshmeat updated
| [Saturday 02 April 2011] [12:46:39] <sustrik>	pieterh: btw, freshmeat links point to 2.1.3 for the repo
| [Saturday 02 April 2011] [12:46:48] <sustrik>	but issue tracker link points to master
| [Saturday 02 April 2011] [12:46:52] <sustrik>	is that intended?
| [Saturday 02 April 2011] [12:46:52] <pieterh>	sustrik: yes, that's right
| [Saturday 02 April 2011] [12:47:14] <sustrik>	ah, 2.1 has issue tracker disabled?
| [Saturday 02 April 2011] [12:47:25] <pieterh>	it was intended but now I think it's better to point to the libzmq git
| [Saturday 02 April 2011] [12:47:46] <sustrik>	it's not disabled
| [Saturday 02 April 2011] [12:47:52] <sustrik>	so what's the idea?
| [Saturday 02 April 2011] [12:47:55] <pieterh>	well, we use it for internal patch tracking
| [Saturday 02 April 2011] [12:48:00] <sustrik>	2 issue trackers or one?
| [Saturday 02 April 2011] [12:48:10] <sustrik>	ah
| [Saturday 02 April 2011] [12:48:17] <pieterh>	one issue tracker, of course, for public use
| [Saturday 02 April 2011] [12:48:29] <sustrik>	ok
| [Saturday 02 April 2011] [12:48:49] <pieterh>	packaging project != library included in it
| [Saturday 02 April 2011] [12:49:02] <pieterh>	where do you go log an openpgm issue?
| [Saturday 02 April 2011] [12:49:08] <pieterh>	actually, anywhere you can :-)
| [Saturday 02 April 2011] [12:49:16] <sustrik>	i send an email to steve...
| [Saturday 02 April 2011] [12:49:20] <sustrik>	:)
| [Saturday 02 April 2011] [12:50:44] <sustrik>	mikko: how it's going?
| [Saturday 02 April 2011] [12:50:49] <pieterh>	well, my point is you'd not log an openpgm issue in the libzmq tracker
| [Saturday 02 April 2011] [12:51:06] 	 * pieterh doesn't really have a point
| [Saturday 02 April 2011] [12:51:24] <sustrik>	people actually do, then it's kind of upstreamed to openpgm
| [Saturday 02 April 2011] [12:51:33] <sustrik>	but there's no real process there
| [Saturday 02 April 2011] [12:51:35] <pieterh>	yes, but it's not consistent
| [Saturday 02 April 2011] [12:51:53] <pieterh>	consistency is, IMO, issues get tracked close to packaging
| [Saturday 02 April 2011] [12:51:57] <pieterh>	not that I really want this
| [Saturday 02 April 2011] [12:52:13] <pieterh>	but it's what you'd expect: you report an issue to the person who gave you the package
| [Saturday 02 April 2011] [12:52:19] <pieterh>	that person reports it upstream, etc.
| [Saturday 02 April 2011] [12:52:35] <sustrik>	yep, something like that
| [Saturday 02 April 2011] [12:52:43] <pieterh>	I think this will become easier now with the new name
| [Saturday 02 April 2011] [12:59:38] <sustrik>	travlr: hi
| [Saturday 02 April 2011] [13:00:18] <mikko>	sustrik: should be done
| [Saturday 02 April 2011] [13:00:51] <sustrik>	great!
| [Saturday 02 April 2011] [13:00:58] <sustrik>	thanks for help!
| [Saturday 02 April 2011] [13:01:33] <mikko>	np
| [Saturday 02 April 2011] [13:01:44] <mikko>	i'll rename the builds at some point as well
| [Saturday 02 April 2011] [13:01:44] <pieterh>	sustrik: ok, there's no way to make an html redirect, but I've made a map
| [Saturday 02 April 2011] [13:02:08] <mikko>	is zeromq2-1 going to be libzmq2-1?
| [Saturday 02 April 2011] [13:02:29] <pieterh>	mikko: no, libzmq is the library, zeromq is the package
| [Saturday 02 April 2011] [13:02:41] <pieterh>	package = (libzmq, libpgm, libzapi, etc)
| [Saturday 02 April 2011] [13:03:01] <sustrik>	you should package some bindings along with it
| [Saturday 02 April 2011] [13:03:08] <sustrik>	people would love that
| [Saturday 02 April 2011] [13:03:14] <pieterh>	yes, indeed
| [Saturday 02 April 2011] [13:03:35] <pieterh>	the idea was to start with the simplest one, libzapi, since it already uses the same autotooling, and then add more bindings
| [Saturday 02 April 2011] [13:03:51] <sustrik>	jzmq used to use autotools
| [Saturday 02 April 2011] [13:04:01] <sustrik>	but that may have changed in the meantime
| [Saturday 02 April 2011] [13:04:27] <pieterh>	sustrik: the map is at https://github.com/zeromq/zeromq2
| [Saturday 02 April 2011] [13:05:06] <sustrik>	wouldn't it be better to just point to the website?
| [Saturday 02 April 2011] [13:05:28] <sustrik>	the links will break gradually in the future
| [Saturday 02 April 2011] [13:05:28] <pieterh>	"there's no way to make an html redirect, but I've made a map"
| [Saturday 02 April 2011] [13:05:56] <sustrik>	i mean, there are pointers to 10 different projects in the map
| [Saturday 02 April 2011] [13:06:11] <pieterh>	yes
| [Saturday 02 April 2011] [13:06:21] <sustrik>	not likely to stay functional
| [Saturday 02 April 2011] [13:06:27] <pieterh>	right now many of these projects don't have their own web sites or pages
| [Saturday 02 April 2011] [13:06:38] <pieterh>	they should, then pages like this can be properly done
| [Saturday 02 April 2011] [13:06:47] <sustrik>	why not just point to zero.mq
| [Saturday 02 April 2011] [13:06:49] <sustrik>	or something
| [Saturday 02 April 2011] [13:07:21] <sustrik>	"This is a deprecated project. Please check zero.mq for more info."
| [Saturday 02 April 2011] [13:07:27] <pieterh>	because anyone coming here, looking for the repository, is going to be really confused (and annoyed) if they land on zero.mq instead
| [Saturday 02 April 2011] [13:07:36] <pieterh>	"OMG 0MQ is deprecated!"
| [Saturday 02 April 2011] [13:07:49] <pieterh>	the point is to assist people who land on the old URI
| [Saturday 02 April 2011] [13:07:58] <pieterh>	placing libzmq in its context
| [Saturday 02 April 2011] [13:08:08] <pieterh>	this page will be abandoned in a few weeks
| [Saturday 02 April 2011] [13:08:12] <sustrik>	"Repo have been moved. Check github.com/zeromq/libzmq instead."
| [Saturday 02 April 2011] [13:08:24] <sustrik>	ah, ok then
| [Saturday 02 April 2011] [13:08:27] <pieterh>	well, that's what it says, doesn't it?
| [Saturday 02 April 2011] [13:08:39] <sustrik>	don't forget to delete it afterwards
| [Saturday 02 April 2011] [13:09:24] <pieterh>	this repository has no purpose except to help people who still use the old URI
| [Saturday 02 April 2011] [13:09:34] <pieterh>	I'd like to put a map like this onto the community site as well
| [Saturday 02 April 2011] [13:09:50] <pieterh>	but it requires more explicit and consistent visibility for each project
| [Saturday 02 April 2011] [13:34:08] <sustrik>	CIA is broken
| [Saturday 02 April 2011] [13:34:15] <sustrik>	mato has to fix that
| [Saturday 02 April 2011] [13:59:58] <pieterh>	sustrik: those patches, which ones can go into 2.1 stable?
| [Saturday 02 April 2011] [14:00:28] <pieterh>	I assume all except the 'project name change'?
| [Saturday 02 April 2011] [14:01:33] <sustrik>	all of them i think
| [Saturday 02 April 2011] [14:01:44] <sustrik>	the 'name change' changes README
| [Saturday 02 April 2011] [14:01:53] <sustrik>	that points to zeromq2
| [Saturday 02 April 2011] [14:02:50] <pieterh>	ah, ok... nice, thanks
| [Saturday 02 April 2011] [14:15:14] <yrashk>	fixing totally broken erlzmq2
| [Saturday 02 April 2011] [14:17:53] <yrashk>	was everything broken on purpose or is it 3.0 preparation?
| [Saturday 02 April 2011] [14:18:06] <pieterh>	yrashk: 'totally broken' means what exactly?
| [Saturday 02 April 2011] [14:18:39] <jond>	pieterh , sustrik: git pull is complaining for me now. I have a feeling this change could have been managed better
| [Saturday 02 April 2011] [14:18:39] <yrashk>	well the API went south
| [Saturday 02 April 2011] [14:18:49] <yrashk>	constants, different calls
| [Saturday 02 April 2011] [14:18:51] <yrashk>	(master)
| [Saturday 02 April 2011] [14:18:57] <pieterh>	yrashk: indeed, the API has changed in libzmq master
| [Saturday 02 April 2011] [14:19:10] <pieterh>	jond: you'll need to change your remote
| [Saturday 02 April 2011] [14:19:20] <yrashk>	so when do we need to start supporting it?
| [Saturday 02 April 2011] [14:19:31] <pieterh>	yrashk: it's still unstable so up to you, really
| [Saturday 02 April 2011] [14:19:37] <jond>	pieterh : i've done the commands from the email
| [Saturday 02 April 2011] [14:20:04] <yrashk>	may be later in a branch, then
| [Saturday 02 April 2011] [14:20:08] <pieterh>	jond: could you tell me what git complains about, then?
| [Saturday 02 April 2011] [14:20:35] <pieterh>	yrashk: I'm going to support the 3.0 API in libzapi as soon as possible
| [Saturday 02 April 2011] [14:21:02] <jond>	pieterh: this is what its saying .... jon@ubik:~/work/zeromq2$ git pull
| [Saturday 02 April 2011] [14:21:02] <jond>	You asked me to pull without telling me which branch you
| [Saturday 02 April 2011] [14:21:02] <jond>	want to merge with, and 'branch.master.merge' in
| [Saturday 02 April 2011] [14:21:02] <jond>	your configuration file does not tell me either.	Please
| [Saturday 02 April 2011] [14:21:02] <jond>	specify which branch you want to merge on the command line and
| [Saturday 02 April 2011] [14:21:03] <jond>	try again (e.g. 'git pull <repository> <refspec>').
| [Saturday 02 April 2011] [14:21:04] <jond>	See git-pull(1) for details.
| [Saturday 02 April 2011] [14:21:06] <jond>	If you often merge with the same branch, you may want to
| [Saturday 02 April 2011] [14:21:08] <jond>	configure the following variables in your configuration
| [Saturday 02 April 2011] [14:21:10] <jond>	file:
| [Saturday 02 April 2011] [14:21:12] <jond>	    branch.master.remote = <nickname>
| [Saturday 02 April 2011] [14:21:14] <jond>	    branch.master.merge = <remote-ref>
| [Saturday 02 April 2011] [14:21:16] <jond>	    remote.<nickname>.url = <url>
| [Saturday 02 April 2011] [14:21:18] <jond>	    remote.<nickname>.fetch = <refspec>
| [Saturday 02 April 2011] [14:21:20] <jond>	See git-config(1) for details.
| [Saturday 02 April 2011] [14:21:23] <pieterh>	git madness...
| [Saturday 02 April 2011] [14:21:30] <pieterh>	what command were you using?
| [Saturday 02 April 2011] [14:21:37] <jond>	pieterh: git pull
| [Saturday 02 April 2011] [14:21:51] <pieterh>	there are defaults, I don't know how they work and never use them
| [Saturday 02 April 2011] [14:21:55] <pieterh>	git pull origin master
| [Saturday 02 April 2011] [14:22:07] <pieterh>	pulling the wrong branch by accident is traumatic
| [Saturday 02 April 2011] [14:22:32] <jond>	pieterh: thx that appears to have worked
| [Saturday 02 April 2011] [14:22:51] <pieterh>	goodo!
| [Saturday 02 April 2011] [14:23:25] <jond>	pieter: but subsequent 'git pull' produce the same message. I never used to do this......
| [Saturday 02 April 2011] [14:24:10] <pieterh>	jond: like I said, there are defaults, I don't use them, don't trust them.
| [Saturday 02 April 2011] [14:24:19] <jond>	pieterh: life is too short i'll clone it
| [Saturday 02 April 2011] [14:24:30] <pieterh>	indeed
| [Saturday 02 April 2011] [14:33:27] <yrashk>	where did ZMQ_RECOVERY_IVL_MSEC/ZMQ_RECONNECT_IVL_MAX go in v2.1.0?
| [Saturday 02 April 2011] [14:34:20] <sustrik>	there were not yet there back then iirc
| [Saturday 02 April 2011] [14:34:32] <yrashk>	I am lost
| [Saturday 02 April 2011] [14:34:40] <yrashk>	erlzmq2 already supported those
| [Saturday 02 April 2011] [14:34:45] <yrashk>	:-\
| [Saturday 02 April 2011] [14:34:56] <sustrik>	what's wrong with using 2.1.3?
| [Saturday 02 April 2011] [14:35:03] <yrashk>	where's the tag for it?
| [Saturday 02 April 2011] [14:35:14] <sustrik>	zeromq2-1 repo
| [Saturday 02 April 2011] [14:35:38] <yrashk>	:-O
| [Saturday 02 April 2011] [14:35:49] <mikko>	this is confusing for the end-users
| [Saturday 02 April 2011] [14:35:53] <yrashk>	very
| [Saturday 02 April 2011] [14:36:08] <sustrik>	yep, many changes at the same time
| [Saturday 02 April 2011] [14:36:30] <yrashk>	multiple repos are baaaaad
| [Saturday 02 April 2011] [14:36:30] <sustrik>	but still better than doing one change at a time
| [Saturday 02 April 2011] [14:36:31] <yrashk>	:-(
| [Saturday 02 April 2011] [14:36:32] <mikko>	i mean the whole multiple repos
| [Saturday 02 April 2011] [14:37:22] <sustrik>	well, it's about process
| [Saturday 02 April 2011] [14:37:47] <sustrik>	for 1 repo you need 1 process
| [Saturday 02 April 2011] [14:38:13] <sustrik>	so people would have to agree on what the right process is
| [Saturday 02 April 2011] [14:38:22] <yrashk>	what do you mean by process?
| [Saturday 02 April 2011] [14:38:28] <yrashk>	what's wrong with branches?
| [Saturday 02 April 2011] [14:38:29] <mikko>	sustrik: i disagree with this
| [Saturday 02 April 2011] [14:38:34] <sustrik>	the set of rules to maintain the repo
| [Saturday 02 April 2011] [14:38:39] <yrashk>	what's wrong with branches?
| [Saturday 02 April 2011] [14:38:40] <mikko>	sustrik: for one logical entity you need a process
| [Saturday 02 April 2011] [14:38:56] <mikko>	sustrik: that logical entity can live in the same repo
| [Saturday 02 April 2011] [14:39:01] <sustrik>	you mean having different processes for different branches?
| [Saturday 02 April 2011] [14:39:07] <mikko>	sustrik: the process would be no different if 2-1 was a branch
| [Saturday 02 April 2011] [14:39:17] <mikko>	pieter would still merge changes from other branches
| [Saturday 02 April 2011] [14:39:55] <sustrik>	yes, that's not the problem
| [Saturday 02 April 2011] [14:40:09] <mikko>	sustrik: but it is
| [Saturday 02 April 2011] [14:40:16] <sustrik>	?
| [Saturday 02 April 2011] [14:40:18] <mikko>	sustrik: currently people expect to find everything in libzmq repo
| [Saturday 02 April 2011] [14:40:31] <mikko>	like tags, branches etc
| [Saturday 02 April 2011] [14:40:36] <sustrik>	i am happy to host 2-1 stable in libzmq
| [Saturday 02 April 2011] [14:40:45] <sustrik>	but then i want it to follow my process
| [Saturday 02 April 2011] [14:40:47] <sustrik>	that's it
| [Saturday 02 April 2011] [14:41:00] <mikko>	why does it have to if it doesn't touch your work at all?
| [Saturday 02 April 2011] [14:41:02] <yrashk>	you can do this with a branch
| [Saturday 02 April 2011] [14:41:17] <sustrik>	well, yes, that's the question
| [Saturday 02 April 2011] [14:41:29] <sustrik>	is it ok to have separate processes for separate branches?
| [Saturday 02 April 2011] [14:41:37] 	 * yrashk fixed erlzmq2 to use zeromq2-1 repo meanwhile
| [Saturday 02 April 2011] [14:41:42] <yrashk>	sustrik: of course it is
| [Saturday 02 April 2011] [14:41:50] <mikko>	my current thinking is the following:
| [Saturday 02 April 2011] [14:42:06] <mikko>	i would be a lot happier if i had a branch / branches in libzmq repo
| [Saturday 02 April 2011] [14:42:08] <sustrik>	like for branch X it's ok to break backward compatibility for minor version, while in branch Y it cannot happen?
| [Saturday 02 April 2011] [14:42:12] <mikko>	that people can merge 
| [Saturday 02 April 2011] [14:42:17] <mikko>	sustrik: yes
| [Saturday 02 April 2011] [14:43:15] <yrashk>	sustrik: totally fine
| [Saturday 02 April 2011] [14:43:16] <jond>	mikko: i agree. the process and repos seem to be different to any other project , but i'm far from a git expert. but something instinctive tells me there has to be an easier way
| [Saturday 02 April 2011] [14:43:21] <mikko>	i tend to find the mailing-list patches very tedious
| [Saturday 02 April 2011] [14:43:28] <yrashk>	and MUCH less confusing than multiple repos
| [Saturday 02 April 2011] [14:43:37] <mikko>	and they make things very hard to track on this side of the fence
| [Saturday 02 April 2011] [14:43:47] <mikko>	having multiple patches "in-flight"
| [Saturday 02 April 2011] [14:44:02] <pieterh>	it'd be nice to move the 2.1 branch back into libzmq and keep the distribution repo purely for packaging
| [Saturday 02 April 2011] [14:44:20] <mikko>	pieterh: you can achieve this with submodules i believe
| [Saturday 02 April 2011] [14:44:25] <pieterh>	sure, easy
| [Saturday 02 April 2011] [14:44:36] <pieterh>	the real problem is as sustrik said, different processes within one repo
| [Saturday 02 April 2011] [14:44:37] <mikko>	that way there are no copies
| [Saturday 02 April 2011] [14:44:46] <mikko>	pieterh: why is this a problem?
| [Saturday 02 April 2011] [14:44:53] <mikko>	pieterh: you have multiple branches
| [Saturday 02 April 2011] [14:44:55] <pieterh>	well, it's been a big problem in the past
| [Saturday 02 April 2011] [14:45:05] <pieterh>	agreed, we didn't have separate branches
| [Saturday 02 April 2011] [14:45:15] <mikko>	there was master/maint in the past
| [Saturday 02 April 2011] [14:45:33] <pieterh>	well, I see these specific issues:
| [Saturday 02 April 2011] [14:45:38] <pieterh>	- single issue tracker
| [Saturday 02 April 2011] [14:45:42] <pieterh>	- single set of pull requests
| [Saturday 02 April 2011] [14:46:14] <mikko>	the issue tracker in github is not very good to be fair
| [Saturday 02 April 2011] [14:46:23] <sustrik>	true
| [Saturday 02 April 2011] [14:46:24] <pieterh>	but mikko, this would not solve the problem of applying patches to X versions
| [Saturday 02 April 2011] [14:46:26] <sustrik>	and slow
| [Saturday 02 April 2011] [14:46:27] <mikko>	but in normal cases you would select the version of the product
| [Saturday 02 April 2011] [14:46:33] <pieterh>	it would not change anything, really
| [Saturday 02 April 2011] [14:46:39] <mikko>	the single set of pull requests is ok imho
| [Saturday 02 April 2011] [14:46:55] <pieterh>	take your latest three patches
| [Saturday 02 April 2011] [14:47:10] <pieterh>	what's the process for applying these to 2.1, 2.2, and 3.0?
| [Saturday 02 April 2011] [14:47:15] <mikko>	pieterh: how would it be nay different for you applying to a branch then a separate repo?
| [Saturday 02 April 2011] [14:47:26] <pieterh>	mikko: that's six and half-a-dozen, for sure
| [Saturday 02 April 2011] [14:47:43] <pieterh>	with the difference that working in one repo makes it easier to really mess up other peoples' work
| [Saturday 02 April 2011] [14:48:45] <pieterh>	this is a real risk, especially for core projects
| [Saturday 02 April 2011] [14:49:00] <mikko>	why is this a risk?
| [Saturday 02 April 2011] [14:49:13] <pieterh>	people like me get distracted and make mistakes with git
| [Saturday 02 April 2011] [14:49:16] <pieterh>	unrecoverable mistakes
| [Saturday 02 April 2011] [14:49:21] <mikko>	the multiple repos seem to be about creating silos
| [Saturday 02 April 2011] [14:49:28] <pieterh>	the more complex the repo, the more risk of error
| [Saturday 02 April 2011] [14:49:30] <yrashk>	unrecoverable? how so?
| [Saturday 02 April 2011] [14:49:45] <pieterh>	well, given sufficient git expertise, anything is recoverable
| [Saturday 02 April 2011] [14:49:52] <pieterh>	I assume
| [Saturday 02 April 2011] [14:50:06] <yrashk>	unless you do rm -rf when you're distracted
| [Saturday 02 April 2011] [14:50:12] <yrashk>	but noting is going to help with that :-P
| [Saturday 02 April 2011] [14:50:16] <mikko>	your process would be very much similar to what it is now
| [Saturday 02 April 2011] [14:50:22] <mikko>	you would cherry pick changes as you do now
| [Saturday 02 April 2011] [14:50:30] <pieterh>	mikko: we agree on that, don't need to convince me of anything
| [Saturday 02 April 2011] [14:50:33] <mikko>	let's break the silos rather than create more
| [Saturday 02 April 2011] [14:50:46] <pieterh>	however your branch becomes the silo, it's no different
| [Saturday 02 April 2011] [14:51:01] <mikko>	but the tools give you more visibility
| [Saturday 02 April 2011] [14:51:05] <mikko>	git log --all for example
| [Saturday 02 April 2011] [14:51:10] <pieterh>	I have 40 gits and would rather each one just had a master branch
| [Saturday 02 April 2011] [14:51:20] <pieterh>	than one or two having a whole bunch of branches
| [Saturday 02 April 2011] [14:52:16] <pieterh>	but like I said, it'd be nice to have the 2.1 branch back where it belongs
| [Saturday 02 April 2011] [14:52:22] <pieterh>	I'm not arguing against that, really
| [Saturday 02 April 2011] [14:52:35] <pieterh>	however, it won't solve mikko's problem of "where do I send this patch"
| [Saturday 02 April 2011] [14:53:24] <mikko>	so let's just reiterate things:
| [Saturday 02 April 2011] [14:53:33] <mikko>	why do we send patches to mailing-list at the moment?
| [Saturday 02 April 2011] [14:53:48] <mikko>	what is the problem that this solves?
| [Saturday 02 April 2011] [14:53:49] <pieterh>	that's how the linux kernel process works
| [Saturday 02 April 2011] [14:53:50] <sustrik>	1. no patch goes publicly unnoticed
| [Saturday 02 April 2011] [14:53:53] <sustrik>	2. peer review
| [Saturday 02 April 2011] [14:54:10] <pieterh>	those points are happily covered by posting a commit URI to the list
| [Saturday 02 April 2011] [14:54:16] <pieterh>	as we saw with the HTTP transport thread
| [Saturday 02 April 2011] [14:54:32] <sustrik>	3. no dependency of logs on a specific commercial entity (github)
| [Saturday 02 April 2011] [14:54:40] <mikko>	sustrik: would you argue that there would be more visibility if all commits went to mailing-list?
| [Saturday 02 April 2011] [14:54:52] <mikko>	sustrik: at the moment your work for example is not very visible to mailing-lists
| [Saturday 02 April 2011] [14:55:01] <pieterh>	mikko: that would be good for libzmq, not for other projects
| [Saturday 02 April 2011] [14:55:09] <sustrik>	mikko: i would prefer to send my work there as well
| [Saturday 02 April 2011] [14:55:18] <sustrik>	if people agree, i would start with that
| [Saturday 02 April 2011] [14:55:24] <pieterh>	but not patches, just the commit summary, as for IRC
| [Saturday 02 April 2011] [14:56:07] <pieterh>	mikko: this should apply to all libzmq branches which are for public consumption
| [Saturday 02 April 2011] [14:56:35] <mikko>	github can do this: http://help.github.com/post-receive-hooks/
| [Saturday 02 April 2011] [14:56:39] <sustrik>	actually, it up to me to decide :)
| [Saturday 02 April 2011] [14:56:43] <mikko>	which would allow us to automate the mailing
| [Saturday 02 April 2011] [14:56:48] <sustrik>	i'll start sending patches to the mailing list
| [Saturday 02 April 2011] [14:57:13] <pieterh>	sustrik: I think your reluctance to post github URIs is counter-productive
| [Saturday 02 April 2011] [14:57:20] <sustrik>	mikko: how does that work?
| [Saturday 02 April 2011] [14:57:28] <sustrik>	creates a pull request from an email?
| [Saturday 02 April 2011] [14:57:37] <mikko>	sustrik: github sends a HTTP post to your defined url
| [Saturday 02 April 2011] [14:57:45] <mikko>	which can then assemble email and send to list
| [Saturday 02 April 2011] [14:57:55] <pieterh>	sustrik: if at some point github dies, the URIs can trivially be mapped to another location, the commit IDs don't change
| [Saturday 02 April 2011] [14:58:12] <sustrik>	mikko: that heppens when a patch is pushed to the repo?
| [Saturday 02 April 2011] [14:58:19] <pieterh>	yes
| [Saturday 02 April 2011] [14:58:41] <sustrik>	no good, the review should happen before the patch is pushed
| [Saturday 02 April 2011] [14:58:52] <pieterh>	sustrik: topic branches, then
| [Saturday 02 April 2011] [14:59:05] <pieterh>	and you can simply post the commit URI and ask for review
| [Saturday 02 April 2011] [14:59:05] <sustrik>	how would that work?
| [Saturday 02 April 2011] [14:59:14] <sustrik>	ah
| [Saturday 02 April 2011] [14:59:20] <sustrik>	no log then once github fies
| [Saturday 02 April 2011] [14:59:22] <sustrik>	dies
| [Saturday 02 April 2011] [14:59:30] <mikko>	sustrik: what do you mean?
| [Saturday 02 April 2011] [14:59:38] <pieterh>	see my comment just now about "when github dies"
| [Saturday 02 April 2011] [14:59:38] <mikko>	sustrik: they are branches, everyone will have a copy
| [Saturday 02 April 2011] [14:59:41] <sustrik>	you won't be able to trace the discussion back
| [Saturday 02 April 2011] [14:59:45] <pieterh>	sigh
| [Saturday 02 April 2011] [14:59:50] <mikko>	sustrik: the discussion happens on mailing-list
| [Saturday 02 April 2011] [15:00:00] <mikko>	sustrik: only thing github does is automate the mailing
| [Saturday 02 April 2011] [15:00:03] <sustrik>	ah you mean everybody would work on libzmq repo
| [Saturday 02 April 2011] [15:00:03] <sustrik>	?
| [Saturday 02 April 2011] [15:00:08] <mikko>	sustrik: yes
| [Saturday 02 April 2011] [15:00:16] <sustrik>	hm
| [Saturday 02 April 2011] [15:00:19] <mikko>	think about repository and branch as different concepts
| [Saturday 02 April 2011] [15:00:39] <sustrik>	would that require everyone to have write access to libzmq repo?
| [Saturday 02 April 2011] [15:00:51] <pieterh>	mikko: I'm happy to switch to any new organization you propose, if you can make clear instructions for using git properly
| [Saturday 02 April 2011] [15:00:56] <mikko>	sustrik: i think a selected crowd would be good enough
| [Saturday 02 April 2011] [15:01:08] <sustrik>	what about others?
| [Saturday 02 April 2011] [15:01:12] <sustrik>	mailing list?
| [Saturday 02 April 2011] [15:01:22] <mikko>	for example
| [Saturday 02 April 2011] [15:01:28] <sustrik>	that makes sense
| [Saturday 02 April 2011] [15:01:36] <mikko>	what i am after is a bit smoother workflow for people who contribute more than one patch
| [Saturday 02 April 2011] [15:01:43] <sustrik>	ack
| [Saturday 02 April 2011] [15:01:49] <mikko>	being able to do refactoring etc in my own branch
| [Saturday 02 April 2011] [15:02:00] <sustrik>	yes, i think that makes sense
| [Saturday 02 April 2011] [15:02:06] <mikko>	for example in some cases there are incremental changes
| [Saturday 02 April 2011] [15:02:08] <mikko>	or so
| [Saturday 02 April 2011] [15:02:12] <pieterh>	mikko: what branch do your three patches go to?
| [Saturday 02 April 2011] [15:02:30] <mikko>	pieterh: master
| [Saturday 02 April 2011] [15:02:33] <pieterh>	do you make a topic branch with them?
| [Saturday 02 April 2011] [15:02:47] <mikko>	pieterh: in this workflow:
| [Saturday 02 April 2011] [15:02:57] <mikko>	i would branch off from master, do my changes
| [Saturday 02 April 2011] [15:03:02] <mikko>	push the branch to github
| [Saturday 02 April 2011] [15:03:04] <pieterh>	mikko: and then if they don't apply cleanly to 2.1, I ask you for help?
| [Saturday 02 April 2011] [15:03:10] <mikko>	pieterh: yes
| [Saturday 02 April 2011] [15:03:15] <mikko>	i think that's only fair
| [Saturday 02 April 2011] [15:03:17] <pieterh>	perfect
| [Saturday 02 April 2011] [15:03:20] <mikko>	let's collaborate
| [Saturday 02 April 2011] [15:03:26] <mikko>	rather than silo ourselves
| [Saturday 02 April 2011] [15:03:30] <pieterh>	I think this is close to the original workflow I proposed ages ago
| [Saturday 02 April 2011] [15:03:50] <sustrik>	sounds good
| [Saturday 02 April 2011] [15:03:55] <pieterh>	the silo is really to allow experimentation, and I think that's been very important
| [Saturday 02 April 2011] [15:04:02] <sustrik>	but these are *topic* branches
| [Saturday 02 April 2011] [15:04:05] <mikko>	if people who know about the patches collaborate on the different branches we can ship best possible product
| [Saturday 02 April 2011] [15:04:09] <pieterh>	indeed
| [Saturday 02 April 2011] [15:04:11] <mikko>	which i think is the ultimate aim
| [Saturday 02 April 2011] [15:04:16] <sustrik>	the 2-1 is a bit different
| [Saturday 02 April 2011] [15:04:26] <pieterh>	that was my idea of splitting 'release maintainer' from 'contributor'
| [Saturday 02 April 2011] [15:04:28] <sustrik>	as it's a maintenance branch. not a topic branch
| [Saturday 02 April 2011] [15:04:42] <pieterh>	sustrik: topic branches always apply to master, right?
| [Saturday 02 April 2011] [15:04:57] <pieterh>	maintenance branches get downstreamed from master
| [Saturday 02 April 2011] [15:05:08] <sustrik>	that's the simplest system
| [Saturday 02 April 2011] [15:05:13] <pieterh>	makes sense to me
| [Saturday 02 April 2011] [15:05:25] <sustrik>	however, maintainers sometimes choose to maintain a patchset without upstreaming it
| [Saturday 02 April 2011] [15:05:29] <sustrik>	say RHEL patches
| [Saturday 02 April 2011] [15:05:30] <pieterh>	for sure, yes
| [Saturday 02 April 2011] [15:05:37] <pieterh>	especially when master diverges too far
| [Saturday 02 April 2011] [15:05:43] <pieterh>	old code will have its own bugs
| [Saturday 02 April 2011] [15:06:05] <pieterh>	we have this with 2.0
| [Saturday 02 April 2011] [15:06:44] <pieterh>	mikko: thanks for pushing these ideas
| [Saturday 02 April 2011] [15:07:03] <sustrik>	ok, so topic branches make sense
| [Saturday 02 April 2011] [15:07:11] <pieterh>	I'm happy to work within any process that is documented so I can use it on Monday morning before coffee
| [Saturday 02 April 2011] [15:07:16] <sustrik>	having stable branches in main repo as well
| [Saturday 02 April 2011] [15:07:20] <pieterh>	yes
| [Saturday 02 April 2011] [15:07:22] <sustrik>	however, there's still the process problem
| [Saturday 02 April 2011] [15:07:29] <pieterh>	yes
| [Saturday 02 April 2011] [15:07:45] <pieterh>	sustrik: you realize that mail archives can be patched
| [Saturday 02 April 2011] [15:07:53] <pieterh>	and that any URIs to dead sites can be fixed up
| [Saturday 02 April 2011] [15:08:10] <pieterh>	what's relevant is that commit IDs are independent of the website
| [Saturday 02 April 2011] [15:08:24] <sustrik>	i mean the multiple processes problem, not the github problem
| [Saturday 02 April 2011] [15:08:38] <pieterh>	I think we resolve that with clear documentation
| [Saturday 02 April 2011] [15:08:59] <pieterh>	no ad-hoc workflows
| [Saturday 02 April 2011] [15:09:03] <pieterh>	otherwise it'll crash and burn
| [Saturday 02 April 2011] [15:09:20] <mikko>	testing the hooks now
| [Saturday 02 April 2011] [15:09:22] <mikko>	brb
| [Saturday 02 April 2011] [15:09:37] <sustrik>	i mean, if i am responsible for a repo i don't want any backward incompatible changes in minor versions
| [Saturday 02 April 2011] [15:09:50] <sustrik>	because that can break things in production
| [Saturday 02 April 2011] [15:09:59] <pieterh>	sustrik: I think that's a different discussion
| [Saturday 02 April 2011] [15:10:07] <sustrik>	and i don't want to be responsible for a repo that does that
| [Saturday 02 April 2011] [15:10:14] <pieterh>	valid, but it really requires user involvement in such decisions
| [Saturday 02 April 2011] [15:10:44] <pieterh>	every time we've asked this question, people have answered "give us new functionality, we can handle breakage"
| [Saturday 02 April 2011] [15:11:02] <pieterh>	I think you'll be surprised by the speed people jump onto 3.0
| [Saturday 02 April 2011] [15:11:03] <sustrik>	most people have no experience with process
| [Saturday 02 April 2011] [15:11:10] <sustrik>	they just want new functionality
| [Saturday 02 April 2011] [15:11:12] <pieterh>	sure, but 0MQ is still a young product
| [Saturday 02 April 2011] [15:11:20] <pieterh>	messaging lifecycles are 12-18 months
| [Saturday 02 April 2011] [15:11:26] <sustrik>	they don't care about breaking other's deployments
| [Saturday 02 April 2011] [15:11:33] <pieterh>	it's a mistake to over-estimate the depth of production deployment
| [Saturday 02 April 2011] [15:11:38] <pieterh>	IMO
| [Saturday 02 April 2011] [15:11:56] <pieterh>	and binding authors should be super-sensitive to this, they are the ones who will get the blame
| [Saturday 02 April 2011] [15:12:01] <sustrik>	why i mistake/
| [Saturday 02 April 2011] [15:12:02] <sustrik>	?
| [Saturday 02 April 2011] [15:12:08] <sustrik>	you can't go wrong on that side
| [Saturday 02 April 2011] [15:12:17] <sustrik>	you can go wrong on the other side though
| [Saturday 02 April 2011] [15:12:21] <mikko>	https://gist.github.com/1f309de5283ea59c3395
| [Saturday 02 April 2011] [15:12:32] <mikko>	this is the email github sends if you use their pre-defined email hook
| [Saturday 02 April 2011] [15:12:43] <pieterh>	well, look, we've solved this problem for 0MQ
| [Saturday 02 April 2011] [15:12:57] <sustrik>	?
| [Saturday 02 April 2011] [15:13:00] <pieterh>	we do have rapid stable releases and freedom to break new versions
| [Saturday 02 April 2011] [15:13:14] <sustrik>	mikko: so every change to a topic branch would go to the mailing list?
| [Saturday 02 April 2011] [15:13:14] <pieterh>	any new functionality in the 2.x branch goes into 2.2
| [Saturday 02 April 2011] [15:13:30] <pieterh>	as far as I'm concerned (and there have been zero actual complaints) it's solved
| [Saturday 02 April 2011] [15:13:45] <mikko>	sustrik: every change would be mailed out
| [Saturday 02 April 2011] [15:13:46] <sustrik>	the stable releases are not backward and forward compatible
| [Saturday 02 April 2011] [15:13:56] <mikko>	sustrik: i can create custom hook that mails just topic branches
| [Saturday 02 April 2011] [15:13:57] <pieterh>	sustrik: zero actual complaints
| [Saturday 02 April 2011] [15:13:59] <sustrik>	that's why i don't want to be responsible for them
| [Saturday 02 April 2011] [15:14:09] <pieterh>	I'm not going to stress over philosophy
| [Saturday 02 April 2011] [15:14:14] 	 * sustrik can still point to pieterh when something goes terribly wrong
| [Saturday 02 April 2011] [15:14:21] <pieterh>	sure, that's why I'm here
| [Saturday 02 April 2011] [15:14:39] <pieterh>	but I've no patience for another six months of "we can't improve this code because people might be using it"
| [Saturday 02 April 2011] [15:14:43] <mikko>	brb, need to buy milk
| [Saturday 02 April 2011] [15:15:00] <pieterh>	that is bad in a fast-moving project, sorry
| [Saturday 02 April 2011] [15:15:02] <sustrik>	mikko: i think the point is that you don't want *all* the commits to topic branches to go to the mailing list
| [Saturday 02 April 2011] [15:15:08] <sustrik>	just the polished version
| [Saturday 02 April 2011] [15:15:15] 	 * pieterh has to go eat steak, cya tomorrow
| [Saturday 02 April 2011] [15:15:19] <sustrik>	cyl
| [Saturday 02 April 2011] [15:15:51] <pieterh>	sustrik: my confidence in this way of working is based on making FOSS packages for mass consumption since 1996 or so
| [Saturday 02 April 2011] [15:16:30] 	 * pieterh is out of here
| [Saturday 02 April 2011] [15:16:32] <sustrik>	pieterh: ok, what about you becoming maintainer of the whole thing?
| [Saturday 02 April 2011] [15:16:39] <sustrik>	i can work on my private repo
| [Saturday 02 April 2011] [15:16:42] <pieterh>	sustrik: fine by me
| [Saturday 02 April 2011] [15:16:48] <sustrik>	and you can pull whatever you want
| [Saturday 02 April 2011] [15:16:53] <pieterh>	I think *we* as community should be maintainer
| [Saturday 02 April 2011] [15:17:01] <pieterh>	but of processes, rather than code
| [Saturday 02 April 2011] [15:17:11] <pieterh>	I hope you see the distinction
| [Saturday 02 April 2011] [15:17:42] <pieterh>	we define a clear process by which code flows from contributor to user
| [Saturday 02 April 2011] [15:17:43] 	 * sustrik don't follows
| [Saturday 02 April 2011] [15:18:02] <pieterh>	people end up trusting the process
| [Saturday 02 April 2011] [15:18:03] <sustrik>	there have been one and still is one for master
| [Saturday 02 April 2011] [15:18:21] <pieterh>	the process on master doesn't deliver code to users
| [Saturday 02 April 2011] [15:18:34] <sustrik>	that's what i can manage
| [Saturday 02 April 2011] [15:18:43] <sustrik>	i can still hand that responsibility to someone else
| [Saturday 02 April 2011] [15:18:49] <pieterh>	and fwiw, you can make 3.0 compatible with 2.1 in 30 seconds...
| [Saturday 02 April 2011] [15:19:02] <sustrik>	how so?
| [Saturday 02 April 2011] [15:19:09] <pieterh>	how is it not compatible?
| [Saturday 02 April 2011] [15:19:23] <sustrik>	the API and ABI have changed
| [Saturday 02 April 2011] [15:19:41] 	 * pieterh is confused, reading the IRC log
| [Saturday 02 April 2011] [15:20:05] 	 * sustrik is confused
| [Saturday 02 April 2011] [15:20:15] <pieterh>	you said, "I don't want any backward incompatible changes in minor versions"
| [Saturday 02 April 2011] [15:20:22] <pieterh>	implying I'd done that
| [Saturday 02 April 2011] [15:20:27] <sustrik>	ah
| [Saturday 02 April 2011] [15:20:32] <sustrik>	you dropped the devices
| [Saturday 02 April 2011] [15:20:50] <pieterh>	they were not documented, not used, not finished, and not maintained
| [Saturday 02 April 2011] [15:20:59] <sustrik>	well, and?
| [Saturday 02 April 2011] [15:21:20] <pieterh>	further, several attempts to fix them were rejected on the grounds that they were scheduled for removal
| [Saturday 02 April 2011] [15:21:26] <sustrik>	the point of stable is not to break client installations
| [Saturday 02 April 2011] [15:21:30] <pieterh>	I'm not going to ship crap to my users, sorry
| [Saturday 02 April 2011] [15:21:32] <sustrik>	exactly
| [Saturday 02 April 2011] [15:21:42] <sustrik>	thus you keep them till next major version
| [Saturday 02 April 2011] [15:21:46] <sustrik>	then drop them
| [Saturday 02 April 2011] [15:21:56] <pieterh>	What part of "undocumented" isn't clear?
| [Saturday 02 April 2011] [15:22:13] <sustrik>	documentation is just part of compatibility
| [Saturday 02 April 2011] [15:22:16] <pieterh>	this is an example of dangerous prudence
| [Saturday 02 April 2011] [15:22:34] <pieterh>	by assuming people use these in production you actually made it impossible for real device projects to happen
| [Saturday 02 April 2011] [15:22:37] <sustrik>	well, debian package already run to that problem
| [Saturday 02 April 2011] [15:22:55] <pieterh>	undocumented code is not deliverable in my book
| [Saturday 02 April 2011] [15:22:57] <sustrik>	it has to do something when upgrading to 2.1.3
| [Saturday 02 April 2011] [15:22:59] <pieterh>	sorry, I have standards
| [Saturday 02 April 2011] [15:23:24] <sustrik>	anyway, no point in this discussion
| [Saturday 02 April 2011] [15:23:36] <pieterh>	indeed, if you'd documented the devices they would still be there
| [Saturday 02 April 2011] [15:23:55] <pieterh>	if you consider this "breaking the API", I'm just lolling
| [Saturday 02 April 2011] [15:24:12] <sustrik>	that's why i don't to be responsible for the releases you make
| [Saturday 02 April 2011] [15:24:21] <sustrik>	i am simply more prudent than you are
| [Saturday 02 April 2011] [15:24:23] <sustrik>	that's all
| [Saturday 02 April 2011] [15:24:32] <pieterh>	I think this is a fair balance to be honest
| [Saturday 02 April 2011] [15:24:47] <sustrik>	evenry man has his own balance
| [Saturday 02 April 2011] [15:24:49] <pieterh>	it certainly seems to work well
| [Saturday 02 April 2011] [15:24:51] <sustrik>	i am pretty conservative
| [Saturday 02 April 2011] [15:25:05] <pieterh>	I am ultraanarchist
| [Saturday 02 April 2011] [15:25:09] <sustrik>	:)
| [Saturday 02 April 2011] [15:25:29] <pieterh>	philosophical anarchist, to be honest, but who cares
| [Saturday 02 April 2011] [15:25:40] <pieterh>	catch you tomorrow!
| [Saturday 02 April 2011] [15:25:49] <sustrik>	see you
| [Saturday 02 April 2011] [15:42:08] <sustrik>	mikko: still there?
| [Saturday 02 April 2011] [15:42:36] <sustrik>	never mind
| [Saturday 02 April 2011] [15:45:48] <yrashk>	btw what's the timeline for 3.0?
| [Saturday 02 April 2011] [15:45:53] <yrashk>	if any
| [Saturday 02 April 2011] [15:56:25] <sustrik>	yrashk: you mean, when it becomes stable?
| [Saturday 02 April 2011] [15:56:36] <sustrik>	it depends on binding maintainers, i would say
| [Saturday 02 April 2011] [15:57:15] <mikko>	sustrik: here now
| [Saturday 02 April 2011] [15:57:16] <sustrik>	once most bindings are updated to work with 3.0, than it can be reasonable used
| [Saturday 02 April 2011] [15:57:28] <yrashk>	sustrik: I just want to plan erlzmq2 update
| [Saturday 02 April 2011] [15:57:36] <sustrik>	no haste
| [Saturday 02 April 2011] [15:57:38] <yrashk>	like when should I start worrying about 3.0 API compatibility?
| [Saturday 02 April 2011] [15:57:54] <sustrik>	the change is not that big actually
| [Saturday 02 April 2011] [15:58:16] <sustrik>	mostly renaming zmq_send->zmq_sendmsg and zmq_recv->zmq_recvmsg
| [Saturday 02 April 2011] [15:58:38] <sustrik>	and almost all socket option types were changed to int
| [Saturday 02 April 2011] [15:58:50] <sustrik>	mikko: re topic branches
| [Saturday 02 April 2011] [15:59:06] <sustrik>	i would say you want to develop on your repo
| [Saturday 02 April 2011] [15:59:18] <sustrik>	and push to the topic branch once you are ready
| [Saturday 02 April 2011] [15:59:27] <sustrik>	basically asking for review
| [Saturday 02 April 2011] [15:59:30] <sustrik>	right?
| [Saturday 02 April 2011] [16:00:57] <sustrik>	yrashk: i plan to add some goodies to 3.0
| [Saturday 02 April 2011] [16:01:05] <sustrik>	to make incentives for the migration
| [Saturday 02 April 2011] [16:01:13] <yrashk>	good
| [Saturday 02 April 2011] [16:01:15] <sustrik>	so just wait till users start demanding 3.0
| [Saturday 02 April 2011] [16:01:22] <seb`>	subports? :-p
| [Saturday 02 April 2011] [16:01:22] <sustrik>	then update erlzmq
| [Saturday 02 April 2011] [16:01:22] <yrashk>	:)
| [Saturday 02 April 2011] [16:01:27] <sustrik>	exactly
| [Saturday 02 April 2011] [16:01:34] <sustrik>	subports
| [Saturday 02 April 2011] [16:01:59] <yrashk>	what's that?
| [Saturday 02 April 2011] [16:02:23] <sustrik>	zmq_connect ("tcp://192.168.0.111:5555.23");
| [Saturday 02 April 2011] [16:02:36] <sustrik>	you can pass multiple flows via single port
| [Saturday 02 April 2011] [16:02:39] <sustrik>	seb`: i was kind of hesitant about subports
| [Saturday 02 April 2011] [16:02:52] <sustrik>	but i think i got the point
| [Saturday 02 April 2011] [16:03:00] <seb`>	nice:-)
| [Saturday 02 April 2011] [16:03:31] <seb`>	it's very useful in environments where port numbers are a rare commodity
| [Saturday 02 April 2011] [16:03:32] <yrashk>	sweet
| [Saturday 02 April 2011] [16:03:36] <sustrik>	it's about fast deploy cycle, right?
| [Saturday 02 April 2011] [16:03:38] <yrashk>	nice indeed
| [Saturday 02 April 2011] [16:03:44] <yrashk>	any overhead?
| [Saturday 02 April 2011] [16:03:57] <seb`>	it would make firewalling WAY easier
| [Saturday 02 April 2011] [16:04:02] <sustrik>	you just deploy the programs, don't have to worry about assigning ports
| [Saturday 02 April 2011] [16:04:22] <seb`>	yes among other things
| [Saturday 02 April 2011] [16:04:26] <sustrik>	yrashk: no overhead
| [Saturday 02 April 2011] [16:04:47] <yrashk>	niiiiice
| [Saturday 02 April 2011] [16:04:51] <yrashk>	I want it
| [Saturday 02 April 2011] [16:04:57] <sustrik>	the downside is that you can't distinguish the feeds on networking hardware
| [Saturday 02 April 2011] [16:05:04] <seb`>	I'm in a highly firewalled environment. Opening new ports is "complicated"
| [Saturday 02 April 2011] [16:05:08] <sustrik>	so you can't do say feed-based traffic shaping
| [Saturday 02 April 2011] [16:05:15] <sustrik>	but it's a trade-off
| [Saturday 02 April 2011] [16:05:17] <seb`>	sustrik: true
| [Saturday 02 April 2011] [16:05:25] <sustrik>	the user should choose
| [Saturday 02 April 2011] [16:05:29] <yrashk>	still nice for subprotocols or somthing
| [Saturday 02 April 2011] [16:06:05] <sustrik>	seb`: i got it at ietf plenary last week
| [Saturday 02 April 2011] [16:06:39] <sustrik>	the theme was how downloading the client side code have shortened the deployment cycle
| [Saturday 02 April 2011] [16:06:54] <seb`>	I see
| [Saturday 02 April 2011] [16:07:09] <seb`>	how is the ietf stuff going btw? (It must be long and boring)
| [Saturday 02 April 2011] [16:07:24] <sustrik>	tell me
| [Saturday 02 April 2011] [16:07:34] <sustrik>	lasted 6 days
| [Saturday 02 April 2011] [16:07:48] <seb`>	whoah
| [Saturday 02 April 2011] [16:07:53] <sustrik>	my ass is all itching from all the sitting down
| [Saturday 02 April 2011] [16:08:02] <seb`>	haha
| [Saturday 02 April 2011] [16:08:21] <sustrik>	but it's kind of interesting otoh
| [Saturday 02 April 2011] [16:09:10] <sustrik>	so, the point made there was that fast deployment actually beats standardisation
| [Saturday 02 April 2011] [16:09:23] <sustrik>	and i thought:
| [Saturday 02 April 2011] [16:09:51] <sustrik>	we can think of ports assigned as a standard between the parties involved in 0mq communication
| [Saturday 02 April 2011] [16:10:09] <sustrik>	we can deploy new code pretty fast
| [Saturday 02 April 2011] [16:10:21] <sustrik>	but we can't break the "standard" that fast
| [Saturday 02 April 2011] [16:10:31] <sustrik>	thus creating long deployment cycles
| [Saturday 02 April 2011] [16:10:40] <seb`>	got it
| [Saturday 02 April 2011] [16:10:43] <sustrik>	which hurt the agicel business
| [Saturday 02 April 2011] [16:10:46] <sustrik>	agile
| [Saturday 02 April 2011] [16:11:07] <sustrik>	the consequence is, that i want suports in asap
| [Saturday 02 April 2011] [16:11:34] <seb`>	thats good news:-)
| [Saturday 02 April 2011] [16:14:15] <tproa>	subports sound fairly handy. 
| [Saturday 02 April 2011] [16:17:43] <sustrik>	yep, the obvious drawback is that 2 processes on the same machine cannot bind to the same port
| [Saturday 02 April 2011] [16:17:55] <sustrik>	even though they use different subport
| [Saturday 02 April 2011] [16:18:18] <sustrik>	this can be solved in in-kernel implementation though
| [Saturday 02 April 2011] [16:19:53] <yrashk>	it
| [Saturday 02 April 2011] [16:20:11] <yrashk>	it'd be interesting to try out replacing erlang's distribution with zmq-based one
| [Saturday 02 April 2011] [16:20:14] <yrashk>	just for fun
| [Saturday 02 April 2011] [16:20:40] <sustrik>	what's erlang distribution?
| [Saturday 02 April 2011] [16:20:57] <sustrik>	downloading the code?
| [Saturday 02 April 2011] [16:21:55] <yrashk>	nope
| [Saturday 02 April 2011] [16:22:01] <yrashk>	the way it talks between nods
| [Saturday 02 April 2011] [16:22:38] <yrashk>	http://www.erlang.org/doc/apps/erts/alt_dist.html
| [Saturday 02 April 2011] [16:23:19] <yrashk>	the fun thing is that it is replaceable
| [Saturday 02 April 2011] [16:23:33] <sustrik>	aha
| [Saturday 02 April 2011] [16:23:56] <sustrik>	but it has to be a general-purpose messaging i assume
| [Saturday 02 April 2011] [16:24:07] <sustrik>	i.e. "send to an mailbox" semantics
| [Saturday 02 April 2011] [16:25:59] <yrashk>	afair it is much lower level
| [Saturday 02 April 2011] [16:29:33] <yrashk>	so may be one day I'll feel adventurous enough :)
| [Saturday 02 April 2011] [16:29:50] <sustrik>	:)
| [Saturday 02 April 2011] [16:30:07] <yrashk>	it's good it is documented at all
| [Saturday 02 April 2011] [16:30:13] <yrashk>	and documented fairly well
| [Saturday 02 April 2011] [17:10:11] <mikko>	sustrik: possibly
| [Saturday 02 April 2011] [17:10:33] <mikko>	sustrik: i want to push code as often as possible so that there is visibility to my work
| [Saturday 02 April 2011] [17:10:44] <mikko>	and that local hardware failure doesnt cause things to get lost
| [Sunday 03 April 2011] [05:05:19] <pieterh>	sustrik: hi
| [Sunday 03 April 2011] [05:45:11] <sustrik>	hi
| [Sunday 03 April 2011] [05:45:46] <pieterh>	git rename seems to have worked :-)
| [Sunday 03 April 2011] [05:46:51] <sustrik>	yes, looks there are no problems
| [Sunday 03 April 2011] [05:47:33] <sustrik>	well, aside of broken CIA
| [Sunday 03 April 2011] [05:47:40] <sustrik>	i need mato to fix it
| [Sunday 03 April 2011] [05:47:45] <sustrik>	presumably on Tuesday
| [Sunday 03 April 2011] [05:50:22] <sustrik>	btw, are the library version numbering rules outlined somewhere?
| [Sunday 03 April 2011] [05:50:41] 	 * sustrik suspect he should change the library version for 3.0
| [Sunday 03 April 2011] [05:53:14] <pieterh>	afair the original release policies page covered versioning of the library
| [Sunday 03 April 2011] [05:53:31] <sustrik>	thx
| [Sunday 03 April 2011] [05:54:28] <pieterh>	sustrik: sorry, I'm wrong, reading the original text now and it doesn't discuss this
| [Sunday 03 April 2011] [05:54:43] <sustrik>	never mind
| [Sunday 03 April 2011] [05:54:48] <sustrik>	i'll google it
| [Sunday 03 April 2011] [05:55:25] <pieterh>	worth writing down once it's clear...
| [Sunday 03 April 2011] [05:55:45] <sustrik>	maybe just copy it from somewhere
| [Sunday 03 April 2011] [05:55:50] <sustrik>	it's not specific to 0mq
| [Sunday 03 April 2011] [05:55:57] <sustrik>	or link the relevant text
| [Sunday 03 April 2011] [05:56:11] <pieterh>	it's the version of the ABI, right?
| [Sunday 03 April 2011] [05:56:17] <sustrik>	yes
| [Sunday 03 April 2011] [05:56:46] <pieterh>	presumably as long as it's a different number, that's sufficient to allow tools to recognize it
| [Sunday 03 April 2011] [05:56:58] <pieterh>	but there is a justification somewhere that would be useful to link to
| [Sunday 03 April 2011] [06:01:39] <sustrik>	i think there are detailed guidelines somewhere
| [Sunday 03 April 2011] [06:02:01] <sustrik>	it should be done right, as iirc the linker uses it to choose the right library version
| [Sunday 03 April 2011] [06:02:12] <pieterh>	indeed
| [Sunday 03 April 2011] [06:02:47] <pieterh>	mato is the expert in this area, you may want to wait till he gets back
| [Sunday 03 April 2011] [06:03:06] <sustrik>	http://www.usenix.org/publications/library/proceedings/als00/2000papers/papers/full_papers/browndavid/browndavid_html/
| [Sunday 03 April 2011] [06:03:16] <sustrik>	anyway, i'll wait for mato
| [Sunday 03 April 2011] [06:03:23] <sustrik>	just to be sure
| [Sunday 03 April 2011] [06:05:09] <pieterh>	looks right
| [Sunday 03 April 2011] [06:23:25] <mikko>	good morning
| [Sunday 03 April 2011] [06:26:03] <pieterh>	hi mikko
| [Sunday 03 April 2011] [06:28:37] <mikko>	did you merge from 2-2 to 2-1 or both from libzmq?
| [Sunday 03 April 2011] [06:28:52] <pieterh>	mikko: I merged from libzmq into both 2-1 and 2-2
| [Sunday 03 April 2011] [06:29:00] <pieterh>	cherry-picked the various patches
| [Sunday 03 April 2011] [06:29:11] <pieterh>	hmm, sorry, the various commits
| [Sunday 03 April 2011] [06:29:39] <pieterh>	I'm not sure why that sometimes gives a conflict
| [Sunday 03 April 2011] [06:32:12] <mikko>	i can check
| [Sunday 03 April 2011] [06:32:29] <pieterh>	apart from those conflicts, downstreaming seems to work fine
| [Sunday 03 April 2011] [06:34:23] <pieterh>	e.g., cherry-picking bdeddb89f727c434ad499da5a349f3959eba322 from libzmq gave a conflict on acinclude.m4
| [Sunday 03 April 2011] [06:37:30] <mikko>	2.2 still has devices?
| [Sunday 03 April 2011] [06:37:37] <pieterh>	shouldn't have...
| [Sunday 03 April 2011] [06:37:38] <mikko>	and no openpgm build fixes
| [Sunday 03 April 2011] [06:38:09] <mikko>	what i did was:
| [Sunday 03 April 2011] [06:38:17] <mikko>	git remote add 2-1 <url>
| [Sunday 03 April 2011] [06:38:19] <mikko>	git remote add 2-2 <url>
| [Sunday 03 April 2011] [06:38:23] <mikko>	git fetch 2-1 
| [Sunday 03 April 2011] [06:38:24] <mikko>	git fetch 2-2
| [Sunday 03 April 2011] [06:38:32] <mikko>	git diff 2-2/master 2-1/master
| [Sunday 03 April 2011] [06:39:37] 	 * pieterh is checking devices...
| [Sunday 03 April 2011] [06:40:09] <mikko>	2-2 is missing some other commits as well
| [Sunday 03 April 2011] [06:40:42] <mikko>	32ded2b4
| [Sunday 03 April 2011] [06:41:07] <pieterh>	nice catch, let me get 2-2 up to scratch
| [Sunday 03 April 2011] [06:41:17] <mikko>	the diff helps a lot
| [Sunday 03 April 2011] [06:42:10] <pieterh>	for some reason when I tried that it gave diffs that weren't accurate
| [Sunday 03 April 2011] [06:42:23] <pieterh>	didn't do it quite the same way, my git fu is too weak :-(
| [Sunday 03 April 2011] [06:43:45] <pieterh>	mikko: in fact the 32ded2 commit is in 2-2 but not in 2-1 and that's deliberate
| [Sunday 03 April 2011] [06:44:32] <mikko>	ok
| [Sunday 03 April 2011] [06:44:38] <pieterh>	what are the missing openpgm fixes?
| [Sunday 03 April 2011] [06:45:00] <pieterh>	short message abort?
| [Sunday 03 April 2011] [06:45:19] <mikko>	just a sec
| [Sunday 03 April 2011] [06:46:21] <mikko>	ZMQ_MAXMSGSIZE is 2.2 only?
| [Sunday 03 April 2011] [06:46:59] <pieterh>	yes, also
| [Sunday 03 April 2011] [06:47:19] <mikko>	-!foreign/openpgm/Makefile.am
| [Sunday 03 April 2011] [06:47:20] <pieterh>	I see the missing openpgm fixes, 5.1.115 upgrade
| [Sunday 03 April 2011] [06:47:24] <mikko>	2.2 needs that to gitignore
| [Sunday 03 April 2011] [06:47:31] <mikko>	yeah
| [Sunday 03 April 2011] [06:47:37] <mikko>	the devices clutter the diff a bit
| [Sunday 03 April 2011] [06:50:23] <pieterh>	ok, I'm searching around for the correct commits to cherry-pick for openpgm...
| [Sunday 03 April 2011] [06:52:05] <mikko>	have you got gitk?
| [Sunday 03 April 2011] [06:52:16] <pieterh>	gitk sounds fun, what does it do?
| [Sunday 03 April 2011] [06:53:17] <mikko>	it's a repository browser
| [Sunday 03 April 2011] [06:53:29] <mikko>	visualises commit graphs etc
| [Sunday 03 April 2011] [06:53:33] <pieterh>	sigh... why can't I find those OpenPGM commits in libzmq?
| [Sunday 03 April 2011] [06:53:38] <mikko>	fbf1f5146860a2557f247cdb0f94bda647c75ceb on pre30
| [Sunday 03 April 2011] [06:53:57] <mikko>	git show fbf1f5146860a2557f247cdb0f94bda647c75ceb
| [Sunday 03 April 2011] [06:54:36] <mikko>	if you want to see the log on all branches you can do git log --all
| [Sunday 03 April 2011] [06:54:37] <pieterh>	ah, that one
| [Sunday 03 April 2011] [06:55:00] <pieterh>	ok, I see the confusion
| [Sunday 03 April 2011] [06:55:21] <pieterh>	you sent me individual patches, I applied to 2-1, then you sent a single patch to master
| [Sunday 03 April 2011] [06:55:33] <pieterh>	that never got downstreamed again, so I didn't apply it to 2-2
| [Sunday 03 April 2011] [06:56:09] <mikko>	does fbf1f5146860a2557f247cdb0f94bda647c75ceb merge cleanly?
| [Sunday 03 April 2011] [06:56:20] <pieterh>	nope, just tried, got conflicts
| [Sunday 03 April 2011] [06:56:55] <mikko>	did you remove decives?
| [Sunday 03 April 2011] [06:57:02] <pieterh>	should we be using LIBZMQ_ or AC_ZMQ now?
| [Sunday 03 April 2011] [06:57:04] <mikko>	devices*
| [Sunday 03 April 2011] [06:57:05] <pieterh>	yes, I've removed the devices
| [Sunday 03 April 2011] [06:57:17] <mikko>	let me pull and see why it conflicts
| [Sunday 03 April 2011] [06:57:26] <mikko>	ZMQ_ or LIBZMQ_ is fine
| [Sunday 03 April 2011] [06:57:29] <pieterh>	I'll resolve the conflicts, they're not complex
| [Sunday 03 April 2011] [06:57:33] <pieterh>	hang on...
| [Sunday 03 April 2011] [06:57:39] <mikko>	but AC_ZMQ_ ac_zmq_ causes warning
| [Sunday 03 April 2011] [06:57:41] <mikko>	not sure why
| [Sunday 03 April 2011] [06:59:00] 	 * pieterh starts to actively hate git
| [Sunday 03 April 2011] [06:59:16] <pieterh>	having to checkout /reset HEAD three times to undo a failed merge
| [Sunday 03 April 2011] [06:59:41] <mikko>	you can do git merge --no-commit ?
| [Sunday 03 April 2011] [06:59:52] <mikko>	that way you can just stash the changes
| [Sunday 03 April 2011] [07:00:14] <pieterh>	sure, I can go back 30 seconds in time :-) and fix my stupid optimistic command
| [Sunday 03 April 2011] [07:00:42] <mikko>	you learn every time
| [Sunday 03 April 2011] [07:00:53] 	 * pieterh doesn't want to learn... it hurts
| [Sunday 03 April 2011] [07:00:55] <pieterh>	mikko: ok, I've pushed 2-2 without devices
| [Sunday 03 April 2011] [07:01:05] <pieterh>	you're committer on that repo
| [Sunday 03 April 2011] [07:02:30] <pieterh>	if you could merge fbf1f5, that'd be lovely
| [Sunday 03 April 2011] [07:03:02] <mikko>	i shall
| [Sunday 03 April 2011] [07:03:49] <pieterh>	apart from glitches like this it's fairly simple to maintain multiple branches
| [Sunday 03 April 2011] [07:04:18] 	 * pieterh is going to play with gitk
| [Sunday 03 April 2011] [07:13:57] <mikko>	pieterh: builds/msvc/Makefile.am
| [Sunday 03 April 2011] [07:14:01] <mikko>	still has devices in it
| [Sunday 03 April 2011] [07:14:14] <pieterh>	ack, checking...
| [Sunday 03 April 2011] [07:14:24] <mikko>	and the spec-file for rpms has them
| [Sunday 03 April 2011] [07:15:17] <pieterh>	tough little buggers are hard to squash, they get everywhere...
| [Sunday 03 April 2011] [07:15:31] <pieterh>	how do you want to do it?
| [Sunday 03 April 2011] [07:16:25] <pieterh>	I'd take the files from 2-1, where they're correct
| [Sunday 03 April 2011] [07:17:09] <pieterh>	mikko: give me 1 min, I'll do that and push a new 2-2
| [Sunday 03 April 2011] [07:19:31] <pieterh>	ok, done
| [Sunday 03 April 2011] [07:22:07] <mikko>	ok, here goes merge
| [Sunday 03 April 2011] [07:22:55] <mikko>	hmm
| [Sunday 03 April 2011] [07:23:02] <mikko>	heh
| [Sunday 03 April 2011] [07:23:03] <mikko>	ok
| [Sunday 03 April 2011] [07:23:10] <pieterh>	conflicts, right?
| [Sunday 03 April 2011] [07:23:34] <mikko>	nope
| [Sunday 03 April 2011] [07:23:37] <mikko>	small issue
| [Sunday 03 April 2011] [07:23:53] <mikko>	just a sec
| [Sunday 03 April 2011] [07:23:55] 	 * pieterh is in awe of mikko's git fu
| [Sunday 03 April 2011] [07:25:28] <mikko>	https://gist.github.com/d947d4a8f240c85ce194
| [Sunday 03 April 2011] [07:25:34] <mikko>	this needs to go to 2-2 and 2-1
| [Sunday 03 April 2011] [07:25:59] <mikko>	2-2 and 2-1 have both in the configure.in
| [Sunday 03 April 2011] [07:28:18] <pieterh>	error in my conflict resolution?
| [Sunday 03 April 2011] [07:28:41] <mikko>	in the earlier patches
| [Sunday 03 April 2011] [07:28:43] <mikko>	http://build.zero.mq/job/ZeroMQ2-1_GCC-debian/375/console
| [Sunday 03 April 2011] [07:28:46] <mikko>	did you see this?
| [Sunday 03 April 2011] [07:29:29] <pieterh>	didn't see it, presumably the test code hasn't moved to the 3.0 api
| [Sunday 03 April 2011] [07:29:50] <pieterh>	will you fix up acinclude.m4 or shall I do it?
| [Sunday 03 April 2011] [07:30:08] <mikko>	either way
| [Sunday 03 April 2011] [07:30:22] <mikko>	have you got 2-1 and 2-2 in one local repo?
| [Sunday 03 April 2011] [07:30:26] <pieterh>	I'd be happier if you do it, less chance of mistake...
| [Sunday 03 April 2011] [07:30:27] <mikko>	or do you use two repos?
| [Sunday 03 April 2011] [07:30:33] <pieterh>	I use two repos
| [Sunday 03 April 2011] [07:30:39] <pieterh>	two directory trees
| [Sunday 03 April 2011] [07:30:52] <mikko>	ok
| [Sunday 03 April 2011] [07:30:55] <pieterh>	so there's no state to remember, I go there and it's all ready
| [Sunday 03 April 2011] [07:30:58] <mikko>	i just did this:
| [Sunday 03 April 2011] [07:31:05] <mikko>	git branch --track 2-1-master 2-1/master && git branch --track 2-2-master 2-2/master
| [Sunday 03 April 2011] [07:31:24] <mikko>	so now i got two local branches tracking two remote masters
| [Sunday 03 April 2011] [07:31:51] <pieterh>	that's what I figured was possible, so you get the same effect as if it was one repo with two branches
| [Sunday 03 April 2011] [07:32:00] <pieterh>	read/write?
| [Sunday 03 April 2011] [07:32:58] <mikko>	that way when i am in 2-2-master 'git diff' is against 2-2/master
| [Sunday 03 April 2011] [07:33:07] <mikko>	git pull/push etc follow that 
| [Sunday 03 April 2011] [07:33:17] <pieterh>	right
| [Sunday 03 April 2011] [07:36:00] <pieterh>	mikko: I need to do an errand, bbl
| [Sunday 03 April 2011] [07:37:17] <mikko>	ok
| [Sunday 03 April 2011] [07:37:21] <mikko>	i'll push the changes in a min
| [Sunday 03 April 2011] [07:37:31] <pieterh>	excellent!
| [Sunday 03 April 2011] [07:56:56] <mikko>	interesting
| [Sunday 03 April 2011] [08:12:17] <mikko>	pieterh: pushed to 2-2 and 2-1
| [Sunday 03 April 2011] [08:20:49] <pieterh>	mikko: thanks, tested build, it works
| [Sunday 03 April 2011] [08:20:57] <pieterh>	btw I like the new compact makefile output
| [Sunday 03 April 2011] [08:21:38] <pieterh>	aw, inproc_lat.cpp:70: error: zmq_recvmsg was not declared in this scope
| [Sunday 03 April 2011] [08:22:21] <pieterh>	this is what you were saying... I missed it
| [Sunday 03 April 2011] [08:22:30] <pieterh>	one of the downstream patches was bogus
| [Sunday 03 April 2011] [08:24:15] <mikko>	pieterh: cool
| [Sunday 03 April 2011] [08:24:21] <mikko>	that breaks https://build.zero.mq/view/ZeroMQ%202.1/
| [Sunday 03 April 2011] [08:24:21] <pieterh>	:q
| [Sunday 03 April 2011] [08:24:24] <mikko>	all red
| [Sunday 03 April 2011] [08:24:34] 	 * pieterh types vi commands in irc sigh
| [Sunday 03 April 2011] [08:24:36] <mikko>	i'm now adding all the builds that need to be executed
| [Sunday 03 April 2011] [08:24:56] <mikko>	libzmq, zeromq2-2, zeromq2-1, libzapi, libzfl
| [Sunday 03 April 2011] [08:25:18] <mikko>	do we need libzapi builds against libzmq, zeromq2-2 and zeromq2-1 ?
| [Sunday 03 April 2011] [08:25:41] <pieterh>	mikko: I'd say against 2-1 only for now
| [Sunday 03 April 2011] [08:25:52] <pieterh>	eventually against all versions when libzapi handles 3.0
| [Sunday 03 April 2011] [08:26:07] <pieterh>	I need to fix the inproc tests, they're not valid for 2.x
| [Sunday 03 April 2011] [08:28:46] <pieterh>	ok, done
| [Sunday 03 April 2011] [08:28:52] <pieterh>	all builds correctly now
| [Sunday 03 April 2011] [08:41:55] <mikko>	cool
| [Sunday 03 April 2011] [12:24:06] <pieterh>	mikko: what do you think of an --with-valgrind option for configure?
| [Sunday 03 April 2011] [12:26:08] <sustrik>	we should create a valgrind suppression file instead imo
| [Sunday 03 April 2011] [12:26:17] <sustrik>	mato promissed to create one long time ago
| [Sunday 03 April 2011] [12:26:22] <sustrik>	but never actually done it
| [Sunday 03 April 2011] [12:27:33] <pieterh>	I like it
| [Sunday 03 April 2011] [12:27:41] <pieterh>	so no compile changes, automatically works with valgrind
| [Sunday 03 April 2011] [12:27:57] <pieterh>	I'm using valgrind systematically, it's extremely useful
| [Sunday 03 April 2011] [12:29:05] <pieterh>	sustrik: I assume that such a file will have to be completed over time as people use different parts of 0MQ
| [Sunday 03 April 2011] [12:29:13] <pieterh>	I'll try to make one that works for me...
| [Sunday 03 April 2011] [12:29:25] <sustrik>	pieterh: sure
| [Sunday 03 April 2011] [12:29:47] <sustrik>	i don't have experience with suppressions files myself
| [Sunday 03 April 2011] [12:29:59] <sustrik>	http://valgrind.org/docs/manual/manual-core.html#manual-core.suppress
| [Sunday 03 April 2011] [12:30:07] <pieterh>	their docs are... painful :-)
| [Sunday 03 April 2011] [12:30:23] <pieterh>	I'm sure there's a way to turn the error report into a file automatically
| [Sunday 03 April 2011] [12:31:01] <pieterh>	hehe
| [Sunday 03 April 2011] [12:31:04] <pieterh>	--gen-suppressions=all
| [Sunday 03 April 2011] [12:42:19] <mikko>	yeah, valgrind would be nice
| [Sunday 03 April 2011] [12:42:25] <mikko>	some builds might be broken atm
| [Sunday 03 April 2011] [12:42:28] <mikko>	don't worry about that yet
| [Sunday 03 April 2011] [12:42:37] <mikko>	i'm adding more diskspace to the box 
| [Sunday 03 April 2011] [12:42:39] <pieterh>	np :-)
| [Sunday 03 April 2011] [12:42:43] <mikko>	so things might still be in-flight
| [Sunday 03 April 2011] [12:48:42] <pieterh>	sustrik: I have a minimal suppression file that works for all of my examples I've tested so far
| [Sunday 03 April 2011] [12:49:01] <pieterh>	what I'll do is make a wiki page explaining how it works, and how to extend it
| [Sunday 03 April 2011] [12:49:16] <pieterh>	when we have something more complete we can package it up
| [Sunday 03 April 2011] [12:50:19] <sustrik>	ack
| [Sunday 03 April 2011] [13:00:33] <neopallium>	which thread is the zmq_free_fn callback set in zmq_msg_init_data() called from?  I would think it is called from one of the IO threads and that it would need to be thread-safe.
| [Sunday 03 April 2011] [13:00:57] <neopallium>	If that callback needs to be thread-safe, then a note should be added to the man page for zmq_msg_init_data().
| [Sunday 03 April 2011] [13:08:07] <pieterh>	ok, suppression file made, documented, announced
| [Sunday 03 April 2011] [13:08:23] <pieterh>	it's 7 lines of code, at least initially
| [Sunday 03 April 2011] [13:08:41] <pieterh>	neopallium: good catch, you may want to submit a patch to the man page
| [Sunday 03 April 2011] [13:10:56] <sustrik>	pieterh: the link on the valgrind page is broken
| [Sunday 03 April 2011] [13:11:38] <sustrik>	neopallium: it's called from arbitrary thread
| [Sunday 03 April 2011] [13:11:39] <pieterh>	yugh, thanks, you fixing it?
| [Sunday 03 April 2011] [13:11:53] <pieterh>	page is edit locked
| [Sunday 03 April 2011] [13:11:53] <sustrik>	so yes, it has to be thread-safe
| [Sunday 03 April 2011] [13:11:56] <sustrik>	pieterh: no
| [Sunday 03 April 2011] [13:12:01] <sustrik>	force unlock
| [Sunday 03 April 2011] [13:13:19] <pieterh>	sustrik: ok, works now
| [Sunday 03 April 2011] [13:16:24] <neopallium>	How do you edit the manpages?  Do you edit the .txt or .3 file in the libzmq/doc folder?
| [Sunday 03 April 2011] [13:16:34] <pieterh>	neopallium: edit the .txt
| [Sunday 03 April 2011] [13:21:02] <neopallium>	pieterh: How about this: CAUTION: The deallocation function 'ffn' needs to be thread-safe, since it
| [Sunday 03 April 2011] [13:21:03] <neopallium>	will be called from an arbitrary thread.
| [Sunday 03 April 2011] [13:21:53] <pieterh>	sounds fine, maybe Caution rather than CAUTION
| [Sunday 03 April 2011] [13:22:24] <neopallium>	in the .txt file the outher Cautions are all upper-case.
| [Sunday 03 April 2011] [13:22:36] <pieterh>	ah, sure then
| [Sunday 03 April 2011] [13:24:35] <sustrik>	pieterh: just checking old email; haven't you forgot about smalltalk examples?
| [Sunday 03 April 2011] [13:24:44] <sustrik>	the email looks unaswered
| [Sunday 03 April 2011] [13:25:01] <pieterh>	sustrik: hmm, let me check... yup, forgotten
| [Sunday 03 April 2011] [13:25:07] <pieterh>	email is a lousy workflow tool
| [Sunday 03 April 2011] [13:25:14] <sustrik>	use tagging
| [Sunday 03 April 2011] [13:25:27] <pieterh>	use pull requests
| [Sunday 03 April 2011] [13:25:43] <pieterh>	thanks for catching this
| [Sunday 03 April 2011] [13:26:13] <pieterh>	ah, hang on, this email was not aimed at the Guide
| [Sunday 03 April 2011] [13:26:24] <pieterh>	or else I need to explain how to properly translate examples...
| [Sunday 03 April 2011] [13:26:33] <sustrik>	ok
| [Sunday 03 April 2011] [13:28:53] <pieterh>	'sender send: (Random between: 0 and: 100) asString'
| [Sunday 03 April 2011] [13:28:55] <pieterh>	very nice
| [Sunday 03 April 2011] [13:30:15] <neopallium>	pieterh: patch sent to mailing list.
| [Sunday 03 April 2011] [13:30:32] <pieterh>	neopallium: your target is actually sustrik, for patches... :)
| [Sunday 03 April 2011] [13:30:43] <neopallium>	oh
| [Sunday 03 April 2011] [13:30:50] <pieterh>	I just tend to say "submit a patch then" whenever someone has a good idea for an improvement...
| [Sunday 03 April 2011] [13:31:16] <pieterh>	the list is the right place, np
| [Sunday 03 April 2011] [13:32:56] <sustrik>	neopallium: thanks
| [Sunday 03 April 2011] [13:32:58] <neopallium>	The list thread "Zero-copy message API" is what got me thinking about that missing note on thread-safety.
| [Sunday 03 April 2011] [13:33:16] <sustrik>	will apply the patch shortly
| [Sunday 03 April 2011] [13:33:33] <neopallium>	your welcome.
| [Sunday 03 April 2011] [13:43:24] <neopallium>	what is the zeromq-dev@mail.imatix.com mailing list and how do I un-subscribe from it?  I sometimes get duplicate e-mails from it.
| [Sunday 03 April 2011] [13:55:56] <pieterh>	neopallium: there are links in every email, at the footer IMO
| [Sunday 03 April 2011] [13:56:11] <pieterh>	you are perhaps subscribed to two lists, the main one and the announcements list
| [Sunday 03 April 2011] [13:56:21] <pieterh>	or else you are subscribed with two email addresses
| [Sunday 03 April 2011] [14:03:13] <sustrik>	pieterh: no, it happens for me as well
| [Sunday 03 April 2011] [14:04:35] <pieterh>	shrug... email lists are just 0MQ done badly
| [Sunday 03 April 2011] [14:07:01] <sustrik>	neopallium: which email are you looking at?
| [Sunday 03 April 2011] [15:17:28] <neopallium>	pieterh: The last one that I got a dup on is from the "Re: [zeromq-dev] flushing (again)" thread from "Martin Sustrik".  The e-mail's CC: field includes <zeromq-dev@mail.imatix.com>.
| [Sunday 03 April 2011] [15:17:31] <neopallium>	It is like there are two mailing lists.  Maybe an old list that is forwarding to the current zeromq-dev list.
| [Sunday 03 April 2011] [15:17:50] <pieterh>	neopallium: it's because people do "Reply to all" and you're there twice
| [Sunday 03 April 2011] [15:18:00] <pieterh>	most email clients will filter this out
| [Sunday 03 April 2011] [15:18:04] <neopallium>	no not for that e-mail
| [Sunday 03 April 2011] [15:18:28] <pieterh>	I'll do a test, hang on...
| [Sunday 03 April 2011] [15:18:33] <neopallium>	this is the post I am talking about: http://lists.zeromq.org/pipermail/zeromq-dev/2011-April/010280.html
| [Sunday 03 April 2011] [15:19:10] <neopallium>	I will pastebin a copy of the e-mail headers.
| [Sunday 03 April 2011] [15:19:36] 	 * pieterh dropped off, window error...
| [Sunday 03 April 2011] [15:19:53] <pieterh>	neopallium: you will maybe get two emails containing "Nice, thanks. I've updated the 2.1 and 2.2 distribution branches as well."
| [Sunday 03 April 2011] [15:20:48] <neopallium>	yup, but that is not what I am talking about.  I know why I get dups of those types of e-mails.
| [Sunday 03 April 2011] [15:21:14] <pieterh>	sometimes the email list is also repeated as destination
| [Sunday 03 April 2011] [15:21:19] <pieterh>	it'll give the same effect
| [Sunday 03 April 2011] [15:22:03] <pieterh>	there is an explanation which someone familiar with SMTP could provide based on email headers that clients set when they post to the list
| [Sunday 03 April 2011] [15:22:24] <pieterh>	emails from sustrik, and yourself, for example always reply-to the person, whereas emails from other people reply-to the list
| [Sunday 03 April 2011] [15:23:18] <neopallium>	correct e-mail: http://pastebin.com/nU22B940 , dup e-mail: http://pastebin.com/N56DKXhH
| [Sunday 03 April 2011] [15:24:05] <neopallium>	take a look at lines 12 & 13 of both.
| [Sunday 03 April 2011] [15:24:19] <neopallium>	in the dup you have: X-Original-To: zeromq-dev@mail.imatix.com
| [Sunday 03 April 2011] [15:25:05] <pieterh>	so someone is sending emails to the wrong address?
| [Sunday 03 April 2011] [15:25:28] <neopallium>	sometimes people CC zeromq-dev@mail.imatix.com
| [Sunday 03 April 2011] [15:25:39] <pieterh>	they shouldn't, that's an invalid address
| [Sunday 03 April 2011] [15:25:51] <neopallium>	let me try sending a test e-mail to that address.
| [Sunday 03 April 2011] [15:25:56] <pieterh>	well, it's valid, it's the same as the list, but clients won't detect the duplicates then
| [Sunday 03 April 2011] [15:26:07] <pieterh>	don't bother, it's clear what the problem is
| [Sunday 03 April 2011] [15:26:18] <pieterh>	the two addresses resolve to the same list address
| [Sunday 03 April 2011] [15:26:51] <pieterh>	people should not be emailing zeromq-dev@mail.imatix.com, IMO
| [Sunday 03 April 2011] [15:27:05] <neopallium>	some mailservers or mail clients might detect the duplicate message and merge then or reject the dup.
| [Sunday 03 April 2011] [15:27:40] <pieterh>	right, but some won't
| [Sunday 03 April 2011] [15:27:47] <pieterh>	for example I'm not seeing duplicates, at all
| [Sunday 03 April 2011] [15:28:56] <neopallium>	both messages have the same "Message-ID:" header.  That must be why you don't get dups.
| [Sunday 03 April 2011] [15:29:34] <pieterh>	what email client are you using?
| [Sunday 03 April 2011] [15:30:15] <neopallium>	kmail on debian linux.
| [Sunday 03 April 2011] [15:30:37] <pieterh>	file a bug with the kmail folk, they seem to be getting this wrong then
| [Sunday 03 April 2011] [15:31:26] <pieterh>	I have to go tuck the kids into bed, cyal
| [Sunday 03 April 2011] [15:35:53] <mikko>	https://build.zero.mq/job/libzmq_GCC-debian/432/cobertura/_default_/
| [Sunday 03 April 2011] [15:54:09] <mikko>	pieterh: there?
| [Sunday 03 April 2011] [22:28:19] <lestrrat>	I assume jenkins is complaining about the perl binding because of the upcoming 3.0 changes
| [Sunday 03 April 2011] [22:28:31] <lestrrat>	can the tests run against the 2.1.x tree for now?
| [Sunday 03 April 2011] [22:31:50] <mikko>	lestrrat: yeah
| [Sunday 03 April 2011] [22:31:54] <mikko>	been doing a lot of changes lately
| [Sunday 03 April 2011] [22:35:31] <mikko>	building now
| [Monday 04 April 2011] [04:17:47] Notice	-NickServ- travlr_ is not a registered nickname.
| [Monday 04 April 2011] [04:17:50] Notice	-ChanServ- [#qt] Here are the rules for #qt: (1) Don't just join, ask, and quit - stay around and answer questions yourself! (2) Be patient, people may not see your question right away.
| [Monday 04 April 2011] [04:29:05] <mikko-->	sustrik
| [Monday 04 April 2011] [04:29:07] <mikko-->	pieterh
| [Monday 04 April 2011] [04:29:11] <pieter_hintjens1>	hi mikko
| [Monday 04 April 2011] [04:31:19] <mikko-->	pieterh: rpm packaging is broken
| [Monday 04 April 2011] [04:31:23] <mikko-->	device manual pages
| [Monday 04 April 2011] [04:31:29] <mikko-->	http://build.zero.mq/view/RPM%20packaging/
| [Monday 04 April 2011] [04:31:31] <mikko-->	all branches
| [Monday 04 April 2011] [04:31:37] <pieter_hintjens1>	let me take a look
| [Monday 04 April 2011] [04:31:40] <mikko-->	i was up until 4 AM adding / fixing builds
| [Monday 04 April 2011] [04:31:44] <mikko-->	almost everything there
| [Monday 04 April 2011] [04:31:49] <mikko-->	still needs libzfl
| [Monday 04 April 2011] [04:32:05] <pieter_hintjens1>	i saw it... a lot of work!
| [Monday 04 April 2011] [04:36:55] <pieter_hintjens1>	OK, found the error for zmq_device, should build now
| [Monday 04 April 2011] [04:38:05] <pieter_hintjens1>	for master, it's zmq_cpp, I assume that's been removed from the tree but not the zeromq.spec file
| [Monday 04 April 2011] [04:40:34] <mikko-->	it's the device manual page
| [Monday 04 April 2011] [04:40:42] <mikko-->	that causes the packaging error for 2-2 and 2-1
| [Monday 04 April 2011] [04:40:49] <pieter_hintjens1>	I've fixed that, mikko
| [Monday 04 April 2011] [04:40:56] <mikko-->	cool
| [Monday 04 April 2011] [04:41:10] <pieter_hintjens1>	there's still a problem with master, due to a reference to the zmq_cpp man page
| [Monday 04 April 2011] [04:41:42] <pieter_hintjens1>	I think at some point we should consider generating these files automatically
| [Monday 04 April 2011] [04:42:01] <pieter_hintjens1>	the current approach breaks every time anything is added or removed
| [Monday 04 April 2011] [04:42:06] <sustrik__>	fixing it
| [Monday 04 April 2011] [04:42:08] <sustrik__>	a second
| [Monday 04 April 2011] [04:42:53] <sustrik__>	btw: source line is wrong
| [Monday 04 April 2011] [04:43:02] <sustrik__>	Source:        http://www.zeromq.org/local--files/area:download/%{name}-%{version}.tar.gz
| [Monday 04 April 2011] [04:43:24] <pieter_hintjens1>	hmm, indeed
| [Monday 04 April 2011] [04:43:31] <mikko-->	sustrik: https://build.zero.mq/view/libzmq/job/libzmq_GCC-debian/440/cppcheckResult/source.20/?
| [Monday 04 April 2011] [04:43:37] <mikko-->	see the highlighted line
| [Monday 04 April 2011] [04:44:16] <sustrik__>	mikko: "The page isn't redirecting properly"
| [Monday 04 April 2011] [04:44:51] <mikko-->	oh, indeed
| [Monday 04 April 2011] [04:45:03] <mikko-->	hmm, i wonder what happened to permissions there
| [Monday 04 April 2011] [04:45:04] <mikko-->	sec
| [Monday 04 April 2011] [04:45:58] <mikko-->	brbr
| [Monday 04 April 2011] [04:46:02] <sustrik__>	this should be probably changed as well:
| [Monday 04 April 2011] [04:46:02] <sustrik__>	Name:          zeromq
| [Monday 04 April 2011] [04:46:06] <sustrik__>	should be libzmq
| [Monday 04 April 2011] [04:46:42] <sustrik__>	otherwise the "source" line won't expand properly
| [Monday 04 April 2011] [04:47:07] <pieter_hintjens1>	sustrik__: the source line isn't going to be accurate anyhow
| [Monday 04 April 2011] [04:48:00] <sustrik__>	2 issues
| [Monday 04 April 2011] [04:48:03] <sustrik__>	the name
| [Monday 04 April 2011] [04:48:05] <sustrik__>	the path
| [Monday 04 April 2011] [04:48:17] <sustrik__>	should i try to fix it?
| [Monday 04 April 2011] [04:48:26] <sustrik__>	i have no idea how rpm packaging works :|
| [Monday 04 April 2011] [04:48:46] <pieter_hintjens1>	presumably it's a comment rather than functional
| [Monday 04 April 2011] [04:48:53] <pieter_hintjens1>	because it's been wrong for some time
| [Monday 04 April 2011] [04:49:48] <pieter_hintjens1>	I'd suggest leaving the package name as zeromq, and fixing the URI to download.zeromq.org
| [Monday 04 April 2011] [04:49:53] <pieter_hintjens1>	that is at least accurate
| [Monday 04 April 2011] [04:50:08] <pieter_hintjens1>	http://download.zeromq.org/%{name}-%{version}.tar.gz
| [Monday 04 April 2011] [04:56:55] <mikko-->	sustrik:
| [Monday 04 April 2011] [04:56:57] <mikko-->	http://build.zero.mq/view/libzmq/job/libzmq_GCC-debian/440/cppcheckResult/source.20/?
| [Monday 04 April 2011] [04:57:01] <mikko-->	should load now
| [Monday 04 April 2011] [05:17:36] <mikko_k>	sustrik: did you get it?
| [Monday 04 April 2011] [05:34:40] <sustrik__>	mikko_k: yes
| [Monday 04 April 2011] [05:34:48] <sustrik__>	what problem does it report?
| [Monday 04 April 2011] [05:35:36] <sustrik__>	unnecessary cast?
| [Monday 04 April 2011] [05:36:27] <mikko_k>	unused variable
| [Monday 04 April 2011] [05:36:59] <sustrik__>	ok, let me fix it
| [Monday 04 April 2011] [05:37:04] <sustrik__>	what about the rpm stuff?
| [Monday 04 April 2011] [05:37:12] <sustrik__>	do you have any idea how it works?
| [Monday 04 April 2011] [05:37:14] <mikko_k>	yeah
| [Monday 04 April 2011] [05:37:52] <sustrik__>	%{name} -- what does it resolves to?
| [Monday 04 April 2011] [05:38:26] <mikko_k>	Name:
| [Monday 04 April 2011] [05:38:45] <sustrik__>	aha
| [Monday 04 April 2011] [05:38:53] <sustrik__>	thus we have to change Name: to libzmq
| [Monday 04 April 2011] [05:39:01] <sustrik__>	or hard-wite libzmq into the source path
| [Monday 04 April 2011] [05:39:52] <mikko_k>	you don't have to use %{name}
| [Monday 04 April 2011] [05:39:59] <mikko_k>	it just seems to be a common convention
| [Monday 04 April 2011] [05:40:23] <sustrik__>	what is the name used for?
| [Monday 04 April 2011] [05:40:27] <mikko_k>	usually you see %{name}-%{version}.tar.gz 
| [Monday 04 April 2011] [05:40:29] <sustrik__>	tracking identity of tha package?
| [Monday 04 April 2011] [05:40:52] <sustrik__>	if so, we have to keep zeromq as name
| [Monday 04 April 2011] [05:40:54] <mikko_k>	sustrik__: i guess it's just a convention
| [Monday 04 April 2011] [05:40:59] <mikko_k>	you can hardcode it as well
| [Monday 04 April 2011] [05:41:17] <pieter_hintjens1>	like I said, the package name will have to remain zeromq
| [Monday 04 April 2011] [05:41:17] <sustrik__>	i mean, if the guys at RH/CentOS are using name
| [Monday 04 April 2011] [05:41:28] <sustrik__>	to say "this is the same package, just a newer version"
| [Monday 04 April 2011] [05:41:36] <mikko_k>	yeah
| [Monday 04 April 2011] [05:41:38] <mikko_k>	makes sense
| [Monday 04 April 2011] [05:41:38] <pieter_hintjens1>	unless we make separate distributions for the core library and the package
| [Monday 04 April 2011] [05:41:56] <sustrik__>	ok, let me hardwire the path then
| [Monday 04 April 2011] [05:48:31] <sustrik__>	hm, are we going to keep the name of the dist "zeromq"
| [Monday 04 April 2011] [05:48:40] <sustrik__>	or are we going to change it to libzmq?
| [Monday 04 April 2011] [05:49:00] <pieter_hintjens1>	sustrik__: for the third time... :-) we have to keep the name of the dist as "zeromq"
| [Monday 04 April 2011] [05:49:16] <pieter_hintjens1>	unless we also (which we can do) create a package specifically and only for libzmq
| [Monday 04 April 2011] [05:49:33] <sustrik__>	the dist is only libzmq
| [Monday 04 April 2011] [05:49:42] <sustrik__>	i mean
| [Monday 04 April 2011] [05:49:49] <sustrik__>	what you get when you type "make dist"
| [Monday 04 April 2011] [05:50:13] <pieter_hintjens1>	then you can use package = libzmq in master, for sure
| [Monday 04 April 2011] [05:50:20] <pieter_hintjens1>	in the dist branches it's zeromq
| [Monday 04 April 2011] [05:50:39] <sustrik__>	ok
| [Monday 04 April 2011] [05:50:47] <pieter_hintjens1>	however unless you're uploading those .tag.gz files somewhere, they're not on any download URI
| [Monday 04 April 2011] [05:50:53] <Guthur>	still naming discussions I see, hehe
| [Monday 04 April 2011] [05:51:10] <pieter_hintjens1>	Guthur: well, the naming is just settling into place afaics
| [Monday 04 April 2011] [05:51:45] <Guthur>	cool, I've been out of the loop somewhat, being in Hamburg 
| [Monday 04 April 2011] [05:51:49] <pieter_hintjens1>	sustrik__: in any case if we start including other projects into the zeromq dist the redhat packaging will change
| [Monday 04 April 2011] [05:51:58] <sustrik__>	BuildRequires: glib2-devel
| [Monday 04 April 2011] [05:52:11] <sustrik__>	the rpm file looks completely out-of-date
| [Monday 04 April 2011] [05:52:16] <pieter_hintjens1>	Guthur: I've heard that Internet is coming to Hamburg in 2015...
| [Monday 04 April 2011] [05:52:58] <Guthur>	pieter_hintjens1: yeah the sooner the better, getting a wifi connection was more challenging than I expected
| [Monday 04 April 2011] [05:53:02] <sustrik__>	why so?
| [Monday 04 April 2011] [05:53:22] <sustrik__>	with packaging for distros you want to have individual project be different packages
| [Monday 04 April 2011] [05:53:27] <Guthur>	well there was one at the conference but the only other one I really got was at a starbucks
| [Monday 04 April 2011] [05:53:34] <sustrik__>	so that it works ok with package managers
| [Monday 04 April 2011] [05:53:48] <pieterh>	sustrik__: you're probably right
| [Monday 04 April 2011] [05:54:14] 	 * sustrik__ has no packaging experience whatsoever :|
| [Monday 04 April 2011] [05:54:22] <pieterh>	but I'm not sure we *don't* want a ZeroMQ distro that includes everything sane
| [Monday 04 April 2011] [05:55:23] <sustrik__>	definitely on win32
| [Monday 04 April 2011] [05:55:32] <sustrik__>	no idea about deifferent UX-es
| [Monday 04 April 2011] [05:55:43] <pieterh>	well, openpgm is a good example
| [Monday 04 April 2011] [05:55:43] 	 * so_solid_moo is a fedora developer if you have any questions about that specifically :)
| [Monday 04 April 2011] [05:55:57] <pieterh>	do you want to have to go build it separately?
| [Monday 04 April 2011] [05:56:29] <sustrik__>	the distros are pretty clear about not wanting bundled libs
| [Monday 04 April 2011] [05:56:40] <pieterh>	yes, but that's not really our problem here
| [Monday 04 April 2011] [05:56:45] <pieterh>	this is not about libzmq in a distro
| [Monday 04 April 2011] [05:56:49] <sustrik__>	that's why mikko did the separate compile work last week
| [Monday 04 April 2011] [05:56:58] <sustrik__>	rpm?
| [Monday 04 April 2011] [05:57:02] <pieterh>	it's about making our own packages (this RPM stuff is not RHEL)
| [Monday 04 April 2011] [05:57:28] <sustrik__>	well, the script is in directory called "redhat" :)
| [Monday 04 April 2011] [05:57:28] <pieterh>	it's about making RPMs that can be used to install 0MQ on boxes
| [Monday 04 April 2011] [05:57:40] <mikko_k>	i can provide unofficial yum repository later
| [Monday 04 April 2011] [05:57:49] <mikko_k>	now that there is 64bit build capacity
| [Monday 04 April 2011] [05:58:07] <sustrik__>	mikko: what do you thing of the glib dep in the rpm?
| [Monday 04 April 2011] [05:58:31] <pieterh>	sustrik__: it's clearly out of date but should we be maintaining the rpm spec?
| [Monday 04 April 2011] [05:58:39] <pieterh>	there's an author
| [Monday 04 April 2011] [05:58:50] <sustrik__>	mikko?
| [Monday 04 April 2011] [06:03:24] <sustrik__>	mikko_k: are you there?
| [Monday 04 April 2011] [06:03:36] <sustrik__>	what do you thing of the glib dep in the rpm?
| [Monday 04 April 2011] [06:04:16] <pieterh>	sustrik__: that's a hangover from OpenPGM, isn't it?
| [Monday 04 April 2011] [06:04:24] <sustrik__>	looks like
| [Monday 04 April 2011] [06:04:35] <pieterh>	do we really want to be maintaining this file though?
| [Monday 04 April 2011] [06:04:46] <sustrik__>	where else should it go?
| [Monday 04 April 2011] [06:05:02] <pieterh>	my question is whether we (you, me, Mikko) should be editing and fixing this spec file
| [Monday 04 April 2011] [06:05:20] <pieterh>	there's an author who wrote it, and people who use it (probably the same person)
| [Monday 04 April 2011] [06:05:33] <sustrik__>	mikko is listed as an author
| [Monday 04 April 2011] [06:06:32] <pieterh>	ok, git blame confirms it
| [Monday 04 April 2011] [06:06:49] <mikko_k>	i can edit it
| [Monday 04 April 2011] [06:06:55] <mikko_k>	when i get home
| [Monday 04 April 2011] [06:07:24] <sustrik__>	it's up to you
| [Monday 04 April 2011] [06:07:30] <sustrik__>	you are the build system maintainer
| [Monday 04 April 2011] [06:07:37] <sustrik__>	if you want it there, there is stays
| [Monday 04 April 2011] [06:07:50] <sustrik__>	if you want to remove it, do so
| [Monday 04 April 2011] [06:08:13] <mikko_k>	glib dependency should go afaik
| [Monday 04 April 2011] [06:08:58] <sustrik__>	do you want me to fix it?
| [Monday 04 April 2011] [06:09:08] <sustrik__>	or would you check it yourself later on?
| [Monday 04 April 2011] [06:09:34] <mikko_k>	two things at least:
| [Monday 04 April 2011] [06:09:50] <mikko_k>	well, i can do it tonight
| [Monday 04 April 2011] [06:09:59] <mikko_k>	i'll add option to use system openpgm to spec files
| [Monday 04 April 2011] [06:10:13] <mikko_k>	so that in future RHEL/etc can easily package the two separately
| [Monday 04 April 2011] [06:10:23] <mikko_k>	possibly package openpgm 5.1.115 as RPM as well
| [Monday 04 April 2011] [06:10:30] <mikko_k>	and provide a yum repository for these
| [Monday 04 April 2011] [06:10:30] <sustrik__>	ok
| [Monday 04 April 2011] [06:10:41] <sustrik__>	if you want a help just ask
| [Monday 04 April 2011] [06:11:16] <mikko_k>	do we have zeromq GPG key?
| [Monday 04 April 2011] [06:11:21] <mikko_k>	that i can use to sign the packages
| [Monday 04 April 2011] [06:11:26] <mikko_k>	or should i create one?
| [Monday 04 April 2011] [06:12:31] <sustrik__>	hm, mato would be right person to answer that
| [Monday 04 April 2011] [06:12:38] <sustrik__>	he's out of town today though
| [Monday 04 April 2011] [06:35:46] <mikko_k>	sustrik: https://build.zero.mq/view/libzmq/job/libzmq_mingw32-debian/281/console
| [Monday 04 April 2011] [06:36:31] <pieterh>	mikko_k: as far as I know we don't have a ZeroMQ GPG key
| [Monday 04 April 2011] [06:36:47] <pieterh>	and you should create one IMO
| [Monday 04 April 2011] [06:41:49] <sustrik__>	mato is doing debian packaging
| [Monday 04 April 2011] [06:41:53] <sustrik__>	he may have one
| [Monday 04 April 2011] [06:43:10] <pieterh>	I'd assume if he did anything in the name of the 0MQ community he'd share it
| [Monday 04 April 2011] [06:44:04] <sustrik__>	isn't the key confidential?
| [Monday 04 April 2011] [06:44:12] <pieterh>	its existence shouldn't be
| [Monday 04 April 2011] [06:44:16] 	 * sustrik__ has no idea about security
| [Monday 04 April 2011] [06:44:45] <pieterh>	given that you and myself are the benevolent dictators here, we should have all the keys
| [Monday 04 April 2011] [06:45:15] <pieterh>	that is how we have worked since the start, it's a good principle
| [Monday 04 April 2011] [06:46:01] <pieterh>	I assume mato would by default work like that, and since he's not shared any keys, I assume they don't exist
| [Monday 04 April 2011] [06:46:44] <sustrik__>	if it's used for signing official debian distro, it does exist
| [Monday 04 April 2011] [06:46:48] <sustrik__>	wait till tomorrow
| [Monday 04 April 2011] [06:47:04] <pieterh>	of course
| [Monday 04 April 2011] [06:47:11] <mikko_k>	sustrik: did you see the new error ?
| [Monday 04 April 2011] [06:48:20] <sustrik__>	yes, fixing it
| [Monday 04 April 2011] [06:48:23] <sustrik__>	wait a sec
| [Monday 04 April 2011] [06:51:02] <mikko_k>	cool, thanks
| [Monday 04 April 2011] [06:51:41] <sustrik__>	mikko_k: ok, done
| [Monday 04 April 2011] [07:03:31] <ianbarber>	sustrik__: mato was saying that he didn't actually adding the debian packages directly as he wasn't a debian dev, so the packages may be signed by the repo
| [Monday 04 April 2011] [07:04:23] <sustrik__>	aha
| [Monday 04 April 2011] [07:04:34] <sustrik__>	then we presumably have no key
| [Monday 04 April 2011] [07:04:57] <sustrik__>	mikko: feel free to generate one
| [Monday 04 April 2011] [07:05:27] <pieterh>	sustrik__: you sure you don't want to wait a day and ask Mato?
| [Monday 04 April 2011] [07:05:45] <sustrik__>	well, if he's not signing the packages
| [Monday 04 April 2011] [07:06:05] <mikko_k>	sustrik: http://build.zero.mq/view/libzmq/job/libzmq_mingw32-debian/283/consoleText 
| [Monday 04 April 2011] [07:06:10] <mikko_k>	lunch!
| [Monday 04 April 2011] [07:06:44] <sustrik__>	anyway, no haste, we can discuss the key matter tomorrow
| [Monday 04 April 2011] [07:06:53] <sustrik__>	mikko_k: thx, giving it a look
| [Monday 04 April 2011] [07:10:01] <ianbarber>	sustrik__: thanks for the reply to my router idea by the way, good point about the two distinctions. I hadn't thought about the stateful service situation much, but it is a different and tricky problem. 
| [Monday 04 April 2011] [07:13:23] <sustrik__>	ianbarber: yes, that's why Erlang doesn't allow for any local state
| [Monday 04 April 2011] [07:13:46] <sustrik__>	no state => scalability & transpatrent failover
| [Monday 04 April 2011] [07:13:51] <sustrik__>	state => ?
| [Monday 04 April 2011] [07:13:52] <ianbarber>	yeah
| [Monday 04 April 2011] [07:21:25] <sustrik__>	mikko: fixed
| [Monday 04 April 2011] [07:45:51] <mikko_k>	pieterh: http://build.zero.mq/job/libzapi-master_libzmq_mingw32-debian/2/consoleText
| [Monday 04 April 2011] [09:47:56] <pieterh>	mikko_k: fixed, should build on Win32 now but I've not had time to try that yet
| [Monday 04 April 2011] [09:49:26] <pieterh>	sustrik__: did you say you could, or could not, make it to Brussels for the 10th?
| [Monday 04 April 2011] [10:04:52] Notice	-NickServ- travlr__ is not a registered nickname.
| [Monday 04 April 2011] [10:04:55] Notice	-ChanServ- [#qt] Here are the rules for #qt: (1) Don't just join, ask, and quit - stay around and answer questions yourself! (2) Be patient, people may not see your question right away.
| [Monday 04 April 2011] [10:23:38] <saurabhd>	hi...i have problem related to zmq_device..
| [Monday 04 April 2011] [10:23:44] <saurabhd>	anyone can help out?
| [Monday 04 April 2011] [10:53:00] <boothead>	hi guys, i would like to close a socket with one unsent message in the buffer and then open another socket to the same endpoint as the first - would ZMQ_LINGER let me chuck the unsent messages?
| [Monday 04 April 2011] [10:55:00] <sustrik__>	boothead: set linger to zero
| [Monday 04 April 2011] [10:55:11] <sustrik__>	pieterh: no, i won't be able to come
| [Monday 04 April 2011] [10:56:45] <boothead>	sustrik__, thanks, I will try that.
| [Monday 04 April 2011] [10:59:33] <boothead>	does it matter if i set linger before or after connecting (like identity?)
| [Monday 04 April 2011] [10:59:53] <sustrik__>	it does not matter
| [Monday 04 April 2011] [11:02:47] <boothead>	thanks sustrik__ works perfectly :-)
| [Monday 04 April 2011] [12:00:10] <pieterh>	sustrik__: I'm going to cancel it then, not much point
| [Monday 04 April 2011] [12:12:28] <ianbarber>	sustrik__: is your moscow talk going to a) be videoed b) in english? 
| [Monday 04 April 2011] [12:25:20] <pieterh>	sustrik__: I can look for another date in May, it was already mostly full
| [Monday 04 April 2011] [12:31:32] <ianbarber>	i am still waiting to find out whether i am OK for that date from work, end of the financial year = bottom of the priority pile i suspect :)
| [Monday 04 April 2011] [13:58:00] <eyeris>	If I create a push/pull pair with an explicit identity on each side, does the durability (which I assume is journaled) allow the two sides to operate in a disconnected state? (total noob here, just reading the guide)
| [Monday 04 April 2011] [13:58:53] <michaelgreene_>	I'm in the process of converting a system I'm using from 2.0.11 to 2.1.4 and have a few hundred automated tests that run a pyzmq test harness against my system that is implemented using the low-level C API.  All the tests seem to pass still, but I see "Invalid argument (mutex.hpp:98)" printed while tearing down each test. Any ideas what this is actually telling me? It looks like that line is just a lock acquire.
| [Monday 04 April 2011] [13:59:08] <pieterh>	eyeris: nope
| [Monday 04 April 2011] [13:59:30] <pieterh>	the durability is not reliable, it just creates a kind of persistent network buffer
| [Monday 04 April 2011] [14:00:11] <pieterh>	michaelgreene_: sounds like code is using a closed socket or somesuch
| [Monday 04 April 2011] [14:00:16] <eyeris>	pieterh: OK, thanks.
| [Monday 04 April 2011] [14:00:41] <pieterh>	eyeris: if you want disconnected clients / workers, check out the Majordomo pattern in Ch4
| [Monday 04 April 2011] [14:00:55] <pieterh>	hmm, sorry, the Titanic pattern :-)
| [Monday 04 April 2011] [14:11:46] <Guthur>	what would be the major wins for zeromq if it reaches the kernel, low latency?
| [Monday 04 April 2011] [14:12:19] <pieterh>	Guthur: accessibility to any application that uses normal sockets, in theory
| [Monday 04 April 2011] [14:15:26] <Guthur>	pieterh, is that what you see as  the biggest win?
| [Monday 04 April 2011] [14:16:22] <Guthur>	which reminds me, one of the common questions I got asked at the ELS, was 'why should I use zeromq sockets over plain TCP'
| [Monday 04 April 2011] [14:19:59] <pieterh>	Guthur: you'd have to ask sustrik, kernelification is his vision
| [Monday 04 April 2011] [14:20:30] <pieterh>	why use zeromq sockets over plain TCP... turns 2,000 lines of code into 20, that's all
| [Monday 04 April 2011] [14:21:36] <pieterh>	it's pretty exhaustively explained in the Guide, all the difficulties you have to solve if you use TCP sockets
| [Monday 04 April 2011] [14:22:35] <Guthur>	yeah, it was an easy one to answer to be fair
| [Monday 04 April 2011] [14:34:52] <sustrik__>	pieterh: it's more about money, i extremely short of it atm, so i am not sure i can actually afford going to bxl now
| [Monday 04 April 2011] [14:35:07] <sustrik__>	i you are willing to reschedule though
| [Monday 04 April 2011] [14:35:28] <sustrik__>	it would be nice to move it to later on
| [Monday 04 April 2011] [14:35:34] <sustrik__>	prepare a real program
| [Monday 04 April 2011] [14:35:46] <pieterh>	unconfs don't really have programs, that's the point
| [Monday 04 April 2011] [14:35:58] <sustrik__>	why would anyone come then?
| [Monday 04 April 2011] [14:36:05] <pieterh>	to meet other people
| [Monday 04 April 2011] [14:36:15] <pieterh>	iot
| [Monday 04 April 2011] [14:36:23] <pieterh>	it's basically an extended meetup
| [Monday 04 April 2011] [14:36:47] <sustrik__>	then pair it with some other conference or something
| [Monday 04 April 2011] [14:37:04] <pieterh>	why? you don't think it's worth meeting people just for 0MQ?
| [Monday 04 April 2011] [14:37:05] <sustrik__>	it's unlikely that many people will travel to bxl just to have a beer
| [Monday 04 April 2011] [14:37:10] <pieterh>	sigh
| [Monday 04 April 2011] [14:37:18] <sustrik__>	it's expensive
| [Monday 04 April 2011] [14:37:26] <pieterh>	well, I'm happy to travel to London just to meet 0MQ folk
| [Monday 04 April 2011] [14:37:36] <sustrik__>	that's you
| [Monday 04 April 2011] [14:37:45] <sustrik__>	and london is quite close to bxl
| [Monday 04 April 2011] [14:38:40] <sustrik__>	ianbarber: no idea about video
| [Monday 04 April 2011] [14:38:51] <sustrik__>	i'll speak in english
| [Monday 04 April 2011] [14:39:11] <sustrik__>	not much help if it's not recorded though :)
| [Monday 04 April 2011] [14:39:23] <ianbarber>	cool :) well, if you have slides they would be great to see
| [Monday 04 April 2011] [14:39:32] <ianbarber>	 on slideshare or something
| [Monday 04 April 2011] [14:39:49] <sustrik__>	definitely
| [Monday 04 April 2011] [14:39:56] <ianbarber>	sustrik__: unconfs are quite fun, people do go to them as well - the idea is that people talk, but the schedule isn't decided up front
| [Monday 04 April 2011] [14:40:40] <pieterh>	look, Brussels is central, easy to get to
| [Monday 04 April 2011] [14:41:00] <pieterh>	but I'm not really stressed to make a conference now
| [Monday 04 April 2011] [14:41:19] <sustrik__>	sure, if there's an interest why not
| [Monday 04 April 2011] [14:41:19] <pieterh>	it'd be good for 0MQ, good to spread the word
| [Monday 04 April 2011] [14:41:56] <Guthur>	+1 on unconf being pretty good
| [Monday 04 April 2011] [14:42:15] <Guthur>	I'm been to one before, local mind you, and I thought it was very successful
| [Monday 04 April 2011] [14:42:50] <ianbarber>	i wonder if it would be an idea to have a brusels 0MQ meetup this month? just to gauge the local scene as well
| [Monday 04 April 2011] [14:43:35] <sustrik__>	that's what pieter is organising
| [Monday 04 April 2011] [14:43:39] <Guthur>	you made cannibalism the unconf a bit, considering it's so close
| [Monday 04 April 2011] [14:43:58] <Guthur>	cannibalize*
| [Monday 04 April 2011] [14:44:03] <sustrik__>	ah
| [Monday 04 April 2011] [14:44:10] 	 * sustrik__ misunderstood
| [Monday 04 April 2011] [14:45:45] <pieterh>	it's not sensible to try to make a conventional conference, we'd not get speakers
| [Monday 04 April 2011] [14:45:45] <pieterh>	nor is it sensible to try to mix with another conference, not in Brussels
| [Monday 04 April 2011] [14:45:45] <pieterh>	unless you are passionate about EU farming subsidy discussions
| [Monday 04 April 2011] [14:45:46] <pieterh>	sure, why not
| [Monday 04 April 2011] [14:45:46] <pieterh>	I've always enjoyed the unconf model
| [Monday 04 April 2011] [14:45:46] 	 * pieterh has also organized large classic conferences
| [Monday 04 April 2011] [14:45:46] <pieterh>	they are extraordinarily hard work and expensive, since speakers expect to have their costs paid
| [Monday 04 April 2011] [14:47:10] <Guthur>	i thought that's why conferences usually charge
| [Monday 04 April 2011] [14:47:24] <ianbarber>	and sponsored
| [Monday 04 April 2011] [14:47:26] <pieterh>	indeed
| [Monday 04 April 2011] [14:47:30] <pieterh>	which is a lot of work
| [Monday 04 April 2011] [14:47:51] <ianbarber>	yeah, a traditional conference is serious effort
| [Monday 04 April 2011] [14:48:04] <pieterh>	when I organized 2-day conferences against software patents, it took 2-3 months *full time* per conference
| [Monday 04 April 2011] [14:48:40] <sustrik__>	yuck
| [Monday 04 April 2011] [14:48:45] <pieterh>	you can do it in 2 weeks with a team of 10 people
| [Monday 04 April 2011] [14:48:57] <pieterh>	thus, an unconf is much cooler
| [Monday 04 April 2011] [14:49:08] <pieterh>	you just need a good location, and a good subject
| [Monday 04 April 2011] [14:49:37] <ianbarber>	unconference is still a fair bit of work, particularly in convincing people to go. I think it would be easier to get people to go the more experts there are though, particularly pieterh sustrik__ and mato, but as many contributors as possible really. 
| [Monday 04 April 2011] [14:49:53] <Guthur>	+1 that
| [Monday 04 April 2011] [14:49:55] <pieterh>	ianbarber: indeed, it usually takes 2-3 events for the notion to take off
| [Monday 04 April 2011] [14:50:05] <pieterh>	I'd expect a fairly quite first unconf
| [Monday 04 April 2011] [14:50:24] <pieterh>	but the point is that without starting, you can't build it up
| [Monday 04 April 2011] [14:50:37] <Guthur>	The thing that puts me in two minds about this unconf is that there is little visibility of that expert driven content
| [Monday 04 April 2011] [14:50:47] <pieterh>	sustrik__: do you remember the first AMQP conference?
| [Monday 04 April 2011] [14:50:54] <sustrik__>	which one was that?
| [Monday 04 April 2011] [14:51:01] <pieterh>	don't know if you were there, in London
| [Monday 04 April 2011] [14:51:09] <pieterh>	the one with three people in the audience
| [Monday 04 April 2011] [14:51:10] <sustrik__>	don't think so
| [Monday 04 April 2011] [14:51:23] <sustrik__>	i remember the one when you got those business types into your loft :)
| [Monday 04 April 2011] [14:51:36] <sustrik__>	ah, the qcon
| [Monday 04 April 2011] [14:51:39] <sustrik__>	i think
| [Monday 04 April 2011] [14:51:43] <sustrik__>	heard about it
| [Monday 04 April 2011] [14:51:43] <pieterh>	sustrik__: agh, flashbacks... yes, the qcon one
| [Monday 04 April 2011] [14:51:54] <Guthur>	hehe, a pile of suits in a loft
| [Monday 04 April 2011] [14:51:55] <pieterh>	Guthur: we could post some topics for discussion on the wiki page
| [Monday 04 April 2011] [14:51:59] <Guthur>	a pretty picture
| [Monday 04 April 2011] [14:52:35] <Guthur>	pieterh, that would beneficial I think
| [Monday 04 April 2011] [14:53:17] <Guthur>	would help me sell it to myself at least, hehe
| [Monday 04 April 2011] [14:53:23] <pieterh>	but it's basically up to attendees to be prepared to present stuff
| [Monday 04 April 2011] [14:53:27] <pieterh>	well, I can post stuff I'd talk about but that's it
| [Monday 04 April 2011] [14:53:29] 	 * pieterh has to go tuck the kids into bed, bb rs
| [Monday 04 April 2011] [14:53:38] <sustrik__>	cyl
| [Monday 04 April 2011] [14:53:47] 	 * Guthur is travelling twice this month to mainland europe
| [Monday 04 April 2011] [14:53:49] <sustrik__>	well, who's going to attend?
| [Monday 04 April 2011] [14:54:31] <Guthur>	if I got to 0MQ  unconf that would be 3 trips in a little over a month
| [Monday 04 April 2011] [14:54:45] <sustrik__>	same here
| [Monday 04 April 2011] [14:55:08] <Guthur>	sustrik__, where are you based?
| [Monday 04 April 2011] [14:55:13] <sustrik__>	Bratislava
| [Monday 04 April 2011] [14:55:24] <sustrik__>	Slovakia
| [Monday 04 April 2011] [14:55:32] <Guthur>	ah, I always assume you where belgian as well for some reason
| [Monday 04 April 2011] [14:56:09] <sustrik__>	Well, if I was in bxl, I could attend an uncof there every day
| [Monday 04 April 2011] [14:56:40] <Guthur>	...true
| [Monday 04 April 2011] [14:56:46] <sustrik__>	but travelling across half of europe just to have a beer
| [Monday 04 April 2011] [14:56:59] <sustrik__>	dunno
| [Monday 04 April 2011] [14:59:04] <ianbarber>	would you come to the conference if it was a traditional conference (though one you weren't speaking at)?
| [Monday 04 April 2011] [14:59:44] <guido_g>	would depend on the progem
| [Monday 04 April 2011] [15:00:20] <guido_g>	for me the main reason to go to a conference is learn something
| [Monday 04 April 2011] [15:00:21] <Guthur>	oh hi guido_g, sorry never got a chance to give you a call while in Hamburg
| [Monday 04 April 2011] [15:00:40] <Guthur>	the schedule was a lot fuller than I thought
| [Monday 04 April 2011] [15:00:40] <jond>	sustrik__, ianbarber: referring to earlier stuff that was a good point about the statefull servers because that's exactly the problem i have....
| [Monday 04 April 2011] [15:00:47] <guido_g>	Guthur: thought so, Guthur lost in lisp :)
| [Monday 04 April 2011] [15:01:19] <Guthur>	hehe, indeed, it was great to finally meet some other lispers
| [Monday 04 April 2011] [15:01:24] <Guthur>	a rare breed
| [Monday 04 April 2011] [15:01:33] <guido_g>	indeed
| [Monday 04 April 2011] [15:01:42] <guido_g>	most of them must be quite old  :)
| [Monday 04 April 2011] [15:02:17] <Guthur>	there is always a chosen few who pick up the torch
| [Monday 04 April 2011] [15:02:36] <Guthur>	there was actually some pretty cool stuff
| [Monday 04 April 2011] [15:03:12] <jond>	guthur:  what was the best presentation?
| [Monday 04 April 2011] [15:03:45] <Guthur>	3 stand out ones, I need to go away for 15 mins though
| [Monday 04 April 2011] [15:03:48] <Guthur>	back soon
| [Monday 04 April 2011] [15:05:53] <sustrik__>	ianbarber: well, i just spent 6 days on a conference that i weren't speaking at
| [Monday 04 April 2011] [15:06:06] <sustrik__>	it's a const/benefit thing i would guess
| [Monday 04 April 2011] [15:06:37] <sustrik__>	if it solves a problem, i don't object to travelling
| [Monday 04 April 2011] [15:07:27] <sustrik__>	jond: yes, the stateful services are a problem
| [Monday 04 April 2011] [15:07:52] <sustrik__>	i am not even sure there's an accepted generic solution for that
| [Monday 04 April 2011] [15:08:28] <sustrik__>	the most cases i've seen simply tweaked the architecture until it kind of worked
| [Monday 04 April 2011] [15:15:47] <WebWeasel>	I was wondering how long 0mq has been in development?
| [Monday 04 April 2011] [15:19:30] <jond>	sustrik: yes, 0mq patterns tend to assume that all workers nodes can do identical tasks, but retrieving state would not be solution as it would be too slow and as the messages are small it's quicker to route to process or thread hosting the state.
| [Monday 04 April 2011] [15:21:49] <jond>	and as topic matching and subscription forwarding would be useful for that, rather than use xrep route to identity
| [Monday 04 April 2011] [15:22:07] <jond>	that's why i'm always interested in that
| [Monday 04 April 2011] [15:25:58] <sustrik__>	WebWeasel: since Nov 2007 iirc
| [Monday 04 April 2011] [15:26:19] <WebWeasel>	Thank you.
| [Monday 04 April 2011] [15:27:17] <sustrik__>	jond: well, the basic idea is that all the state is contained in the message itself
| [Monday 04 April 2011] [15:28:10] <guido_g>	rest, the mq way :)
| [Monday 04 April 2011] [15:28:42] <sustrik__>	yeah
| [Monday 04 April 2011] [15:28:52] <sustrik__>	the problem is that legacy apps don't work that way
| [Monday 04 April 2011] [15:29:27] <sustrik__>	thus porting a legacy app to 0mq may is often problematic
| [Monday 04 April 2011] [15:29:50] <guido_g>	true
| [Monday 04 April 2011] [15:30:05] <guido_g>	but that applies to basically everything
| [Monday 04 April 2011] [15:30:19] <sustrik__>	true
| [Monday 04 April 2011] [15:33:07] <jond>	sustrik__: yes, i am just not sure it always possible though with ordering guarantees etc. it might need another layer of indirection, ie another set of queues in front of the pool which can perform any request. 
| [Monday 04 April 2011] [15:34:01] <Guthur>	jond: the standout presentations for me where,  Compiling for the Common Case, Reconfigurable Computing on Steroids: Using Common Lisp to Generate Domain Specific Hardware, The Scheme Natural Language Toolkit, and Implementing huge term automata.
| [Monday 04 April 2011] [15:34:22] <Guthur>	the Common Case one was not very specific to Lisp though
| [Monday 04 April 2011] [15:34:49] <Guthur>	but it did promise greater benefits for dynamic languages in general
| [Monday 04 April 2011] [15:35:26] <Guthur>	the talk was given by Craig Zilles, who does some R&D for intel
| [Monday 04 April 2011] [15:36:20] <Guthur>	it's basically compiling highly optimized code that will be run the majority of the time, and then falling back to more general code for the edge cases
| [Monday 04 April 2011] [15:36:42] <Guthur>	sounded pretty cool
| [Monday 04 April 2011] [15:37:45] <Guthur>	the reconfigurable computing was also interesting, a company Novasparks which is developing FPGA based low latency computing boxes using Common Lisp to program the hardware
| [Monday 04 April 2011] [15:38:12] <Guthur>	they will aim to expose a DSL to the customer for reconfiguration
| [Monday 04 April 2011] [15:39:13] <Guthur>	The NLP stuff was just interesting, and the huge term automata was a little over my head but still a nice use of functional programming paradigm to solve a problem that would not otherwise be solvable
| [Monday 04 April 2011] [15:39:58] <Guthur>	unless you had infinite memory of course
| [Monday 04 April 2011] [15:40:16] <jond>	guthur: there was job going in london looking for people programming FPGAm didnt mention lisp though
| [Monday 04 April 2011] [15:40:49] <jond>	guthur: was the NLP/ huge automata scheme?
| [Monday 04 April 2011] [15:53:35] <Guthur>	jond: NLP was Scheme
| [Monday 04 April 2011] [15:53:49] <Guthur>	the huge automata was CL, some graph theory stuff
| [Monday 04 April 2011] [15:54:43] <jond>	guthur: cheers i'll look for papers on website, might even checkout clojure
| [Monday 04 April 2011] [15:55:07] <Guthur>	I find it hard to warm to clojure
| [Monday 04 April 2011] [15:55:24] <Guthur>	it breaks the nice uniformity of Lisp syntax
| [Monday 04 April 2011] [15:55:27] <michaelgreene_>	Continuing my port to 2.1, in some cases I end up waiting on a single socket when terminating the context out of several created by my application.  One red flag in gdb is that socket.mailbox shows { w = 26, r = 27 }.  Should these numbers be balanced? Is there a way to tell whether this socket is waiting on a send or just hasn't been closed? Also, is there anywhere for me to poke at the data that ZMQ is waiting on in the case of a send?
| [Monday 04 April 2011] [15:55:49] <Guthur>	it uses square brackets for parameter lists and arrays I think
| [Monday 04 April 2011] [15:56:22] <jond>	guthur: that  was a point i made to a friend about a year ago, seemed to change things for no good reason
| [Monday 04 April 2011] [15:56:27] <Guthur>	michaelgreene_, I think you may want the Linger opt
| [Monday 04 April 2011] [15:56:50] <jond>	guthur: have you read kizcales mop book?
| [Monday 04 April 2011] [15:57:31] <Guthur>	jond: nope, link?
| [Monday 04 April 2011] [15:58:05] <Guthur>	ah AMOP
| [Monday 04 April 2011] [15:58:20] <michaelgreene_>	Guthur: I am aware that setting Linger could force the socket down, but that is not the behavior I want.  In my case, most of the sockets close cleanly, and I want to figure out what is causing 1 socket to remain unclosed and hold up context termination.  I'm just not sure how to debug it do to not being familiar enough with ZMQ's implementation structures.
| [Monday 04 April 2011] [15:58:41] <Guthur>	jond, It's something I have been meaning to pick up, it's often cited as a must read
| [Monday 04 April 2011] [15:58:50] <realazthat__>	ahoy
| [Monday 04 April 2011] [15:58:51] <jond>	guthur: old but worth a read
| [Monday 04 April 2011] [16:00:05] <jond>	guthur: outta here for a while. i really ought to talk 0mq here when i get back.....
| [Monday 04 April 2011] [16:00:17] <Guthur>	michaelgreene_, I'm not sure of any easy way to reflect that information
| [Monday 04 April 2011] [16:01:06] <Guthur>	jond, Lisp is cool, i should start was 0MQ project in CL
| [Monday 04 April 2011] [16:02:27] <Guthur>	michaelgreene_, someone more knowledgeable of 0MQ might be able to answer it
| [Monday 04 April 2011] [16:02:32] <Guthur>	but I suspect it is not possible
| [Monday 04 April 2011] [16:03:17] <Guthur>	the public API certainly does not provide anything
| [Monday 04 April 2011] [16:03:26] <michaelgreene_>	I'm not sure how it could not be possible... the data has to exist somewhere, or the reaper wouldn't have an appropriate condition triggered for it to terminate.
| [Monday 04 April 2011] [16:03:34] <michaelgreene_>	Oh, sure, but I'm in gdb, not the public API.
| [Monday 04 April 2011] [16:03:53] <Guthur>	sustrik__, might be able to answer it