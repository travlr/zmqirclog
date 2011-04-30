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
| [Monday 04 April 2011] [16:04:25] <michaelgreene_>	Guthur: I guess I'll have to poke around the source more to see how normal termination works.  Thanks for trying.
| [Monday 04 April 2011] [16:05:17] <Guthur>	hehe, it's ok I didn't have to try too hard, after the public API my knowledge kind of stops
| [Monday 04 April 2011] [16:08:05] <realz>	humm, I know u guys get poor dumb idiots like me all the time asking stupid questions ...
| [Monday 04 April 2011] [16:08:25] <realz>	but can 0mx be used for real-time applications over WAN?
| [Monday 04 April 2011] [16:08:49] <realz>	ie. for a twitch multiplayer game etc.
| [Monday 04 April 2011] [16:10:43] <mikko>	realz: good question
| [Monday 04 April 2011] [16:11:59] <Guthur>	twitch games tend to use highly tuned (usually after a couple of patches, hehe) UDP connections to get the low latency required
| [Monday 04 April 2011] [16:12:17] <Guthur>	but it would indeed be interesting to see if 0MQ could pull it off
| [Monday 04 April 2011] [16:12:34] <mikko>	i think this would be interesting use case for udt transport
| [Monday 04 April 2011] [16:15:28] <Guthur>	is UDT not more for better throughput rather than Lat
| [Monday 04 April 2011] [16:16:36] <Guthur>	throughput is not so much an issue but you need to have really low latency
| [Monday 04 April 2011] [16:18:18] <Guthur>	twitch game network engines tend to be very tolerant of dropped packets, as far as I understand
| [Monday 04 April 2011] [16:23:23] <realz>	I am looking into UDT as well
| [Monday 04 April 2011] [16:23:33] <realz>	UDT is very configurable
| [Monday 04 April 2011] [16:24:03] <realz>	are you looking into using UDT for transport?
| [Monday 04 April 2011] [16:26:51] <mikko>	realz: yes, we've been talking about it
| [Monday 04 April 2011] [16:27:02] <mikko>	realz: in fact i have an open question with them
| [Monday 04 April 2011] [16:27:10] <mikko>	the problem currently is polling
| [Monday 04 April 2011] [16:27:13] <realz>	mikko: how modular is 0mq with regard to transport?
| [Monday 04 April 2011] [16:27:18] <mikko>	realz: not very
| [Monday 04 April 2011] [16:27:39] <mikko>	realz: http://sourceforge.net/projects/udt/forums/forum/393036/topic/4061830
| [Monday 04 April 2011] [16:28:46] <realz>	ok, so lets back up a little
| [Monday 04 April 2011] [16:29:03] <realz>	excuse my ignorance, but what are some use cases of zeromq?
| [Monday 04 April 2011] [16:29:09] <realz>	ie. where does it shine
| [Monday 04 April 2011] [16:31:36] <mikko>	a lot of things really
| [Monday 04 April 2011] [16:31:44] <mikko>	the biggest things to me are:
| [Monday 04 April 2011] [16:31:58] <mikko>	not having to worry about too low-level things about different platforms
| [Monday 04 April 2011] [16:32:12] <mikko>	being able to work with 'messages' as a concept
| [Monday 04 April 2011] [16:32:18] <mikko>	rather than streams of bytes
| [Monday 04 April 2011] [16:32:31] <mikko>	the patterns
| [Monday 04 April 2011] [16:38:01] <realz>	yes, I working that message concept into my project now
| [Monday 04 April 2011] [16:38:30] <mikko>	also, threading
| [Monday 04 April 2011] [16:38:41] <mikko>	not having to create shared data structures and all the pain that comes with it
| [Monday 04 April 2011] [16:38:46] <mikko>	rather just pass messages between threads 
| [Monday 04 April 2011] [16:38:46] <realz>	I want to test multiple transports. currently using TCP, will try UDP, and UDT, maybe enet
| [Monday 04 April 2011] [16:39:17] <realz>	true indeed
| [Monday 04 April 2011] [16:39:35] <realz>	thankfully single threaded for now
| [Monday 04 April 2011] [16:39:45] <realz>	at least the event system
| [Monday 04 April 2011] [16:40:11] <realz>	I am using asio, so I dont know what threads it uses, but it is sync'd by the time it gets to my event listener
| [Monday 04 April 2011] [16:40:32] <realz>	I am using netstrings to separate messages in TCP
| [Monday 04 April 2011] [16:40:40] <realz>	I don't know how good of idea that is lol
| [Monday 04 April 2011] [16:40:57] <realz>	but it would be great to have a messaging api
| [Monday 04 April 2011] [16:41:03] <realz>	instead of rolling my own
| [Monday 04 April 2011] [16:43:45] <realz>	I also have messages that would be nice to multicast over wan
| [Monday 04 April 2011] [16:44:18] <realz>	does 0mq do anything to that effect?
| [Monday 04 April 2011] [16:44:40] <mikko>	well, pub/sub might be close to what you need there
| [Monday 04 April 2011] [16:44:48] <mikko>	multicast over wan sounds problematic
| [Monday 04 April 2011] [16:45:18] <mikko>	some people like to compare pub-sub to radio broadcast
| [Monday 04 April 2011] [16:45:37] <mikko>	all the clients will receive the message while tuned in
| [Monday 04 April 2011] [16:45:50] <mikko>	and you can split your messages into different topics
| [Monday 04 April 2011] [16:46:17] <realz>	thats cool i get the gist
| [Monday 04 April 2011] [16:49:49] <mikko>	if udt guys add the polling of normal filehandle
| [Monday 04 April 2011] [16:50:01] <mikko>	that makes it fairly easy to implement in libzmq
| [Monday 04 April 2011] [16:50:06] <mikko>	which would be good
| [Monday 04 April 2011] [17:02:35] <d4de>	what else might call zmq_term() or in general terminate the context aside from zmq_term() itself
| [Monday 04 April 2011] [17:02:51] <d4de>	I mean without calling zmq_term() directly of course
| [Monday 04 April 2011] [17:03:57] <d4de>	cause in the middle of nowhere, a call to getsockopt(), precisely in the check if (unlikely(ctx_terminated)) context is found terminated, and I'm unable to trace what might be terminating the context
| [Monday 04 April 2011] [17:04:29] <d4de>	there is no way the context is terminated otherwise without the application being terminated itself
| [Monday 04 April 2011] [17:04:42] <d4de>	(in my own application of course)
| [Monday 04 April 2011] [17:07:06] <pieterh>	multiple threads?
| [Monday 04 April 2011] [17:08:27] <d4de>	yes
| [Monday 04 April 2011] [17:08:49] <d4de>	context is shared among threads ... but documentation says that its safe
| [Monday 04 April 2011] [17:08:56] <pieterh>	sure, it's safe
| [Monday 04 April 2011] [17:09:06] <pieterh>	but one of your threads is exiting and terminating the context
| [Monday 04 April 2011] [17:09:14] <pieterh>	explicitly, by calling zmq_term
| [Monday 04 April 2011] [17:09:52] <d4de>	that's the thing you see, I don't have zmq_term anywhere! (or I should just look harder)
| [Monday 04 April 2011] [17:09:57] <pieterh>	print "hello" before every single instance of zmq_term called in your code
| [Monday 04 April 2011] [17:10:16] <d4de>	so there is no other way a context gets terminated except by calling zmq_term?
| [Monday 04 April 2011] [17:10:21] <pieterh>	what language are you using?
| [Monday 04 April 2011] [17:10:26] <d4de>	C/C++
| [Monday 04 April 2011] [17:10:39] <pieterh>	any external classes or APIs?
| [Monday 04 April 2011] [17:10:58] <d4de>	yeah I have my own wrappers
| [Monday 04 April 2011] [17:11:45] <pieterh>	so go into libzmq and edit zmq.cpp, and add 'assert (0);' in zmq_term
| [Monday 04 April 2011] [17:11:57] <pieterh>	then when you get an assertion failure, check the backtrace
| [Monday 04 April 2011] [17:12:08] <pieterh>	there are probably less brutal ways to isolate this
| [Monday 04 April 2011] [17:12:24] <d4de>	right .. never thought of that hah. Well thanks
| [Monday 04 April 2011] [17:12:28] <pieterh>	nope, there are no other ways to terminate a context except by calling zmq_term
| [Monday 04 April 2011] [17:12:30] <d4de>	I at least need some method to do it
| [Monday 04 April 2011] [17:12:42] <d4de>	thanks though :-)
| [Monday 04 April 2011] [19:51:45] <realazthat_>	humm, anyone know some sort of network-CS channel? I would love to discuss some scalability ideas
| [Monday 04 April 2011] [23:36:22] <realz>	lol turns out 0mq also uses netstrings for messages :D
| [Tuesday 05 April 2011] [01:24:09] <sustrik__>	michaelgreene_: hi
| [Tuesday 05 April 2011] [01:24:09] <sustrik__>	if you are seeing socket beeing blocked when it should not be
| [Tuesday 05 April 2011] [01:24:09] <sustrik__>	strip down the test case to its minimal version
| [Tuesday 05 April 2011] [01:24:09] <sustrik__>	and report it either on the mailing list or in bug tracker
| [Tuesday 05 April 2011] [01:24:09] <sustrik__>	you can try to debug it yourself using gdb as well
| [Tuesday 05 April 2011] [01:24:09] <sustrik__>	as for {r=26,w=27}, that's a socket pair, the fds
| [Tuesday 05 April 2011] [02:39:01] <mikko>	pieterh: 2-1 and 2-2 broken on win atm
| [Tuesday 05 April 2011] [05:11:55] <sustrik__>	Guthur: btw, the NovaSparks you've mentioned
| [Tuesday 05 April 2011] [05:12:13] <Guthur>	sustrik__: yep
| [Tuesday 05 April 2011] [05:12:17] <sustrik__>	the author of common lisp 0mq bindings is working for them
| [Tuesday 05 April 2011] [05:12:38] <Guthur>	ah, yes he did ask if I knew him
| [Tuesday 05 April 2011] [05:12:58] <Guthur>	he was actually quite interested in 0MQ
| [Tuesday 05 April 2011] [05:13:12] <pouete>	Hi all !
| [Tuesday 05 April 2011] [05:13:16] <sustrik__>	morning
| [Tuesday 05 April 2011] [05:13:23] <Guthur>	I unfortunately had to rush off at the time and didn't get a proper chance to talk to him
| [Tuesday 05 April 2011] [05:13:32] <Guthur>	I need to improve my networking skills
| [Tuesday 05 April 2011] [05:13:47] <sustrik__>	yes, i met him once as he lives quite close to here
| [Tuesday 05 April 2011] [05:14:03] <sustrik__>	i think they are either using or considering 0mq use
| [Tuesday 05 April 2011] [05:15:46] <Guthur>	They are considering it afaia
| [Tuesday 05 April 2011] [05:16:08] <Guthur>	they offer a number of interconnect strategies
| [Tuesday 05 April 2011] [05:17:11] <Guthur>	it's cool tech, I hope they are successful
| [Tuesday 05 April 2011] [05:18:00] <Guthur>	Programming hardware with with CommonLisp is pretty neat, by the looks of VHDL i can see the motivation as well
| [Tuesday 05 April 2011] [05:18:13] <sustrik__>	:)
| [Tuesday 05 April 2011] [05:18:38] <Guthur>	it's also very easy to make DSLs with CL which then helps at the customer end of the abstraction, win win
| [Tuesday 05 April 2011] [05:44:29] <Guthur>	sustrik__: What in your opinion is the biggest win of having zeromq in the kernel?
| [Tuesday 05 April 2011] [05:56:06] <jsimmons>	more people developing it :D
| [Tuesday 05 April 2011] [05:57:20] <sustrik__>	:)
| [Tuesday 05 April 2011] [05:57:29] <sustrik__>	well, it logically belongs there
| [Tuesday 05 April 2011] [05:57:54] <sustrik__>	doing it in user space means spending half of the development effort
| [Tuesday 05 April 2011] [05:58:09] <sustrik__>	trying to find workarounds around not being in the kernel
| [Tuesday 05 April 2011] [05:58:54] <sustrik__>	and from business perspective, getting into mainline linux kernel means immense deployment base
| [Tuesday 05 April 2011] [06:07:07] <Guthur>	so more logistical wins as opposed to any performance benefits
| [Tuesday 05 April 2011] [06:10:03] <sustrik__>	kind of
| [Tuesday 05 April 2011] [06:10:10] <sustrik__>	and obviosuly, saner API is a big win
| [Tuesday 05 April 2011] [06:10:21] <sustrik__>	for example, 0mq socket would a file descriptor
| [Tuesday 05 April 2011] [06:10:30] <sustrik__>	no need for zmq_init and zmq_term
| [Tuesday 05 April 2011] [06:10:50] <sustrik__>	and no associated waiting on zmq_term to send pending messages
| [Tuesday 05 April 2011] [06:10:51] <sustrik__>	etc.
| [Tuesday 05 April 2011] [06:23:28] <pouete>	I have a question : ihave ubuntu 10.10 using the MQ library, i am doing this : http://pastebin.com/gLEx8yAN and, when i am importing from python ( import zmq) i get this error : http://pastebin.com/pUsimgPv . could it be a version missmatch ?
| [Tuesday 05 April 2011] [06:23:39] <pouete>	and how can i solve this problem ?
| [Tuesday 05 April 2011] [06:31:03] <Guthur>	pouete: personally, I think for sanity sake it is better to download the source for 0MQ directly, compile and install
| [Tuesday 05 April 2011] [06:31:11] <Guthur>	YMMV though
| [Tuesday 05 April 2011] [06:31:22] <sustrik__>	looks like some old 2.0.x version
| [Tuesday 05 April 2011] [06:32:27] <pouete>	sustrik__: indeed, the test suite tell me that i have     ZMQ version detected: 2.0.6
| [Tuesday 05 April 2011] [06:32:48] <pouete>	so, have to uninstall it first i suppose
| [Tuesday 05 April 2011] [06:32:48] <sustrik__>	getsockopt was introduced in 2.0.7 iirc
| [Tuesday 05 April 2011] [06:36:01] <pouete>	A! seems better, aptitude didnt purged all the files
| [Tuesday 05 April 2011] [06:37:12] <pouete>	sorry : i didnt asked aptitude to purge all files :)
| [Tuesday 05 April 2011] [06:43:33] <pouete>	ERROR: test messages from memoryview (only valid for python >= 2.7) < i have this error and python == 2.6.6, do i have to considere this as a real error (install python => 2.7) or a minor feature i dont need (keep my python version )? 
| [Tuesday 05 April 2011] [07:41:37] <private_meta>	hmm... dammit, need to rewrite the majordomo protocol for me alredy
| [Tuesday 05 April 2011] [07:41:38] <private_meta>	*already
| [Tuesday 05 April 2011] [07:42:45] <Guthur>	private_meta: you need to add to the spec?
| [Tuesday 05 April 2011] [07:42:55] <private_meta>	no
| [Tuesday 05 April 2011] [07:42:57] <private_meta>	well
| [Tuesday 05 April 2011] [07:43:04] <private_meta>	I need client-to-broker heartbeats
| [Tuesday 05 April 2011] [07:43:13] <private_meta>	that ain't possible in the current design
| [Tuesday 05 April 2011] [07:43:17] <private_meta>	not like that
| [Tuesday 05 April 2011] [07:46:49] <Guthur>	private_meta: not sure why you need that
| [Tuesday 05 April 2011] [07:47:21] <private_meta>	I just need it
| [Tuesday 05 April 2011] [07:47:28] <Guthur>	a client is strictly synchronous, so you could feasibly just timeout on any request
| [Tuesday 05 April 2011] [07:47:35] <Guthur>	no need for heartbeat
| [Tuesday 05 April 2011] [07:47:47] <private_meta>	no, it's async for me
| [Tuesday 05 April 2011] [07:47:58] <Guthur>	well then you have already left the spec
| [Tuesday 05 April 2011] [07:48:30] <Guthur>	you could maybe have the client as a worker as well
| [Tuesday 05 April 2011] [07:48:36] <Guthur>	or some such
| [Tuesday 05 April 2011] [07:49:11] <private_meta>	in a way that would be a nice idea
| [Tuesday 05 April 2011] [07:49:22] <private_meta>	that way I'd just have to implement worker-to-worker comm
| [Tuesday 05 April 2011] [07:50:44] <Guthur>	as long as the workers, brokers and clients full fill their contract per the spec I think you can get away with any connection pattern
| [Tuesday 05 April 2011] [07:51:57] <private_meta>	Well, I'd still have to change the spec in the way that the Client address would be the service name
| [Tuesday 05 April 2011] [07:53:06] <private_meta>	but that would be a less major change in the protocol
| [Tuesday 05 April 2011] [07:53:21] <private_meta>	hmm... it'd still change the implementation to some extent, gotta look into that
| [Tuesday 05 April 2011] [07:54:11] <Guthur>	afaics there is nothing in the spec that says a client can not use an explicit address
| [Tuesday 05 April 2011] [07:55:17] <Guthur>	though you would not fullful the "Clients SHOULD use a REQ socket "
| [Tuesday 05 April 2011] [07:55:31] <Guthur>	unless you use two sockets
| [Tuesday 05 April 2011] [07:55:41] <Guthur>	at the client/worker end
| [Tuesday 05 April 2011] [07:56:40] <Guthur>	actually the only way you could full fill the two connection contracts is by using two sockets
| [Tuesday 05 April 2011] [07:56:44] <Guthur>	imo
| [Tuesday 05 April 2011] [08:55:27] <ASY>	ZMQ sockets are connected in nature, which basically means that you can not do any type of auto-discovery on the network.  I use UDP broadcasts to identify nodes on the network. I have to continue using UDP and then use ZMQ only when UDP broadcaster has located something.  Am I correct about all of this?
| [Tuesday 05 April 2011] [08:56:46] <guido_g>	pub/sub over (e)pgm would do
| [Tuesday 05 April 2011] [08:58:02] <ASY>	ok, I have to look at PGM then.  Thanks.
| [Tuesday 05 April 2011] [09:35:11] <jmslagle>	Morning peeps :)
| [Tuesday 05 April 2011] [09:35:24] <jmslagle>	Is the on the wire protocol documented anywhere?
| [Tuesday 05 April 2011] [09:35:33] 	 * jmslagle considers writing PL/SQL binding :P
| [Tuesday 05 April 2011] [09:36:21] <jmslagle>	Ooh I found it
| [Tuesday 05 April 2011] [11:32:27] <drbobbeaty>	sustrik: you around? I have an issue that popped up with ZMQ 2.1.4 and I wanted to see if you had any ideas on it.
| [Tuesday 05 April 2011] [11:34:01] <drbobbeaty>	If anyone can help, the problem is detailed here: https://gist.github.com/903836 and it's basically, that in encoder_t::message_ready() the function zmq_msg_size() is called and it seg faults.
| [Tuesday 05 April 2011] [11:34:40] <drbobbeaty>	I wonder if you have any ideas... 
| [Tuesday 05 April 2011] [11:36:14] <guido_g>	bad logic, getting the size of a closed message
| [Tuesday 05 April 2011] [11:38:50] <drbobbeaty>	So is there anything I can do short of patching the zmq_msg_size() method and then submitting that?
| [Tuesday 05 April 2011] [11:39:02] <guido_g>	what?
| [Tuesday 05 April 2011] [11:39:19] <guido_g>	when you're closing the message it's gone
| [Tuesday 05 April 2011] [11:40:20] <drbobbeaty>	My code makes a zmq::message_t, and sends it out the socket. I'm assuming (maybe incorrectly) that the send() method copies the provided message so that it's available for sending when the socket gets around to it.
| [Tuesday 05 April 2011] [11:40:38] <drbobbeaty>	So I'm not purposefully closing it (in C++). 
| [Tuesday 05 April 2011] [11:40:54] <guido_g>	you're simply plain wrong
| [Tuesday 05 April 2011] [11:41:10] <drbobbeaty>	I'm sorry. 
| [Tuesday 05 April 2011] [11:42:10] <drbobbeaty>	Let me double-check the Guide, but I'm pretty sure I'm using code right out of there for this...
| [Tuesday 05 April 2011] [11:42:48] <guido_g>	the code in the paste is wrong, no matter  where it came from
| [Tuesday 05 April 2011] [11:43:05] <drbobbeaty>	You mean the code in the gist I posted?
| [Tuesday 05 April 2011] [11:43:33] <guido_g>	what else?
| [Tuesday 05 April 2011] [11:43:43] <guido_g>	i can't see your code from here
| [Tuesday 05 April 2011] [11:43:47] <drbobbeaty>	Sorry for being dense here, but I just want to make sure.
| [Tuesday 05 April 2011] [11:43:54] <drbobbeaty>	The code in the gist is from the 2.1.4 tarball.
| [Tuesday 05 April 2011] [11:44:10] <drbobbeaty>	If it's wrong, then it's in that tarball that it's wrong.
| [Tuesday 05 April 2011] [11:44:51] <guido_g>	might be
| [Tuesday 05 April 2011] [11:45:12] <drbobbeaty>	If it's a new bug, then I'd be glad to patch the zmq_msg_size() to check the msg->context for NULL before the size check.
| [Tuesday 05 April 2011] [11:45:23] <drbobbeaty>	Or is there another error you see?
| [Tuesday 05 April 2011] [11:46:32] <guido_g>	the message is closed unconditionally and then the size is requested
| [Tuesday 05 April 2011] [11:46:40] <guido_g>	looks like a bigger issue
| [Tuesday 05 April 2011] [11:47:18] <guido_g>	but i'm not well versed in the core
| [Tuesday 05 April 2011] [11:47:21] <drbobbeaty>	I see - in the encoder... the message is destroyed, and then possibly init-ed again.
| [Tuesday 05 April 2011] [11:48:07] <Seta00>	yeah but line 68 is only reached when the message is closed
| [Tuesday 05 April 2011] [11:48:37] <guido_g>	which sounds wrong
| [Tuesday 05 April 2011] [11:48:42] <drbobbeaty>	I'll send it to the mailing list and see see what Sustrik thinks... it does seem a little odd.
| [Tuesday 05 April 2011] [11:48:52] <guido_g>	ack
| [Tuesday 05 April 2011] [11:49:21] <Seta00>	but I agree zmq_msg_size should assert the context
| [Tuesday 05 April 2011] [11:49:42] <guido_g>	the code doesn't make sense
| [Tuesday 05 April 2011] [11:49:48] <Seta00>	I know
| [Tuesday 05 April 2011] [11:49:53] <guido_g>	at least w/o digging deeper
| [Tuesday 05 April 2011] [11:50:05] <Seta00>	but still, segfaulting on a fairly common case like that is Bad.
| [Tuesday 05 April 2011] [11:50:50] <guido_g>	why is the message closed and accessed again afterwards?
| [Tuesday 05 April 2011] [11:51:26] <drbobbeaty>	I'm trying to put it all in a nice email to the list. All good points... 
| [Tuesday 05 April 2011] [11:52:09] <guido_g>	good idea
| [Tuesday 05 April 2011] [11:54:57] <ianbarber>	pretty sure it doesn't copy when sending, else the zero copy method would be dubious. 
| [Tuesday 05 April 2011] [11:57:05] <Seta00>	yes, I remember having problems deleting the message right after sending it
| [Tuesday 05 April 2011] [11:57:37] <guido_g>	you shouldn't do that, see send man page
| [Tuesday 05 April 2011] [12:27:37] <mikko>	pieterh: MSVC issues with 2-1 and 2-2
| [Tuesday 05 April 2011] [12:27:44] <mikko>	builds: libzmq2-1_MSVC-win7 and libzmq2-2_MSVC-win7
| [Tuesday 05 April 2011] [14:13:20] <so_solid_moo>	hrm, has anyone seen this error before: usr/include/zmq.h:246:16: note: expected struct zmq_pollitem_t * but argument is of type struct zmq_pollitem_t *
| [Tuesday 05 April 2011] [14:13:22] <so_solid_moo>	:S
| [Tuesday 05 April 2011] [14:28:34] <mikko>	so_solid_moo: looks odd
| [Tuesday 05 April 2011] [14:28:47] <so_solid_moo>	yeah :(
| [Tuesday 05 April 2011] [17:04:11] <geck>	so, I've been playing with the perl bindings and the 100-basic.t unit test is giving an erro about the default ZMQ_RATE value not being 100
| [Tuesday 05 April 2011] [17:04:20] <geck>	upon further checking, the value is actually 40000
| [Tuesday 05 April 2011] [17:04:35] <geck>	is this a case of a the test not being updated, or an indication of a more serious problem?
| [Tuesday 05 April 2011] [17:05:15] <geck>	steps to reproduce: `cpan ZeroMQ` after installing 2.1.14
| [Tuesday 05 April 2011] [17:06:09] <guido_g>	the value has been changed lately
| [Tuesday 05 April 2011] [17:07:09] <geck>	file issue on github? or is that handled via rt.cpan.org?
| [Tuesday 05 April 2011] [17:07:43] <stutter>	if i have a push server set up, and 2 pull clients connected to it...is there any way to build my app so that i can start a 3rd pull client and immediately alleviate load from the existing pull clients? (take over messages that have been sent on the push server, but not processed on the pull clients yet)
| [Tuesday 05 April 2011] [17:08:20] <guido_g>	stutter: this is the default behaviour
| [Tuesday 05 April 2011] [17:08:48] <guido_g>	the push will start sending messages to the 3rd client as soon it has connected itself
| [Tuesday 05 April 2011] [17:08:53] <stutter>	yeah, just wondering if i could tweak it to start doing work immediatley
| [Tuesday 05 April 2011] [17:09:09] <stutter>	new messages only, nothing in the queue gets re-routed
| [Tuesday 05 April 2011] [17:09:21] <guido_g>	true
| [Tuesday 05 April 2011] [20:00:30] <rizenine>	Anyone get the zmq gem working on Ubuntu 10.10 64bit? I'm having issues. Can't find much in a search.
| [Wednesday 06 April 2011] [05:52:03] <mile_>	sustrik,
| [Wednesday 06 April 2011] [05:53:54] <sustrik>	HI
| [Wednesday 06 April 2011] [05:55:50] <mile_>	hi
| [Wednesday 06 April 2011] [05:55:54] <mile_>	I'm stuck with erlzmq
| [Wednesday 06 April 2011] [05:56:02] <mile_>	got a minute?
| [Wednesday 06 April 2011] [05:56:25] <sustrik>	sure
| [Wednesday 06 April 2011] [05:57:01] <mile_>	I suspect I forgot some include or similar
| [Wednesday 06 April 2011] [05:57:10] <mile_>	since I had this working on the same machine
| [Wednesday 06 April 2011] [05:57:47] <mile_>	9> c('../src/erlzmq'). 
| [Wednesday 06 April 2011] [05:57:47] <mile_>	{ok,erlzmq}
| [Wednesday 06 April 2011] [05:57:47] <mile_>	10> c('../test/mytest').
| [Wednesday 06 April 2011] [05:57:47] <mile_>	../test/mytest.erl:16: Warning: variable 'Msg' is unused
| [Wednesday 06 April 2011] [05:57:47] <mile_>	{ok,mytest}
| [Wednesday 06 April 2011] [05:57:48] <mile_>	11> mytest:test().      
| [Wednesday 06 April 2011] [05:57:50] <mile_>	** exception error: undefined function erlzmq_nif:context/1
| [Wednesday 06 April 2011] [05:57:54] <mile_>	     in function  mytest:test/0
| [Wednesday 06 April 2011] [05:58:09] <mile_>	and the line in mytest is 
| [Wednesday 06 April 2011] [05:58:11] <mile_>	 {ok, C} = erlzmq:context(0),
| [Wednesday 06 April 2011] [05:58:24] <mile_>	i have tried with 1 and without arguments
| [Wednesday 06 April 2011] [05:58:32] <mile_>	but always get the same
| [Wednesday 06 April 2011] [05:59:02] <sustrik>	hm, you should speak to yrashk
| [Wednesday 06 April 2011] [05:59:10] <mile_>	mytest is slightly modified test file
| [Wednesday 06 April 2011] [05:59:12] 	 * sustrik is not an erlang expert
| [Wednesday 06 April 2011] [05:59:25] <mile_>	oh, sorry, I have talked to you about nginx
| [Wednesday 06 April 2011] [05:59:42] <mile_>	in the similar context
| [Wednesday 06 April 2011] [05:59:48] <mile_>	thanks !
| [Wednesday 06 April 2011] [05:59:55] <sustrik>	np
| [Wednesday 06 April 2011] [06:00:07] <sustrik>	i would just file bug report on erlzmq project or somesuch
| [Wednesday 06 April 2011] [06:00:42] <mile_>	I guess I made some stupid mistake
| [Wednesday 06 April 2011] [06:00:57] <mile_>	so i'd like to rule that out...
| [Wednesday 06 April 2011] [06:02:22] <ianbarber>	context(0) looks fishy
| [Wednesday 06 April 2011] [06:02:58] <sustrik>	it should work, however, you will be able to use only inproc transport
| [Wednesday 06 April 2011] [06:04:27] <ianbarber>	that's true
| [Wednesday 06 April 2011] [06:04:43] <mile_>	(), (1) and (0) all give the same errmsg
| [Wednesday 06 April 2011] [06:04:48] <ianbarber>	oh ok, 
| [Wednesday 06 April 2011] [06:05:07] <ianbarber>	i was going to suggest () :)
| [Wednesday 06 April 2011] [06:05:16] <mile_>	so I assume the problem is before it even gets there
| [Wednesday 06 April 2011] [06:06:08] <ianbarber>	do the tests that come with erlzmq2 work?
| [Wednesday 06 April 2011] [06:06:14] <ianbarber>	there is a make test I believe
| [Wednesday 06 April 2011] [06:06:30] <mile_>	they do compile, I believe that is the test assumption
| [Wednesday 06 April 2011] [06:06:41] <mile_>	but when I run the methods manually
| [Wednesday 06 April 2011] [06:06:47] <mile_>	they produce the same problem
| [Wednesday 06 April 2011] [06:09:52] <ianbarber>	what version of zmq did you build against?
| [Wednesday 06 April 2011] [06:12:13] <mile_>	hm, I'd have to rebuild it to know
| [Wednesday 06 April 2011] [06:12:32] <mile_>	which is not that bad idea :)
| [Wednesday 06 April 2011] [06:42:56] <alkemann>	hey. I am looking at the worker (PHP) bit of the Divide and conquer example. why is there no if recieved bit. it seems to every loop run do both (in the code, but not in actuallity)?
| [Wednesday 06 April 2011] [06:48:54] <ianbarber>	what's the file name of that one?
| [Wednesday 06 April 2011] [06:49:05] <alkemann>	http://zguide.zeromq.org/php:taskwork
| [Wednesday 06 April 2011] [06:49:47] <alkemann>	ianbarber: does the recv() "continue;" the loop on a "missing connection" ?
| [Wednesday 06 April 2011] [06:54:06] <sustrik>	alkemann: recv() is blocking
| [Wednesday 06 April 2011] [06:54:31] <sustrik>	it doesn't end unless there's a message afaiu
| [Wednesday 06 April 2011] [06:54:32] <alkemann>	ah doah
| [Wednesday 06 April 2011] [06:55:19] <alkemann>	so while is not about endlessly listen, is about respond to an infinite amount of recieved connections
| [Wednesday 06 April 2011] [06:56:05] <sustrik>	processing arbitrary number of messages
| [Wednesday 06 April 2011] [06:56:48] <alkemann>	makes sense now thanks
| [Wednesday 06 April 2011] [07:01:52] <alkemann>	ianbarber: when I took your advice, when I watched your talk, I had no projects for 0mq, but I've managed to get it into a project :)
| [Wednesday 06 April 2011] [07:02:26] <alkemann>	well, advice you quoted anyway :)
| [Wednesday 06 April 2011] [07:17:26] <mile_>	I have tried rebuilding erlzmq2, which fetches zeromq from the git
| [Wednesday 06 April 2011] [07:17:43] <mile_>	but 
| [Wednesday 06 April 2011] [07:17:45] <mile_>	deps/zeromq2/include/zmq.h:217: note: expected size_t * but argument is of type size_t *
| [Wednesday 06 April 2011] [07:17:45] <mile_>	ERROR: $CC -c $CFLAGS $DRV_CFLAGS c_src/erlzmq_nif.c -o c_src/erlzmq_nif.o failed with error: 1
| [Wednesday 06 April 2011] [07:17:45] <mile_>	make: *** [compile] Error 1
| [Wednesday 06 April 2011] [07:18:00] <mile_>	I've tried with 2.1.4. and 2.1.2
| [Wednesday 06 April 2011] [07:18:08] <mile_>	both give the same error
| [Wednesday 06 April 2011] [07:18:32] <mile_>	$ gcc --version
| [Wednesday 06 April 2011] [07:18:32] <mile_>	gcc (Ubuntu/Linaro 4.4.4-14ubuntu5) 4.4.5
| [Wednesday 06 April 2011] [07:18:53] <mile_>	anyone seen something like that?
| [Wednesday 06 April 2011] [07:20:45] <sustrik>	nope
| [Wednesday 06 April 2011] [07:20:54] <sustrik>	size_t type must be re-defined or something
| [Wednesday 06 April 2011] [07:21:12] <so_solid_moo>	mile_: I saw something like that just yesterday ;)
| [Wednesday 06 April 2011] [07:21:25] <so_solid_moo>	turned out to be a gcc bug and/or something very odd in C I don't understand
| [Wednesday 06 April 2011] [07:21:29] <sustrik>	have you solved it?
| [Wednesday 06 April 2011] [07:22:06] <so_solid_moo>	well, I had an g_array of zmq_pollitem_t, and I got that error when I had to make three references to the data
| [Wednesday 06 April 2011] [07:22:15] <so_solid_moo>	e.g. object->array->data
| [Wednesday 06 April 2011] [07:22:31] <so_solid_moo>	if I took a reference to object->array, and then used array->data, the error/warning went away
| [Wednesday 06 April 2011] [07:23:54] <so_solid_moo>	I assumed it was some kind of internal type referencing / aliasing thing in gcc getting confused
| [Wednesday 06 April 2011] [07:24:08] <mile_>	I'm not sure whether the error lies in the erlang binding or in the zmq code itself...
| [Wednesday 06 April 2011] [07:24:30] <so_solid_moo>	mile_: if it's the same type of thing as mine, neither (imho)
| [Wednesday 06 April 2011] [07:24:44] <mile_>	should I just get an older gcc?
| [Wednesday 06 April 2011] [07:26:10] <so_solid_moo>	maybe; I wasn't sure exactly why it emitted that error :(
| [Wednesday 06 April 2011] [07:26:23] <so_solid_moo>	the only suggestion I got was to try clang and see if that had a different opinion
| [Wednesday 06 April 2011] [07:27:04] <mile_>	I'm a total c noob...
| [Wednesday 06 April 2011] [07:27:29] <mile_>	so I'm kind of stuck there
| [Wednesday 06 April 2011] [07:28:05] <sustrik>	what's the compilation unit that causes the error?
| [Wednesday 06 April 2011] [07:28:12] <sustrik>	something from erlzmq?
| [Wednesday 06 April 2011] [07:28:44] <mile_>	Compiling c_src/erlzmq_nif.c
| [Wednesday 06 April 2011] [07:28:44] <mile_>	In file included from c_src/erlzmq_nif.c:26:
| [Wednesday 06 April 2011] [07:28:44] <mile_>	c_src/vector.h:44: error: conflicting types for size_t
| [Wednesday 06 April 2011] [07:28:44] <mile_>	/usr/lib/gcc/i686-linux-gnu/4.4.5/include/stddef.h:211: note: previous declaration of size_t was here
| [Wednesday 06 April 2011] [07:28:44] <mile_>	c_src/erlzmq_nif.c: In function erlzmq_nif_getsockopt:
| [Wednesday 06 April 2011] [07:28:46] <mile_>	etc
| [Wednesday 06 April 2011] [07:29:01] <mile_>	I guess its c_src/erlzmq_nif.c:26
| [Wednesday 06 April 2011] [07:29:45] <so_solid_moo>	ah, you have conflicting types
| [Wednesday 06 April 2011] [07:29:51] <so_solid_moo>	that's different to me I think
| [Wednesday 06 April 2011] [07:30:19] <so_solid_moo>	c_src/vector.h:44 is the error I would look at
| [Wednesday 06 April 2011] [07:30:28] <mile_>	do you know how to clone an older version from the GIT?
| [Wednesday 06 April 2011] [07:31:00] <sustrik>	git checkout <tag>
| [Wednesday 06 April 2011] [07:31:37] <mile_>	tx
| [Wednesday 06 April 2011] [07:34:05] <mile_>	hm, no tags in erlzmq2... I guess I'll have to wait for yrashk 
| [Wednesday 06 April 2011] [07:35:50] <sustrik>	ask him to make tags then :)
| [Wednesday 06 April 2011] [07:37:08] <mile_>	will do :)
| [Wednesday 06 April 2011] [09:45:57] <pdhborges>	Hi guys, I'd like to ask if it's common to send the same message many times
| [Wednesday 06 April 2011] [09:54:32] <sustrik>	pdhborges: the message is nullified when you send it
| [Wednesday 06 April 2011] [09:54:49] <sustrik>	thus you have to do a copy of it before sending it twice
| [Wednesday 06 April 2011] [09:54:55] <sustrik>	use zmq_msg_copy()
| [Wednesday 06 April 2011] [09:55:21] <pdhborges>	sustrik: even if I init the message with my own buffer?
| [Wednesday 06 April 2011] [09:55:30] <sustrik>	yes
| [Wednesday 06 April 2011] [09:55:34] <pdhborges>	a provide a special free function
| [Wednesday 06 April 2011] [09:55:41] <pdhborges>	s/a/and
| [Wednesday 06 April 2011] [09:55:50] <sustrik>	zmq_msg_copy() just increments refcount on your buffer
| [Wednesday 06 April 2011] [09:56:18] <sustrik>	so that you dealloc function is called only after it's pushed to all destinations
| [Wednesday 06 April 2011] [09:56:44] <pdhborges>	what if the same message is sent from multiple sockets?
| [Wednesday 06 April 2011] [09:56:52] <sustrik>	from?
| [Wednesday 06 April 2011] [09:57:10] <pdhborges>	eg: I create a message
| [Wednesday 06 April 2011] [09:57:12] <sustrik>	you mean _to_
| [Wednesday 06 April 2011] [09:57:28] <sustrik>	the same thing
| [Wednesday 06 April 2011] [09:57:29] <pdhborges>	the send the message from 2 diferent sockets
| [Wednesday 06 April 2011] [09:57:35] <pdhborges>	a ok
| [Wednesday 06 April 2011] [09:57:39] <sustrik>	send (s1, msg);
| [Wednesday 06 April 2011] [09:57:44] <sustrik>	send (s2, msg);
| [Wednesday 06 April 2011] [09:58:31] <sustrik>	sorry, actually, it should look like this
| [Wednesday 06 April 2011] [09:58:44] <sustrik>	zmq_msg_copy (msg_tmp, msg);
| [Wednesday 06 April 2011] [09:58:50] <sustrik>	zmq_send (s1, msg);
| [Wednesday 06 April 2011] [09:58:56] <sustrik>	zmq_send (s2. msg_tmp);
| [Wednesday 06 April 2011] [09:59:38] <pdhborges>	so in that case zmq_free_fn would onl be called once
| [Wednesday 06 April 2011] [09:59:44] <sustrik>	yes
| [Wednesday 06 April 2011] [09:59:53] <sustrik>	it uses the same buffer
| [Wednesday 06 April 2011] [09:59:58] <pdhborges>	a great
| [Wednesday 06 April 2011] [10:01:26] <pdhborges>	thanks for the help
| [Wednesday 06 April 2011] [10:01:33] <pdhborges>	but is this a common use case?
| [Wednesday 06 April 2011] [10:02:38] <pdhborges>	I'm writting some bindings and I would like to know if implementing messages with shared buffers is relevant
| [Wednesday 06 April 2011] [10:06:05] <joelr>	good day
| [Wednesday 06 April 2011] [10:07:18] <joelr>	in the case of multiple clients connected to a push/pull socket, does the data get sent (pushed) when the client does a receive? Alternatively, is data accumulated on the client regardless of whether the client does a receive?
| [Wednesday 06 April 2011] [10:09:10] <joelr>	in other words, where is data accumulated with a push/pull socket before clients do a receive?
| [Wednesday 06 April 2011] [10:18:05] <sustrik>	pdhborges: it's an advanced functionality that is supported from almost no bindings
| [Wednesday 06 April 2011] [10:18:27] <sustrik>	i wouldn't care about it atm
| [Wednesday 06 April 2011] [10:18:57] <pdhborges>	sustrik: that is the only problem left for the ocaml binding
| [Wednesday 06 April 2011] [10:20:18] <joelr>	in the case of multiple clients connected to a push/pull socket, does the data get sent (pushed) when the client does a receive? Alternatively, is data accumulated on the client regardless of whether the client does a receive? in other words, where is data accumulated with a push/pull socket before clients do a receive? 
| [Wednesday 06 April 2011] [10:27:09] <joelr>	pdhborges: what's the topic of discussion?
| [Wednesday 06 April 2011] [10:28:18] <pdhborges>	joelr remember the discussion about the zero copy api for ocaml?
| [Wednesday 06 April 2011] [10:28:32] <pdhborges>	well zero copy is not possible
| [Wednesday 06 April 2011] [10:28:33] <joelr>	yes
| [Wednesday 06 April 2011] [10:28:45] <pdhborges>	but copy once with reuse is certainly possible
| [Wednesday 06 April 2011] [10:28:48] <joelr>	pdhborges: why not? you can allocate the data on the c side
| [Wednesday 06 April 2011] [10:29:13] <pdhborges>	joelr yes but I have to copy the data to that buffer
| [Wednesday 06 April 2011] [10:29:19] <pdhborges>	hence it's not really zero copy
| [Wednesday 06 April 2011] [10:29:25] <pdhborges>	the python implementation
| [Wednesday 06 April 2011] [10:29:35] <pdhborges>	reuses the buffer alloc'ed by python
| [Wednesday 06 April 2011] [10:30:06] <pdhborges>	btw how is polling working for you?
| [Wednesday 06 April 2011] [10:30:10] <joelr>	pdhborges: you would write the data into the buffer from ocaml and then it won't be copied
| [Wednesday 06 April 2011] [10:30:33] <pdhborges>	yes, that is the copy once solution I was talking about
| [Wednesday 06 April 2011] [10:31:09] <joelr>	pdhborges: then zero-copy is possible
| [Wednesday 06 April 2011] [10:31:40] <pdhborges>	zero copy would be to use the result form String_val as the message buffer
| [Wednesday 06 April 2011] [10:31:52] <pdhborges>	which of course can't be done
| [Wednesday 06 April 2011] [10:32:48] <joelr>	pdhborges: what if you allocate the string on the c size and use its buffer to return an ocaml string?
| [Wednesday 06 April 2011] [10:33:14] <joelr>	on the c side
| [Wednesday 06 April 2011] [10:33:53] <pdhborges>	the message still needs to be copied to that particular buffer anyway you look at it
| [Wednesday 06 April 2011] [10:34:36] <joelr>	pdhborges: yes but only once. and you don't count that because that's not counted in zero-copy. the assumption is that you have a buffer pre-filled with data and zero-copy refers to copies made in the process of sending the buffer out through the socket
| [Wednesday 06 April 2011] [10:35:46] <pdhborges>	in that case your definition of zero copy is equal to my definition of copy once and there is no problem implementing that
| [Wednesday 06 April 2011] [10:37:40] <pdhborges>	at least as long as zmq_msg_copy is implemented with refenrece counting
| [Wednesday 06 April 2011] [10:46:43] <joelr>	pieterh: any suggestions on my question?
| [Wednesday 06 April 2011] [10:46:48] <joelr>	sustrik__: ^
| [Wednesday 06 April 2011] [10:47:43] <pdhborges>	joelr: is polling working fiine?
| [Wednesday 06 April 2011] [10:48:04] <joelr>	pdhborges: will test later this week, thanks
| [Wednesday 06 April 2011] [11:31:03] <Florent>	Hello everyone
| [Wednesday 06 April 2011] [11:32:32] <Florent>	Does anybody know if 0MQ has built-in bandwith control features?
| [Wednesday 06 April 2011] [11:35:39] <guido_g>	for pgm yes, for tcp no
| [Wednesday 06 April 2011] [11:38:20] <Florent>	Thank you. I don't know what pgm is. Let me ask my friend google...
| [Wednesday 06 April 2011] [11:39:43] <guido_g>	Florent: http://api.zeromq.org/master:zmq-pgm
| [Wednesday 06 April 2011] [11:40:08] <joelr>	help help help
| [Wednesday 06 April 2011] [11:40:14] <Florent>	thx guido_g 
| [Wednesday 06 April 2011] [11:41:35] <Florent>	unfortunately I'm using the PUSH/PULL model thus PGM won't help me that much.
| [Wednesday 06 April 2011] [11:43:02] <Florent>	I'm saying this because I just read "The pgm and epgm transports can only be used with the ZMQ_PUB and ZMQ_SUB socket types."
| [Wednesday 06 April 2011] [11:44:06] <guido_g>	<Florent> Does anybody know if 0MQ has built-in bandwith control features?   <- your question
| [Wednesday 06 April 2011] [11:48:30] <Florent>	guido_g: I know and I thank you for your anwser which was right.
| [Wednesday 06 April 2011] [11:48:47] <Florent>	I have to go. Goodbye and thank you again.
| [Wednesday 06 April 2011] [14:00:42] <zedas>	hey can someone point me at a sample in zmq 2.1.x that gets the raw socket for a zmq socket so that I can put it in my own epoll?
| [Wednesday 06 April 2011] [14:01:06] <guido_g>	there is no such thing
| [Wednesday 06 April 2011] [14:01:48] <guido_g>	but you can get a fd specifically for that w/ getsockopt
| [Wednesday 06 April 2011] [14:03:59] <zedas>	guido_g: right so you getsockopt with ZMQ_FD to get the FD
| [Wednesday 06 April 2011] [14:04:23] <guido_g>	right
| [Wednesday 06 April 2011] [14:04:30] <zedas>	and then ZMQ_EVENTS to get the events available.
| [Wednesday 06 April 2011] [14:04:37] <guido_g>	also right
| [Wednesday 06 April 2011] [14:05:21] <guido_g>	there is no other way because one mq socket can hold a lot of os sockets
| [Wednesday 06 April 2011] [14:05:33] <guido_g>	at least this is what i understood
| [Wednesday 06 April 2011] [14:05:50] <zedas>	ok so what's missing is an example of:  1. get fd, 2. put in epoll/kqueue, 3. fd goes off, 4. tell zmq to deal with it.
| [Wednesday 06 April 2011] [14:06:22] <guido_g>	4. is not needed
| [Wednesday 06 April 2011] [14:06:38] <guido_g>	all mq io activity is done by the io threads
| [Wednesday 06 April 2011] [14:07:12] <guido_g>	and there are some experimental integrations into other event loops afair
| [Wednesday 06 April 2011] [14:07:16] <zedas>	ok, so then #4 is really just do a zmq_recv/zmq_send depending on ZMQ_EVENTS results
| [Wednesday 06 April 2011] [14:07:31] <guido_g>	exactly
| [Wednesday 06 April 2011] [14:08:49] <zedas>	ok i'm going to write an example of this with epoll
| [Wednesday 06 April 2011] [14:09:49] <guido_g>	there are some projects doing that afair
| [Wednesday 06 April 2011] [14:09:49] <joelr>	in the case of multiple clients connected to a push/pull socket, does the data get sent (pushed) when the client does a receive? Alternatively, is data accumulated on the client regardless of whether the client does a receive? in other words, where is data accumulated with a push/pull socket before clients do a receive?
| [Wednesday 06 April 2011] [14:09:56] <guido_g>	have a look at the mailing list
| [Wednesday 06 April 2011] [14:12:20] <guido_g>	joelr: the data is sent to a _connected_ peer as soon as possible, if the underlying send-buffers are full, queueing takes place in the sender; the reciever fetches the data and puts it in his queue
| [Wednesday 06 April 2011] [14:13:07] <sustrik__>	zedas: have a look at src/zmq.cpp
| [Wednesday 06 April 2011] [14:13:10] <joelr>	guido_g: thanks, that's what i thought. and the send buffer will be full if receivers have not received, right?
| [Wednesday 06 April 2011] [14:13:19] <sustrik__>	there's an implementation of zmq_poll using ZMQ_FD and ZMQ_EVENTS
| [Wednesday 06 April 2011] [14:13:29] <guido_g>	joelr: no
| [Wednesday 06 April 2011] [14:13:43] <sustrik__>	one important thing is to take care the the FD is edge-triggered
| [Wednesday 06 April 2011] [14:13:52] <guido_g>	joelr: receive is asynchronous and done in the mq io thread
| [Wednesday 06 April 2011] [14:14:41] <joelr>	guido_g: so when i call recv in the client, it's just a data transfer into the calling thread?
| [Wednesday 06 April 2011] [14:15:58] <joelr>	guido_g: what i'm trying to get at is whether data will be sent round-robin to the zmq thread (background) of the the connected client, regardless of whether the client calls zmq_recv
| [Wednesday 06 April 2011] [14:16:14] <joelr>	will it be sent or will it not be sent?
| [Wednesday 06 April 2011] [14:16:17] <zedas>	sustrik__: i am, but that 5 nested loop poll isn't a very good example (or a very good poll to be honest)
| [Wednesday 06 April 2011] [14:16:39] <sustrik__>	i don't know whether there are any simple examples
| [Wednesday 06 April 2011] [14:16:45] <sustrik__>	but the logic is simple
| [Wednesday 06 April 2011] [14:17:03] <sustrik__>	1. check ZMQ_EVENTS to find out whether you can read/write immediately
| [Wednesday 06 April 2011] [14:17:16] <sustrik__>	2. if not, poll on ZMQ_FD
| [Wednesday 06 April 2011] [14:17:23] <sustrik__>	3. goto 1
| [Wednesday 06 April 2011] [14:17:31] <joelr>	guido_g: what do you say?
| [Wednesday 06 April 2011] [14:19:19] <zedas>	sustrik__: yep i'll write a clear simple example that doesn't wrap a two for-loops in an error stuffing while loop inside two #defines that should be functions.
| [Wednesday 06 April 2011] [14:21:04] <joelr>	sustrik__: with a connected pull socket, will any data be pushed to the client if they do not call zmq_recv?
| [Wednesday 06 April 2011] [14:21:11] <sustrik__>	zedas: thanks
| [Wednesday 06 April 2011] [14:21:25] <sustrik__>	two important points are
| [Wednesday 06 April 2011] [14:21:40] <sustrik__>	1. you have to check EVENTS first, otherwise you can deadlock
| [Wednesday 06 April 2011] [14:22:03] <sustrik__>	2. if FD is signaled, it doesn't necessarily mean, there a message available
| [Wednesday 06 April 2011] [14:22:09] <sustrik__>	you still have to check EVENTS
| [Wednesday 06 April 2011] [14:22:23] <sustrik__>	joelr: yes
| [Wednesday 06 April 2011] [14:23:10] <joelr>	sustrik__: so in the case of a durable socket, will this data be resent by the sender if the receiver crashes before calling zmq_recv?
| [Wednesday 06 April 2011] [14:24:28] <sustrik__>	no, it won't
| [Wednesday 06 April 2011] [14:24:46] <sustrik__>	there's an ticket for that
| [Wednesday 06 April 2011] [14:24:59] <sustrik__>	but it's not coded
| [Wednesday 06 April 2011] [14:25:07] <joelr>	sustrik__: oh, ok then. because it would seem that there's not much of a point in a durable socket if that happens
| [Wednesday 06 April 2011] [14:25:14] <guido_g>	sorry, life person visit here
| [Wednesday 06 April 2011] [14:25:23] <joelr>	sustrik__: thanks for the info
| [Wednesday 06 April 2011] [14:26:30] <sustrik__>	yes, there's not much point in durable sockets
| [Wednesday 06 April 2011] [14:26:48] <sustrik__>	but they can't be removed because of backward compatibility
| [Wednesday 06 April 2011] [14:26:52] <joelr>	sustrik__: what is the suggested workaround until this is fixed? push/pull sockets are awfully nice because of load balancing
| [Wednesday 06 April 2011] [14:27:05] <joelr>	well, i guess that's the wrong question 
| [Wednesday 06 April 2011] [14:27:07] <joelr>	hmm
| [Wednesday 06 April 2011] [14:27:43] <joelr>	sustrik__: some kind of a "work received, work completed" feedback system to the sender?
| [Wednesday 06 April 2011] [14:29:06] <sustrik__>	to be frank, full reliability is impossible
| [Wednesday 06 April 2011] [14:29:18] <sustrik__>	even if there's resend functionality
| [Wednesday 06 April 2011] [14:29:35] <sustrik__>	the message that was being processed by consumer at the point of crash
| [Wednesday 06 April 2011] [14:29:38] <sustrik__>	will be lost
| [Wednesday 06 April 2011] [14:29:41] <joelr>	sustrik__: so a feedback system then for each item of work completed?
| [Wednesday 06 April 2011] [14:30:07] <joelr>	sustrik__: with a resend of some kind through a direct (REQ?) channel?
| [Wednesday 06 April 2011] [14:30:42] <sustrik__>	depends on your topology
| [Wednesday 06 April 2011] [14:30:55] <sustrik__>	if there's single origin of all messages, they can be numbered
| [Wednesday 06 April 2011] [14:31:16] <sustrik__>	and if there's single final destination for messages, the missing ones can be detected
| [Wednesday 06 April 2011] [14:31:24] <sustrik__>	and the source can be asked to resend them
| [Wednesday 06 April 2011] [14:31:34] <joelr>	sustrik__: i'm trying to design the topology. it certainly starts with mongrel and from the handler of the mongrel messages there are several other services to be accessed
| [Wednesday 06 April 2011] [14:31:55] <joelr>	i'm thinking that all end-services should just be rep since they do a thing and send results back
| [Wednesday 06 April 2011] [14:32:02] <sustrik__>	the question is: what kind of reliability do you need?
| [Wednesday 06 April 2011] [14:32:11] <sustrik__>	when are you willing to accept a message loss?
| [Wednesday 06 April 2011] [14:32:33] <joelr>	sustrik__: i'm not. a web request needs to be serviced so a resend is needed.
| [Wednesday 06 April 2011] [14:32:43] <joelr>	assuming all services come at least in pairs
| [Wednesday 06 April 2011] [14:32:59] <joelr>	and you can obtain the endpoints for each service via a name service 
| [Wednesday 06 April 2011] [14:33:43] <joelr>	so a message loss is not acceptable
| [Wednesday 06 April 2011] [14:34:34] <sustrik__>	impossible, sorry
| [Wednesday 06 April 2011] [14:34:55] <sustrik__>	no system is 100% reliable
| [Wednesday 06 April 2011] [14:35:14] <joelr>	99.9% would be ok
| [Wednesday 06 April 2011] [14:35:24] <joelr>	or something like erlang's 99.999%
| [Wednesday 06 April 2011] [14:35:34] <sustrik__>	yes, that's acceptable
| [Wednesday 06 April 2011] [14:35:44] <sustrik__>	so, you have to make your app bug free
| [Wednesday 06 April 2011] [14:35:55] <sustrik__>	buy an UPC unit
| [Wednesday 06 April 2011] [14:36:02] <zedas>	joelr: what you want to get that is set the recv_ident and send_ident on both sides, in the handler and in mongrel2, then it's at that level
| [Wednesday 06 April 2011] [14:36:06] <joelr>	sustrik__: you are pontificating whereas i'm looking for practical advice with topology ;-)
| [Wednesday 06 April 2011] [14:36:07] <sustrik__>	that would do for 99.9
| [Wednesday 06 April 2011] [14:36:33] <sustrik__>	the point is you have to have reasonable expectation
| [Wednesday 06 April 2011] [14:36:45] <joelr>	sustrik__: yes
| [Wednesday 06 April 2011] [14:37:00] <sustrik__>	so back to the original question
| [Wednesday 06 April 2011] [14:37:08] <sustrik__>	is there a single source of all messages>
| [Wednesday 06 April 2011] [14:37:09] <sustrik__>	?
| [Wednesday 06 April 2011] [14:37:09] <zedas>	joelr: another thing is, if the message is of the kind where it *must* be delivered, then you'll want to send it to something that stores it. then other things are notified it's stored and work on it.
| [Wednesday 06 April 2011] [14:37:20] <joelr>	sustrik__: mongrel, i suppose
| [Wednesday 06 April 2011] [14:37:37] <joelr>	zedas: i'm processing mongrel requests
| [Wednesday 06 April 2011] [14:38:04] <joelr>	but the handler needs to call other services to assemble a reply
| [Wednesday 06 April 2011] [14:38:22] <zedas>	joelr: yep, i know. so let's say there's a particular handler that must always process everything it gets. that handler should store it, then work on it and it should be setup so that it's async.
| [Wednesday 06 April 2011] [14:38:43] <joelr>	zedas: why async?
| [Wednesday 06 April 2011] [14:39:16] <zedas>	joelr: async works better with http and with complex/long running tasks.
| [Wednesday 06 April 2011] [14:39:36] <zedas>	you receive the request and then set it up and get out of there, notifying the front-end immediately.
| [Wednesday 06 April 2011] [14:39:56] <joelr>	zedas: i suppose because the handler can continue dispatching work and can always route it back to the right mongrel via the identity
| [Wednesday 06 April 2011] [14:40:02] <zedas>	now, you are free to work on it as you need, scale it out, carve it up, and the end result is notifying the user, via the GUI, that it's done.
| [Wednesday 06 April 2011] [14:40:38] <zedas>	bingo. the key is to switch from "this message must always go trhough like the emails!" to "after I store this, a bunch of people work on it, and I'll tell you when it's ready"
| [Wednesday 06 April 2011] [14:40:40] <joelr>	zedas: well, in my case i cannot notify the front-end (browser) with json until i complete processing the request
| [Wednesday 06 April 2011] [14:40:52] <joelr>	sustrik__: mongrel is the single source
| [Wednesday 06 April 2011] [14:41:10] <zedas>	that's fine, in mongrel2 the socket stays open until you close it, and the receiver doesn't need to be the reply entity
| [Wednesday 06 April 2011] [14:41:37] <zedas>	so, have one handler receive and store it right away. then hav eother handlers work on it. then have the final master send the response.
| [Wednesday 06 April 2011] [14:41:51] <joelr>	zedas: if the receiver does not need to be the reply entity, then something has to know the mongrel endpoint or be connected to it, right? the sub end of it
| [Wednesday 06 April 2011] [14:42:10] <zedas>	however, that's going to fail.  any time you have these kinds of requests, if the GUI isn't designed to assume a later async response, then you'll have problems.
| [Wednesday 06 April 2011] [14:42:13] <joelr>	i don't see how you can do it another way
| [Wednesday 06 April 2011] [14:42:32] <zedas>	you totally know the endpoint, that's why you have the uuid, conn_id, and access to the sqlite database.
| [Wednesday 06 April 2011] [14:42:49] <zedas>	do a query on it, pull it up and then tlak to it.  I do this in Tir all the time.
| [Wednesday 06 April 2011] [14:42:51] <joelr>	zedas: if mongrel just sits there waiting for a reply on its pub socket then i can always send the reply somewhat later, no?
| [Wednesday 06 April 2011] [14:43:00] <joelr>	after i assemble it
| [Wednesday 06 April 2011] [14:43:19] <zedas>	totally.  mongrel2 has no notion of "request/reply".  you can have 10 other handlers reply
| [Wednesday 06 April 2011] [14:43:45] <zedas>	another batch of advice:  you're over optimizing right now.  you should just get the thing working with one handler, *then* figure out how to make it never fail.
| [Wednesday 06 April 2011] [14:43:49] <joelr>	my question is really that of how to scale the various services on the backend. it seems that having several endpoints and instances for each services should do it (freelance pattern)
| [Wednesday 06 April 2011] [14:44:13] <zedas>	the reason is it's *way* easier for me to tell you how to fix something you ahve that's simple but broken, but we could talk for days about hypothetical failure modes that might or might not happen without code.
| [Wednesday 06 April 2011] [14:44:17] <joelr>	zedas: i'm acquiring knowledge how to do the never fail but i won't be implementing it for now
| [Wednesday 06 April 2011] [14:44:33] <joelr>	zedas: scalability is what i'm interested in
| [Wednesday 06 April 2011] [14:44:46] <joelr>	scaling by adding more instances of each of my services
| [Wednesday 06 April 2011] [14:44:50] <joelr>	this is an ad network, btw
| [Wednesday 06 April 2011] [14:45:00] <zedas>	joelr: alright and i'm saying: go code it.  it's possible, and you could code all the scenarios you want in about a day.
| [Wednesday 06 April 2011] [14:45:15] <zedas>	that's why zeromq works so well.  you can prototype any bizarre network scalability mess you want.
| [Wednesday 06 April 2011] [14:45:49] <joelr>	so i have services like stats that keep track of clicks, impressions, etc. people ask this service for click-through rate for a given page displayed
| [Wednesday 06 April 2011] [14:45:56] <zedas>	joelr: also read http://gengnosis.blogspot.com/2007/01/level-triggered-and-edge-triggered.html
| [Wednesday 06 April 2011] [14:46:21] <joelr>	how do i scale it? it seems like i could use the freelance pattern where there are several instances of the service
| [Wednesday 06 April 2011] [14:46:52] <joelr>	and simply have each service use a REP socket
| [Wednesday 06 April 2011] [14:46:55] <joelr>	valid?
| [Wednesday 06 April 2011] [14:46:55] <zedas>	joelr: you scale it with http://programming-motherfucker.com/
| [Wednesday 06 April 2011] [14:47:19] <zedas>	hehe, seriously, you're at a point where you should code up a tiny prototype to see what's possible.
| [Wednesday 06 April 2011] [14:47:28] <sustrik__>	zedas: btw, i am having a talk about 0mq in moscow, but it's a webdev conference, so i would like to say something about mongrel2
| [Wednesday 06 April 2011] [14:47:44] <sustrik__>	what should i read about it to get a picture?
| [Wednesday 06 April 2011] [14:47:45] <joelr>	zedas: i'm at a point where i have already coded my tiny prototypes and i'm looking at the next step
| [Wednesday 06 April 2011] [14:48:06] <zedas>	sustrik__: oooh moscow, always wanted to go there.  what you looking to talk about re:mongrel2?  how zmq is used?
| [Wednesday 06 April 2011] [14:48:14] <joelr>	and so i'm looking know-how 
| [Wednesday 06 April 2011] [14:48:22] <sustrik__>	yes, more or less
| [Wednesday 06 April 2011] [14:48:36] <zedas>	sustrik__: you seen my presentation for pycon?  i can shoot you the slides.
| [Wednesday 06 April 2011] [14:48:49] <sustrik__>	yep, seen it
| [Wednesday 06 April 2011] [14:48:58] <sustrik__>	but maybe some more technical detail
| [Wednesday 06 April 2011] [14:49:18] <sustrik__>	should i read the docs?
| [Wednesday 06 April 2011] [14:51:07] <zedas>	sustrik__: docs would work, but there's plenty of code samples in various languages.  i'd take a look at http://tir.mongrel2.org/ and http://www.photon-project.com/ and https://github.com/j2labs/brubeck as examples of how it's being used
| [Wednesday 06 April 2011] [14:51:24] <sustrik__>	ok, will do
| [Wednesday 06 April 2011] [14:51:35] <sustrik__>	thx for advice
| [Wednesday 06 April 2011] [14:51:59] <zedas>	sustrik__: also how zeromq simplifies a common pain in webdev: background tasks: http://www.photon-project.com/doc/tasks
| [Wednesday 06 April 2011] [14:52:23] <zedas>	mongrel2 by itself might not be attractive, but the pattern of doing an async background task of zeromq is killer for web dev.
| [Wednesday 06 April 2011] [14:52:41] <zedas>	as joelr was just fretting over.  it's pretty much *the* pain in the web's ass.
| [Wednesday 06 April 2011] [14:52:48] <sustrik__>	aha, that looks like something that may be interesting for the audience
| [Wednesday 06 April 2011] [14:53:30] <zedas>	sustrik__: in Tir it's similar http://tir.mongrel2.org/home and read Builtin Background Tasks
| [Wednesday 06 April 2011] [14:53:46] <sustrik__>	ok, I'll do some reading, I will ask you if i am not sure of some aspects of thing
| [Wednesday 06 April 2011] [14:54:54] <zedas>	go for it.
| [Wednesday 06 April 2011] [14:55:09] <zedas>	joelr: feel free to continue this in #mongrel2, seems like more of a topic for there.
| [Wednesday 06 April 2011] [14:55:35] <joelr>	zedas: fair
| [Wednesday 06 April 2011] [14:55:43] <sustrik__>	joelr: sorry
| [Wednesday 06 April 2011] [14:55:58] <joelr>	sustrik__: no problem
| [Wednesday 06 April 2011] [14:56:01] <sustrik__>	zedas is more relevant for this topic than i am :)
| [Wednesday 06 April 2011] [15:56:05] <achin>	if i've got a question about building pyzmq, can i ask in here?
| [Wednesday 06 April 2011] [15:56:36] <sustrik__>	sure
| [Wednesday 06 April 2011] [15:59:00] <achin>	i build libzmq from the latest source, and then i ran the following issue:  http://pastebin.com/iXk705eM
| [Wednesday 06 April 2011] [16:00:51] <achin>	i think some cython magic has gone awry, but i don't have any experience with cython and all the fancy stuff it does
| [Wednesday 06 April 2011] [16:08:36] <sustrik__>	ah
| [Wednesday 06 April 2011] [16:08:50] <sustrik__>	the master is now undergoing changes
| [Wednesday 06 April 2011] [16:08:55] <sustrik__>	use 2.1.4 instead
| [Wednesday 06 April 2011] [16:10:49] <achin>	same thing i'm afraid (using the 2.1.4 branch of pyzmq)
| [Wednesday 06 April 2011] [16:29:35] <sustrik__>	same errors?
| [Wednesday 06 April 2011] [16:30:17] <sustrik__>	you must have headers from master installed somewhere
| [Wednesday 06 April 2011] [16:30:57] <sustrik__>	the errors in the pastebin are complaining about the changes done in master
| [Wednesday 06 April 2011] [16:35:14] <achin>	i did a setup.py clean, and another configure:  http://pastebin.com/FBk7fF9g
| [Wednesday 06 April 2011] [16:36:28] <sustrik__>	it looks like the pyzmq is getting the header file from master still
| [Wednesday 06 April 2011] [16:36:38] <sustrik__>	check for zmq.h files on your disk
| [Wednesday 06 April 2011] [16:38:18] <achin>	maybe i'm just confused.  i'm still using master from libzmq -- is that appropriate? or should i use something older?
| [Wednesday 06 April 2011] [17:54:12] <freeformz>	Has anyone used rzmq with sinatra in any way successfully? Including testing? I'd love to understand your usage pattern
| [Thursday 07 April 2011] [01:39:39] <sustrik__>	achin: you need zeromq 2.1.4 aside of pyzmq 2.1.4
| [Thursday 07 April 2011] [06:38:15] <mile_>	evax, thanks for the erlzmq patch
| [Thursday 07 April 2011] [06:38:39] <mile_>	but sadly, it diesn't work
| [Thursday 07 April 2011] [06:38:49] <mile_>	I just got around to try it
| [Thursday 07 April 2011] [06:39:48] <autotron>	any folks here use the nodejs binding ?
| [Thursday 07 April 2011] [06:49:09] <onr>	autotron: is there a nodejs binding?
| [Thursday 07 April 2011] [06:49:41] <autotron>	onr: https://github.com/JustinTulloss/zeromq.node
| [Thursday 07 April 2011] [07:05:54] <onr>	autotron: looks neat
| [Thursday 07 April 2011] [08:26:07] <pieterh>	hi folks
| [Thursday 07 April 2011] [08:34:48] <achin>	sustrik__, ah, ok, thanks.  i didn't think to do that since there is no "2.1.4" tag or branch in the libzmq repo.  i guess i'll have to download a tarball
| [Thursday 07 April 2011] [08:45:09] <pieterh>	achin: we started making stable releases of 0MQ a few months back
| [Thursday 07 April 2011] [08:45:30] <pieterh>	what's in the repo is generally unstable and only for those wanting to test the latest code
| [Thursday 07 April 2011] [08:50:35] <achin>	there's a v2.1.0 tag in the repo, so i guess i would have expected to find a v.2.1.4 tag as well
| [Thursday 07 April 2011] [08:50:59] <pieterh>	achin: for various reasons, we split the release process off the development process
| [Thursday 07 April 2011] [08:51:16] <pieterh>	so there are separate repos for releases, which do have the tags
| [Thursday 07 April 2011] [08:51:43] <pieterh>	we're probably going to merge these back into the libzmq repo at some point
| [Thursday 07 April 2011] [08:52:13] <achin>	ok, that's good to know, thanks
| [Thursday 07 April 2011] [08:52:38] <pieterh>	the 2-1 release repo is at https://github.com/zeromq/zeromq2-1
| [Thursday 07 April 2011] [08:53:05] <pieterh>	there is an intention to broaden the "release" to include other projects, such as bindings
| [Thursday 07 April 2011] [08:53:30] <achin>	ahh, that's really the repo i should be using
| [Thursday 07 April 2011] [08:54:01] <pieterh>	well, unless you specifically want a git (e.g. to work on the code) you should take the packages
| [Thursday 07 April 2011] [08:54:12] <pieterh>	they are recent, fresh, stable
| [Thursday 07 April 2011] [08:55:08] <achin>	i thought i would try the latest, but i was having issues building pyzmq, so i'm going to back up a step and use the latest [matching stable] versions for both
| [Thursday 07 April 2011] [08:56:03] <pieterh>	yeah, the libzmq master has morphed into 3.0, so you want the 2.1.4 tarball
| [Thursday 07 April 2011] [08:56:21] <pieterh>	this should be indicated on the pyzmq page
| [Thursday 07 April 2011] [09:09:31] <achin>	pieterh, using both zmq 2.1.4 and pyzmq 2.1.4, everything builds cleanly, as expected
| [Thursday 07 April 2011] [09:09:40] <pieterh>	achin: nice
| [Thursday 07 April 2011] [09:09:57] <pieterh>	achin: it'd be worth fixing whatever path you followed, so others get this right
| [Thursday 07 April 2011] [09:11:23] <achin>	i checked out master of the libzmq repo.  this built cleanly.  i then checked out master from the pyzmq repo, which had problems building against libzmq master
| [Thursday 07 April 2011] [09:11:41] <pieterh>	so why did you go to the libzmq master?
| [Thursday 07 April 2011] [09:12:10] <achin>	good question
| [Thursday 07 April 2011] [09:12:15] <pieterh>	I assume you started at www.zeromq.org?
| [Thursday 07 April 2011] [09:12:55] <achin>	i did.  i'm trying to find the page/link that pointed me to libzmq
| [Thursday 07 April 2011] [09:13:17] <pieterh>	let's find it and fix it, that's a trap for the unwary
| [Thursday 07 April 2011] [09:14:08] <pieterh>	possibly via this page: http://www.zeromq.org/bindings:python?
| [Thursday 07 April 2011] [09:14:45] <achin>	well, that page got to me the pyzmq repo
| [Thursday 07 April 2011] [09:15:11] <achin>	i *think* i might have wandered around until i found this: http://www.zeromq.org/docs:source-git
| [Thursday 07 April 2011] [09:15:55] <achin>	and thought "ooh, i like github, let me play here"
| [Thursday 07 April 2011] [09:16:43] <pieterh>	ok, I'll add a note on that page
| [Thursday 07 April 2011] [09:18:41] <achin>	i sometimes like to track a git repo instead of downloading tarballs because i find a "git checkout [new tag]" is quicker than navigating to a webpage to get a new URL to download
| [Thursday 07 April 2011] [09:19:43] <pieterh>	achin: OK, I'll add a link to the tagged repo on the download page
| [Thursday 07 April 2011] [09:20:16] <achin>	that sounds great. thanks
| [Thursday 07 April 2011] [09:22:10] <pieterh>	achin: can you check http://www.zeromq.org/intro:get-the-software and see if that makes sense?
| [Thursday 07 April 2011] [09:23:53] <achin>	sorry, i don't see anything that looks different
| [Thursday 07 April 2011] [09:24:07] <pieterh>	links to the two gits, just after the download packages
| [Thursday 07 April 2011] [09:24:22] <pieterh>	too subtle?
| [Thursday 07 April 2011] [09:25:49] <achin>	maybe the old page is stuck in some cache?  this is what i see: http://i.imgur.com/YtdT6.png
| [Thursday 07 April 2011] [09:26:10] <pieterh>	wikidot does quite aggressive caching, try reloading?
| [Thursday 07 April 2011] [09:26:34] <achin>	oh wait.  yeah, after mashing F5, i see it now
| [Thursday 07 April 2011] [09:26:41] <pieterh>	ok
| [Thursday 07 April 2011] [09:26:44] <achin>	that looks perfect
| [Thursday 07 April 2011] [09:27:04] <pieterh>	it's true that git is quite a nice way to get code
| [Thursday 07 April 2011] [09:27:11] <pieterh>	great!
| [Thursday 07 April 2011] [09:27:59] <achin>	git fetch, git tag -l *oh, somethign new* git checkout 
| [Thursday 07 April 2011] [09:31:14] <achin>	thanks for the help, and thanks for being so aware of your users' experiences.  i now can start hacking out neat distributed applications
| [Thursday 07 April 2011] [09:35:30] <mikko>	pieterh: msvc
| [Thursday 07 April 2011] [09:35:48] <pieterh>	achin: np, it's always fun to improve the 'experience'
| [Thursday 07 April 2011] [09:36:02] <pieterh>	mikko: hi!, and a good msvc to you too
| [Thursday 07 April 2011] [09:36:19] <mikko>	http://build.zero.mq/view/libzmq%202.1/job/libzmq2-1_MSVC-win7/10/console
| [Thursday 07 April 2011] [09:36:22] <mikko>	same thing with 2-2
| [Thursday 07 April 2011] [09:36:25] <mikko>	not sure what it is
| [Thursday 07 April 2011] [09:36:52] <mikko>	apart from that all succeeding
| [Thursday 07 April 2011] [09:37:16] <pieterh>	hmm, could it be some code that leaked in from 3.0?
| [Thursday 07 April 2011] [09:37:34] <mikko>	it's possible
| [Thursday 07 April 2011] [09:37:38] <pieterh>	I'll fire up my win xp box and give it a shot
| [Thursday 07 April 2011] [09:37:38] <mikko>	but 3.0 succeeds that build
| [Thursday 07 April 2011] [09:37:43] <mikko>	it looks like openpgm related
| [Thursday 07 April 2011] [09:37:46] <mikko>	i've seen this before
| [Thursday 07 April 2011] [09:37:58] <pieterh>	ah, only with WithOpenPGM
| [Thursday 07 April 2011] [09:38:34] <pieterh>	it's only this, right? :
| [Thursday 07 April 2011] [09:38:35] <pieterh>	..\..\..\src\connect_session.cpp(46): error C2511: 'void zmq::connect_session_t::start_connecting(BOOL)' : overloaded member function not found in 'zmq::connect_session_t' 
| [Thursday 07 April 2011] [09:38:41] <mikko>	i think so
| [Thursday 07 April 2011] [09:38:50] <mikko>	might be related to definition of bool?
| [Thursday 07 April 2011] [09:39:27] <pieterh>	looks something like that
| [Thursday 07 April 2011] [09:49:57] <pieterh>	mikko: it's definitely in the pgm layer in libzmq
| [Thursday 07 April 2011] [09:50:08] <pieterh>	I'd suggest bubbling this up to steve
| [Thursday 07 April 2011] [10:07:49] <evax>	ok, the patch didn't work, but I reproduced and fixed it including stddef.h in vector.h AND removing the ifndef/typedef
| [Thursday 07 April 2011] [10:09:03] <stevan_>	I am running into issues trying to compile jzmq on Mac OS X, it seems to fall into a recursive hole and never stop compiling the java files
| [Thursday 07 April 2011] [10:09:06] <stevan_>	anyone seen this before?
| [Thursday 07 April 2011] [10:10:13] <stevan_>	oh wait, wow, nevermind
| [Thursday 07 April 2011] [10:10:32] 	 * stevan_ had some bad path settings, and a new shell was all that was needed
| [Thursday 07 April 2011] [10:11:03] <stevan_>	(attempting to compile unfamiliar libs in unfamiliar languages very late at night)-- 
| [Thursday 07 April 2011] [10:22:24] <evax>	(oops wrong window, sorry for the noise)
| [Thursday 07 April 2011] [10:48:34] <NikolaVeber>	evax, thanks for the patch
| [Thursday 07 April 2011] [10:50:14] <NikolaVeber>	I still have one problem though, I'm not sure if it has anything to do with the architectural issues, similar to the bug
| [Thursday 07 April 2011] [11:06:52] <NikolaVeber>	solved :)
| [Thursday 07 April 2011] [11:07:22] <evax>	NikolaVeber: oh, better yet :)
| [Thursday 07 April 2011] [11:08:11] <NikolaVeber>	I forgot the -pa argument to erl
| [Thursday 07 April 2011] [11:08:26] <NikolaVeber>	idiotic :/
| [Thursday 07 April 2011] [11:08:39] <evax>	use kerl :)
| [Thursday 07 April 2011] [11:10:21] <NikolaVeber>	http://sourceforge.net/projects/kerl/ ??
| [Thursday 07 April 2011] [11:10:45] <evax>	https://github.com/evax/kerl
| [Thursday 07 April 2011] [11:11:02] <evax>	:)
| [Thursday 07 April 2011] [11:14:23] <evax>	NikolaVeber: I only checked github before choosing the name, I missed this one :\
| [Thursday 07 April 2011] [11:21:10] <NikolaVeber>	evax, looks good... :)
| [Thursday 07 April 2011] [11:21:27] <NikolaVeber>	just that google doen't know that much about it yet :)
| [Thursday 07 April 2011] [11:22:06] <NikolaVeber>	and docs look very very nice, KUDOs
| [Thursday 07 April 2011] [11:25:54] <evax>	NikolaVeber: thanks ! btw erlzmq2 is agnerized, so once you have a kerl installation activated, you can install it with "agner install erlzmq" and it will be available on your next erl invocation
| [Thursday 07 April 2011] [11:30:24] <NikolaVeber>	cool
| [Thursday 07 April 2011] [11:30:37] <NikolaVeber>	I'll definitely have a look into it!
| [Thursday 07 April 2011] [11:45:17] <NikolaVeber>	evax, I found another inconsistence since the version a couple of weeks ago
| [Thursday 07 April 2011] [11:45:29] <NikolaVeber>	{ok, C} = erlzmq:context(),
| [Thursday 07 April 2011] [11:45:29] <NikolaVeber>	    {ok, S1} = erlzmq:socket(C, req),
| [Thursday 07 April 2011] [11:45:34] <NikolaVeber>	 erlzmq:send(S1, "Hello"),
| [Thursday 07 April 2011] [11:45:45] <NikolaVeber>	** exception error: no function clause matching erlzmq:send({1,<<>>},"Hello")
| [Thursday 07 April 2011] [11:45:45] <NikolaVeber>	     in function  mytest:request/2
| [Thursday 07 April 2011] [11:45:54] <NikolaVeber>	this code worked fine then
| [Thursday 07 April 2011] [11:46:32] <NikolaVeber>	oh, I've just seen the test file
| [Thursday 07 April 2011] [11:47:54] <NikolaVeber>	works like a charm!
| [Thursday 07 April 2011] [12:23:14] <dale18>	In the case where there is one publisher and one subscriber, should it be identical which socket binds and which one connects? It looks like if the publisher is the one connecting, it acts like a durable publisher and won't drop messages if there is no subscriber (this is different from what's in the documentation?)
| [Thursday 07 April 2011] [12:30:02] <pieterh>	dale18: it should be identical, yes
| [Thursday 07 April 2011] [12:30:31] <pieterh>	if you have a simple test case where the publisher is not dropping messages, post it, thanks
| [Thursday 07 April 2011] [12:31:07] <dale18>	okay, I do have a simple minimal example. where should I post it, right here? (it's about 10 lines of code for the publisher and the subscriber)
| [Thursday 07 April 2011] [12:31:28] <pieterh>	send it to the mailing list, and put the source code in a pastebin, e.g. github gist
| [Thursday 07 April 2011] [12:31:44] <pieterh>	also, log an issue on the libzmq repository, so it doesn't get forgotten
| [Thursday 07 April 2011] [13:10:51] <paupau>	Anyone used MQ on iOS?
| [Thursday 07 April 2011] [13:11:48] <paupau>	I've compiled it successfully at least and I guess kqueue is supported internally and all
| [Thursday 07 April 2011] [13:12:22] <paupau>	I wonder if it's a good idea re: things like wireless radio/battery life
| [Thursday 07 April 2011] [13:12:48] <paupau>	I guess that's an iOS-specific question though.
| [Thursday 07 April 2011] [13:13:00] <paupau>	Mostly just wondering if anyone else has experience with that
| [Thursday 07 April 2011] [13:15:05] <pieterh>	hi paupau
| [Thursday 07 April 2011] [13:15:30] <pieterh>	by default 0MQ doesn't do anything that would use the radio unless you ask it to
| [Thursday 07 April 2011] [13:15:58] <pieterh>	there are a few tricks like using a tickless timer in poll loops
| [Thursday 07 April 2011] [13:16:06] <paupau>	cool
| [Thursday 07 April 2011] [13:16:15] <pieterh>	but you build these yourself, on top of 0MQ
| [Thursday 07 April 2011] [13:16:45] <pieterh>	there's an example at the end of Ch4 of the Guide
| [Thursday 07 April 2011] [13:17:19] <pieterh>	you also need to do heartbeating properly, if you're using a mobile device
| [Thursday 07 April 2011] [13:17:51] <paupau>	hmm hmm
| [Thursday 07 April 2011] [16:07:33] <pieterh>	mikko: you around?
| [Thursday 07 April 2011] [16:20:58] <eyeris>	I'm trying to get pyzmq up and running on Windows. After a setup.py build and install, I get an import error "No module named win32api"
| [Thursday 07 April 2011] [16:23:20] <eyeris>	I've googled for a package named win32api, but nothing obvious comes up. There's no win32api package on pypi. There's something called PyWin32, but it seems to only be available with the ActiveState dist
| [Thursday 07 April 2011] [16:25:53] <eyeris>	Oh, wait, nvm. That's the package and it's now on sf.net
| [Thursday 07 April 2011] [16:36:09] <mikko>	pieterh: yes
| [Thursday 07 April 2011] [16:36:22] <pieterh>	mikko: I've fixed the libzapi errors for win32
| [Thursday 07 April 2011] [16:36:29] <pieterh>	it should build on mingw properly now
| [Thursday 07 April 2011] [16:36:36] <mikko>	let me try
| [Thursday 07 April 2011] [16:36:42] <pieterh>	selftests pass OK and everything... :)
| [Thursday 07 April 2011] [16:39:46] <pieterh>	mikko: it got a lot further, failed with something post-build afaics
| [Thursday 07 April 2011] [16:40:34] <mikko>	yeah
| [Thursday 07 April 2011] [16:40:43] <mikko>	noticed that coverage was on for some reason
| [Thursday 07 April 2011] [16:40:44] <mikko>	sec
| [Thursday 07 April 2011] [16:42:53] <pieterh>	success!
| [Thursday 07 April 2011] [16:43:04] <mikko>	cool
| [Thursday 07 April 2011] [16:43:15] <mikko>	almost everything for 2-1 and 2-2 succeeding now
| [Thursday 07 April 2011] [16:43:17] <pieterh>	yeah, very cool indeed...
| [Thursday 07 April 2011] [16:43:41] <pieterh>	next is to build and test the 90+ guide examples in 10 languages...
| [Thursday 07 April 2011] [16:43:49] <pieterh>	just kidding :)
| [Thursday 07 April 2011] [16:46:11] <mikko>	interesting thing is that libzmq_GCC-linux_s390x tests succeed consistently now
| [Thursday 07 April 2011] [16:46:23] <mikko>	and for 2-1 and 2-2 shutdown_stress fails
| [Thursday 07 April 2011] [16:46:53] <pieterh>	same OS & box?
| [Thursday 07 April 2011] [16:47:16] <mikko>	yes
| [Thursday 07 April 2011] [16:48:14] <mikko>	i wonder if something has changed in 30
| [Thursday 07 April 2011] [16:48:18] <mikko>	3.0*
| [Thursday 07 April 2011] [16:49:15] <sustrik__>	i've lowered the number of iterations
| [Thursday 07 April 2011] [16:49:24] <sustrik__>	so it's not that invasive
| [Thursday 07 April 2011] [16:50:03] <jond>	mikko, pieterh: quick question if i checkout 'master' from libzmq that's pretty much the latest release yes? the 3.0 stuff is  on the pre3.0 branch?
| [Thursday 07 April 2011] [16:50:44] <pieterh>	jond: nope, the 3.0 stuff is now merged into master
| [Thursday 07 April 2011] [16:50:56] <pieterh>	if you want the latest *stable* release, see the main download page
| [Thursday 07 April 2011] [16:51:12] <pieterh>	sustrik__: can you tell me where to change that in 2.1?
| [Thursday 07 April 2011] [16:51:12] <jond>	pieterh: i never use the releases!
| [Thursday 07 April 2011] [16:51:23] <pieterh>	jond: like I said, see the main download page
| [Thursday 07 April 2011] [16:51:37] <mikko>	sustrik__: that explains
| [Thursday 07 April 2011] [16:51:37] <pieterh>	unless you specifically want the unstable latest master
| [Thursday 07 April 2011] [16:51:43] <mikko>	sustrik__: have you seen this error before:
| [Thursday 07 April 2011] [16:51:55] <sustrik__>	pieterh: tests/test_shutdown_stress.cpp
| [Thursday 07 April 2011] [16:51:55] <mikko>	https://build.zero.mq/view/libzmq%202.1/job/libzmq2-1_MSVC-win7/11/console
| [Thursday 07 April 2011] [16:52:08] <mikko>	i think this has been fixed once at some point somewhere
| [Thursday 07 April 2011] [16:52:14] <mikko>	but i really can't remember the details of it
| [Thursday 07 April 2011] [16:52:33] <sustrik__>	mikko: that's steven redefining 'bool' in openpgm headers
| [Thursday 07 April 2011] [16:52:47] <sustrik__>	he've fixed that afaik
| [Thursday 07 April 2011] [16:52:56] <sustrik__>	what version of openpgm are you using?
| [Thursday 07 April 2011] [16:53:10] <pieterh>	mikko: the shutdown stress in 2.1 is the same as in 3.0 master
| [Thursday 07 April 2011] [16:53:14] <pieterh>	100 threads
| [Thursday 07 April 2011] [16:53:48] <mikko>	sustrik__: will check
| [Thursday 07 April 2011] [16:53:57] <pieterh>	ah, you changed it to 10 threads
| [Thursday 07 April 2011] [16:54:15] <sustrik__>	yes
| [Thursday 07 April 2011] [16:54:31] <pieterh>	sustrik__: you didn't send me a patch
| [Thursday 07 April 2011] [16:55:00] <sustrik__>	it was probably part of the patch that updated the tests for 3.0 api
| [Thursday 07 April 2011] [16:55:14] <sustrik__>	just patch the number in 2.1
| [Thursday 07 April 2011] [16:55:27] <mikko>	5.1.102
| [Thursday 07 April 2011] [16:55:31] <pieterh>	sure
| [Thursday 07 April 2011] [16:55:34] <mikko>	i should probably update that
| [Thursday 07 April 2011] [16:55:58] <sustrik__>	iirc it was fixed somewhere around 5.1.111
| [Thursday 07 April 2011] [16:56:37] <mikko>	i need to ask steven for newer installer package
| [Thursday 07 April 2011] [16:57:30] <pieterh>	mikko: ok, fixed shutdown stress tests on 2.1 and 2.2
| [Thursday 07 April 2011] [16:57:35] <mikko>	cool
| [Thursday 07 April 2011] [16:57:41] <mikko>	should be ok in the morning build
| [Thursday 07 April 2011] [16:57:50] <mikko>	i still need to add libzfl builds at some point
| [Thursday 07 April 2011] [16:57:55] <mikko>	what is the situation for 10th may?
| [Thursday 07 April 2011] [16:57:59] <mikko>	is it happening?
| [Thursday 07 April 2011] [16:58:21] <pieterh>	mikko: well, I have to pay the deposit for the room tomorrow
| [Thursday 07 April 2011] [16:58:29] <pieterh>	if we want it, it's cheap and nice
| [Thursday 07 April 2011] [17:00:09] <pieterh>	mikko: ok, random decision, it's on
| [Thursday 07 April 2011] [17:00:17] <mikko>	ok, cool
| [Thursday 07 April 2011] [17:00:24] <mikko>	i'll book eurostar at some point
| [Thursday 07 April 2011] [17:00:28] <mikko>	sustrik can't make it?
| [Thursday 07 April 2011] [17:00:37] <mikko>	Assertion failed: !sent && errno == EAGAIN, file test_hwm.cpp, line 53
| [Thursday 07 April 2011] [17:00:38] <pieterh>	sustrik will be recovering from vodak poisoning
| [Thursday 07 April 2011] [17:00:41] <mikko>	also interesting
| [Thursday 07 April 2011] [17:00:51] <mikko>	sustrik__: it would be cool if you can make brussels too
| [Thursday 07 April 2011] [17:00:59] <mikko>	hopefully ianbarber is coming as well
| [Thursday 07 April 2011] [17:01:06] <mikko>	he might be joining me from london
| [Thursday 07 April 2011] [17:03:10] <pieterh>	there's a few other people I'm working with in London who might come
| [Thursday 07 April 2011] [17:03:25] <pieterh>	I mean we could do the event in London
| [Thursday 07 April 2011] [17:03:42] <pieterh>	but I was there a couple of days ago and paid 10 pounds for a proper beer
| [Thursday 07 April 2011] [17:03:47] <jond>	mikko: do you have enough git-foo to explain how I get the sub forwarding stuff from the libzmq onto the zeromq2-1?
| [Thursday 07 April 2011] [17:04:37] <mikko>	jond: checkout 2-1, git remote add libzmq
| [Thursday 07 April 2011] [17:04:47] <mikko>	git cherry-pick <commit hash> 
| [Thursday 07 April 2011] [17:04:53] <mikko>	and hope it merges cleanly :)
| [Thursday 07 April 2011] [17:05:15] <mikko>	pieterh: booking a proper room in london might be more expensive
| [Thursday 07 April 2011] [17:05:19] <mikko>	not sure
| [Thursday 07 April 2011] [17:05:26] <jond>	mikko: but the subforwarding is a branch? does that make a difference?
| [Thursday 07 April 2011] [17:05:34] <pieterh>	yes, in Brussels too, this place is especially nice for that
| [Thursday 07 April 2011] [17:05:38] <mikko>	jond: shouldn't
| [Thursday 07 April 2011] [17:05:49] <pieterh>	jond: we can merge the subforwarding onto 2-2, but not 2-1
| [Thursday 07 April 2011] [17:06:22] <jond>	pieterh: can that be done on github?
| [Thursday 07 April 2011] [17:06:39] <pieterh>	jond, with git, yes
| [Thursday 07 April 2011] [17:07:23] <jond>	pieterh: so it would appear as branch of 2-2. if so that sounds easier?
| [Thursday 07 April 2011] [17:07:56] <pieterh>	jond... you can create a branch in 2-2, then pull the branch from libzmq, I guess
| [Thursday 07 April 2011] [17:08:38] <jond>	pieterh: ok, will report back....
| [Thursday 07 April 2011] [17:08:39] <mikko>	pieterh: http://skillsmatter.com/go/training-room-hire-clerkenwell
| [Thursday 07 April 2011] [17:08:46] <mikko>	i know that place in london for room hire
| [Thursday 07 April 2011] [17:08:53] <mikko>	are the prices a lot higher than brussels?
| [Thursday 07 April 2011] [17:09:28] <pieterh>	mikko: the room I'm renting has space for 50-100 people and costs 175 Euro and is right in the center
| [Thursday 07 April 2011] [17:09:38] <mikko>	that is pretty cheap
| [Thursday 07 April 2011] [17:10:46] <mikko>	brb
| [Thursday 07 April 2011] [17:42:28] <jond>	mikko: is this a new change that you do not see the compilation commands when building 2-2?  eg  CXX    libzmq_la-clock.lo
| [Thursday 07 April 2011] [18:01:14] <pieterh>	jond: we backported that to 2.1 as well
| [Thursday 07 April 2011] [18:01:51] <jond>	pieterh: is there anyway to force it log the whole command elsewhere?
| [Thursday 07 April 2011] [18:02:22] <pieterh>	jond: checking...
| [Thursday 07 April 2011] [18:02:58] <pieterh>	./configure --disable-silent-rules
| [Thursday 07 April 2011] [18:03:13] <jond>	pieterh: thx
| [Friday 08 April 2011] [01:25:17] <kevin__>	can anyone help with installation of python bindings for zeromq on mac os x snowleopard?
| [Friday 08 April 2011] [01:26:05] <kevin__>	"OSError: dlopen(zmq/_zeromq.so, 10): image not found"
| [Friday 08 April 2011] [01:31:56] <kevin__>	anyone? "-_-
| [Friday 08 April 2011] [01:32:29] <sustrik__>	try later on when more people are online
| [Friday 08 April 2011] [01:32:37] <sustrik__>	or, presumably, send an email to the mailing list
| [Friday 08 April 2011] [01:33:22] 	 * sustrik__ has no experience with either pyzmq or osx
| [Friday 08 April 2011] [01:33:33] <kevin__>	ah alrighty
| [Friday 08 April 2011] [01:33:37] <kevin__>	thanks
| [Friday 08 April 2011] [04:19:15] <pieterh>	sustrik__: I think that was just "forgot to also build zeromq"
| [Friday 08 April 2011] [04:19:53] <pieterh>	a lot of people have trouble getting a language stack working
| [Friday 08 April 2011] [04:22:02] <guido_g>	hi all
| [Friday 08 April 2011] [04:22:44] <guido_g>	pieterh: any new ideas wrt the meeting in brussels?
| [Friday 08 April 2011] [04:22:56] <pieterh>	guido_g: meeting is on, for sure
| [Friday 08 April 2011] [04:23:03] <guido_g>	ok
| [Friday 08 April 2011] [04:23:35] <pieterh>	sustrik will be there
| [Friday 08 April 2011] [04:23:57] <guido_g>	i saw it (tracking the page :)
| [Friday 08 April 2011] [04:24:26] <pieterh>	I've also emailed the list about a larger conference in the US later this year
| [Friday 08 April 2011] [04:25:57] <guido_g>	hmmm... i need to catch up on the list mails...
| [Friday 08 April 2011] [04:27:10] 	 * pieterh should start putting *URGENT*!!! in every subject line
| [Friday 08 April 2011] [04:27:23] <pieterh>	cyl, I'm off to do some shopping
| [Friday 08 April 2011] [04:27:30] <guido_g>	have fun!
| [Friday 08 April 2011] [04:28:39] <joelr>	good day!
| [Friday 08 April 2011] [04:30:56] <guido_g>	howdy!
| [Friday 08 April 2011] [04:37:21] <joelr>	guido_g: do you by chance know the project that holds zmsg_* functions
| [Friday 08 April 2011] [04:37:55] <guido_g>	not w/o searching, sorry
| [Friday 08 April 2011] [04:38:23] <guido_g>	looks like one of the projects of pieterh 
| [Friday 08 April 2011] [04:43:32] <joelr>	i think it's the libzapi project
| [Friday 08 April 2011] [04:43:43] <joelr>	well, no, it is the libzapi project
| [Friday 08 April 2011] [04:43:54] <guido_g>	:)
| [Friday 08 April 2011] [06:23:25] <Intellect>	can anyone help me with zeromq on windows?
| [Friday 08 April 2011] [06:24:02] <Intellect>	I used the msi installer from pyzmq's git page
| [Friday 08 April 2011] [06:26:51] <Intellect>	importi zmq gives me "WindowsError: [Error 14001] The application has failed to start because its side-by-side configuration is incorrect"
| [Friday 08 April 2011] [06:51:44] <pieterh>	Intellect: have you installed ZeroMQ?
| [Friday 08 April 2011] [06:52:39] <Intellect>	pieterh: that msi installs libzmq along with it
| [Friday 08 April 2011] [06:52:51] <Intellect>	I am trying to install from git now
| [Friday 08 April 2011] [06:53:06] <pieterh>	please don't install 0MQ from git
| [Friday 08 April 2011] [06:53:19] <pieterh>	there is a stable release package, 2.1.4, which goes with pyzmq 2.1.4
| [Friday 08 April 2011] [06:54:31] <Intellect>	pieterh: I unzipped that package, and built it in visual studio
| [Friday 08 April 2011] [06:55:37] <Intellect>	now I am trying "python setup.py configure --zmq=../libzmq"
| [Friday 08 April 2011] [06:55:59] <Intellect>	but it is giving me an error
| [Friday 08 April 2011] [06:57:40] <pieterh>	Intellect: I'm not familiar with the pyzmq setup process, sorry... the folks who make that are mostly in California and probably waking up soon
| [Friday 08 April 2011] [06:58:42] <Intellect>	pieterh: how exactly do I install zeromq?
| [Friday 08 April 2011] [06:58:53] <Intellect>	I unzipped the package and built it in VS
| [Friday 08 April 2011] [06:59:06] <pieterh>	Intellect: well, you build the project and then put the library and header files somewhere
| [Friday 08 April 2011] [06:59:09] <Intellect>	that just gives a dll on the lib folder right
| [Friday 08 April 2011] [06:59:22] <pieterh>	put the DLL on the path
| [Friday 08 April 2011] [06:59:42] <pieterh>	I usually copy the DLL to a directory that is on my PATH
| [Friday 08 April 2011] [07:00:15] <Intellect>	what about the header files?
| [Friday 08 April 2011] [07:00:29] <pieterh>	any project that needs them has to point to them
| [Friday 08 April 2011] [07:00:39] <pieterh>	I don't think there's any standard for Windows
| [Friday 08 April 2011] [07:01:06] <pieterh>	in msvc you can define 'additional include directories' that refer to random places
| [Friday 08 April 2011] [07:02:11] <Intellect>	pieterh: the msi installer should work. It made a zmq directory inside python side packages which has the dll
| [Friday 08 April 2011] [07:02:27] <Intellect>	it says "On Windows, libzmq.dll will be copied into the zmq directory, and installed along with pyzmq, so you shouldn't need to edit your PATH"
| [Friday 08 April 2011] [07:02:33] <pieterh>	right
| [Friday 08 April 2011] [07:02:47] <Intellect>	but importing zmq gave me that error
| [Friday 08 April 2011] [07:03:01] 	 * pieterh doesn't know, sorry
| [Friday 08 April 2011] [07:03:07] <Intellect>	:( 
| [Friday 08 April 2011] [07:03:09] <Intellect>	thanks anyway
| [Friday 08 April 2011] [07:22:47] <Intellect>	pieterh: I installed it from the msi again, but this time I replaced the dll with a one I built myself
| [Friday 08 April 2011] [07:22:49] <Intellect>	seems to work
| [Friday 08 April 2011] [07:22:50] <Intellect>	:)
| [Friday 08 April 2011] [07:23:20] <pieterh>	Intellect: great! you may want to tell the authors, and/or mention it on the pyzmq binding page
| [Friday 08 April 2011] [07:24:13] <Intellect>	pieterh: I think it is because I am on x64
| [Friday 08 April 2011] [07:24:14] <Intellect>	not sure though
| [Friday 08 April 2011] [07:24:20] <pieterh>	ah, probably
| [Friday 08 April 2011] [07:24:25] <Intellect>	they mention that the msi is dodgy on the git page 
| [Friday 08 April 2011] [07:24:28] <Intellect>	so they probably know
| [Friday 08 April 2011] [08:18:32] <Intellect>	pieterh: still around?
| [Friday 08 April 2011] [08:28:14] <pieterh>	Intellect: sorry, went out for a while, back now
| [Friday 08 April 2011] [08:28:52] <Intellect>	pieterh: I was just trying out my first program. Have a PUB sending message and a SUB receiving it
| [Friday 08 April 2011] [08:29:09] <Intellect>	the send script seems to work, but nothing is received 
| [Friday 08 April 2011] [08:29:09] <pieterh>	right
| [Friday 08 April 2011] [08:29:15] <pieterh>	that's normal
| [Friday 08 April 2011] [08:29:36] <Intellect>	do I need to run anything else?
| [Friday 08 April 2011] [08:29:45] <Intellect>	how do I receive what I sent?
| [Friday 08 April 2011] [08:29:55] <pieterh>	well, you need to read the Guide
| [Friday 08 April 2011] [08:30:11] <pieterh>	SUB sockets don't capture the beginning of a PUB stream accurately
| [Friday 08 April 2011] [08:30:16] <pieterh>	it's always fuzzy
| [Friday 08 April 2011] [08:30:20] <pieterh>	try sending 1M messages
| [Friday 08 April 2011] [08:31:02] <pieterh>	you may also enjoy this: http://zguide.zeromq.org/page:all#Missing-Message-Problem-Solver
| [Friday 08 April 2011] [08:31:21] <Intellect>	pieterh: it should work proper in REQ REP ?
| [Friday 08 April 2011] [08:31:34] <pieterh>	yes, also push/pull
| [Friday 08 April 2011] [08:31:43] <Intellect>	ok, let me try that instead then
| [Friday 08 April 2011] [08:31:50] <pieterh>	please do read the guide, it is explained in detail
| [Friday 08 April 2011] [08:32:15] <Intellect>	yea I should do that. I was reading this - http://nichol.as/zeromq-an-introduction
| [Friday 08 April 2011] [09:24:49] <mikko>	pieterh: wikidot limits api usage to pro users
| [Friday 08 April 2011] [09:24:54] <mikko>	noticed last night
| [Friday 08 April 2011] [09:25:07] <pieterh>	mikko: I'll get your account upgraded
| [Friday 08 April 2011] [09:25:43] <mikko>	it used to be free-for-all ?
| [Friday 08 April 2011] [09:25:45] <mikko>	i think so
| [Friday 08 April 2011] [09:26:00] <pieterh>	the API used to be on request, in beta
| [Friday 08 April 2011] [09:27:34] <mikko>	i sent rpm spec files for openpgm to steve
| [Friday 08 April 2011] [09:27:42] <pieterh>	mikko: ok, upgrade requested, it'll take an hour or two
| [Friday 08 April 2011] [09:27:47] <mikko>	hopefully openpgm RPMs available soon for rpm based distros
| [Friday 08 April 2011] [09:28:02] <pieterh>	neat
| [Friday 08 April 2011] [09:28:18] <Intellect>	it works :D
| [Friday 08 April 2011] [09:28:20] <mikko>	one step closed to distro packaged zeromq/openpgm
| [Friday 08 April 2011] [09:29:00] <mikko>	pieterh: congrats on libzapi
| [Friday 08 April 2011] [09:29:17] <pieterh>	mikko: thanks! it's really useful for C work
| [Friday 08 April 2011] [09:29:29] <pieterh>	I've ported all the Guide examples, am using it in a couple of new ones
| [Friday 08 April 2011] [09:29:42] <pieterh>	mainly it lets me 'fix' all the flaws in the 0MQ api :)
| [Friday 08 April 2011] [09:30:00] <mikko>	what is the difference of libzapi and libzfl?
| [Friday 08 April 2011] [09:30:07] <mikko>	zapi is 0mq related and zfl is generic?
| [Friday 08 April 2011] [09:30:21] <pieterh>	scope, I guess... a lot of libzfl went into libzapi but libzfl will grow larger
| [Friday 08 April 2011] [09:30:32] <pieterh>	whereas libzapi should remain a pure binding
| [Friday 08 April 2011] [09:31:00] <pieterh>	e.g. I have a bunch of classes for resilience, they will go into libzfl
| [Friday 08 April 2011] [09:31:22] <pieterh>	libzfl depends on libzapi & libzmq
| [Friday 08 April 2011] [09:31:40] 	 * pieterh likes to build layers...
| [Friday 08 April 2011] [09:34:26] <mikko>	cool
| [Friday 08 April 2011] [09:34:29] <mikko>	hmm
| [Friday 08 April 2011] [11:05:43] <desjardins>	Having a little trouble building erlzmq2 on OSX... https://gist.github.com/e244de338b24ada74b0e
| [Friday 08 April 2011] [11:06:29] <desjardins>	Any ideas? Not sure how that script could be missing, considering the build finds other files that live in that same dir.
| [Friday 08 April 2011] [11:11:29] <desjardins>	Ah, figured it out - glibtoolize depends on gsed but doesn't declare it as a dependency.
| [Friday 08 April 2011] [11:26:02] <evax>	hi, it's already the third time I have to deal with an issue related to the fact that zmq_recv can return before the corresponding zmq_send for inproc sockets. could this point be documented in the man page ?
| [Friday 08 April 2011] [14:34:56] <zedas>	sustrik: hey, so with the ZMQ_FD that's returned, is it triggered only on a read event or should it be polled on read/write like with a normal socket.
| [Friday 08 April 2011] [14:38:34] <MrGoodbyte>	hello. I just read that "To begin, instead of being stream (TCP), or datagram (UDP) oriented, ZeroMQ communication is message-oriented. This means that if a client socket sends a 150kb message, then the server socket will receive a complete, identical message on the other end without having to implement any explicit buffering or framing."
| [Friday 08 April 2011] [14:39:07] <MrGoodbyte>	what if my client sends a message larger than 150K?
| [Friday 08 April 2011] [14:39:15] <MrGoodbyte>	what that means?
| [Friday 08 April 2011] [14:41:48] <zedas>	MrGoodbyte: it'll be that size.  what they mean is, unlike with a socket, when you request to read a message, you get the entire message, not whatever happens to be in the socket buffer.
| [Friday 08 April 2011] [14:42:00] <sustrik>	zedas: you should poll only on IN
| [Friday 08 April 2011] [14:42:22] <sustrik>	getting IN event means "something happened" to the socket
| [Friday 08 April 2011] [14:42:31] <zedas>	sustrik: rock thanks.
| [Friday 08 April 2011] [14:42:33] <sustrik>	then you should check EVENTS
| [Friday 08 April 2011] [14:42:45] <zedas>	right then events has the real POLLIN/POLLOUT
| [Friday 08 April 2011] [14:42:55] <sustrik>	yes
| [Friday 08 April 2011] [14:43:09] <sustrik>	it's pain in ass, but cannot be done simpler on top of POSIX OS
| [Friday 08 April 2011] [14:43:25] <sustrik>	there's no way to simulated real FDs in user space
| [Friday 08 April 2011] [14:45:48] <MrGoodbyte>	zedas: thanks for your response. I'm thinkin of that porting my task server application from gevent to 0mq. but some of my task clients works with 400K data avg. what happens if clients pass that data to server? server gets only the part sized 150k of whole bunch?
| [Friday 08 April 2011] [14:52:06] <zedas>	MrGoodbyte: first, gevent can do 0mq, so you might be able to port real easy. 2nd, that's too big, you should be storing that somewhere, then sending references to it.
| [Friday 08 April 2011] [14:52:45] <zedas>	MrGoodbyte: 3rd you are reading wayyyy to much into this.  If you do this:  x = "0" * (400 * 1024) ; sock.send(x); sock.recv(x); print len(x)
| [Friday 08 April 2011] [14:53:24] <zedas>	then it'll print 409600.
| [Friday 08 April 2011] [14:53:53] <zedas>	additionally, you could probably have gone and written a small sample server to test this limitation by now :-)
| [Friday 08 April 2011] [15:03:16] <MrGoodbyte>	zedas: it was just an example. in fact, I have kinda shared memory task in my task server application and I store data on them as memcached. that s why I told u about working with larger data. It s probably not 400k in avg but I m sure there are some objects that big (:
| [Friday 08 April 2011] [15:04:07] <achin>	zedas, can you expand on "that's too big"? 
| [Friday 08 April 2011] [15:04:52] <achin>	if i want to send a 5Mb file to a worker, i should use zmq to send task info, but send the big data using another channel?
| [Friday 08 April 2011] [15:29:10] <eyeris>	The docs for pyzmq's zmq.core.poll.Poller.poll doesn't explain the return value. It's a list of 2-tuples which contain a socket and an integer
| [Friday 08 April 2011] [15:29:31] <Toba>	could be errnos
| [Friday 08 April 2011] [15:29:33] <eyeris>	I'm assuming that the integer is a code for read vs write vs exception, but I can't confirm that in the source code
| [Friday 08 April 2011] [15:29:46] <Toba>	or, not
| [Friday 08 April 2011] [15:34:46] <eyeris>	It seems to be 1=data to read, 2=ready for write.
| [Friday 08 April 2011] [16:13:22] <Toba>	what if it's... both?
| [Friday 08 April 2011] [16:13:23] <Toba>	3?
| [Friday 08 April 2011] [16:25:48] <zedas>	achin: generally i don't try to send giant messages around a set of processes. i'd send it to one, store it, then have the others go get it
| [Friday 08 April 2011] [16:31:38] <eyeris>	Toba: REQ and REP sockets are stateful.
| [Friday 08 April 2011] [16:31:55] <eyeris>	You cannot call send or receive twice in a row
| [Friday 08 April 2011] [16:32:28] <eyeris>	send(); send() will raise an error, becuase it expects a recv() call for every send() call for a REQ socket and the reverse pattern for a REP socket
| [Friday 08 April 2011] [16:34:25] <eyeris>	thus there is no way a socket can be in both the readable and writable states
| [Friday 08 April 2011] [16:42:17] <achin>	zedas, what if each process needs a different large message?  seems like pushing that large message down a ZMQ socket isn't too terrible
| [Friday 08 April 2011] [16:44:18] <Toba>	huh
| [Friday 08 April 2011] [16:44:33] <Toba>	so I must always do reply() even if the request related to send() failed utterly
| [Friday 08 April 2011] [16:44:35] <Toba>	noted
| [Friday 08 April 2011] [17:19:41] <zedas>	achin: nope you can shove tons of crap around, but if it's the same thing then sending it over and over is kind of dumb
| [Friday 08 April 2011] [17:49:33] <lt_schmidt_jr>	quick question about what is expected if a socket is registered with a poller after messages have queued up for it - will the poller report immediately that it has messages?
| [Friday 08 April 2011] [18:20:32] <achin>	zedas, ok.  in the application in my mind, you'd be sending large and unique data to each worker
| [Friday 08 April 2011] [18:29:06] <kwag>	Hi. Anyone can point me in the right direction? Does zmq has something similar to Pyro, where objects are "registered" on a name server, so in this case, remote message queues can be found on the network by name? instead of forced IP adddresses? Thanks.
| [Friday 08 April 2011] [19:24:28] <lt_schmidt_jr>	kwag: no that is something you would have to build yourself on top of 0mq
| [Friday 08 April 2011] [19:26:17] <kwag>	tnx, lt_schmidt_jr
| [Friday 08 April 2011] [22:10:30] <yrashk>	this is driving me crazy
| [Friday 08 April 2011] [22:10:36] <yrashk>	we have two erlzmq2s now :-(
| [Saturday 09 April 2011] [02:37:07] <yrashk>	pieterh: so it looks like we're going to have two erlzmq2s, one official an one fork
| [Saturday 09 April 2011] [02:37:10] <yrashk>	:D
| [Sunday 10 April 2011] [14:38:14] <pieterh>	Seta00: and now?
| [Sunday 10 April 2011] [15:07:46] <Seta00>	pieterh: :(
| [Sunday 10 April 2011] [15:07:55] <pieterh>	Seta00: bingo!
| [Sunday 10 April 2011] [15:08:00] <Seta00>	ah!
| [Sunday 10 April 2011] [15:08:26] <pieterh>	regarding the Guide, I've done it for PHP and Lua
| [Sunday 10 April 2011] [15:08:47] <pieterh>	all I need is most of the examples translated into language X, then I'll make a version in that language
| [Sunday 10 April 2011] [15:09:36] <Seta00>	how do I specify the language to use? or are the PHP and Lua versions hosted somewhere else?
| [Sunday 10 April 2011] [15:09:45] <pieterh>	have you gone to the main page?
| [Sunday 10 April 2011] [15:10:01] <pieterh>	http://zguide.zeromq.org
| [Sunday 10 April 2011] [15:10:10] <pieterh>	Click "PHP" or "Lua"
| [Sunday 10 April 2011] [15:10:35] <Seta00>	ah, I was going directly to page:all
| [Sunday 10 April 2011] [15:11:03] <pieterh>	hmm, sure, that's the link most people spread around
| [Sunday 10 April 2011] [15:11:27] <pieterh>	I'll add the language menu to the start there
| [Sunday 10 April 2011] [15:12:11] <Seta00>	nice
| [Sunday 10 April 2011] [15:12:26] <Seta00>	and what about the zmq_msg_* functions?
| [Sunday 10 April 2011] [15:15:48] <Seta00>	might as well ask that on the mailing list
| [Sunday 10 April 2011] [15:16:24] <pieterh>	hmm, ask on the list, afaik sustrik added this in 3.0 for sockets and contexts, could be done for messages too
| [Sunday 10 April 2011] [17:09:14] <seangrove>	Hey all, getting an abort trap in zmq
| [Sunday 10 April 2011] [17:09:15] <seangrove>	Bad file descriptor
| [Sunday 10 April 2011] [17:09:15] <seangrove>	rc != -1 (kqueue.cpp:67)
| [Sunday 10 April 2011] [17:09:15] <seangrove>	Abort trap
| [Sunday 10 April 2011] [17:09:45] <seangrove>	That happens right after forking, but the forked process shouldn't be accessing anything zmq related
| [Sunday 10 April 2011] [17:09:55] <seangrove>	Do I still need to generate a new zmq context for it?
| [Monday 11 April 2011] [07:54:53] <NikolaVeber>	yrashk, 
| [Monday 11 April 2011] [08:06:09] <valmac>	hi everybody!
| [Monday 11 April 2011] [08:09:12] 	 * valmac1 valmac
| [Monday 11 April 2011] [10:09:33] <NikolaVeber>	yrashk, I've just made some simple test using erlang binding and c++ over gigabit network
| [Monday 11 April 2011] [10:10:49] <NikolaVeber>	I was able to saturate the network easily with strings ca 200-300 characters long
| [Monday 11 April 2011] [10:11:55] <NikolaVeber>	and for short messages I got about 0,5 / 0,6 million msg/sec
| [Monday 11 April 2011] [10:12:03] <NikolaVeber>	pub-sub pattern
| [Monday 11 April 2011] [10:16:18] <evax>	NikolaVeber: hi, were you using active or passive mode ?
| [Monday 11 April 2011] [10:16:34] <NikolaVeber>	hm...
| [Monday 11 April 2011] [10:16:37] <NikolaVeber>	no idea :)
| [Monday 11 April 2011] [10:16:57] <evax>	active mode delivers messages to your process directly
| [Monday 11 April 2011] [10:17:04] <evax>	passive mode requires you to recv
| [Monday 11 April 2011] [10:17:11] <NikolaVeber>	passive
| [Monday 11 April 2011] [10:17:20] <NikolaVeber>	subscriber.recv(&msg);
| [Monday 11 April 2011] [10:17:27] <NikolaVeber>	thats in my subscriber loop
| [Monday 11 April 2011] [10:17:52] <evax>	I meant from Erlang
| [Monday 11 April 2011] [10:18:09] <NikolaVeber>	I was sending from erlang
| [Monday 11 April 2011] [10:18:28] <NikolaVeber>	just got it one way so far
| [Monday 11 April 2011] [10:19:25] <NikolaVeber>	active should be faster?
| [Monday 11 April 2011] [10:19:34] <evax>	no
| [Monday 11 April 2011] [10:19:46] <evax>	and active is for receiving from erlang
| [Monday 11 April 2011] [10:20:06] <evax>	could you paste your code to some place ?
| [Monday 11 April 2011] [10:20:11] <NikolaVeber>	priv?
| [Monday 11 April 2011] [10:20:25] <NikolaVeber>	or let me open pastebin
| [Monday 11 April 2011] [10:22:35] <seangrove>	Hmm, looks like I've painte myself into a corner with zeromq causing segfaults now
| [Monday 11 April 2011] [10:22:46] <seangrove>	What should I make of "Assertion failed: unnamed_sessions.empty () (socket_base.cpp:507)
| [Monday 11 April 2011] [10:22:49] <seangrove>	?
| [Monday 11 April 2011] [11:04:22] <mikko>	seangrove: how does that happen?
| [Tuesday 12 April 2011] [03:38:58] <x58>	It's a tad bit of a long read, but if anyone is able to help with this I'd appreciate it: https://gist.github.com/915117
| [Tuesday 12 April 2011] [03:41:07] <mikko>	x58: you need ZMQ_LINGER
| [Tuesday 12 April 2011] [03:41:23] <x58>	mikko: Where?
| [Tuesday 12 April 2011] [03:41:26] <mikko>	x58: assuming exit(127) is somewhat controlled exit
| [Tuesday 12 April 2011] [03:41:29] <x58>	No
| [Tuesday 12 April 2011] [03:41:30] <mikko>	on the sender side
| [Tuesday 12 April 2011] [03:41:37] <x58>	Assume that exit(127) means it crashed hard
| [Tuesday 12 April 2011] [03:41:38] <x58>	core dump
| [Tuesday 12 April 2011] [03:41:51] <x58>	Or a ctrl +c, or a server went down.
| [Tuesday 12 April 2011] [03:42:00] <mikko>	ctrl + c would be sigint
| [Tuesday 12 April 2011] [03:42:11] <mikko>	which is still controlled 
| [Tuesday 12 April 2011] [03:42:18] <x58>	Assume it is not contorled.
| [Tuesday 12 April 2011] [03:42:25] <x58>	s/contorled/controlled/
| [Tuesday 12 April 2011] [03:42:49] <mikko>	well, zmq_linger controls how long the messages linger in the socket when the socket has been closed
| [Tuesday 12 April 2011] [03:42:59] <mikko>	ZMQ_LINGER = 0 is the old behaviour
| [Tuesday 12 April 2011] [03:43:07] <mikko>	where all messages are discarded immediately
| [Tuesday 12 April 2011] [03:43:24] <x58>	Would that be the case on the server side?
| [Tuesday 12 April 2011] [03:43:42] <mikko>	well, to be honest i quite didn't read the full piece
| [Tuesday 12 April 2011] [03:43:52] <x58>	I figured as much...
| [Tuesday 12 April 2011] [03:44:14] <x58>	I understand it is a long post, but I needed that to explain what I expected and what I am trying to do.
| [Tuesday 12 April 2011] [03:44:55] <x58>	BTW, ZMQ_LINGER wouldn't help, the message has already been sent to the remote ... so at that point ZeroMQ could shut down cleanly even with SIGINT
| [Tuesday 12 April 2011] [03:45:22] <x58>	The REP socket has to discard the data it has received from the REQ upon the REQ closing the connection.
| [Tuesday 12 April 2011] [03:45:29] <x58>	However that is not the case.
| [Tuesday 12 April 2011] [03:46:28] <mikko>	and doesn't make sense either
| [Tuesday 12 April 2011] [03:46:49] <x58>	Why not? It is a REQ/REP socket, if the REQ is gone, why bother reading it's request?
| [Tuesday 12 April 2011] [03:47:10] <x58>	In TCP/IP if I receive a request, and the remote socket is already closed, I don't bother formulating a reponse.
| [Tuesday 12 April 2011] [03:47:26] <x58>	If I want fire and forget I'll use PUSH/PULL.
| [Tuesday 12 April 2011] [03:48:17] <x58>	Note, that if I remember correctly in 2.0 the remote REP socket would discard the REQ's sent data upon the REQ dropping the connection.
| [Tuesday 12 April 2011] [03:48:31] <x58>	I will do some testing when my VM boots up.
| [Tuesday 12 April 2011] [03:49:16] <mikko>	x58: it's possible that you are seeing the old linger semantics
| [Tuesday 12 April 2011] [03:49:53] <x58>	mikko: So what you are saying is that on 2.0 the ZeroMQ socket wouldn't send the data from the REQ socket until the REP socket called recv()? That doesn't even make sense.
| [Tuesday 12 April 2011] [03:50:07] <x58>	How would a poll on the REP socket know that it has data incoming then?
| [Tuesday 12 April 2011] [03:50:10] <guido_g>	no
| [Tuesday 12 April 2011] [03:50:10] <mikko>	no
| [Tuesday 12 April 2011] [03:50:15] <guido_g>	:)
| [Tuesday 12 April 2011] [03:52:30] <x58>	I'm looking at the setsockopt() page on api.zeromq.org and I don't see anything about LINGER applying to messages that are already sent.
| [Tuesday 12 April 2011] [03:52:46] <mikko>	x58: sent where?
| [Tuesday 12 April 2011] [03:52:56] <mikko>	sent over to network or sent to zeromq's send buffer?
| [Tuesday 12 April 2011] [03:53:17] <x58>	Sent over the network.
| [Tuesday 12 April 2011] [03:53:48] <guido_g>	if the message was recevied it needs to be read by the receiver
| [Tuesday 12 April 2011] [03:53:55] <x58>	Going back to my exmaple, REQ sends out "WOOT" over the network. Before REP can retrieve the message from the ZeroMQ receive buffer REQ dies a horribl
| [Tuesday 12 April 2011] [03:54:00] <x58>	e death.
| [Tuesday 12 April 2011] [03:54:20] <x58>	Now in 2.0 IIRC this meant that the message the REQ sent "woot" in this case, would be discarded on the REP side as well.
| [Tuesday 12 April 2011] [03:54:24] <mikko>	x58: it's very hard to say in which transit buffer it is at that point
| [Tuesday 12 April 2011] [03:55:09] <mikko>	most likely linger semantics apply there if you die immediately after send
| [Tuesday 12 April 2011] [03:55:35] <mikko>	i.e. it's still in the send buffer when you die
| [Tuesday 12 April 2011] [03:55:56] <mikko>	the new linger semantics cause the shutdown to delay until the message has been transmitten
| [Tuesday 12 April 2011] [03:56:07] <mikko>	with the old semantics it might or might not be sent
| [Tuesday 12 April 2011] [03:56:16] <x58>	Okay, so lets assume it is still in the send buffer and it gets sent.
| [Tuesday 12 April 2011] [03:56:30] <x58>	What I am saying is that the REP's recv() shouldn't fetch that message from the buffer at all.
| [Tuesday 12 April 2011] [03:56:44] <x58>	Since a send() will fail.
| [Tuesday 12 April 2011] [03:57:04] <x58>	What is the point of recv() data from a REQ by REP if the REQ is never going to get its request answered?
| [Tuesday 12 April 2011] [03:58:17] <guido_g>	how should that be detected?
| [Tuesday 12 April 2011] [03:58:47] <x58>	If I am an HTTP server, and I have an incoming queue of messages, and I am temporarily doing something else, and I accept() a connection and then immediately get an error trying to recv() on that socket I just accepted, I don't bother formulating a response and sending it back to the socket since it no longer exists.
| [Tuesday 12 April 2011] [03:59:03] <x58>	ZeroMQ knows when a client comes and goes (it after all uses TCP/IP)
| [Tuesday 12 April 2011] [03:59:08] <guido_g>	mq is not http
| [Tuesday 12 April 2011] [03:59:19] <mikko>	x58: but, see
| [Tuesday 12 April 2011] [03:59:30] <mikko>	x58: where does the recv() error happen?
| [Tuesday 12 April 2011] [03:59:34] <guido_g>	sure, after a read you know if a connection has been gone or not
| [Tuesday 12 April 2011] [03:59:43] <guido_g>	repeat "after a read"
| [Tuesday 12 April 2011] [03:59:44] <mikko>	if you are receiveing message in zeromq it means that recv() has succeeded
| [Tuesday 12 April 2011] [04:00:05] <guido_g>	and there is also a receive buffer...
| [Tuesday 12 April 2011] [04:01:34] <x58>	Before in my user code I call recv(), the ZeroMQ thread has already called recv() on the underlying TCP/IP socket, it also knows that before I called my recv() in my own thread that the remote client (the one that sent the data it just recv()'ed) is now gone.
| [Tuesday 12 April 2011] [04:02:02] <x58>	What ZeroMQ can do is remove that data from its receive buffer since technically the endpoint is no longer valid.
| [Tuesday 12 April 2011] [04:02:13] <x58>	Do you at least agree with me on that?
| [Tuesday 12 April 2011] [04:02:41] <guido_g>	no
| [Tuesday 12 April 2011] [04:02:47] <x58>	?
| [Tuesday 12 April 2011] [04:03:31] <guido_g>	because it might fit your mental model of messaging it does not fit mine
| [Tuesday 12 April 2011] [04:03:48] <guido_g>	or the that of the guys who wrote it that way
| [Tuesday 12 April 2011] [04:05:15] <x58>	So if I have 1000 clients connect, I start doing work for client number 1, now 400 of those clients kill their connection because of some sort of timeout, or because a network cable is unplugged, I now have to go through 400 REQ packets that when I send a reply won't go anywhere since the endpoint no longer exists? If each of those 400 REQ's take a second each that is 400 seconds that I am dealing with connections that are completely useles
| [Tuesday 12 April 2011] [04:07:55] <mikko>	sustrik: do you send the patches manually after commit?
| [Tuesday 12 April 2011] [04:08:14] <mikko>	x58: you can implement a poll / timeout for clients
| [Tuesday 12 April 2011] [04:08:42] <mikko>	x58: i think the biggest issue with that model is that you create affinity between TCP/IP connection and message
| [Tuesday 12 April 2011] [04:10:46] <x58>	mikko: At this point I might as well just use TCP/IP myself because the magic of ZeroMQ doesn't work when a connection is lost ...
| [Tuesday 12 April 2011] [04:10:59] <x58>	Instead of adding yet another ZeroMQ stream on top of my REQ/REP.
| [Tuesday 12 April 2011] [04:15:01] <mikko>	x58: i don't really see at which point you should be signaled that underlying tcp/ip has failed
| [Tuesday 12 April 2011] [04:15:33] <x58>	mikko: I shouldn't. ZeroMQ should discard the incoming REQ since it is "invalid" since sending a reply will fail anyway.
| [Tuesday 12 April 2011] [04:15:52] <x58>	ZeroMQ should work its magic at that point.
| [Tuesday 12 April 2011] [04:16:08] <guido_g>	as said, that's you point of view
| [Tuesday 12 April 2011] [04:16:40] <guido_g>	oh, there is no question that there should be a method to check if an underlying connection has vanished
| [Tuesday 12 April 2011] [04:16:41] <x58>	guido_g: Yes. And that makes much more sense. If you want a fire and forget, use PUSH/PULL.
| [Tuesday 12 April 2011] [04:16:46] <mikko>	this might work ok peer to peer over really fast network
| [Tuesday 12 April 2011] [04:16:55] <mikko>	and even then it's riddled with race conditions
| [Tuesday 12 April 2011] [04:17:02] <mikko>	but what about when you add middle devices?
| [Tuesday 12 April 2011] [04:17:05] <mikko>	router nodes?
| [Tuesday 12 April 2011] [04:17:12] <x58>	Yes? What about them?
| [Tuesday 12 April 2011] [04:17:14] <mikko>	should there be disconnection forwarding?
| [Tuesday 12 April 2011] [04:17:26] <mikko>	client <-> streamer <-> server 
| [Tuesday 12 April 2011] [04:17:43] <mikko>	maybe it's worth chatting to sustrik about this
| [Tuesday 12 April 2011] [04:17:56] <mikko>	but i'm bound to say that this is application level issue
| [Tuesday 12 April 2011] [04:18:02] <guido_g>	it is
| [Tuesday 12 April 2011] [04:18:43] <x58>	In my gist i've already possitted that. I said that if it has already been recved() and is being passed on, oh well, spend the time, but in the case of the streamer for example, it could drop 400 connections without having to bother the server with them ...
| [Tuesday 12 April 2011] [04:18:55] <x58>	What I am writing is a least recently used queueing router.
| [Tuesday 12 April 2011] [04:19:10] <x58>	I receive messages from the frontend, and they need to go to workers. Workers are on EC2 instances
| [Tuesday 12 April 2011] [04:19:13] <x58>	they come and go as they please
| [Tuesday 12 April 2011] [04:19:40] <x58>	If I have no traffic, sometimes there are 20 - 30 works that have said "send me data", but none of them are active anymore
| [Tuesday 12 April 2011] [04:20:02] <x58>	now my message router has to blindly fire off the messages to one of them, never receive a reply, and have to fall back to timeouts and retries
| [Tuesday 12 April 2011] [04:20:08] <sustrik>	mikko: yes, i send them manually before commit
| [Tuesday 12 April 2011] [04:20:15] <sustrik>	if uncontroversial i commit them
| [Tuesday 12 April 2011] [04:20:26] <sustrik>	otherwise i wait for comments/review
| [Tuesday 12 April 2011] [04:20:28] <x58>	now if my retries are set to 3 for example, I won't get through the entire backlog of workers that no longer exist.
| [Tuesday 12 April 2011] [04:20:46] <x58>	before my retries are up and I send a failure message back to the "frontend"
| [Tuesday 12 April 2011] [04:21:48] <mikko>	sustrik: cool
| [Tuesday 12 April 2011] [04:24:37] <mikko>	x58: i still think this feels like application level issue
| [Tuesday 12 April 2011] [04:25:26] 	 * sustrik is reading though the log
| [Tuesday 12 April 2011] [04:25:31] <x58>	mikko: I disagree. I've opened an issue request on github. Unless there is some way that I can be notified about the remote client having disconnected using REQ/REP doesn't feel natural anymore.
| [Tuesday 12 April 2011] [04:25:47] <mikko>	sustrik: about dropping messages from zeromq recv buffer based on tcp/ip connections going away
| [Tuesday 12 April 2011] [04:26:02] <x58>	sustrik: I've got my gist at https://gist.github.com/915117
| [Tuesday 12 April 2011] [04:26:09] <x58>	BRB
| [Tuesday 12 April 2011] [04:26:22] <sustrik>	x58 has point in that messages from particular peer can be dropped in REP socket once the peer goes away *if there's no identity set be the peer*
| [Tuesday 12 April 2011] [04:26:42] <sustrik>	the replies will be dropped anyway
| [Tuesday 12 April 2011] [04:26:59] <sustrik>	so there's no point in delivering the requests
| [Tuesday 12 April 2011] [04:28:06] <mikko>	in some cases i might still want to do the processing
| [Tuesday 12 April 2011] [04:28:14] <guido_g>	ack
| [Tuesday 12 April 2011] [04:28:15] <x58>	Then use PUSH/PULL.
| [Tuesday 12 April 2011] [04:28:26] <x58>	REQ/REP isn't fire and forget.
| [Tuesday 12 April 2011] [04:28:27] <mikko>	i'm not talking about fire and forget
| [Tuesday 12 April 2011] [04:28:35] <sustrik>	mikko: what's the use case?
| [Tuesday 12 April 2011] [04:28:37] <mikko>	but fire and do the best you can 
| [Tuesday 12 April 2011] [04:29:08] <x58>	The whole point of a REQ/REP is that you send a request, and get a reply. PUSH/PULL can be a fire and do the best you can.
| [Tuesday 12 April 2011] [04:29:30] <x58>	If you don't require a reply, then REQ/REP is the wrong socket type to use.
| [Tuesday 12 April 2011] [04:29:41] <x58>	And with a fire and do the best you can you clearly don't.
| [Tuesday 12 April 2011] [04:30:09] <x58>	If anything, make it a socket option.
| [Tuesday 12 April 2011] [04:30:12] <mikko>	yes, i guess in that scenario i can use backchannel for replies
| [Tuesday 12 April 2011] [04:30:22] <x58>	So that I can get the behaviour that seems most natural...
| [Tuesday 12 April 2011] [04:31:54] <x58>	The onous should be on the client (and I think in ZeroMQ as well) to retry sending the last data if it has yet to recv() a reply to its REQ.
| [Tuesday 12 April 2011] [04:32:21] <sustrik>	x58: yes, that's on the roudmap
| [Tuesday 12 April 2011] [04:32:33] <mikko>	i summarised the ticket as well
| [Tuesday 12 April 2011] [04:32:46] <mikko>	sustrik: where is 3.0 roadmap nowadays?
| [Tuesday 12 April 2011] [04:33:03] <sustrik>	i have no idea :)
| [Tuesday 12 April 2011] [04:33:08] <x58>	sustrik: better question, since it seems you are well versed in the code. Where can I modify the code to get the behavior I am expecting to use for my project?
| [Tuesday 12 April 2011] [04:33:11] <sustrik>	the discussion was kind of inconclusive
| [Tuesday 12 April 2011] [04:33:27] <mikko>	sustrik: you mean on the 3.0 overall ?
| [Tuesday 12 April 2011] [04:33:32] <sustrik>	yep
| [Tuesday 12 April 2011] [04:34:04] <sustrik>	mikko: probably we should discuss that at the conference
| [Tuesday 12 April 2011] [04:34:25] <sustrik>	x58: what behaviour is that?
| [Tuesday 12 April 2011] [04:34:39] <sustrik>	sorry, i haven't managed to read the whole backlog
| [Tuesday 12 April 2011] [04:34:43] <x58>	sustrik: Dropping of the data associated with that peer if the peer goes away.
| [Tuesday 12 April 2011] [04:34:52] <sustrik>	ah, let me see
| [Tuesday 12 April 2011] [04:37:18] <sustrik>	have a look at zmq::session_t::detach
| [Tuesday 12 April 2011] [04:37:29] <sustrik>	that's what gets called when connection breaks
| [Tuesday 12 April 2011] [04:37:52] <sustrik>	you don't want the behaviour to happen in all socket types
| [Tuesday 12 April 2011] [04:37:58] <sustrik>	so you should check for socket type
| [Tuesday 12 April 2011] [04:38:05] <sustrik>	that's stored in options.type
| [Tuesday 12 April 2011] [04:38:08] <x58>	Off course.
| [Tuesday 12 April 2011] [04:38:37] <x58>	Okay, I will take a look in the next couple of days. I've got some other stuff to write first, for now I just hope I don't have too many issues with disappearing REQ's.
| [Tuesday 12 April 2011] [04:38:43] <x58>	Thanks!
| [Tuesday 12 April 2011] [04:39:10] <sustrik>	np
| [Tuesday 12 April 2011] [04:39:51] <x58>	Oh, should I do my hacking on ZeroMQ2-1 or libzmq?
| [Tuesday 12 April 2011] [04:41:00] <ianbarber>	pieterh: been looking at the zero.mq issues, seems to be the .mq DNS servers. Mediaserv may not be the best nic in the world :)
| [Tuesday 12 April 2011] [04:41:23] <mikko>	x58: i think libzmq
| [Tuesday 12 April 2011] [04:41:30] <sustrik>	x58: what language binding are you using?
| [Tuesday 12 April 2011] [04:42:03] <mikko>	i think patches should be fairly easy to backport from libzmq to the other branch
| [Tuesday 12 April 2011] [04:42:06] <mikko>	e
| [Tuesday 12 April 2011] [04:42:08] <x58>	sustrik: I am ultimately going to be using the Python bindings, but on the roadmap for the project i need to re-write the message queue router in C++.
| [Tuesday 12 April 2011] [04:42:09] <mikko>	s
| [Tuesday 12 April 2011] [04:42:35] <x58>	So Python for now, C++ later.
| [Tuesday 12 April 2011] [04:42:46] <sustrik>	the problem with libzmq (dev) is that some backward incompatible have been introduced recently
| [Tuesday 12 April 2011] [04:42:52] <sustrik>	which breaks the bindings
| [Tuesday 12 April 2011] [04:43:03] <x58>	Was ZMQ 2.1.x tagged?
| [Tuesday 12 April 2011] [04:43:17] <ianbarber>	it's in a separate repos x58 
| [Tuesday 12 April 2011] [04:43:21] <x58>	Ah
| [Tuesday 12 April 2011] [04:43:47] <x58>	sustrik: I'll hack on ZeroMQ2-1 for now, when I've got something substantial I'll work on incorporation it on libzmq.
| [Tuesday 12 April 2011] [04:43:57] <x58>	incorporating *
| [Tuesday 12 April 2011] [04:44:00] <sustrik>	sure
| [Tuesday 12 April 2011] [04:44:10] <x58>	(I'm getting tired, still at work at 2:43 in the morning!)
| [Tuesday 12 April 2011] [04:44:21] <sustrik>	yuck
| [Tuesday 12 April 2011] [04:44:37] <x58>	Have a good night guys. I'll hang around, mostly idling, will be back to ask more questions soon I think ;-)
| [Tuesday 12 April 2011] [04:44:41] <mikko>	sustrik: what's the plan for 2.2 ?
| [Tuesday 12 April 2011] [04:45:02] <mikko>	if the development effort is focused on 3.0 and it's already diverging a lot from 2.1 and 2.2
| [Tuesday 12 April 2011] [04:45:07] <mikko>	not sure where that leaves 2.2
| [Tuesday 12 April 2011] [04:45:10] <sustrik>	ask pieter, it's his project
| [Tuesday 12 April 2011] [04:45:36] <mikko>	i think we need to discuss about this as well
| [Tuesday 12 April 2011] [04:45:40] <mikko>	at some point
| [Tuesday 12 April 2011] [04:46:07] <sustrik>	yes
| [Tuesday 12 April 2011] [04:46:20] <sustrik>	don't expect easy solutions though :)
| [Tuesday 12 April 2011] [04:47:36] <sustrik>	the problem is there are already too much distinct and often incompatible interests to address
| [Tuesday 12 April 2011] [04:52:36] <ianbarber>	fwiw, i kind of see 3.0 as a fork - some projects do ground up rewrites on major versions, and just after a fairly small time it's not practical to worry too much about trying to get the same patches into both systems
| [Tuesday 12 April 2011] [04:53:18] <mikko>	ianbarber: that's fair
| [Tuesday 12 April 2011] [04:53:23] <mikko>	but where does that leave 2.2 ?
| [Tuesday 12 April 2011] [04:53:24] <sustrik>	ack
| [Tuesday 12 April 2011] [04:54:04] <sustrik>	however, i still think the question is: do we want 3.0 at all?
| [Tuesday 12 April 2011] [04:54:10] <drbobbeaty>	I'm just a little concerned that the quick move to 3.0 as somewhat stranded 2.1.x into the "legacy" camp when it's really just a few weeks old.
| [Tuesday 12 April 2011] [04:54:51] <ianbarber>	mikko: 2.1/2.2 etc for all intents and purposes *are* zeromq
| [Tuesday 12 April 2011] [04:55:13] <drbobbeaty>	sustrik: I wonder if it's even possible to know that answer with 2.1.x so new. I mean, has there even been sufficient time to see all the warts and problems in the 2.1.x -- and see that they can only be fixed by a major re-write?
| [Tuesday 12 April 2011] [04:55:17] <ianbarber>	ZMQ3.0 needs time, to work out what is being changes, how it should work, and to really break things and rebuild them how they need to be
| [Tuesday 12 April 2011] [04:55:46] <mikko>	ianbarber: but 3.0 is already diverging a bit
| [Tuesday 12 April 2011] [04:55:55] <mikko>	also supplying patches gets more and more painful
| [Tuesday 12 April 2011] [04:55:56] <ianbarber>	mikko: of course, and it should continue
| [Tuesday 12 April 2011] [04:56:20] <ianbarber>	you need a small core of people working on 3, while the main bulk of the community builds stuff on 2 and feeds back
| [Tuesday 12 April 2011] [04:56:20] <mikko>	not only because 2-1, 2-2 and libzmq follow different approach to contributing
| [Tuesday 12 April 2011] [04:56:48] <ianbarber>	the reason we're having this discussion is that the move from 2.0 to 2.1 (for example) was pretty quick - the code was pretty stable, so many people were basically using trunk
| [Tuesday 12 April 2011] [04:57:14] <sustrik>	yes, the backward incompatible changes were held back for ages
| [Tuesday 12 April 2011] [04:57:16] <ianbarber>	i think that isn't sustainable - there has to be a stable line of branches, and trunk has to be free to go off to different places
| [Tuesday 12 April 2011] [04:57:53] <ianbarber>	mikko: in PHP terms, it's andrei and co working on 6, while a bunch of others worked on 5.3 (but hopefully with a more positive outcome)
| [Tuesday 12 April 2011] [04:58:30] <sustrik>	there's one more aspect to it: "product" vs. "research"
| [Tuesday 12 April 2011] [04:58:39] <ianbarber>	yeah, definitely
| [Tuesday 12 April 2011] [04:58:47] <sustrik>	the problem being that 0mq is the first instance of distributed messaging
| [Tuesday 12 April 2011] [04:58:52] <sustrik>	worldwide
| [Tuesday 12 April 2011] [04:59:08] <sustrik>	so the bleeding edge is basically research
| [Tuesday 12 April 2011] [04:59:20] <sustrik>	which doesn't play well with "product"
| [Tuesday 12 April 2011] [04:59:57] <ianbarber>	so, i think the only question is: is 2.x ready for taking the ongoing 'product' status? i think it is. 
| [Tuesday 12 April 2011] [05:00:09] <sustrik>	yes
| [Tuesday 12 April 2011] [05:00:13] <sustrik>	i would say so
| [Tuesday 12 April 2011] [05:00:58] <sustrik>	that's why i proposed reverting 3.0 changes: forget about research, focus on product
| [Tuesday 12 April 2011] [05:01:21] <drbobbeaty>	sustrik: I agree with your stance.
| [Tuesday 12 April 2011] [05:01:28] <sustrik>	there's a large community using 0mq and there's lot to be done to support them
| [Tuesday 12 April 2011] [05:01:46] <sustrik>	fix the bugs, fill in the gaps in functionality, document everything
| [Tuesday 12 April 2011] [05:02:08] <sustrik>	as for the research it can still be done in kernel implemetnation or whereever
| [Tuesday 12 April 2011] [05:02:23] <ianbarber>	the *ideal* outcome, from my point of view, would be if you would be working on 3.0, maybe with a couple of others, trying stuff out, doing the research side, but also contributing to 2.x (in a lesser capacity). 
| [Tuesday 12 April 2011] [05:03:40] <sustrik>	that'll definitely happen 
| [Tuesday 12 April 2011] [05:03:46] <mgoetzke>	can somebody explain the difference between https://github.com/zeromq/libzmq and the packing projects on github ? I though they were just branches of sorts but the commits differ a bit
| [Tuesday 12 April 2011] [05:04:00] <ianbarber>	similar thing with any contributor: for example mikko, it would be great to have to doign what you're doing for 2.x, but also being involved in helping with 3.0, but probably more 2.x than 3.x
| [Tuesday 12 April 2011] [05:04:31] <mikko>	i would be happy if we could come up with one process for all these
| [Tuesday 12 April 2011] [05:04:47] <sustrik>	mgoetzke: just use the packing projects, the libzmq should be considered unstable at the moment
| [Tuesday 12 April 2011] [05:04:59] <mgoetzke>	ok thanks
| [Tuesday 12 April 2011] [05:05:25] <ianbarber>	sustrik: it actually might be worth a note to that effect in the libzmq README
| [Tuesday 12 April 2011] [05:05:43] <sustrik>	yup, i can do that
| [Tuesday 12 April 2011] [05:06:15] <ianbarber>	mikko: what do you want out of the process though? because I just dont think sharing patches between the two projects is going to be realistic, they can and should diverge. 
| [Tuesday 12 April 2011] [05:07:15] <mikko>	move things back into one repo, make them branches, being able to commit patches that are uncontroversial
| [Tuesday 12 April 2011] [05:07:33] <mikko>	have commits mailed to mailing-list
| [Tuesday 12 April 2011] [05:08:05] <sustrik>	well, if we drop 3.0 that's where we get, right?
| [Tuesday 12 April 2011] [05:08:34] <sustrik>	2-1 and 2-2, both maintained by a single person
| [Tuesday 12 April 2011] [05:08:44] <sustrik>	thus easily mergeable into a single repo
| [Tuesday 12 April 2011] [05:08:51] <mikko>	see, that's not ideal
| [Tuesday 12 April 2011] [05:09:00] <mikko>	the single person maintainmentship(?)
| [Tuesday 12 April 2011] [05:09:04] <mikko>	maintainership
| [Tuesday 12 April 2011] [05:09:39] <sustrik>	hm, right
| [Tuesday 12 April 2011] [05:10:10] <mikko>	i tried to have a discussion with pieter about this
| [Tuesday 12 April 2011] [05:10:15] <mikko>	but there was too much beer 
| [Tuesday 12 April 2011] [05:10:27] <sustrik>	:)
| [Tuesday 12 April 2011] [05:10:40] <sustrik>	ok, let's leave that for brussels
| [Tuesday 12 April 2011] [05:11:02] <mikko>	i'm just saying that there is certain amount of uncontroversial patches
| [Tuesday 12 April 2011] [05:11:16] <mikko>	and the current process makes it slightly uncomfortable
| [Tuesday 12 April 2011] [05:11:47] <sustrik>	ack
| [Tuesday 12 April 2011] [05:11:57] <mikko>	work on changes, commit, format-patch, mail changes, wait for merge, reset HEAD~1, pull from upstream, format patch again, apply to 2-1 and 2-2 and push
| [Tuesday 12 April 2011] [05:12:16] <mikko>	especially when they are different repos you can't push to all of them from single local repo
| [Tuesday 12 April 2011] [05:12:39] <mikko>	you need to have zeromq2-1 from where you can push to zeromq2-1 and zeromq2-2 from where you can push zeromq2-2
| [Tuesday 12 April 2011] [05:12:49] <sustrik>	understood
| [Tuesday 12 April 2011] [05:12:54] <mikko>	and all repos have all other repos as 'remotes' so that you can cherry pick changes
| [Tuesday 12 April 2011] [05:13:07] <mikko>	for people contributing to many branches it's getting out of hand
| [Tuesday 12 April 2011] [05:13:48] <sustrik>	yes
| [Tuesday 12 April 2011] [05:14:16] <sustrik>	take a step back though
| [Tuesday 12 April 2011] [05:14:29] <sustrik>	individual repos are tight to specific interests
| [Tuesday 12 April 2011] [05:14:35] <sustrik>	whether commercial or personal
| [Tuesday 12 April 2011] [05:14:56] <sustrik>	so, to minimise number of repos these interest should be identified
| [Tuesday 12 April 2011] [05:14:59] <sustrik>	and dealt with
| [Tuesday 12 April 2011] [05:15:11] <sustrik>	for example, my personal interest is research
| [Tuesday 12 April 2011] [05:15:34] <sustrik>	i have a libzmq repo which i wanted to use for research
| [Tuesday 12 April 2011] [05:16:10] <sustrik>	however, it turns out that people are not that enthusiastic about research and want basically what they have now, but more stable and feature complete
| [Tuesday 12 April 2011] [05:16:39] <mikko>	see, that's where we disagree
| [Tuesday 12 April 2011] [05:16:50] <mikko>	i don't see how your research has to happen in isolation
| [Tuesday 12 April 2011] [05:17:23] <mikko>	there are some fixes / improvements going to 3.0 that benefits the commercial interest as well
| [Tuesday 12 April 2011] [05:17:53] <sustrik>	i'm not saying that, i'm just saying that discussion of specific interests should happen
| [Tuesday 12 April 2011] [05:18:09] <sustrik>	and the structure of repos should follow from that
| [Tuesday 12 April 2011] [05:19:02] <sustrik>	then there are commercial interests
| [Tuesday 12 April 2011] [05:19:04] <mikko>	sure, it's an important discussion to have
| [Tuesday 12 April 2011] [05:19:41] <sustrik>	it's not your case, afaiu, as you are an consultant not a software provider
| [Tuesday 12 April 2011] [05:20:04] <sustrik>	but others may use 0mq in different ways
| [Tuesday 12 April 2011] [05:20:27] <sustrik>	say, adding a set of specific patches and keeping them off-tree
| [Tuesday 12 April 2011] [05:20:43] <sustrik>	to get a "enterprise-grade distro" or whatever
| [Tuesday 12 April 2011] [05:20:52] <mikko>	that's different from upstream-development in my opinion
| [Tuesday 12 April 2011] [05:21:10] <mikko>	what i think is valuable is making contributing as easy and predictable as possible
| [Tuesday 12 April 2011] [05:21:19] <mikko>	so that people are drawn into the community
| [Tuesday 12 April 2011] [05:21:28] <mikko>	rather than alienated by red tape and process
| [Tuesday 12 April 2011] [05:21:35] <sustrik>	yes
| [Tuesday 12 April 2011] [05:21:40] <mikko>	well, unpredictable process
| [Tuesday 12 April 2011] [05:21:48] <sustrik>	but that also means stabilisation of the codebase
| [Tuesday 12 April 2011] [05:21:54] <sustrik>	so that's easy to catch up
| [Tuesday 12 April 2011] [05:21:58] <mikko>	not necessarily
| [Tuesday 12 April 2011] [05:22:17] <mikko>	this is how i see it:
| [Tuesday 12 April 2011] [05:22:43] <mikko>	a user finds a bug
| [Tuesday 12 April 2011] [05:22:46] <mikko>	debugs
| [Tuesday 12 April 2011] [05:22:51] <mikko>	finds a solution and creates a patch
| [Tuesday 12 April 2011] [05:23:04] <mikko>	that patch should be really easy to contribute
| [Tuesday 12 April 2011] [05:23:20] <mikko>	we shouldn't care whether it's github pull request, patch to mailing-list etc
| [Tuesday 12 April 2011] [05:23:39] <mikko>	we as the developers should take the pain of managing this
| [Tuesday 12 April 2011] [05:23:49] <mikko>	to make it as easy as possible to users to contribute
| [Tuesday 12 April 2011] [05:24:55] <mikko>	i can see that we follow a proven process (linux kernel)
| [Tuesday 12 April 2011] [05:25:04] <mikko>	but we don't have thousands of contributors
| [Tuesday 12 April 2011] [05:25:20] <mikko>	we got handful and our goal should be to get people working with the code
| [Tuesday 12 April 2011] [05:25:26] <mikko>	and have them sucked in
| [Tuesday 12 April 2011] [05:25:42] <sustrik>	otoh, if you create a new process, you are likely to mess it up
| [Tuesday 12 April 2011] [05:25:58] <sustrik>	that could be pretty bad especially if the legal part gets wrong
| [Tuesday 12 April 2011] [05:26:41] <sustrik>	that's what i am worried about with github pull requests: basically, out legal paperowrk is handled by a 3rd party
| [Tuesday 12 April 2011] [05:26:58] <sustrik>	that can go out of business tomorrow
| [Tuesday 12 April 2011] [05:27:10] <mikko>	does FSF give help on these kind of issues?
| [Tuesday 12 April 2011] [05:28:01] <sustrik>	i think they are pretty busy and unlikely to give advise in specific cases
| [Tuesday 12 April 2011] [05:29:57] <sustrik>	anyway, let's discuss this face-to-face
| [Tuesday 12 April 2011] [05:30:28] <mikko>	are you going to brussels on 9th?
| [Tuesday 12 April 2011] [05:30:32] <ianbarber>	10th
| [Tuesday 12 April 2011] [05:30:46] <ianbarber>	is the conf, but i see your point :)
| [Tuesday 12 April 2011] [05:30:46] <sustrik>	yes
| [Tuesday 12 April 2011] [05:31:12] <mikko>	ianbarber: you flying or train?
| [Tuesday 12 April 2011] [05:31:17] <sustrik>	when are you arriving/leaving, guys?
| [Tuesday 12 April 2011] [05:31:25] <mikko>	i'm flexible
| [Tuesday 12 April 2011] [05:31:39] <mikko>	might arrive on afternoon / evening of 9th
| [Tuesday 12 April 2011] [05:31:53] <sustrik>	i have to spend at least one night there
| [Tuesday 12 April 2011] [05:32:03] <sustrik>	no way to get from BTX to BXL and back in a single day
| [Tuesday 12 April 2011] [05:32:31] <sustrik>	BTS*
| [Tuesday 12 April 2011] [05:32:38] <sustrik>	so the question is whether it's better to stay from 9 to 10
| [Tuesday 12 April 2011] [05:32:43] <sustrik>	or from 10 to 11
| [Tuesday 12 April 2011] [05:32:44] <ianbarber>	i'm not staying, in and out on the 10th on the train
| [Tuesday 12 April 2011] [05:32:55] <sustrik>	ok, i see
| [Tuesday 12 April 2011] [05:33:07] <ianbarber>	i'm sure people will be around though
| [Tuesday 12 April 2011] [05:33:08] <mikko>	thats like hit'n'run
| [Tuesday 12 April 2011] [05:33:20] <ianbarber>	mikko: i'm doing 1 day of DPC this year. boom.
| [Tuesday 12 April 2011] [05:33:52] <mikko>	thats the problem of being a popular conference speaker
| [Tuesday 12 April 2011] [05:33:55] <ianbarber>	if i had the time, i'd stay the evening of the 10th, for more drinking and likely some good breakfast discussion/waffels
| [Tuesday 12 April 2011] [05:33:56] <mikko>	so many commitments
| [Tuesday 12 April 2011] [05:34:34] <mikko>	i was thinking about renting skills matter in london at some point
| [Tuesday 12 April 2011] [05:34:38] <mikko>	and have a mini-conference
| [Tuesday 12 April 2011] [05:34:44] <mikko>	maybe some time summer
| [Tuesday 12 April 2011] [05:35:27] <sustrik>	why not
| [Tuesday 12 April 2011] [05:35:35] <ianbarber>	mikko: definitely would be up for that, happy to help organise
| [Tuesday 12 April 2011] [05:35:49] <so_solid_moo>	london \o/
| [Tuesday 12 April 2011] [05:36:23] <ianbarber>	on that front, we should organise a london pubmeet for june
| [Tuesday 12 April 2011] [05:36:49] <mikko>	ianbarber: my liver can't take another this soon
| [Tuesday 12 April 2011] [05:36:51] <mikko>	:)
| [Tuesday 12 April 2011] [05:36:54] <ianbarber>	hehe
| [Tuesday 12 April 2011] [06:01:04] <xs>	hi, i'm randomly getting Assertion failed: new_sndbuf > old_sndbuf (mailbox.cpp:183) with pyzmq 2.1.2, any ideas?
| [Tuesday 12 April 2011] [06:01:54] <mikko>	ianbarber: heading out, will give you a rin
| [Tuesday 12 April 2011] [06:01:56] <mikko>	g
| [Tuesday 12 April 2011] [06:08:48] <sustrik>	xs: increase default socket buffers on your OS
| [Tuesday 12 April 2011] [06:12:23] <xs>	sustrik: does that require root access?
| [Tuesday 12 April 2011] [06:12:29] <xs>	(i'm using linux_
| [Tuesday 12 April 2011] [06:14:50] <xs>	hm. this code looks broken, from the linux manpage on tcp: "On individual connections, the socket buffer size must be set prior to the listen() or connect() calls in order to have it take effect. "
| [Tuesday 12 April 2011] [06:15:07] <xs>	yet this code appears to be changing it after connect/listen and expecting it to have an effect
| [Tuesday 12 April 2011] [06:20:28] <xs>	
| [Tuesday 12 April 2011] [06:37:23] <sustrik>	xs: http://www.zeromq.org/docs:tuning-zeromq
| [Tuesday 12 April 2011] [07:33:36] <xs>	sustrik: i found that, it's not help
| [Tuesday 12 April 2011] [07:33:44] <xs>	it seems zeromq is broken
| [Tuesday 12 April 2011] [07:33:49] <xs>	what a waste of time this has been
| [Tuesday 12 April 2011] [07:35:37] <ianbarber>	where are you seeing the code changing it after connect/listen?
| [Tuesday 12 April 2011] [08:10:15] <xs>	ianbarber: zmq::mailbox_t::send in src/mailbox.cpp afaict
| [Tuesday 12 April 2011] [08:13:12] <xs>	anyways, i give up on zeromq
| [Tuesday 12 April 2011] [09:57:18] <NikolaVeber>	evax, there?
| [Tuesday 12 April 2011] [09:59:21] <evax>	yes
| [Tuesday 12 April 2011] [10:01:05] <NikolaVeber>	do you have a minute, I'm struggling with running the perf code
| [Tuesday 12 April 2011] [10:01:25] <NikolaVeber>	I'm trying out what u suggested yesterday
| [Tuesday 12 April 2011] [10:02:16] <NikolaVeber>	as I understood it, the remote_lat.erl for example should be run as a shell script?
| [Tuesday 12 April 2011] [10:02:51] <NikolaVeber>	~/erlzmq2$ ./perf/remote_lat_active.erl
| [Tuesday 12 April 2011] [10:04:36] <NikolaVeber>	returns 
| [Tuesday 12 April 2011] [10:04:36] <NikolaVeber>	escript: exception error: {function_clause,[{local,main,[[]]}]}
| [Tuesday 12 April 2011] [10:04:36] <NikolaVeber>	  in function  escript:code_handler/4
| [Tuesday 12 April 2011] [10:04:36] <NikolaVeber>	  in call from erl_eval:local_func/5
| [Tuesday 12 April 2011] [10:04:36] <NikolaVeber>	  in call from escript:interpret/4
| [Tuesday 12 April 2011] [10:04:38] <NikolaVeber>	  in call from escript:start/1
| [Tuesday 12 April 2011] [10:04:40] <NikolaVeber>	  in call from init:start_it/1
| [Tuesday 12 April 2011] [10:04:42] <NikolaVeber>	  in call from init:start_em/1
| [Tuesday 12 April 2011] [10:05:06] <evax>	you should run it with escript
| [Tuesday 12 April 2011] [10:05:18] <evax>	escript perf/remote_lat_active.erl ...
| [Tuesday 12 April 2011] [10:05:53] <NikolaVeber>	ok... I think I messed up the arguments
| [Tuesday 12 April 2011] [10:06:05] <NikolaVeber>	but hold on, if I have, results are just about there :)I
| [Tuesday 12 April 2011] [10:08:01] <NikolaVeber>	what is supposed to be running on the other part as a listener?
| [Tuesday 12 April 2011] [10:08:54] <NikolaVeber>	I have both erl and c++ perf code on both machines ready
| [Tuesday 12 April 2011] [10:09:08] <evax>	you should read this if you haven't yet: http://www.zeromq.org/results:perf-howto
| [Tuesday 12 April 2011] [10:09:40] <NikolaVeber>	tx
| [Tuesday 12 April 2011] [10:11:00] <NikolaVeber>	got it! 
| [Tuesday 12 April 2011] [10:11:20] <NikolaVeber>	are you interested in any specific parameters?
| [Tuesday 12 April 2011] [10:19:02] <evax>	can you generate some graphs with the included python script and post them somewhere ?
| [Tuesday 12 April 2011] [10:20:37] <NikolaVeber>	sure
| [Tuesday 12 April 2011] [10:23:23] <evax>	you'll have to edit it to work accross machines
| [Tuesday 12 April 2011] [10:23:44] <evax>	(just ssh on of the commands)
| [Tuesday 12 April 2011] [10:23:50] <evax>	*one
| [Tuesday 12 April 2011] [10:25:28] <NikolaVeber>	remotecmd = "escript perf/remote_lat"+(active and "_active" or "")+".erl" \
| [Tuesday 12 April 2011] [10:25:28] <NikolaVeber>	                " tcp://localhost:1234 "+str(msgsize)+" "+str(msgcount)
| [Tuesday 12 April 2011] [10:25:32] <NikolaVeber>	this line?
| [Tuesday 12 April 2011] [10:26:43] <NikolaVeber>	sorry, I get what you mean
| [Tuesday 12 April 2011] [12:30:39] <lazyshot>	when trying to create a push socket in node.js i get: Assertion failed: rc == 0 (zmq_connecter.cpp:48)
| [Tuesday 12 April 2011] [12:30:43] <lazyshot>	is this a known issue?
| [Tuesday 12 April 2011] [12:31:00] <lazyshot>	or does anyone know of a solution?
| [Tuesday 12 April 2011] [13:03:40] <sustrik>	lazyshot: what version of 0mq are you using?
| [Tuesday 12 April 2011] [13:04:40] <sustrik>	it has something to do with address resolution
| [Tuesday 12 April 2011] [13:04:51] <sustrik>	presumably it fails in connect or bind call
| [Tuesday 12 April 2011] [13:15:15] <jdroid->	One of the python examples on the docs is incorrect
| [Tuesday 12 April 2011] [13:15:16] <jdroid->	http://zguide.zeromq.org/py:asyncsrv
| [Tuesday 12 April 2011] [13:15:24] <jdroid->	(notice the init function)
| [Tuesday 12 April 2011] [13:24:20] <sustrik>	jdroid-: send a note to the mailing list
| [Tuesday 12 April 2011] [13:42:14] <andy_dawson>	Hi, excuse my noobness. when restarting an application I infrequently get "Error - Failed to bind the ZMQ: Address already in use" there isn't anything using zmq except this (test) applicatoin - how to I forcibly restart/release all 0mq activity?
| [Tuesday 12 April 2011] [13:47:31] <Toba>	did you try turning it off and on again?
| [Tuesday 12 April 2011] [13:49:26] <andy_dawson>	what are you referring to?
| [Tuesday 12 April 2011] [13:52:22] <andy_dawson>	if I stop the app (photon php) and stop mongrel2 and kill any processes which look like thy might be related - when I try to then start the application it fails because ... Address already in use
| [Tuesday 12 April 2011] [13:53:09] <andy_dawson>	so rather than blindly killing processes I hope there's a better way(R) :)
| [Tuesday 12 April 2011] [13:53:35] <tproa>	use your operating system's flavor of "what process is bound to this port"?
| [Tuesday 12 April 2011] [13:54:25] <Toba>	netstat/sockstat
| [Tuesday 12 April 2011] [14:00:52] <andy_dawson>	netstat doesn't show anything for the port the app is trying to bind to. maybe I've managed to try and bind twice
| [Tuesday 12 April 2011] [14:01:39] <andy_dawson>	changing the port number doesn't make any difference either.. odd
| [Tuesday 12 April 2011] [14:01:44] <Toba>	could be the classic 'process died in an ugly way, nobody can bind to it for a bit' issue
| [Tuesday 12 April 2011] [14:01:48] <Toba>	ok
| [Tuesday 12 April 2011] [14:01:49] <Toba>	you're doing it wrong I think
| [Tuesday 12 April 2011] [14:02:09] <andy_dawson>	probably. what do you mean
| [Tuesday 12 April 2011] [14:03:51] <lazyshot>	sustrik: i'm using 2.1.4 and i have a script spawning a process that connects to the parent via tcp, i'm guessing that the socket isn't binding before the child process is created
| [Tuesday 12 April 2011] [14:04:00] <lazyshot>	and attempting to connect
| [Tuesday 12 April 2011] [14:06:17] <sustrik>	what address are you passing to the connect?
| [Tuesday 12 April 2011] [14:08:40] <lazyshot>	tcp://127.0.0.1:7049
| [Tuesday 12 April 2011] [14:09:01] <lazyshot>	which upon netstat -l it shows that it's listening on that port
| [Tuesday 12 April 2011] [14:10:16] <lazyshot>	it's also throwing an error that the zeromq object is undefined, but that's when it still attempts to send
| [Tuesday 12 April 2011] [14:10:36] <lazyshot>	this is in node.js, btw
| [Tuesday 12 April 2011] [14:33:35] <isvara>	Hi. I was thinking zmq would be an excellent protocol to build upon for a chat server. My thought was that a client would connect to a REQ/REP channel to authenticate and be given a session ID (and to send events), then connect to a PUB/SUB channel and subscribe to its session ID to receive events. However, it seems that you can simply subscribe to *all* messages, which makes that idea invalid. What would be the correct way to do this?
| [Tuesday 12 April 2011] [14:44:00] <isvara>	Oh. PUB/SUB is filtered on the subscriber side anyway, so that's definitely the wrong way to do it.
| [Tuesday 12 April 2011] [15:01:37] <eyeris>	I've built the zeromq library. Now I'm getting a bunch of undefined reference errors when trying to build pyzmq. The build script suggests that I don't have the dev files installed for either python or zeromq, but I do. I've tried with the newest zeromq and pyzmq from git and the 2.1.4 packages for both.
| [Tuesday 12 April 2011] [15:01:56] <eyeris>	Here's a paste of the errors and an ls of the files it suspects are missing: http://pastebin.ca/2045542
| [Tuesday 12 April 2011] [15:04:37] <isvara>	Perhaps because you're compiling with 'cc', so it's not linking with the C++ libraries.
| [Tuesday 12 April 2011] [15:05:16] <isvara>	How did you kick off the build, and what platform are you on?
| [Tuesday 12 April 2011] [15:05:33] <isvara>	Cygwin?
| [Tuesday 12 April 2011] [15:05:41] <eyeris>	That would make sense. That was my initial reaction too, but the build message says I need a C compiler.
| [Tuesday 12 April 2011] [15:05:52] <eyeris>	Yes, cygwin -- I should have mentioned that
| [Tuesday 12 April 2011] [15:06:34] <isvara>	How did you build it? (I don't know what the process is, because I used the Python package that builds it statically.)
| [Tuesday 12 April 2011] [15:07:13] <eyeris>	./configure && make && make install
| [Tuesday 12 April 2011] [15:07:36] <isvara>	Can you paste the output from configure?
| [Tuesday 12 April 2011] [15:09:21] <eyeris>	Sure, here's the most recent attempt, with 2.1.4: http://pastebin.ca/2045544
| [Tuesday 12 April 2011] [15:09:54] <eyeris>	The --enable-shared is the default, I just added it to be paranoid
| [Tuesday 12 April 2011] [15:11:45] <isvara>	Well, it certainly detects that you have g++.
| [Tuesday 12 April 2011] [15:12:40] <eyeris>	Yeah, the zeromq builds fine, using g++
| [Tuesday 12 April 2011] [15:12:48] <eyeris>	It's the pyzmq C extension that fails
| [Tuesday 12 April 2011] [15:14:52] <isvara>	Looks like it's building vers.exe that is failing.
| [Tuesday 12 April 2011] [15:15:16] <isvara>	cc detect/vers.o -L/usr/local/lib -Wl,-R/usr/local/lib -lzmq -o detect/vers.exe
| [Tuesday 12 April 2011] [15:15:24] <isvara>	I wonder what would happen if you added a -lc++ to that.
| [Tuesday 12 April 2011] [15:15:37] <isvara>	Or -lstdc++ or whatever it is (it's been a while).
| [Tuesday 12 April 2011] [15:16:59] <eyeris>	I tried to export CC=g++ (which implies linking to the C++ stdlib), which did not change anything
| [Tuesday 12 April 2011] [15:17:42] <eyeris>	Oh, nvm, the cygwin build doesn't use CC
| [Tuesday 12 April 2011] [15:23:47] <sustrik>	what's missing is definitely -lstdc++
| [Tuesday 12 April 2011] [15:23:58] <sustrik>	no experience with cygwin though
| [Tuesday 12 April 2011] [15:36:42] <isvara>	eyeris: Can you just skip it? Do you need vers.exe? Or does other stuff fail too?
| [Tuesday 12 April 2011] [15:40:40] <eyeris>	Perhaps I could skip it. I have no idea what vers.exe does.
| [Tuesday 12 April 2011] [15:41:04] <eyeris>	I'm still trying to figure out how to make it use stdc++ lib
| [Tuesday 12 April 2011] [15:41:23] <eyeris>	It doesn't use CFLAGS or CXXFLAGS
| [Tuesday 12 April 2011] [15:42:05] <eyeris>	It also complains with I pass -Xlinker
| [Tuesday 12 April 2011] [15:46:08] <eyeris>	Part of the problem may be that what would be /usr/lib/libstdc++ on my debian system is /bin/cygstdc++ on this cygwin install
| [Tuesday 12 April 2011] [15:52:12] <isvara>	If it was using the right driver, though (presumably g++), the driver would know what to link with implicitly.
| [Tuesday 12 April 2011] [15:54:46] <eyeris>	Right. That's why I was trying to make it run g++, since gcc would look for libstdc++.a, given -lstdc++
| [Tuesday 12 April 2011] [15:55:06] <eyeris>	I just noticed that my gcc and g++ packages are still v3.4
| [Tuesday 12 April 2011] [15:55:16] <eyeris>	That's probably (part of) the problem
| [Tuesday 12 April 2011] [16:05:02] <isvara>	Do you specifically need in Cygwin? Would a Visual Studio build or a Linux build in a VM be an option?
| [Tuesday 12 April 2011] [16:07:55] <eyeris>	The rest of the software is built around cygwin :/
| [Tuesday 12 April 2011] [23:39:36] <ilya>	can someone help by explaining to me which topology I should choose?  I'm looking to use 0mq as an remote control agent on the server.  Numerous clients will connect and issue commands.  Server will perform various commands and reply.  pub/sub would be fine if we didn't need the reply piece, but I'd like to be able to use more of req/rep style, but without blocking the server.
| [Tuesday 12 April 2011] [23:41:01] <ilya>	I can manage threads/processes myself and start up enough processes to handle the requests with req/rep, but I'm wondering if there is a way the 0mq can manage threads/processes.  (I'm using python bindings)
| [Tuesday 12 April 2011] [23:48:43] <ilya>	I've skimmed through the docs, but don't see much comprehensive info/examples.   Thanks.
| [Wednesday 13 April 2011] [02:27:01] <benoitc>	are some people using zeromq for internal message exchange in their appplication ?
| [Wednesday 13 April 2011] [02:28:48] <benoitc>	i wonder if it could be  areplacement to the queue I use to rewrite data data coming from one tcp source and sent to another
| [Wednesday 13 April 2011] [02:33:58] <sustrik>	yes, if you don't care about using 0MQ's wire protocol on top of TCP
| [Wednesday 13 April 2011] [02:39:22] <benoitc>	sustrik: well i've a tcp proxy that do transparent A -> B B->A, i would like to introduce a rewrite process between so I can do A -> C -> B C is rewriting dta from A before they are sent to B
| [Wednesday 13 April 2011] [02:41:43] <benoitc>	I wat to let the possibility to allows C to send data in a streaming fashion, so my idea is to introduce a REQ/REP zmq socket in the middle rather than queing messages and consume the queue in C and aving another queue filled by C that i consime to send to B
| [Wednesday 13 April 2011] [02:41:53] <benoitc>	not sure I'm clear
| [Wednesday 13 April 2011] [03:11:57] <cyball>	hi .... i've tried to start an ZMQQueue with jzmq but it seems not to work is there something known about that ? ... i use the ZeroMQ 2.1 GIT - Version and also the JZMQ GIT Version and the platform is OSX 10.6.7 ... i also have tried it on Gentoo the same result there is no binding happen for front and backend XREP and XREQ ... thx
| [Wednesday 13 April 2011] [03:23:24] <sustrik>	cyball: you should ask on the mailing list
| [Wednesday 13 April 2011] [03:23:33] <sustrik>	i am not sure any java guys are here
| [Wednesday 13 April 2011] [03:23:43] <sustrik>	benoitc: not really, sorry
| [Wednesday 13 April 2011] [03:24:20] <benoitc>	sustrik: basic idea is that i need to rewrite teh reqwest before sending it to the remote
| [Wednesday 13 April 2011] [03:24:34] <benoitc>	so this rewrite should be on the fly
| [Wednesday 13 April 2011] [03:24:39] <sustrik>	sure
| [Wednesday 13 April 2011] [03:24:42] <cyball>	sustrik: thx for the info :-)
| [Wednesday 13 April 2011] [03:24:43] <sustrik>	no problem with that
| [Wednesday 13 April 2011] [03:25:44] <benoitc>	and i have this weird idea to use a zmq socket instead of impleting my own app level using 2 queue (one is to put the request and the second to publish the rewrite on the fly before it is sent 
| [Wednesday 13 April 2011] [03:25:58] <benoitc>	but it looks like over engineered :)
| [Wednesday 13 April 2011] [03:28:01] <sustrik>	it's easier to create a device of your own
| [Wednesday 13 April 2011] [03:28:12] <sustrik>	the device code is trivial
| [Wednesday 13 April 2011] [03:28:19] <sustrik>	some 20 lines of code
| [Wednesday 13 April 2011] [03:28:28] <sustrik>	you can add your rewrite logic to there
| [Wednesday 13 April 2011] [03:33:04] <benoitc>	mm not sure to follow , you mean putting my own code rather than using zmq ?
| [Wednesday 13 April 2011] [03:48:01] <benoitc>	i'm lost now :)
| [Wednesday 13 April 2011] [03:50:09] <benoitc>	sustrik: are you speaking about zmq device here 
| [Wednesday 13 April 2011] [03:50:11] <benoitc>	?
| [Wednesday 13 April 2011] [03:50:35] <sustrik>	benoitc: 0mq "device" is a concept
| [Wednesday 13 April 2011] [03:50:50] <sustrik>	you can either use one delivered with the library
| [Wednesday 13 April 2011] [03:51:00] <sustrik>	or write your own on top of 0MQ sockets
| [Wednesday 13 April 2011] [03:51:12] <sustrik>	the implementation of device is trivial
| [Wednesday 13 April 2011] [03:51:18] <sustrik>	let me find the code...
| [Wednesday 13 April 2011] [03:52:17] <sustrik>	https://github.com/zeromq/zeromq2-1/blob/master/src/device.cpp
| [Wednesday 13 April 2011] [03:52:22] <benoitc>	k thanks 
| [Wednesday 13 April 2011] [03:52:25] <sustrik>	it's C so it's rather long
| [Wednesday 13 April 2011] [03:52:38] <sustrik>	but most of it is just error handling and somesuch
| [Wednesday 13 April 2011] [03:52:45] <benoitc>	sorry my question was more if you were still speaking about zmq, was last a minute or two :)
| [Wednesday 13 April 2011] [03:52:57] <benoitc>	looking at the code
| [Wednesday 13 April 2011] [03:53:13] <sustrik>	my point is you can take that code and fill in youtr rewrite logic
| [Wednesday 13 April 2011] [03:53:49] <sustrik>	if you are not using multipart messages the code gets even simpler
| [Wednesday 13 April 2011] [03:54:08] <benoitc>	ok looks good, thanks a lot :)
| [Wednesday 13 April 2011] [07:46:10] <NikolaVeber>	erlang bindings benchmark over the gbit network http://nikolaveber.blogspot.com/
| [Wednesday 13 April 2011] [07:52:23] <sustrik>	NikolaVeber: what about linking the article from zeromq.org?
| [Wednesday 13 April 2011] [07:52:42] <NikolaVeber>	sure, forgot it, sorry
| [Wednesday 13 April 2011] [07:52:56] <sustrik>	There's a "performance" section there...
| [Wednesday 13 April 2011] [07:53:17] <sustrik>	http://www.zeromq.org/area:results
| [Wednesday 13 April 2011] [07:53:40] <locklace>	is there a proper wire protocol spec for zeromq
| [Wednesday 13 April 2011] [07:54:24] <sustrik>	over tcp?
| [Wednesday 13 April 2011] [07:54:39] <sustrik>	have a look at zmq_tcp(7)
| [Wednesday 13 April 2011] [07:54:44] <locklace>	over everything, ideally
| [Wednesday 13 April 2011] [07:54:59] <sustrik>	then there's protocol for packet based unreliable transports
| [Wednesday 13 April 2011] [07:55:08] <sustrik>	can be found at zmq_pgm(7)
| [Wednesday 13 April 2011] [07:55:30] <locklace>	no udp transport support yet, is that right?
| [Wednesday 13 April 2011] [07:55:48] <sustrik>	nope
| [Wednesday 13 April 2011] [07:56:06] <sustrik>	you are welcome to give it a try :)
| [Wednesday 13 April 2011] [07:56:43] <locklace>	tcp is pretty heavyweight/restricted for a lot of app classes, so ability to run zmq over other internet transports would be very useful
| [Wednesday 13 April 2011] [07:57:06] <locklace>	but it's not clear to me how much of the reliability logic would then need to be added to zmq itself
| [Wednesday 13 April 2011] [07:57:11] <bwaine_>	hello
| [Wednesday 13 April 2011] [07:57:14] <sustrik>	what's internet transport?
| [Wednesday 13 April 2011] [07:57:25] <sustrik>	hi
| [Wednesday 13 April 2011] [07:57:38] <locklace>	anything running over ip
| [Wednesday 13 April 2011] [07:57:42] <sustrik>	tcp?
| [Wednesday 13 April 2011] [07:57:50] <locklace>	sctp is probably a better actual fit for a lot of what zmq is used for, other than that most deployed networks don't know how to deal with it
| [Wednesday 13 April 2011] [07:58:04] <bwaine_>	a quick question. Im using the PHP bindings. Has anyone created a class file netbeans can use to provide auto complete for ZMQ?
| [Wednesday 13 April 2011] [07:58:13] <bwaine_>	If not I'll be happy to make it :0
| [Wednesday 13 April 2011] [07:58:20] <sustrik>	mpales was contemplating writing an sctp transport
| [Wednesday 13 April 2011] [07:58:31] <sustrik>	you may ask him what's the status quo
| [Wednesday 13 April 2011] [07:58:46] <locklace>	it's pretty silly to start (as one usually does) with message-based delivery requirements, and then have to convert messages to/from the tcp "byte stream" abstraction
| [Wednesday 13 April 2011] [07:59:26] <NikolaVeber>	sustrik, I have linked the results section in the blogpost. This isn't as comprehensive as other benchmarks, I'm not sure if it belongs on that site..
| [Wednesday 13 April 2011] [08:00:00] <sustrik>	why not?
| [Wednesday 13 April 2011] [08:00:19] <sustrik>	even if it's not perfect, it's still something people can benefit from
| [Wednesday 13 April 2011] [08:00:26] <NikolaVeber>	ok :)
| [Wednesday 13 April 2011] [08:01:00] <NikolaVeber>	can I link it myself?
| [Wednesday 13 April 2011] [08:01:18] <sustrik>	sure
| [Wednesday 13 April 2011] [08:01:21] <sustrik>	go on
| [Wednesday 13 April 2011] [08:03:07] <sustrik>	NikolaVeber: looks like you are from formet yougoslavia; where from exactly?
| [Wednesday 13 April 2011] [08:03:12] <sustrik>	former*
| [Wednesday 13 April 2011] [08:03:15] <NikolaVeber>	serbia
| [Wednesday 13 April 2011] [08:03:25] 	 * sustrik is from slovakia
| [Wednesday 13 April 2011] [08:03:32] <NikolaVeber>	cool! 
| [Wednesday 13 April 2011] [08:03:38] <NikolaVeber>	I was in bratislava, loved it!
| [Wednesday 13 April 2011] [08:03:48] <sustrik>	never been in beograd
| [Wednesday 13 April 2011] [08:03:54] <sustrik>	one day i'll get there
| [Wednesday 13 April 2011] [08:04:19] <NikolaVeber>	hehe, I organized java conferences there a couple years ago
| [Wednesday 13 April 2011] [08:04:21] <locklace>	am i alone in thinking that the current zmq architecture blurs layer/functional boundaries that would better be cleanly separated?  specifically, transport-type functions like socket reliability and topology with message routing
| [Wednesday 13 April 2011] [08:04:44] <NikolaVeber>	we might have had a zmq talk, but I wasn't working with it back then
| [Wednesday 13 April 2011] [08:04:56] <sustrik>	next time
| [Wednesday 13 April 2011] [08:05:01] <NikolaVeber>	sure :)
| [Wednesday 13 April 2011] [08:05:04] <sustrik>	:)
| [Wednesday 13 April 2011] [08:05:35] <NikolaVeber>	im running an erlang -> c++ test right now, I'll make an update and post all together..
| [Wednesday 13 April 2011] [08:05:42] <sustrik>	locklace: there's no reliability in 0mq atm
| [Wednesday 13 April 2011] [08:05:55] <locklace>	iow it looks to me like zmq wants to be both a "network layer" and a "transport layer" but mixes the issues between the two together.  maybe i just don't "get it" yet
| [Wednesday 13 April 2011] [08:06:37] <sustrik>	it's meant to be an L5 layer, above the two mentioned
| [Wednesday 13 April 2011] [08:08:10] <locklace>	well sure, that's where it sits in practice, but in reality what you have is basically another network+transport layer that sits on top of the existing L3/L4
| [Wednesday 13 April 2011] [08:08:25] <locklace>	tcp connections (for instance) just become your links at this new layer
| [Wednesday 13 April 2011] [08:08:57] <sustrik>	true
| [Wednesday 13 April 2011] [08:09:03] <sustrik>	i don't see an alternative though
| [Wednesday 13 April 2011] [08:09:38] <locklace>	and you end up having to solve all the same kinds of problems that existing L3/L4 layers do, like addressing/identifiers, routing, and end-to-end message delivery semantics
| [Wednesday 13 April 2011] [08:09:49] <locklace>	oh, it's not a criticism; it's in a sense the only possibility :)
| [Wednesday 13 April 2011] [08:10:20] <locklace>	if there's a criticism here, it's only that zmq doesn't appear to explicitly recognise this fact, and split its functionality up accordingly along well-known boundaries
| [Wednesday 13 April 2011] [08:10:28] <sustrik>	the problem is that 0mq deals with routing based on business logic
| [Wednesday 13 April 2011] [08:10:41] <sustrik>	whereas L3 deals with routing based on network logic
| [Wednesday 13 April 2011] [08:11:07] <sustrik>	it's not clear whether the two can be merged in any way
| [Wednesday 13 April 2011] [08:11:22] <locklace>	i think (in short) that they can and should be
| [Wednesday 13 April 2011] [08:11:27] <sustrik>	how?
| [Wednesday 13 April 2011] [08:12:16] <locklace>	there's a class of applications that would really want/need to take advantage of technical network-layer routing functionality; but zmq currently doesn't support that so you'd have to reinvent routing protocols on top of it
| [Wednesday 13 April 2011] [08:12:49] <sustrik>	the protocols on 0mq layer are based on business logic
| [Wednesday 13 April 2011] [08:12:54] <sustrik>	that's not visible at L3
| [Wednesday 13 April 2011] [08:13:04] <sustrik>	if you try to merge the two
| [Wednesday 13 April 2011] [08:13:14] <sustrik>	you have to either propagate business logic to L3
| [Wednesday 13 April 2011] [08:13:36] <sustrik>	virtually asking network admins to understand business logic of the apps running on top of the network
| [Wednesday 13 April 2011] [08:14:02] <sustrik>	or other way round, you would have to implement network routing at L5
| [Wednesday 13 April 2011] [08:14:16] <sustrik>	which means duplicating the whole IP infrastructure
| [Wednesday 13 April 2011] [08:15:03] <locklace>	that zmq does bus-log routing/topology is a great strength of it, but in its current form it blurs over all kinds of useful and well-established layer stack distinctions, like network vs. transport functionality
| [Wednesday 13 April 2011] [08:15:36] <sustrik>	feel free to propose an alternative :)
| [Wednesday 13 April 2011] [08:15:45] <locklace>	well, what i had in mind was closer to your second option - implementing a proper network layer in zmq - but one that wouldn't just duplicate ip
| [Wednesday 13 April 2011] [08:16:23] <sustrik>	you'll need thousands of manyears to get anywhere near the level the TCP/IP stack is at now
| [Wednesday 13 April 2011] [08:16:41] <locklace>	it looks to me (correct me if i'm wrong) that you're starting to run into a set of classic issues related to how you handle addressing/identifiers/routing, which you are having to grapple with, and which arise because you don't have a proper network layer
| [Wednesday 13 April 2011] [08:17:23] <sustrik>	depends on what you mean by "proper network layer"
| [Wednesday 13 April 2011] [08:17:33] <sustrik>	0mq routing is very different from IP routing
| [Wednesday 13 April 2011] [08:17:54] <sustrik>	as it deals with "business topologies"
| [Wednesday 13 April 2011] [08:18:03] <sustrik>	such as "NASDAQ stock quote feed"
| [Wednesday 13 April 2011] [08:18:41] <sustrik>	these topologies can contain large amount of nodes
| [Wednesday 13 April 2011] [08:19:02] <sustrik>	and the routing within the topology is based on an algorithm called "messaging pattern"
| [Wednesday 13 April 2011] [08:19:14] <sustrik>	there's no equivalent at L3
| [Wednesday 13 April 2011] [08:20:01] <locklace>	is it possible to connect a node up to a zmq network and send a message to another node identified by a globally-unique id that gets there efficiently?
| [Wednesday 13 April 2011] [08:20:09] <sustrik>	nope
| [Wednesday 13 April 2011] [08:20:37] <sustrik>	it works as a cloud
| [Wednesday 13 April 2011] [08:20:45] <sustrik>	you connect to the cloud
| [Wednesday 13 April 2011] [08:20:48] <sustrik>	send a message
| [Wednesday 13 April 2011] [08:20:53] <sustrik>	message gets somewhere
| [Wednesday 13 April 2011] [08:21:06] <locklace>	that's one of the fundamental problems/limitations at present imo :)
| [Wednesday 13 April 2011] [08:21:07] <locklace>	as there is a class of applications where you'd want to rely on the zmq network to do exactly that
| [Wednesday 13 April 2011] [08:21:27] <sustrik>	why not use standard L3/L4 for those apps?
| [Wednesday 13 April 2011] [08:21:45] <sustrik>	is seems to fullfil all the requirements nicely
| [Wednesday 13 April 2011] [08:22:25] <locklace>	i think there are advantages and disadvantages to having a "network layer" that "hard-codes" certain business logic or "messaging" patterns.  advantage is it makes it very easy for people who want to just use those common patterns; but it makes things very hard when you want to build new patterns because there isn't a proper layer to bulid them on
| [Wednesday 13 April 2011] [08:22:39] <locklace>	well, one reason is that the classic socket apis suck :)
| [Wednesday 13 April 2011] [08:23:09] <sustrik>	ha
| [Wednesday 13 April 2011] [08:23:29] <sustrik>	i think that's the core of the current discussion
| [Wednesday 13 April 2011] [08:23:40] <sustrik>	people want to use 0mq as a nice networking framework
| [Wednesday 13 April 2011] [08:23:51] <sustrik>	a peer to ACE or Boost.Asio
| [Wednesday 13 April 2011] [08:24:17] <sustrik>	which is a legitimate requirement, but it is not what 0mq is atm
| [Wednesday 13 April 2011] [08:24:38] <sustrik>	maybe separating the two aspects would be the right solution...
| [Wednesday 13 April 2011] [08:25:12] <locklace>	i see zmq as potentially solving a very wide class of problems, but in its current form it only solves a subset of that class well (traditional enterprise/business messaging) because that's what it was designed for, and it does it very well.  but because it also has a lot of features of a really nice generalised socket architecture/api-replacement, it could do a lot more, and the right way (i think) to do that is to separate its layers 
| [Wednesday 13 April 2011] [08:25:14] <locklace>	 more cleanly
| [Wednesday 13 April 2011] [08:25:16] <locklace>	if that makes sense
| [Wednesday 13 April 2011] [08:25:35] <sustrik>	yep
| [Wednesday 13 April 2011] [08:25:51] <sustrik>	generic networking helpers
| [Wednesday 13 April 2011] [08:25:58] <sustrik>	and the patterns on top of them
| [Wednesday 13 April 2011] [08:26:04] <locklace>	that would also allow for developer modularity, e.g. so you can have different sets of people working somewhat independently on the different layers and progress them in parallel
| [Wednesday 13 April 2011] [08:26:26] <guido_g>	utopia here we come
| [Wednesday 13 April 2011] [08:26:27] <locklace>	basically this is just classic good stack/layering/protocol design
| [Wednesday 13 April 2011] [08:27:01] <sustrik>	i was never interested in ACE/Boost.Asio side of the thing
| [Wednesday 13 April 2011] [08:27:19] <sustrik>	but it seems it would be helpful to have such layer
| [Wednesday 13 April 2011] [08:27:30] <sustrik>	you may try to separate the two
| [Wednesday 13 April 2011] [08:27:36] <sustrik>	but it's not a trivial task
| [Wednesday 13 April 2011] [08:28:06] <locklace>	well, since zmq already goes halfway or more toward giving the world a massively improved socket layer, it would be nice to see it evolve fully into that role...
| [Wednesday 13 April 2011] [08:28:09] <sustrik>	hi guido :)
| [Wednesday 13 April 2011] [08:28:20] <sustrik>	sure, give it a try
| [Wednesday 13 April 2011] [08:28:21] <guido_g>	hi sustrik 
| [Wednesday 13 April 2011] [08:29:21] <sustrik>	locklace: one problem you'll encounter is that the 0mq API niceness
| [Wednesday 13 April 2011] [08:29:32] <sustrik>	is a product of messaging patterns
| [Wednesday 13 April 2011] [08:29:38] <guido_g>	the world is full of projects with a broad and _general_ scope... unsurprisingly most of them are dead
| [Wednesday 13 April 2011] [08:29:51] <guido_g>	one of the best points of mq is it's focus
| [Wednesday 13 April 2011] [08:29:54] <sustrik>	by selecting a pattern, 0mq can do a lot of logic for you and never bothers you about it
| [Wednesday 13 April 2011] [08:30:34] <sustrik>	when you start exposing all the details you need for generic messaging via API you end up with something very similar to BSD socket API
| [Wednesday 13 April 2011] [08:30:54] <sustrik>	guido_g: well, that's my focus
| [Wednesday 13 April 2011] [08:30:59] <locklace>	so you'd end up with a complete and well-defined socket layer and api (effectively a new network+transport layer that treats classic L4 circuits as its links, and allows you to request different kinds of delivery semantics), and then a layer of "messaging patterns" on top of that which simply crystallise the most common use cases, but which can then easily be extended
| [Wednesday 13 April 2011] [08:31:07] <sustrik>	people are free to to try their own ideas
| [Wednesday 13 April 2011] [08:31:15] <sustrik>	but somehow that doesn't happen :)
| [Wednesday 13 April 2011] [08:31:37] <guido_g>	what a surprise
| [Wednesday 13 April 2011] [08:31:49] <sustrik>	:)
| [Wednesday 13 April 2011] [08:32:18] <sustrik>	locklace: try to do that; but recall the main motivation was that BSD socket API sucks
| [Wednesday 13 April 2011] [08:32:43] <sustrik>	so if you end up with equivalent or worse API, you've failed to achieve the goal
| [Wednesday 13 April 2011] [08:33:59] <locklace>	you could be right.  it's certainly plausible that attempting to generalise zmq would be a regression and not an improvement.  there's no question it would be tricky, but since it's already gone 3/4 of the way there or so, it doesn't look impossible to me
| [Wednesday 13 April 2011] [08:34:16] <locklace>	i guess what i'd like to know is what the plans are for the future in this regard
| [Wednesday 13 April 2011] [08:34:47] <sustrik>	no plans myself, but watch for discussion on the mailing list
| [Wednesday 13 April 2011] [08:34:52] <sustrik>	it seems to be a hot topic :0
| [Wednesday 13 April 2011] [08:34:56] <sustrik>	:)
| [Wednesday 13 April 2011] [08:35:13] <locklace>	yeah
| [Wednesday 13 April 2011] [08:35:51] <locklace>	when i see people grappling with classic network-layer problems like how to handle addressing and routing, then this where my thinking leads :)
| [Wednesday 13 April 2011] [08:37:24] <sustrik>	well, i'm coming from an enterprise-messaging sphere
| [Wednesday 13 April 2011] [08:37:43] <sustrik>	so i have enough experience with duplicit functionality
| [Wednesday 13 April 2011] [08:38:03] <locklace>	heh
| [Wednesday 13 April 2011] [08:38:06] <sustrik>	0mq actually evolved from classic enterprise messaging ideas
| [Wednesday 13 April 2011] [08:38:12] <sustrik>	by removing the duplicities
| [Wednesday 13 April 2011] [08:38:26] <sustrik>	almost everything didn't passed the duplicty test
| [Wednesday 13 April 2011] [08:38:29] <sustrik>	and was removed
| [Wednesday 13 April 2011] [08:38:34] <locklace>	i'm coming from core networking
| [Wednesday 13 April 2011] [08:38:43] <sustrik>	i've figured out
| [Wednesday 13 April 2011] [08:38:58] <sustrik>	what remained was messaging patterns
| [Wednesday 13 April 2011] [08:39:16] <sustrik>	as those cannot be delegated to upper layer (like transactions or serialisation)
| [Wednesday 13 April 2011] [08:39:26] <sustrik>	or to lower layer, like L3/L4
| [Wednesday 13 April 2011] [08:40:23] <locklace>	i think that's a good insight
| [Wednesday 13 April 2011] [08:40:29] <sustrik>	locklace: what's exactly is you area of experience?
| [Wednesday 13 April 2011] [08:40:45] <sustrik>	i'm kind of missing lower layer people in 0mq community
| [Wednesday 13 April 2011] [08:41:39] <locklace>	it just looks to me like zmq blurs that layer with what's effectively a "higher" L3/L4 set of functionality that's required to handle routing and reliability semantics.  and what i see from present discussions is that it's exactly this area that's giving you trouble at the moment, and it's happening because the layers are blurred
| [Wednesday 13 April 2011] [08:42:19] <locklace>	sustrik: core network architecture and platform/protocol design
| [Wednesday 13 April 2011] [08:42:41] <sustrik>	are you involved in ietf by chance?
| [Wednesday 13 April 2011] [08:42:53] <locklace>	yes
| [Wednesday 13 April 2011] [08:42:58] <sustrik>	nice
| [Wednesday 13 April 2011] [08:43:07] <sustrik>	been in prague?
| [Wednesday 13 April 2011] [08:43:17] <locklace>	very recently :)
| [Wednesday 13 April 2011] [08:43:21] <sustrik>	heh
| [Wednesday 13 April 2011] [08:43:42] <sustrik>	i've posted a notice on the mailing list about me being in prague...
| [Wednesday 13 April 2011] [08:43:49] <sustrik>	we could have had a beer
| [Wednesday 13 April 2011] [08:44:10] <locklace>	yeah, i didn't actually know about zmq until about two days ago
| [Wednesday 13 April 2011] [08:44:19] <sustrik>	pity
| [Wednesday 13 April 2011] [08:44:36] <sustrik>	anyway, my idea is to get patterns standardised in the future
| [Wednesday 13 April 2011] [08:44:51] <sustrik>	but there's a long way to go still
| [Wednesday 13 April 2011] [08:45:07] <locklace>	standardised how?
| [Wednesday 13 April 2011] [08:45:25] <sustrik>	hard to say
| [Wednesday 13 April 2011] [08:45:27] <sustrik>	one option is
| [Wednesday 13 April 2011] [08:45:38] <sustrik>	to start with fixing the semantics
| [Wednesday 13 April 2011] [08:46:08] <sustrik>	and providing that as a means for bridging existing messaging implementations into larger topologies
| [Wednesday 13 April 2011] [08:46:45] <sustrik>	the other option is to actually focus on the actual wire level protocol
| [Wednesday 13 April 2011] [08:47:08] <sustrik>	but that's kind of contentious, given there's a lot of existing messaging protocols out there
| [Wednesday 13 April 2011] [08:48:26] <locklace>	yes, it will be
| [Wednesday 13 April 2011] [08:48:54] <sustrik>	anyway, i think there'll be a lot of support for that kind of thing in the future
| [Wednesday 13 April 2011] [08:49:37] <sustrik>	the need for hardware-software interaction can even lead to need for actual binary protocol
| [Wednesday 13 April 2011] [08:49:41] <locklace>	but i'd still suggest it's the right way to do things; it actually doesn't matter whether X group of people think it's contentious, what matters is the discipline of writing it up in that form and subjecting it to the full community review process that enables
| [Wednesday 13 April 2011] [08:50:08] <sustrik>	yep
| [Wednesday 13 April 2011] [08:50:40] <sustrik>	what's your email btw?
| [Wednesday 13 April 2011] [08:50:52] <locklace>	i.e. if you can write the whole protocol up in draft form so it can be properly reviewed, you'll be able to emerge with a much better and more solid end result
| [Wednesday 13 April 2011] [08:50:53] <sustrik>	i'll ping you if anything interesting happens in this area
| [Wednesday 13 April 2011] [08:51:16] <locklace>	ok. i'll send you a note offline
| [Wednesday 13 April 2011] [08:51:20] <sustrik>	thanks
| [Wednesday 13 April 2011] [08:51:32] 	 * sustrik needs sould to form a bof :)
| [Wednesday 13 April 2011] [08:51:36] <sustrik>	souls*
| [Wednesday 13 April 2011] [08:52:04] <locklace>	yeah, but there's a lot of work needed to even get near that point
| [Wednesday 13 April 2011] [08:52:19] <sustrik>	ack
| [Wednesday 13 April 2011] [08:52:26] <locklace>	the write-up above and an initial public review cycle, mainly ;)
| [Wednesday 13 April 2011] [08:53:06] <sustrik>	yep, well get there
| [Wednesday 13 April 2011] [08:54:14] <locklace>	if you (or someone with the knowledge of zmq) is willing to put the work in to write it all up in draft form, i might be able to help as editor and with some process stuff
| [Wednesday 13 April 2011] [08:54:21] <mikko>	sustrik: http://sourceforge.net/projects/udt/forums/forum/393036/topic/4061830
| [Wednesday 13 April 2011] [08:54:55] <locklace>	i think you'll also find that once you have it down in that format, it will greatly improve the traction you get on design issues on the mailing list etc.
| [Wednesday 13 April 2011] [08:55:21] <sustrik>	mikko: i've seen that
| [Wednesday 13 April 2011] [08:55:24] <locklace>	traction is always *much* easier to achieve when people can comment on specific parts of draft text
| [Wednesday 13 April 2011] [08:55:34] <sustrik>	there doesn't seem to be an answer
| [Wednesday 13 April 2011] [08:55:44] <sustrik>	other than "coming soon"
| [Wednesday 13 April 2011] [08:56:08] <sustrik>	anyway, let's see, maybe the guy will really implement it
| [Wednesday 13 April 2011] [08:56:47] <sustrik>	locklace: yes, you are right
| [Wednesday 13 April 2011] [08:57:07] <sustrik>	the biggest problem with an initial draft is who to focus it on
| [Wednesday 13 April 2011] [08:57:22] <sustrik>	enterprise messaging devs are not participating on ietf
| [Wednesday 13 April 2011] [08:57:35] <sustrik>	while ietf folks have no idea of enterprise messaging
| [Wednesday 13 April 2011] [08:57:57] <sustrik>	and, additionally, 0mq-style messaging is no longer an enterprise messaging proper
| [Wednesday 13 April 2011] [08:58:01] <locklace>	well, my suggestion is to forget about targeting it at any specific group at the moment, but write it up in the format of an ietf draft
| [Wednesday 13 April 2011] [08:58:33] <locklace>	regardless of where it goes from there, that will be a major step in the right direction even just internally for the zmq project and mailing list
| [Wednesday 13 April 2011] [08:58:58] <sustrik>	yeah, it should probably be worded in the most generic way
| [Wednesday 13 April 2011] [08:59:05] <sustrik>	so that anyone can understand it
| [Wednesday 13 April 2011] [08:59:19] <sustrik>	but then, it would probably look like a vapourware
| [Wednesday 13 April 2011] [08:59:22] <sustrik>	oh my
| [Wednesday 13 April 2011] [08:59:56] <locklace>	yes, and writing it up in that format (a) helps you structure it as a proper protocol architecture, and (b) helps focus discussion
| [Wednesday 13 April 2011] [09:01:23] <sustrik>	ack
| [Wednesday 13 April 2011] [09:02:33] <locklace>	and of course, if it then does get edited into a shape fit for possible ietf work, that enables you to think about stuff like having a bof with a nonzero chance of success
| [Wednesday 13 April 2011] [09:03:55] <locklace>	this is probably obvious, but i'll say it anyway: the first thing the draft should address is the set of requirements.  in fact, the first version should probably be nothing *but* a set of requirements, which people can then argue over and loosely agree on before anything else is done
| [Wednesday 13 April 2011] [09:04:15] <sustrik>	yes, that's the plan
| [Wednesday 13 April 2011] [09:04:46] <sustrik>	the another interesting question is which area it should be dealt with in
| [Wednesday 13 April 2011] [09:05:02] <sustrik>	so far i am in contact with apps area guys
| [Wednesday 13 April 2011] [09:05:06] <locklace>	area?
| [Wednesday 13 April 2011] [09:05:24] <sustrik>	ietf area
| [Wednesday 13 April 2011] [09:05:45] <sustrik>	but the think is a bit lower layer
| [Wednesday 13 April 2011] [09:05:53] <sustrik>	somewhere between transport and apps
| [Wednesday 13 April 2011] [09:05:56] <locklace>	well let's just say there are good reasons why i said not to worry about targeting any particular group at the outset ;)
| [Wednesday 13 April 2011] [09:06:04] <sustrik>	:)
| [Wednesday 13 April 2011] [09:06:12] <locklace>	i really would not worry about that kind of thing at present, you have enough work to do without worrying about the organisational politics
| [Wednesday 13 April 2011] [09:06:44] <locklace>	get a sound technical draft put together first, worry about where it goes to later
| [Wednesday 13 April 2011] [09:07:11] <locklace>	it will be pretty much impossible to answer the "where should it go" question until the requirements and architecture are clear anyway
| [Wednesday 13 April 2011] [09:08:02] 	 * sustrik is up to writing the draft tomorrow
| [Wednesday 13 April 2011] [09:09:05] <locklace>	xml2rfc makes writing things up easy now, yay
| [Wednesday 13 April 2011] [09:09:36] <sustrik>	yep, i want to learn to use it
| [Wednesday 13 April 2011] [09:09:46] <locklace>	it will take you five minutes
| [Wednesday 13 April 2011] [09:09:46] <sustrik>	formatting drafts by hand is a pain
| [Wednesday 13 April 2011] [09:10:46] <locklace>	just go to xml.resource.org, submit the xml and it spits out text.  the actual xml schema is almost trivial, hit the "unofficial successor" link at the top of the page to get to the reference, and start with some existing draft .xml file as a template
| [Wednesday 13 April 2011] [09:11:41] <sustrik>	thx
| [Wednesday 13 April 2011] [09:44:40] <pantsman>	hi - it's great that there are windows binaries for pyzmq on its github downloads page, but I still need visual studio installed to run them - does this mean they're debug builds?
| [Wednesday 13 April 2011] [09:45:47] <sustrik>	why do you need msvc?
| [Wednesday 13 April 2011] [09:47:37] <pantsman>	sustrik, because without, the libzmq.dll that comes with the pyzmq installer can't find a DLL called Microsoft.VC90.DebugCRT
| [Wednesday 13 April 2011] [09:48:41] <sustrik>	yes, the library was compiled with debug CRT
| [Wednesday 13 April 2011] [09:49:01] <sustrik>	where have you got the binary from?
| [Wednesday 13 April 2011] [09:49:43] <pantsman>	I was using https://github.com/downloads/zeromq/pyzmq/pyzmq-2.1.4.win32-py2.7.msi
| [Wednesday 13 April 2011] [09:52:30] <sustrik>	no idea where that comes from
| [Wednesday 13 April 2011] [09:52:35] <sustrik>	mikko: are you there?
| [Wednesday 13 April 2011] [09:54:17] <sustrik>	hm, looks like he's not here
| [Wednesday 13 April 2011] [09:54:35] <sustrik>	pantsman: can you please complain about it on the mailing list?
| [Wednesday 13 April 2011] [09:55:38] <pantsman>	sustrik, sure
| [Wednesday 13 April 2011] [09:55:50] <sustrik>	thanks
| [Wednesday 13 April 2011] [09:56:11] <guido_g>	mentioning pyzmq in the subject, as it seems to be a problem with pyzmq build
| [Wednesday 13 April 2011] [09:58:20] <mikko>	sustrik: yes
| [Wednesday 13 April 2011] [09:58:39] <NikolaVeber>	sustrik, I have linked the post at http://www.zeromq.org/area:results,
| [Wednesday 13 April 2011] [10:04:55] <sustrik>	mikko: any idea where that binary comes from?
| [Wednesday 13 April 2011] [10:05:02] <sustrik>	NikolaVeber: thanks
| [Wednesday 13 April 2011] [10:05:11] <NikolaVeber>	np! :)
| [Wednesday 13 April 2011] [10:08:32] <evax>	NikolaVeber: the last test is fine, notice the 1e7 on top of the graph :)
| [Wednesday 13 April 2011] [10:08:58] <NikolaVeber>	oh, yeah! :)
| [Wednesday 13 April 2011] [10:09:14] <NikolaVeber>	I'll update the note
| [Wednesday 13 April 2011] [10:10:02] <NikolaVeber>	done
| [Wednesday 13 April 2011] [10:10:42] <sustrik>	 btw, the order of graphs is somewhat chaotic
| [Wednesday 13 April 2011] [10:14:18] <NikolaVeber>	just done that
| [Wednesday 13 April 2011] [10:18:50] <mikko>	sustrik: the .msi?
| [Wednesday 13 April 2011] [10:18:56] <sustrik>	yes
| [Wednesday 13 April 2011] [10:19:05] <mikko>	must be minrk / bgranger
| [Wednesday 13 April 2011] [10:19:09] <sustrik>	i see
| [Wednesday 13 April 2011] [10:19:09] <mikko>	i would imagine
| [Wednesday 13 April 2011] [10:19:20] <mikko>	Microsoft.VC90.DebugCRT 
| [Wednesday 13 April 2011] [10:19:24] <mikko>	sounds like it's a debug build
| [Wednesday 13 April 2011] [10:19:35] <mikko>	rather than a release build
| [Wednesday 13 April 2011] [10:19:38] <sustrik>	or a bad CRT option passed to the compiler
| [Wednesday 13 April 2011] [10:20:42] <sustrik>	anyway, it's reported on the ML
| [Wednesday 13 April 2011] [10:20:54] <sustrik>	it's up to pyzmq guys noqw
| [Wednesday 13 April 2011] [10:32:00] <pantsman>	fortunately not a big problem for me since I can build libzmq.dll myself; however building pyzmq is something that's beyond me at the moment
| [Wednesday 13 April 2011] [10:48:51] <yawniek>	if i add zmq.SNDMORE with pyzmq the receiver does not get the message imediately but only after the last message of the multipart message has been sent off. shouldnt it be possible to stream multipart messages?
| [Wednesday 13 April 2011] [10:49:46] <yawniek>	err mybad
| [Wednesday 13 April 2011] [10:57:40] <sustrik>	yawniek: it's transactional
| [Wednesday 13 April 2011] [10:57:56] <sustrik>	message is treated as an atomic unit
| [Wednesday 13 April 2011] [10:58:19] <sustrik>	you either get whole message, or none of it
| [Wednesday 13 April 2011] [10:59:21] <yawniek>	ok. i want to build an interface for a database where the results should be streamable. so query gets sent and a stream of messages should come back. how should the architecture look like?
| [Wednesday 13 April 2011] [11:00:31] <sustrik>	the reply doesn't fit into memory, right?
| [Wednesday 13 April 2011] [11:01:19] <yawniek>	exactely
| [Wednesday 13 April 2011] [11:01:48] <sustrik>	0mq holds messages in memory
| [Wednesday 13 April 2011] [11:02:22] <sustrik>	so it's hard to work with a message that does not fit into it
| [Wednesday 13 April 2011] [11:02:35] <sustrik>	you can use XREQ/XREP to get a streaming like behaviour
| [Wednesday 13 April 2011] [11:02:48] <sustrik>	not nice, but doable
| [Wednesday 13 April 2011] [11:02:54] <sustrik>	check the guide
| [Wednesday 13 April 2011] [11:04:34] <yawniek>	yeah, im reading it over and over again. i think a two step process with PUSH/PULL socket for the streaming is a way but that gives some overhead
| [Wednesday 13 April 2011] [13:51:23] <yziquel>	is there any quick and fast way of knowing the ip of the host of a client socket that connects on a server? from the server?
| [Wednesday 13 April 2011] [13:56:22] <erickt>	yziquel: I don't believe that's exposed from the api
| [Wednesday 13 April 2011] [13:56:38] <yziquel>	ok. thanks.
| [Wednesday 13 April 2011] [13:58:51] <erickt>	you can get the identity for certain socket types. That's talked about here: http://zguide.zeromq.org/page:all
| [Wednesday 13 April 2011] [14:04:16] <yziquel>	what i really need is a directory of endpoints which is info to be served by a central server.
| [Wednesday 13 April 2011] [14:04:44] <yziquel>	erickt: so i'm wondering how to populate it precisely.
| [Wednesday 13 April 2011] [14:05:49] <mikko>	yziquel: there is a project aiming to do that
| [Wednesday 13 April 2011] [14:06:03] <mikko>	yziquel: but i think it's only a wiki-page has been written about it this far
| [Wednesday 13 April 2011] [15:01:23] <mpales>	hi
| [Wednesday 13 April 2011] [15:01:53] <mpales>	i have a question related to application design
| [Wednesday 13 April 2011] [15:02:08] <mpales>	anyone here?
| [Wednesday 13 April 2011] [15:03:07] <isvara>	I am here, but that probably doesn't help you.
| [Wednesday 13 April 2011] [15:09:53] <sustrik>	mpales: hi
| [Wednesday 13 April 2011] [15:10:44] <mpales>	sustrik: i am trying to create a messaging pattern and need a help
| [Wednesday 13 April 2011] [15:11:20] 	 * sustrik listens
| [Wednesday 13 April 2011] [15:11:24] <mpales>	the system should reassemble segmented messages and process them
| [Wednesday 13 April 2011] [15:11:50] <mpales>	i'd like to have several workers for reassembling
| [Wednesday 13 April 2011] [15:12:18] <mpales>	the point is that is a worker gets a segment, it should also receive all thge other segments
| [Wednesday 13 April 2011] [15:12:29] <mpales>	so i cannot use a plain round robin or lru
| [Wednesday 13 April 2011] [15:12:52] <sustrik>	why not multipart messages?
| [Wednesday 13 April 2011] [15:13:34] <mpales>	the application has no control over segments
| [Wednesday 13 April 2011] [15:13:40] <mpales>	they are the input
| [Wednesday 13 April 2011] [15:13:52] <mpales>	other clients sent them
| [Wednesday 13 April 2011] [15:14:22] <sustrik>	why don't they sent them as multipart msgs?
| [Wednesday 13 April 2011] [15:14:38] <mpales>	it's not a zmq based system
| [Wednesday 13 April 2011] [15:15:01] <sustrik>	ok, what's the problem with 0mq then?
| [Wednesday 13 April 2011] [15:15:23] <mpales>	how to route those segments
| [Wednesday 13 April 2011] [15:15:33] <sustrik>	i mean
| [Wednesday 13 April 2011] [15:15:40] <sustrik>	you get a list of segments
| [Wednesday 13 April 2011] [15:15:41] <mpales>	all segments with same id should go to the same worker
| [Wednesday 13 April 2011] [15:15:54] <sustrik>	then you send it to a worker as a multipart message
| [Wednesday 13 April 2011] [15:17:23] <mpales>	but all segments belong to the same message
| [Wednesday 13 April 2011] [15:17:42] <sustrik>	?
| [Wednesday 13 April 2011] [15:17:51] <sustrik>	i think i don't get it
| [Wednesday 13 April 2011] [15:17:58] <mpales>	oops, my mistake
| [Wednesday 13 April 2011] [15:18:07] <mpales>	segments belong to different messages
| [Wednesday 13 April 2011] [15:18:42] <guido_g>	create a map: source id -> mq worker
| [Wednesday 13 April 2011] [15:18:51] <sustrik>	aha
| [Wednesday 13 April 2011] [15:18:58] <sustrik>	you want stateful services
| [Wednesday 13 April 2011] [15:19:14] <mpales>	guido: that's also my idea
| [Wednesday 13 April 2011] [15:19:24] <mpales>	sustrik: yes
| [Wednesday 13 April 2011] [15:19:29] <sustrik>	there's no easy way to do that in 0mq
| [Wednesday 13 April 2011] [15:19:40] <sustrik>	the issue is being hotly discussed
| [Wednesday 13 April 2011] [15:19:52] <guido_g>	mpales: look at the lru examples in the guide
| [Wednesday 13 April 2011] [15:20:11] <sustrik>	yep, have a look into the guide
| [Wednesday 13 April 2011] [15:20:22] <guido_g>	they will show you how to deal w/ socket identities
| [Wednesday 13 April 2011] [15:20:23] <sustrik>	there are various workarounds there
| [Wednesday 13 April 2011] [15:20:29] <mpales>	sustrik: i actually do not really expect that zmq will support it, but want to be sure :)
| [Wednesday 13 April 2011] [15:20:38] <guido_g>	and instead of the lru use the source id for routing
| [Wednesday 13 April 2011] [15:20:47] <mpales>	i already read the whole guide
| [Wednesday 13 April 2011] [15:21:19] <guido_g>	so?
| [Wednesday 13 April 2011] [15:21:23] <mpales>	sustrik: since the routing decision is on application level and zmq sits below it
| [Wednesday 13 April 2011] [15:21:57] <sustrik>	what pieter does in the guide is using XREP socket as a way to route message to specific peers
| [Wednesday 13 April 2011] [15:22:00] <mpales>	guido_g: yes, that could do it
| [Wednesday 13 April 2011] [15:22:29] <sustrik>	that kind of helps with stateful services
| [Wednesday 13 April 2011] [15:22:41] <guido_g>	mpales: it will because your problem is only a variation of the lru example
| [Wednesday 13 April 2011] [15:22:52] <sustrik>	it basically shifts all the responsibility for routing to the user
| [Wednesday 13 April 2011] [15:23:18] <mpales>	ok, thanks guys
| [Wednesday 13 April 2011] [15:24:18] <mpales>	sustrik: the only problem with using xrep i have that it discards messages if they cannot be delivered
| [Wednesday 13 April 2011] [15:24:34] <mpales>	in my case i woulk prefer blocking
| [Wednesday 13 April 2011] [15:24:38] <mpales>	if the worker is busy
| [Wednesday 13 April 2011] [15:25:08] <mpales>	since i _need_ to deliver to that particular worker and prefer to wait over dropping the message
| [Wednesday 13 April 2011] [15:25:26] <sustrik>	mpales: yes, that's because xrep is meant to be a stateless service
| [Wednesday 13 April 2011] [15:25:33] <sustrik>	ie. it sends the reply
| [Wednesday 13 April 2011] [15:25:45] <sustrik>	if the requester is not there anymore it drops the message
| [Wednesday 13 April 2011] [15:26:02] <mpales>	sustrik: yes, that's clear
| [Wednesday 13 April 2011] [15:26:23] <mpales>	what i need is a xrep alternative that will block
| [Wednesday 13 April 2011] [15:26:30] <sustrik>	so, i would say, you have to modify 0mq itself
| [Wednesday 13 April 2011] [15:26:51] <sustrik>	introduce the blocking behaviour
| [Wednesday 13 April 2011] [15:27:38] <mpales>	sustrik: i was thinking about a socket type where you can configure its behaviour - to avoid multiple types
| [Wednesday 13 April 2011] [15:28:09] <sustrik>	if you believe you can deal with all the possible combinations, why not
| [Wednesday 13 April 2011] [15:28:51] <guido_g>	sustrik: would zmq_send return != 0 in such a case?
| [Wednesday 13 April 2011] [15:29:21] <guido_g>	i mean when sending to a xrep socket w/ hwm reached
| [Wednesday 13 April 2011] [15:29:31] <sustrik>	with ZMQ_NOBLOCK flag it returns -1 and EAGAIN
| [Wednesday 13 April 2011] [15:29:38] <sustrik>	without it, it just blocks
| [Wednesday 13 April 2011] [15:29:41] <guido_g>	ha! :)
| [Wednesday 13 April 2011] [15:30:18] <guido_g>	no, i was talking of xrep, where it drops the message
| [Wednesday 13 April 2011] [15:30:52] <sustrik>	no, it's silent
| [Wednesday 13 April 2011] [15:31:07] <guido_g>	what if this would be changed?
| [Wednesday 13 April 2011] [15:31:24] <sustrik>	mpales: would that help?
| [Wednesday 13 April 2011] [15:31:28] <sustrik>	sounds easy to implement
| [Wednesday 13 April 2011] [15:31:42] <guido_g>	it still drops the message but the return code signales that the send was *not* done
| [Wednesday 13 April 2011] [15:31:53] <mpales>	the configuration of that 'generic' socket could be limited to incoming/outgoing routing strategy and hwm option action
| [Wednesday 13 April 2011] [15:31:54] <guido_g>	like with xreq in NOBLOCK mode
| [Wednesday 13 April 2011] [15:33:43] <mpales>	sustrik: you're suggesting to set ZMQ_NOBLOCK to the socket?
| [Wednesday 13 April 2011] [15:34:01] <sustrik>	nope, i was just answering guido_g
| [Wednesday 13 April 2011] [15:34:56] <guido_g>	mpales: the idea was to make the send on an XREP socket retunr != 0 when the message has been droppen, so that the application has a way to see that the message was not sent
| [Wednesday 13 April 2011] [15:35:29] <mpales>	guido_g: aha, that would help
| [Wednesday 13 April 2011] [15:36:06] <sustrik>	mpales: check zmq::xrep_t::xsend
| [Wednesday 13 April 2011] [15:36:20] <sustrik>	look for this line: if (it != outpipes.end ()) {
| [Wednesday 13 April 2011] [15:37:52] <mpales>	sustrik: got it
| [Wednesday 13 April 2011] [15:38:38] <guido_g>	sustrik: any reasons that this should not be done for all socket types that drop silently on send?
| [Wednesday 13 April 2011] [15:39:21] <sustrik>	this is just a workaround for mpales
| [Wednesday 13 April 2011] [15:39:30] <sustrik>	in reality it doesn't really woek
| [Wednesday 13 April 2011] [15:39:32] <sustrik>	work
| [Wednesday 13 April 2011] [15:39:52] <guido_g>	why?
| [Wednesday 13 April 2011] [15:39:55] <sustrik>	if you insert a device between sender and receiver, the message may be dropped without sender ever noticing it
| [Wednesday 13 April 2011] [15:40:36] <guido_g>	i see
| [Wednesday 13 April 2011] [15:41:17] 	 * guido_g steps into this trap every time
| [Wednesday 13 April 2011] [15:41:48] <sustrik>	it's a "scalability check" principle
| [Wednesday 13 April 2011] [15:41:56] <sustrik>	should be documented somewhere even
| [Wednesday 13 April 2011] [15:42:16] <guido_g>	need heavy re-wiring of some brain areas
| [Wednesday 13 April 2011] [15:42:30] <sustrik>	:)
| [Wednesday 13 April 2011] [15:43:16] <guido_g>	i'm playing w/ mq for months now and still "don't get it"
| [Wednesday 13 April 2011] [15:45:29] <sustrik>	i tend to play "what if it was TCP/IP?" game
| [Wednesday 13 April 2011] [15:45:47] <sustrik>	if you add a router into middle, would it still work?
| [Wednesday 13 April 2011] [15:46:01] <guido_g>	yes
| [Wednesday 13 April 2011] [15:46:42] <guido_g>	it's just that i need to develop this as a reflex
| [Wednesday 13 April 2011] [15:47:22] <guido_g>	it'S a matter of training i guess
| [Wednesday 13 April 2011] [15:47:46] <sustrik>	yep, i'm training it for couple of years now
| [Wednesday 13 April 2011] [15:47:56] <sustrik>	still i sometimes get trapped
| [Wednesday 13 April 2011] [15:47:57] <guido_g>	*sigh*
| [Wednesday 13 April 2011] [15:49:34] <mpales>	sustrik: in that code i also need to change the logic to be able to do a resend, right?
| [Wednesday 13 April 2011] [15:50:35] <sustrik>	well, you should not change the state of socket in any way if you are dropping the message
| [Wednesday 13 April 2011] [15:50:58] <sustrik>	the question is what to do with subdequent message parts
| [Wednesday 13 April 2011] [15:51:04] <sustrik>	in case of multipart messages
| [Wednesday 13 April 2011] [15:51:13] <sustrik>	ie. first one is dropped
| [Wednesday 13 April 2011] [15:51:24] <sustrik>	do we expect other parts yet to be sent
| [Wednesday 13 April 2011] [15:51:41] <sustrik>	or do we expect the user to back down and don't send subsequent parts?
| [Wednesday 13 April 2011] [15:52:36] <mpales>	sustrik: i would suggest the latter
| [Wednesday 13 April 2011] [15:52:45] <sustrik>	it's up to you
| [Wednesday 13 April 2011] [15:53:01] <sustrik>	do it in such a way as to make you app benefit from it
| [Wednesday 13 April 2011] [15:56:23] <mpales>	sustrik: is it possible that only first part is sent and the rest is dropped in case the queue is full?
| [Wednesday 13 April 2011] [15:56:45] <sustrik>	no
| [Wednesday 13 April 2011] [15:56:47] <sustrik>	it's atomic
| [Wednesday 13 April 2011] [15:56:57] <sustrik>	it either sends the whole message
| [Wednesday 13 April 2011] [15:56:59] <sustrik>	or nothing
| [Wednesday 13 April 2011] [15:57:32] <mpales>	ok
| [Wednesday 13 April 2011] [16:01:28] <mpales>	sustrik: i also noticed that ypipe is affected by false sharing in case you have several io threads or several contexts
| [Wednesday 13 April 2011] [16:02:15] <mpales>	putting cacheline size pads between *w and *r would help
| [Wednesday 13 April 2011] [16:02:30] <sustrik>	nice spot
| [Wednesday 13 April 2011] [16:02:59] <sustrik>	would you provide a patch?
| [Wednesday 13 April 2011] [16:03:10] <mpales>	i can, sure
| [Wednesday 13 April 2011] [16:03:14] <sustrik>	:)
| [Wednesday 13 April 2011] [16:03:17] <sustrik>	great
| [Wednesday 13 April 2011] [16:03:26] <mpales>	but later this week, too busy these days
| [Wednesday 13 April 2011] [16:43:29] <private_meta>	When using IPC sockets, how do I specify absolut locations of IPC files?
| [Wednesday 13 April 2011] [16:43:50] <private_meta>	+e
| [Wednesday 13 April 2011] [16:48:39] <sustrik>	ipc:///my/path
| [Wednesday 13 April 2011] [16:49:09] <private_meta>	yeah, found it as well, thanks
| [Wednesday 13 April 2011] [17:27:50] <eyeris>	I've installed zeromq 2.1.4 under cygwin but gcc complains about undefined references when I compile  a simple test program (from the guide).
| [Wednesday 13 April 2011] [17:28:33] <eyeris>	all of the undefined references it complains about begin with _zmq
| [Wednesday 13 April 2011] [17:30:16] <Seta00>	are you linking your project with zmq properly?
| [Wednesday 13 April 2011] [17:30:21] <eyeris>	Yeah, making a paste now
| [Wednesday 13 April 2011] [17:31:13] <eyeris>	http://pastebin.ca/2046149
| [Wednesday 13 April 2011] [17:34:15] <eyeris>	If I run make check in the zeromq build tree a bunch of them fail and then it seems to hang after test_hwm.exe passes
| [Wednesday 13 April 2011] [19:27:57] <stevan_>	is this a good place to ask about jzmq build issues on windows?
| [Wednesday 13 April 2011] [19:28:08] <stevan_>	or is there a more jzmq specific room?
| [Wednesday 13 April 2011] [19:28:51] <stevan_>	this is what I am getting -> http://codepeek.com/paste/4da6318a6cac63f86c754600
| [Wednesday 13 April 2011] [19:28:59] <stevan_>	libzmq compiled just fine
| [Wednesday 13 April 2011] [19:29:19] <stevan_>	this is with Visual Studio 2010 too, if that makes any difference
| [Wednesday 13 April 2011] [19:52:49] <stevan_>	ah ha, I got it
| [Wednesday 13 April 2011] [19:53:11] <stevan_>	libzmq HEAD was not what I really wanted, I wanted the one on the downloads page
| [Thursday 14 April 2011] [09:09:20] <mikko>	hey ho
| [Thursday 14 April 2011] [09:58:38] <sustrik>	hi
| [Thursday 14 April 2011] [09:58:47] <djc>	I've setup a FORWARDER device with the publishing (outbound) socket bound to inproc://something and am trying to set up subscribers listening to it, but I get a connection refused error
| [Thursday 14 April 2011] [09:58:55] <djc>	anyone got tips on debugging that?
| [Thursday 14 April 2011] [09:59:13] <sustrik>	access rights?
| [Thursday 14 April 2011] [09:59:19] <sustrik>	ah
| [Thursday 14 April 2011] [09:59:23] <sustrik>	inproc
| [Thursday 14 April 2011] [09:59:30] <sustrik>	sorry, i though it's ipc
| [Thursday 14 April 2011] [09:59:47] <sustrik>	are you using the same context?
| [Thursday 14 April 2011] [10:00:08] <djc>	ah, no
| [Thursday 14 April 2011] [10:00:12] <djc>	it should be, I guess?
| [Thursday 14 April 2011] [10:00:24] <sustrik>	the inproc endpoints are shared only within the same context
| [Thursday 14 April 2011] [10:01:03] <djc>	that makes sense
| [Thursday 14 April 2011] [10:01:20] <djc>	I'm using a small wrapper class for the subscriber, but of course it sets up its own context
| [Thursday 14 April 2011] [10:01:29] <djc>	there we go with the leaking abstraction!
| [Thursday 14 April 2011] [10:07:51] <djc>	sustrik: thanks
| [Thursday 14 April 2011] [10:08:03] <sustrik>	you are welcome
| [Thursday 14 April 2011] [10:21:15] <ianbarber>	yrashk: about?
| [Thursday 14 April 2011] [12:13:28] <mikko>	hummm
| [Thursday 14 April 2011] [12:35:22] <joelr>	good day
| [Thursday 14 April 2011] [12:35:33] <joelr>	<- is rewriting the freelance pattern in ocaml
| [Thursday 14 April 2011] [12:36:59] <mikko>	good stuff
| [Thursday 14 April 2011] [12:41:55] <joelr>	zeromq is a strange beast
| [Thursday 14 April 2011] [12:42:12] <joelr>	kind of like a performance engine on a frame. 
| [Thursday 14 April 2011] [12:43:03] <joelr>	it's got wheels and it rolls but there's no suspension, hydraulic steering, seats or body
| [Thursday 14 April 2011] [12:43:30] <joelr>	i think even steering is some sort of a lever rather than a wheel
| [Thursday 14 April 2011] [12:43:34] <yrashk>	ianbarber: ?
| [Thursday 14 April 2011] [12:43:41] <joelr>	point being that you've got to add the rest
| [Thursday 14 April 2011] [12:51:49] <pieterh>	joelr: seems like that sometimes
| [Thursday 14 April 2011] [12:52:28] <joelr>	it certainly does
| [Thursday 14 April 2011] [17:18:00] <jhawk28>	ZMQ and J2EE don't play well
| [Thursday 14 April 2011] [17:19:16] <jhawk28>	it looks like I'm gonna need to create a native Java version of libzmq
| [Thursday 14 April 2011] [17:19:53] <jhawk28>	EJB's forbid using JNI libraries
| [Thursday 14 April 2011] [17:28:08] <eyeris>	With the pyzmq bindings, calling recv_json() is returning a string form of the serialized json. type(sock.recv_json()) -> unicode
| [Thursday 14 April 2011] [17:28:46] <eyeris>	The json-encoded string represents a json object, so I would expect type(sock.recv_json()) to return a dict
| [Thursday 14 April 2011] [19:13:37] <lestrrat>	so I'm finally moving perl zmq to work with 3.x. 
| [Thursday 14 April 2011] [19:14:29] <lestrrat>	what's the status of zmq_device() ? I remember reading about it in a thread somewhere, but how should we binding authors deal with it?
| [Friday 15 April 2011] [01:33:12] <sustrik>	lestrrat: i wouldn't move to 3.0 yet
| [Friday 15 April 2011] [01:33:21] <sustrik>	it's not fully stable yet
| [Friday 15 April 2011] [01:48:51] <lestrrat>	well, not so much for really moving, but I want to silence the test failures (at least for now)
| [Friday 15 April 2011] [01:54:02] <sustrik>	ok, i see
| [Friday 15 April 2011] [01:54:23] <sustrik>	as for devices the plan is to move them to a separate project
| [Friday 15 April 2011] [02:05:15] <lestrrat>	k, I guess I'd need to create a separate binding for it, then
| [Friday 15 April 2011] [02:05:54] <sustrik>	ok, no haste needed, though
| [Friday 15 April 2011] [02:06:48] <lestrrat>	yeah, I'll just skip the code that uses it.
| [Friday 15 April 2011] [02:48:42] <lestrrat>	mikko: can you please point the jenkins tests to look at  "libzmq3" branch for the perl binding + 0MQ 3.x? master is currently for 2.1.x
| [Friday 15 April 2011] [02:48:42] <lestrrat>	I started changing stuff for zmq3 on libzmq3 branch.
| [Friday 15 April 2011] [03:04:51] <mikko>	lestrrat: will do
| [Friday 15 April 2011] [03:04:55] <mikko>	give me a sec
| [Friday 15 April 2011] [03:05:40] <mikko>	lestrrat: building now
| [Friday 15 April 2011] [03:05:52] <lestrrat>	mikko: it will fail :)
| [Friday 15 April 2011] [03:05:57] <mikko>	it did
| [Friday 15 April 2011] [03:06:04] <mikko>	but the build should be now configured correctly
| [Friday 15 April 2011] [03:06:07] <mikko>	so it's a good start
| [Friday 15 April 2011] [03:06:11] <lestrrat>	cool :)
| [Friday 15 April 2011] [03:25:57] <pieterh>	lestrrat: we should backport the fixes to the tests to 2.x
| [Friday 15 April 2011] [03:26:24] <pieterh>	mikko: did you get a chance to look at the rhat packaging for 2.x?
| [Friday 15 April 2011] [03:55:54] <mikko>	i to the b
| [Friday 15 April 2011] [09:46:55] <yawniek>	hi, from the examples i try to run asyncsrv.py. but the code where the ClientTask receives the answers is never executed. any hints?
| [Friday 15 April 2011] [09:53:06] <yawniek>	talking about https://gist.github.com/883983/1940c7aff75871e1a1dcad4f8d340cf3a9a26ae1
| [Friday 15 April 2011] [09:57:06] <pieterh>	yawniek: hi
| [Friday 15 April 2011] [09:57:18] <pieterh>	how far does the request get?
| [Friday 15 April 2011] [10:00:18] <yawniek>	the worker sends the replies
| [Friday 15 April 2011] [10:00:25] <pieterh>	you see them in the server?
| [Friday 15 April 2011] [10:00:39] <yawniek>	yes
| [Friday 15 April 2011] [10:00:50] <pieterh>	so the normal problem here is with the XREP/ROUTER socket
| [Friday 15 April 2011] [10:00:59] <pieterh>	which silently drops messages if the address is wrong
| [Friday 15 April 2011] [10:01:26] <pieterh>	you want to print/trace the first frame (message part) that the server sends back to the client
| [Friday 15 April 2011] [10:01:35] <pieterh>	make sure it's a valid identity
| [Friday 15 April 2011] [10:02:04] <pieterh>	see http://zguide.zeromq.org/page:all#Missing-Message-Problem-Solver
| [Friday 15 April 2011] [10:03:19] <yawniek>	ok thanks
| [Friday 15 April 2011] [10:08:26] <yawniek>	pieterh: to trace i need to receive multipart and print all parts?
| [Friday 15 April 2011] [10:08:46] <pieterh>	yawniek: no idea how this works in Python, sorry... but that sounds right
| [Friday 15 April 2011] [10:08:56] <mikko>	hello
| [Friday 15 April 2011] [10:08:58] <pieterh>	in any case you need to receive / send multipart if you're using a XREP socket
| [Friday 15 April 2011] [10:09:00] <pieterh>	hi mikko!
| [Friday 15 April 2011] [10:09:38] <mikko>	been pretty exciting time in .nl
| [Friday 15 April 2011] [10:10:09] <pieterh>	conference?
| [Friday 15 April 2011] [10:10:29] <mikko>	im stalking people
| [Friday 15 April 2011] [10:10:33] <pieterh>	lol
| [Friday 15 April 2011] [10:10:34] <mikko>	using kinect sensor
| [Friday 15 April 2011] [10:10:41] <mikko>	http://www.vimeo.com/22386826
| [Friday 15 April 2011] [11:23:45] <Lemmih>	Hiya, say I want a bunch of nodes to agree on the ordering of messages. Should I use N publishers and N subscribers together with some logic for ordering the messages or is there an easier way?
| [Friday 15 April 2011] [11:24:04] <pieterh>	messages produced by multiple nodes?
| [Friday 15 April 2011] [11:24:08] <Lemmih>	Yes.
| [Friday 15 April 2011] [11:24:26] <pieterh>	only simple way is to push them all through a single point
| [Friday 15 April 2011] [11:24:49] <Lemmih>	That would give me a single point of failure, no?
| [Friday 15 April 2011] [11:25:10] <pieterh>	you have another way of ordering messages across multiple nodes?
| [Friday 15 April 2011] [11:27:56] <Lemmih>	There are a couple of different ways to do it but I don't know enough about publisher/subscriber semantics to know how to go about it.
| [Friday 15 April 2011] [11:28:06] <pieterh>	how would you do it?
| [Friday 15 April 2011] [11:29:55] <pieterh>	Lemmih: you need to explain what you mean by "agree on the ordering"
| [Friday 15 April 2011] [11:31:02] <pieterh>	However note that if you have multiple publishers and multiple subscribers talking N to N
| [Friday 15 April 2011] [11:31:47] <pieterh>	then each subscriber will get messages from different publishers in an arbitrary order
| [Friday 15 April 2011] [11:31:48] <Lemmih>	I want all nodes to see the messages in the same order. The exact order doesn't matter as long as it is consistent across each node.
| [Friday 15 April 2011] [11:32:19] <pieterh>	if you want a single stream of messages, simplest is a central node to create that ordering
| [Friday 15 April 2011] [11:32:33] <locklace>	Lemmih: sequence numbers
| [Friday 15 April 2011] [11:32:50] <pieterh>	you might plausibly reorder within each client but it's still not robust
| [Friday 15 April 2011] [11:33:04] <pieterh>	locklace: sequence numbers won't be unique if there are multiple publishers
| [Friday 15 April 2011] [11:33:27] <locklace>	timestamps then
| [Friday 15 April 2011] [11:33:36] <pieterh>	timestamps won't be accurate across a network
| [Friday 15 April 2011] [11:33:47] <pieterh>	not at high message rates
| [Friday 15 April 2011] [11:33:48] <Lemmih>	They don't have to be.
| [Friday 15 April 2011] [11:33:54] <locklace>	they will if you're doing proper time sync, as you should be
| [Friday 15 April 2011] [11:34:13] <pieterh>	not accurate down to the microsecond afaik
| [Friday 15 April 2011] [11:34:40] <pieterh>	Lemmih: what 0MQ will do for you is e.g. fair queuing from all publishers
| [Friday 15 April 2011] [11:34:49] <locklace>	depends on the time distribution method
| [Friday 15 April 2011] [11:35:02] <locklace>	but it's not clear what the precision requirement is for this application
| [Friday 15 April 2011] [11:37:57] <pieterh>	Lemmih: can you provide more background on your use case?
| [Friday 15 April 2011] [11:38:01] <Lemmih>	pieterh: Alright. I'm fine with ordering the messages myself. Just wanted to make sure I didn't reinvent the wheel.
| [Friday 15 April 2011] [11:39:05] <Lemmih>	I have a transaction queue which has to be identical on each node. And each node should be able to push data to the transaction queue.
| [Friday 15 April 2011] [11:40:52] <pieterh>	Hmm, nice problem, and you want to work without a central device
| [Friday 15 April 2011] [11:41:28] <pieterh>	If your transaction rate is not too high you can use locklace's timestamp method
| [Friday 15 April 2011] [11:42:04] <cremes>	ntp is usually good for +/- 1 millisecond on a LAN
| [Friday 15 April 2011] [11:42:20] <cremes>	i wouldn't count on it for microsecond or nanosecond granularity
| [Friday 15 April 2011] [11:42:26] <pieterh>	so it also depends on the speed of processing of the transaction queue
| [Friday 15 April 2011] [11:42:34] <pieterh>	if it's fast you won't be able to reorder properly
| [Friday 15 April 2011] [11:42:54] <Lemmih>	I can do the ordering using timestamps (still works when the clocks differs, just adds latency) or non-local sequence numbers. However, since some of the other messaging libraries I've used in the path provided this functionality by default, I wanted to make sure I didn't rewrite something that's already in 0MQ. Those other messaging systems wheren't brokerless, though.
| [Friday 15 April 2011] [11:43:30] <pieterh>	Lemmih: 0MQ is a rocket engine but without a chassis
| [Friday 15 April 2011] [11:43:30] <Lemmih>	Oops, meant to write 'non-unique', not 'non-local'.
| [Friday 15 April 2011] [11:44:28] <pieterh>	how do you reorder when you've already processed a transaction?
| [Friday 15 April 2011] [11:44:47] <pieterh>	i.e. two clients get B, A, and A, B
| [Friday 15 April 2011] [11:45:16] <Lemmih>	I don't. I keep the messages in a queue until they can be ordered.
| [Friday 15 April 2011] [11:46:46] <Lemmih>	If A and B have timestamps and I know that the publishers can't/won't send any messages younger than the oldest of A and B, then A and B has been assigned order globally.
| [Friday 15 April 2011] [11:47:21] <Lemmih>	This can also be done using ticks instead of timestamps.
| [Friday 15 April 2011] [11:47:29] <pieterh>	so you either timeout per publisher, or wait for another message to arrive
| [Friday 15 April 2011] [11:49:00] <pieterh>	in fact you can do it without timestamps at all
| [Friday 15 April 2011] [11:49:10] <pieterh>	as long as you have unique publisher ids
| [Friday 15 April 2011] [11:49:12] <Lemmih>	Right.
| [Friday 15 April 2011] [11:49:23] <Lemmih>	And I do have that.
| [Friday 15 April 2011] [11:49:33] <pieterh>	but it's going to add latency... and still be breakable 
| [Friday 15 April 2011] [11:49:42] <Lemmih>	Breakable how?
| [Friday 15 April 2011] [11:50:14] <pieterh>	if a message gets stuck somewhere, for longer than your timeout, the order can become bogus
| [Friday 15 April 2011] [11:50:49] <Lemmih>	Is it possible for a publisher to send two messages and have the second arrive before the first?
| [Friday 15 April 2011] [11:51:03] <pieterh>	no, but two messages from two publishers will arrive in arbitrary order
| [Friday 15 April 2011] [11:51:07] <pieterh>	obviously
| [Friday 15 April 2011] [11:51:17] <pieterh>	from one publisher, it's a TCP stream
| [Friday 15 April 2011] [11:51:43] <pieterh>	also you have no way to handle a crashing publisher
| [Friday 15 April 2011] [11:51:51] <pieterh>	i.e. which has sent to some clients but not to others
| [Friday 15 April 2011] [11:53:19] <Lemmih>	I do, actually, but that's due to the way I use the transaction log.
| [Friday 15 April 2011] [11:54:37] <pieterh>	it'd be interesting to see your solution in print, once you get it working with 0MQ
| [Friday 15 April 2011] [11:54:44] <pieterh>	it sounds like it'll work easily
| [Friday 15 April 2011] [11:54:46] <Lemmih>	Just receiving a message isn't enough to consider it commited. It also has to be confirmed durable on a supermajority of the nodes.
| [Friday 15 April 2011] [11:55:08] <pieterh>	I still have my doubts about the design but that's just because I don't see enough of it
| [Friday 15 April 2011] [11:55:42] <pieterh>	you're basically doing atomic multicast iiuc
| [Friday 15 April 2011] [11:56:23] <guido_g>	did somone say lamport? :)
| [Friday 15 April 2011] [11:56:35] <Lemmih>	Well, I'll get back to you when it works (: Btw, I'm writing this code in Haskell.
| [Friday 15 April 2011] [11:57:27] <pieterh>	guido_g: sounds like it :)
| [Friday 15 April 2011] [11:57:46] <pieterh>	Lemmih: I assume whatever pattern you build will work in any language over 0MQ
| [Friday 15 April 2011] [11:58:03] 	 * pieterh has an empty slot in the guide for atomic multicast
| [Friday 15 April 2011] [11:59:36] <guido_g>	using vector clocks?
| [Friday 15 April 2011] [11:59:50] 	 * pieterh has no effin idea :)
| [Friday 15 April 2011] [12:00:06] <guido_g>	ah ok
| [Friday 15 April 2011] [12:00:13] 	 * pieterh is waiting for a smarter person to explain how to do atomic multicast over 0MQ
| [Friday 15 April 2011] [12:00:13] <guido_g>	will wait then
| [Friday 15 April 2011] [12:00:45] <pieterh>	Lemmih: I'm interested in your work, will it be open source?
| [Friday 15 April 2011] [12:02:01] <Lemmih>	pieterh: Oh, you wrote "The Guide"? Damn that thing is long. I just spent most of my day reading it. (:
| [Friday 15 April 2011] [12:02:09] <Lemmih>	pieterh: Yes, it will be open source.
| [Friday 15 April 2011] [12:02:22] <pieterh>	Lemmih: lol, it's my work, yes, with the help of lots of people translating the examples
| [Friday 15 April 2011] [12:02:47] <pieterh>	there is a lot of detail in some patterns
| [Friday 15 April 2011] [12:02:51] <Lemmih>	I might contribute a few Haskell examples along the way.
| [Friday 15 April 2011] [12:02:59] <pieterh>	I'm doing Clone, and have six models to show the evolution
| [Friday 15 April 2011] [12:03:18] <pieterh>	Haskell examples would be great, the language isn't well represented today
| [Friday 15 April 2011] [12:10:56] <Lemmih>	FYI, I'm working on adding multimaster replication to a database system written in Haskell.
| [Friday 15 April 2011] [12:12:55] <pieterh>	Lemmih: there's a database written in Haskell?
| [Friday 15 April 2011] [12:12:59] <pieterh>	neat
| [Friday 15 April 2011] [12:13:35] <pieterh>	BTW, I'm really happy to hear you're using 0MQ for this, it should be a perfect fit
| [Friday 15 April 2011] [12:14:48] <Lemmih>	Calling it a database is probably a bit generous. It's a system for adding ACID guarantees to native-language data-types. Like Prevaylor if you've heard of it.
| [Friday 15 April 2011] [12:15:39] <Lemmih>	Yeah, I really like 0MQ for this. Feels much better than the other message systems I've tried in the past.
| [Friday 15 April 2011] [12:16:39] <pieterh>	yeah
| [Friday 15 April 2011] [12:23:46] <iAmTheDave>	Not sure this is the forum, but we just released a Django message queue app using 0MQ. https://github.com/dmgctrl/django-ztask
| [Friday 15 April 2011] [12:24:06] <iAmTheDave>	It was so nice to work with 0MQ, it was so light-weight...
| [Friday 15 April 2011] [12:24:39] <pieterh>	iAmTheDave: nice!
| [Friday 15 April 2011] [12:25:16] <iAmTheDave>	pieterh: it totally is. we were using celery and all the cruft that goes along with it (not knocking it) but we wanted something WAY smaller.
| [Friday 15 April 2011] [12:25:51] <pieterh>	iAmTheDave: would you send me a short story of how this happened?
| [Friday 15 April 2011] [12:25:55] <iAmTheDave>	so like, thanks for 0MQ!
| [Friday 15 April 2011] [12:25:59] <pieterh>	I'd like to publish that on our wiki somewhere
| [Friday 15 April 2011] [12:26:12] <pieterh>	a testimonial...
| [Friday 15 April 2011] [12:26:14] <iAmTheDave>	yeah you bet. that'd be awesome!
| [Friday 15 April 2011] [12:26:17] <pieterh>	:)
| [Friday 15 April 2011] [12:26:22] <pieterh>	email it to ph@imatix.com
| [Friday 15 April 2011] [12:26:32] <iAmTheDave>	can do
| [Friday 15 April 2011] [12:26:34] <pieterh>	I'll make sure your project gets coverage
| [Friday 15 April 2011] [12:26:40] <pieterh>	have already twitted about it
| [Friday 15 April 2011] [12:27:00] <pieterh>	next step is to update the zeromq myspace page!
| [Friday 15 April 2011] [12:27:42] <iAmTheDave>	oh wow. thanks :) didn't expect all that, just wanted to let you know we're really happy with it
| [Friday 15 April 2011] [12:27:43] <locklace>	it's just like 2003
| [Friday 15 April 2011] [12:28:07] 	 * pieterh doesn't actually have a myspace page but only because he's not that cool
| [Friday 15 April 2011] [12:28:35] <locklace>	extra points for picking the right twitter verb too
| [Friday 15 April 2011] [12:29:18] <pieterh>	locklace: I tried to write twitted but my spelling checker changed it to twitted
| [Friday 15 April 2011] [12:29:32] <pieterh>	:)
| [Friday 15 April 2011] [13:11:01] <pdhborges>	s
| [Friday 15 April 2011] [13:26:35] <iAmTheDave>	pieterh: sent something your way, email-style
| [Friday 15 April 2011] [13:27:30] <pieterh>	iAmTheDave: read it, lovely
| [Friday 15 April 2011] [13:27:43] <pieterh>	I'll post it to the wiki shortly, am just going for pizza with the family
| [Friday 15 April 2011] [13:29:18] <iAmTheDave>	whoa whoa whoa - what's more important here?? 
| [Friday 15 April 2011] [13:29:20] <iAmTheDave>	;)
| [Friday 15 April 2011] [13:29:47] <iAmTheDave>	also, now i'm hungry for pizza.
| [Friday 15 April 2011] [13:32:13] <pieterh>	:) OK, posted the story to http://www.zeromq.org/story:3, now it's really pizza time!
| [Friday 15 April 2011] [13:32:49] <iAmTheDave>	dude i was kidding
| [Friday 15 April 2011] [15:22:58] 	 * pieterh had a great pizza, back to work
| [Friday 15 April 2011] [15:29:24] <pdhborges>	Dany
| [Friday 15 April 2011] [15:29:34] <pdhborges>	o leo nnao t c ainda
| [Friday 15 April 2011] [15:30:03] <pdhborges>	ups wrong window
| [Friday 15 April 2011] [19:33:50] <danolj>	good evening. I have a question on a log file collection scenario.
| [Friday 15 April 2011] [19:34:33] <danolj>	I'd like to take log files from n-servers and place the contents into a zmq bus on which there may be zero or more listeners
| [Friday 15 April 2011] [19:34:41] <danolj>	is there a pattern that someone here would recommend?
| [Friday 15 April 2011] [19:35:17] <danolj>	at the moment I can certainly have each server PUB to an endpoint, but the listeners would need to know all the endpoints in order to SUB
| [Friday 15 April 2011] [19:35:30] <danolj>	any thoughts? thanks
| [Friday 15 April 2011] [20:32:06] <Toba>	danolj: that's an interesting problem. are you sure someone else hasn't already built exactly what you're looking for?
| [Friday 15 April 2011] [20:44:32] <danolj>	I am not sure - been googling for patterns / solutions
| [Friday 15 April 2011] [20:49:10] <danolj>	I suspect that an intermediate forwarder is likely with some kind of mechanism for discovery of all the publishing endpoints
| [Friday 15 April 2011] [21:12:10] <jsimmons_>	why do they need to know all the end points danolj?
| [Friday 15 April 2011] [21:12:28] <jsimmons_>	you can bind on either side of the connection. ie your subscriber can bind, and publishers connect
| [Friday 15 April 2011] [23:21:19] <danolj>	it is more about wanting "magic" to happen so that I don't have to keep configs updated across nodes
| [Friday 15 April 2011] [23:21:26] <danolj>	as to what all the end points are today
| [Friday 15 April 2011] [23:22:06] <danolj>	there are some things that spread offers in terms of service discovery over udp that I'd like to replicate
| [Friday 15 April 2011] [23:22:19] <danolj>	btw, thanks for the discussion!
| [Friday 15 April 2011] [23:56:28] <Toba>	danolj: well, there are tools that manage configs. lots of htem. you may be solving the wrong problem.
| [Saturday 16 April 2011] [01:02:21] <danolj>	Toba: you may be correct. Thanks.
| [Saturday 16 April 2011] [01:02:35] <Toba>	good luck, I'm going to bed 
| [Saturday 16 April 2011] [02:41:21] <guido_g>	danolj: you can either use a forwarder device or the (e)pgm transport
| [Saturday 16 April 2011] [02:41:58] <guido_g>	with the forwarder device there is only one endpoint to be known (configured) for publishers and subscribers
| [Saturday 16 April 2011] [02:42:14] <guido_g>	otoh, it's a spof
| [Saturday 16 April 2011] [02:42:47] <guido_g>	or you use the (e)pgm, which is real multicast and you get want you want: a bus structure
| [Saturday 16 April 2011] [02:43:12] <guido_g>	but multicast does have it's own set of probl^W implications :)
| [Saturday 16 April 2011] [05:30:10] <sustrik>	mikko: are you there?
| [Saturday 16 April 2011] [05:30:27] <sustrik>	any idea whether openpgm should work on osx?
| [Saturday 16 April 2011] [05:33:30] <locklace>	it claims to support os x / amd64
| [Saturday 16 April 2011] [05:35:34] <sustrik>	thanks
| [Saturday 16 April 2011] [05:35:47] <sustrik>	there's an bug report about it
| [Saturday 16 April 2011] [05:37:31] <mikko>	sustrik: i think it should
| [Saturday 16 April 2011] [05:37:35] <mikko>	i can test it
| [Saturday 16 April 2011] [05:37:53] <mikko>	i saw the report yesterday but was at the airport
| [Saturday 16 April 2011] [05:38:02] <sustrik>	you have osx?
| [Saturday 16 April 2011] [05:38:07] <mikko>	yes
| [Saturday 16 April 2011] [05:38:14] <sustrik>	give it a try then
| [Saturday 16 April 2011] [05:39:13] <mikko>	building
| [Saturday 16 April 2011] [05:41:14] <mikko>	same result
| [Saturday 16 April 2011] [05:42:00] <sustrik>	hm, let me check on linux
| [Saturday 16 April 2011] [05:42:20] <mikko>	that struct doesn't seem to be defined on ox s
| [Saturday 16 April 2011] [05:42:22] <mikko>	os x
| [Saturday 16 April 2011] [05:42:27] <mikko>	based on grep -r /usr/include
| [Saturday 16 April 2011] [05:44:09] <sustrik>	looks like an openpgm issue then
| [Saturday 16 April 2011] [05:45:10] <mikko>	one for steve maybe
| [Saturday 16 April 2011] [05:45:22] <mikko>	same thing happens on mingw32 
| [Saturday 16 April 2011] [05:45:27] <mikko>	as the struct is missing
| [Saturday 16 April 2011] [05:46:06] <sustrik>	would you ping him?
| [Saturday 16 April 2011] [05:46:09] <sustrik>	or should i?
| [Saturday 16 April 2011] [05:47:58] <mikko>	i can ping him
| [Saturday 16 April 2011] [05:48:09] <mikko>	he should be back today / tomorrow i think
| [Saturday 16 April 2011] [05:48:16] <sustrik>	ok
| [Saturday 16 April 2011] [05:48:16] <mikko>	he was travelling europe this week
| [Saturday 16 April 2011] [05:48:26] <sustrik>	yes, i recall
| [Saturday 16 April 2011] [05:51:18] <pieterh>	g'morning
| [Saturday 16 April 2011] [05:53:00] <sustrik>	morning
| [Saturday 16 April 2011] [05:53:25] <pieterh>	I made a rough proposal for libzutil, no response from the list
| [Saturday 16 April 2011] [05:54:03] <sustrik>	what's the difference from zfl?
| [Saturday 16 April 2011] [05:54:12] <pieterh>	target audience
| [Saturday 16 April 2011] [05:54:22] <pieterh>	libzutil is aimed specifically at language bindings
| [Saturday 16 April 2011] [05:54:35] <pieterh>	sits underneath libzapi, for example
| [Saturday 16 April 2011] [05:54:55] <pieterh>	libzfl sits on top of libzapi and is specifically for C apps
| [Saturday 16 April 2011] [05:55:55] <pieterh>	example use case for libzutil is how to make swap device accessible to Java apps
| [Saturday 16 April 2011] [05:56:42] <sustrik>	i like this line:
| [Saturday 16 April 2011] [05:56:43] <sustrik>	* Provide a set of clock and timer functions (which aren't otherwise portable).
| [Saturday 16 April 2011] [05:57:10] <sustrik>	if the idea gets traction
| [Saturday 16 April 2011] [05:57:14] <pieterh>	yes, you remember the old discussion about providing timers in the core library
| [Saturday 16 April 2011] [05:57:17] <sustrik>	i can remove zmq_utils from libzmq
| [Saturday 16 April 2011] [05:57:22] <pieterh>	yes
| [Saturday 16 April 2011] [05:57:51] <pieterh>	I have these timer/clock functions in zapi already, would move them down a layer
| [Saturday 16 April 2011] [05:58:19] <sustrik>	ok
| [Saturday 16 April 2011] [05:58:34] 	 * sustrik is leaving
| [Saturday 16 April 2011] [05:58:36] <sustrik>	cyl
| [Saturday 16 April 2011] [05:58:40] <pieterh>	cyl
| [Saturday 16 April 2011] [06:14:20] <mikko>	hmm, i integrated zeromq to this project already 
| [Saturday 16 April 2011] [06:14:37] <pieterh>	mikko: which project?
| [Saturday 16 April 2011] [06:14:44] <mikko>	needed to test coordinates of camera and noticed that zeromq is a lot easier than writing to file and copying it over
| [Saturday 16 April 2011] [06:14:55] <mikko>	pieterh: http://code.google.com/p/lecturerecorder/
| [Saturday 16 April 2011] [06:15:00] <pieterh>	lol
| [Saturday 16 April 2011] [06:15:28] <mikko>	now i got coordinate data coming from kinect sensor and camera controlling daemon subscribes to that data
| [Saturday 16 April 2011] [06:15:37] <mikko>	and moves the hardware camera based on it
| [Saturday 16 April 2011] [06:15:45] <pieterh>	0MQ is like a magic connectivity wand
| [Saturday 16 April 2011] [08:16:47] <Tapan>	Hello!! Is anyone out there?
| [Saturday 16 April 2011] [08:17:28] <mikko>	ye
| [Saturday 16 April 2011] [08:18:01] <Tapan>	Thanks... I am seeking some help in installing zeromq on redhat ES 5.5 64 bit.
| [Saturday 16 April 2011] [08:18:23] <mikko>	sure, do you want RPMS?
| [Saturday 16 April 2011] [08:18:32] <Tapan>	i have used ./configure, make and make install successfully but i don't know how to start zeromq.
| [Saturday 16 April 2011] [08:18:39] <mikko>	http://snapshot.zero.mq/rpm/centos5/x86_64/
| [Saturday 16 April 2011] [08:18:45] <mikko>	theres rpms built on centos5
| [Saturday 16 April 2011] [08:18:46] <Tapan>	Can you please suggest how should i start zeromq?
| [Saturday 16 April 2011] [08:18:51] <mikko>	should work in EL5 as well
| [Saturday 16 April 2011] [08:19:02] <mikko>	ahmm, what do you mean by starting zeromq?
| [Saturday 16 April 2011] [08:19:19] <Tapan>	thanks for the rpms links.
| [Saturday 16 April 2011] [08:19:39] <Tapan>	i means like zeromq -d 0.0.0.0 -p 8000 something like this.
| [Saturday 16 April 2011] [08:20:26] <mikko>	zeromq is not really a daemon 
| [Saturday 16 April 2011] [08:20:29] <Tapan>	Can you please suggest which version i should try as once sucussfully tested we want to install under production.
| [Saturday 16 April 2011] [08:20:40] <mikko>	it's more of a library to build your own daemons
| [Saturday 16 April 2011] [08:20:41] <Tapan>	Ohhhh
| [Saturday 16 April 2011] [08:20:54] <Tapan>	ahmm
| [Saturday 16 April 2011] [08:21:30] <Tapan>	I have seen one video on the zeromq site which shows how to connect with php.
| [Saturday 16 April 2011] [08:21:51] <pieterh>	Tapan: how much of the Guide did you read yet?
| [Saturday 16 April 2011] [08:22:23] <mikko>	Tapan: you mean ian barber's presentation?
| [Saturday 16 April 2011] [08:22:30] <Tapan>	i am sorry, i have only few hours of understanding of zeromq yet.
| [Saturday 16 April 2011] [08:22:58] <pieterh>	Tapan: it's best if you read http://zguide.zeromq.org/ first
| [Saturday 16 April 2011] [08:22:59] <Tapan>	I think yes....
| [Saturday 16 April 2011] [08:24:02] <Tapan>	Ok i will read the guide first and will come back with question if i have.....Thanks for the support....
| [Saturday 16 April 2011] [08:24:25] <Tapan>	Must admit good community...good support....
| [Saturday 16 April 2011] [09:55:34] <Tapan>	Hello! Is any out there?
| [Saturday 16 April 2011] [09:57:24] <mikko>	yea
| [Saturday 16 April 2011] [09:59:14] <Tapan>	I rad the guide and i am able to bind on perticuler port.
| [Saturday 16 April 2011] [09:59:21] <Tapan>	my example code is 
| [Saturday 16 April 2011] [09:59:23] <Tapan>	<?php  /*     The server waits for messages from the client     and echoes back the received message */ $server = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REP); $server->bind("tcp://127.0.0.1:5555");  /* Loop receiving and echoing back */ while ($message = $server->recv()) {     echo date("Y-m-d H:i:s")."-" ."$message\n";     /* echo back the message */     $server->send($message); } ?>
| [Saturday 16 April 2011] [10:00:28] <Tapan>	Is anyone out there now?
| [Saturday 16 April 2011] [10:00:32] <mikko>	yes
| [Saturday 16 April 2011] [10:00:43] <Tapan>	Thx...
| [Saturday 16 April 2011] [10:00:53] <Tapan>	I am also able to send message to queue like this
| [Saturday 16 April 2011] [10:01:08] <Tapan>	<?php  /*   The client sends two messages using two different sockets   and then exits  */ $is_persistent = true; /* Create new queue object */ $queue = new ZMQSocket(new ZMQContext($is_persistent), ZMQ::SOCKET_REQ, "MySock1"); $queue->connect("tcp://127.0.0.1:5555");  echo "Start Time:-" . date("Y-m-d H:i:s") . "\n"; /* Assign socket 1 to the queue, send and receive */ $queue->send("hello there!");  echo "End Time:-" . date("Y-m-d H:
| [Saturday 16 April 2011] [10:01:38] <Tapan>	Now i  want to test how much throughput i am getting this code so that i can think of using in my production application.
| [Saturday 16 April 2011] [10:02:06] <Tapan>	and my example code to test zeromq throughput is 
| [Saturday 16 April 2011] [10:02:29] <Tapan>	but after 1st request sent to socket it is throwing error.
| [Saturday 16 April 2011] [10:02:50] <Tapan>	and the error is PHP Fatal error:  Uncaught exception 'ZMQSocketException' with message 'Failed to send message: Operation cannot be accomplished in current state' in /var/www/html/zeromq/test.php:18 Stack trace: #0 /var/www/html/zeromq/test.php(18): ZMQSocket->send('hello there!-1') #1 {main}   thrown in /var/www/html/zeromq/test.php on line 18
| [Saturday 16 April 2011] [10:03:03] <Tapan>	is this persistance connection issue?
| [Saturday 16 April 2011] [10:03:08] <mikko>	nope
| [Saturday 16 April 2011] [10:03:21] <mikko>	with request - reply pattern you need to do things in sequence
| [Saturday 16 April 2011] [10:03:29] <mikko>	request,reply,request,reply 
| [Saturday 16 April 2011] [10:04:04] <mikko>	Operation cannot be accomplished in current state means that you are not in the correct state
| [Saturday 16 April 2011] [10:05:13] <Tapan>	can you please share very basic code with looping? so that i can check zeromq throughput.
| [Saturday 16 April 2011] [10:05:22] <Tapan>	If you have...
| [Saturday 16 April 2011] [10:07:45] <mikko>	just make sure that your server always does recv,send,recv,send and client does send,recv,send.recv 
| [Saturday 16 April 2011] [10:08:09] <Tapan>	Thanks Mikko
| [Saturday 16 April 2011] [10:08:15] <Tapan>	I understood.
| [Saturday 16 April 2011] [10:08:35] <Tapan>	now my script is like this and it is working...
| [Saturday 16 April 2011] [10:09:17] <Tapan>	This community is really rocks and working for fresher...:-
| [Saturday 16 April 2011] [10:09:20] <Tapan>	)
| [Saturday 16 April 2011] [10:10:56] <Tapan>	Can you please suggest what is the maximum throughput which we can expect from zeromq?
| [Saturday 16 April 2011] [10:14:59] <neopallium>	Tapan: See the through benchmark results on this page: https://github.com/Neopallium/lua-zmq
| [Saturday 16 April 2011] [10:18:05] <neopallium>	Tapan: See the through benchmark results on this page: https://github.com/Neopallium/lua-zmq
| [Saturday 16 April 2011] [10:18:15] <neopallium>	*throughput
| [Saturday 16 April 2011] [10:18:18] <Tapan>	how much throughput we can expect from zeromq?
| [Saturday 16 April 2011] [10:18:23] <Tapan>	any suggestion?
| [Saturday 16 April 2011] [10:18:43] <Tapan>	thanks checking
| [Saturday 16 April 2011] [10:18:58] <neopallium>	that page shows throughtput for Lua and C++ code.
| [Saturday 16 April 2011] [10:19:39] <neopallium>	Tapan: also for throughput testing it is using PUB/SUB sockets not REQ/REP sockets like the code you posted.
| [Saturday 16 April 2011] [10:19:41] <guido_g>	http://www.zeromq.org/area:results  <- more on performance
| [Saturday 16 April 2011] [10:21:55] <guido_g>	pieterh: there're no history links on the specs, makes checking the changes a bit hard
| [Saturday 16 April 2011] [10:22:19] <pieterh>	guido_g: let me check...
| [Saturday 16 April 2011] [10:23:16] <guido_g>	thx
| [Saturday 16 April 2011] [10:23:23] <Tapan>	Yes indeed the sites shows huge (very good--No i should say great throughput) throughput.
| [Saturday 16 April 2011] [10:23:58] <pieterh>	guido_g: if you reload the page you should see the links at the bottom. now
| [Saturday 16 April 2011] [10:24:52] <guido_g>	pieterh: sorry, no change yet
| [Saturday 16 April 2011] [10:25:01] <pieterh>	guido_g: may be cached for a while
| [Saturday 16 April 2011] [10:25:43] <guido_g>	pieterh: right, will check again later, thanks!
| [Saturday 16 April 2011] [10:25:58] <neopallium>	Tapan: If you are going to use zeromq from PHP you might want to port the latency & throughput benchmarks to PHP
| [Saturday 16 April 2011] [10:30:11] <Tapan>	Sure...
| [Saturday 16 April 2011] [10:59:20] <Tapan>	neopallium: How to run local_thr.cpp to check throughput of my installation?
| [Saturday 16 April 2011] [11:00:05] <guido_g>	Tapan: http://www.zeromq.org/results:perf-howto
| [Saturday 16 April 2011] [11:01:08] <guido_g>	pieterh: still no history link
| [Saturday 16 April 2011] [11:01:27] <pieterh>	guido_g: I'll logout of wikidot and try it... hang on
| [Saturday 16 April 2011] [11:01:44] <Tapan>	neopallium: And how should i check the throughput in php?
| [Saturday 16 April 2011] [11:01:55] <pieterh>	guido_g: I see the link, bottom right
| [Saturday 16 April 2011] [11:01:55] <guido_g>	pieterh: i'm logged in too, does this matter?
| [Saturday 16 April 2011] [11:02:03] <pieterh>	guido_g: shouldn't matter
| [Saturday 16 April 2011] [11:02:53] <guido_g>	pieterh: on which page do you check?
| [Saturday 16 April 2011] [11:03:06] <guido_g>	mine is http://rfc.zeromq.org/spec:7 
| [Saturday 16 April 2011] [11:03:35] <pieterh>	guido_g: well, it's helpful if we agree what page we're looking at, I'm at http://www.zeromq.org/results:perf-howto
| [Saturday 16 April 2011] [11:03:50] <Tapan>	guido_g: I have already opened that link and when i firing the scritp i am getting error.
| [Saturday 16 April 2011] [11:03:51] <Tapan>	[root@node03 perf]# ./local_thr.cpp tcp://eth0:5555 1 100000 ./local_thr.cpp: line 1: /bin: is a directory ./local_thr.cpp: line 2: syntax error near unexpected token `c' ./local_thr.cpp: line 2: `    Copyright (c) 2007-2011 iMatix Corporation' [root@node03 perf]#
| [Saturday 16 April 2011] [11:03:52] <pieterh>	sorry, meant http://www.zeromq.org/area:results
| [Saturday 16 April 2011] [11:04:03] <pieterh>	rfc is another wiki, I'll fix the permissions on that now
| [Saturday 16 April 2011] [11:05:15] <pieterh>	guido_g: ok, try that now?
| [Saturday 16 April 2011] [11:05:15] <guido_g>	ahhh....
| [Saturday 16 April 2011] [11:05:32] <pieterh>	I missed where you said 'the specs'
| [Saturday 16 April 2011] [11:05:50] <guido_g>	np
| [Saturday 16 April 2011] [11:07:04] <guido_g>	there it is, but only if i'm logged in
| [Saturday 16 April 2011] [11:07:53] <pieterh>	permissions are definitely correct now, must be a refresh issue
| [Saturday 16 April 2011] [11:08:33] <guido_g>	as said, when i'm logged in the links are there
| [Saturday 16 April 2011] [11:08:47] <pieterh>	I'm testing via a proxy browser (totally anonymous), links are there
| [Saturday 16 April 2011] [11:09:21] <guido_g>	then my firefox is playing games on me :/
| [Saturday 16 April 2011] [11:10:17] <guido_g>	opera is showing them when i'm not signed in anymore
| [Saturday 16 April 2011] [11:10:24] <guido_g>	so everything ok, i assume
| [Saturday 16 April 2011] [11:10:26] <guido_g>	thanks
| [Saturday 16 April 2011] [11:12:13] <guido_g>	and all this because 4 words changed :)
| [Saturday 16 April 2011] [11:13:10] <pieterh>	:)
| [Saturday 16 April 2011] [11:13:32] <guido_g>	oh, this number 12 looks very interesting...
| [Saturday 16 April 2011] [11:13:43] <pieterh>	it's the Clone pattern
| [Saturday 16 April 2011] [11:14:00] <pieterh>	damn thing took weeks to get right
| [Saturday 16 April 2011] [11:14:38] <pieterh>	actually the client-server part is easy, it's the reliable server failover that was nasty
| [Saturday 16 April 2011] [11:14:52] <guido_g>	as usual
| [Saturday 16 April 2011] [11:14:57] <pieterh>	as usual
| [Saturday 16 April 2011] [11:16:33] <guido_g>	i mean, even ibm didn't get it right in the first (2nd, 3rd...) go
| [Saturday 16 April 2011] [11:16:56] <guido_g>	i remember the fuzz when we tested that wllm thing
| [Saturday 16 April 2011] [11:17:35] <pieterh>	ironically even when failover works, it's pretty much pointless
| [Saturday 16 April 2011] [11:17:46] <pieterh>	better to have simpler boxes that break less often
| [Saturday 16 April 2011] [11:17:58] <guido_g>	yes
| [Saturday 16 April 2011] [11:18:38] <guido_g>	afair, they (dt. brse) dropped the intra-day service restart requirement after the tests
| [Saturday 16 April 2011] [11:19:01] <pieterh>	lol
| [Saturday 16 April 2011] [11:19:21] <guido_g>	agreed (now, back then it wasn't funny at all)
| [Saturday 16 April 2011] [11:20:05] <pieterh>	infrastructure projects always seem fairly painful
| [Saturday 16 April 2011] [11:20:12] <guido_g>	i wish i could show you the communication diagram we all lived of
| [Saturday 16 April 2011] [11:20:25] <guido_g>	the diagram was actually an accident
| [Saturday 16 April 2011] [11:21:09] <guido_g>	it resulted out of a meeting where all programming groups were invited
| [Saturday 16 April 2011] [11:21:25] <pieterh>	how long ago was this?
| [Saturday 16 April 2011] [11:21:38] <jond>	guido_g: I assume yr referrring to dt borse optimise platform ... isnt it based on wllm?
| [Saturday 16 April 2011] [11:21:46] <guido_g>	ack
| [Saturday 16 April 2011] [11:21:55] <guido_g>	pieterh: 2009 and early 2010
| [Saturday 16 April 2011] [11:22:06] 	 * pieterh was laterally involved...
| [Saturday 16 April 2011] [11:22:10] <guido_g>	jond: it is
| [Saturday 16 April 2011] [11:22:38] <guido_g>	pieterh: what? why?
| [Saturday 16 April 2011] [11:22:54] 	 * guido_g was only a little technical tester
| [Saturday 16 April 2011] [11:23:00] <pieterh>	at the time 0MQ was a stalking horse to get IBM to lower their license prices
| [Saturday 16 April 2011] [11:23:23] <jond>	guido_g: it's just gone live hasnt it?
| [Saturday 16 April 2011] [11:23:23] <pieterh>	s/was/was used as/
| [Saturday 16 April 2011] [11:23:30] <guido_g>	ic
| [Saturday 16 April 2011] [11:23:54] <jond>	pieterh: did you know that at the time?
| [Saturday 16 April 2011] [11:24:16] <pieterh>	jond: it became more or less obvious
| [Saturday 16 April 2011] [11:24:58] <jond>	pieterh: depressing....
| [Saturday 16 April 2011] [11:25:27] <guido_g>	the whole project was
| [Saturday 16 April 2011] [11:25:43] <guido_g>	or is, i think they're still on it
| [Saturday 16 April 2011] [11:26:01] <pieterh>	jond: it'd have been more depressing to spend another X years of ones' life trying to make upper management happy
| [Saturday 16 April 2011] [11:26:44] <jond>	guido_g: but the press releases said 'best in class etc etc' ;-)
| [Saturday 16 April 2011] [11:27:08] <guido_g>	jond: did you see the cialis ad next to it?
| [Saturday 16 April 2011] [11:27:16] <guido_g>	more substance, really
| [Saturday 16 April 2011] [11:27:40] <guido_g>	was my first project afer going freelance
| [Saturday 16 April 2011] [11:27:52] <jond>	pieterh: too true, and many decisions appear to be political rather than technical
| [Saturday 16 April 2011] [11:28:15] <guido_g>	except for optimise
| [Saturday 16 April 2011] [11:28:30] <guido_g>	there was *no* technical decision ever
| [Saturday 16 April 2011] [11:28:53] <jond>	guido_g: nope, what's cialis ?
| [Saturday 16 April 2011] [11:29:13] <guido_g>	jond: go check your spam folder :)
| [Saturday 16 April 2011] [11:29:48] <jond>	guido_g: lol
| [Saturday 16 April 2011] [11:30:30] <guido_g>	jond: there once was a quote from a top-manager at dt. brse that the new trading paltorm was doing >1 million trades per second
| [Saturday 16 April 2011] [11:31:22] <pieterh>	guido_g: sounds like they got their money's worth!
| [Saturday 16 April 2011] [11:31:32] <guido_g>	jond: this was at a time where the perf tests needed to talk to tha backend services directy, because the gateway service either a) seegfaulted or b) processed at max. 5k msgs/sec
| [Saturday 16 April 2011] [11:32:07] <guido_g>	but this time didn't last for long
| [Saturday 16 April 2011] [11:32:47] <guido_g>	after even the top-managers realized the real performance, the perf tests were cancelled 
| [Saturday 16 April 2011] [11:33:17] <pieterh>	hopefully they fired the idiot who wrote such slow perf tests
| [Saturday 16 April 2011] [11:33:32] <guido_g>	*sigh*
| [Saturday 16 April 2011] [11:33:59] <jond>	guido_g: I can see I could have an interesting conversation around this area, but not on irc.
| [Saturday 16 April 2011] [11:34:04] <pieterh>	what's the point for paying for perf tests that don't add a few zeros here and there... :-)
| [Saturday 16 April 2011] [11:34:12] <pieterh>	guido_g: can't you come to the 0MQ Unconf?
| [Saturday 16 April 2011] [11:34:41] <jond>	pieterh: I'm looking into it now
| [Saturday 16 April 2011] [11:34:43] <guido_g>	jond: *sigh* yes, unfortunately
| [Saturday 16 April 2011] [11:34:59] <pieterh>	jond: great!
| [Saturday 16 April 2011] [11:35:55] <guido_g>	pieterh: what i've seen so far it'll be more about mq development and process and such, nothing i'm interested in
| [Saturday 16 April 2011] [11:36:11] <pieterh>	guido_g: what would you be interested in?
| [Saturday 16 April 2011] [11:36:27] <pieterh>	I mean, it's an unconf, the participants define the agenda
| [Saturday 16 April 2011] [11:36:41] <guido_g>	pieterh: mostly how to *use* mq
| [Saturday 16 April 2011] [11:36:50] <mikko>	guido_g: i can demo my current project there
| [Saturday 16 April 2011] [11:36:53] <mikko>	guido_g: possibly
| [Saturday 16 April 2011] [11:37:01] <jond>	what i don't understand is why there's isnt more interest in sub forwarding....
| [Saturday 16 April 2011] [11:37:06] <guido_g>	i'm still having troubles to udnerstand some things in there (or not)
| [Saturday 16 April 2011] [11:37:13] <pieterh>	jond: too difficult to make it work IMO
| [Saturday 16 April 2011] [11:37:20] <pieterh>	no plugin framework for sockets in 0MQ
| [Saturday 16 April 2011] [11:37:47] <guido_g>	pieterh: sure, i read about the unconf thingy
| [Saturday 16 April 2011] [11:37:50] <pieterh>	guido_g: it'd be great to see you there, and you'd have time to get into any area you want
| [Saturday 16 April 2011] [11:38:32] <jond>	pieterh: i thought 29 west managed it?
| [Saturday 16 April 2011] [11:38:50] <pieterh>	jond: managed it? you mean sub forwarding?
| [Saturday 16 April 2011] [11:39:02] <pieterh>	in theory it's pretty simple
| [Saturday 16 April 2011] [11:39:04] <guido_g>	pieterh: ok, i'll get to a travel agency next week
| [Saturday 16 April 2011] [11:39:14] <pieterh>	the difficulty is just writing code that fits into the core lib afaics
| [Saturday 16 April 2011] [11:39:16] <mikko>	guido_g: where are you based?
| [Saturday 16 April 2011] [11:39:26] <guido_g>	mikko: hamburg, germany
| [Saturday 16 April 2011] [11:39:27] <pieterh>	guido_g: yay! :)
| [Saturday 16 April 2011] [11:39:37] <mikko>	cool
| [Saturday 16 April 2011] [11:40:04] <jond>	mikko: are you and ian barber going on the eurostar
| [Saturday 16 April 2011] [11:40:06] 	 * pieterh likes a good party
| [Saturday 16 April 2011] [11:40:13] <mikko>	jond: my plan is still a bit open
| [Saturday 16 April 2011] [11:40:19] <mikko>	ian is going on morning of 10th
| [Saturday 16 April 2011] [11:40:22] <guido_g>	pieterh: this will cost me over half a month of living w/o the need to work, better the beer is tasty and the chocolate plenty (or vice versa)  :)
| [Saturday 16 April 2011] [11:40:23] <mikko>	and leaving in the evening
| [Saturday 16 April 2011] [11:40:37] <mikko>	i am either going on morning of 10th or evening of 9th
| [Saturday 16 April 2011] [11:40:50] <pieterh>	guido_g: I promise the beer will be the best in Belgium and the company even better
| [Saturday 16 April 2011] [11:41:00] <jond>	mikko: thanks for info
| [Saturday 16 April 2011] [11:41:37] <guido_g>	pieterh: ok, then
| [Saturday 16 April 2011] [11:42:07] <pieterh>	guido_g: :)
| [Saturday 16 April 2011] [11:42:45] <jond>	gotta go do some family stuff, cyl
| [Saturday 16 April 2011] [11:42:49] <pieterh>	cyal
| [Saturday 16 April 2011] [11:43:41] <guido_g>	cu
| [Saturday 16 April 2011] [11:43:56] <guido_g>	hmmm... train is ~7h
| [Saturday 16 April 2011] [11:59:36] <pieterh>	guido_g: you don't fly?
| [Saturday 16 April 2011] [12:00:27] <guido_g>	pieterh: given that it *needs* a cell phone to get a flight, i was looking for alternatives
| [Saturday 16 April 2011] [12:01:04] <pieterh>	hmm, 7h is a long train journey
| [Saturday 16 April 2011] [12:01:05] <guido_g>	that's why i decided to dump the whole thing at a travel agency
| [Saturday 16 April 2011] [12:01:11] <guido_g>	full ack
| [Saturday 16 April 2011] [12:01:49] <guido_g>	oh... need to fix the laptop
| [Saturday 16 April 2011] [12:03:46] <pieterh>	guido_g: all the flights I can see are insanely expensive :(
| [Saturday 16 April 2011] [12:04:12] <guido_g>	pieterh: ~250 lufthansa
| [Saturday 16 April 2011] [12:04:22] <pieterh>	return? that's a good price...
| [Saturday 16 April 2011] [12:04:26] <guido_g>	it's a privilege to live in germany :(
| [Saturday 16 April 2011] [12:04:33] <pieterh>	he
| [Saturday 16 April 2011] [12:04:57] 	 * pieterh needs to go find lunch, bbl
| [Saturday 16 April 2011] [12:05:13] <guido_g>	have fun
| [Saturday 16 April 2011] [15:44:11] <thatch_>	I am trying to get pyzmq running on rhel5 zeromq 2.1.4 compiles without problems, but the pyzmq bindings fail in the setup.py decause of a python 2.5 construct. What version of pyzmq will run on python 2.4? If any? I am having a hard time finding the python versioning info for pyzmq
| [Saturday 16 April 2011] [15:50:12] <guido_g>	i don't think that 2.4 is supported at all
| [Saturday 16 April 2011] [15:58:21] <thatch_>	curses
| [Saturday 16 April 2011] [16:01:17] <guido_g>	it's been quite a time since 2004-11-30
| [Saturday 16 April 2011] [16:02:05] <thatch_>	heh, I built an application running on zeromq that I was hoping to get working on RHEL5, but it seems that is not going to be possible
| [Saturday 16 April 2011] [16:02:48] <guido_g>	there is now newer python? how old is this thing?
| [Saturday 16 April 2011] [16:02:54] <thatch_>	oh well, it runs great on Fedora and Arch, so, nuts to RHEL 5 I guess :)
| [Saturday 16 April 2011] [16:03:08] <thatch_>	Red Hat enterprise 5? It is crazy old
| [Saturday 16 April 2011] [16:03:16] <thatch_>	like 2007
| [Saturday 16 April 2011] [16:03:21] <guido_g>	OUCH
| [Saturday 16 April 2011] [16:03:29] <thatch_>	right
| [Saturday 16 April 2011] [16:03:43] <thatch_>	but most of the Linux servers in the world are running on in
| [Saturday 16 April 2011] [16:03:46] <thatch_>	on it
| [Saturday 16 April 2011] [16:03:55] <guido_g>	at least they had electricity back then
| [Saturday 16 April 2011] [16:04:09] <guido_g>	thatch_: say who?
| [Saturday 16 April 2011] [16:04:14] <guido_g>	*says
| [Saturday 16 April 2011] [16:04:33] <thatch_>	ok, maybe not "most" but a lot of em'
| [Saturday 16 April 2011] [16:04:43] <thatch_>	no worries, I will just not support it
| [Saturday 16 April 2011] [16:05:03] <thatch_>	it will be dead soon anyway since RHEL 6 is out
| [Saturday 16 April 2011] [16:05:46] <guido_g>	ahh
| [Saturday 16 April 2011] [16:05:58] <thatch_>	what python version is suported btw? My stuff seems to work just fine on 2.6
| [Saturday 16 April 2011] [16:06:06] <guido_g>	no idea
| [Saturday 16 April 2011] [16:06:13] <thatch_>	ok
| [Saturday 16 April 2011] [16:06:15] <guido_g>	i'm all on debian
| [Saturday 16 April 2011] [16:06:25] <guido_g>	except my phone :)
| [Saturday 16 April 2011] [16:06:30] <thatch_>	well, with RHEL5 out of the way that bumps me up to 2.6
| [Saturday 16 April 2011] [16:06:43] <thatch_>	debian eh?
| [Saturday 16 April 2011] [16:06:50] <thatch_>	Debian is awesome
| [Saturday 16 April 2011] [16:06:56] <thatch_>	but I am an Arch Linux dev
| [Saturday 16 April 2011] [16:07:26] <guido_g>	it works for me since 2003, never did an upgrade :)
| [Saturday 16 April 2011] [16:07:52] <thatch_>	Are there zeromq/pyzmq packages out there for Debian 6?
| [Saturday 16 April 2011] [16:08:00] <thatch_>	I did not see them in the main repos
| [Saturday 16 April 2011] [16:09:13] <headzone>	only testing/unstable (2.0) and experimental (2.1)
| [Saturday 16 April 2011] [16:09:28] <guido_g>	libzmq 2.0.10 is in testing nut no pyzmq
| [Saturday 16 April 2011] [16:09:28] <thatch_>	thanks!
| [Saturday 16 April 2011] [16:09:43] <thatch_>	thats enough for me :)
| [Saturday 16 April 2011] [16:10:00] <guido_g>	just get the tar-ball
| [Saturday 16 April 2011] [16:10:09] <thatch_>	I should ask you guys to tell me what I can do better in my zeromq app
| [Saturday 16 April 2011] [16:10:15] <thatch_>	no, I can install it just fine
| [Saturday 16 April 2011] [16:10:34] <thatch_>	I just want to have packages so that it is easier to others to deploy my software
| [Saturday 16 April 2011] [16:10:42] <thatch_>	https://github.com/thatch45/salt
| [Saturday 16 April 2011] [16:11:07] <guido_g>	unfortunately the update-frequency of libzmq and pyzmq is quite high
| [Saturday 16 April 2011] [16:11:36] <guido_g>	so you will need the freshest tar-balls for bug-fixes anyway
| [Saturday 16 April 2011] [16:11:39] <thatch_>	yes, I maintain pyzmq for Arch, I am kept on my toes
| [Saturday 16 April 2011] [16:12:25] <thatch_>	well, good info, thanks guido_g!
| [Saturday 16 April 2011] [16:12:31] <guido_g>	np
| [Saturday 16 April 2011] [16:14:36] <thatch_>	BTW, zeromq is AMAZING, and has let me do some very powerfull stuff, thanks for being brilliant zeromq team!
| [Saturday 16 April 2011] [16:15:06] <guido_g>	what is this salt thingy ment to do?
| [Saturday 16 April 2011] [16:15:49] <thatch_>	salt is a remote execution system, basically I made it to replace func and puppet labs' marionate collective
| [Saturday 16 April 2011] [16:16:11] <thatch_>	so you can execute commands on groups of servers in paralell 
| [Saturday 16 April 2011] [16:16:20] <guido_g>	ic
| [Saturday 16 April 2011] [16:16:48] <thatch_>	I also have some guys using it for general distributed computing and som hpc work
| [Saturday 16 April 2011] [16:17:55] <thatch_>	I also use it to gather system stats, and as the backend communication layer for my cloud controller
| [Saturday 16 April 2011] [16:18:17] <thatch_>	I have a bunch of explanations here:
| [Saturday 16 April 2011] [16:18:27] <thatch_>	http://red45.wordpress.com/
| [Saturday 16 April 2011] [16:18:50] <guido_g>	nice
| [Saturday 16 April 2011] [16:18:55] <thatch_>	thanks
| [Saturday 16 April 2011] [16:19:57] <guido_g>	i thnink pieterh should know about your projects
| [Saturday 16 April 2011] [16:20:05] <thatch_>	pieterh?
| [Saturday 16 April 2011] [16:20:17] <guido_g>	he's the uber-marketing guy for mq
| [Saturday 16 April 2011] [16:20:34] <thatch_>	Should I post to the mailing list?
| [Saturday 16 April 2011] [16:20:50] <guido_g>	yes, i think he'll love it
| [Saturday 16 April 2011] [16:20:53] <thatch_>	I would love to be on the list "stuf made with zeromq"
| [Saturday 16 April 2011] [16:21:01] <thatch_>	ok, I will do just that
| [Saturday 16 April 2011] [16:21:08] <guido_g>	and i'm sure he'll ask you to add the projects to the wiki :)
| [Saturday 16 April 2011] [16:21:46] <thatch_>	sweet, because I want more attention for salt, it is amazing what zeromq has enabled me to do with it
| [Saturday 16 April 2011] [16:22:23] <thatch_>	I will have a full replacement backend for nagios and munin/cactai soo based on salt and on zeromq
| [Saturday 16 April 2011] [16:22:38] <guido_g>	sounds great
| [Saturday 16 April 2011] [16:22:48] <guido_g>	all python based?
| [Saturday 16 April 2011] [16:22:51] <thatch_>	I think it will be
| [Saturday 16 April 2011] [16:22:56] <thatch_>	yes, all python
| [Saturday 16 April 2011] [16:23:07] <thatch_>	well, and some cythin for the bits that need speed of course
| [Saturday 16 April 2011] [16:23:11] <thatch_>	cython
| [Saturday 16 April 2011] [16:23:29] <guido_g>	of course
| [Saturday 16 April 2011] [16:23:51] <guido_g>	http://www.zeromq.org/docs:labs  <- page with the projects
| [Saturday 16 April 2011] [16:24:55] <thatch_>	Sweet, a posting I wil go
| [Saturday 16 April 2011] [16:27:06] <guido_g>	have fun!
| [Saturday 16 April 2011] [18:08:12] <cmarth>	I installed the 2.1.4 released on OS X 10.6.7 with : ./configure; make; make install.  All seemed to work. Now, trying to link the hello world server example from "The Guide" I get a "Undefined symbols for architecture x86_64" for anything 0MQ related.  Any thoughts?
| [Saturday 16 April 2011] [19:08:33] <cmarth>	Never mind - forgot to add -lzmq to my gcc ...
| [Saturday 16 April 2011] [19:15:59] <Toba>	never forget!
| [Sunday 17 April 2011] [03:26:16] <rod_>	Hi, i'm new to 0mq so forgive me if my question has an obvious answer.  What i'm trying to do use use a REQ socket to receive a request, then dispatch a job to worker threads which call back when they're done.  But it seems with the REQ socket type you need to send a reply before you can receive another request, is this true?  if so is there another solution for my problem?  Thanks.
| [Sunday 17 April 2011] [03:27:38] <Toba>	you have to use REP socket for the server side (the one receiving requests) not a 
| [Sunday 17 April 2011] [03:27:46] <Toba>	you use REQ on the side making the requests.
| [Sunday 17 April 2011] [03:27:56] <Toba>	this may be your first problem :)
| [Sunday 17 April 2011] [03:28:09] <rod_>	ah yes sorry that's what i meant :D
| [Sunday 17 April 2011] [03:28:25] <rod_>	(see, i am new to this!)
| [Sunday 17 April 2011] [03:28:29] <pieterh>	rod_: it's explained in the Guide
| [Sunday 17 April 2011] [03:28:34] <Toba>	I don't know a way to work around this, no.
| [Sunday 17 April 2011] [03:28:40] <Toba>	but, the Guide is all knowing, and eternal.
| [Sunday 17 April 2011] [03:28:48] <pieterh>	if you want to handle multiple requests in parallel, use a ROUTER socket
| [Sunday 17 April 2011] [03:29:03] <pieterh>	aka xrep
| [Sunday 17 April 2011] [03:29:33] <pieterh>	there is an example that does exactly what you want, asyncsrv
| [Sunday 17 April 2011] [03:29:37] <rod_>	ah perfect.  ok i'll give that a go, thanks pieterh!
| [Sunday 17 April 2011] [03:30:37] <pieterh>	http://zguide.zeromq.org/page:all#Asynchronous-Client-Server
| [Sunday 17 April 2011] [03:30:52] <pieterh>	however, before trying that, please do read & understand chapters 1 and 2
| [Sunday 17 April 2011] [03:32:29] <rod_>	i've made it to the end of chapter 2 so far, but i'm trying to build some examples to help me learn (so might be jumping ahead too which is the problem here i think)
| [Sunday 17 April 2011] [04:26:41] <guyvdb_>	Hi, I was listening to a video of Zed Shaw speaking from the zmq site. He stated something along the lines of do not use zmq over the internet. I.e. keep it within your lan for connecting server processes. Is this correct?
| [Sunday 17 April 2011] [04:26:43] <guido_g>	ahhh... salt already made it into the wiki
| [Sunday 17 April 2011] [04:27:42] <guido_g>	guyvdb_: sure, and you can always use a vpn
| [Sunday 17 April 2011] [04:28:22] <pieterh>	guyvdb_: 0MQ sockets tend to crash if you throw garbage at them
| [Sunday 17 April 2011] [04:29:39] <guyvdb_>	hmm ... I have a bunch of embedded devices that connect via 3G that I want to keep track of. After Zeds comments my idea is asio between well known address (broker) and clients and then zmq in the back to worker processes. Does this make sense?
| [Sunday 17 April 2011] [04:31:42] <pieterh>	guyvdb_: asio isn't going to be more secure than 0MQ
| [Sunday 17 April 2011] [04:32:04] <pieterh>	well, perhaps it is... yes, this makes sense
| [Sunday 17 April 2011] [04:32:22] <pieterh>	if I was doing it over public Internet I'd use HTTP for the server
| [Sunday 17 April 2011] [04:32:40] <guido_g>	why?
| [Sunday 17 April 2011] [04:33:07] <guyvdb_>	hmm I thought of that... but I want allways connected... I.e. server push to client...
| [Sunday 17 April 2011] [04:33:10] <guido_g>	i mean http is ok, but not the answer to everything
| [Sunday 17 April 2011] [04:33:21] <pieterh>	guido_g: several reasons, but mainly it's friendly for sysadmins (ports 80 and 443), has proven security (TLS), and has stacks in clients
| [Sunday 17 April 2011] [04:33:43] <pieterh>	guyvdb_: you can quite easily do server push using long polling
| [Sunday 17 April 2011] [04:34:16] <guyvdb_>	would http long poll make sense? This seems like a bit of a hack when i could just use tcp with thrift or protocol buffer
| [Sunday 17 April 2011] [04:34:34] <guido_g>	long polling and mobiles devices isn't that clever, to get a reasonable reaction time you to wake up the device quite often
| [Sunday 17 April 2011] [04:34:51] <guyvdb_>	The clients are embedded bits of hardware... no user interface, etc
| [Sunday 17 April 2011] [04:35:11] <pieterh>	guyvdb_: http long poll is nothing special, but you may need some intelligence in the server
| [Sunday 17 April 2011] [04:35:24] <pieterh>	i.e. to not disconnect clients if they're silent
| [Sunday 17 April 2011] [04:36:00] <guyvdb_>	but would an ASIO server maintaining say 5000 connections with the clients not be better than long polling
| [Sunday 17 April 2011] [04:36:29] <pieterh>	guyvdb_: afaics it's precisely the same setup except that with HTTP you get a standard answer to parts of the problem
| [Sunday 17 April 2011] [04:36:30] <guido_g>	and find someone who did that to ask him how the carriers behave in this case
| [Sunday 17 April 2011] [04:36:45] <guyvdb_>	I also want to implement heartbeat ala AMQP or something like that
| [Sunday 17 April 2011] [04:37:00] <pieterh>	you would want a friendly http server
| [Sunday 17 April 2011] [04:37:27] <guido_g>	and websockets :)
| [Sunday 17 April 2011] [04:37:37] <guyvdb_>	any suggestions? mongrel 2? ngnix
| [Sunday 17 April 2011] [04:37:54] <guyvdb_>	There is no web browser involved
| [Sunday 17 April 2011] [04:37:57] <guido_g>	mongrel2 is of course the first choice if you want to use mq
| [Sunday 17 April 2011] [04:38:04] <pieterh>	guyvdb_: I'd suggest mongrel2, yes, mainly because you can probably tweak it if you need it
| [Sunday 17 April 2011] [04:38:14] <pieterh>	also, take a look at restms.org 
| [Sunday 17 April 2011] [04:38:25] <guido_g>	guyvdb_: websockets is an hhtp protocol extension, no browser needed
| [Sunday 17 April 2011] [04:38:33] <guido_g>	guyvdb_: but is was more of a joke
| [Sunday 17 April 2011] [04:38:35] <pieterh>	guyvdb_: do you have security requirements?
| [Sunday 17 April 2011] [04:39:03] <guyvdb_>	yes.. i want a pki infrastructure where i am CA and all clients must have valid certs
| [Sunday 17 April 2011] [04:39:27] <pieterh>	so using https gives you this basically for free
| [Sunday 17 April 2011] [04:39:31] <guido_g>	then use a good http kit
| [Sunday 17 April 2011] [04:39:50] <guyvdb_>	yea... does mongrel2 use openssl?
| [Sunday 17 April 2011] [04:39:54] <pieterh>	after that you can use various techniques to switch to a bidirectional async protocol on top of http
| [Sunday 17 April 2011] [04:40:01] <pieterh>	guyvdb_: i assume it does
| [Sunday 17 April 2011] [04:40:50] <guyvdb_>	hmm any insight into a bidirectional async protocol on http... have you seen any implementations / papers / blogs on this?
| [Sunday 17 April 2011] [04:40:55] <pieterh>	guyvdb_: the very simplest is to open two connections per client, one for reading, one for writing
| [Sunday 17 April 2011] [04:41:05] <pieterh>	reading uses long polling (see restms for some hints)
| [Sunday 17 April 2011] [04:41:11] <pieterh>	writing just posts stuff
| [Sunday 17 April 2011] [04:41:39] <pieterh>	a more efficient approach is to use the http protocol upgrade method
| [Sunday 17 April 2011] [04:41:55] <pieterh>	which lets you start a http session, then switch to your own binary async protocol afterwards
| [Sunday 17 April 2011] [04:42:09] <pieterh>	that requires a cooperative http server, obviously
| [Sunday 17 April 2011] [04:42:25] <guyvdb_>	that sounds promising
| [Sunday 17 April 2011] [04:42:36] <pieterh>	i believe there are quite a few such stacks already built
| [Sunday 17 April 2011] [04:43:01] <pieterh>	you could look at http://bwtp.wikidot.com/ for inspiration
| [Sunday 17 April 2011] [04:43:33] <pieterh>	websockets is meant to standardize this area but it's stuck in endless ietf discussions
| [Sunday 17 April 2011] [04:44:27] <pieterh>	an example implementation of bwtp: http://code.google.com/p/serf/
| [Sunday 17 April 2011] [04:45:16] <guyvdb_>	Ok... i think that is a lot for me to absorb right now... going to start with lots of reading :) Thanks pieterh you have been very helpful
| [Sunday 17 April 2011] [04:45:35] <pieterh>	guyvdb_: my advice would be to start with a minimal proof of concept using something like restms's transport layer (resttl)
| [Sunday 17 April 2011] [04:45:51] <pieterh>	and if you find http works for you, look at more efficient designs
| [Sunday 17 April 2011] [04:46:05] <pieterh>	let us know how you get on :)
| [Sunday 17 April 2011] [04:46:27] <guyvdb_>	will do... thx
| [Sunday 17 April 2011] [06:25:43] <guido_g>	i will not implement this!  https://twitter.com/#!/hintjens/status/59561500293083136  
| [Sunday 17 April 2011] [06:28:41] <headzone>	good, we're relying on you to implement zeromq over BLOAT (RFC 3252)
| [Sunday 17 April 2011] [06:28:50] <headzone>	that clearly takes priority
| [Sunday 17 April 2011] [06:37:53] <guido_g>	:)
| [Sunday 17 April 2011] [07:34:38] <wayneeseguin>	Is there an example of using zeromq with a C program ?
| [Sunday 17 April 2011] [07:34:44] <wayneeseguin>	I am reading the docs but 
| [Sunday 17 April 2011] [07:34:49] <wayneeseguin>	would like a full example to look at 
| [Sunday 17 April 2011] [07:39:17] <wayneeseguin>	Perhaps I can glean this from mongrel2...
| [Sunday 17 April 2011] [07:43:22] <guido_g>	wayneeseguin: see the guide
| [Sunday 17 April 2011] [07:43:29] <guido_g>	full of c it is
| [Sunday 17 April 2011] [07:44:47] <wayneeseguin>	guido_g: I've ben looking at http://libzapi.zeromq.org/
| [Sunday 17 April 2011] [07:45:06] <wayneeseguin>	guido_g: But I was looking for a simple example of usage, is there another page with that? or is that not the guidee
| [Sunday 17 April 2011] [07:47:05] <headzone>	wayneeseguin: http://zguide.zeromq.org/
| [Sunday 17 April 2011] [07:47:10] <headzone>	every example is available in c
| [Sunday 17 April 2011] [07:52:15] <wayneeseguin>	*awesome*
| [Sunday 17 April 2011] [07:52:17] <wayneeseguin>	thank you both
| [Sunday 17 April 2011] [07:52:50] <wayneeseguin>	I was simply looing at the wrong pages :)
| [Sunday 17 April 2011] [13:14:45] <seangrove>	Hey all, what are unnamed sessions, and why would an assertion about them be failing?
| [Sunday 17 April 2011] [13:18:29] <mikko>	seangrove: what is the exact assertion?
| [Sunday 17 April 2011] [13:19:23] <seangrove>	Assertion failed: unnamed_sessions.empty () (socket_base.cpp:507)
| [Sunday 17 April 2011] [13:20:05] <seangrove>	So, I'm probably mixing up a few pieces here
| [Sunday 17 April 2011] [13:20:18] <seangrove>	But trying to get my head around some of the vocabulary
| [Sunday 17 April 2011] [13:24:40] <seangrove>	hmm
| [Sunday 17 April 2011] [13:24:47] <seangrove>	So this seems to happen right around forking
| [Sunday 17 April 2011] [13:25:23] <seangrove>	If I call ZMQ::Context.new(1) after forking, or don't call it at all, I get the assertion failure and a segfault
| [Sunday 17 April 2011] [13:25:39] <seangrove>	If I call ZMQ::Context.new(1) before forking, I only get the assertion failure
| [Sunday 17 April 2011] [13:28:05] <seangrove>	mikko: Any suggestions on where to read up to understand this?
| [Sunday 17 April 2011] [13:31:54] <mikko>	you should have one context per process
| [Sunday 17 April 2011] [13:32:02] <mikko>	i don't think context survices fork
| [Sunday 17 April 2011] [13:32:28] <mikko>	what language is this?
| [Sunday 17 April 2011] [13:32:52] <seangrove>	Ruby
| [Sunday 17 April 2011] [13:33:01] <seangrove>	I know the one-context-per-process
| [Sunday 17 April 2011] [13:33:24] <seangrove>	Should I create a new context in the parent pre-fork, the child-post-fork, or the parent-post-fork?
| [Sunday 17 April 2011] [13:33:34] <seangrove>	I believe the guide says in the parent pre-fork
| [Sunday 17 April 2011] [13:35:30] <mikko>	i think in each child after fork
| [Sunday 17 April 2011] [13:35:55] <seangrove>	Hmm, that gets me a segfault
| [Sunday 17 April 2011] [13:36:00] <seangrove>	I wonder if it's a library version problem
| [Sunday 17 April 2011] [13:36:06] <seangrove>	Certainly possible
| [Sunday 17 April 2011] [13:37:32] <seangrove>	And is that regardless of whether the child process uses anythign zmq-related?
| [Sunday 17 April 2011] [13:37:51] <seangrove>	None of my child processes do anything with zmq
| [Sunday 17 April 2011] [13:53:32] <sustrik>	seangrove: if you create new context in the child if should work ok
| [Sunday 17 April 2011] [13:53:40] <sustrik>	if it does not, it's a bug
| [Sunday 17 April 2011] [13:53:48] <sustrik>	please, do report it
| [Sunday 17 April 2011] [13:56:12] <seangrove>	sustrik: Ok, sounds good
| [Sunday 17 April 2011] [13:56:18] <seangrove>	Thanks for the tip
| [Sunday 17 April 2011] [13:56:32] <seangrove>	I need to refactor zmq out of the frontend of my app right now anyway
| [Sunday 17 April 2011] [13:57:36] <seangrove>	Put it where it really belongs 
| [Monday 18 April 2011] [02:14:12] <NikoS>	hi, all. I'm testing my application based on zmq with pub/sub sockets. Test creates 1000 threads which emulates chat, each thread has own sub socket for recieving msgs and use general pub socket to send msg to chat. Application crashes after ~550 threads has joined to chat with error "ZMQError: Too many open files". I've increased ulimit, but anyway it crashes after ~550 threads
| [Monday 18 April 2011] [02:15:33] <NikoS>	I forgot to add that i write on python with pyzmq
| [Monday 18 April 2011] [02:16:40] <NikoS>	Has anyone tested zeromq application on same manner?
| [Monday 18 April 2011] [02:16:46] <guido_g>	which ulimit setting did yoi increase and how?
| [Monday 18 April 2011] [02:16:59] <guido_g>	and why do you do so much threads?
| [Monday 18 April 2011] [02:17:12] <guido_g>	it's not a mq problem at all
| [Monday 18 April 2011] [02:17:40] <NikoS>	i've set it to 65535
| [Monday 18 April 2011] [02:18:02] <guido_g>	set what to 65535?
| [Monday 18 April 2011] [02:19:22] <NikoS>	fs.file_max in /etc/sysctl.conf
| [Monday 18 April 2011] [02:21:00] <guido_g>	check if "ulimit -n" changed
| [Monday 18 April 2011] [02:21:23] <NikoS>	done ) it's realy 65535
| [Monday 18 April 2011] [02:22:11] <guido_g>	in the same shell the python program runs?
| [Monday 18 April 2011] [02:22:18] <NikoS>	yes
| [Monday 18 April 2011] [02:23:31] <guido_g>	which transport you're using?
| [Monday 18 April 2011] [02:24:46] <NikoS>	Transport? Is it subscriber/publisher pattern?
| [Monday 18 April 2011] [02:24:59] <guido_g>	*sigh*
| [Monday 18 April 2011] [02:25:32] <guido_g>	is it tcp, incproc or what?
| [Monday 18 April 2011] [02:25:32] <NikoS>	)
| [Monday 18 April 2011] [02:26:36] <NikoS>	ooph ) tcp
| [Monday 18 April 2011] [02:27:20] <guido_g>	then check with netstat how many sockets are opened when the program runs
| [Monday 18 April 2011] [02:35:17] <NikoS>	It seems that application opens more than 2000 unix sockets
| [Monday 18 April 2011] [03:06:01] <sustrik>	NikoS: there's max_sockets limit in 0mq
| [Monday 18 April 2011] [03:06:10] <sustrik>	set by defaault to 512
| [Monday 18 April 2011] [03:06:28] <sustrik>	if you need more sockets, you have to modify src/config.hpp
| [Monday 18 April 2011] [03:06:34] <sustrik>	and recompile the whole thing
| [Monday 18 April 2011] [04:59:57] <NikolaVeber>	is zhelpers library maintained along with the distribution?
| [Monday 18 April 2011] [05:00:16] <NikolaVeber>	it is used in most of the examples in the guide
| [Monday 18 April 2011] [07:25:01] <NikolaVeber>	does anyone have experience with php-zmq?
| [Monday 18 April 2011] [07:28:43] <sustrik>	mikko should, he's the author :)
| [Monday 18 April 2011] [07:29:59] <NikolaVeber>	:)
| [Monday 18 April 2011] [07:30:22] <NikolaVeber>	Docs say its experimental, I'm just wondering how experimental :)
| [Monday 18 April 2011] [07:34:56] <mikko>	a bit
| [Monday 18 April 2011] [07:35:23] <mikko>	it's fairly stable
| [Monday 18 April 2011] [07:35:31] <mikko>	i think it's going to be 1.0.0 very soon
| [Monday 18 April 2011] [07:42:21] <NikolaVeber>	great! :)
| [Monday 18 April 2011] [07:43:45] <mikko>	the api is unlikely to change in near future
| [Monday 18 April 2011] [07:43:54] <mikko>	at least not in a backwards incompatible way
| [Monday 18 April 2011] [13:05:41] <rod_>	Hi, I'm trying to work through some of the examples in chapter 3 of the zguide in PHP, and have come to some that use the Zmsg class - but can't find where this is available?  Or am I supposed to write it myself?  Pointers appreciated, cheers
| [Monday 18 April 2011] [13:11:34] <guido_g>	https://github.com/imatix/zguide/tree/master/examples/PHP
| [Monday 18 April 2011] [13:12:31] <rod_>	aha wicked - looks like lots of good stuff there.  thanks very much guido_g.
| [Monday 18 April 2011] [17:24:17] <benwaine>	Hello
| [Monday 18 April 2011] [17:25:03] <benwaine>	Im having loads of fun with 0mq but have hit my first problem. Anyone round to help?
| [Monday 18 April 2011] [17:26:22] <mikko>	benwaine: yep
| [Monday 18 April 2011] [17:26:28] <benwaine>	woo hoo :)
| [Monday 18 April 2011] [17:26:52] <benwaine>	A quick intro to what im doing:
| [Monday 18 April 2011] [17:27:53] <benwaine>	I have a connection to twitter with an open stream. As tweets come in they get sent to workers using push and pull sockets.
| [Monday 18 April 2011] [17:28:20] <benwaine>	I then had them fan back into a sink as in the example in the guide
| [Monday 18 April 2011] [17:28:57] <benwaine>	all good so far. However I then want to push all the processed tweets into a queue device
| [Monday 18 April 2011] [17:29:28] <benwaine>	I get the error: Fatal error: Uncaught exception 'ZMQSocketException' with message 'Failed to bind the ZMQ: Operation not supported by device' 
| [Monday 18 April 2011] [17:29:49] <benwaine>	when trying to bin the queue device to localhost
| [Monday 18 April 2011] [17:30:02] <mikko>	you have to bind by ip / iface
| [Monday 18 April 2011] [17:30:06] <mikko>	not by hostname
| [Monday 18 April 2011] [17:32:22] <benwaine>	ahh i see. Is that true only of devices? I have it working with localhost in another example? 
| [Monday 18 April 2011] [17:32:44] <mikko>	benwaine: it shouldn't really work
| [Monday 18 April 2011] [17:32:58] <mikko>	unless it's been fixed very recently
| [Monday 18 April 2011] [17:33:11] <mikko>	connecting by hostname is ok
| [Monday 18 April 2011] [17:33:13] <mikko>	but not binding
| [Monday 18 April 2011] [17:33:34] <benwaine>	ahh yes - i can see in my code I am connecting not binding
| [Monday 18 April 2011] [17:34:09] <benwaine>	Is it advisable to bind by IP or just use *:port ?
| [Monday 18 April 2011] [17:37:13] <mikko>	maybe *
| [Monday 18 April 2011] [17:37:18] <mikko>	makes it a bit more portable
| [Monday 18 April 2011] [17:37:31] <mikko>	if binding to 0.0.0.0 is not a problem there
| [Monday 18 April 2011] [17:37:33] <mikko>	brb
| [Monday 18 April 2011] [17:57:31] <benwaine>	Mikko: That got me back on track. Thanks very much.
| [Tuesday 19 April 2011] [04:42:03] <djc>	pieter_hintjens: you have "probabably" in the guide
| [Tuesday 19 April 2011] [04:47:03] <djc>	I was wondering, are subscription filters applied on the publisher, on the subscriber, or is that behavior undefined?
| [Tuesday 19 April 2011] [04:50:31] <pieter_hintjens>	djc: hi
| [Tuesday 19 April 2011] [04:50:41] <pieter_hintjens>	they're applied on the subscriber at present
| [Tuesday 19 April 2011] [04:51:16] <djc>	that's what I thought, perhaps it should be in the docs somewhere (possibly with caveat about future changes)
| [Tuesday 19 April 2011] [04:51:34] <pieterh>	where does the guide say 'probably'? I can't find that
| [Tuesday 19 April 2011] [04:51:59] <djc>	http://zguide.zeromq.org/page:all#toc40
| [Tuesday 19 April 2011] [04:53:06] <pieterh>	that points to a section on zero copy... ??
| [Tuesday 19 April 2011] [04:53:24] <djc>	yeah, and in the second line it has "probabably"
| [Tuesday 19 April 2011] [04:53:55] <pieterh>	heh
| [Tuesday 19 April 2011] [04:54:45] <pieterh>	djc: thanks for catching that, fixing it now
| [Tuesday 19 April 2011] [05:14:46] <djc>	pieterh: so can you add something about the filtering behavior, too?
| [Tuesday 19 April 2011] [05:14:56] <djc>	either to the guide or to the reference
| [Tuesday 19 April 2011] [05:15:13] <pieterh>	I don't have write access to the reference
| [Tuesday 19 April 2011] [05:15:22] <pieterh>	but I'll add this to the guide, yes
| [Tuesday 19 April 2011] [05:15:44] <djc>	nice
| [Tuesday 19 April 2011] [05:16:05] <guido_g>	pieterh: and while you're at it: https://github.com/imatix/zguide/issues/50  :)
| [Tuesday 19 April 2011] [05:16:09] <djc>	final question for the day: is there any intended ETA for 2.1.5? as the gentoo maintainer, I'm kind of looking forward to 2.1.5 :)
| [Tuesday 19 April 2011] [05:16:11] <guido_g>	howdy all, btw
| [Tuesday 19 April 2011] [05:16:16] <pieterh>	hi guido_g
| [Tuesday 19 April 2011] [05:16:30] <pieterh>	djc: there are no real issues with 2.1.4 in fact
| [Tuesday 19 April 2011] [05:16:44] <drbobbeaty>	pieterh: I need to talk to David still about the support contract. I'm sorry it's taking so long, but I'm in the middle of a near-impossible time-frame.
| [Tuesday 19 April 2011] [05:17:00] <pieterh>	drbobbeaty: np
| [Tuesday 19 April 2011] [05:17:12] <drbobbeaty>	pieterh: the only issue I know of with 2.1.4 is the one Martin patched just today with the message bit flags.
| [Tuesday 19 April 2011] [05:17:25] <djc>	pieterh: sure, I just want --with-system-pgm
| [Tuesday 19 April 2011] [05:17:32] <drbobbeaty>	I'm going to try it today
| [Tuesday 19 April 2011] [05:17:33] <pieterh>	djc, ah, ok
| [Tuesday 19 April 2011] [05:17:44] <pieterh>	drbobbeaty: that was message validation afaik
| [Tuesday 19 April 2011] [05:17:52] <pieterh>	i.e. runtime validation that message objects are sane
| [Tuesday 19 April 2011] [05:17:58] <drbobbeaty>	yes indeed.
| [Tuesday 19 April 2011] [05:18:23] <pieterh>	djc: I'll push the 2.1.5 release up for you then
| [Tuesday 19 April 2011] [05:18:51] <djc>	awesome
| [Tuesday 19 April 2011] [05:20:16] <pieterh>	guido_g: would a link to the git repository & explanation be OK?
| [Tuesday 19 April 2011] [05:20:29] <guido_g>	pieterh: i think so
| [Tuesday 19 April 2011] [05:20:37] <pieterh>	ok, making that now
| [Tuesday 19 April 2011] [05:21:16] <guido_g>	the issue came up yesterday where one looked for something but wasn't aware of the Guides repo and the examples
| [Tuesday 19 April 2011] [05:22:31] <djc>	pieterh: also, in the "Getting the Message Out" section, it would be nice if "In Chapter Two I'll explain how to" came with a more concrete reference to a section in chapter 2
| [Tuesday 19 April 2011] [05:23:01] <pieterh>	djc: I don't like making concrete references because they're a pain to maintain
| [Tuesday 19 April 2011] [05:23:16] <pieterh>	lacking tools to do it properly, for now
| [Tuesday 19 April 2011] [05:23:21] <pieterh>	will think about improving this...
| [Tuesday 19 April 2011] [05:24:47] <djc>	what tech are you using for the guide?
| [Tuesday 19 April 2011] [05:25:16] <pieterh>	djc: well, it's in the repo bin directory, a perl script that mangles text into wikidot format
| [Tuesday 19 April 2011] [05:25:17] <djc>	it feels kind of silly that you only have a kind of abstract reference and I have to go hunting for the section if I want it, particularly for html docs
| [Tuesday 19 April 2011] [05:25:25] <pieterh>	yeah, I know
| [Tuesday 19 April 2011] [05:25:40] <djc>	perhaps you should learn sphinx?
| [Tuesday 19 April 2011] [05:25:47] <djc>	it's pretty easy and very powerful
| [Tuesday 19 April 2011] [05:25:58] <pieterh>	djc: won't help
| [Tuesday 19 April 2011] [05:26:04] <pieterh>	the tool chain is very specific
| [Tuesday 19 April 2011] [05:26:21] <djc>	what's very specific about it?
| [Tuesday 19 April 2011] [05:26:40] <pieterh>	well, it turns text diagrams into images, extracts code blocks and colorizes them
| [Tuesday 19 April 2011] [05:26:45] <pieterh>	builds all the links in the text
| [Tuesday 19 April 2011] [05:26:49] <djc>	sphinx comes with a graphviz extension, so you can still do the graphs
| [Tuesday 19 April 2011] [05:26:59] <djc>	and it also has code blocks and syntax highlighting
| [Tuesday 19 April 2011] [05:27:01] <djc>	all built in
| [Tuesday 19 April 2011] [05:27:07] <pieterh>	djc: forget it :-) srsly
| [Tuesday 19 April 2011] [05:27:13] <djc>	mkay
| [Tuesday 19 April 2011] [05:27:20] <pieterh>	unless you're willing to rewrite the whole guide to fit...
| [Tuesday 19 April 2011] [05:28:25] <djc>	I could take a stab at it, if you're willing to use sphinx after that :)
| [Tuesday 19 April 2011] [05:28:25] <pieterh>	however, if you want to collect any weak references in the text, I'll turn them into hyperlinks
| [Tuesday 19 April 2011] [05:28:39] <pieterh>	djc: you're welcome to play with it, the text is all open source
| [Tuesday 19 April 2011] [05:28:55] <pieterh>	but seriously, it's not going to work, there's a reason I made this from scratch
| [Tuesday 19 April 2011] [07:04:02] <drbobbeaty>	pieterh: Are you planning on a 2.1.5? And if so, will the patch Martin sent this morning about the Seg Fault on zmq_msg_size() make it in? And when would you be cutting that 2.1.5 release?
| [Tuesday 19 April 2011] [07:10:07] <sustrik>	drbobbeaty: hi
| [Tuesday 19 April 2011] [07:10:15] <sustrik>	what version are you using today?
| [Tuesday 19 April 2011] [07:11:02] <drbobbeaty>	2.1.4, and I can patch it with your patch, but I wondered if Pieter was going to cut another release sometime soon. I thought I saw him say something about it earlier this morning
| [Tuesday 19 April 2011] [07:11:44] <sustrik>	not sure whether the patch would apply cleanly
| [Tuesday 19 April 2011] [07:12:10] <sustrik>	i guess, i should commit it to the master
| [Tuesday 19 April 2011] [07:12:18] <sustrik>	and move it to pieter for backporting
| [Tuesday 19 April 2011] [07:12:26] <drbobbeaty>	That would be great.
| [Tuesday 19 April 2011] [07:12:40] <sustrik>	ok
| [Tuesday 19 April 2011] [07:13:13] <sustrik>	done
| [Tuesday 19 April 2011] [07:13:47] <drbobbeaty>	Wow... exceptionally fast. Thanks.
| [Tuesday 19 April 2011] [08:18:17] <NikolaVeber>	mikko, I can't find the php-zmq package in PECL
| [Tuesday 19 April 2011] [08:18:25] <NikolaVeber>	is that a feature or a bug? :)
| [Tuesday 19 April 2011] [08:24:35] <mikko>	NikolaVeber: feature
| [Tuesday 19 April 2011] [08:24:45] <mikko>	http://pear.zero.mq/
| [Tuesday 19 April 2011] [08:24:53] <NikolaVeber>	then there is a bug in the installation docs ;)
| [Tuesday 19 April 2011] [08:25:10] <mikko>	php docgen autogenerates those
| [Tuesday 19 April 2011] [08:25:14] <NikolaVeber>	but pear works even better :)
| [Tuesday 19 April 2011] [08:25:22] <mikko>	i'll update them at some point
| [Tuesday 19 April 2011] [08:25:42] <NikolaVeber>	great, thanks!
| [Tuesday 19 April 2011] [08:25:55] <NikolaVeber>	maybe just update README
| [Tuesday 19 April 2011] [08:26:04] <NikolaVeber>	thats the first place I looked
| [Tuesday 19 April 2011] [08:27:36] <mikko>	updated
| [Tuesday 19 April 2011] [08:50:16] <NikolaVeber>	thanks!
| [Tuesday 19 April 2011] [10:01:43] <NikolaVeber>	mikko, I'm getting 'Failed to bind the ZMQ: Address already in use'
| [Tuesday 19 April 2011] [10:01:51] <NikolaVeber>	on what I believe should be a persistent socket
| [Tuesday 19 April 2011] [10:02:54] <NikolaVeber>	I have set $context = new ZMQContext(1, true);
| [Tuesday 19 April 2011] [10:03:05] <NikolaVeber>	and $queue = new ZMQSocket($context, ZMQ::SOCKET_PUSH, "MySock1");
| [Tuesday 19 April 2011] [10:03:16] <NikolaVeber>	then bind to tcp://*:5555
| [Tuesday 19 April 2011] [10:03:27] <mikko>	you bind persistent socket only once
| [Tuesday 19 April 2011] [10:03:47] <mikko>	you might have socket in the background that's been bound 
| [Tuesday 19 April 2011] [10:03:55] <mikko>	the persistent sockets work a lot better with connecting sockets
| [Tuesday 19 April 2011] [10:04:30] <NikolaVeber>	so I should check in each call if the persistent socket is up and running
| [Tuesday 19 April 2011] [10:04:41] <NikolaVeber>	and if not, bind it?
| [Tuesday 19 April 2011] [10:05:56] <guido_g>	it's not a matter of the mq socket, it's like that the port is already used
| [Tuesday 19 April 2011] [10:06:24] <guido_g>	given that you bind to every available interface this is not surprising
| [Tuesday 19 April 2011] [10:07:13] <NikolaVeber>	I'm testing this isolated, after restarting the apache,  I can bind again
| [Tuesday 19 April 2011] [10:07:50] <NikolaVeber>	but I'll try with connecting, not binding
| [Tuesday 19 April 2011] [10:08:04] <NikolaVeber>	that I need to change anyhow.. :)
| [Tuesday 19 April 2011] [10:30:13] <mikko>	NikolaVeber: with connecting use the on_new callback
| [Tuesday 19 April 2011] [10:30:24] <mikko>	that is called only when new underlying socket is created
| [Tuesday 19 April 2011] [10:38:46] <neale1>	My introduction to 0MQ article was published in the April/May z/Journal (a web/paper magazine for IBM mainframe users). http://www.mainframezone.com/it-management/lightweight-messaging-middleware/P1
| [Tuesday 19 April 2011] [10:52:58] <mikko>	neale1: have you had any follow-ups / reactions?
| [Tuesday 19 April 2011] [10:54:44] <neale1>	It only came out a few days ago. It looks like I'll be presenting on it in Orlando in August at the IBM user group meeting "SHARE"
| [Tuesday 19 April 2011] [11:09:56] <NikolaVeber>	mikko, I followed this example
| [Tuesday 19 April 2011] [11:09:56] <NikolaVeber>	http://php.zero.mq/zmqsocket.connect.html
| [Tuesday 19 April 2011] [11:10:17] <NikolaVeber>	can you point me to the on_new references in the docs?
| [Tuesday 19 April 2011] [11:10:31] <NikolaVeber>	sorry
| [Tuesday 19 April 2011] [11:10:34] <NikolaVeber>	got it
| [Tuesday 19 April 2011] [11:22:58] <ianbarber>	neale1: very nice article!
| [Tuesday 19 April 2011] [11:25:02] <neale1>	Tks
| [Tuesday 19 April 2011] [11:43:56] <jfs>	anybody know if any problems building pyzmq (via easy_install pyzmq) on osx against zeromq 2.1.4? I'm getting the error "zmq/core/constants.c:2574: fatal error: error writing to -: Broken pipe"
| [Tuesday 19 April 2011] [13:39:31] <ketralnis>	How does setsockopt(ZMQ_SUBSCRIBE, filter) behave with multipart messages? Does it match only the first body?
| [Tuesday 19 April 2011] [14:16:06] <cremes>	ketralnis: it matches the bytes in the first message part only
| [Tuesday 19 April 2011] [14:16:35] <cremes>	so you should always prepend your topic to the first thing you send
| [Tuesday 19 April 2011] [14:21:32] <ketralnis>	cremes: thanks :)
| [Tuesday 19 April 2011] [14:21:46] <cremes>	you are welcome
| [Tuesday 19 April 2011] [14:49:14] <CudaDeveloper>	How do I get push/pull not to do fair sheduling? When one worker is much slower than the rest, fair scheduling means it holds everything up.
| [Tuesday 19 April 2011] [15:42:23] <cremes>	CudaDeveloper: fair scheduling is the only kind available for those sockets; if you need a different algo, you will need to roll
| [Tuesday 19 April 2011] [15:42:36] <cremes>	your own and (likely) build it on top of xreq/xrep
| [Tuesday 19 April 2011] [15:56:25] <crodas>	hi guys, I have little doubt about pubsub
| [Tuesday 19 April 2011] [15:56:30] <crodas>	is this the right place to ask?
| [Tuesday 19 April 2011] [15:56:36] <crodas>	or mailing list is better?
| [Tuesday 19 April 2011] [16:01:25] <crodas>	I'm building a chat server using pubsub. I'm wondering which is better, subscribe my peers to many channels, or if they listen to their account ID and I send one message to each one (message goes to channel) 
| [Tuesday 19 April 2011] [16:05:43] <cremes>	crodas: i would start with one pub socket for all channels
| [Tuesday 19 April 2011] [16:06:06] <cremes>	then each chat user would subscribe to the channels they care about
| [Tuesday 19 April 2011] [16:06:11] <crodas>	cremes: so the peers are subscribing to their channel ?
| [Tuesday 19 April 2011] [16:06:13] <crodas>	great
| [Tuesday 19 April 2011] [16:06:30] <crodas>	thanks
| [Tuesday 19 April 2011] [16:06:33] <cremes>	all chat messages go to a single pub socket
| [Tuesday 19 April 2011] [16:06:35] <cremes>	so, yes
| [Tuesday 19 April 2011] [16:06:54] <crodas>	btw, I'm going to give a talk about ZeroMQ in Jun :-)
| [Tuesday 19 April 2011] [16:07:01] <crodas>	it is so awesome that I have to tell the people about it
| [Tuesday 19 April 2011] [16:07:10] <cremes>	great enws
| [Tuesday 19 April 2011] [16:07:12] <crodas>	(I'm using it with PHP and NodeJS)
| [Tuesday 19 April 2011] [16:07:32] <cremes>	nodejs scales nicely so it will pair up with 0mq quite well
| [Tuesday 19 April 2011] [16:07:46] <crodas>	indeed
| [Tuesday 19 April 2011] [16:08:03] <crodas>	but mongrel2 with any other language (such as PHP) is awesome
| [Tuesday 19 April 2011] [16:12:32] <mikko>	crodas: where is the talk?
| [Tuesday 19 April 2011] [16:12:41] <crodas>	Rio de Janeiro, Brazil
| [Tuesday 19 April 2011] [16:12:50] <crodas>	it is 100% confirmed yet
| [Tuesday 19 April 2011] [16:12:56] <crodas>	but almost 
| [Tuesday 19 April 2011] [16:13:30] <mikko>	which conference is that?
| [Tuesday 19 April 2011] [16:17:47] <crodas>	I don't recall, looking no
| [Tuesday 19 April 2011] [16:17:49] <crodas>	*now*
| [Tuesday 19 April 2011] [16:17:57] <crodas>	FSLDC (Frum de Software Livre de Duque de Caxias)
| [Tuesday 19 April 2011] [16:18:25] <crodas>	http://forumsoftwarelivre.com.br/2011/
| [Tuesday 19 April 2011] [16:18:35] <crodas>	perhaps someone could record the talk
| [Tuesday 19 April 2011] [16:18:44] <sustrik>	nice
| [Tuesday 19 April 2011] [16:18:51] <crodas>	(It'd be in English, I don't speak Portuguese, just Spanish and English)
| [Tuesday 19 April 2011] [16:19:09] <sustrik>	once you have the talk confirmed, place a link to zero.mq page
| [Tuesday 19 April 2011] [16:19:35] <crodas>	how do I do that?
| [Tuesday 19 April 2011] [16:19:41] <sustrik>	it's wiki
| [Tuesday 19 April 2011] [16:19:51] <crodas>	cool, I'll do it
| [Tuesday 19 April 2011] [16:20:02] <sustrik>	great
| [Tuesday 19 April 2011] [16:21:13] <crodas>	I'll upload my slides next week
| [Tuesday 19 April 2011] [16:21:17] <crodas>	so I can have feedback
| [Tuesday 19 April 2011] [16:21:39] <crodas>	I'm kinda new with ZeroMQ (~2 months) but I'm using it already on various projects
| [Tuesday 19 April 2011] [16:25:42] <ianbarber>	to be honest, i think with 0mq you spend a few weeks learning everything the library can do, and then months understanding good messaging architectures :) that's part of the fun
| [Tuesday 19 April 2011] [16:27:11] <crodas>	ianbarber: actually Derick Rethans (I don't know how to spell it) showed me your video
| [Tuesday 19 April 2011] [16:27:22] <crodas>	I became a fun since then :-)
| [Tuesday 19 April 2011] [16:27:30] <crodas>	*fanatic*
| [Tuesday 19 April 2011] [16:27:34] <ianbarber>	:) 
| [Tuesday 19 April 2011] [16:27:50] <crodas>	kudos, I owe lots of beers
| [Tuesday 19 April 2011] [16:28:25] <ianbarber>	giving further talks is the best payback :) i'll have to thank derick next time i see him
| [Tuesday 19 April 2011] [16:28:56] <crodas>	I'll spread the word here in South America
| [Tuesday 19 April 2011] [23:33:02] <crodas>	does pub/sub works with 'inproc' ?
| [Wednesday 20 April 2011] [00:51:01] <sustrik>	crodas: yes
| [Wednesday 20 April 2011] [00:51:30] <crodas>	sustrik: I supposed that, I can't make it work with node's driver
| [Wednesday 20 April 2011] [00:51:37] <crodas>	so it's a driver bug.
| [Wednesday 20 April 2011] [00:54:39] <sustrik>	possibly
| [Wednesday 20 April 2011] [01:10:40] <guido_g>	good morning all
| [Wednesday 20 April 2011] [01:11:01] <guido_g>	while browsing i found http://jeffkreeftmeijer.com/2010/why-arent-you-using-git-flow/
| [Wednesday 20 April 2011] [01:11:17] <guido_g>	just as a point for the next process discussion ,)
| [Wednesday 20 April 2011] [01:19:03] <sustrik>	thx
| [Wednesday 20 April 2011] [01:19:45] <guido_g>	i'm not sure it'll fit the mindset of you and the other main devs
| [Wednesday 20 April 2011] [01:26:52] <sustrik>	it was already discussed in the past
| [Wednesday 20 April 2011] [01:27:13] <sustrik>	the main problem, imo, is to agree on who's going to do what etc.
| [Wednesday 20 April 2011] [01:27:16] <guido_g>	oh sorry, i must have missed that
| [Wednesday 20 April 2011] [01:27:32] <sustrik>	the physical proces is just a consequence of that
| [Wednesday 20 April 2011] [01:28:07] <guido_g>	given that you don't know beforehand who will participate, this is a big problem
| [Wednesday 20 April 2011] [01:28:26] <sustrik>	there's me, mikko and pieter at least
| [Wednesday 20 April 2011] [01:28:34] <sustrik>	we are doing most of the work
| [Wednesday 20 April 2011] [01:28:40] <guido_g>	but the link wasn't meant to re-start that discussion
| [Wednesday 20 April 2011] [01:28:44] <guido_g>	ack
| [Wednesday 20 April 2011] [01:29:24] <guido_g>	we should talk about that at brussels
| [Wednesday 20 April 2011] [01:29:37] <sustrik>	definitely
| [Wednesday 20 April 2011] [01:31:23] <guido_g>	hmmm.... seems i need to write down the points i want to talk about
| [Wednesday 20 April 2011] [01:31:34] <sustrik>	sure, do so
| [Wednesday 20 April 2011] [01:31:38] <sustrik>	i should do the same
| [Wednesday 20 April 2011] [01:31:55] <sustrik>	maybe we can post that on the wiki page
| [Wednesday 20 April 2011] [01:32:18] <guido_g>	good idea
| [Wednesday 20 April 2011] [02:03:18] <guido_g>	added a few lines to the wiki page
| [Wednesday 20 April 2011] [03:39:22] <djc>	where is this talk video from ianbarber?
| [Wednesday 20 April 2011] [03:40:08] <ianbarber>	PHP UK 2011
| [Wednesday 20 April 2011] [04:01:20] <djc>	http://www.phpconference.co.uk/talk/zeromq-answer to be exact :)
| [Wednesday 20 April 2011] [04:01:21] <djc>	thanks
| [Wednesday 20 April 2011] [06:14:41] <pieterh>	hi folks
| [Wednesday 20 April 2011] [06:17:54] <mikko>	pieterh: hi
| [Wednesday 20 April 2011] [06:18:00] <mikko>	pieterh: two new attendees from london
| [Wednesday 20 April 2011] [06:18:04] <mikko>	possibly more coming later
| [Wednesday 20 April 2011] [06:18:06] <pieterh>	sweet!
| [Wednesday 20 April 2011] [06:18:19] <pieterh>	how are you doing mikko?
| [Wednesday 20 April 2011] [06:18:32] <pieterh>	still doing the weird stuff with the kinnect?
| [Wednesday 20 April 2011] [06:18:32] <mikko>	awesomely busy
| [Wednesday 20 April 2011] [06:18:35] <mikko>	yes
| [Wednesday 20 April 2011] [06:18:37] <pieterh>	:)
| [Wednesday 20 April 2011] [06:19:01] <mikko>	http://code.google.com/p/lecturerecorder/wiki/ProgramSummary
| [Wednesday 20 April 2011] [06:19:02] <pieterh>	i have a serious question for you
| [Wednesday 20 April 2011] [06:19:18] <mikko>	sure
| [Wednesday 20 April 2011] [06:19:25] <pieterh>	oso I'
| [Wednesday 20 April 2011] [06:19:39] <pieterh>	fingers aren't awake yet... 
| [Wednesday 20 April 2011] [06:19:46] <pieterh>	so I'd like to start on libzutil
| [Wednesday 20 April 2011] [06:20:35] <pieterh>	i'd like people who get the zeromq package to get a single library (libzmq) but containing libzutil as well
| [Wednesday 20 April 2011] [06:20:47] <pieterh>	is that possible in your opinion?
| [Wednesday 20 April 2011] [06:21:06] <pieterh>	assuming libzutil is a separate git, like libzapi, using autotools
| [Wednesday 20 April 2011] [06:21:29] <mikko>	how do you want them to get it?
| [Wednesday 20 April 2011] [06:21:36] <mikko>	single ./configure?
| [Wednesday 20 April 2011] [06:21:41] <pieterh>	yes, I think so
| [Wednesday 20 April 2011] [06:21:47] <pieterh>	but probably via a packaging project of some kind
| [Wednesday 20 April 2011] [06:21:53] <pieterh>	e.g. zeromq2-2
| [Wednesday 20 April 2011] [06:22:00] <mikko>	zeromq-bundle or something?
| [Wednesday 20 April 2011] [06:22:02] <pieterh>	actually, also including libzapi
| [Wednesday 20 April 2011] [06:22:11] <pieterh>	zeromq-bundle is right
| [Wednesday 20 April 2011] [06:22:32] <pieterh>	anyone going to libzmq git will get just the core library
| [Wednesday 20 April 2011] [06:22:33] <mikko>	you could create packaging project that contains simple build that invokes the sub builds
| [Wednesday 20 April 2011] [06:22:36] <pieterh>	yes
| [Wednesday 20 April 2011] [06:23:02] <pieterh>	hmm, excellent
| [Wednesday 20 April 2011] [06:23:27] <pieterh>	so zeromq2-2 can be this, simple build that invokes subbuilds for libzmq, libzutil, libzapi
| [Wednesday 20 April 2011] [06:24:07] <pieterh>	would you help me make this?
| [Wednesday 20 April 2011] [06:24:20] <pieterh>	all I need are some outlines, I can do all the grunt work
| [Wednesday 20 April 2011] [06:26:20] <mikko>	sure, this is very much similar to how openpgm is built inside zeromq build
| [Wednesday 20 April 2011] [06:26:36] <pieterh>	that's what I thought but I've not looked more closely
| [Wednesday 20 April 2011] [06:27:02] <pieterh>	ok, so I'll start with a minimal libzutil rsn, with one class, and then we can experiment with this
| [Wednesday 20 April 2011] [06:27:19] <pieterh>	zeromq2-2 will basically be the same stable 2.1 plus this extra stuff (zutil, zapi)
| [Wednesday 20 April 2011] [06:27:35] <pieterh>	the point is to make life easier for people when 3.0 arrives
| [Wednesday 20 April 2011] [06:27:42] <pieterh>	premigration
| [Wednesday 20 April 2011] [06:28:40] <pieterh>	sustrik: you around?
| [Wednesday 20 April 2011] [06:30:33] 	 * pieterh is going to make a 2.1.5 release today
| [Wednesday 20 April 2011] [07:07:12] 	 * pieterh has just pushed the 2.1.5 release
| [Wednesday 20 April 2011] [07:58:18] <NikolaVeber>	I'm trying to open one socket per thread
| [Wednesday 20 April 2011] [07:58:23] <NikolaVeber>	for a benchmark
| [Wednesday 20 April 2011] [07:58:35] <NikolaVeber>	and then stress the server
| [Wednesday 20 April 2011] [07:58:44] <NikolaVeber>	should I open one context
| [Wednesday 20 April 2011] [07:58:49] <NikolaVeber>	or one per thread?
| [Wednesday 20 April 2011] [07:59:54] <NikolaVeber>	does it make any sense at all, sending from multiple threads VS sequential loop
| [Wednesday 20 April 2011] [08:00:02] <NikolaVeber>	it's a PUSH socket
| [Wednesday 20 April 2011] [08:08:51] <pieterh>	hi NikolaVeber
| [Wednesday 20 April 2011] [08:09:17] <pieterh>	it makes no sense to start multiple threads
| [Wednesday 20 April 2011] [08:09:37] <pieterh>	unless you know you're full with 1 thread
| [Wednesday 20 April 2011] [08:09:53] <djc>	pieterh: thanks for the release
| [Wednesday 20 April 2011] [08:09:58] <djc>	mikko: around?
| [Wednesday 20 April 2011] [08:10:01] <pieterh>	djc: happy to oblige
| [Wednesday 20 April 2011] [08:11:05] <djc>	pieterh: --with-system-pgm doesn't seem to entirely do the trick here :(
| [Wednesday 20 April 2011] [08:11:20] <pieterh>	djc: interesting... mikko: you around?
| [Wednesday 20 April 2011] [08:11:35] <pieterh>	djc: you want to discuss this with mikko
| [Wednesday 20 April 2011] [08:11:41] <djc>	yeah, I figured :)
| [Wednesday 20 April 2011] [08:19:55] <NikolaVeber>	pieterh, ok, tx :)
| [Wednesday 20 April 2011] [08:20:24] <pieterh>	NikolaVeber: a single client thread, looping, can overwhelm a server that does *anything* at all with the messages
| [Wednesday 20 April 2011] [08:20:40] <pieterh>	the only reason to have multiple client threads is to test server parallelism
| [Wednesday 20 April 2011] [08:24:15] <NikolaVeber>	then it should work for me, I just need to bring the server to the max
| [Wednesday 20 April 2011] [08:24:22] <NikolaVeber>	and measure latencies along the way
| [Wednesday 20 April 2011] [08:36:13] <djc>	hmm, maybe I could use some advice
| [Wednesday 20 April 2011] [08:36:30] <djc>	I have a set of n sources (like ZMQ publishers)
| [Wednesday 20 April 2011] [08:36:44] <djc>	and a set of m sinks
| [Wednesday 20 April 2011] [08:37:16] <djc>	and in the middle are some rules about which sinks want to receive what data (think ZMQ_SUBSCRIBE filters) from what sources
| [Wednesday 20 April 2011] [08:37:28] <djc>	what do I use?
| [Wednesday 20 April 2011] [08:37:50] <guido_g>	more coffee :)
| [Wednesday 20 April 2011] [08:38:31] <djc>	I don't do coffee, maybe that's my problem :P
| [Wednesday 20 April 2011] [08:38:32] <drbobbeaty>	pieterh: Question about the newly released 2.1.5... and maybe this is for mikko, but I'm getting errors in the build - all with the 'make check-TESTS' target. Throwing a lot of zmq::error_t exceptions. What's up?
| [Wednesday 20 April 2011] [08:38:53] <guido_g>	djc: oh sorry
| [Wednesday 20 April 2011] [08:39:12] <pieterh>	drbobbeaty: we'll check it out
| [Wednesday 20 April 2011] [08:39:22] <pieterh>	seems I was a little hasty with the 2.1.5 release
| [Wednesday 20 April 2011] [08:39:35] <drbobbeaty>	pieterh: thanks for checking on this. I really appreciate it.
| [Wednesday 20 April 2011] [08:40:14] <guido_g>	djc: did you see chapter 5 of guide? http://zguide.zeromq.org/page:all#Chapter-Five-Advanced-Publish-Subscribe
| [Wednesday 20 April 2011] [08:40:32] <guido_g>	maybe there is something you can use
| [Wednesday 20 April 2011] [08:40:46] <pieterh>	djc: "rules" meaning what?
| [Wednesday 20 April 2011] [08:41:01] <pieterh>	data that you can move around, or code?
| [Wednesday 20 April 2011] [08:41:15] <djc>	pieterh: things that will change during execution
| [Wednesday 20 April 2011] [08:41:30] <pieterh>	I'd suggest a couple of flows
| [Wednesday 20 April 2011] [08:41:31] <djc>	e.g. the client says I now want to subscribe to source b with filters c
| [Wednesday 20 April 2011] [08:41:36] <pieterh>	a. pub to sub of all data
| [Wednesday 20 April 2011] [08:41:46] <pieterh>	b. rules to subs of all rules, as they change
| [Wednesday 20 April 2011] [08:41:58] <pieterh>	subs can then unsubcribe/resubscribe dynamically
| [Wednesday 20 April 2011] [08:44:48] <pieter_hintjens>	sigh. my son turned the power off for the whole building
| [Wednesday 20 April 2011] [08:45:01] <pieter_hintjens>	djc: did you get that?
| [Wednesday 20 April 2011] [08:45:37] <guido_g>	pieter_hintjens: last was: <pieterh> subs can then...
| [Wednesday 20 April 2011] [08:45:54] <pieter_hintjens>	ok, so one pubsub flow for data, one pubsub flow for rules
| [Wednesday 20 April 2011] [08:46:22] <pieter_hintjens>	subscribers can then get the rules they want, apply them by subscribing/unsubscribing dynamically
| [Wednesday 20 April 2011] [08:46:47] <djc>	pieter_hintjens: ok, so I basically code my own FORWARDER with the subscriber connecting to multiple publishers, so I get a single pub-stream?
| [Wednesday 20 April 2011] [08:47:06] <djc>	and then use a smart header for those messages to subs can do useful filtering?
| [Wednesday 20 April 2011] [08:47:29] 	 * pieter_hintjens doesn't see why you'd need any of this...
| [Wednesday 20 April 2011] [08:47:38] <pieter_hintjens>	you have N subscribers?
| [Wednesday 20 April 2011] [08:47:49] <djc>	yes
| [Wednesday 20 April 2011] [08:47:58] <pieter_hintjens>	so cross connect them all, it's simplest
| [Wednesday 20 April 2011] [08:48:05] <pieter_hintjens>	every subscriber to every publisher
| [Wednesday 20 April 2011] [08:48:27] <djc>	hm
| [Wednesday 20 April 2011] [08:48:30] <guido_g>	or use (e)pgm
| [Wednesday 20 April 2011] [08:48:32] <pieter_hintjens>	then, separately, connect every subscriber to the rule broker
| [Wednesday 20 April 2011] [08:48:41] <pieter_hintjens>	using the same SUB socket, for simplicity
| [Wednesday 20 April 2011] [08:48:45] <pieter_hintjens>	now process incoming messages
| [Wednesday 20 April 2011] [08:48:57] <pieter_hintjens>	make sure your rules have an identifiable key
| [Wednesday 20 April 2011] [08:48:59] <djc>	I don't need the rule broker because each sub sets its own sub rules
| [Wednesday 20 April 2011] [08:49:17] <pieter_hintjens>	you said "in the middle are some rules"
| [Wednesday 20 April 2011] [08:49:27] <pieter_hintjens>	who produces rules at runtime?
| [Wednesday 20 April 2011] [08:49:27] <djc>	that was just my mental model failing
| [Wednesday 20 April 2011] [08:49:34] <djc>	the subs produce the rules
| [Wednesday 20 April 2011] [08:49:40] <pieter_hintjens>	ah, so even simpler
| [Wednesday 20 April 2011] [08:49:43] <djc>	yeah
| [Wednesday 20 April 2011] [08:49:50] <pieter_hintjens>	just sub/unsub dynamically
| [Wednesday 20 April 2011] [08:50:49] <pieter_hintjens>	are you trying to get a single consistent stream to all subscribers?
| [Wednesday 20 April 2011] [08:51:24] <pieter_hintjens>	or is it OK for each subscriber to get messages in different orders
| [Wednesday 20 April 2011] [08:51:42] <djc>	I don't think exact order matters here
| [Wednesday 20 April 2011] [08:51:58] <djc>	certainly not order accross streams
| [Wednesday 20 April 2011] [08:52:15] <djc>	why would the order be different on different subscribers?
| [Wednesday 20 April 2011] [08:52:28] <pieter_hintjens>	publishers will unicast to each subscriber
| [Wednesday 20 April 2011] [08:52:37] <pieter_hintjens>	arrival order at subscribers will vary
| [Wednesday 20 April 2011] [08:52:53] <pieter_hintjens>	if you have >1 publisher, messages from each will arrive in varied order
| [Wednesday 20 April 2011] [08:53:04] <pieter_hintjens>	sub 1 will get A1, B1, B2, A2
| [Wednesday 20 April 2011] [08:53:05] <djc>	because of the interleaving, right?
| [Wednesday 20 April 2011] [08:53:10] <pieter_hintjens>	sub 2 will get A1, A2, B1, B2
| [Wednesday 20 April 2011] [08:53:11] <pieter_hintjens>	etc.
| [Wednesday 20 April 2011] [08:53:18] <djc>	but A1 will always come before A2?
| [Wednesday 20 April 2011] [08:53:21] <pieter_hintjens>	yes
| [Wednesday 20 April 2011] [08:53:31] <djc>	yeah, I don't think that's a problem
| [Wednesday 20 April 2011] [08:54:03] <pieter_hintjens>	so don't use a device, it'll add complexity for nothing
| [Wednesday 20 April 2011] [08:54:19] <pieter_hintjens>	unless you want to make publishers invisible to subscribers, then it can help
| [Wednesday 20 April 2011] [08:54:48] <djc>	well, everything is flowing through a single process
| [Wednesday 20 April 2011] [08:55:08] <pieter_hintjens>	what does that mean?
| [Wednesday 20 April 2011] [08:55:20] <pieter_hintjens>	you just said you have N publishers and N subscribers :)
| [Wednesday 20 April 2011] [08:55:35] <djc>	yeah, but there's a single process handling the connection
| [Wednesday 20 April 2011] [08:56:12] <djc>	it's a WebSockets server that clients can connect to, subscribe to ZeroMQ streams and get JSON messages
| [Wednesday 20 April 2011] [08:56:29] <pieter_hintjens>	djc: your explanation isn't helping, you need to draw a picture
| [Wednesday 20 April 2011] [08:56:35] <djc>	sorry :)
| [Wednesday 20 April 2011] [08:57:16] <pieter_hintjens>	'flowing through' means, to me, 0MQ sockets talking to each other, but you're not explaining that
| [Wednesday 20 April 2011] [08:57:22] <pieter_hintjens>	so, confusion
| [Wednesday 20 April 2011] [08:57:42] <djc>	is there like a pastebin for drawing graphs? :P
| [Wednesday 20 April 2011] [08:58:30] <pieter_hintjens>	hmm, that'd be a neat service... I use ditaa for graphs but there's no pastebin for that
| [Wednesday 20 April 2011] [08:58:40] <headzone>	http://www.lucidchart.com/pages/
| [Wednesday 20 April 2011] [08:59:13] <djc>	using gdocs for now...
| [Wednesday 20 April 2011] [09:02:01] <djc>	https://docs.google.com/drawings/pub?id=1n2IFhfm-mO2mCAzwHLk4-tESDG9D9mCxbIaKAlKgckc&w=960&h=720
| [Wednesday 20 April 2011] [09:02:08] <djc>	is what I'm thinking of
| [Wednesday 20 April 2011] [09:03:48] <pieter_hintjens>	headzone: sweet god that's amazingly well done...
| [Wednesday 20 April 2011] [09:04:19] <pieter_hintjens>	djc: where is the "single process"?
| [Wednesday 20 April 2011] [09:04:26] <djc>	it's the big fat thing in the middle
| [Wednesday 20 April 2011] [09:04:32] <pieter_hintjens>	multithreaded?
| [Wednesday 20 April 2011] [09:04:39] <djc>	if needed, yes
| [Wednesday 20 April 2011] [09:04:58] <pieter_hintjens>	well, if multithreaded, it's effectively N processes
| [Wednesday 20 April 2011] [09:05:08] <pieter_hintjens>	not relevant to discussion, really
| [Wednesday 20 April 2011] [09:05:18] <djc>	so that's why I said it was N processes :P
| [Wednesday 20 April 2011] [09:05:47] <pieter_hintjens>	anyhow, yes, this'll work, you don't need any forwarder device afaics
| [Wednesday 20 April 2011] [09:06:00] <djc>	I just said it was flowing through a single process to explain that I might use a forwarder to forward stuff from local to inproc, so I don't need three or four streams of the same over my LAN
| [Wednesday 20 April 2011] [09:06:08] <djc>	(the left side)
| [Wednesday 20 April 2011] [09:06:41] <pieter_hintjens>	what's the message size/rate you expect?
| [Wednesday 20 April 2011] [09:08:10] <djc>	the sizes are not very impressive, but I expect a fairly rate
| [Wednesday 20 April 2011] [09:08:17] <djc>	+high
| [Wednesday 20 April 2011] [09:08:22] <djc>	not sure how high, exactly
| [Wednesday 20 April 2011] [09:09:03] <djc>	zmq doesn't handle that for me, right? like, it doesn't multiplex for multiple subscribers subscribing to the same publisher within the same context?
| [Wednesday 20 April 2011] [09:28:23] <djc>	would actually be cool if it could do that
| [Wednesday 20 April 2011] [09:29:20] <th>	what does a "what():  Bad address" mean when doing recv()?  i could understand that for bind/connect
| [Wednesday 20 April 2011] [09:29:47] <th>	this happens for me in c++ with 2.1.5 and it did not happen in 2.1.4
| [Wednesday 20 April 2011] [09:34:49] <th>	hmmm #define EFAULT      14  /* Bad address */
| [Wednesday 20 April 2011] [09:36:27] <th>	http://api.zeromq.org/2-1:zmq-recv    tells me EFAULT can mean invalid socket or message; and the changelog for 2.1.5 mentions "Checks zmq_msg_t validity at each operation"
| [Wednesday 20 April 2011] [09:42:40] <mikko>	i'm back
| [Wednesday 20 April 2011] [09:42:46] <mikko>	making moroccon lamb stew
| [Wednesday 20 April 2011] [09:44:29] <mikko>	djc: which os?
| [Wednesday 20 April 2011] [09:51:00] <djc>	mikko: gentoo linux
| [Wednesday 20 April 2011] [09:52:17] <mikko>	ok, which version of OpenPGM?
| [Wednesday 20 April 2011] [09:53:34] <mikko>	and can you run with ./configure --disable-silent-rules
| [Wednesday 20 April 2011] [09:53:41] <mikko>	so that i can see the output of linking
| [Wednesday 20 April 2011] [09:54:37] <djc>	5.1.115
| [Wednesday 20 April 2011] [09:54:56] <djc>	I'll try that
| [Wednesday 20 April 2011] [09:55:27] <mikko>	it sounds like pkg-config for openpgm might fail
| [Wednesday 20 April 2011] [09:55:33] <mikko>	there is currently no check for that
| [Wednesday 20 April 2011] [09:56:59] <pieter_hintjens>	djc: I'm back, sorry
| [Wednesday 20 April 2011] [09:57:12] <pieter_hintjens>	currently zmq sub sockets will multiplex to all sub sockets
| [Wednesday 20 April 2011] [09:57:25] <pieter_hintjens>	there's a work in progress to be smarter about this but it's not got a lot of traction
| [Wednesday 20 April 2011] [09:58:01] <pieter_hintjens>	using an inprocess frontend device is an obvious optimization
| [Wednesday 20 April 2011] [09:58:40] <pieter_hintjens>	http://zguide.zeromq.org/page:all#High-speed-Subscribers-Black-Box-Pattern
| [Wednesday 20 April 2011] [09:59:17] <pieter_hintjens>	th: hi
| [Wednesday 20 April 2011] [09:59:28] <pieter_hintjens>	I think we have a problem in the 2.1.5 release
| [Wednesday 20 April 2011] [09:59:49] <pieter_hintjens>	but it's not clear yet
| [Wednesday 20 April 2011] [10:00:36] <mikko>	what problem?
| [Wednesday 20 April 2011] [10:00:54] <pieter_hintjens>	tests and other code are failing due to last commit which checks msg validity
| [Wednesday 20 April 2011] [10:00:59] <pieter_hintjens>	make  check-TESTS
| [Wednesday 20 April 2011] [10:01:00] <pieter_hintjens>	make[2]: Entering directory `/vol1/home/ph/work/zeromq2-1/tests'
| [Wednesday 20 April 2011] [10:01:00] <pieter_hintjens>	terminate called after throwing an instance of 'zmq::error_t'
| [Wednesday 20 April 2011] [10:01:00] <pieter_hintjens>	  what():  Bad address
| [Wednesday 20 April 2011] [10:01:00] <pieter_hintjens>	/bin/bash: line 5:   883 Aborted                 (core dumped) ${dir}$tst
| [Wednesday 20 April 2011] [10:01:00] <pieter_hintjens>	FAIL: test_pair_inproc
| [Wednesday 20 April 2011] [10:01:16] 	 * pieter_hintjens mutters something about running tests *before* making a new release
| [Wednesday 20 April 2011] [10:01:36] <mikko>	http://build.zero.mq/view/libzmq%202.1/ shows all ok
| [Wednesday 20 April 2011] [10:01:39] <mikko>	strange
| [Wednesday 20 April 2011] [10:01:45] <mikko>	is the commit after this morning build?
| [Wednesday 20 April 2011] [10:02:45] <djc>	mikko: http://paste.pocoo.org/raw/375143/
| [Wednesday 20 April 2011] [10:03:05] <pieter_hintjens>	mikko: I applied a patch from sustrik after this mornings' build
| [Wednesday 20 April 2011] [10:03:08] <mikko>	djc: the whole output if you can
| [Wednesday 20 April 2011] [10:04:37] <mikko>	djc: as that linking failure is for perf programs
| [Wednesday 20 April 2011] [10:04:52] <mikko>	would be interesting if -lpgm is skipped for libzmq.la for some reason
| [Wednesday 20 April 2011] [10:05:51] <djc>	http://dirkjan.ochtman.nl/files/build.log
| [Wednesday 20 April 2011] [10:06:09] <pieter_hintjens>	sustrik: ping, are you around?
| [Wednesday 20 April 2011] [10:09:14] <mikko>	djc: strange
| [Wednesday 20 April 2011] [10:09:32] <mikko>	can you pastebin the output of 'nm' for openpgm.so
| [Wednesday 20 April 2011] [10:14:23] <th>	a simple chain of new zmq::context_t(1); new zmq::socket_t(*context, ZMQ_XREP); bind("tcp://127.0.0.1:5555"); zsock->recv(&message);     results in "Bad address"
| [Wednesday 20 April 2011] [10:14:31] <th>	this makes 2.1.5 somewhat unusable at least for me here
| [Wednesday 20 April 2011] [10:14:57] <mikko>	Please do *not* use the 2.1.5 package released today, the zmq_msg_t
| [Wednesday 20 April 2011] [10:14:57] <mikko>	validity checking appears to be reporting errors on valid code.
| [Wednesday 20 April 2011] [10:15:06] <mikko>	peter's mail 8 minutes ago
| [Wednesday 20 April 2011] [10:19:48] <th>	oh - i did not even notice that this release was from today
| [Wednesday 20 April 2011] [10:20:14] <th>	i just checked the page, because someone told me a bug was fixed
| [Wednesday 20 April 2011] [10:21:06] <djc>	mikko: nm finds no symbols in libpgm.so
| [Wednesday 20 April 2011] [10:21:11] <djc>	..
| [Wednesday 20 April 2011] [10:21:17] <pieter_hintjens>	th: so sorry, I've reverted the download page to point to 2.1.4
| [Wednesday 20 April 2011] [10:21:27] <th>	pieter_hintjens: but not the changelog;)
| [Wednesday 20 April 2011] [10:21:53] <pieter_hintjens>	th: I'll push a clean git history (aaagh) in a second
| [Wednesday 20 April 2011] [10:22:38] <th>	pieter_hintjens: is there any recommended git revision > 2.1.4?
| [Wednesday 20 April 2011] [10:22:43] <pieter_hintjens>	th: nope
| [Wednesday 20 April 2011] [10:22:59] <pieter_hintjens>	take https://github.com/zeromq/zeromq2-1/commits/v2.1.4
| [Wednesday 20 April 2011] [10:23:04] <pieter_hintjens>	or take the package
| [Wednesday 20 April 2011] [10:23:08] <th>	pieter_hintjens: which is the same as ... ok
| [Wednesday 20 April 2011] [10:23:22] <th>	pieter_hintjens: that still has the multipart intermixing issues
| [Wednesday 20 April 2011] [10:23:28] <th>	under higher load
| [Wednesday 20 April 2011] [10:23:54] <pieter_hintjens>	th: I'm not familiar with that bug, and do not think it's been downstreamed to 2.1.5 at all
| [Wednesday 20 April 2011] [10:24:49] <djc>	pieter_hintjens: you shouldn't unpublish changes from a public repo
| [Wednesday 20 April 2011] [10:25:13] <pieter_hintjens>	djc: well, I shouldn't allow buggy code to get into a stable distro
| [Wednesday 20 April 2011] [10:25:15] <th>	pieter_hintjens: i'll see if i can make the test-case smaller and more readable. it's 100% reproducable already for me. but it needs a './server & ; while ./client ; do;done'
| [Wednesday 20 April 2011] [10:25:56] <djc>	pieter_hintjens: so publish a new revision
| [Wednesday 20 April 2011] [10:26:11] <djc>	or even a new tag
| [Wednesday 20 April 2011] [10:26:14] <pieter_hintjens>	djc: ok, I'll respect the rules for once
| [Wednesday 20 April 2011] [10:26:16] <pieter_hintjens>	question then
| [Wednesday 20 April 2011] [10:26:23] <pieter_hintjens>	2.1.6 or 2.1.5 or 2.1.5.1?
| [Wednesday 20 April 2011] [10:26:44] <djc>	if you're taking 2.1.5 and just removing on buggy cset, call it 2.1.5.1
| [Wednesday 20 April 2011] [10:26:49] <djc>	s/on/one/
| [Wednesday 20 April 2011] [10:27:02] <pieter_hintjens>	ok, that's what I'd done before sustrik asked me to pause
| [Wednesday 20 April 2011] [10:40:38] <pieter_hintjens>	sustrik: ping, are you around?
| [Wednesday 20 April 2011] [11:20:45] <mikko>	th: no symbols at all?
| [Wednesday 20 April 2011] [12:30:56] <sustrik>	re
| [Wednesday 20 April 2011] [12:31:35] <sustrik>	pieter_hintjens: sorry, the reply abnout the issue was accidentally sent only to artem
| [Wednesday 20 April 2011] [12:31:40] <sustrik>	let me forward it to the list
| [Wednesday 20 April 2011] [12:39:46] <pieterh>	sustrik: thx
| [Wednesday 20 April 2011] [12:40:20] <pieterh>	sustrik: seems we have a problem with cherry-picking
| [Wednesday 20 April 2011] [12:40:23] <pieterh>	it does not work reliably
| [Wednesday 20 April 2011] [12:42:46] <sustrik>	np
| [Wednesday 20 April 2011] [12:42:53] <pieterh>	what happened was this...
| [Wednesday 20 April 2011] [12:43:04] <pieterh>	well, yes, we do have a problem somewhere... :-/
| [Wednesday 20 April 2011] [12:43:11] <pieterh>	when I apply the commit, it gives a conflict
| [Wednesday 20 April 2011] [12:43:27] <pieterh>	there should be no conflict
| [Wednesday 20 April 2011] [12:43:37] <pieterh>	clearly I'm not modifying these files anywhere else
| [Wednesday 20 April 2011] [12:43:53] <pieterh>	incorrect conflict resolution -> garbage
| [Wednesday 20 April 2011] [12:44:15] <pieterh>	anyone with sufficient git fu to help figure this out?
| [Wednesday 20 April 2011] [12:45:04] <pieterh>	the only way I can see now to fix this is to reset history to before the cherry-pick and do it again
| [Wednesday 20 April 2011] [12:45:11] <pieterh>	this is really unpleasant
| [Wednesday 20 April 2011] [12:46:16] <headzone>	what's the situation (in generic git terms)
| [Wednesday 20 April 2011] [12:47:04] <pieterh>	headzone: ok, here's where I find myself...
| [Wednesday 20 April 2011] [12:47:28] <pieterh>	working in github.com/zeromq/zeromq2-1, which fetches commits from github.com/zeromq/libzmq
| [Wednesday 20 April 2011] [12:47:49] <pieterh>	'git fetch --no-tags libzmq' followed by cherry-picking of specific commits
| [Wednesday 20 April 2011] [12:48:15] <pieterh>	one of these manages to fail, partially and silently, on zmq.cpp
| [Wednesday 20 April 2011] [12:48:22] <sustrik>	the conflict is presumably between changes that were not backported and those that were backported
| [Wednesday 20 April 2011] [12:49:11] <sustrik>	in one of the previous commits in libzmq i've moved message-related functions into a separate compilation unit
| [Wednesday 20 April 2011] [12:49:17] <sustrik>	msg.hpp/cpp
| [Wednesday 20 April 2011] [12:49:28] <sustrik>	that's what causing the conflict imo
| [Wednesday 20 April 2011] [12:49:28] <pieterh>	sustrik: there wasn't even a conflict on this, in fact
| [Wednesday 20 April 2011] [12:49:30] <pieterh>	http://pastebin.com/ddC7HfDH
| [Wednesday 20 April 2011] [12:49:43] <pieterh>	yes, I got an error on msg.cpp
| [Wednesday 20 April 2011] [12:49:55] <pieterh>	but the missing chunks were on zmq.cpp... 
| [Wednesday 20 April 2011] [12:50:15] <pieterh>	anyhow, I now have a bit of a mess in my zeromq2-1 repository
| [Wednesday 20 April 2011] [12:50:16] <sustrik>	which contains functions that are in zmq.cpp in 2.x
| [Wednesday 20 April 2011] [12:50:25] <sustrik>	backporting i shard
| [Wednesday 20 April 2011] [12:50:48] <pieterh>	ah... so the fix is in a file I don't actually have...
| [Wednesday 20 April 2011] [12:50:58] <sustrik>	you may try to apply the parch that moved the functions to msg.cpp
| [Wednesday 20 April 2011] [12:51:00] <sustrik>	first
| [Wednesday 20 April 2011] [12:51:07] <sustrik>	ack
| [Wednesday 20 April 2011] [12:52:00] <pieterh>	sustrik: I really don't want to be creative with the libzmq code...
| [Wednesday 20 April 2011] [12:52:26] <pieterh>	the changes that are missing in zmq.cpp are presumably few
| [Wednesday 20 April 2011] [12:52:38] <sustrik>	let me have a look
| [Wednesday 20 April 2011] [12:53:01] <pieterh>	sustrik: can you clone git@github.com:zeromq/zeromq2-1.git?
| [Wednesday 20 April 2011] [12:53:10] <sustrik>	i did
| [Wednesday 20 April 2011] [12:53:13] <pieterh>	nice
| [Wednesday 20 April 2011] [12:53:43] <pieterh>	headzone: with luck sustrik will be able to help me patch this up and we can go forwards...
| [Wednesday 20 April 2011] [12:53:52] 	 * pieterh is happy to understand what went wrong
| [Wednesday 20 April 2011] [12:54:10] <headzone>	it sounds like you're trying to cherry-pick something from a branch that's diverged from yours, which is usually not a great idea
| [Wednesday 20 April 2011] [12:54:16] <pieterh>	yup
| [Wednesday 20 April 2011] [12:54:49] <pieterh>	i should have caught this in testing, which will happen from now on
| [Wednesday 20 April 2011] [12:54:52] <pieterh>	properly
| [Wednesday 20 April 2011] [12:54:58] <sustrik>	ok, afaics the only thing you need to do is to apply the changes reported as been done to msg.cpp
| [Wednesday 20 April 2011] [12:55:03] <sustrik>	to zmq.cpp instead
| [Wednesday 20 April 2011] [12:55:23] <pieterh>	ok... let me review those
| [Wednesday 20 April 2011] [12:56:08] <pieterh>	sustrik: I'll give that a shot, it should be doable
| [Wednesday 20 April 2011] [12:56:31] <sustrik>	ok
| [Wednesday 20 April 2011] [13:02:04] <headzone>	in future, you may also find it useful to use the -n option to cherry-pick or format-patch instead, to see and inspect how things will look first without messing up your tree
| [Wednesday 20 April 2011] [13:04:17] <pieterh>	headzone: yes, will use -n option on cherry-pick
| [Wednesday 20 April 2011] [13:05:25] <pieterh>	I assume after reviewing, one commits with 'git commit -c nnnnnn'?
| [Wednesday 20 April 2011] [13:06:34] <headzone>	sure
| [Wednesday 20 April 2011] [13:08:06] <pieterh>	thx, I'm keeping the idiot proof instructions here: http://www.zeromq.org/docs:distributions
| [Wednesday 20 April 2011] [13:10:37] <headzone>	in the second part, "git pull source master; git fetch source" is better written "git fetch source; git merge source/master"
| [Wednesday 20 April 2011] [13:13:39] <pieterh>	headzone: thanks, I'll fix it (you can also edit, it's a wiki)
| [Wednesday 20 April 2011] [13:14:56] <pieterh>	sustrik: what code is producing this error...?
| [Wednesday 20 April 2011] [13:15:05] <pieterh>	terminate called after throwing an instance of 'zmq::error_t'
| [Wednesday 20 April 2011] [13:15:06] <pieterh>	  what():  Bad address
| [Wednesday 20 April 2011] [13:15:06] <pieterh>	Aborted (core dumped)
| [Wednesday 20 April 2011] [13:15:09] <pieterh>	in the test cases?
| [Wednesday 20 April 2011] [13:15:27] <pieterh>	after patching zmq.cpp, it fails exactly the same way, I can't trace where
| [Wednesday 20 April 2011] [13:17:18] <sustrik>	try to run the failing test case under dgb
| [Wednesday 20 April 2011] [13:17:21] <sustrik>	gdb
| [Wednesday 20 April 2011] [13:17:37] <sustrik>	there's should be a way to say 'stop at exception'
| [Wednesday 20 April 2011] [13:17:53] <pieterh>	not executable format? wtf?
| [Wednesday 20 April 2011] [13:18:02] 	 * pieterh is getting seriously frustrated at a lost day of work...
| [Wednesday 20 April 2011] [13:18:18] <pieterh>	agh
| [Wednesday 20 April 2011] [13:18:54] <sustrik>	aha, Bad address is EFAULT
| [Wednesday 20 April 2011] [13:19:04] <sustrik>	ie. message validation fails
| [Wednesday 20 April 2011] [13:19:10] <pieterh>	I can't even see where the test executables are...
| [Wednesday 20 April 2011] [13:19:20] <sustrik>	tests subdir
| [Wednesday 20 April 2011] [13:19:47] <pieterh>	all I see are scripts that magically run the test executables
| [Wednesday 20 April 2011] [13:20:01] <th>	mikko: symbols? you meant me?
| [Wednesday 20 April 2011] [13:20:04] <mikko>	yes
| [Wednesday 20 April 2011] [13:20:07] <mikko>	no
| [Wednesday 20 April 2011] [13:20:12] <mikko>	i meant djc 
| [Wednesday 20 April 2011] [13:20:12] <sustrik>	i see, that's because it uses shared libs
| [Wednesday 20 April 2011] [13:20:23] <sustrik>	so there's a script that changes paths
| [Wednesday 20 April 2011] [13:20:28] <sustrik>	to load the right library
| [Wednesday 20 April 2011] [13:20:44] <sustrik>	you can configure with --disable-shared
| [Wednesday 20 April 2011] [13:20:52] <sustrik>	which will force the static linking
| [Wednesday 20 April 2011] [13:21:01] <sustrik>	and thus remove the need for scripts
| [Wednesday 20 April 2011] [13:21:05] <pieterh>	well, when I tried artem's fix, I didn't do any of that, and the fix seemed to work
| [Wednesday 20 April 2011] [13:21:16] <pieterh>	now I can't get even a 'printf' to display
| [Wednesday 20 April 2011] [13:21:23] <sustrik>	it will fail if the message is shared
| [Wednesday 20 April 2011] [13:21:32] <pieterh>	sure, that's not my point
| [Wednesday 20 April 2011] [13:21:48] <pieterh>	it's that I find myself stuck in a twisty maze of "am I running this version or not..."
| [Wednesday 20 April 2011] [13:22:02] <pieterh>	I'll disable shared libraries
| [Wednesday 20 April 2011] [13:22:08] <sustrik>	i do it that
| [Wednesday 20 April 2011] [13:22:09] <sustrik>	way
| [Wednesday 20 April 2011] [13:22:23] <sustrik>	you'll get executables with statically linked libzmq
| [Wednesday 20 April 2011] [13:22:30] <sustrik>	directly in tests subdir
| [Wednesday 20 April 2011] [13:23:18] <pieterh>	sure, makes sense but I never had to do that before
| [Wednesday 20 April 2011] [13:25:00] <pieterh>	nah, this is just messed up
| [Wednesday 20 April 2011] [13:25:06] <pieterh>	it aborts on zmq.hpp:278
| [Wednesday 20 April 2011] [13:25:15] <pieterh>	the file only has 266 lines
| [Wednesday 20 April 2011] [13:25:26] <pieterh>	somehow I'm getting versions totally mixed up :-(
| [Wednesday 20 April 2011] [13:26:18] <pieterh>	mikko: if I run 'make' in zeromq2-1 root, it shouldn't be pulling in so's from elsewhere, should it...?
| [Wednesday 20 April 2011] [13:27:51] <pieterh>	isn't this the day skynet takes control?
| [Wednesday 20 April 2011] [13:28:22] <pieterh>	sustrik: for some godforsaken reason the tests won't build correctly for me
| [Wednesday 20 April 2011] [13:30:35] 	 * pieterh stops complaining and digs back into the code
| [Wednesday 20 April 2011] [13:36:41] <mikko>	pieterh: sorry?
| [Wednesday 20 April 2011] [13:37:15] <pieterh>	mikko: sorry, skynet temporarily got past my cortical firewall, it's gone now... 
| [Wednesday 20 April 2011] [13:38:08] <pieterh>	i found out what the problem was, and it seems much better now
| [Wednesday 20 April 2011] [13:41:10] <pieterh>	mikko: djc reported earlier today that --with-system-pgm didn't work in 2.1.5
| [Wednesday 20 April 2011] [13:41:33] <mikko>	yep
| [Wednesday 20 April 2011] [13:41:48] <pieterh>	do you want me to hold off with 2.1.5.1?
| [Wednesday 20 April 2011] [13:41:56] <mikko>	please
| [Wednesday 20 April 2011] [13:42:07] <mikko>	i'll look into it tonight
| [Wednesday 20 April 2011] [13:42:15] <pieterh>	ok, np
| [Wednesday 20 April 2011] [13:42:28] <pieterh>	btw we can also get that redhat spec file into it if you have it
| [Wednesday 20 April 2011] [13:42:34] <pieterh>	depends how long your nights are... :)
| [Wednesday 20 April 2011] [13:55:30] <mikko>	that change is pretty trivial
| [Wednesday 20 April 2011] [14:00:55] <pieterh>	everything is trivial to the right brain :-)
| [Wednesday 20 April 2011] [14:05:51] <mikko>	i need to take a small break
| [Wednesday 20 April 2011] [14:05:57] <mikko>	juggling million things at the moment
| [Wednesday 20 April 2011] [14:05:59] <mikko>	bbl
| [Wednesday 20 April 2011] [14:06:55] <pieterh>	cyl
| [Wednesday 20 April 2011] [14:10:40] <guido_g>	pieterh: do you have an idea what a taxi ride from the airport to the meeting place might cost?
| [Wednesday 20 April 2011] [14:11:03] <pieterh>	guido_g: I'll add a travel guide to the wiki page, taxis are extortionate
| [Wednesday 20 April 2011] [14:11:06] <pieterh>	it'
| [Wednesday 20 April 2011] [14:11:18] <pieterh>	it's easy to get to by public transport
| [Wednesday 20 April 2011] [14:11:24] <guido_g>	ok
| [Wednesday 20 April 2011] [14:12:19] <guido_g>	just wanted to know if i could do it the lazy way :)
| [Wednesday 20 April 2011] [14:18:43] <jond>	pieterh: are master and 2.1 repo still bust with the message check bug?
| [Wednesday 20 April 2011] [14:19:16] <pieterh>	jond: libzmq master was always working, 2.1 master is now in theory working again
| [Wednesday 20 April 2011] [14:20:20] <jond>	pieterh : so how did the patch for libzmq -> 2.1 go wrong then? does it have to be applied and fixed manually?
| [Wednesday 20 April 2011] [14:21:26] <pieterh>	libzmq had diverged and the patch was not usable as-such, and my resolution of that error was wrong
| [Wednesday 20 April 2011] [14:22:54] <jond>	pieterh: ok understood, just wanted to be clear, so essentially patches to libzmq master now may have to be manually reworked for the backport.
| [Wednesday 20 April 2011] [14:23:21] <pieterh>	jond: not until now, no
| [Wednesday 20 April 2011] [14:23:39] <pieterh>	but this seems to be inevitable as 3.0 diverges
| [Wednesday 20 April 2011] [14:23:58] <pieterh>	I guess we were kind of expecting it but missed it when it actually happened :-(
| [Wednesday 20 April 2011] [14:25:08] <jond>	pieterh: yeah, looked bad on the list....but stuff happens
| [Wednesday 20 April 2011] [14:25:30] <pieterh>	well, stuff happens... I don't mind looking bad, so long as we don't make the same mistakes twice
| [Wednesday 20 April 2011] [14:26:17] <pieterh>	Its far worse to not make releases out of fear of getting it wrong
| [Wednesday 20 April 2011] [14:40:26] <guido_g>	ohh... an irish pub, how pleasant
| [Wednesday 20 April 2011] [14:47:48] <pieterh>	guido_g: an irish pub wandered into your office?
| [Wednesday 20 April 2011] [14:48:02] <guido_g>	ah no
| [Wednesday 20 April 2011] [14:48:09] <guido_g>	a) i'm at home
| [Wednesday 20 April 2011] [14:48:24] <guido_g>	and b) was looking at brussels w/ google-earth
| [Wednesday 20 April 2011] [14:48:47] <traviscline>	just pushed some further cython optimizations to gevent-zeromq's HEAD please report any issues if they occur
| [Wednesday 20 April 2011] [15:07:54] <pieterh>	guido_g: :) irish pubs in brussels are crap (my word of the day)
| [Wednesday 20 April 2011] [15:08:10] <pieterh>	the best pubs are the authentically ethnic ones
| [Wednesday 20 April 2011] [15:08:36] <guido_g>	ok
| [Wednesday 20 April 2011] [15:08:49] 	 * guido_g cancels the booking for brussels
| [Wednesday 20 April 2011] [15:08:55] <pieterh>	hehehe
| [Wednesday 20 April 2011] [15:09:07] 	 * guido_g is visiting friend in dublin instead
| [Wednesday 20 April 2011] [15:09:07] <pieterh>	I meant, the Irish Pubs are fantastic!
| [Wednesday 20 April 2011] [15:09:17] <pieterh>	brussels imports all its beer from dublin
| [Wednesday 20 April 2011] [15:09:20] <pieterh>	srsly
| [Wednesday 20 April 2011] [15:10:16] <guido_g>	you should be happy that i'm not the average german
| [Wednesday 20 April 2011] [15:10:52] <guido_g>	you know how picky they are wrt beer
| [Wednesday 20 April 2011] [15:18:13] <pieterh>	guido_g: I once had a GF from Bavaria... sigh... 
| [Wednesday 20 April 2011] [15:18:33] <pieterh>	beautiful but beer crazy
| [Wednesday 20 April 2011] [15:18:43] <pieterh>	this is very relevant to #zeromq somehow
| [Wednesday 20 April 2011] [15:19:05] 	 * guido_g shuts up
| [Wednesday 20 April 2011] [15:19:08] <pieterh>	btw I put up some transport tips on the unconf page
| [Wednesday 20 April 2011] [15:19:19] <guido_g>	would be great!
| [Wednesday 20 April 2011] [15:19:28] <pieterh>	see if they make even random sense
| [Wednesday 20 April 2011] [15:19:37] <guido_g>	will do
| [Wednesday 20 April 2011] [15:20:05] <pieterh>	guido_g: I was asserting that beer *is* relevant to zeromq
| [Wednesday 20 April 2011] [15:20:42] <guido_g>	i can confirm that
| [Wednesday 20 April 2011] [15:21:27] <jond>	pieterh: only if it passes certain purity and strength tests!
| [Wednesday 20 April 2011] [15:21:46] <pieterh>	jond: purity and strength are the defining characteristics of 0MQ!
| [Wednesday 20 April 2011] [15:22:00] 	 * pieterh ponders the lack of Orval in the fridge
| [Wednesday 20 April 2011] [15:22:31] <pieterh>	maybe I can change the 0MQ website logo to "Purity and Strength!" ?
| [Wednesday 20 April 2011] [15:22:43] <pieterh>	nah, people would think we're a cult of some kind
| [Wednesday 20 April 2011] [15:22:51] <pieterh>	which is totally not the case
| [Wednesday 20 April 2011] [15:24:04] <guido_g>	does sacrificial blood count as liquid when flying?
| [Wednesday 20 April 2011] [15:25:15] <pieterh>	guido_g: only if it's not yours afaik
| [Wednesday 20 April 2011] [15:25:56] <guido_g>	no problem, can collect some at the airport
| [Wednesday 20 April 2011] [15:26:42] <pieterh>	they sell it in Brussels, np
| [Wednesday 20 April 2011] [15:27:10] <guido_g>	what a town
| [Wednesday 20 April 2011] [15:27:28] <pieterh>	not sure if it's entirely within the Reinheitsgebot
| [Wednesday 20 April 2011] [15:27:38] <pieterh>	probably got added chocolate or somesuch
| [Wednesday 20 April 2011] [15:27:57] <guido_g>	hehe
| [Wednesday 20 April 2011] [15:53:27] <guido_g>	n8 all!
| [Wednesday 20 April 2011] [15:54:12] <pieterh>	bye guido_g
| [Wednesday 20 April 2011] [15:54:32] <phpcodemonkey>	hi all, am here looking for help with 0mq / php issue - I'm running 2.1.4 / PHP pecl zmq-beta 0.7.0 on PHP 5.3.6, x86_64 Fedora 14: I'm getting a segfault when running the basic hwclient.php from https://github.com/imatix/zguide/blob/master/examples/PHP/hwclient.php the related hwserver.php runs fine sits there waiting for client connections. I've posted a backtrace at: http://pastebin.com/ruEzjAdT anyone got any ide
| [Wednesday 20 April 2011] [15:55:50] <pieterh>	phpcodemonkey: there seems to be an error on a uid generating function
| [Wednesday 20 April 2011] [15:55:57] <pieterh>	you might need to install libuuid or similar
| [Wednesday 20 April 2011] [15:56:15] <pieterh>	gen_uuid.c: No such file or directory.
| [Wednesday 20 April 2011] [15:56:54] <phpcodemonkey>	k
| [Wednesday 20 April 2011] [15:57:49] <phpcodemonkey>	already got: libuuid-devel-2.18-4.8.fc14.x86_64 rpm installed
| [Wednesday 20 April 2011] [15:58:09] <pieterh>	that should be sufficient IMO
| [Wednesday 20 April 2011] [15:59:05] <pieterh>	mikko should be able to help, he's the guy who wrote the PHP binding
| [Wednesday 20 April 2011] [15:59:11] <pieterh>	he'll be around later on this evening normally
| [Wednesday 20 April 2011] [15:59:14] <phpcodemonkey>	provides uuid.h in /usr/include so all seems to be correct
| [Wednesday 20 April 2011] [15:59:28] <phpcodemonkey>	pieterh: he's already asked for a backtrace via twitter :)
| [Wednesday 20 April 2011] [15:59:45] <pieterh>	phpcodemonkey: some of the uuid packages don't provide the right functions
| [Wednesday 20 April 2011] [16:00:02] <phpcodemonkey>	nice
| [Wednesday 20 April 2011] [16:01:08] <pieterh>	googling that error gives quite a lot of results
| [Wednesday 20 April 2011] [16:01:19] <pieterh>	check if there are other uuid rpms
| [Wednesday 20 April 2011] [16:01:24] <mikko>	here
| [Wednesday 20 April 2011] [16:01:27] <pieterh>	:)
| [Wednesday 20 April 2011] [16:01:43] <mikko>	enjoyed a bit of C++ dev on windows
| [Wednesday 20 April 2011] [16:01:53] <mikko>	and when i say enjoy i mean sticking bamboo sticks under nails
| [Wednesday 20 April 2011] [16:02:55] <mikko>	phpcodemonkey: have you got imagick / uuid pecl extension loaded?
| [Wednesday 20 April 2011] [16:04:01] <phpcodemonkey>	imagick 3.0.1
| [Wednesday 20 April 2011] [16:04:17] <mikko>	can you try loading zmq extension before imagick?
| [Wednesday 20 April 2011] [16:04:36] <mikko>	this is a known unknown issue with imagemagick / uuid 
| [Wednesday 20 April 2011] [16:04:40] <phpcodemonkey>	e.g. change zeromq.ini to 0mq.ini?
| [Wednesday 20 April 2011] [16:04:45] <mikko>	yes
| [Wednesday 20 April 2011] [16:04:48] <mikko>	that should do the trick
| [Wednesday 20 April 2011] [16:05:06] <mikko>	http://usrportage.de/archives/922-PHP-segfaulting-with-pecluuid-and-peclimagick.html
| [Wednesday 20 April 2011] [16:05:10] <mikko>	it looks like this issue
| [Wednesday 20 April 2011] [16:05:16] <mikko>	i have no idea what is going on in there
| [Wednesday 20 April 2011] [16:05:27] <mikko>	seems to be some global state inside uuid lib or so
| [Wednesday 20 April 2011] [16:05:39] <phpcodemonkey>	mikko: you rock, that was it!
| [Wednesday 20 April 2011] [16:05:51] <phpcodemonkey>	perhaps that out to be in the docs somewhere?
| [Wednesday 20 April 2011] [16:06:11] <mikko>	sure, if you can add a git pull request ill merge it
| [Wednesday 20 April 2011] [16:07:38] <phpcodemonkey>	git != svn ;)
| [Wednesday 20 April 2011] [16:12:33] <mikko>	pieterh: --with-system-pgm works for me (tm)
| [Wednesday 20 April 2011] [16:13:16] <pieterh>	mikko: did djc provide details of what "doesn't work" means for him?
| [Wednesday 20 April 2011] [16:13:26] <mikko>	yes
| [Wednesday 20 April 2011] [16:13:28] <mikko>	fails to link
| [Wednesday 20 April 2011] [16:13:37] <mikko>	and nm on openpgm.so doesnt show _any_ symbols
| [Wednesday 20 April 2011] [16:13:41] <pieterh>	ah
| [Wednesday 20 April 2011] [16:13:41] <mikko>	djc: are you still here?
| [Wednesday 20 April 2011] [16:13:52] <pieterh>	empty library or somesuch
| [Wednesday 20 April 2011] [16:14:06] <pieterh>	mikko: nice catch on phpcodemonkey's problem there
| [Wednesday 20 April 2011] [16:14:53] <mikko>	thanks
| [Wednesday 20 April 2011] [16:15:05] <phpcodemonkey>	definitely, was frustrating the heck out of me!
| [Wednesday 20 April 2011] [16:16:18] <phpcodemonkey>	though having read the blog post you referenced, it seems that 0mq and imagick on their own do the damage, don't have pecl/uuid installed
| [Wednesday 20 April 2011] [16:37:40] <mikko>	phpcodemonkey: it's any extension using uuid functions + imagick
| [Wednesday 20 April 2011] [16:38:04] <phpcodemonkey>	mikko: figured that, was just confirming :)
| [Wednesday 20 April 2011] [16:47:31] <mikko>	pieterh: want me to push the spec file change directly?
| [Wednesday 20 April 2011] [16:47:46] <pieterh>	mikko: sure, that'd be simplest
| [Wednesday 20 April 2011] [16:49:12] <mikko>	ok, will push soon(ish)
| [Wednesday 20 April 2011] [16:49:26] <mikko>	i'll make sure that the change makes it midnight's rpm builds
| [Wednesday 20 April 2011] [16:58:21] <mikko>	pieterh: can you test 2.1?
| [Wednesday 20 April 2011] [16:58:36] <pieterh>	you mean a normal make check?
| [Wednesday 20 April 2011] [16:59:15] <pieterh>	ok, running a full build / test process
| [Wednesday 20 April 2011] [17:00:15] <mikko>	if make dist works it should be fine
| [Wednesday 20 April 2011] [17:00:25] <mikko>	i'll fix small bug in ztools and run rpm builds now
| [Wednesday 20 April 2011] [17:02:17] <pieterh>	mikko: it all seems to work, with your changes
| [Wednesday 20 April 2011] [17:06:21] <mikko>	build running
| [Wednesday 20 April 2011] [17:06:22] <mikko>	bbr
| [Wednesday 20 April 2011] [17:06:23] <mikko>	brb
| [Wednesday 20 April 2011] [17:21:30] <mikko>	pieterh: seems to be ok
| [Wednesday 20 April 2011] [18:53:49] <coopernurse>	hi zeromq folks.  anyone have a few minutes to chat with a zeromq newb?  I have some basic architectural questions.  I have read the whitepaper.  I'm coming from a traditional broker based background, so I'm trying to unlearn some concepts.
| [Wednesday 20 April 2011] [19:04:18] <traviscline>	coopernurse: irc etiquette is "to ask, not to ask to ask"  
| [Wednesday 20 April 2011] [19:04:40] <traviscline>	*cough cough* it's mostly so people don't accidentally get roped into questions they can't answer and look wrong :P
| [Wednesday 20 April 2011] [19:05:01] <coopernurse>	ok, great
| [Wednesday 20 April 2011] [19:06:32] <coopernurse>	I just read this: http://www.zeromq.org/whitepapers:brokerless
| [Wednesday 20 April 2011] [19:07:13] <coopernurse>	and I want to make sure I understand the suggested approach
| [Wednesday 20 April 2011] [19:07:39] <coopernurse>	is it correct to consider zeromq a toolkit for building your own message routers?
| [Wednesday 20 April 2011] [19:07:59] <coopernurse>	for example, in the distributed broker diagram
| [Wednesday 20 April 2011] [19:08:45] <coopernurse>	Q1, Q2, and Q3 are daemons that I would write correct?  that would encapsulate whatever routing topology was relevant
| [Wednesday 20 April 2011] [19:21:35] <jond>	coopernurse: I think reading the guide will be better, some of the whitepapers are quite old ; http://zguide.zeromq.org/page:all
| [Wednesday 20 April 2011] [19:22:15] <coopernurse>	jond: I've read through that as well (about a month ago).  Nothing I've read talks about suggested deployment architectures.
| [Wednesday 20 April 2011] [19:23:33] <coopernurse>	For example, I want to have a conversation with some operations folks about this
| [Wednesday 20 April 2011] [19:23:48] <coopernurse>	And they think in terms of redundancy and points of failure
| [Wednesday 20 April 2011] [19:24:07] <jond>	coopernurse: well in that case , it would be better to be on here on CET timezone. Though yes with zeromq you could build custom routers
| [Wednesday 20 April 2011] [19:25:11] <coopernurse>	The whitepaper was the closest thing I've seen so far to discussing deployment topologies
| [Wednesday 20 April 2011] [19:25:34] <coopernurse>	I understood the suggestion to potentially use a directory service for components to locate queue endpoints
| [Wednesday 20 April 2011] [19:26:05] <coopernurse>	But I was unclear whether the Q1, Q2, etc were provided out of the box by zeromq, or were daemons you write yourself
| [Wednesday 20 April 2011] [19:26:17] <coopernurse>	I'm assuming it's something I would have to write
| [Wednesday 20 April 2011] [19:26:23] <jond>	there also is some stuff in the later chapters of the guide which may have been added recently: It would be best to hook up with pieterh on here
| [Wednesday 20 April 2011] [19:26:55] <coopernurse>	ok
| [Wednesday 20 April 2011] [19:27:16] <coopernurse>	but in general is it correct to view zeromq as a toolkit for creating your own messaging topologies?
| [Wednesday 20 April 2011] [19:27:37] <coopernurse>	or are there higher level turnkey solutions that I have missed that come with the distribution?
| [Wednesday 20 April 2011] [19:29:14] <jond>	well I've just looked atb the whitepaper, if you look at the stuff below the distributed broker which clicks to a chat example which is now marked as deprecated, so the best place is gonna be the guide and then irc or the mailing list
| [Wednesday 20 April 2011] [19:29:37] <headzone>	coopernurse: funnily enough, we have just been debating that question
| [Wednesday 20 April 2011] [19:29:47] <coopernurse>	jond: ok thanks
| [Wednesday 20 April 2011] [19:30:23] <coopernurse>	headzone: oh yeah?
| [Wednesday 20 April 2011] [19:31:16] <headzone>	coopernurse: the current thinking appears to be that the goal of 0mq is to provide standard/pre-packaged known-good messaging patterns (topologies), rather than be a toolkit that users use to build their own custom ones
| [Wednesday 20 April 2011] [19:32:15] <coopernurse>	ah, interesting.  and if that's the case, would those pre-packaged patterns take the form of daemons you can run out of the box?
| [Wednesday 20 April 2011] [19:32:57] <headzone>	no, they take the form of the patterns supported by the sockets, e.g. req/rep, pub/sub
| [Wednesday 20 April 2011] [19:33:22] <coopernurse>	ok, so this is where I really just don't get it
| [Wednesday 20 April 2011] [19:33:27] <coopernurse>	perhaps I need to rtfm more carefully
| [Wednesday 20 April 2011] [19:33:48] <headzone>	with maybe some "devices" on top at a higher layer (the things currently called queue/forwarder/streamer)
| [Wednesday 20 April 2011] [19:33:55] <jond>	headzone: I think you can use it for both, but in some areas that is quite fluid. There was a concept of devices -> queue, forwarder, streamer but they are being moved out of the core
| [Wednesday 20 April 2011] [19:34:42] <coopernurse>	ok, so "devices" is the term I probably need to be examining in the guide more closely
| [Wednesday 20 April 2011] [19:34:59] <headzone>	coopernurse: the reason this is confusing at the moment is that the current state of 0mq is sort of stuck in the middle of "standard patterns" and "toolkit for building custom application-layer routing topologies", for historical reasons
| [Wednesday 20 April 2011] [19:35:05] <coopernurse>	presumably the Q1, Q2, etc in the (perhaps deprecated?) whitepaper are potentially devices zeromq provides
| [Wednesday 20 April 2011] [19:35:28] <coopernurse>	ok
| [Wednesday 20 April 2011] [19:36:08] <jond>	coopernurse: the guide doesnt mention them much and it also uses this libzapi which sits atop 0mq; pieterh is the one behind all this
| [Wednesday 20 April 2011] [19:36:44] <headzone>	coopernurse: i found this out by assuming the goal was to become a generic application-layer routing topology construction kit and suggesting a protocol stack that would accomplish this in a sane manner
| [Wednesday 20 April 2011] [19:38:03] <coopernurse>	As someone who is coming from ActiveMQ/RabbitMQ/etc it's difficult to find analogs in zeromq
| [Wednesday 20 April 2011] [19:38:08] <headzone>	coopernurse: but it is far from clear that that is a desirable goal to aim for, because it amounts to recapitulating what the IP network and transport layers already provide
| [Wednesday 20 April 2011] [19:38:47] <coopernurse>	headzone: yes, I'm just trying to wrap my head around how an application developer could use zeromq to transition a monolithic web app into a set of more loosely coupled components
| [Wednesday 20 April 2011] [19:39:21] <coopernurse>	I agree with the "broker is a single point of failure" stuff in the zeromq literature.  That got me interested.
| [Wednesday 20 April 2011] [19:39:37] <coopernurse>	But I'm not sure how I avoid writing lots of little devices that are each single points of failure
| [Wednesday 20 April 2011] [19:40:11] <headzone>	right, and basically you do that by combining the standard messaging patterns, the "device" functions (which are really just commonly used pieces of application logic), and application logic to handle anything else that's required
| [Wednesday 20 April 2011] [19:41:20] <coopernurse>	headzone: ok, thanks.  I appreciate your time.
| [Wednesday 20 April 2011] [19:41:25] <headzone>	regarding redundancy, i happen to think that solving that problem in a general way inexorably leads you to reinventing routing
| [Wednesday 20 April 2011] [19:42:08] <coopernurse>	is there a recommended way to do it in zeromq?
| [Wednesday 20 April 2011] [19:42:17] <coopernurse>	(redundancy that is)
| [Wednesday 20 April 2011] [19:42:52] <headzone>	well, there are lots of examples in the guide
| [Wednesday 20 April 2011] [19:43:14] <coopernurse>	ok
| [Wednesday 20 April 2011] [19:43:41] <headzone>	a fair portion of it is about the hoops you have to jump through to get reliability
| [Wednesday 20 April 2011] [19:44:05] <coopernurse>	all of it seems very point to point though
| [Wednesday 20 April 2011] [19:44:25] <headzone>	it's also all very ad-hoc
| [Wednesday 20 April 2011] [19:44:28] <coopernurse>	all the examples I've seen seem to assume the components know who to talk to
| [Wednesday 20 April 2011] [19:45:19] <coopernurse>	I'm looking at the "Designing Reliability" section again now
| [Wednesday 20 April 2011] [19:48:28] <coopernurse>	ok, well thanks headzone and jond.  I'll keep reading.  I'm off.
| [Thursday 21 April 2011] [00:30:53] <MK_FG>	Hi. I'm trying to use dealer-to-dealer sockets to implement async event processing (events are emitted from one socket group, and replies are sent only when it's necessary to take action on it)
| [Thursday 21 April 2011] [00:31:29] <MK_FG>	But I've hit a problem: if processing is slow, emitters start eating all the ram available
| [Thursday 21 April 2011] [00:32:03] <MK_FG>	And setting HWM to, say 5, everywhere doesn't seem to have any effect
| [Thursday 21 April 2011] [00:32:33] <MK_FG>	Yet docs seem to indicate that sending dealer sockets should block after not being able to dispose of 5 msg...
| [Thursday 21 April 2011] [00:33:01] <MK_FG>	Where am I doing it wrong? ;)
| [Thursday 21 April 2011] [01:01:59] <MK_FG>	Hm... my mistake it this case was setting hwm after connecting socket (doesn't seem to be documented), although setting it to 5 with a single emitter and single collector (on both sides) still allows the former to send 1k msgs when the latter blocks on the first one
| [Thursday 21 April 2011] [01:10:36] <guido_g>	http://api.zeromq.org/2-1:zmq-setsockopt  <- see top of the page
| [Thursday 21 April 2011] [01:11:30] <MK_FG>	Indeed, I seem to be ignoring stuff in fancy frames, thanks
| [Thursday 21 April 2011] [01:12:14] <guido_g>	ok
| [Thursday 21 April 2011] [01:12:57] <guido_g>	for the other problem just post a minimal example showing this behaviour to a pastebin
| [Thursday 21 April 2011] [01:13:07] <MK_FG>	Sure, a moment...
| [Thursday 21 April 2011] [01:13:33] <MK_FG>	http://paste.pocoo.org/raw/375603/ <-- emitter, http://paste.pocoo.org/raw/375604/ <-- collector
| [Thursday 21 April 2011] [01:14:00] <MK_FG>	libzmq 2.1.0, pyzmq 2.1.4
| [Thursday 21 April 2011] [01:14:05] <guido_g>	ahhh... a langauge i know... :)
| [Thursday 21 April 2011] [01:14:18] <MK_FG>	Everyone knows python ;_)
| [Thursday 21 April 2011] [01:14:43] <guido_g>	luckily this is not the case
| [Thursday 21 April 2011] [01:15:26] <MK_FG>	Well, I've yet to see a person IRL who can't read it, at least ;)
| [Thursday 21 April 2011] [01:16:47] <guido_g>	so true
| [Thursday 21 April 2011] [01:16:50] <MK_FG>	Starting these two, emitter gets to "Sent: 1052" here before seeing the first reply
| [Thursday 21 April 2011] [01:17:26] <MK_FG>	I'd have expected 10 or 5, but 1k...
| [Thursday 21 April 2011] [01:18:59] <guido_g>	i think you got the socket types wrong
| [Thursday 21 April 2011] [01:19:07] <guido_g>	did you read the guide?
| [Thursday 21 April 2011] [01:19:25] <MK_FG>	Yes, I did
| [Thursday 21 April 2011] [01:20:05] <guido_g>	http://zguide.zeromq.org/page:all#Chapter-Three-Advanced-Request-Reply-Patterns <- re-read carefully
| [Thursday 21 April 2011] [01:23:36] <guido_g>	dealer sockets (xreq) are not ment to talks to each other
| [Thursday 21 April 2011] [01:24:01] <MK_FG>	What about http://zguide.zeromq.org/page:all#Asynchronous-Client-Server then?
| [Thursday 21 April 2011] [01:24:06] <guido_g>	and from the reference: "When a ZMQ_DEALER socket is connected to a ZMQ_REP socket each message sent must consist of an empty message part, the delimiter, followed by one or more body parts."
| [Thursday 21 April 2011] [01:24:32] <MK_FG>	"is connected to a ZMQ_REP socket" is not true in my case!
| [Thursday 21 April 2011] [01:25:28] <guido_g>	and?
| [Thursday 21 April 2011] [01:25:54] <guido_g>	it's about the message format required
| [Thursday 21 April 2011] [01:26:57] <MK_FG>	Hmm...
| [Thursday 21 April 2011] [01:27:41] <guido_g>	you got the envelope wrong
| [Thursday 21 April 2011] [01:27:57] <guido_g>	and btw, "fanout" is the term to use for a 1:1 link
| [Thursday 21 April 2011] [01:28:04] <guido_g>	*is not the
| [Thursday 21 April 2011] [01:28:10] <MK_FG>	Thanks, guess I'll re-read the envelope sections there
| [Thursday 21 April 2011] [01:28:35] <MK_FG>	In my case it should be "few emitters" and "lots of collectors"
| [Thursday 21 April 2011] [01:28:37] <guido_g>	or describe the use-case and hope for some help :)
| [Thursday 21 April 2011] [01:28:51] <guido_g>	it's called pub-sub
| [Thursday 21 April 2011] [01:29:14] <MK_FG>	"[10:30:35]<MK_FG> Hi. I'm trying to use dealer-to-dealer sockets to implement async event processing (events are emitted from one socket group, and replies are sent only when it's necessary to take action on it)"
| [Thursday 21 April 2011] [01:29:33] <guido_g>	this is not a use-case
| [Thursday 21 April 2011] [01:29:35] <MK_FG>	Not really, I don't need to send the same message to _all_ collectors, only to a single one
| [Thursday 21 April 2011] [01:29:51] <guido_g>	then you build a router
| [Thursday 21 April 2011] [01:30:13] <guido_g>	your naming really needs an upgrade
| [Thursday 21 April 2011] [01:30:50] <MK_FG>	Guess so
| [Thursday 21 April 2011] [01:32:22] <guido_g>	http://zguide.zeromq.org/page:all#Least-Recently-Used-Routing-LRU-Pattern  <- might be the thing you want
| [Thursday 21 April 2011] [01:33:20] <MK_FG>	REQ is flip-flop afair, so if it'll get a request, it must send a reply
| [Thursday 21 April 2011] [01:33:28] <MK_FG>	And I don't need a replies 99% of time
| [Thursday 21 April 2011] [01:34:06] <MK_FG>	I thought about splitting replies into a separate channel, but dealer-to-dealer seemed to handle the case nicely...
| [Thursday 21 April 2011] [01:34:35] <MK_FG>	Guess I'll test it a bit more and check envelopes, then re-evaluate that idea
| [Thursday 21 April 2011] [01:36:50] <guido_g>	why not push socket to distribute the requests?
| [Thursday 21 April 2011] [01:37:23] <guido_g>	the back channel could also be built w/ push, this time on the worker side
| [Thursday 21 April 2011] [01:42:41] <MK_FG>	Yes, guess that's how I'll rebuild it, but I still can't quite see why dealer-to-dealer shouldn't work
| [Thursday 21 April 2011] [03:18:28] <saurabh_>	hi
| [Thursday 21 April 2011] [03:19:43] <saurabh_>	had a question regarding zeromq durable sockets ...
| [Thursday 21 April 2011] [03:20:21] <saurabh_>	did the following:
| [Thursday 21 April 2011] [03:20:41] <saurabh_>	1) created connection between xrep(bind) and xreq(connect) sockets
| [Thursday 21 April 2011] [03:21:25] <saurabh_>	2) sent messages from xrep to xreq sockets ( this is working properly)
| [Thursday 21 April 2011] [03:21:47] <saurabh_>	3) now I kill xrep socket ...
| [Thursday 21 April 2011] [03:22:17] <saurabh_>	heres the problem ...
| [Thursday 21 April 2011] [03:23:16] <saurabh_>	since I don't explicitly set identity on xrep. I am expecting xreq to start dropping messages to xrep. but xreq keeps adding those messages to its queue and caching them.
| [Thursday 21 April 2011] [03:28:44] <saurabh_>	what I want is that all messages sent to xreq socket should either be dropped or sent to xrep if connected.
| [Thursday 21 April 2011] [03:29:00] <saurabh_>	this queuing behaviour causes problems on 2 levels
| [Thursday 21 April 2011] [03:29:21] <saurabh_>	1) consumes memory xreq side
| [Thursday 21 April 2011] [03:30:02] <saurabh_>	2) blasts messages on xrep side when it comes back up
| [Thursday 21 April 2011] [03:32:31] <MK_FG>	saurabh_, send with xreq should block upon reaching hwm, in my (quite limited yet) understanding
| [Thursday 21 April 2011] [03:32:39] <sustrik>	saurabh_: how are you killing the xrep side?
| [Thursday 21 April 2011] [03:33:04] <sustrik>	Ctrl+C? Power-downing the machine?
| [Thursday 21 April 2011] [03:33:04] <saurabh_>	kill -9
| [Thursday 21 April 2011] [03:33:08] <saurabh_>	yep
| [Thursday 21 April 2011] [03:33:30] <sustrik>	hm, not sure whether TCP reports the connection disruption then
| [Thursday 21 April 2011] [03:33:38] <sustrik>	have you tried with Ctrl+C?
| [Thursday 21 April 2011] [03:34:19] <saurabh_>	i'll give it a try
| [Thursday 21 April 2011] [03:36:05] <headzone>	tcp won't know until the far end comes back up and sends an RST in response to the next segment sent
| [Thursday 21 April 2011] [03:38:26] <saurabh_>	tried something else ... received 10 msgs on xrep end & then explicitly called socket.close followed by context.term & ~2sec of wait before normal program termination
| [Thursday 21 April 2011] [03:38:47] <saurabh_>	still xreq cached those messages
| [Thursday 21 April 2011] [03:40:01] <sustrik>	saurabh_: ok, it looks like a bug then
| [Thursday 21 April 2011] [03:40:02] <saurabh_>	seems ok 
| [Thursday 21 April 2011] [03:40:15] <saurabh_>	1-30 i received that way
| [Thursday 21 April 2011] [03:40:16] <sustrik>	can you report it in the bug tracker?
| [Thursday 21 April 2011] [03:40:25] <saurabh_>	& then i received 90-
| [Thursday 21 April 2011] [03:40:33] <saurabh_>	so its fine ...
| [Thursday 21 April 2011] [03:40:47] 	 * sustrik is confused
| [Thursday 21 April 2011] [03:40:59] <saurabh_>	ok ... explaing
| [Thursday 21 April 2011] [03:41:12] <saurabh_>	req end was doing non stop sending after some sleep
| [Thursday 21 April 2011] [03:41:24] <saurabh_>	jsut nos (1, 2, etc.)
| [Thursday 21 April 2011] [03:41:24] <guido_g>	may i dare to ask for a minimal code example?
| [Thursday 21 April 2011] [03:42:24] <saurabh_>	sure ... 
| [Thursday 21 April 2011] [03:42:35] <sustrik>	guido_g: afaiu what saurabh_ is saying that it actually works as expected
| [Thursday 21 April 2011] [03:42:37] <guido_g>	into a paste-bin, please
| [Thursday 21 April 2011] [03:42:39] <sustrik>	right?
| [Thursday 21 April 2011] [03:42:52] <guido_g>	sustrik: i'm not sure what he is saying
| [Thursday 21 April 2011] [03:43:07] <saurabh_>	will paste the code link ... 2 mins
| [Thursday 21 April 2011] [03:43:18] <sustrik>	thx
| [Thursday 21 April 2011] [03:44:33] <saurabh_>	http://pastebin.com/1xXYn4x3
| [Thursday 21 April 2011] [03:45:04] <saurabh_>	its java code ... it has some other oops stuff to create messages & all
| [Thursday 21 April 2011] [03:45:27] <saurabh_>	to explain xreq was sending messages numbered 1, 2, 3, etc.
| [Thursday 21 April 2011] [03:45:42] <saurabh_>	xrep used to read 10 messages & then shutdown
| [Thursday 21 April 2011] [03:46:23] <saurabh_>	but still xrep read 1-10, <shutdown>, 11,20, <shutdown>, 21-30
| [Thursday 21 April 2011] [03:46:36] <saurabh_>	after this xrep read msg no 96
| [Thursday 21 April 2011] [03:48:20] <saurabh_>	so i think some messages added to queue were persisted even though xrep shutdown & restart cycles
| [Thursday 21 April 2011] [03:48:22] <saurabh_>	ok?
| [Thursday 21 April 2011] [03:49:32] <sustrik>	they may have been already passed to the peer when the shutdown happened
| [Thursday 21 April 2011] [03:50:22] <saurabh_>	sry .. didn't get u
| [Thursday 21 April 2011] [03:51:18] <sustrik>	forget it, the last line i wrote is nonsense
| [Thursday 21 April 2011] [03:52:45] <sustrik>	ok, i see
| [Thursday 21 April 2011] [03:53:09] <sustrik>	MK_FG was right
| [Thursday 21 April 2011] [03:53:23] <sustrik>	xreq socket blocks when there's noone to send the message to
| [Thursday 21 April 2011] [03:53:30] <sustrik>	so when xrep is killed
| [Thursday 21 April 2011] [03:53:38] <sustrik>	the sending application just waits doing nothing
| [Thursday 21 April 2011] [03:53:50] <saurabh_>	i hadn't set hwm
| [Thursday 21 April 2011] [03:53:58] <saurabh_>	that happens only in case hwm is set
| [Thursday 21 April 2011] [03:54:04] <sustrik>	hwm is per-peer
| [Thursday 21 April 2011] [03:54:16] <sustrik>	if there's no peer, there's no queue to store messages in
| [Thursday 21 April 2011] [03:54:23] <sustrik>	so it simply blocks
| [Thursday 21 April 2011] [03:54:52] <sustrik>	this can be implemented better, but that's the way it is for now
| [Thursday 21 April 2011] [03:55:06] <saurabh_>	the xreq sending code was running throught ... it didn't block
| [Thursday 21 April 2011] [03:55:22] <saurabh_>	u see i sends one msg & then increments
| [Thursday 21 April 2011] [03:55:26] <saurabh_>	*it
| [Thursday 21 April 2011] [03:55:40] <sustrik>	and no message is dropped in the same test?
| [Thursday 21 April 2011] [03:55:41] <saurabh_>	so the sending code reached 90s in terms of msg sent
| [Thursday 21 April 2011] [03:56:04] <saurabh_>	messages were dropped - the ones in between 30 & 96
| [Thursday 21 April 2011] [03:56:11] <saurabh_>	saurabh_> but still xrep read 1-10, <shutdown>, 11,20, <shutdown>, 21-30
| [Thursday 21 April 2011] [03:56:17] <saurabh_>	<saurabh_> after this xrep read msg no 96
| [Thursday 21 April 2011] [03:56:52] <sustrik>	sound strange
| [Thursday 21 April 2011] [03:57:02] <sustrik>	please, create an issue in the bug tracker
| [Thursday 21 April 2011] [03:57:09] <sustrik>	i'll have a look later on
| [Thursday 21 April 2011] [03:57:14] <saurabh_>	ok
| [Thursday 21 April 2011] [04:04:14] <mikko>	pieterh: 2-2 builds get stuck occasionally
| [Thursday 21 April 2011] [04:04:25] <mikko>	/home/jenkins/build/jobs/libzmq2-2_clang-debian/workspace/tests/.libs/lt-test_pair_inproc
| [Thursday 21 April 2011] [04:04:34] <mikko>	Process 4830 attached - interrupt to quit
| [Thursday 21 April 2011] [04:04:35] <mikko>	recv(4, 
| [Thursday 21 April 2011] [04:04:40] <mikko>	blocking on recv
| [Thursday 21 April 2011] [04:14:16] <djc>	mikko: I'm back now, if you have time to investigate the --with-system-pgm issues
| [Thursday 21 April 2011] [04:15:26] <cwb>	I'm trying a minimal test case using pyzmq and 0MQ 2.1.5 on Ubuntu 10.04 and am getting a "Bad address" on the socket.recv() command. I've opened my firewalls up fully so I don't think that is the problem. What does might "Bad address" mean?
| [Thursday 21 April 2011] [04:18:16] <cwb>	I'm using pyzmq 2.1.4
| [Thursday 21 April 2011] [04:19:56] <th>	cwb: that was a mistake in the 2.1.5 release - thats why it's no longer available for download
| [Thursday 21 April 2011] [04:20:58] <cwb>	Aha, thanks! Am I better of using 2.1.4 or trunk?
| [Thursday 21 April 2011] [04:21:28] <guido_g>	2.1.4
| [Thursday 21 April 2011] [04:21:38] <th>	there is a fix in git already, but asking that question yesterday i got the answer that there is no recommended git revision in 21 branch > 2.1.4 meaning that i should use 2.1.4
| [Thursday 21 April 2011] [04:22:46] <cwb>	Super, thanks for your help.
| [Thursday 21 April 2011] [04:35:56] <benoitc>	hum not sure to understand,, reading the code of mongrel2 it seems to bind to a PUSH socket where i thought we could just connect
| [Thursday 21 April 2011] [04:36:13] <benoitc>	in which case can you connect to PUSH or bind ?
| [Thursday 21 April 2011] [04:37:27] <MK_FG>	benoitc, Why it can't be both? ;)
| [Thursday 21 April 2011] [04:38:28] <benoitc>	well pyzmq tell me "unknown error Operation not supported by device
| [Thursday 21 April 2011] [04:38:29] <benoitc>	"
| [Thursday 21 April 2011] [04:38:42] <benoitc>	and i don't understand the bind here then
| [Thursday 21 April 2011] [04:39:07] <benoitc>	how could I get connections on a PUSH ? if i cant recv
| [Thursday 21 April 2011] [04:39:43] <MK_FG>	Same error for me
| [Thursday 21 April 2011] [04:40:20] <MK_FG>	But I don't really understand the limitation - .connect() and socket operations seem to be orthogonal
| [Thursday 21 April 2011] [04:41:00] <guido_g>	benoitc: huh? push is send only
| [Thursday 21 April 2011] [04:41:06] <guido_g>	what do you do?
| [Thursday 21 April 2011] [04:41:15] <benoitc>	if i read the doc it tells "zmq_bind - accept connections on a socket" (like a socket) , since you can't recv on PUSH it sound logical you can't recv
| [Thursday 21 April 2011] [04:41:18] <guido_g>	minimal example -> pastebin
| [Thursday 21 April 2011] [04:41:24] <benoitc>	guido_g: that what I say
| [Thursday 21 April 2011] [04:41:25] <djc>	mikko: I used objdump -T instead of nm, that gives symbols
| [Thursday 21 April 2011] [04:41:34] <djc>	(our way of building openpgm strips libraries)
| [Thursday 21 April 2011] [04:41:35] <benoitc>	i don't understand how you could bind them
| [Thursday 21 April 2011] [04:41:38] <benoitc>	then
| [Thursday 21 April 2011] [04:41:50] <djc>	but pgm_send isn't in there (a bunch of other pgm_* functions are)
| [Thursday 21 April 2011] [04:42:10] <MK_FG>	benoitc, You can bind XREQ socket and then .send() on it
| [Thursday 21 April 2011] [04:42:29] <benoitc>	guido_g: in mongrel2 code I have void *handler_socket = mqsocket(ZMQ_PUSH);
| [Thursday 21 April 2011] [04:42:36] <benoitc>	rc = zmq_bind(handler_socket, send_spec);
| [Thursday 21 April 2011] [04:42:52] <benoitc>	not sure how you could bind on a PUSH here
| [Thursday 21 April 2011] [04:42:56] <guido_g>	and?
| [Thursday 21 April 2011] [04:43:04] <benoitc>	and I can't do it with pyzmq.
| [Thursday 21 April 2011] [04:43:28] <benoitc>	binding on somthing you can't recv is illogical for me.
| [Thursday 21 April 2011] [04:43:34] <MK_FG>	benoitc, Not that I advise to use XREQ, just want to point out that .connect doesn't seem to conflict with high-level queueing operations
| [Thursday 21 April 2011] [04:43:36] <benoitc>	so pyzmq looks right
| [Thursday 21 April 2011] [04:44:32] <benoitc>	MK_FG: II agree, you can obviously send on a binded socket, just trying to understand if normally you can bind on a PUSH and if in this case there isn't a bug in pyzmq
| [Thursday 21 April 2011] [04:45:08] <guido_g>	benoitc: https://gist.github.com/933998 works here
| [Thursday 21 April 2011] [04:45:38] <guido_g>	tcp        0      0 0.0.0.0:9998            0.0.0.0:*               LISTEN      15755/python
| [Thursday 21 April 2011] [04:45:46] <guido_g>	netstat says
| [Thursday 21 April 2011] [04:47:03] <MK_FG>	Erm... indeed it works, as I'd expect, and my "same error for me" before was yet another copy-pasting bug of mine, sorry
| [Thursday 21 April 2011] [04:47:15] <guido_g>	tz tz tz
| [Thursday 21 April 2011] [04:47:40] <MK_FG>	Just pasted push into code that does .recv() and seen the same error
| [Thursday 21 April 2011] [04:47:52] <guido_g>	omg
| [Thursday 21 April 2011] [04:48:08] <MK_FG>	...w/o looking at the line where the error actually happens
| [Thursday 21 April 2011] [04:52:00] <benoitc>	hum definitly have something weird in my code then
| [Thursday 21 April 2011] [04:52:53] <benoitc>	and now wondering how i can manage things simply on a multiprocess tcp->zeromq thing
| [Thursday 21 April 2011] [04:53:19] <guido_g>	whatever that might be
| [Thursday 21 April 2011] [04:53:53] <benoitc>	https://github.com/benoitc/tproxy/commit/b7a36aff16de593a16d27a5dbff444f9d9e8558c .
| [Thursday 21 April 2011] [04:54:16] <benoitc>	but problem is that i can have only one handler behind. 
| [Thursday 21 April 2011] [04:54:30] <benoitc>	so i should change the way I bind/connect to sockets
| [Thursday 21 April 2011] [04:55:07] <benoitc>	since obviously i can only have one bind, 
| [Thursday 21 April 2011] [04:57:49] <guido_g>	i _guess_ that you want to take on arbitrary tcp connections and forward the data via mq push socket, right?
| [Thursday 21 April 2011] [04:58:47] <benoitc>	yup 
| [Thursday 21 April 2011] [04:59:12] <guido_g>	ok
| [Thursday 21 April 2011] [04:59:51] <guido_g>	next assumption would be that you have "worker" that fetch data from the mq push socket
| [Thursday 21 April 2011] [05:00:13] <guido_g>	s/"worker"/a bunch of "workers"/
| [Thursday 21 April 2011] [05:00:17] <benoitc>	well i have one tcp socket shared between workers on different cpus
| [Thursday 21 April 2011] [05:00:38] <guido_g>	what you have is not necessarily what you need
| [Thursday 21 April 2011] [05:00:41] <benoitc>	the tcp request is handle by one of the worker depending how the system loadbalanced it
| [Thursday 21 April 2011] [05:01:06] <benoitc>	gand yes second operation is that
| [Thursday 21 April 2011] [05:01:15] <benoitc>	guido_g: any idea ?
| [Thursday 21 April 2011] [05:02:12] <guido_g>	you read the data from the tcp sockets and send them to the push socket
| [Thursday 21 April 2011] [05:02:49] <guido_g>	on the worker side you fetch da data via a pull socket
| [Thursday 21 April 2011] [05:02:52] <benoitc>	mmm no i read the data from tcp soccket and send them via the push socket
| [Thursday 21 April 2011] [05:03:01] <guido_g>	what?
| [Thursday 21 April 2011] [05:03:14] <benoitc>	and have a pull handler
| [Thursday 21 April 2011] [05:03:19] <benoitc>	that what I have now
| [Thursday 21 April 2011] [05:03:35] <benoitc>	the push socket is sending them to the pull socket
| [Thursday 21 April 2011] [05:03:41] <guido_g>	of couse
| [Thursday 21 April 2011] [05:03:43] <guido_g>	*course
| [Thursday 21 April 2011] [05:03:56] <benoitc>	tehn i resend them to tcp using a PUB/SUB
| [Thursday 21 April 2011] [05:04:21] <guido_g>	what?
| [Thursday 21 April 2011] [05:04:40] <guido_g>	lets make clear, tcp means raw tcp sockets, os level
| [Thursday 21 April 2011] [05:04:46] <guido_g>	pub/sub is mq
| [Thursday 21 April 2011] [05:04:49] <benoitc>	yes
| [Thursday 21 April 2011] [05:05:12] <guido_g>	then "<benoitc> tehn i resend them to tcp using a PUB/SUB" doesn't make sense
| [Thursday 21 April 2011] [05:05:24] <benoitc>	the pull worker, publish the message, and the tcp worker suscribing to this message and resend it
| [Thursday 21 April 2011] [05:05:31] <benoitc>	to the tcp
| [Thursday 21 April 2011] [05:05:43] <guido_g>	ahhh... much better
| [Thursday 21 April 2011] [05:06:39] <guido_g>	you're using mongrel2, right?
| [Thursday 21 April 2011] [05:07:24] <guido_g>	so this push and pub/sub mixture is inevitable
| [Thursday 21 April 2011] [05:08:18] <benoitc>	i have http://friendpaste.com/6DuX34KU54f0rs89epqOZY
| [Thursday 21 April 2011] [05:08:34] <benoitc>	mongrel2 do differently and isn't multicore so that why it works
| [Thursday 21 April 2011] [05:08:57] <benoitc>	mongrel2 bind to a PUSH socket where I connect
| [Thursday 21 April 2011] [05:09:05] <benoitc>	and connect to a PULL where i bind
| [Thursday 21 April 2011] [05:09:15] <benoitc>	the same is true for PUB/SUB
| [Thursday 21 April 2011] [05:09:41] <benoitc>	the advantage for mongrel2 is that it can balance a worker to multiple handler, where I can have only one
| [Thursday 21 April 2011] [05:10:01] <benoitc>	which is better imo
| [Thursday 21 April 2011] [05:10:02] 	 * guido_g is confused
| [Thursday 21 April 2011] [05:10:17] <benoitc>	balance a tcp request sorry
| [Thursday 21 April 2011] [05:10:36] <guido_g>	i simply don't get what you want
| [Thursday 21 April 2011] [05:10:58] <benoitc>	i can only have one zmq handler accepting forwarded tcp requests currently
| [Thursday 21 April 2011] [05:11:43] <benoitc>	and I would like to have more than one to remove and add them dynamically
| [Thursday 21 April 2011] [05:12:11] <guido_g>	you can add as much handlers as you want to a push socket
| [Thursday 21 April 2011] [05:12:18] <benoitc>	the problem is that I can't do it right now in my schem
| [Thursday 21 April 2011] [05:12:23] <benoitc>	only if i bind it
| [Thursday 21 April 2011] [05:12:42] <guido_g>	??
| [Thursday 21 April 2011] [05:15:34] <benoitc>	you need to bind the PUSH and connect to a PULL load balance PUSH to PULL
| [Thursday 21 April 2011] [05:16:03] <guido_g>	you bind the push socket
| [Thursday 21 April 2011] [05:16:24] <guido_g>	you connect the pulls from the workers to the bound address of the push
| [Thursday 21 April 2011] [05:16:44] <guido_g>	where is the problem?
| [Thursday 21 April 2011] [05:17:03] <benoitc>	yes so that something I can't in my design. since i'm multicore and read the route depending on the data (the conf is not loaded at first)
| [Thursday 21 April 2011] [05:17:12] <mikko>	djc: i installed upstream openpgm
| [Thursday 21 April 2011] [05:17:20] <mikko>	djc: and --with-system-pgm seems to link ok
| [Thursday 21 April 2011] [05:17:31] <djc>	mikko: what version did you get?
| [Thursday 21 April 2011] [05:17:34] <guido_g>	benoitc: what has multicore to do with that?
| [Thursday 21 April 2011] [05:18:01] <guido_g>	benoitc: and if you don't have the config, then you should better make sure the config there when you need it
| [Thursday 21 April 2011] [05:18:05] <mikko>	hmm, spotify just rickrolled me
| [Thursday 21 April 2011] [05:18:10] <benoitc>	cause i'm know that I have to use a PUSH socket only in the worker.
| [Thursday 21 April 2011] [05:18:12] <mikko>	random music playing
| [Thursday 21 April 2011] [05:18:17] <mikko>	djc: 5.1.115
| [Thursday 21 April 2011] [05:18:19] <djc>	did you see my messages before, about objdump?
| [Thursday 21 April 2011] [05:18:23] <benoitc>	and I can't bind to a PUSH socket in each workers.
| [Thursday 21 April 2011] [05:18:34] <mikko>	djc: yep
| [Thursday 21 April 2011] [05:18:34] <guido_g>	benoitc: then don't do it
| [Thursday 21 April 2011] [05:18:41] <mikko>	djc: not sure why the symbol isn't there
| [Thursday 21 April 2011] [05:18:48] <mikko>	djc: does your build break it?
| [Thursday 21 April 2011] [05:19:02] <mikko>	as in visibility flags foobarred or something
| [Thursday 21 April 2011] [05:19:09] <djc>	mikko: so does your build of upstream openpgm show symbols for nm?
| [Thursday 21 April 2011] [05:19:28] <djc>	and if you do objdump -T, does it show pgm_send?
| [Thursday 21 April 2011] [05:19:46] <mikko>	djc: give me a second, just ran to swap starting a virtual machine
| [Thursday 21 April 2011] [05:19:49] <benoitc>	jaja i like such answer. anyway thanks will try to revisit the way i can handle it. or just trash this support, thanks for the help
| [Thursday 21 April 2011] [05:20:28] <guido_g>	benoitc: hey, don't blame me if you're not capable of explaining what you want
| [Thursday 21 April 2011] [05:20:38] <mikko>	djc: # nm /usr/local/lib/libpgm.so | grep pgm_send
| [Thursday 21 April 2011] [05:20:38] <mikko>	000000000002d555 T pgm_send
| [Thursday 21 April 2011] [05:21:54] <djc>	right, and now with objdump -T?
| [Thursday 21 April 2011] [05:22:16] <mikko>	000000000002d555 g    DF .text  0000000000000241  Base        pgm_send
| [Thursday 21 April 2011] [05:22:29] <djc>	ugh
| [Thursday 21 April 2011] [05:22:33] <djc>	that's pretty weird
| [Thursday 21 April 2011] [05:22:53] <mikko>	try taking the upstream tarball and building to --prefix
| [Thursday 21 April 2011] [05:23:07] <mikko>	is the gentoo .so built with scons or autotools?
| [Thursday 21 April 2011] [05:23:27] <mikko>	can you build unstripped version?
| [Thursday 21 April 2011] [05:23:29] <djc>	autotools, I think
| [Thursday 21 April 2011] [05:23:46] <benoitc>	guido_g: i wouln't say that also didn't put any blame in my sentence.
| [Thursday 21 April 2011] [05:24:38] <djc>	mikko: building without stripping now, let's see what happens
| [Thursday 21 April 2011] [05:24:53] <guido_g>	benoitc: "<benoitc> jaja i like such answer..." <- reads like someone is unhappy
| [Thursday 21 April 2011] [05:25:31] <guido_g>	benoitc: try to describe what you want to achieve, not what you have (and what obviously is not working)
| [Thursday 21 April 2011] [05:26:28] <djc>	mikko: when building with "nostrip", I see pgm_send in nm but not in objdump -T
| [Thursday 21 April 2011] [05:26:34] <djc>	so something is fishy there
| [Thursday 21 April 2011] [05:27:51] <benoitc>	to decribe what i want to achieve i needed to decribe what I had and what i want to achieve, so i can make it perfectly clear that route is handled on the worker level and until this moment i don't know if Ihave to uforward to a zmq thing, or simply forwarding tcp. so i can not pre-bind
| [Thursday 21 April 2011] [05:29:21] <mikko>	djc: can you try with upstream tarball?
| [Thursday 21 April 2011] [05:29:37] <mikko>	do you apply weird patches on gentoo side?
| [Thursday 21 April 2011] [05:29:38] <djc>	mikko: this is from the upstream tarball
| [Thursday 21 April 2011] [05:29:42] <djc>	no openpgm patches
| [Thursday 21 April 2011] [05:29:49] <mikko>	5.1.115?
| [Thursday 21 April 2011] [05:30:00] <djc>	yup
| [Thursday 21 April 2011] [05:30:00] <guido_g>	benoitc: sorry, can't parse that
| [Thursday 21 April 2011] [05:34:16] <djc>	mikko: so are you building with autotools or cmake?
| [Thursday 21 April 2011] [05:34:16] <mikko>	djc: interesting
| [Thursday 21 April 2011] [05:34:22] <mikko>	djc: autotools
| [Thursday 21 April 2011] [05:34:30] <mikko>	i've been using cmake lately
| [Thursday 21 April 2011] [05:34:42] <mikko>	and it makes autotools look pretty cumbersome
| [Thursday 21 April 2011] [05:35:00] <mikko>	off-topic
| [Thursday 21 April 2011] [05:35:08] <djc>	so where is visibility controlled with autotools?
| [Thursday 21 April 2011] [05:35:18] <djc>	or s/where/how/
| [Thursday 21 April 2011] [05:35:18] <mikko>	djc: what do you mean?
| [Thursday 21 April 2011] [05:35:24] <mikko>	-fvisibility to compiler
| [Thursday 21 April 2011] [05:35:40] <mikko>	it's a compiler thing rather than autotools
| [Thursday 21 April 2011] [05:35:52] <mikko>	although i don't see why the symbol isn't there at all
| [Thursday 21 April 2011] [05:36:04] <mikko>	even if the symbol was hidden it should still be there (just hidden)
| [Thursday 21 April 2011] [05:36:09] <djc>	for example, I'm passing -DCONFIG_HAVE_DSO_VISIBILITY
| [Thursday 21 April 2011] [05:36:20] <djc>	could that have anything to do with it?
| [Thursday 21 April 2011] [05:36:53] <mikko>	shouldn't
| [Thursday 21 April 2011] [05:37:07] <mikko>	can you compile without optimizations as well?
| [Thursday 21 April 2011] [05:37:10] <mikko>	-O0
| [Thursday 21 April 2011] [05:37:26] <mikko>	just to be sure that the symbol doesn't accidentally get optimised out
| [Thursday 21 April 2011] [05:38:07] <djc>	I'll give it a shot
| [Thursday 21 April 2011] [05:39:44] <djc>	with -O0 it's the same
| [Thursday 21 April 2011] [05:39:54] <benoitc>	guido_g: drawing a schema
| [Thursday 21 April 2011] [05:40:38] <mikko>	djc: that is just strange
| [Thursday 21 April 2011] [05:41:01] <djc>	this is the compiler invocation on source.c (which defines pgm_send, I think): http://paste.pocoo.org/show/375706/
| [Thursday 21 April 2011] [05:41:32] <guido_g>	benoitc: good idea
| [Thursday 21 April 2011] [05:42:52] <guido_g>	benoitc: you might want to try https://www.lucidchart.com 
| [Thursday 21 April 2011] [05:43:54] <mikko>	djc: i just downloaded 5.1.116
| [Thursday 21 April 2011] [05:44:04] <mikko>	and the symbol is there after fresh compile
| [Thursday 21 April 2011] [05:44:10] <mikko>	what gcc version are you using?
| [Thursday 21 April 2011] [05:44:20] <mikko>	# nm /opt/test-pgm/lib/libpgm.so  | grep pgm_send
| [Thursday 21 April 2011] [05:44:21] <mikko>	00020910 T pgm_send
| [Thursday 21 April 2011] [05:44:36] <mikko>	gcc version 4.4.5 (Debian 4.4.5-8) 
| [Thursday 21 April 2011] [05:44:38] <benoitc>	guido_g: thanks
| [Thursday 21 April 2011] [05:44:39] <mikko>	ia32
| [Thursday 21 April 2011] [05:45:05] <djc>	gcc (Gentoo 4.4.5 p1.2, pie-0.4.5) 4.4.5
| [Thursday 21 April 2011] [05:45:15] <djc>	let me try .116
| [Thursday 21 April 2011] [05:45:59] <djc>	(on amd64)
| [Thursday 21 April 2011] [05:46:08] <mikko>	just compiled on amd64 as well
| [Thursday 21 April 2011] [05:46:11] <mikko>	the symbol is still there
| [Thursday 21 April 2011] [05:46:40] <djc>	are you familiar with the openpgm community?
| [Thursday 21 April 2011] [05:47:37] <mikko>	yes
| [Thursday 21 April 2011] [05:47:40] <mikko>	well, steven
| [Thursday 21 April 2011] [05:48:09] <djc>	ah! objdump -T on the libpgm-5.1.so.0.0.116 has pgm_send
| [Thursday 21 April 2011] [05:48:40] <djc>	so would it be safe to use zeromq-2.1.5 (or .5.1 or whatever will be released soon) with openpgm-5.1.116?
| [Thursday 21 April 2011] [05:50:09] <djc>	ah, it's probably this: http://code.google.com/p/openpgm/source/detail?r=1360
| [Thursday 21 April 2011] [05:50:49] <djc>	and it looks like the changes between .115 and .116 are fairly minor
| [Thursday 21 April 2011] [05:50:55] <djc>	(there's only one other change)
| [Thursday 21 April 2011] [05:51:47] <mikko>	should be ok
| [Thursday 21 April 2011] [05:52:16] <mikko>	can you comment on the ticket as well?
| [Thursday 21 April 2011] [05:52:20] <mikko>	on the progress
| [Thursday 21 April 2011] [05:52:27] <djc>	will do
| [Thursday 21 April 2011] [05:52:35] <mikko>	so that other people possibly facing the same issue can benfit
| [Thursday 21 April 2011] [05:52:45] <mikko>	pieterh: have you merged message fixes to 2.2 ?
| [Thursday 21 April 2011] [05:54:41] <djc>	mikko: so we like to remove bundled libraries from the process to make sure they don't get built
| [Thursday 21 April 2011] [05:54:55] <djc>	but that seems to fail
| [Thursday 21 April 2011] [05:55:18] <djc>	ah wait, is pgm still optional with zeromq-2.1?
| [Thursday 21 April 2011] [06:02:58] <mikko>	yes
| [Thursday 21 April 2011] [06:03:17] <djc>	it would be nice if the foreign/openpgm/Makefile.in was optional
| [Thursday 21 April 2011] [06:03:18] <mikko>	what do you mean "seems to fail" ?
| [Thursday 21 April 2011] [06:03:28] <mikko>	autotools doesn't support that
| [Thursday 21 April 2011] [06:03:38] <djc>	mm, ok
| [Thursday 21 April 2011] [06:03:53] <mikko>	i had a long fight with autotools to get it even this flexible :)
| [Thursday 21 April 2011] [06:04:11] <mikko>	http://www.gnu.org/software/hello/manual/automake/Conditional-Subdirectories.html
| [Thursday 21 April 2011] [06:04:13] <djc>	ah, nice, I made it remove the libpgm tarball in there
| [Thursday 21 April 2011] [06:04:21] <djc>	and leave the Makefile.in
| [Thursday 21 April 2011] [06:04:26] <djc>	and that seems to work fine
| [Thursday 21 April 2011] [06:04:36] <mikko>	it should
| [Thursday 21 April 2011] [06:04:55] <mikko>	it would be nice to be able to make it fully conditional but that doesn't seem to be possible
| [Thursday 21 April 2011] [06:05:04] <djc>	okay, so that was the without-pgm build, let's check the with-system-pgm build once more
| [Thursday 21 April 2011] [06:05:49] <djc>	yup, works
| [Thursday 21 April 2011] [06:05:52] <djc>	I think we're done here
| [Thursday 21 April 2011] [06:05:57] <djc>	thanks a lot for the help!
| [Thursday 21 April 2011] [06:06:27] <mikko>	no problem
| [Thursday 21 April 2011] [06:06:48] <mikko>	hopefully debian and others follow soon
| [Thursday 21 April 2011] [06:07:10] <mikko>	if debian packages zeromq 2.1 it should trickle down to ubuntu and kubuntu pretty soon(ish)
| [Thursday 21 April 2011] [06:07:31] <djc>	so now that this is fixed, will 2.1.5.1 be released soon?
| [Thursday 21 April 2011] [06:07:42] <djc>	i.e. has the other 2.1.5 problem been fixed?
| [Thursday 21 April 2011] [06:07:55] <mikko>	yes, http://build.zero.mq/view/libzmq%202.1/
| [Thursday 21 April 2011] [06:08:01] <mikko>	this is this morning's build
| [Thursday 21 April 2011] [06:08:44] <mikko>	tests seem to pass at least
| [Thursday 21 April 2011] [06:14:58] <benoitc>	guido_g: http://www.lucidchart.com/publicSegments/view/4db0036d-f058-4240-8613-59060ad6198e/image.png is what I'm trying to achieve
| [Thursday 21 April 2011] [06:15:40] <guido_g>	ouch
| [Thursday 21 April 2011] [06:15:47] <guido_g>	why accepts in multiple processes?
| [Thursday 21 April 2011] [06:16:18] <benoitc>	to load balance the connection
| [Thursday 21 April 2011] [06:16:30] <mikko>	you can accept and pass down the accepted handle
| [Thursday 21 April 2011] [06:16:31] <guido_g>	accept in one process and send the fd of the accepted socket to a child
| [Thursday 21 April 2011] [06:16:40] <mikko>	makes it easier architecturally to accept in one process
| [Thursday 21 April 2011] [06:16:46] <mikko>	guido_g: >)
| [Thursday 21 April 2011] [06:17:13] <benoitc>	well not really , here we let the os load balance the connection, he knows its job
| [Thursday 21 April 2011] [06:17:19] <benoitc>	s/its/his
| [Thursday 21 April 2011] [06:17:45] <guido_g>	ic
| [Thursday 21 April 2011] [06:17:52] <mikko>	that's what i've been wondering 
| [Thursday 21 April 2011] [06:18:05] <mikko>	do you get a race condition when you have multiple acceptors?
| [Thursday 21 April 2011] [06:18:10] <mikko>	or does the os invoke just one?
| [Thursday 21 April 2011] [06:18:19] <benoitc>	the os invoke just one
| [Thursday 21 April 2011] [06:18:23] <guido_g>	it damn complicated to get right, see apache code
| [Thursday 21 April 2011] [06:18:29] <guido_g>	*its
| [Thursday 21 April 2011] [06:18:37] <benoitc>	you share the socket handle between all the workers
| [Thursday 21 April 2011] [06:19:04] <guido_g>	why should one do that?
| [Thursday 21 April 2011] [06:19:21] <guido_g>	what os is that?
| [Thursday 21 April 2011] [06:19:42] <benoitc>	well this is designed for atchiecture where you can't spawn os threads
| [Thursday 21 April 2011] [06:19:48] <benoitc>	between cpus
| [Thursday 21 April 2011] [06:19:57] <benoitc>	eg any python programs.
| [Thursday 21 April 2011] [06:20:13] <benoitc>	any UNIX/POSIX system is designed for that
| [Thursday 21 April 2011] [06:20:16] <guido_g>	huh?
| [Thursday 21 April 2011] [06:20:39] <benoitc>	1 python vm is locked to once CPU.
| [Thursday 21 April 2011] [06:20:42] <benoitc>	one
| [Thursday 21 April 2011] [06:20:51] <guido_g>	it'S not locked
| [Thursday 21 April 2011] [06:20:57] <benoitc>	it is.
| [Thursday 21 April 2011] [06:21:02] <benoitc>	gil and such
| [Thursday 21 April 2011] [06:21:08] <guido_g>	threads are synchroniced by t eh gil
| [Thursday 21 April 2011] [06:21:13] <guido_g>	which is something compeltely differnt
| [Thursday 21 April 2011] [06:21:28] <guido_g>	but with processes it would work
| [Thursday 21 April 2011] [06:21:50] <benoitc>	well by process you mean os forks ?
| [Thursday 21 April 2011] [06:22:02] <guido_g>	and what i suggested was exactly that: one process accepts the tcp connection and forwards the socket fd to a child process
| [Thursday 21 April 2011] [06:22:26] <benoitc>	and what is your policy to load balance ?
| [Thursday 21 April 2011] [06:22:33] <benoitc>	also that exactly what does teh os here 
| [Thursday 21 April 2011] [06:22:46] <benoitc>	you share the socket fd between forks
| [Thursday 21 April 2011] [06:22:58] <benoitc>	and only one will accept
| [Thursday 21 April 2011] [06:23:10] <guido_g>	no, between parent and child processes, for is system call
| [Thursday 21 April 2011] [06:23:14] <guido_g>	*fork is a
| [Thursday 21 April 2011] [06:24:05] <benoitc>	yes sure. so what are you calling process ?
| [Thursday 21 April 2011] [06:24:06] <guido_g>	your diagrams states that you do the accept in the workers, which is -- as some of know -- a very very bad idea
| [Thursday 21 April 2011] [06:24:20] <benoitc>	could be anything , os threads, threads or green threads or os processes
| [Thursday 21 April 2011] [06:24:39] <benoitc>	not really that's unixish
| [Thursday 21 April 2011] [06:24:43] <benoitc>	share a socket
| [Thursday 21 April 2011] [06:24:46] <benoitc>	accept on it
| [Thursday 21 April 2011] [06:24:51] <benoitc>	the os will load balance
| [Thursday 21 April 2011] [06:25:00] <benoitc>	that what does nginx, gunicorn, unicorn and such
| [Thursday 21 April 2011] [06:25:04] <guido_g>	benoitc: http://en.wikipedia.org/wiki/Process_(computing)
| [Thursday 21 April 2011] [06:25:26] <guido_g>	benoitc: no, the os will not "loadbalance"
| [Thursday 21 April 2011] [06:25:33] <benoitc>	yes it will.
| [Thursday 21 April 2011] [06:25:53] <benoitc>	that what we use in gunicorn
| [Thursday 21 April 2011] [06:25:56] <guido_g>	it will just allow the processes to run as they need according to the os's scheduling policy
| [Thursday 21 April 2011] [06:26:19] <guido_g>	benoitc: ok, show me the load-balancing in the linux kernel, please
| [Thursday 21 April 2011] [06:26:30] <benoitc>	and if it can.
| [Thursday 21 April 2011] [06:27:37] <guido_g>	to distribute load is not load balancing
| [Thursday 21 April 2011] [06:27:59] <benoitc>	if your cpu is busy or the process is it won't pass to it. that what we call load balancing
| [Thursday 21 April 2011] [06:28:54] <benoitc>	that part works pefrfectly anyway. that not the part i'm trying to achieve.
| [Thursday 21 April 2011] [06:29:00] <guido_g>	load balancing is a process where the load is sent to a specific processing unit according to some algorithm
| [Thursday 21 April 2011] [06:29:13] <guido_g>	the kernel and your code don't do that
| [Thursday 21 April 2011] [06:31:17] <benoitc>	oh dear. load balancing only mean that it will balance depeding on the load. ie if smth is busy or not . that could be just a try/fail system. which is done by the os.
| [Thursday 21 April 2011] [06:31:59] <benoitc>	anyway you're just here saying a common pattern in unix doesn't work. 
| [Thursday 21 April 2011] [06:32:17] <guido_g>	what?
| [Thursday 21 April 2011] [06:57:52] <benoitc>	to be clear, all workers share the same listener and do a non blocking acccept. The kernel decide which worker process will get the socket and the other will sleeps if there is nothing to accept, this model works well. that's more the second part i'hev problem to achieve
| [Thursday 21 April 2011] [08:17:10] <th>	anyone interested in looking into an c++ example where multipart messages get mixed?
| [Thursday 21 April 2011] [08:21:39] <th>	i collected information here: http://thzn.de/0mq/   client (stress.cc) and server (server.cc) with output.txt
| [Thursday 21 April 2011] [08:24:49] <th>	every part of the multipart message is prefixed when sending. and the receiving side checks that all parts of the received mp have the same prefix. which fails
| [Thursday 21 April 2011] [08:25:05] <th>	it only fails under high load
| [Thursday 21 April 2011] [08:25:17] <th>	(meaning: while ./stress.cc ; do ; done)
| [Thursday 21 April 2011] [08:25:24] <th>	aehh.. not ".cc" of course
| [Thursday 21 April 2011] [08:27:13] <th>	the server also prints the identity (XREP) received as first part in hex
| [Thursday 21 April 2011] [08:33:11] <pieterh_>	th: can you post to the list?
| [Thursday 21 April 2011] [08:33:47] <pieterh_>	I'm not at a pc now but will look at it later
| [Thursday 21 April 2011] [08:48:52] <th>	pieterh_: done.
| [Thursday 21 April 2011] [09:02:37] <Balistic>	How can one do proper message routing(Based on contents of a message) in zmq?
| [Thursday 21 April 2011] [09:11:13] <guido_g>	from the channel topic: Before asking for advice here, Please Read the Guide - http://zero.mq/zg
| [Thursday 21 April 2011] [09:12:30] <Balistic>	guido_g: i read that a few months ago, had nothing on routing
| [Thursday 21 April 2011] [09:12:44] <guido_g>	yeah
| [Thursday 21 April 2011] [09:13:25] <guido_g>	but now is now
| [Thursday 21 April 2011] [09:14:50] <Balistic>	i see, the guide is more than double in length compared to what it was
| [Thursday 21 April 2011] [09:18:15] <mpales>	Balistic: would you like to use zeromq for stateful services?
| [Thursday 21 April 2011] [09:20:12] <Balistic>	mpales: yes
| [Thursday 21 April 2011] [09:28:42] <mpales>	zeromq is not quite there yet
| [Thursday 21 April 2011] [09:29:24] <mpales>	and it's not quite its job to do application level routing
| [Thursday 21 April 2011] [09:30:08] <mpales>	it would really help if zeromq had an "email" type socket
| [Thursday 21 April 2011] [09:31:40] <mpales>	atm you need to do the address mapping yourself
| [Thursday 21 April 2011] [12:04:07] <coopernurse>	if you have a REQ connected to REP and doing a send/recv loop
| [Thursday 21 April 2011] [12:04:29] <coopernurse>	will the REQ socket reconnect automatically if the REP endpoint dies and is restarted on the same port?
| [Thursday 21 April 2011] [12:05:00] <coopernurse>	I'm using 2.1 with the Python bindings
| [Thursday 21 April 2011] [12:06:08] <coopernurse>	the behavior I'm seeing is the REQ process is still running, but idle after I restarted the REP process
| [Thursday 21 April 2011] [12:53:09] <Toba>	that depends on if you use a timeout or not on the recv portion. if you don't use pollitem_t and not recv() until you know there is a result, a "lost result" can hang a looping requestor.
| [Thursday 21 April 2011] [12:53:48] <coopernurse>	Toba: ah, cool, thank you I'll read about that more
| [Thursday 21 April 2011] [13:01:16] <Toba>	note to self: add timeout on the recv portion of my req/rep systems
| [Thursday 21 April 2011] [13:01:48] <coopernurse>	:-)
| [Thursday 21 April 2011] [15:20:51] <else->	hm, anyone knows why my libzapi git checkout fails during compilation of zsocket.c with "zsocket.c:116:28: error: ZMQ_XSUB undeclared"? i'm at commit 2c1bd38bfd1220226c04c03a39a28e62adf4c631
| [Thursday 21 April 2011] [16:24:07] <Bwen>	I was looking thru the irc archive and I was wondering why there is 3 "2010-March" ? O.o
| [Thursday 21 April 2011] [16:24:59] <lt_schmidt_jr>	3 subscribers consuming  a published event :)
| [Thursday 21 April 2011] [17:28:10] <hardwire>	ahoy.
| [Thursday 21 April 2011] [17:28:19] 	 * hardwire parts #0mq
| [Thursday 21 April 2011] [17:29:29] <hardwire>	I don't suppose there is a way to subscribe to published data and filter if the publisher sends json is there.
| [Thursday 21 April 2011] [17:30:31] <hardwire>	unless the json is ordered.
| [Thursday 21 April 2011] [17:42:21] <lt_schmidt_jr>	hardwire, I don't understand the question
| [Thursday 21 April 2011] [17:43:00] <hardwire>	subscription filters pass strings that start with the filter
| [Thursday 21 April 2011] [17:43:27] <lt_schmidt_jr>	but I am using PUB/SUB with json with multipart with the first part of the message containing the data (bytes) used for routing
| [Thursday 21 April 2011] [17:43:41] <hardwire>	since item order in json isn't static in most cases.. it's hard to filter unless you post process and subscribe to everything
| [Thursday 21 April 2011] [17:44:27] <hardwire>	lt_schmidt_jr: so you're concatenating a json string and a routing string?
| [Thursday 21 April 2011] [17:45:18] <lt_schmidt_jr>	no - ZMQ allows for multipart messages
| [Thursday 21 April 2011] [17:45:28] <lt_schmidt_jr>	I use 2 parts 
| [Thursday 21 April 2011] [17:46:06] <lt_schmidt_jr>	1st is the routing data
| [Thursday 21 April 2011] [17:46:38] <lt_schmidt_jr>	2nd is the json
| [Thursday 21 April 2011] [17:46:42] <lt_schmidt_jr>	string
| [Thursday 21 April 2011] [17:48:17] <lt_schmidt_jr>	you can just use the 2nd part for whatever it is you intend to do with it
| [Thursday 21 April 2011] [17:52:31] <hardwire>	what api are you using?
| [Thursday 21 April 2011] [17:52:56] <lt_schmidt_jr>	i am using jzmq
| [Thursday 21 April 2011] [17:53:29] <lt_schmidt_jr>	java, but its available in the c api as well, should be in other
| [Thursday 21 April 2011] [17:53:31] <lt_schmidt_jr>	s
| [Thursday 21 April 2011] [17:53:35] <hardwire>	<- python
| [Thursday 21 April 2011] [17:56:56] <hardwire>	ah.. spiffers
| [Thursday 21 April 2011] [17:56:57] <hardwire>	danke
| [Thursday 21 April 2011] [17:57:10] <lt_schmidt_jr>	did you find it?
| [Thursday 21 April 2011] [18:08:56] <hardwire>	your a genus.
| [Thursday 21 April 2011] [18:09:15] <hardwire>	send + SNDMORE flag
| [Thursday 21 April 2011] [18:09:18] <lt_schmidt_jr>	yes
| [Thursday 21 April 2011] [18:09:21] <hardwire>	send_json w/o flag
| [Thursday 21 April 2011] [18:09:25] <hardwire>	and recv_multipart
| [Thursday 21 April 2011] [18:09:27] <lt_schmidt_jr>	correct
| [Thursday 21 April 2011] [18:09:39] <hardwire>	works for me.
| [Thursday 21 April 2011] [18:09:41] <lt_schmidt_jr>	I am also a specie
| [Thursday 21 April 2011] [18:09:42] <lt_schmidt_jr>	:)
| [Thursday 21 April 2011] [18:10:00] <hardwire>	I could do the json using the json module.. but I like the zmq module handing it for now :)
| [Thursday 21 April 2011] [18:10:30] <else->	do you guys know whether there are prebuilt debian packages for libzmq and libzapi somewhere?
| [Thursday 21 April 2011] [18:10:50] <lt_schmidt_jr>	not me
| [Thursday 21 April 2011] [18:10:52] <hardwire>	I do
| [Thursday 21 April 2011] [18:11:01] <hardwire>	else-: which debian?
| [Thursday 21 April 2011] [18:11:04] <else->	squeeze
| [Thursday 21 April 2011] [18:11:12] <hardwire>	you can install the experimental packages directly.
| [Thursday 21 April 2011] [18:11:25] <hardwire>	I backported them from experimental
| [Thursday 21 April 2011] [18:11:26] <else->	i didn't find libzapi though
| [Thursday 21 April 2011] [18:11:37] <hardwire>	ah.. I'm not familiar with it.
| [Thursday 21 April 2011] [18:12:18] <else->	well i heard about 0mq just recently and would like to try out the examples, and as far as i've understood they use libzapi
| [Thursday 21 April 2011] [18:13:00] <hardwire>	else-: I don't see their existance.
| [Thursday 21 April 2011] [18:13:17] <hardwire>	are you familiar with building libzapi yourself?
| [Thursday 21 April 2011] [18:13:44] <else->	i tried, but it fails (see my msg at 09:20pm)
| [Thursday 21 April 2011] [18:14:32] <hardwire>	I wasn't here then.. dunno if I could help either
| [Thursday 21 April 2011] [18:14:38] <hardwire>	maybe.. however
| [Thursday 21 April 2011] [18:14:47] <hardwire>	do you have build-essentials installed?
| [Thursday 21 April 2011] [18:14:48] <else->	ok, wait
| [Thursday 21 April 2011] [18:14:50] <else->	yes
| [Thursday 21 April 2011] [18:15:04] <hardwire>	did you build libzmq from source?
| [Thursday 21 April 2011] [18:15:16] <else->	my libzapi git checkout fails during compilation of zsocket.c with "zsocket.c:116:28: error: ZMQ_XSUB undeclared"
| [Thursday 21 April 2011] [18:15:19] <else->	hardwire: yes
| [Thursday 21 April 2011] [18:15:28] <hardwire>	what was the make error?
| [Thursday 21 April 2011] [18:19:55] <else->	hardwire: http://piratepad.net/IbgeoMZWjv
| [Thursday 21 April 2011] [18:20:07] <else->	and configure completes without any errors
| [Thursday 21 April 2011] [18:20:56] <hardwire>	looks like your zmq build didn't install headers for some reason
| [Thursday 21 April 2011] [18:21:18] <hardwire>	or there is a version problem.. I'm not sure
| [Thursday 21 April 2011] [18:22:10] <else->	i have installed zmq 2.0.11
| [Thursday 21 April 2011] [18:22:50] <lt_schmidt_jr>	else-: you should avoid using 2.0 - many issues resovled in 2,1
| [Thursday 21 April 2011] [18:22:52] <lt_schmidt_jr>	2.1
| [Thursday 21 April 2011] [18:23:03] <else->	ok, i'll try that
| [Thursday 21 April 2011] [18:23:04] <else->	thanks
| [Thursday 21 April 2011] [18:24:22] <hardwire>	else-: I'm guessing zapi wants 2.1
| [Thursday 21 April 2011] [18:24:31] <else->	let's see :)
| [Thursday 21 April 2011] [18:25:46] <hardwire>	I'm integrating zmq with some django apps... right now I just need message queueing per django thread so this is gonna be spiffers.
| [Thursday 21 April 2011] [18:29:50] <else->	awesome, works now :) thanks guys
| [Thursday 21 April 2011] [18:30:04] <lt_schmidt_jr>	NP
| [Thursday 21 April 2011] [18:30:13] <lt_schmidt_jr>	the more the merrire
| [Thursday 21 April 2011] [18:30:16] <lt_schmidt_jr>	merrier
| [Thursday 21 April 2011] [20:37:47] <Toba>	hey, I'm getting an odd error trying to use zmq::poll from C++.  It claims I'm doing a socket operation on a non-socket, but I think that's not true at all.  Do I need to have a REQ client connected to the REP server before poll() is valid?
| [Thursday 21 April 2011] [20:41:09] <Toba>	perhaps it's socket options. *digs*
| [Thursday 21 April 2011] [20:56:49] <Toba>	oh well. that's a puzzle for tomorrow. anyone who knows what I speak of, please ping me :)
| [Thursday 21 April 2011] [20:56:53] 	 * Toba goes home
| [Friday 22 April 2011] [04:03:08] <pieterh>	Toba: typically, either you're passing another object (context?) by mistake, or you're polling on a closed socket
| [Friday 22 April 2011] [04:04:40] <wewqewq>	ok
| [Friday 22 April 2011] [04:04:51] <wewqewq>	pl
| [Friday 22 April 2011] [04:06:24] <pieterh>	else-: I've fixed libzapi to complain if you're using libzmq/2.0, there's too much missing in that version
| [Friday 22 April 2011] [04:39:22] <Guthur>	has anyone had issues using zeromq on windows server OS
| [Friday 22 April 2011] [04:43:51] <mikko>	that's a broad question
| [Friday 22 April 2011] [04:43:59] <mikko>	sustrik: are you there?
| [Friday 22 April 2011] [04:44:18] <sustrik>	hi
| [Friday 22 April 2011] [04:44:38] <mikko>	so, as you have serious trust issues with github?
| [Friday 22 April 2011] [04:44:41] <mikko>	:)
| [Friday 22 April 2011] [04:44:59] <sustrik>	dunno, they can go out of business in couple of years
| [Friday 22 April 2011] [04:45:03] <mikko>	maybe i could synchronise the issues on daily basis and take a dump
| [Friday 22 April 2011] [04:45:09] <sustrik>	and what we end up with is uncomprehensible change log
| [Friday 22 April 2011] [04:45:17] <mikko>	that way we would always have the data
| [Friday 22 April 2011] [04:45:25] <mikko>	their api allows pulling them out
| [Friday 22 April 2011] [04:45:28] <mikko>	http://develop.github.com/p/issues.html
| [Friday 22 April 2011] [04:45:56] <Guthur>	mikko: Well more wanting to know if it worked
| [Friday 22 April 2011] [04:45:58] <Guthur>	at all
| [Friday 22 April 2011] [04:46:01] <mikko>	that way github would need to go out of business and my backup in two locations would need to die
| [Friday 22 April 2011] [04:46:02] <sustrik>	yeah, but what's the point anyway?
| [Friday 22 April 2011] [04:46:13] <sustrik>	the changelog should be self-contained
| [Friday 22 April 2011] [04:46:17] <Guthur>	I having headaches trying to deploy an app to win server
| [Friday 22 April 2011] [04:46:22] <Guthur>	runs fine on XP
| [Friday 22 April 2011] [04:46:30] <mikko>	sustrik: being able to refer to issue numbers from changelog for more information
| [Friday 22 April 2011] [04:46:44] <mikko>	sustrik: there might be some background information in the issue 
| [Friday 22 April 2011] [04:46:48] <Guthur>	tried both win server 2003 and 2008, on both the app fails to find the dll
| [Friday 22 April 2011] [04:47:12] <Guthur>	but the same MSI works fine on win XP, doing my head in
| [Friday 22 April 2011] [04:47:16] <mikko>	you could comming with message "Fixed XYZ pushing to ABC. Fixes issue #12345"
| [Friday 22 April 2011] [04:47:25] <mikko>	and it automatically closes the issue
| [Friday 22 April 2011] [04:48:00] <sustrik>	mikko: i am not sure it would be useful for anybody, but if you are happy archiving the issues, i can refer to issue numbers in the changelog
| [Friday 22 April 2011] [04:49:11] <sustrik>	Guthur: have you check the dll is installed in the proper place?
| [Friday 22 April 2011] [04:50:15] <Guthur>	sustrik: yep it's in the execution directory, the MSI drops in the dll
| [Friday 22 April 2011] [04:51:31] <sustrik>	no idea then
| [Friday 22 April 2011] [04:51:40] 	 * sustrik doesn't have win server to test
| [Friday 22 April 2011] [04:53:08] <Guthur>	this is the first time I've tried win server as well
| [Friday 22 April 2011] [04:53:45] <Guthur>	I suppose I should really try a simple C app for as a sanity check
| [Friday 22 April 2011] [04:55:58] <sustrik>	presumably
| [Friday 22 April 2011] [04:56:11] <sustrik>	you can use perf tests from libzmq
| [Friday 22 April 2011] [05:12:20] <Guthur>	ah ha
| [Friday 22 April 2011] [05:12:32] <Guthur>	I think I may have found the issue
| [Friday 22 April 2011] [05:13:27] <Guthur>	msvcp.dll is not on the win server boxes
| [Friday 22 April 2011] [05:14:18] <Guthur>	or msvcr.dll
| [Friday 22 April 2011] [05:15:11] <Guthur>	probably due to visual studio c runtime stuff not being installed
| [Friday 22 April 2011] [05:15:20] <Guthur>	c++*
| [Friday 22 April 2011] [05:15:51] <Guthur>	these are not development boxes
| [Friday 22 April 2011] [05:16:29] <mikko>	use dependency walker
| [Friday 22 April 2011] [05:31:18] <Guthur>	ah success it was indeed the msvc dependency
| [Friday 22 April 2011] [05:31:43] <Guthur>	this only became apparent when running the C example code 
| [Friday 22 April 2011] [05:34:04] <sustrik>	doesn't msi check for dependencies?
| [Friday 22 April 2011] [05:39:07] <Guthur>	You can probably build an MSI to do such
| [Friday 22 April 2011] [05:39:13] <Guthur>	I just made a simple one
| [Friday 22 April 2011] [05:40:01] <Guthur>	If only this error message was more informative when running the original app
| [Friday 22 April 2011] [05:40:43] <Guthur>	the original app said it could not find libzmq.dll, but the real issue was the msvc dlls
| [Friday 22 April 2011] [06:00:54] <Guthur>	just noticed that intel have opened up a parallel computing competition http://software.intel.com/en-us/blogs/2011/04/18/and-theyre-off-intel-threading-challenge-2011-started-today-bigger-prizes-this-year/
| [Friday 22 April 2011] [06:01:11] <Guthur>	maybe a zmq app could fit the problem domains
| [Friday 22 April 2011] [06:01:28] <Guthur>	not sure if the rules might exclude it's use though
| [Friday 22 April 2011] [11:57:36] <else->	pieterh: cool. probably a good idea, thanks!
| [Friday 22 April 2011] [12:40:25] <hardwire>	hmm.. anybody found a good way to zeromq ala inetd?
| [Friday 22 April 2011] [13:06:35] <mikko>	hardwire: what do you mean?
| [Friday 22 April 2011] [13:06:42] <mikko>	i didnt know anyone uses inetd nowadays
| [Friday 22 April 2011] [13:12:10] <hardwire>	mikko: :)
| [Friday 22 April 2011] [13:12:39] <hardwire>	it's a pretty quick and dirty process distribution system :)
| [Friday 22 April 2011] [19:21:03] <Graaf>	Hi
| [Friday 22 April 2011] [19:22:37] <Graaf>	I'm trying to install zeromq on a windows system, and install the php bindings. but i'm having trouble to get those php bindings loaded.. .dll file is not reccognized or gives error while loading..
| [Friday 22 April 2011] [20:19:28] <ParadoxG>	Hi, is ZMQ_DELIMITER normally used as a char, or is it an int?
| [Saturday 23 April 2011] [02:52:07] <rukubites>	How would I go about cross-compiling a 32 bit (linux) version of zeromq on 64 bit linux?
| [Saturday 23 April 2011] [02:53:01] <rukubites>	The purpose is to interface with wine, to provide zeromq communication to an application run via wine.
| [Saturday 23 April 2011] [02:53:37] <guido_g>	why?
| [Saturday 23 April 2011] [02:54:00] <guido_g>	there is .net binding for the windows side
| [Saturday 23 April 2011] [02:54:10] <guido_g>	just use the local network interface
| [Saturday 23 April 2011] [02:55:37] <rukubites>	Well I am very unfamiliar with windows coding, and I don't know how to hook into .net from the target application - which has its own language.
| [Saturday 23 April 2011] [02:55:49] <rukubites>	Essentially because this route taps into my knowledge base much easier.
| [Saturday 23 April 2011] [02:56:11] <rukubites>	The target 'platform' is mt4, a trading platform.
| [Saturday 23 April 2011] [02:56:40] <guido_g>	how would a 32 linux version help then?
| [Saturday 23 April 2011] [02:56:45] <guido_g>	*32-bit
| [Saturday 23 April 2011] [02:57:01] <rukubites>	Because wine requires an m32.
| [Saturday 23 April 2011] [02:57:11] <guido_g>	and then?
| [Saturday 23 April 2011] [02:57:21] <rukubites>	And so I can't link to 64bit libzmq.
| [Saturday 23 April 2011] [02:57:30] <guido_g>	and?
| [Saturday 23 April 2011] [02:57:34] <guido_g>	the app is still not useing it
| [Saturday 23 April 2011] [02:58:21] <rukubites>	I have a bit of glue code between zeromq and the target app I am trying to build. There are instructions for wine, but it is failing on libzmq because I only have 64 bit libzmq as I am on 64 bit machine.
| [Saturday 23 April 2011] [02:59:02] <guido_g>	this sounds very strange and fragile
| [Saturday 23 April 2011] [02:59:33] <rukubites>	You are right, it is exotic. The target platform mt4 is known to make it very hard to communicate.
| [Saturday 23 April 2011] [03:00:38] <rukubites>	I want to run on wine because having a virtual machine or dedicated box for one application is expensive in RAM, CPU and/or monetary cost.
| [Saturday 23 April 2011] [03:01:32] <guido_g>	not as expensive as the time for development and maintenace
| [Saturday 23 April 2011] [03:01:52] <guido_g>	and better hope speed is not an issue
| [Saturday 23 April 2011] [03:02:10] <guido_g>	but i can't help you w/ the cross compiling thing
| [Saturday 23 April 2011] [03:02:12] <rukubites>	Speed really isn't the issue. It is a pretty simple end-point.
| [Saturday 23 April 2011] [03:02:24] <guido_g>	try a place where compiler geeks are
| [Saturday 23 April 2011] [03:02:34] <rukubites>	e.g.?
| [Saturday 23 April 2011] [03:02:59] <guido_g>	no clue, i don't do such things ,)
| [Saturday 23 April 2011] [03:03:26] <rukubites>	Fair enough. Thanks for your time, anyway. :-)
| [Saturday 23 April 2011] [03:04:12] <guido_g>	you might want to stay here and wait for mikko, is the build guy and might know a bit
| [Saturday 23 April 2011] [03:05:02] <rukubites>	Okay I will lurk. And hopefully your message pinged him. :D
| [Saturday 23 April 2011] [03:08:21] <pieterh>	rukubites: hi
| [Saturday 23 April 2011] [03:09:23] <rukubites>	Hi pieterh.
| [Saturday 23 April 2011] [03:09:37] <pieterh>	so, gcc lets you builds 32-bit on a 64-bit box
| [Saturday 23 April 2011] [03:09:47] <pieterh>	pass -m32 option
| [Saturday 23 April 2011] [03:10:18] <pieterh>	then, 'configure --help' to see what to do next
| [Saturday 23 April 2011] [03:10:32] <pieterh>	set CFLAGS=-m32 
| [Saturday 23 April 2011] [03:10:44] <pieterh>	./configure and make, and it should have worked
| [Saturday 23 April 2011] [03:11:40] <rukubites>	I will try that next. I did a make just as normal because I need the 64-bit version for normal use. :-)
| [Saturday 23 April 2011] [03:11:59] <rukubites>	Figured I would remove the ubuntu ppa version and compile it myself.
| [Saturday 23 April 2011] [03:12:11] <pieterh>	sure, easy enough
| [Saturday 23 April 2011] [03:15:16] <rukubites>	My first try I will do --build=i686-pc-linux-gnu
| [Saturday 23 April 2011] [03:34:37] <rukubites>	I got through compilation by just compiling on a spare 32 bit instance I had around. I probably should have just downloaded the appropriate daily build from http://build.zero.mq/
| [Saturday 23 April 2011] [03:37:35] <rukubites>	Using CFLAGS=-m32 did not work, I am sure mikko the build guy would know what I should have done. But that step seems solved, thank you for the help pieterh and guido_g.
| [Saturday 23 April 2011] [05:16:55] <justinuza>	Hey all.  I have a problem that I'm trying to solve, and I feel like zeromq can do it, but I just keep reading docs and examples and whatever else I can find and can't seem to visualize how it would work - and what sockets I would need.  If anyone could provide some insight, I would greatly appreciate it...
| [Saturday 23 April 2011] [05:17:08] <justinuza>	I would like to have a Job Manager that producers can submit jobs to, and then the producer should get a response when the job is complete.  The jobs should be picked up by consumers (1 job --> 1 consumer) where the consumer processes the job, returns the result to the Job Manager, which then returns the result to the producer.  For instance, lets say there are 4 types of tasks: Add, Subtract, Multiply, and Divide.  The Job Manager sho
| [Saturday 23 April 2011] [05:17:08] <justinuza>	I'm more interested in the Job Manager <--> Worker communication than the Producer <--> Job Manager.  However, one caveat is that there should be able to be N types of tasks, and potentially new tasks added on the fly.
| [Saturday 23 April 2011] [05:17:08] <justinuza>	Is something like what I'm describing possible to accomplish with zeromq?
| [Saturday 23 April 2011] [05:18:12] <sustrik>	use REQ/REP with an interdediary device
| [Saturday 23 April 2011] [05:19:33] <justinuza>	an intermediary device?  that being the "job manager"?
| [Saturday 23 April 2011] [05:27:33] <justinuza>	does that mean i would need to maintain a worker pool for each task type?  when a 'multiply' job comes in, go to the 'multiply' pool and choose a REQ socket that isn't currently waiting for a REP from a worker, and send the job along?
| [Saturday 23 April 2011] [05:28:06] <sustrik>	depends on who processes different job types
| [Saturday 23 April 2011] [05:28:14] <sustrik>	same application doing all job types?
| [Saturday 23 April 2011] [05:28:22] <sustrik>	or different applications doing different jobs?
| [Saturday 23 April 2011] [05:28:38] <justinuza>	different applications doing different jobs
| [Saturday 23 April 2011] [05:28:58] <sustrik>	then i would suggest using a different topology for each job type
| [Saturday 23 April 2011] [05:29:41] <sustrik>	that way you have different functions clearly separated and manageable without affecting other functions in any way
| [Saturday 23 April 2011] [05:31:37] <justinuza>	right, from my example lets say i have 4 python scripts: add.py, subtract.py, multiply.py, and divide.py.  each worker would be an instance of one of the scripts running on a box (separate processes), but i want to route to all of them from a single job manager
| [Saturday 23 April 2011] [05:33:08] <sustrik>	ok, you then need 4 XREX and XREP sockets in the job manager
| [Saturday 23 April 2011] [05:33:15] <sustrik>	poll on all of them
| [Saturday 23 April 2011] [05:33:25] <sustrik>	pass messages to the corresponsing socket
| [Saturday 23 April 2011] [05:33:28] <sustrik>	that's it
| [Saturday 23 April 2011] [05:34:35] <justinuza>	XREQ sockets in the job manager and XREP sockets in the workers?  or vice versa?
| [Saturday 23 April 2011] [05:34:41] <guido_g>	justinuza: http://zguide.zeromq.org/page:all#Service-Oriented-Reliable-Queuing-Majordomo-Pattern
| [Saturday 23 April 2011] [05:35:23] <guido_g>	lots of questions are answered in The Guide
| [Saturday 23 April 2011] [05:35:30] <sustrik>	guido_g: thanks
| [Saturday 23 April 2011] [05:36:17] <justinuza>	Thanks guido_g.  I tried to read through it, but its a little bit gigantic :)
| [Saturday 23 April 2011] [05:36:23] <guido_g>	sustrik: np, just a hot-key :)
| [Saturday 23 April 2011] [05:37:19] <guido_g>	justinuza: what shall i say? i this this to much to read, how will you learn the principals of MQ and brokerless messaging in generall?
| [Saturday 23 April 2011] [05:39:17] <justinuza>	guido:  I certainly don't disagree... I hope that I do have enough time to get through all of it, and I thank you for your help.
| [Saturday 23 April 2011] [06:58:28] <jsimmons>	Anybody worked on a D binding for zmq?
| [Saturday 23 April 2011] [06:59:18] <guido_g>	http://www.zeromq.org/bindings:d
| [Saturday 23 April 2011] [07:00:27] <jsimmons>	oh that's not a full list I see
| [Saturday 23 April 2011] [07:16:04] <pieter_hintjens>	jsimmons: I
| [Saturday 23 April 2011] [07:16:09] <pieter_hintjens>	I've added D to the main page
| [Saturday 23 April 2011] [07:16:16] <jsimmons>	:D
| [Saturday 23 April 2011] [07:16:30] <pieter_hintjens>	it's not always clear which bindings are actively maintained & used
| [Saturday 23 April 2011] [07:18:11] <th>	so zmq_recv and zmq_send will be more POSIX in 3.0, how is that supposed to be regarding multiparts? will a recv go over part-boundaries?
| [Saturday 23 April 2011] [07:18:28] <th>	or is it like EOF for every part?
| [Saturday 23 April 2011] [07:22:11] <headzone>	what makes you think multipart handling would change
| [Saturday 23 April 2011] [07:22:24] <th>	i dont
| [Saturday 23 April 2011] [07:22:48] <th>	i had a look at the 3.0 roadmap
| [Saturday 23 April 2011] [07:23:22] <th>	which is talking about making the 2 functions more coherent with POSIX send/recv
| [Saturday 23 April 2011] [07:23:45] <headzone>	...by renaming them
| [Saturday 23 April 2011] [07:24:07] <th>	the current ones will become sendmsg and recvmsg, as i read it
| [Saturday 23 April 2011] [07:24:43] <th>	later on in the roadmap there is some code showing those zmq_recv/zmq_send functions
| [Saturday 23 April 2011] [07:25:11] <th>	my interpretation was that current functions become "msg" suffixed and zmq_recv/zmq_send will behave more like POSIX send/recv
| [Saturday 23 April 2011] [07:25:27] <th>	thus resulting in 2 sets of the two functions
| [Saturday 23 April 2011] [07:25:35] <th>	am i wrong?
| [Saturday 23 April 2011] [07:26:29] <th>	i'm referring to "Proposal for send/recv API based on POSIX socket API:"
| [Saturday 23 April 2011] [07:26:43] <th>	at http://www.zeromq.org/docs:3-0
| [Saturday 23 April 2011] [08:00:37] <sustrik>	th: you are right
| [Saturday 23 April 2011] [08:00:54] <sustrik>	the multipart will work in standard way
| [Saturday 23 April 2011] [08:01:19] <sustrik>	actually, it already works in stadard way
| [Saturday 23 April 2011] [08:01:35] <sustrik>	to check the new api give a try to libzmq master
| [Saturday 23 April 2011] [08:10:50] <th>	sustrik: and with standard way you mean using the zmq_recvmsg?
| [Saturday 23 April 2011] [08:16:11] <sustrik>	i mean using ZMQ_SNDMORE and ZMQ_RCVMORE
| [Saturday 23 April 2011] [08:16:43] <sustrik>	it works with zmq_send, zmq_sendmsg, zmq_recv and zmq_recvmsg
| [Saturday 23 April 2011] [23:52:28] <siggimoo>	anyone ever have any trouble with zeromq inside of a mod_wsgi script?
| [Sunday 24 April 2011] [14:16:18] <andrewvc>	cremes: around?
| [Sunday 24 April 2011] [17:10:07] <nodie>	hi
| [Sunday 24 April 2011] [17:10:32] <nodie>	I suppose I can extract that information by reading the sources, but it's sunday and nearly time to go to bed
| [Sunday 24 April 2011] [17:10:47] <nodie>	when I configure a socket with SUBSCRIBE
| [Sunday 24 April 2011] [17:11:14] <nodie>	does the filtering occur at client level or at server level in a PUB/SUB connection?
| [Sunday 24 April 2011] [17:21:35] <Guthur>	nodie, client
| [Sunday 24 April 2011] [17:22:05] <Guthur>	server side subscription is a oft requested feature and may appear in the futur
| [Sunday 24 April 2011] [17:22:08] <Guthur>	future*
| [Sunday 24 April 2011] [18:10:46] <nodie>	thank you Guthur  
| [Sunday 24 April 2011] [18:43:13] <andrewvc>	hi guys, I've got this bug where I get a 'resource temporarily unavailable' error message when trying to send a message on xreq over TCP to a non-existant socket
| [Sunday 24 April 2011] [18:43:19] <andrewvc>	if I start up the listening xrep first
| [Sunday 24 April 2011] [18:43:21] <andrewvc>	no issues
| [Sunday 24 April 2011] [18:43:30] <andrewvc>	this only happens if I send a delimiter string
| [Sunday 24 April 2011] [18:47:48] <andrewvc>	so, it appears to happen only when I bind with the xreq
| [Sunday 24 April 2011] [20:49:23] <phantomcircuit_>	hello, so reading the documentation it strikes me that the pull/push mechanism results in pull sockets having local queueing
| [Sunday 24 April 2011] [20:49:54] <phantomcircuit_>	that seems like an odd decision
| [Sunday 24 April 2011] [21:35:57] <dublisk>	Hi, zeromq will only work with itself right? I can't use it to read from sockets that aren't zeromq on the other end?
| [Sunday 24 April 2011] [21:50:24] <taotetek>	dublisk: correct
| [Sunday 24 April 2011] [21:50:38] <dublisk>	D'oh
| [Sunday 24 April 2011] [21:50:52] <taotetek>	dublisk: you can of course write something to translate from a tcp socket to zeromq
| [Sunday 24 April 2011] [21:51:09] <taotetek>	dublisk: but yeah, you can't connect a zeromq socket and standard socket together without some glue in the middle.
| [Sunday 24 April 2011] [21:52:11] <dublisk>	I was hoping I could just receive messages which would be of whatever length it captured
| [Sunday 24 April 2011] [21:56:09] <taotetek>	dublisk: I do quite a bit of zeromq work with python - when I need to move data between a standard tcp connection and zeromq I usually write a little connecting piece w/ python and eventlet, works pretty well
| [Sunday 24 April 2011] [21:56:17] <taotetek>	dublisk: don't know what languages you're working with though
| [Sunday 24 April 2011] [21:56:31] <dublisk>	C++, but how do you listen to the socket?
| [Sunday 24 April 2011] [21:57:24] <taotetek>	dublisk: I open a tcp port, anything that connects to that port and sends gets forwarded out a zeromq socket (breaking messages apart on \n)
| [Sunday 24 April 2011] [22:05:18] <taotetek>	dublisk: it's worked as a decent stopgap while I wait for people above stream from me in our stack to convert over to zeromq
| [Monday 25 April 2011] [00:37:00] <Taaz_>	hii iam new to it...i would love to contribute..how do i ??
| [Monday 25 April 2011] [11:55:48] <phantomcircuit>	is there a binary build available for windows
| [Monday 25 April 2011] [11:55:49] <phantomcircuit>	?
| [Monday 25 April 2011] [11:56:33] <Guthur>	phantomcircuit, not to my knowledge, but it's pretty trivial to build
| [Monday 25 April 2011] [11:56:54] <Guthur>	should be buildable with the express edition
| [Monday 25 April 2011] [11:57:13] <phantomcircuit>	yeah i've gotten it built
| [Monday 25 April 2011] [11:57:31] <phantomcircuit>	i cant get this to work it'll just take some doing
| [Monday 25 April 2011] [11:57:48] <Guthur>	what is the issue/
| [Monday 25 April 2011] [11:57:49] <Guthur>	?
| [Monday 25 April 2011] [11:59:06] <phantomcircuit>	setup.py is trying to build a test program and is failing because it cant find a compiler
| [Monday 25 April 2011] [11:59:13] <jhawk28>	phantomcircuit: they ship a windows binard as part of the pyzmq
| [Monday 25 April 2011] [11:59:47] <jhawk28>	download the msi from https://github.com/zeromq/pyzmq/downloads
| [Monday 25 April 2011] [12:00:19] <phantomcircuit>	im gonna need to build php bindings also
| [Monday 25 April 2011] [12:00:35] <jhawk28>	If you want to compile it yourself, download the Visual Studio 2008 Express
| [Monday 25 April 2011] [12:01:47] <jhawk28>	http://www.microsoft.com/express/Downloads/#2008-Visual-CPP
| [Monday 25 April 2011] [12:02:01] <phantomcircuit>	yeah i've got that and i've actually built libzmq.lib
| [Monday 25 April 2011] [12:02:02] <jhawk28>	You can use 2010 too, but all the projects are already set up for 2008
| [Monday 25 April 2011] [12:03:22] <jhawk28>	when you distribute your libraries out to the servers, you need to make sure you have the VC++ redistributables that match your compiler environment
| [Monday 25 April 2011] [12:03:49] <jhawk28>	kinda like http://www.microsoft.com/downloads/en/details.aspx?FamilyID=9b2da534-3e03-4391-8a4d-074b9f2bc1bf&displaylang=en
| [Monday 25 April 2011] [12:04:03] <jhawk28>	there are about 3 or 4 version out there
| [Monday 25 April 2011] [12:04:56] <phantomcircuit>	jhawk28, basically this is just a proof of concept, if this works i will not continue using windows servers
| [Monday 25 April 2011] [12:05:06] <phantomcircuit>	this one just happens to be free
| [Monday 25 April 2011] [12:06:45] <Guthur>	I did have a minor issue build the .lib file with 2010
| [Monday 25 April 2011] [12:06:52] <Guthur>	the .dll was fine though
| [Monday 25 April 2011] [12:07:03] <Guthur>	there is a website somewhere detailing the issue, 2 secs
| [Monday 25 April 2011] [12:07:28] <phantomcircuit>	well both are built
| [Monday 25 April 2011] [12:07:43] <Guthur>	http://www.mansysadmin.com/2011/03/using-zeromq-framework-with-visual-studio-2010-tutorial/
| [Monday 25 April 2011] [12:07:51] <phantomcircuit>	ah well im missing the python headers
| [Monday 25 April 2011] [12:07:51] <Guthur>	possibly only a 2010 issue
| [Monday 25 April 2011] [12:09:09] <phantomcircuit>	lol visual studio is so slow
| [Monday 25 April 2011] [12:09:13] <phantomcircuit>	it's like a bad joke
| [Monday 25 April 2011] [12:09:55] <Guthur>	it gets even funnier when you start to ask what do you get for the slowness
| [Monday 25 April 2011] [12:11:38] <phantomcircuit>	code completion 
| [Monday 25 April 2011] [12:11:39] <phantomcircuit>	and uh
| [Monday 25 April 2011] [12:11:41] <phantomcircuit>	yeah that's it
| [Monday 25 April 2011] [12:12:36] <jhawk28>	even the code completion, people get resharper...
| [Monday 25 April 2011] [12:13:15] <Guthur>	yep, it's code completion pretty naff
| [Monday 25 April 2011] [12:18:32] <phantomcircuit>	hmm ok so now how do i get php bindings
| [Monday 25 April 2011] [12:30:35] <phantomcircuit>	hmm getting a php extension built is proving to be a challenge
| [Monday 25 April 2011] [12:34:26] <phantomcircuit>	i take it that nobody cares
| [Monday 25 April 2011] [12:35:39] <Guthur>	well now that you ask... I've never cared much for PHP
| [Monday 25 April 2011] [12:37:02] <phantomcircuit>	i've got a giant application written in php, currently a long running computationally expensive part of it is run in the context of the web server with a bunch of hilarious hacks
| [Monday 25 April 2011] [12:37:44] <Guthur>	there is a few PHPers about here on occasion
| [Monday 25 April 2011] [12:38:00] <phantomcircuit>	i cant really rewrite the entire platform but i can use zmq to send the work requests to python daemons
| [Monday 25 April 2011] [12:39:20] <Guthur>	phantomcircuit, you could try the mailing list
| [Monday 25 April 2011] [12:39:45] <Guthur>	i know Ian Barber is a heavy PHP user but isn't online at the moment
| [Monday 25 April 2011] [12:39:53] <Guthur>	you might catch him on the ML
| [Monday 25 April 2011] [12:41:38] <phantomcircuit>	k thanks
| [Monday 25 April 2011] [13:31:36] <mikko>	phantomcircuit: what is the problem with php extension?
| [Monday 25 April 2011] [13:32:32] <phantomcircuit>	i have no idea how to build it on windows
| [Monday 25 April 2011] [13:32:40] <phantomcircuit>	and i dont see a prebuilt version
| [Monday 25 April 2011] [13:33:14] <mikko>	have you built any other php extensions on windows?
| [Monday 25 April 2011] [13:33:27] <phantomcircuit>	nope
| [Monday 25 April 2011] [13:34:37] <mikko>	so i take it that you don't have php development env setup?
| [Monday 25 April 2011] [13:34:58] <mikko>	https://wiki.php.net/internals/windows/stepbystepbuild
| [Monday 25 April 2011] [13:36:58] <phantomcircuit>	mikko, even if i did i dont see any build instructions for zmq specifically
| [Monday 25 April 2011] [13:37:35] <mikko>	you would build it just like any other pecl extension
| [Monday 25 April 2011] [13:42:52] <cremes>	anyone working on getting 0mq to build on windows using mingw?
| [Monday 25 April 2011] [13:45:02] <mikko>	cremes: it should build
| [Monday 25 April 2011] [13:45:28] <cremes>	mikko: i'll give it a try today and report any errors i see
| [Monday 25 April 2011] [13:46:28] <mikko>	cremes: there is daily build on win7 using mingw32
| [Monday 25 April 2011] [13:47:17] <cremes>	oh, excellent
| [Monday 25 April 2011] [13:47:29] <mikko>	the windows build machine is a bit out of order atm though
| [Monday 25 April 2011] [13:47:38] <mikko>	but overall mingw32 should build without problems
| [Monday 25 April 2011] [13:47:43] <mikko>	pgm wont build
| [Monday 25 April 2011] [13:47:46] <mikko>	openpgm*
| [Monday 25 April 2011] [13:48:00] <cremes>	ok; i don't need pgm so that isn't a show stopper for me
| [Monday 25 April 2011] [13:49:55] <mikko>	phantomcircuit: seems like my build environment still works for win
| [Monday 25 April 2011] [13:50:06] <mikko>	might be able to get a build done 
| [Monday 25 April 2011] [13:52:23] <mikko>	phantomcircuit: http://valokuva.org/builds/ext/vc9/nts/zmq/2011-04-25_1849/php_zmq_nts.dll / http://valokuva.org/builds/ext/vc9/ts/zmq/2011-04-25_1849/php_zmq_ts.dll
| [Monday 25 April 2011] [15:43:00] <jhawk28>	any iMatix people on?
| [Monday 25 April 2011] [15:45:22] <jhawk28>	pieterh
| [Monday 25 April 2011] [15:45:31] <jhawk28>	pieterh: are you there?
| [Monday 25 April 2011] [15:50:22] <jhawk28>	mato: you there?
| [Monday 25 April 2011] [15:53:32] <cremes>	jhawk28: if you have a general question about 0mq, go ahead and ask it
| [Monday 25 April 2011] [15:53:40] <cremes>	there are a bunch of knowledgeable folks in the channel
| [Monday 25 April 2011] [15:53:54] <jhawk28>	cremes: its releated to the OpenAMQ JMS client
| [Monday 25 April 2011] [15:54:16] <cremes>	ask anyway; maybe a lurker has an answer for you
| [Monday 25 April 2011] [15:58:36] <jhawk28>	my management has "dictated" that we must use JMS
| [Monday 25 April 2011] [15:59:26] <jhawk28>	based on my research, it looks like the qpid amqp driver does not interoperate with RabbitMQ based on a "disagreement" in the spec
| [Monday 25 April 2011] [15:59:39] <jhawk28>	the other option is the openamq-jms
| [Monday 25 April 2011] [16:00:29] <jhawk28>	LShift looks to have got it running based on http://www.lshift.net/blog/2009/03/16/openamqs-jms-client-with-rabbitmq-server
| [Monday 25 April 2011] [16:01:18] <jhawk28>	no more chatter can be seen on the subject
| [Monday 25 April 2011] [16:01:37] <jhawk28>	no more commits have been made to the project: https://github.com/imatix/openamq-jms
| [Monday 25 April 2011] [16:01:55] <jhawk28>	is it dead or just so stable it hasn't needed updates?
| [Monday 25 April 2011] [16:03:14] <mato>	jhawk28: yes?
| [Monday 25 April 2011] [16:03:50] <mato>	jhawk28: ah, openamq-jms
| [Monday 25 April 2011] [16:04:01] <mato>	jhawk28: it's basically dead 
| [Monday 25 April 2011] [16:05:58] <jhawk28>	I hate enterprise products
| [Monday 25 April 2011] [16:06:44] <mato>	:-)
| [Monday 25 April 2011] [16:06:54] <jhawk28>	JMS is so verbose
| [Monday 25 April 2011] [16:07:16] <jhawk28>	but yet doen't really have good error messages on what actually went wrong
| [Monday 25 April 2011] [16:10:13] <mato>	convince your management to use zeromq :-)
| [Monday 25 April 2011] [16:11:00] <jhawk28>	we are
| [Monday 25 April 2011] [16:11:13] <jhawk28>	need a durable queue for some more enterprisey things
| [Monday 25 April 2011] [16:11:39] <jhawk28>	slower peformance, etc
| [Monday 25 April 2011] [16:12:14] <jhawk28>	of course, I'm getting to the point where the JNA is biting us
| [Monday 25 April 2011] [16:12:42] <mato>	well, you could always roll your own on top of 0mq
| [Monday 25 April 2011] [16:12:57] <jhawk28>	thought about it
| [Monday 25 April 2011] [16:13:27] <jhawk28>	thinking I'll pursue writing a Java impl of 0mq first so that it can run in the "Enterprise Containers"
| [Monday 25 April 2011] [16:15:33] <jhawk28>	I'm sure that it will be a pain since it doesn't look like the wire format is documented well
| [Monday 25 April 2011] [16:15:57] <jhawk28>	but, it would be really nice to just have a Java library
| [Monday 25 April 2011] [16:20:53] <mato>	jhawk28: is there a particular reason why you can't just use the 0mq Java API?
| [Monday 25 April 2011] [16:21:48] <mato>	jhawk28: you really really don't want to go writing your own implementation, the 0mq protocols (especially the underlying semantics) are still too raw and unstable 
| [Monday 25 April 2011] [16:23:21] <jhawk28>	mato: in many things, the 0mq Java API is fine. Once you try using it in crappy enterprise products like JBoss, the Threading model conflicts and things like EJB's forbid using JNA
| [Monday 25 April 2011] [16:23:40] <mato>	jhawk28: JNA? you mean JNI?
| [Monday 25 April 2011] [16:23:51] <jhawk28>	oops, yes, JNI
| [Monday 25 April 2011] [16:24:29] <mato>	jhawk28: is there anything that can be done on the jzmq side of things to help use in your conditions?
| [Monday 25 April 2011] [16:26:05] <jhawk28>	2 approaches that I can think to fix the issue - write a remoting wrapper so the JNI can live outside the container, write a native Java impl of 0mq so that it can live inside the container
| [Monday 25 April 2011] [16:26:58] <mato>	i would recommend the former if it's not too hard
| [Monday 25 April 2011] [16:27:16] <jhawk28>	that would be my quick and dirty first pass
| [Monday 25 April 2011] [16:27:26] <jhawk28>	since it wouldnt take too long to get up and running
| [Monday 25 April 2011] [16:28:42] <jhawk28>	I know there are some developments on the 0mq side that may fix the issue too like adding it to the posix spec
| [Monday 25 April 2011] [16:29:07] <mato>	jhawk28: well, yes, a kernel-mode implementation of 0mq would make your problem go away
| [Monday 25 April 2011] [16:29:15] <mato>	jhawk28: but that is still a long way away
| [Monday 25 April 2011] [16:29:53] <jhawk28>	agreed, these things take time
| [Monday 25 April 2011] [21:49:44] <hhummel>	I just wandered in.  I'm having trouble installing zeromq on fedora.  Is there a particular directory I should unpack into so that the linker can find the libraries?
| [Monday 25 April 2011] [22:16:10] <hhummel>	I'm having trouble linking a simple c++ "hello world" app.  I know I'm supposed to be linking to .lib files, but I don't see them.  Can anyone help?  I'm using C++ on Fedora 13.
| [Monday 25 April 2011] [23:41:17] <Dantman>	Anyone got tips for solving an UnsatisfiedLinkError for the jzmq library... even though everything seams to be in order...
| [Monday 25 April 2011] [23:42:41] <Dantman>	java.library.path is /usr/local/lib, double checked that... That dir contains libjzmq.{a,la,so,so.0,so.0.0.0}, libzmq.{a,la,so,so.1,so.1.0.0}
| [Monday 25 April 2011] [23:50:55] <Dantman>	Anyone compiled jzmq on 64bit linux?
| [Tuesday 26 April 2011] [00:51:43] <phantomcircuit>	Dantman, i've been trying to build php-zmq pretty much all day
| [Tuesday 26 April 2011] [03:28:34] <djc>	pieterh: is there a reason 2.1.5.1 isn't out yet?
| [Tuesday 26 April 2011] [04:47:02] <drbobbeaty>	pieterh: any news on the revised 2.1.5.1 (2.1.6?) release? With all the nice fixes I've seen in the mailing list, it'd be nice to see them in a 2.1.x release. Along with the other fixes, of course. Just curious if you had an estimate yet.
| [Tuesday 26 April 2011] [07:55:41] <pieterh>	re
| [Tuesday 26 April 2011] [07:56:00] <pieterh>	djc: no reason except it was lovely weather and holidays
| [Tuesday 26 April 2011] [07:56:11] <pieterh>	... will make the 2.1.5.1 release later today
| [Tuesday 26 April 2011] [07:57:11] <pieterh>	drbobbeaty: I've one patch to apply, but that will mean delaying the 2.1.5.1 release by a day or two
| [Tuesday 26 April 2011] [07:57:45] <drbobbeaty>	pieterh: thanks for letting me know. Very much appreciated.
| [Tuesday 26 April 2011] [08:41:57] <mato>	pieterh: why the extra .1 ?
| [Tuesday 26 April 2011] [09:05:34] <toni>	hi there. I m using pyzmq. Theres a method socket.send_pyobj(obj) which serializes the object and a socket.recv_pyobj(). Is there also something like socket.send_pyobj_multipart when explicit addressing is required? or does sending/receiving of objects only target on socket which do not use envelopes?
| [Tuesday 26 April 2011] [09:06:26] <guido_g>	simple message, no routing, no multipart
| [Tuesday 26 April 2011] [09:07:11] <mato>	send_pyobj() is simple code though, so you could always reimplement it yourself if you want to do multipart
| [Tuesday 26 April 2011] [09:08:33] <toni>	ok, thanks... 
| [Tuesday 26 April 2011] [09:10:18] <toni>	mato: do you know where the code for send_pyobj lives?
| [Tuesday 26 April 2011] [09:11:33] <mato>	toni: hang on, they've moved things around since i last looked
| [Tuesday 26 April 2011] [09:11:47] <guido_g>	https://github.com/zeromq/pyzmq/blob/master/zmq/core/socket.pyx
| [Tuesday 26 April 2011] [09:11:56] <toni>	thanks!
| [Tuesday 26 April 2011] [09:12:11] <mato>	that's the one...
| [Tuesday 26 April 2011] [09:26:05] <pieterh>	mato: hi
| [Tuesday 26 April 2011] [09:26:21] <pieterh>	you missed something that passes for excitement in this little community
| [Tuesday 26 April 2011] [09:30:36] <pieterh>	http://lists.zeromq.org/pipermail/zeromq-dev/2011-April/010638.html
| [Tuesday 26 April 2011] [09:31:05] <pieterh>	if you have a better suggestion than sticking an extra '.1' at the end, let me know asap
| [Tuesday 26 April 2011] [09:31:30] <pieterh>	this was kind of the consensus solution here on IRC
| [Tuesday 26 April 2011] [09:32:54] <pieterh>	mato: ping
| [Tuesday 26 April 2011] [09:42:18] <hhummel>	Hi folks.  Thanks for making this terrific product!  I know this is a newbie question, but I can't figure it out.  I'm trying to get started building a stripped down app, and am getting errors that indicate that I'm not linking in the library.  How do I do that using g++ on Fedora?  I'm trying:  [harry@mars zeromq]$ g++ -Wall -L /usr/include/zeromq-2.1.4/src/.libs client2.cpp  but it doesn't help.  Can anyone help?
| [Tuesday 26 April 2011] [09:43:47] <NikolaVeber>	have you tried -lzmq ?
| [Tuesday 26 April 2011] [09:45:07] <hhummel>	Wow, that worked!  What is -lzmq?
| [Tuesday 26 April 2011] [09:45:55] <NikolaVeber>	parameter telling g++ to use the 0mq library installed systemwide
| [Tuesday 26 April 2011] [09:46:25] <NikolaVeber>	you can probably remove the -L part completely
| [Tuesday 26 April 2011] [09:46:38] <NikolaVeber>	gcc -lzmq source.cpp
| [Tuesday 26 April 2011] [09:48:00] <hhummel>	That does the trick, thanks.  I assume -lzmp is somehow introduced as part of the build process?
| [Tuesday 26 April 2011] [09:49:09] <NikolaVeber>	it links to the installed zmq libraries
| [Tuesday 26 April 2011] [09:49:27] <hhummel>	I really appreciate the hand.  Thanks!
| [Tuesday 26 April 2011] [09:50:54] <NikolaVeber>	np :)
| [Tuesday 26 April 2011] [10:11:24] <mato>	pieterh: yes?
| [Tuesday 26 April 2011] [10:11:41] <pieterh>	mato: reason for the extra .1...
| [Tuesday 26 April 2011] [10:11:47] <mato>	pieterh: will look at it in a sec, thx for pointer
| [Tuesday 26 April 2011] [10:12:01] <pieterh>	ok, no hurry... would like to release 2.1.5 today but we have time
| [Tuesday 26 April 2011] [10:12:40] <pieterh>	btw czmq is a much nicer name, thanks for insisting
| [Tuesday 26 April 2011] [10:12:46] <CIA-75>	jzmq: 03Gonzalo Diethelm 07master * rb5037aa 10/ (src/Socket.cpp src/org/zeromq/ZMQ.java): (log message trimmed)
| [Tuesday 26 April 2011] [10:12:47] <CIA-75>	jzmq: Added support for 0MQ 3.0. Everything should still work with previous
| [Tuesday 26 April 2011] [10:12:47] <CIA-75>	jzmq: versions of 0MQ. Changes were:
| [Tuesday 26 April 2011] [10:12:47] <CIA-75>	jzmq: 1. Added all missing socket options.
| [Tuesday 26 April 2011] [10:12:47] <CIA-75>	jzmq: 2. Use zmq_sendmsg() and zmq_recvmsg().
| [Tuesday 26 April 2011] [10:12:47] <CIA-75>	jzmq: 3. Added DONTWAIT as synonym of NOBLOCK.
| [Tuesday 26 April 2011] [10:12:48] <CIA-75>	jzmq: Could use a lot of testing with different versions of the 0MQ library,
| [Tuesday 26 April 2011] [10:13:30] <mato>	pieterh: i'd just call it 2.1.6 and ignore 2.1.5
| [Tuesday 26 April 2011] [10:13:42] <pieterh>	mato: if you're happy with that, it's much easier for me
| [Tuesday 26 April 2011] [10:13:49] <mato>	pieterh: yes, i'm happy with that
| [Tuesday 26 April 2011] [10:14:10] <mato>	normal procedure, i've seen it elsewhere
| [Tuesday 26 April 2011] [10:14:12] <pieterh>	ok, so I can apply the patch martin sent today, and I'll mark 2.1.5 as "broken"
| [Tuesday 26 April 2011] [10:14:21] <mato>	yes
| [Tuesday 26 April 2011] [10:14:35] <pieterh>	nice to have you back
| [Tuesday 26 April 2011] [10:14:55] <mato>	ja, looks like i'll be more active in zmq again
| [Tuesday 26 April 2011] [10:15:19] <mato>	also time to do some work after lots of holidays
| [Tuesday 26 April 2011] [10:15:29] <pieterh>	I will probably be less involved after the summer
| [Tuesday 26 April 2011] [10:15:30] <mato>	btw saying that i arrive late to threads is a bit unfair :)
| [Tuesday 26 April 2011] [10:15:38] <pieterh>	well, it's kind of a pattern... :)
| [Tuesday 26 April 2011] [10:15:41] <mato>	it was only 5 days, *and* i was on a boat in the med
| [Tuesday 26 April 2011] [10:15:47] <pieterh>	diaf
| [Tuesday 26 April 2011] [10:15:52] <pieterh>	on a boat in the med... 
| [Tuesday 26 April 2011] [10:16:07] <mato>	plus, referring to irc discussions is about the same as saying "we discussed it over beer last night, you weren't there" :-)
| [Tuesday 26 April 2011] [10:16:33] <pieterh>	mato: sincerely, this is how it goes, we have an issue, we discuss on email and irc, and move quickly to a solution
| [Tuesday 26 April 2011] [10:16:36] <mato>	yeah, did a circumnavigation of corsica
| [Tuesday 26 April 2011] [10:16:49] <mato>	pieterh: there's no "hurry" :)
| [Tuesday 26 April 2011] [10:16:59] <pieterh>	mato: IMO there is a hurry, yes
| [Tuesday 26 April 2011] [10:17:08] <mato>	anyway, nice we came to a good conclusion
| [Tuesday 26 April 2011] [10:17:13] <pieterh>	but mainly it's more efficient to make two, three fast cycles than one slow one
| [Tuesday 26 April 2011] [10:17:38] <mato>	sure, but there is no hurry regarding ZAPI i mean
| [Tuesday 26 April 2011] [10:17:56] <pieterh>	there is a hurry
| [Tuesday 26 April 2011] [10:18:08] <pieterh>	I've been struggling with an undocumented ad-hoc API in the Guide for half a year
| [Tuesday 26 April 2011] [10:18:19] <pieterh>	it's an unavoidable problem
| [Tuesday 26 April 2011] [10:18:35] <pieterh>	and everyone who learns & translates zhelpers is getting trapped
| [Tuesday 26 April 2011] [10:18:42] <mato>	well, C *is* a low-level language...
| [Tuesday 26 April 2011] [10:18:46] <pieterh>	not really
| [Tuesday 26 April 2011] [10:19:02] <pieterh>	i can write full *complex* apps in a few hundred lines of code
| [Tuesday 26 April 2011] [10:19:14] <pieterh>	it's all about sensible abstractions
| [Tuesday 26 April 2011] [10:19:19] <mato>	yes, but you invent your own object & type/container system on top of C
| [Tuesday 26 April 2011] [10:19:23] <mato>	this is a common pattern
| [Tuesday 26 April 2011] [10:19:30] <mato>	most substantial C project do that
| [Tuesday 26 April 2011] [10:19:42] <pieterh>	so, if we don't offer a reusable set of classes, people will reinvent their own
| [Tuesday 26 April 2011] [10:19:48] <mato>	which is *fine*
| [Tuesday 26 April 2011] [10:19:50] <pieterh>	i'd like to see more consistency between bindings
| [Tuesday 26 April 2011] [10:19:59] <pieterh>	it's important for human portabilty
| [Tuesday 26 April 2011] [10:20:03] <pieterh>	*portability
| [Tuesday 26 April 2011] [10:20:09] <pieterh>	e.g. how to set a socket option
| [Tuesday 26 April 2011] [10:20:24] <mato>	this is exactly my point; we are not out here to give people a C object/type/portability API
| [Tuesday 26 April 2011] [10:20:45] <pieterh>	well, the C API is just one of many but it is my gift, yes
| [Tuesday 26 April 2011] [10:20:50] <mato>	yeah, but you see my point
| [Tuesday 26 April 2011] [10:21:02] <pieterh>	let's say it gives me the authority to speak as a binding author
| [Tuesday 26 April 2011] [10:21:12] <pieterh>	I know what my users (who happen to be me) need
| [Tuesday 26 April 2011] [10:21:20] <pieterh>	(but not only me, even now)
| [Tuesday 26 April 2011] [10:21:25] <mato>	sure
| [Tuesday 26 April 2011] [10:21:39] <mato>	but you see the difference between what you're building and what the native API is there for
| [Tuesday 26 April 2011] [10:21:42] <mato>	right?
| [Tuesday 26 April 2011] [10:21:47] <pieterh>	have you seen the wiki page now?
| [Tuesday 26 April 2011] [10:21:56] <pieterh>	I wanted your review of that, I think it's getting much better
| [Tuesday 26 April 2011] [10:22:10] <mato>	hang on, doing multiple things at once
| [Tuesday 26 April 2011] [10:22:26] <pieterh>	this layering is essential, subtle
| [Tuesday 26 April 2011] [10:24:32] <mato>	well, i kind of see where you're going, libzmq + stuff = zeromq distribution
| [Tuesday 26 April 2011] [10:24:37] <pieterh>	ja
| [Tuesday 26 April 2011] [10:24:44] <pieterh>	this is what the user needs
| [Tuesday 26 April 2011] [10:24:45] <mato>	however that's not the case right now
| [Tuesday 26 April 2011] [10:24:56] <mato>	people equate libzmq with zeromq
| [Tuesday 26 April 2011] [10:25:03] <pieterh>	one step at a time... it's enormously hard to get this kind of change
| [Tuesday 26 April 2011] [10:25:04] <mato>	i'd be happier calling the distribution something else
| [Tuesday 26 April 2011] [10:25:06] <mato>	in fact
| [Tuesday 26 April 2011] [10:25:18] <mato>	that's a business opportunity hiding for you
| [Tuesday 26 April 2011] [10:25:21] <mato>	standard stuff
| [Tuesday 26 April 2011] [10:25:25] 	 * pieterh is not interested in that
| [Tuesday 26 April 2011] [10:25:40] <pieterh>	the key is here is (1) community, (2) community, and (3) community
| [Tuesday 26 April 2011] [10:25:56] <pieterh>	"zeromq = libzmq" is bad for the community
| [Tuesday 26 April 2011] [10:26:13] <pieterh>	I think that's self-evident
| [Tuesday 26 April 2011] [10:26:17] <mato>	why?
| [Tuesday 26 April 2011] [10:26:38] <pieterh>	you really don't see?
| [Tuesday 26 April 2011] [10:26:44] <mato>	i'd like your view
| [Tuesday 26 April 2011] [10:26:56] <pieterh>	because it excludes about 90% of potential and actual contributors to what you call "zeromq"
| [Tuesday 26 April 2011] [10:27:11] <pieterh>	whereas the value to a contributor is to be part of the "zeromq" project
| [Tuesday 26 April 2011] [10:27:22] <pieterh>	not "the" but "a big part of the"
| [Tuesday 26 April 2011] [10:27:51] <pieterh>	you effectively turn all projects except libzmq into 2nd class citizens
| [Tuesday 26 April 2011] [10:28:05] <pieterh>	while at the same time making it *really* hard for people to contribute to libzmq
| [Tuesday 26 April 2011] [10:28:09] <pieterh>	surely you are aware of this?
| [Tuesday 26 April 2011] [10:28:22] <pieterh>	it is a toxic form of elitism that will backfire sooner or later
| [Tuesday 26 April 2011] [10:28:50] <mato>	hey, i'm also learning
| [Tuesday 26 April 2011] [10:29:09] <pieterh>	ok, don't mean to be critical, I've been down this road often before
| [Tuesday 26 April 2011] [10:29:15] <CIA-75>	jzmq: 03Gonzalo Diethelm 07master * r623f6b9 10/ Makefile.am : 
| [Tuesday 26 April 2011] [10:29:15] <CIA-75>	jzmq: Merged pull request #36 from MrEvil/master.
| [Tuesday 26 April 2011] [10:29:15] <CIA-75>	jzmq: Added SHELL variable to Makefile.am. - http://bit.ly/fNmtRa
| [Tuesday 26 April 2011] [10:29:25] <pieterh>	how come jzmq commits are appearing here?
| [Tuesday 26 April 2011] [10:29:25] <mato>	and i am aware of these things, and hopefully they will change for the better
| [Tuesday 26 April 2011] [10:29:31] <mato>	they always were
| [Tuesday 26 April 2011] [10:29:43] <pieterh>	it's nice, we should expand this to more zmq projects
| [Tuesday 26 April 2011] [10:29:46] <mato>	and libzmq commits should also but i forgot to update CIA for the name change
| [Tuesday 26 April 2011] [10:29:49] <pieterh>	yeah
| [Tuesday 26 April 2011] [10:30:06] <pieterh>	my vision, which is always populist and anti-elitist is that we have a community of projects
| [Tuesday 26 April 2011] [10:30:12] <mato>	any project that has a VC repo can be monitored
| [Tuesday 26 April 2011] [10:30:22] <pieterh>	obviously layered, and obviously with different (earned) statuses
| [Tuesday 26 April 2011] [10:30:34] <pieterh>	anyone can join, anyone can compete, at any level
| [Tuesday 26 April 2011] [10:30:48] <pieterh>	the ability to compete is essential
| [Tuesday 26 April 2011] [10:31:03] <pieterh>	if I don't like implementation of X, I have the right (and information) to make X-prime
| [Tuesday 26 April 2011] [10:31:17] <pieterh>	thus, GPL license, proper layered specs, etc.
| [Tuesday 26 April 2011] [10:31:31] <pieterh>	any layer that escapes this competition will become corrupt over time
| [Tuesday 26 April 2011] [10:31:31] <mato>	of course. if you don't like the core API, you can fork it and users (may) follow with their feet
| [Tuesday 26 April 2011] [10:31:34] <pieterh>	yes
| [Tuesday 26 April 2011] [10:31:36] <pieterh>	precisely
| [Tuesday 26 April 2011] [10:31:43] <pieterh>	which is why we need proper WLP specs
| [Tuesday 26 April 2011] [10:32:05] <Guthur>	GPL?
| [Tuesday 26 April 2011] [10:32:09] <mato>	look, it's your modues operandi
| [Tuesday 26 April 2011] [10:32:20] <pieterh>	mato: well, the zeromq community follows my design, yes
| [Tuesday 26 April 2011] [10:32:36] <Guthur>	I thought libzmq was LGPL
| [Tuesday 26 April 2011] [10:32:36] 	 * mato would argue that you force your design on the community
| [Tuesday 26 April 2011] [10:32:38] <pieterh>	but I'm stating principles that are afaics scientifically provable
| [Tuesday 26 April 2011] [10:32:40] <mato>	but that's irrelevant
| [Tuesday 26 April 2011] [10:32:56] <pieterh>	Guthur: LGPL is GPL with an extra clause or two, same thing essentially
| [Tuesday 26 April 2011] [10:33:12] <pieterh>	mato: discussing the design ideology of a thing is relevant
| [Tuesday 26 April 2011] [10:33:17] <pieterh>	when we discuss that thing
| [Tuesday 26 April 2011] [10:33:33] <pieterh>	do recall that the whole 0MQ community was a conscious design from day 1
| [Tuesday 26 April 2011] [10:33:55] 	 * mato does not want to get into this discussion
| [Tuesday 26 April 2011] [10:34:00] <mato>	over beer one day
| [Tuesday 26 April 2011] [10:34:02] <pieterh>	ok, but bear with me...
| [Tuesday 26 April 2011] [10:34:09] <Guthur>	GPL has a lot of stigma for some developers though
| [Tuesday 26 April 2011] [10:34:09] <pieterh>	what it means in terms of definitions
| [Tuesday 26 April 2011] [10:34:23] <pieterh>	is that "zeromq" is the community, not the core library
| [Tuesday 26 April 2011] [10:34:33] <pieterh>	this is perhaps hard to see, from some perspectives
| [Tuesday 26 April 2011] [10:34:59] <pieterh>	but it's my view, and it's based on experience of what will work and not work
| [Tuesday 26 April 2011] [10:35:26] <pieterh>	let me... give you some other examples
| [Tuesday 26 April 2011] [10:35:36] <pieterh>	of successful communities that have done this
| [Tuesday 26 April 2011] [10:35:41] <pieterh>	apache
| [Tuesday 26 April 2011] [10:35:43] <pieterh>	xmpp
| [Tuesday 26 April 2011] [10:35:47] <pieterh>	linux
| [Tuesday 26 April 2011] [10:35:50] <Guthur>	eek, just realised clrzmq2 seems to be published under GPL
| [Tuesday 26 April 2011] [10:36:05] <pieterh>	Guthur: if you're the sole author you can relicense any time you like
| [Tuesday 26 April 2011] [10:36:20] <pieterh>	bsd
| [Tuesday 26 April 2011] [10:36:29] <Guthur>	well, it's slightly complicated I orginally based it of clrzmq
| [Tuesday 26 April 2011] [10:36:47] <pieterh>	Guthur: and that was licensed as what?
| [Tuesday 26 April 2011] [10:36:58] <Guthur>	but it bears very little resemblance to that now
| [Tuesday 26 April 2011] [10:37:19] <Guthur>	pieterh: hehe I copied the license agreement from that
| [Tuesday 26 April 2011] [10:37:21] <pieterh>	Guthur: irrelevant, unfortunately, unless you can explicitly remove all possible derived code
| [Tuesday 26 April 2011] [10:37:31] <pieterh>	so clrzmq2 has to be GPL too...
| [Tuesday 26 April 2011] [10:37:41] <mato>	pieterh: sure, i guess this is not clear
| [Tuesday 26 April 2011] [10:37:49] <pieterh>	you can make a new clean-room implementation, presumably, quite straight-forward
| [Tuesday 26 April 2011] [10:37:56] <Guthur>	pieterh: well that is the probably with software development, there is only one way to do somethings
| [Tuesday 26 April 2011] [10:37:59] <mato>	pieterh: something to be discussed in brussels
| [Tuesday 26 April 2011] [10:38:01] <Guthur>	I can't possibly remove it
| [Tuesday 26 April 2011] [10:38:07] <pieterh>	mato: sure, much easier over beer... :)
| [Tuesday 26 April 2011] [10:38:09] <Guthur>	probably/problem
| [Tuesday 26 April 2011] [10:38:12] <mato>	pieterh: it's still more of a "beer" discussion than anything else
| [Tuesday 26 April 2011] [10:38:21] <mato>	ideology as opposed to "here is code that does stuff"
| [Tuesday 26 April 2011] [10:38:34] <mato>	it's fun to see the personalities at work
| [Tuesday 26 April 2011] [10:38:40] <Guthur>	expecially foreign function calls
| [Tuesday 26 April 2011] [10:38:42] <pieterh>	mato: put it like this, I'm responsible for the 0MQ community design and implementation, and I see it as "code that does stuff"
| [Tuesday 26 April 2011] [10:38:50] <pieterh>	things like legal frameworks are social code
| [Tuesday 26 April 2011] [10:38:56] <pieterh>	that's my lawyer hat
| [Tuesday 26 April 2011] [10:39:38] <mato>	you just like doing all this stuff :)
| [Tuesday 26 April 2011] [10:39:55] <pieterh>	mato: yes, that's true, and I also intensely dislike environments where it's badly done
| [Tuesday 26 April 2011] [10:40:00] <pieterh>	well, you hate those too
| [Tuesday 26 April 2011] [10:40:13] <Guthur>	the other authors where Martin and someone called Jeffrey Dik
| [Tuesday 26 April 2011] [10:40:14] <pieterh>	I don't need to remind you of weekly wednesday phone conferences...
| [Tuesday 26 April 2011] [10:40:21] <mato>	sure
| [Tuesday 26 April 2011] [10:40:27] <pieterh>	Guthur: I'd contact them all and ask if you can relicense their work
| [Tuesday 26 April 2011] [10:40:36] <pieterh>	they have to explicitly grant you a new license
| [Tuesday 26 April 2011] [10:40:55] <mato>	anyhow, i guess my thing is that the zeromq != libzmq thing is not clear
| [Tuesday 26 April 2011] [10:41:10] <pieterh>	mato: I know, but this should in theory become clearer over time
| [Tuesday 26 April 2011] [10:41:21] <pieterh>	renaming the project to 'libzmq' was a large step
| [Tuesday 26 April 2011] [10:41:24] <mato>	and when i see you discouraging use of the core API, i get annoyed since from my point of view (and users i have spoken to), the core API is *good*
| [Tuesday 26 April 2011] [10:41:33] <mato>	i realise you don't like it
| [Tuesday 26 April 2011] [10:41:38] <pieterh>	ah, mato... I didn't intend to discourage it
| [Tuesday 26 April 2011] [10:41:45] <pieterh>	look, it has some real flaws
| [Tuesday 26 April 2011] [10:41:47] <mato>	but you've been doing that quite persistently
| [Tuesday 26 April 2011] [10:41:58] <pieterh>	no, I've been trying to improve it quite persistently
| [Tuesday 26 April 2011] [10:42:07] <pieterh>	when  my suggestions are persistently discarded, what do I do?
| [Tuesday 26 April 2011] [10:42:13] <mato>	make your own
| [Tuesday 26 April 2011] [10:42:16] <pieterh>	exactly
| [Tuesday 26 April 2011] [10:42:17] <mato>	which is fine
| [Tuesday 26 April 2011] [10:42:32] <mato>	but please do not tread on other people who actually like the current API
| [Tuesday 26 April 2011] [10:42:35] <mato>	that is not fair
| [Tuesday 26 April 2011] [10:42:40] <pieterh>	over-sensitive, maybe
| [Tuesday 26 April 2011] [10:42:45] <pieterh>	I don't think I treaded on anyone
| [Tuesday 26 April 2011] [10:42:46] <mato>	and it's abusing your position somewhat IMO
| [Tuesday 26 April 2011] [10:42:54] <pieterh>	if I did, apologies, sincerely...
| [Tuesday 26 April 2011] [10:43:19] <pieterh>	IMO you may be seeing intent where there is none
| [Tuesday 26 April 2011] [10:43:34] <mato>	possibly, but even sans the intent i see the resulting confusion
| [Tuesday 26 April 2011] [10:43:42] <mato>	which is why i spoke up now
| [Tuesday 26 April 2011] [10:43:43] <pieterh>	if I want to tread on the current API, trust me, I won't be subtle about it
| [Tuesday 26 April 2011] [10:43:52] <pieterh>	am I a subtle person?
| [Tuesday 26 April 2011] [10:43:52] <mato>	i would have earlier, but i would have got yelled at that there is no problem :)
| [Tuesday 26 April 2011] [10:43:56] <pieterh>	srsly
| [Tuesday 26 April 2011] [10:44:13] <pieterh>	I have a long list of things to improve with the current API
| [Tuesday 26 April 2011] [10:44:24] <pieterh>	what would you like me to do with that list?
| [Tuesday 26 April 2011] [10:44:39] <mato>	submit patches?
| [Tuesday 26 April 2011] [10:44:47] <pieterh>	sorry, can't do that (not competent)
| [Tuesday 26 April 2011] [10:44:47] <mato>	ask el sustrik, he is the boss on master
| [Tuesday 26 April 2011] [10:44:49] <pieterh>	I'm a user
| [Tuesday 26 April 2011] [10:44:53] <mato>	lol
| [Tuesday 26 April 2011] [10:45:01] <mato>	then do what you're doing now
| [Tuesday 26 April 2011] [10:45:04] <mato>	which is fine
| [Tuesday 26 April 2011] [10:45:06] <Guthur>	pieterh, Sorry to drift a little OT, but would it be possible for me un-derive the work, not that I actually want to
| [Tuesday 26 April 2011] [10:45:19] <pieterh>	Guthur: you need to make a clean room implementation
| [Tuesday 26 April 2011] [10:45:25] <Guthur>	or by looking at the original code has be thought process been tainted
| [Tuesday 26 April 2011] [10:45:31] <Guthur>	be/my
| [Tuesday 26 April 2011] [10:45:35] <pieterh>	Guthur: you document what the binding does, in written form, as detailed as you can but without code
| [Tuesday 26 April 2011] [10:45:47] <pieterh>	you give that to *someone else* and bribe them to make a new version
| [Tuesday 26 April 2011] [10:45:52] <pieterh>	at least a skeleton
| [Tuesday 26 April 2011] [10:45:54] <mato>	pieterh: you say you will be less involved after summer, why's that?
| [Tuesday 26 April 2011] [10:45:55] <Guthur>	lol
| [Tuesday 26 April 2011] [10:46:06] <pieterh>	mato: I'll explain over beer, not here
| [Tuesday 26 April 2011] [10:46:12] <Guthur>	legal stuff is bonkers
| [Tuesday 26 April 2011] [10:46:15] <mato>	incidentally, are you still planning on coming to bts before the brussels conf?
| [Tuesday 26 April 2011] [10:46:25] <pieterh>	Guthur: well, when you reuse someone else's code, that's the cost
| [Tuesday 26 April 2011] [10:46:32] <pieterh>	mato: no, after that
| [Tuesday 26 April 2011] [10:46:38] <mato>	right...
| [Tuesday 26 April 2011] [10:46:50] <mato>	btw how far is charleroi from brussels ?
| [Tuesday 26 April 2011] [10:46:57] <pieterh>	1hour, it's a decent connection
| [Tuesday 26 April 2011] [10:46:58] <mato>	ryanair seems to be the only sane cheap option
| [Tuesday 26 April 2011] [10:47:02] <pieterh>	yes, it's sane and cheap
| [Tuesday 26 April 2011] [10:47:13] <pieterh>	except the return flight is bonkers, it's at 7.30 am or so
| [Tuesday 26 April 2011] [10:47:25] <mato>	it was showing me something during the day
| [Tuesday 26 April 2011] [10:47:27] <mato>	maybe they've changed
| [Tuesday 26 April 2011] [10:47:27] <pieterh>	I have a crazy idea... how about we drive back to BTS together?
| [Tuesday 26 April 2011] [10:47:35] <pieterh>	maybe changed... 
| [Tuesday 26 April 2011] [10:47:42] <pieterh>	ah, that was perhaps the winter schedule...
| [Tuesday 26 April 2011] [10:47:46] 	 * mato is not a fan of long drives
| [Tuesday 26 April 2011] [10:47:52] 	 * pieterh likes the long drives
| [Tuesday 26 April 2011] [10:47:56] <mato>	:-)
| [Tuesday 26 April 2011] [10:48:00] <pieterh>	12 hours of argument :)
| [Tuesday 26 April 2011] [10:48:05] <pieterh>	fuuuuuuuuu.....
| [Tuesday 26 April 2011] [10:48:11] <mato>	night train works too
| [Tuesday 26 April 2011] [10:48:18] <mato>	13 hours of argument *and* beer
| [Tuesday 26 April 2011] [10:48:19] <mato>	:-)
| [Tuesday 26 April 2011] [10:48:27] 	 * pieterh has to drive, sadly, need to pick up some stuff in BTS
| [Tuesday 26 April 2011] [10:48:38] <pieterh>	otherwise train sounds excellent
| [Tuesday 26 April 2011] [10:48:49] <pieterh>	I'
| [Tuesday 26 April 2011] [10:49:01] <pieterh>	I'll add a travel note for those coming via Charleroi
| [Tuesday 26 April 2011] [10:49:08] <mato>	d'you have a floor i can sleep on in brussels? or is there a cheap-ish hotel in the vicinity?
| [Tuesday 26 April 2011] [10:49:15] <pieterh>	mato: yes, you can stay with us
| [Tuesday 26 April 2011] [10:49:25] <pieterh>	we have space, and beer
| [Tuesday 26 April 2011] [10:49:37] <pieterh>	you know you're always welcome in my home
| [Tuesday 26 April 2011] [10:49:54] <pieterh>	if you bring a sleeping bag that'd probably help
| [Tuesday 26 April 2011] [10:50:00] <mato>	i can do that
| [Tuesday 26 April 2011] [10:50:06] <mato>	i have one of those miniature summer ones
| [Tuesday 26 April 2011] [10:50:18] <Guthur>	pieterh: what happens in the case where an author becomes unreadable
| [Tuesday 26 April 2011] [10:50:23] <Guthur>	unreachable*
| [Tuesday 26 April 2011] [10:50:32] <mato>	Guthur: someone else takes over
| [Tuesday 26 April 2011] [10:50:35] <pieterh>	Guthur: you're unable to relicense, period
| [Tuesday 26 April 2011] [10:50:45] <Guthur>	that's pants
| [Tuesday 26 April 2011] [10:50:45] <mato>	oh, sorry, different discussion
| [Tuesday 26 April 2011] [10:50:54] <pieterh>	this is why you need to be pretty sure about this before over-investing
| [Tuesday 26 April 2011] [10:50:56] <Guthur>	what if he's dead
| [Tuesday 26 April 2011] [10:51:12] <pieterh>	Guthur: wait 75 years, or just 50 in Europe
| [Tuesday 26 April 2011] [10:51:12] <mato>	copyright goes to his inheritors
| [Tuesday 26 April 2011] [10:51:15] <pieterh>	welcome to copyright law
| [Tuesday 26 April 2011] [10:51:17] <mato>	doesn't it?
| [Tuesday 26 April 2011] [10:51:20] <pieterh>	it's magical!
| [Tuesday 26 April 2011] [10:51:40] <pieterh>	mato: yes, but 50+ 
| [Tuesday 26 April 2011] [10:52:04] <mato>	pieterh: ah, so you wait 50 years only to be told by surviving family to bugger off anyway :)
| [Tuesday 26 April 2011] [10:52:11] 	 * Guthur hopes the other guy is reachable
| [Tuesday 26 April 2011] [10:52:18] <pieterh>	Guthur: you're welcome to lobby to change the law but in the meantime your options are (a) accept the license under which you got the code (b) get permission to relicense (c) rewrite, clean-room
| [Tuesday 26 April 2011] [10:52:40] <pieterh>	mato: after 50 years the copyright on the original work used for the derivation has expired
| [Tuesday 26 April 2011] [10:52:57] <pieterh>	this is of course a bad joke, in software terms
| [Tuesday 26 April 2011] [10:53:25] <Guthur>	yep
| [Tuesday 26 April 2011] [10:55:11] <pieterh>	mato: I've added travel instructions from Charleroi to Brussels on the http://www.zeromq.org/event:brussels-2011-05-10 page
| [Tuesday 26 April 2011] [10:56:26] <mato>	pieterh: on the charleroi website it mentions some kind of direct shuttle to gare du midi for EUR 22 return
| [Tuesday 26 April 2011] [10:56:43] <pieterh>	I've added the necessary link
| [Tuesday 26 April 2011] [10:57:03] <pieterh>	the train is cheaper and more relaxing but takes longer
| [Tuesday 26 April 2011] [10:57:17] <mato>	oh, I see, the last sentence should be "If you can't get on the shuttle bus" or something
| [Tuesday 26 April 2011] [10:58:25] <mato>	pieterh: the return flight is now 12:20, much saner
| [Tuesday 26 April 2011] [10:59:07] <mato>	how does ryanair work? i take it they are anal about baggage or something being a lowcost carrier?
| [Tuesday 26 April 2011] [10:59:32] <pieterh>	mato: hmm, you're best taking only hand luggage and squeezing your clothes into that
| [Tuesday 26 April 2011] [10:59:46] <pieterh>	also print your boarding passes out beforehand
| [Tuesday 26 April 2011] [11:00:08] <pieterh>	and I tend to pay for the extra "early boarding", the best seats are in the very first row
| [Tuesday 26 April 2011] [11:00:25] <pieterh>	hang luggage has to be within standard dimensions
| [Tuesday 26 April 2011] [11:00:40] <pieterh>	that is I'm sure noted on the ryanair site
| [Tuesday 26 April 2011] [11:00:59] <pieterh>	if you can survive the relative brutality of the experience, it is quite pleasant
| [Tuesday 26 April 2011] [11:01:08] <pieterh>	extremely rapid boarding and deboarding
| [Tuesday 26 April 2011] [11:01:22] <pieterh>	it's the zeromq of plane flights, in some respects
| [Tuesday 26 April 2011] [11:01:37] <Guthur>	Ryanair are the carrier i detest the most
| [Tuesday 26 April 2011] [11:01:41] <pieterh>	hehe
| [Tuesday 26 April 2011] [11:01:58] <mato>	yes, well, but AUA want EUR 380 for a return flight to brussels, that's just insane :-)
| [Tuesday 26 April 2011] [11:02:12] <mato>	Ryanair for 88 EUR is cheap
| [Tuesday 26 April 2011] [11:02:28] <Guthur>	they are the only one that requires a passport of internal flights, let alone the charge for everything setup
| [Tuesday 26 April 2011] [11:02:35] <Guthur>	of/for
| [Tuesday 26 April 2011] [11:04:03] <jhawk28>	I suspect that the pain of blocking would be minimized if there were a timeout version of send
| [Tuesday 26 April 2011] [11:05:40] <pieterh>	mato: yes, it's easily worth it IMO
| [Tuesday 26 April 2011] [11:05:53] <pieterh>	Guthur: all airlines ask for ID, no exceptions, to prevent ticket fraud
| [Tuesday 26 April 2011] [11:06:13] <Guthur>	pieterh: not a passport for travel on an internal flight
| [Tuesday 26 April 2011] [11:06:28] <pieterh>	UK internal you mean?
| [Tuesday 26 April 2011] [11:06:32] <Guthur>	yep
| [Tuesday 26 April 2011] [11:06:39] <Guthur>	Ryanair are the only one
| [Tuesday 26 April 2011] [11:06:46] <pieterh>	well, if the silly UKians had ID cards, that'd be easier
| [Tuesday 26 April 2011] [11:06:56] <mato>	pieterh: ok it means i get in monday evening and leave wednesday AM, which is ideal
| [Tuesday 26 April 2011] [11:06:56] <pieterh>	the point is to avoid ticket fraud
| [Tuesday 26 April 2011] [11:06:56] <Guthur>	i have plenty
| [Tuesday 26 April 2011] [11:07:09] <pieterh>	i.e. I buy a bunch of tickets at 1Euro and resell them for anonymous reuse
| [Tuesday 26 April 2011] [11:07:18] <Guthur>	driving license, and passport
| [Tuesday 26 April 2011] [11:07:21] <pieterh>	official ID cards, not driving license...
| [Tuesday 26 April 2011] [11:07:24] <guido_g>	howdy
| [Tuesday 26 April 2011] [11:07:24] <Guthur>	why would I need another
| [Tuesday 26 April 2011] [11:07:36] <pieterh>	mato: yup, neat
| [Tuesday 26 April 2011] [11:07:37] <Guthur>	driving license is quite official
| [Tuesday 26 April 2011] [11:07:55] <Guthur>	it's got from a government agency
| [Tuesday 26 April 2011] [11:08:26] <pieterh>	Guthur: you're right, I've no idea why I'm defending ryanair, they deserve your scorn, but however they're 1/4r the cost of alternatives, so... easy choice
| [Tuesday 26 April 2011] [11:08:32] <pieterh>	guido_g: hi!
| [Tuesday 26 April 2011] [11:08:53] <guido_g>	hi pieterh!
| [Tuesday 26 April 2011] [11:09:05] <pieterh>	I see you upgraded jzmq to 3.0, nice
| [Tuesday 26 April 2011] [11:09:23] <pieterh>	guido_g: sorry, I'm confusing my 'g's
| [Tuesday 26 April 2011] [11:09:27] <guido_g>	:)
| [Tuesday 26 April 2011] [11:09:40] <Guthur>	pieterh: it's quite alright, I fell foul of their passport requirement, and so I'm quite bitter
| [Tuesday 26 April 2011] [11:09:59] <Guthur>	I know...of course I should have read the terms...
| [Tuesday 26 April 2011] [11:10:04] <pieterh>	Guthur: see, if you lived in a civilized country you'd have an ID card and no stress
| [Tuesday 26 April 2011] [11:10:27] <Guthur>	pieterh: would I also need a driving license and passport?
| [Tuesday 26 April 2011] [11:10:32] <pieterh>	nope
| [Tuesday 26 April 2011] [11:10:45] <pieterh>	not unless you want to drive and cross borders outside schengen
| [Tuesday 26 April 2011] [11:10:51] <Guthur>	lol
| [Tuesday 26 April 2011] [11:11:12] <pieterh>	i can travel to/from UK with only my id card, in fact
| [Tuesday 26 April 2011] [11:11:14] <guido_g>	but these things you'll better do w/ a fake identity anyway ]:->
| [Tuesday 26 April 2011] [11:11:17] <Guthur>	those options are nice to have
| [Tuesday 26 April 2011] [11:11:18] <pieterh>	so it's valid across the whole EU afaics
| [Tuesday 26 April 2011] [11:11:45] <Guthur>	hehe everyone trusts the belgians
| [Tuesday 26 April 2011] [11:11:56] <Guthur>	never done nothing to no one, hehe
| [Tuesday 26 April 2011] [11:12:09] <pieterh>	except large parts of Africa, but nevermind...
| [Tuesday 26 April 2011] [11:12:15] <mato>	bah, they sure do add random bits to the fare
| [Tuesday 26 April 2011] [11:12:22] <mato>	6 EUR "administration fee"
| [Tuesday 26 April 2011] [11:12:23] <mato>	wtf
| [Tuesday 26 April 2011] [11:12:47] <pieterh>	mato: yeah
| [Tuesday 26 April 2011] [11:12:57] <pieterh>	it's still so cheap as to be stupid
| [Tuesday 26 April 2011] [11:13:09] <pieterh>	I was buying tickets to BTS for 40 Euro all in at one point
| [Tuesday 26 April 2011] [11:13:24] <guido_g>	pieterh tweets in dutch? nice...
| [Tuesday 26 April 2011] [11:13:40] <mato>	yeah i checked the train, that would have been ~260 EUR return
| [Tuesday 26 April 2011] [11:13:42] <pieterh>	well, 'tweeten' just sounds weird in Dutch... :)
| [Tuesday 26 April 2011] [11:13:56] <mato>	so 108 EUR is still silly cheap
| [Tuesday 26 April 2011] [11:14:18] <pieterh>	plus it's really a nice little flight
| [Tuesday 26 April 2011] [11:14:29] <pieterh>	both small airports, little hassle
| [Tuesday 26 April 2011] [11:17:32] <Guthur>	where is BTS
| [Tuesday 26 April 2011] [11:18:09] <mato>	Bratislava, Slovakia
| [Tuesday 26 April 2011] [11:18:45] <Guthur>	ah, i honestly would never have got that
| [Tuesday 26 April 2011] [11:19:12] <mato>	pieterh: um, is there something vaguely like an invoice i can get off ryanair?
| [Tuesday 26 April 2011] [11:19:39] <mato>	the email receipt does not have e.g. the card details
| [Tuesday 26 April 2011] [11:19:40] <mato>	oh well
| [Tuesday 26 April 2011] [11:19:58] <pieterh>	mato: I usually print the email receipt, that's sufficient along with the visa card statement, at least in Belgium
| [Tuesday 26 April 2011] [11:20:06] <pieterh>	perhaps also a copy of the boarding passes
| [Tuesday 26 April 2011] [11:21:11] <guido_g>	anything a nerd should see in brussels?
| [Tuesday 26 April 2011] [11:21:20] <pieterh>	guido_g: how long will you have?
| [Tuesday 26 April 2011] [11:21:22] 	 * guido_g arrives at 13:0 on monday
| [Tuesday 26 April 2011] [11:21:27] <guido_g>	*12:30
| [Tuesday 26 April 2011] [11:21:41] <pieterh>	hmm... we might organize a meetup on monday evening...
| [Tuesday 26 April 2011] [11:21:55] <mato>	that's what tuesday evening is for, no?
| [Tuesday 26 April 2011] [11:21:56] <guido_g>	cool... tweo meetups for the price of one!
| [Tuesday 26 April 2011] [11:21:59] <mato>	:)
| [Tuesday 26 April 2011] [11:22:02] <guido_g>	book nonw! limited offer! :)
| [Tuesday 26 April 2011] [11:22:27] <pieterh>	there's like the 'official meetup' and the 'secret' one
| [Tuesday 26 April 2011] [11:22:39] <guido_g>	ahhh...
| [Tuesday 26 April 2011] [11:23:53] <pieterh>	well, if you have time in brussels... there is an original lambic brewery, cantillion
| [Tuesday 26 April 2011] [11:24:10] <pieterh>	otherwise, just chilling in the old town with a laptop and wifi is fun
| [Tuesday 26 April 2011] [11:24:19] <pieterh>	actually right where we have the conference
| [Tuesday 26 April 2011] [11:24:55] <pieterh>	chilling = drinking orval and pretending to work while admiring the view
| [Tuesday 26 April 2011] [12:12:25] <phantomcircuit>	ok this is just ridiculous
| [Tuesday 26 April 2011] [12:12:33] <phantomcircuit>	i cant even get php-zmq to build on linux
| [Tuesday 26 April 2011] [12:12:37] <phantomcircuit>	autotools version mismatch
| [Tuesday 26 April 2011] [12:12:58] <Skaag>	built fine for me on Ubuntu 10.04
| [Tuesday 26 April 2011] [12:13:09] <Skaag>	with the standard build-essentials
| [Tuesday 26 April 2011] [12:19:31] <CIA-75>	libzmq: 03Martin Sustrik 07master * r5816976 10/ (10 files in 3 dirs): 
| [Tuesday 26 April 2011] [12:19:31] <CIA-75>	libzmq: Message validity is checked in the runtime
| [Tuesday 26 April 2011] [12:19:31] <CIA-75>	libzmq: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/eppUbE
| [Tuesday 26 April 2011] [12:19:33] <CIA-75>	libzmq: 03Martin Sustrik 07master * re0246e3 10/ (55 files in 2 dirs): (log message trimmed)
| [Tuesday 26 April 2011] [12:19:33] <CIA-75>	libzmq: Message-related functionality factored out into msg_t class.
| [Tuesday 26 April 2011] [12:19:33] <CIA-75>	libzmq: This patch addresses serveral issues:
| [Tuesday 26 April 2011] [12:19:33] <CIA-75>	libzmq: 1. It gathers message related functionality scattered over whole
| [Tuesday 26 April 2011] [12:19:33] <CIA-75>	libzmq:  codebase into a single class.
| [Tuesday 26 April 2011] [12:19:33] <CIA-75>	libzmq: 2. It makes zmq_msg_t an opaque datatype. Internals of the class
| [Tuesday 26 April 2011] [12:19:34] <CIA-75>	libzmq:  don't pollute zmq.h header file.
| [Tuesday 26 April 2011] [12:19:36] <mato>	ok, that fixes that
| [Tuesday 26 April 2011] [12:19:37] <CIA-75>	libzmq: 03Martin Sustrik 07master * r10fbc78 10/ src/fq.cpp : 
| [Tuesday 26 April 2011] [12:19:38] <CIA-75>	libzmq: Assert during SUB socket termination fixed.
| [Tuesday 26 April 2011] [12:19:38] <CIA-75>	libzmq: Fair queueing algorithm was checking whether the current pipe
| [Tuesday 26 April 2011] [12:19:38] <CIA-75>	libzmq: is not closed in the middle of reading a multipart message.
| [Tuesday 26 April 2011] [12:19:38] <CIA-75>	libzmq: However, this is OK when the socket is closing down.
| [Tuesday 26 April 2011] [12:19:38] <CIA-75>	libzmq: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/geke69
| [Tuesday 26 April 2011] [12:20:10] <jhawk28>	mato: can you make it only do a single line per commit?
| [Tuesday 26 April 2011] [12:20:59] <mato>	checking...
| [Tuesday 26 April 2011] [12:21:08] <mato>	i've also enabled CIA on the pyzmq repo
| [Tuesday 26 April 2011] [12:21:44] <th>	pieterh: did you have a chance to look into this mixed multipart messages bug (#199) is there anything i can provide to help fixing this.
| [Tuesday 26 April 2011] [12:23:05] <phantomcircuit>	Skaag, yeah that's kind of the point actually, the WORKS FOR ME isn't a solution
| [Tuesday 26 April 2011] [12:24:03] <Skaag>	phantomcircuit: what OS are you compiling on?
| [Tuesday 26 April 2011] [12:24:09] <phantomcircuit>	gentoo
| [Tuesday 26 April 2011] [12:24:12] <Skaag>	oh god
| [Tuesday 26 April 2011] [12:24:27] <phantomcircuit>	yeah terrible
| [Tuesday 26 April 2011] [12:24:30] <Skaag>	your tools are probably too new and too bleeding edge
| [Tuesday 26 April 2011] [12:24:33] <phantomcircuit>	except everything else builds fine
| [Tuesday 26 April 2011] [12:24:59] <Skaag>	can you pastebin the error you get?
| [Tuesday 26 April 2011] [12:25:06] <phantomcircuit>	sure
| [Tuesday 26 April 2011] [12:25:18] <Skaag>	I don't hate gentoo, don't get me wrong
| [Tuesday 26 April 2011] [12:25:21] <Skaag>	please.
| [Tuesday 26 April 2011] [12:25:26] <Skaag>	I actually like it.
| [Tuesday 26 April 2011] [12:25:29] <phantomcircuit>	http://codepad.org/pck6IkFZ
| [Tuesday 26 April 2011] [12:25:53] <Skaag>	However, if I had a dime for every time a gentoo guy complained about something not compiling right... I'd definitely be able to buy a very fancy meal for everybody in this channel.
| [Tuesday 26 April 2011] [12:26:08] <Skaag>	I think it just stems from the fact very few developers test their build process on the latest gentoo.
| [Tuesday 26 April 2011] [12:26:14] <Skaag>	looking at your paste. hold on
| [Tuesday 26 April 2011] [12:26:27] <phantomcircuit>	it's definitely due to libtools version being too new
| [Tuesday 26 April 2011] [12:26:55] <pouete>	Hi all, a little question about the C bindig of mq :) : why cant we reuse a msg that as already been initialized ? 
| [Tuesday 26 April 2011] [12:27:00] <CIA-75>	pyzmq: 03MinRK 07master * r65812f5 10/ README.rst : readme updates re: building pyzmq - http://bit.ly/emga3H
| [Tuesday 26 April 2011] [12:27:02] <CIA-75>	pyzmq: 03MinRK 07master * r80e975d 10/ setup.py : (log message trimmed)
| [Tuesday 26 April 2011] [12:27:02] <CIA-75>	pyzmq: add -lpthread on freebsd
| [Tuesday 26 April 2011] [12:27:02] <CIA-75>	pyzmq: closes gh-101
| [Tuesday 26 April 2011] [12:27:03] <CIA-75>	pyzmq: 03MinRK 07master * r02cc78d 10/ (zmq/tests/test_device.py zmq/tests/test_socket.py): cleanup a few more test sockets. - http://bit.ly/i3YDgw
| [Tuesday 26 April 2011] [12:27:23] <Skaag>	phantomcircuit: you tried to install the older libtools and get it to be used instead?
| [Tuesday 26 April 2011] [12:27:48] <Skaag>	or how about indeed recreating aclocal?
| [Tuesday 26 April 2011] [12:27:52] <CIA-75>	libzmq: 03Martin Sustrik 07master * r5816976 10/ (10 files in 3 dirs): 
| [Tuesday 26 April 2011] [12:27:52] <CIA-75>	libzmq: Message validity is checked in the runtime
| [Tuesday 26 April 2011] [12:27:52] <CIA-75>	libzmq: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/eppUbE
| [Tuesday 26 April 2011] [12:27:52] <CIA-75>	libzmq: 03Martin Sustrik 07master * re0246e3 10/ (55 files in 2 dirs): (log message trimmed)
| [Tuesday 26 April 2011] [12:27:52] <CIA-75>	libzmq: Message-related functionality factored out into msg_t class.
| [Tuesday 26 April 2011] [12:27:52] <CIA-75>	libzmq: This patch addresses serveral issues:
| [Tuesday 26 April 2011] [12:27:53] <CIA-75>	libzmq: 03Martin Sustrik 07master * r10fbc78 10/ src/fq.cpp : (log message trimmed)
| [Tuesday 26 April 2011] [12:27:53] <CIA-75>	libzmq: Assert during SUB socket termination fixed.
| [Tuesday 26 April 2011] [12:27:54] <CIA-75>	libzmq: Fair queueing algorithm was checking whether the current pipe
| [Tuesday 26 April 2011] [12:28:05] <Skaag>	wow lots of activity ;) go martin
| [Tuesday 26 April 2011] [12:28:11] <mato>	no, that's just me testing
| [Tuesday 26 April 2011] [12:28:14] <mato>	sorry for the noise 
| [Tuesday 26 April 2011] [12:28:21] <Skaag>	oh ok
| [Tuesday 26 April 2011] [12:28:28] <Skaag>	I don't mind it
| [Tuesday 26 April 2011] [12:28:37] <mato>	jhawk28: header + first line of log message?
| [Tuesday 26 April 2011] [12:28:55] <CIA-75>	libzmq: 03Martin Sustrik 07master * r5816976 10/ (10 files in 3 dirs): Message validity is checked in the runtime ...
| [Tuesday 26 April 2011] [12:28:58] <CIA-75>	libzmq: 03Martin Sustrik 07master * re0246e3 10/ (55 files in 2 dirs): Message-related functionality factored out into msg_t class. ...
| [Tuesday 26 April 2011] [12:29:04] <CIA-75>	libzmq: 03Martin Sustrik 07master * r10fbc78 10/ src/fq.cpp : Assert during SUB socket termination fixed. ...
| [Tuesday 26 April 2011] [12:29:12] <jhawk28>	pouete: I think its because zmq used zero copy
| [Tuesday 26 April 2011] [12:29:16] <phantomcircuit>	Skaag, yeah let me see though
| [Tuesday 26 April 2011] [12:29:21] <mato>	jhawk28: ok, done, seems to work
| [Tuesday 26 April 2011] [12:29:29] <CIA-75>	jzmq: 03Gonzalo Diethelm 07master * r8755367 10/ src/Socket.cpp : Use send/sendmsg and recv/recvmsg depending on 0MQ's version. - http://bit.ly/eYbbIR
| [Tuesday 26 April 2011] [12:30:07] <phantomcircuit>	Skaag, rebuilding aclocal.m4 didn't help
| [Tuesday 26 April 2011] [12:30:09] <jhawk28>	mato: less noisy, better
| [Tuesday 26 April 2011] [12:30:19] <mato>	it's watching libzmq, rbzmq, pyzmq, jzmq, clrzmq
| [Tuesday 26 April 2011] [12:30:33] <Skaag>	phantomcircuit: I guess you need to install the older tools as well. They shouldn't interfere with the new ones, don't worry.
| [Tuesday 26 April 2011] [12:30:34] <mato>	anyone else wants some repos watched, shout
| [Tuesday 26 April 2011] [12:31:00] <phantomcircuit>	Skaag, yeah i guess
| [Tuesday 26 April 2011] [12:31:06] <phantomcircuit>	i hate autotools :|
| [Tuesday 26 April 2011] [12:31:33] <Skaag>	wish I could be more helpful... 
| [Tuesday 26 April 2011] [12:31:48] <phantomcircuit>	Skaag, which version do you have
| [Tuesday 26 April 2011] [12:31:52] <phantomcircuit>	might save me some time...
| [Tuesday 26 April 2011] [12:32:02] <mato>	"only" 237 messages unread in zeromq-dev :-(
| [Tuesday 26 April 2011] [12:32:14] <mato>	time to go, see you all later
| [Tuesday 26 April 2011] [12:32:17] <jhawk28>	pouete: there was some talk on the mailing list about it
| [Tuesday 26 April 2011] [12:33:25] <pouete>	jhawk28: kay, do you remember the approximate date ?
| [Tuesday 26 April 2011] [12:33:31] <pouete>	i mean month ?
| [Tuesday 26 April 2011] [12:33:34] <Skaag>	phantomcircuit: will tell you, sec.
| [Tuesday 26 April 2011] [12:33:35] <jhawk28>	was just this month
| [Tuesday 26 April 2011] [12:34:06] <Skaag>	ltmain.sh (GNU libtool) 2.2.6b
| [Tuesday 26 April 2011] [12:34:12] <Skaag>	automake (GNU automake) 1.11.1
| [Tuesday 26 April 2011] [12:34:22] <Skaag>	autoconf (GNU Autoconf) 2.65
| [Tuesday 26 April 2011] [12:34:23] <phantomcircuit>	weird i've got 2.2.10
| [Tuesday 26 April 2011] [12:34:35] <Skaag>	yah, too new I guess
| [Tuesday 26 April 2011] [12:34:38] <phantomcircuit>	you'd think that minor minor versions would be compatible :|
| [Tuesday 26 April 2011] [12:34:48] <phantomcircuit>	yay gnu :/
| [Tuesday 26 April 2011] [12:34:50] <Skaag>	Agree with you 100% - definitely not proper!
| [Tuesday 26 April 2011] [12:35:08] <Skaag>	you'd think any 2.2.x would play nice
| [Tuesday 26 April 2011] [12:35:24] <pouete>	jhawk28: cheers :) http://www.zeromq.org/blog:zero-copy anyway, is this paper still right ?
| [Tuesday 26 April 2011] [12:36:19] <jhawk28>	pouete: not sure, I haven't had much experience with C
| [Tuesday 26 April 2011] [12:36:56] <phantomcircuit>	lol sadly this box is hilariously slow
| [Tuesday 26 April 2011] [12:36:59] <phantomcircuit>	gogo pentium 4
| [Tuesday 26 April 2011] [12:37:05] <phantomcircuit>	compile like the wind!
| [Tuesday 26 April 2011] [12:37:19] <Skaag>	lol! pentium 4!!!
| [Tuesday 26 April 2011] [12:37:21] <phantomcircuit>	sigh
| [Tuesday 26 April 2011] [12:37:27] <Skaag>	:)
| [Tuesday 26 April 2011] [12:37:47] <Skaag>	I'm all for recycling and stuff, but this is actually worse for the environment...
| [Tuesday 26 April 2011] [12:37:50] <Skaag>	;-)
| [Tuesday 26 April 2011] [12:39:27] <phantomcircuit>	sigh
| [Tuesday 26 April 2011] [12:39:36] <phantomcircuit>	there isn't another libtools package
| [Tuesday 26 April 2011] [12:39:48] <phantomcircuit>	there are higher versions but not lower
| [Tuesday 26 April 2011] [12:39:51] <phantomcircuit>	facepalm
| [Tuesday 26 April 2011] [12:42:12] <pouete>	jhawk28: who could give me the info ?
| [Tuesday 26 April 2011] [12:42:33] <jhawk28>	pieterh or sustrik at least
| [Tuesday 26 April 2011] [12:42:47] <pouete>	thank you very much :) 
| [Tuesday 26 April 2011] [12:43:47] <jhawk28>	pouete: I think you need to clone the data before sending it
| [Tuesday 26 April 2011] [12:44:01] <jhawk28>	in order to send it multiple times
| [Tuesday 26 April 2011] [12:48:59] <phantomcircuit>	this is like a bad joke or something
| [Tuesday 26 April 2011] [12:49:37] <pouete>	jhawk28: what i want to do is to loadbalance one pusher that receive data on different pullers that will process the data. 
| [Tuesday 26 April 2011] [12:51:26] <jhawk28>	pouete: so, kind of the worker pattern?
| [Tuesday 26 April 2011] [12:51:38] <pouete>	worker pattern ?
| [Tuesday 26 April 2011] [12:52:08] <jhawk28>	http://www.rabbitmq.com/tutorials/tutorial-two-python.html
| [Tuesday 26 April 2011] [12:52:21] <jhawk28>	see the picture
| [Tuesday 26 April 2011] [12:52:37] <pouete>	yes, its this :)
| [Tuesday 26 April 2011] [12:52:41] <jhawk28>	http://zguide.zeromq.org/page:all#Divide-and-Conquer
| [Tuesday 26 April 2011] [12:53:03] <pouete>	yep thats it
| [Tuesday 26 April 2011] [12:53:24] <jhawk28>	thats the ZMQ way
| [Tuesday 26 April 2011] [12:54:00] <pouete>	okay, i take a look at that , thanks 
| [Tuesday 26 April 2011] [13:00:10] <pieterh>	pouete: that zerocopy paper is accurate for libzmq/2.x
| [Tuesday 26 April 2011] [13:35:52] <Seta00>	!setinfo <jhawk28> thats the ZMQ way
| [Tuesday 26 April 2011] [13:35:53] <Seta00>	;)
| [Tuesday 26 April 2011] [13:48:09] <pieterh>	jhawk28: pouete: actually http://zguide.zeromq.org/page:all#Service-Oriented-Reliable-Queuing-Majordomo-Pattern is closer to the Rabbit example
| [Tuesday 26 April 2011] [13:48:44] <pieterh>	but if it's just load balancing to workers, one PUSH and multiple PULL sockets is enough
| [Tuesday 26 April 2011] [13:48:48] <jhawk28>	he wasnt wanting reliable
| [Tuesday 26 April 2011] [13:49:04] <pieterh>	jhawk28: yeah, wasn't sure
| [Tuesday 26 April 2011] [13:49:11] <phantomcircuit>	hmm
| [Tuesday 26 April 2011] [13:49:13] <jhawk28>	I just remembered the rabbit picture
| [Tuesday 26 April 2011] [14:00:09] <pieterh>	guido_g: you around?
| [Tuesday 26 April 2011] [14:08:06] <mikko>	pieterh: renamed
| [Tuesday 26 April 2011] [14:37:22] <guido_g>	pieterh: yes
| [Tuesday 26 April 2011] [14:37:28] <guido_g>	what's up?
| [Tuesday 26 April 2011] [14:50:29] <pieterh>	mikko: thanks!
| [Tuesday 26 April 2011] [14:50:51] <pieterh>	guido_g: sorry, and excuse this ignorance, but I was wondering what parts of 0MQ you contributed to
| [Tuesday 26 April 2011] [14:56:42] <guido_g>	the first tests
| [Tuesday 26 April 2011] [14:57:15] <guido_g>	and a patch
| [Tuesday 26 April 2011] [14:57:20] <guido_g>	afair
| [Tuesday 26 April 2011] [14:57:48] <guido_g>	is this of any importance?
| [Tuesday 26 April 2011] [14:58:30] <guido_g>	do i get a better chair at the conf?
| [Tuesday 26 April 2011] [15:20:29] <pieterh>	guido_g: (/me is distracted), do you consider yourself a core developer?
| [Tuesday 26 April 2011] [15:20:54] <pieterh>	it's to add to the conference page, to indicate to visitors more or less who's who
| [Tuesday 26 April 2011] [15:21:05] <pieterh>	you get the best chair even without asking
| [Tuesday 26 April 2011] [15:24:30] <guido_g>	pieterh: no, i'm not a core dev
| [Tuesday 26 April 2011] [15:25:13] <pieterh>	guido_g: ok
| [Tuesday 26 April 2011] [17:32:39] <mikko>	pieterh: are people arriving on 9th ?
| [Tuesday 26 April 2011] [17:32:44] <mikko>	MAy
| [Tuesday 26 April 2011] [18:29:03] <iAmTheDave>	wait, there's a conference?
| [Tuesday 26 April 2011] [18:29:09] 	 * iAmTheDave is totally not paying attention
| [Tuesday 26 April 2011] [18:44:35] <th>	oh there was a patch for message atomicity for pub/sub? is that related to #199 which is about atomocity of xreq/xrep?
| [Tuesday 26 April 2011] [19:05:58] <lt_schmidt_jr>	Where is the May 9 conference  going to be held?
| [Tuesday 26 April 2011] [19:57:00] <zedas>	ok i got an odd question:  if I have an XREP socket, and I've got the idents from them, and those idents are the autogenerated ones, AND i store them to disk:  can i just read them back and then send replies after a crash?
| [Tuesday 26 April 2011] [20:09:39] <zedas>	ah ok it works but you have to wait a bit for the clients to reconnect
| [Wednesday 27 April 2011] [03:56:38] <pieterh>	hi mikko
| [Wednesday 27 April 2011] [03:57:43] <guido_g>	good morning mq
| [Wednesday 27 April 2011] [04:00:14] <pieterh>	hi guido_g!
| [Wednesday 27 April 2011] [04:00:30] <guido_g>	good morning pieterh
| [Wednesday 27 April 2011] [04:15:39] <mikko>	pieterh: hi
| [Wednesday 27 April 2011] [04:15:46] <pieterh>	hi mikko!
| [Wednesday 27 April 2011] [04:15:55] <pieterh>	you asked if people were arriving on the 9th
| [Wednesday 27 April 2011] [04:15:57] <pieterh>	some are, yes
| [Wednesday 27 April 2011] [04:15:59] <mikko>	pieterh: i'll book tickets 9th May - 10t Mayh
| [Wednesday 27 April 2011] [04:16:02] <pieterh>	cool!
| [Wednesday 27 April 2011] [04:16:09] <mikko>	coming back from holidays today
| [Wednesday 27 April 2011] [04:16:24] <pieterh>	I think it's sane to hold a meetup on the evening of the 9th
| [Wednesday 27 April 2011] [04:16:43] <mikko>	can i stay at yours?
| [Wednesday 27 April 2011] [04:16:49] <mikko>	or should i book a hotel?
| [Wednesday 27 April 2011] [04:16:50] <pieterh>	for sure
| [Wednesday 27 April 2011] [04:16:55] <pieterh>	stay with us, mato will also be here
| [Wednesday 27 April 2011] [04:16:59] <mikko>	thanks
| [Wednesday 27 April 2011] [04:17:06] <pieterh>	lots of space, maybe bring a sleeping bag if you have one
| [Wednesday 27 April 2011] [04:17:26] <mikko>	i can buy one, it probably has use later
| [Wednesday 27 April 2011] [04:17:39] <mikko>	i gotta run, check out soon
| [Wednesday 27 April 2011] [04:17:39] <pieterh>	nah, don't waste money for that
| [Wednesday 27 April 2011] [04:17:41] <pieterh>	cyl
| [Wednesday 27 April 2011] [04:17:46] <mikko>	ill be back around GMT 22:00
| [Wednesday 27 April 2011] [04:17:52] <pieterh>	:)
| [Wednesday 27 April 2011] [04:17:59] <pieterh>	I'll be drumming
| [Wednesday 27 April 2011] [04:20:26] <guido_g>	pieterh: you're writing an app? like app in "app for a phone"?
| [Wednesday 27 April 2011] [04:20:33] <pieterh>	hmm, yes
| [Wednesday 27 April 2011] [04:20:34] <guido_g>	just saw that tweet of yours
| [Wednesday 27 April 2011] [04:20:42] <guido_g>	ahh i see
| [Wednesday 27 April 2011] [04:20:53] <pieterh>	its a prototype for a new mobile concept
| [Wednesday 27 April 2011] [04:20:58] <pieterh>	has nothing to do with zeromq sadly
| [Wednesday 27 April 2011] [04:21:17] <guido_g>	hehe
| [Wednesday 27 April 2011] [04:21:25] <pieterh>	except perhaps to convince me we need an HTTP bridge sooner rather than later
| [Wednesday 27 April 2011] [04:21:59] <guido_g>	or real operating systems for mobile devices
| [Wednesday 27 April 2011] [04:22:34] <pieterh>	as compared to Linux? :)
| [Wednesday 27 April 2011] [04:22:50] <guido_g>	no, of course not
| [Wednesday 27 April 2011] [04:23:24] <pieterh>	The problem isn't really running the 0MQ stack on Android or iOS
| [Wednesday 27 April 2011] [04:23:35] <guido_g>	but this tiny things like s60 or ios will not last any longer
| [Wednesday 27 April 2011] [04:23:40] <pieterh>	for sure
| [Wednesday 27 April 2011] [04:23:41] <guido_g>	as ia said, real oses
| [Wednesday 27 April 2011] [04:23:46] <guido_g>	omg
| [Wednesday 27 April 2011] [04:23:47] <pieterh>	there is only one real os, eventually
| [Wednesday 27 April 2011] [04:23:58] <guido_g>	let me type this again: as i said
| [Wednesday 27 April 2011] [04:24:14] <guido_g>	at only one open source
| [Wednesday 27 April 2011] [04:24:32] <pieterh>	the obvious sometimes takes a long time to happen
| [Wednesday 27 April 2011] [04:24:33] <guido_g>	i don't know how close the windows mobile os is to the real windows
| [Wednesday 27 April 2011] [04:25:03] <pieterh>	real windows is barely a real OS by modern standards
| [Wednesday 27 April 2011] [04:25:17] <guido_g>	*sigh*
| [Wednesday 27 April 2011] [04:25:28] <guido_g>	but we do have a build process for it :)
| [Wednesday 27 April 2011] [04:25:39] <guido_g>	we := mq 
| [Wednesday 27 April 2011] [04:25:42] <pieterh>	indeed
| [Wednesday 27 April 2011] [04:25:56] <pieterh>	problem isn't building 0MQ on random mobile device
| [Wednesday 27 April 2011] [04:26:07] <pieterh>	they're all real computers with what approaches an OS
| [Wednesday 27 April 2011] [04:26:09] <Guthur>	windows 8 will probably be that 'real OS' on a mobile
| [Wednesday 27 April 2011] [04:26:23] <pieterh>	problem is running unsecured protocols over the Internet
| [Wednesday 27 April 2011] [04:26:30] <Guthur>	it will have support for the ARM arch
| [Wednesday 27 April 2011] [04:26:45] <guido_g>	Guthur: so there two then, and one if them is free and (nearly) open source :)
| [Wednesday 27 April 2011] [04:27:16] <Guthur>	guido_g: Android?
| [Wednesday 27 April 2011] [04:27:39] <guido_g>	Guthur: jepp
| [Wednesday 27 April 2011] [04:27:51] <guido_g>	i consider my beloved maemo dead
| [Wednesday 27 April 2011] [04:27:55] <Guthur>	Google got slapped with a fine recently in Texas, for patent infringement related to the linux kernel
| [Wednesday 27 April 2011] [04:28:07] <guido_g>	and meego is a still born
| [Wednesday 27 April 2011] [04:28:08] <Guthur>	$5m
| [Wednesday 27 April 2011] [04:28:26] <guido_g>	yeah, read about it
| [Wednesday 27 April 2011] [04:29:21] <pieterh>	Google are big enough to actually take on the patent system, when they get annoyed enough
| [Wednesday 27 April 2011] [04:29:51] <Guthur>	this patent is so bogus, it might actually wake people up to the fact it is very broken
| [Wednesday 27 April 2011] [04:30:19] <pieterh>	Guthur: you think if it wasn't a bogus patent, that'd be better somehow? :)
| [Wednesday 27 April 2011] [04:30:48] <Guthur>	well...
| [Wednesday 27 April 2011] [04:31:02] <pieterh>	Imagine some firm comes up with a really valid patent for 'sockets that automatically fan in and fan out'
| [Wednesday 27 April 2011] [04:31:10] <pieterh>	filed in 1999 or somesuch
| [Wednesday 27 April 2011] [04:31:39] <Guthur>	did you file it, hehe
| [Wednesday 27 April 2011] [04:31:41] <pieterh>	sold to some random holding firm... never turned into software...
| [Wednesday 27 April 2011] [04:31:51] <pieterh>	no, I'm pointing out that it's not about good vs. bogus patents
| [Wednesday 27 April 2011] [04:32:26] 	 * pieterh should not start on software patents... really bad idea
| [Wednesday 27 April 2011] [04:32:58] <guido_g>	like software and idea patents
| [Wednesday 27 April 2011] [04:32:59] <Guthur>	hehe yeah I've read on the net that your have been quite vocal in the past against the current system
| [Wednesday 27 April 2011] [04:33:01] <pieterh>	if you want a history lesson in all that is bad about patents: http://www.digitalmajority.org/forum/t-27067/how-the-french-turned-exclusive-privilege-into-property
| [Wednesday 27 April 2011] [04:33:20] <pieterh>	this is one reason 0MQ is not a conventional commercial closed-source product
| [Wednesday 27 April 2011] [05:09:08] <djc>	pieterh: as for http bridge, I have some code that does 0MQ-to-WebSockets
| [Wednesday 27 April 2011] [05:09:35] <pieterh>	djc: that's interesting, have you published it?
| [Wednesday 27 April 2011] [05:09:56] <djc>	not yet
| [Wednesday 27 April 2011] [05:10:13] <djc>	it's written in Python and it contains some idiosyncrasies specific to the content we're sending over 0MQ
| [Wednesday 27 April 2011] [05:10:21] <djc>	but I could probably publish it somewhere
| [Wednesday 27 April 2011] [05:10:26] <pieterh>	so its not a generic bridge
| [Wednesday 27 April 2011] [05:10:32] <djc>	most of it is generic
| [Wednesday 27 April 2011] [05:10:59] <djc>	but we're sending binary content over zeromq, so you need something to translate to JSON (at least, that seemed easier than parsing the binary stuff in JS)
| [Wednesday 27 April 2011] [05:11:09] <pieterh>	for sure
| [Wednesday 27 April 2011] [05:11:26] <pieterh>	what version of websockets?
| [Wednesday 27 April 2011] [05:11:40] <djc>	whatever Fx4 and currently stable Chrome support
| [Wednesday 27 April 2011] [05:11:50] <pieterh>	ok, the old hixie spec
| [Wednesday 27 April 2011] [05:11:55] <djc>	(you need to tweak a flag in Fx4 because this is the not-so-secure version)
| [Wednesday 27 April 2011] [05:12:20] <djc>	we're actually using this in production, but of course I'll update it as soon as the browsers implement the new stuff
| [Wednesday 27 April 2011] [05:12:22] <pieterh>	there's a topic page on the wiki, it'd be useful to post something about your websockets bridge IMO
| [Wednesday 27 April 2011] [05:12:23] <guido_g>	q: isn't websockets just plain tcp after the http upgrade?
| [Wednesday 27 April 2011] [05:12:28] <pieterh>	guido_g: hah
| [Wednesday 27 April 2011] [05:12:34] <djc>	guido_g: it's not
| [Wednesday 27 April 2011] [05:12:38] <djc>	pieterh: where's that at?
| [Wednesday 27 April 2011] [05:12:49] 	 * pieterh checks... should be listed on the zero.mq page
| [Wednesday 27 April 2011] [05:13:04] <guido_g>	i'm puzzled
| [Wednesday 27 April 2011] [05:13:06] <pieterh>	yeah http://www.zeromq.org/topics:0mq-over-http
| [Wednesday 27 April 2011] [05:13:15] <pieterh>	guido_g: it does, at the least, framing
| [Wednesday 27 April 2011] [05:13:47] <pieterh>	when it went through the ietf mangler it got a lot more complex
| [Wednesday 27 April 2011] [05:14:19] <guido_g>	ok
| [Wednesday 27 April 2011] [05:14:28] <guido_g>	will look it up later then
| [Wednesday 27 April 2011] [05:14:57] <guido_g>	really thought that after the upgrade the os socket be used as a plain tcp socket
| [Wednesday 27 April 2011] [05:15:04] <djc>	no
| [Wednesday 27 April 2011] [05:15:19] <djc>	messages are delineated by one-byte header and footer
| [Wednesday 27 April 2011] [05:15:35] <djc>	so it's a stream of messages, not a stream of bytes
| [Wednesday 27 April 2011] [05:15:47] <djc>	which is probably easier to handle in JS and also maps quite well to 0MQ
| [Wednesday 27 April 2011] [05:15:56] <guido_g>	i do not dare to ask why :)
| [Wednesday 27 April 2011] [05:19:41] <djc>	ugh, the wikidot thing confuses me
| [Wednesday 27 April 2011] [05:20:11] <djc>	I made an account and am trying to comment on the 0mq-over-http page, but it keeps saying "or Sign in as Wikidot user", even though I activated my account and signed in
| [Wednesday 27 April 2011] [05:21:17] <guido_g>	cookies
| [Wednesday 27 April 2011] [05:21:30] <guido_g>	incl. third party ones :(
| [Wednesday 27 April 2011] [05:22:43] <djc>	I deleted all cookies on zeromq-containing domains and the same thing still happens
| [Wednesday 27 April 2011] [05:23:45] <guido_g>	you've to allow cookies to be set
| [Wednesday 27 April 2011] [05:29:12] <pieterh>	djc: ... are you behind some firewall or proxy?
| [Wednesday 27 April 2011] [05:31:41] <djc>	nope
| [Wednesday 27 April 2011] [05:31:57] <djc>	there, wrote an account-less comment
| [Wednesday 27 April 2011] [05:37:37] <pieterh>	djc: what browser are you using?
| [Wednesday 27 April 2011] [05:39:00] <djc>	Fx4
| [Wednesday 27 April 2011] [05:42:04] <pieterh>	Fx? Firefox?
| [Wednesday 27 April 2011] [05:42:43] <pieterh>	so it's doing something (paranoid/silly/too clever) with cookies
| [Wednesday 27 April 2011] [05:53:20] <guido_g>	firefox 4 works, just logged in
| [Wednesday 27 April 2011] [07:13:02] <pieterh>	sustrik: ping?
| [Wednesday 27 April 2011] [14:53:49] <Dantman>	Are there any api docs for jzmq?
| [Wednesday 27 April 2011] [15:34:42] <staylor>	is there a way to get a source ip address of a socket in zeromq given it's id?  DEALER->ROUTER where router side requests the id of DEALER
| [Wednesday 27 April 2011] [17:10:03] <Guthur>	Dantman, there is some example code in the guide
| [Wednesday 27 April 2011] [17:10:10] <Guthur>	staylor, not that I am aware of
| [Wednesday 27 April 2011] [17:11:08] <Dantman>	I know there is the guide, some example code, and zmq docs... but it's a little awkward to read zmq docs to look at the api and try to translate that to Java
| [Wednesday 27 April 2011] [17:11:21] <Dantman>	...especially since I don't do C
| [Wednesday 27 April 2011] [17:54:46] <mikko>	good evening
| [Wednesday 27 April 2011] [17:59:35] <mikko>	pieterh: eurostar booked
| [Wednesday 27 April 2011] [18:20:01] <staylor>	I asked earlier, wondering if anyone knows if it's possible to get the remote ip address of a socket?  ie: a router socket getting the ip address of the dealer socket connected to it?
| [Wednesday 27 April 2011] [18:26:53] <mikko>	staylor: nope, you have to embed this information into messages if you need it
| [Wednesday 27 April 2011] [18:44:53] <staylor>	mikko: yeah encoding it into the message isn't really possible since the dealer could be behind a nat
| [Thursday 28 April 2011] [00:59:06] <Dantman>	I'm writing something with Java and jzmq. I'm doing a NIO server handling multiple client sockets and using NIO's Selector API. From there, I want to send and receive messages over ZMQ to other things. Is jzmq compatible with NIO's Selector API? Can I register a ZMQ socket with a Selector and incorporate waiting for incoming messages on the ZMQ socket into the .select();, or do I have to create a separate thread just to efficiently send and receive stuff 
| [Thursday 28 April 2011] [00:59:06] <Dantman>	over ZMQ.
| [Thursday 28 April 2011] [00:59:38] <guido_g>	yes
| [Thursday 28 April 2011] [00:59:52] <guido_g>	see getsockopt and ZMQ_FD
| [Thursday 28 April 2011] [01:00:14] <guido_g>	you get a fd you can use w/ poll/nio or whatever
| [Thursday 28 April 2011] [01:01:00] <Dantman>	Java NIO... I mean, is it part of the JZMQ java api...
| [Thursday 28 April 2011] [01:01:22] <Dantman>	There's no API docs I can see to check
| [Thursday 28 April 2011] [01:02:27] <guido_g>	http://api.zeromq.org/2-1:zmq-getsockopt
| [Thursday 28 April 2011] [01:05:07] <jer>	only a couple days into 0mq, but it is one of the coolest libraries i've used. to play, i rewrote some code, and managed to quite literally, throw away several hundred lines of code (and the program was already just over a thousand lines of code... 40%, gone.)
| [Thursday 28 April 2011] [01:07:17] <Dantman>	I get that the C api has the ability to return a descriptor that can be polled or selected, so it's possible for jzmq to do it. But I need to know if jzmq has implemented that into a java.nio.channels.SelectableChannel that I can use in conjunction with a java.nio.channels.Selector.
| [Thursday 28 April 2011] [01:08:23] <guido_g>	if you can't figure it out, ask the author of the binding
| [Thursday 28 April 2011] [03:00:22] <Steve-o>	goijfgdgdfg.
| [Thursday 28 April 2011] [03:02:04] <guido_g>	Steve-o: get more coffee :)
| [Thursday 28 April 2011] [03:02:22] <Steve-o>	That's what I"m thinking of MSVC 100
| [Thursday 28 April 2011] [03:02:38] <Steve-o>	They've introduced a tonne of socket option definitions which aren't used anywhere
| [Thursday 28 April 2011] [03:03:31] <Steve-o>	And still a typo on the current page listing IPPROTO socket options
| [Thursday 28 April 2011] [03:04:22] <guido_g>	poor Steve-o 
| [Thursday 28 April 2011] [03:04:32] <Steve-o>	oh well, done now, release early, release often.
| [Thursday 28 April 2011] [03:04:50] <Steve-o>	Looks like Martin & Pieter are having similar fun with recent 0mq builds too though :D
| [Thursday 28 April 2011] [03:07:46] <Steve-o>	aren't there a few low latency events in NYC this week?
| [Thursday 28 April 2011] [03:08:45] <Steve-o>	"The Business and Technology of Low-Latency Trading" at Crowne Plaza
| [Thursday 28 April 2011] [03:09:14] <Steve-o>	looks like I miss everything by a week again
| [Thursday 28 April 2011] [04:28:03] <mikko>	Steve-o: hi
| [Thursday 28 April 2011] [04:28:10] <Steve-o>	yo
| [Thursday 28 April 2011] [04:28:19] <mikko>	how was your travelling?
| [Thursday 28 April 2011] [04:29:20] <Steve-o>	not stopped, back to nyc next monday
| [Thursday 28 April 2011] [04:29:51] <mikko>	did i send you an email about mac os x build failure --with-pgm?
| [Thursday 28 April 2011] [04:30:03] <mikko>	i think i was supposed to send but i dont know if i ever did
| [Thursday 28 April 2011] [04:30:03] <Steve-o>	I have something, one moment
| [Thursday 28 April 2011] [04:30:14] <mikko>	i was in lisbon for holidays
| [Thursday 28 April 2011] [04:30:16] <mikko>	lovely city
| [Thursday 28 April 2011] [04:30:26] <Steve-o>	https://github.com/zeromq/libzmq/issues/193 fixed already
| [Thursday 28 April 2011] [04:30:43] <Steve-o>	Lisbon?  You like it?  It's bit of a dump
| [Thursday 28 April 2011] [04:30:47] <mikko>	ah, nice
| [Thursday 28 April 2011] [04:30:55] <mikko>	yeah, it's not nice and shiny
| [Thursday 28 April 2011] [04:31:01] <mikko>	but a lot of character
| [Thursday 28 April 2011] [04:31:12] <Steve-o>	Zurich is funny, everyone is so old
| [Thursday 28 April 2011] [04:31:14] <mikko>	i shot five rolls of film there
| [Thursday 28 April 2011] [04:31:40] <Steve-o>	we had a nice apartment over looking the lake though, v. nice
| [Thursday 28 April 2011] [04:31:58] <mikko>	i've never been to zurich
| [Thursday 28 April 2011] [04:32:10] <Steve-o>	nice chocolate :-)
| [Thursday 28 April 2011] [04:32:24] <mikko>	i would love to go to south of france at some point
| [Thursday 28 April 2011] [04:32:38] <Steve-o>	st tropez?
| [Thursday 28 April 2011] [04:32:42] <Steve-o>	or just abouts
| [Thursday 28 April 2011] [04:32:54] <mikko>	just anywhere there
| [Thursday 28 April 2011] [04:33:30] <Steve-o>	I see a lot of Brits on HGTV moving to South of France
| [Thursday 28 April 2011] [04:33:50] <Steve-o>	good weather and large residences
| [Thursday 28 April 2011] [04:34:39] <Steve-o>	so I'll be NYC for near 3 months
| [Thursday 28 April 2011] [04:34:48] <Steve-o>	waiting for Green Card interview
| [Thursday 28 April 2011] [04:37:18] <Steve-o>	I've switched my lab off, so that might be entertaining for future updates.
| [Thursday 28 April 2011] [04:38:00] <mikko>	hehe, where is the lab located at?
| [Thursday 28 April 2011] [04:38:11] <Steve-o>	in my office in HK
| [Thursday 28 April 2011] [04:38:26] <mikko>	if we wanted to add PGM testing to daily builds what would that need?
| [Thursday 28 April 2011] [04:38:29] <Steve-o>	although there is a OS X server still running with the source tree on
| [Thursday 28 April 2011] [04:38:30] <mikko>	what kind of gear?
| [Thursday 28 April 2011] [04:39:28] <Steve-o>	bare minimum normally for anything but performance testing
| [Thursday 28 April 2011] [04:39:37] <Steve-o>	you can get away with really crappy gear
| [Thursday 28 April 2011] [04:40:08] <Steve-o>	after all White Barn made PGM in the days of Sparc 1 & 2's
| [Thursday 28 April 2011] [04:40:09] <mikko>	i'm just looking for 'does it work' kind of testing
| [Thursday 28 April 2011] [04:40:45] <mikko>	currently i got two HP DL380s running VMWare ESXi with some amount of virtual machines
| [Thursday 28 April 2011] [04:43:39] <Steve-o>	the unit tests are trivial to run on the command line for any hardware
| [Thursday 28 April 2011] [04:43:50] <Steve-o>	the network tests are not so straight forward
| [Thursday 28 April 2011] [04:44:21] <Steve-o>	I ideally want to rewrite them in 0MQ + Python or something higher level
| [Thursday 28 April 2011] [04:44:42] <Steve-o>	make a great GSoC project :/
| [Thursday 28 April 2011] [04:47:14] <Steve-o>	Ideally you could say 0MQ should be able to mock the PGM socket interface
| [Thursday 28 April 2011] [04:57:03] <mikko>	hmm
| [Thursday 28 April 2011] [04:57:22] <mikko>	do the network tests work with vmware virtual networking?
| [Thursday 28 April 2011] [04:59:44] <Steve-o>	with ESX or VirtualBox would work
| [Thursday 28 April 2011] [05:00:10] <Steve-o>	the older VMware VM's don't support multicast NICs
| [Thursday 28 April 2011] [05:01:45] <Steve-o>	just going to pop out to find an IP-KVM device, later
| [Thursday 28 April 2011] [05:02:04] <mikko>	later
| [Thursday 28 April 2011] [07:58:10] <th>	pieterh: could you give me a pointer where to find the "patch for 191" which applies to 2.1? i'm adapting my testcase to get more information then.
| [Thursday 28 April 2011] [07:58:35] <pieterh>	th: hi
| [Thursday 28 April 2011] [07:58:56] <pieterh>	sustrik posted the patch to the mailing list
| [Thursday 28 April 2011] [07:59:15] <pieterh>	i've also attached it to the issue in github
| [Thursday 28 April 2011] [07:59:37] <pieterh>	in this gist repo: https://gist.github.com/946025
| [Thursday 28 April 2011] [08:00:06] <pieterh>	however... it doesn't apply to 2.1 cleanly...
| [Thursday 28 April 2011] [08:00:24] <pieterh>	give me a second and I'll make a patch for 2.1 and include it in that gist
| [Thursday 28 April 2011] [08:00:34] <th>	pieterh: great thanks!
| [Thursday 28 April 2011] [08:01:14] <th>	pieterh: i did not reduce it to a C testcase (yet) because i could imagine that the issue is within the C++ "bindings"
| [Thursday 28 April 2011] [08:01:27] <th>	some destructing done in incorrect order or something...
| [Thursday 28 April 2011] [08:02:07] <pieterh>	th: could be, esp. since the error always hits the same place afaics
| [Thursday 28 April 2011] [08:02:16] <pieterh>	i've added that patch to the gist repo
| [Thursday 28 April 2011] [08:03:16] <th>	pieterh: the main difference with your patch is that the CLIENT dies while in my testcase the server dies
| [Thursday 28 April 2011] [08:04:23] <th>	2-1/issue191.patch got it
| [Thursday 28 April 2011] [08:05:01] <th>	pieterh: is it a good idea to use 2.1.6 for this?
| [Thursday 28 April 2011] [08:05:12] <pieterh>	th: should not make any difference
| [Thursday 28 April 2011] [08:05:16] <th>	ok
| [Thursday 28 April 2011] [08:08:59] <th>	pieterh: i can not confirm any change with that patch. i dont get the error you get, it's still the server failing because of intermixed message.
| [Thursday 28 April 2011] [08:09:25] <pieterh>	right...
| [Thursday 28 April 2011] [08:09:40] <pieterh>	anyhow the patch didn't fix issue 191, it caused 0MQ to die nastily
| [Thursday 28 April 2011] [08:09:42] <th>	pieterh: which 2.1 revision did you use?
| [Thursday 28 April 2011] [08:10:06] <th>	pieterh: it does not die here
| [Thursday 28 April 2011] [08:10:11] <th>	pieterh: at least not nastily
| [Thursday 28 April 2011] [08:10:20] <pieterh>	indeed, neither with me, then it's probably a different issue than 191
| [Thursday 28 April 2011] [08:10:27] <pieterh>	i'd suggest the best step is to make a C test case that reproduces the problem on 2.1
| [Thursday 28 April 2011] [08:10:33] <th>	ok
| [Thursday 28 April 2011] [08:10:37] <pieterh>	the revision is not going to be significant, anything recent
| [Thursday 28 April 2011] [08:10:40] <th>	and testing 3.0 i assume
| [Thursday 28 April 2011] [08:10:54] <pieterh>	and then, a second test case for 3.0 (it'll be very similar)
| [Thursday 28 April 2011] [08:11:05] <pieterh>	don't use zmq_device, that's gone in 3.0...
| [Thursday 28 April 2011] [08:11:30] <th>	pieterh: i didn't
| [Thursday 28 April 2011] [08:11:41] <th>	pieterh: must be indirectly
| [Thursday 28 April 2011] [08:12:54] <pieterh>	ah, perhaps a side effect of using the C++ binding
| [Thursday 28 April 2011] [08:13:01] <pieterh>	it was a compile error, not a link error
| [Thursday 28 April 2011] [08:13:20] <th>	pieterh: i only use {context,socket,message}_t and bind,connect,recv,send,{get,set}sockopt
| [Thursday 28 April 2011] [08:13:36] <th>	ahh ok
| [Thursday 28 April 2011] [08:14:01] <th>	removing C++ first then, i'd say. to know where it comes from.
| [Thursday 28 April 2011] [08:15:03] <pieterh>	yes
| [Thursday 28 April 2011] [08:50:17] <th>	reference manual says about zmq_msg_init_data: "MQ shall take ownership of the supplied buffer", is that only true when a deallocation function pointer is given?
| [Thursday 28 April 2011] [08:51:00] <mato>	th: you mean "... is not given" ?
| [Thursday 28 April 2011] [08:51:17] <pieterh>	mato: when give, I think...
| [Thursday 28 April 2011] [08:51:20] <pieterh>	*given
| [Thursday 28 April 2011] [08:51:21] <th>	there are examples in the guide passing a constant static string, and NULL,NULL for ffn,hint
| [Thursday 28 April 2011] [08:51:34] <th>	it makes no sense to giveownership to a string like that
| [Thursday 28 April 2011] [08:51:52] <mato>	it does what you think it does :-)
| [Thursday 28 April 2011] [08:52:21] <th>	mato: so it does not call any free() unless i pass a function pointer to a free()?
| [Thursday 28 April 2011] [08:52:36] <mato>	th: actually good question
| [Thursday 28 April 2011] [08:52:36] <pieterh>	th: those examples should absolutely not be using the _data method, I'm changing that
| [Thursday 28 April 2011] [08:52:47] <th>	????????zmq_msg_init_data?(&reply,?"World",?5,?NULL,?NULL);
| [Thursday 28 April 2011] [08:52:51] <th>	talking od that code
| [Thursday 28 April 2011] [08:52:58] <pieterh>	yes, hwserver & hwclient
| [Thursday 28 April 2011] [08:52:59] <th>	sorry for the broken paste
| [Thursday 28 April 2011] [08:53:23] <mato>	th: if no ffn is passed, none is called
| [Thursday 28 April 2011] [08:53:40] <pieterh>	mato: problem is that statement in the man page, "shall take ownership..."
| [Thursday 28 April 2011] [08:53:44] <th>	pieterh: i'm looking fo replacemtn of `zmq::message_t m(len); memcpy((void *) m.data(), buffer, len);`
| [Thursday 28 April 2011] [08:53:50] <mato>	pieterh: yes, it's wrong
| [Thursday 28 April 2011] [08:54:30] 	 * mato needs to give the manual some TLC
| [Thursday 28 April 2011] [08:54:30] <th>	mato: then i think the reference manual should be changed to make that clear. it says "shall take ownership"
| [Thursday 28 April 2011] [08:54:33] <pieterh>	th: in C, zmq_msg_init_size() and then memcpy into zmq_msg_data()
| [Thursday 28 April 2011] [08:54:47] <th>	perhaps it should more hint to the user to keep that buffer valid until message's EOL
| [Thursday 28 April 2011] [08:55:08] <mato>	yes
| [Thursday 28 April 2011] [08:55:17] <mato>	if you don't supply a ffn then the buffer must stay around forever
| [Thursday 28 April 2011] [08:55:23] <mato>	or at least until context deinit anyway
| [Thursday 28 April 2011] [08:55:41] <th>	mato: _context_ deinit? not message deinit?
| [Thursday 28 April 2011] [08:56:20] <mato>	th: technically message deinit, but due to internal refcounting that's probably not a 100% safe approach
| [Thursday 28 April 2011] [08:56:20] <th>	(which should be msg_close, i assume)
| [Thursday 28 April 2011] [08:56:24] <mato>	yes
| [Thursday 28 April 2011] [08:56:57] <th>	pieterh: is it wrong in the examples because it is easily used incorrectly?
| [Thursday 28 April 2011] [08:57:01] <th>	pieterh: or is there another reason?
| [Thursday 28 April 2011] [08:57:39] <pieterh>	th: the init_data method is rather poorly named
| [Thursday 28 April 2011] [08:57:57] <pieterh>	it should be called zmq_msg_zero_copy_do_not_use_unless_you_know_what_its_for()
| [Thursday 28 April 2011] [08:58:06] <mato>	:-)
| [Thursday 28 April 2011] [08:58:06] <th>	pieterh: should it be named something like zmq_msg_set_data_reference?
| [Thursday 28 April 2011] [08:58:13] <pieterh>	and my error in using that in hello world methods
| [Thursday 28 April 2011] [08:58:13] <th>	ahh ok
| [Thursday 28 April 2011] [08:58:26] <pieterh>	highly misleading, but I also got caught by the name originally
| [Thursday 28 April 2011] [09:10:59] <Steve-o>	pieterh: updated PGM github issues in libzmq/zeromq2-1, mainly appear to be cases resolved in newer versions.  One wishlist issue for improved logging.
| [Thursday 28 April 2011] [09:11:21] <pieterh>	neat, thanks
| [Thursday 28 April 2011] [09:12:37] <pieterh>	Steve-o: btw I put Miru on http://www.zeromq.org/intro:commercial-support
| [Thursday 28 April 2011] [09:12:52] <pieterh>	can you take a look and see if the description is OK for you?
| [Thursday 28 April 2011] [09:14:47] <Steve-o>	Cool, I have a Chinese site too:  http://./
| [Thursday 28 April 2011] [09:15:52] <Steve-o>	Well, Traditional Chinese anyway.
| [Thursday 28 April 2011] [09:16:37] <pieterh>	Steve-o: afaik zeromq.org isn't available in mainland China... :-/
| [Thursday 28 April 2011] [09:18:27] <Steve-o>	Works in Hong Kong & Taiwan though
| [Thursday 28 April 2011] [09:20:41] <pieterh>	It could be neat to make a Chinese zeromq.org site... but not using Wikidot then
| [Thursday 28 April 2011] [09:21:08] <Steve-o>	is it just .org blocked?
| [Thursday 28 April 2011] [09:21:16] <pieterh>	Steve-o: it's Wikidot that's blocked
| [Thursday 28 April 2011] [09:21:28] <pieterh>	the IP address, afaik
| [Thursday 28 April 2011] [09:21:29] <Steve-o>	oh, as a wiki, igi
| [Thursday 28 April 2011] [09:21:47] <ezl>	having trouble installing zeromq on ubuntu 10.10
| [Thursday 28 April 2011] [09:21:48] <ezl>	 uuid-dev : Depends: libuuid1 (= 2.17.2-0ubuntu1) but 2.17.2-0ubuntu1.10.10.2 is to be installed
| [Thursday 28 April 2011] [09:21:48] <ezl>	E: Broken packages
| [Thursday 28 April 2011] [09:21:50] <ezl>	But installing uuid-dev shows I have the most recent version
| [Thursday 28 April 2011] [09:22:11] <Steve-o>	pieterh: all wikis are blocked, including similar bits of Google
| [Thursday 28 April 2011] [09:22:46] <ezl>	any ideas?
| [Thursday 28 April 2011] [09:23:03] <pieterh>	Steve-o: I assume the Chinese govt hates the Internet
| [Thursday 28 April 2011] [09:23:23] <pieterh>	ezl: no ideas immediately, haven't hit this on Ubuntu 10.10 myself
| [Thursday 28 April 2011] [09:23:54] <pieterh>	ezl: when do you get this error message?
| [Thursday 28 April 2011] [09:24:13] <ezl>	.configure
| [Thursday 28 April 2011] [09:24:24] <pieterh>	what 0MQ package did you download?
| [Thursday 28 April 2011] [09:24:51] <ezl>	2.1.6 off the website this morning
| [Thursday 28 April 2011] [09:25:03] <pieterh>	let me just try that for sanity's sake...
| [Thursday 28 April 2011] [09:25:16] <ezl>	thanks pieterh
| [Thursday 28 April 2011] [09:25:38] <ezl>	checking for uuid_generate in -luuid... no
| [Thursday 28 April 2011] [09:25:38] <ezl>	configure: error: cannot link with -luuid, install uuid-dev.
| [Thursday 28 April 2011] [09:25:50] <ezl>	was the 2 lines of output before configure quit
| [Thursday 28 April 2011] [09:26:07] <pieterh>	ezl: so I have uuid-dev installed
| [Thursday 28 April 2011] [09:26:16] <pieterh>	it sounds like you don't have it installed (or properly)
| [Thursday 28 April 2011] [09:27:16] <ezl>	ah. right, i don't. when trying to install uuiddev, i get the error message above about Depending on libuuid1
| [Thursday 28 April 2011] [09:27:31] <ezl>	"Depends: libuuid1 (= 2.17.2-0ubuntu1) but 2.17.2-0ubuntu1.10.10.2 is to be installed"
| [Thursday 28 April 2011] [09:27:42] <ezl>	which when i try to install linuuid1, it says that i have the latest version
| [Thursday 28 April 2011] [09:27:44] 	 * pieterh does a quick google...
| [Thursday 28 April 2011] [09:28:07] <ezl>	libuuid1 is already the newest version.
| [Thursday 28 April 2011] [09:28:10] <pieterh>	ezl: I know there was a Ubuntu update today
| [Thursday 28 April 2011] [09:28:17] <pieterh>	maybe you're halfway through an update?
| [Thursday 28 April 2011] [09:28:18] <ezl>	(sorry, I did google it too, just didn't get very far)
| [Thursday 28 April 2011] [09:28:29] <ezl>	(also pretty new to ubuntu, so it could be just a newb problem)
| [Thursday 28 April 2011] [09:29:02] <pieterh>	try sudo apt-get dist-upgrade
| [Thursday 28 April 2011] [09:29:12] <pieterh>	all the way through, including restart if needed
| [Thursday 28 April 2011] [09:29:33] <ezl>	ok thanks trying
| [Thursday 28 April 2011] [09:29:34] <pieterh>	it's something aberrant because this normally /always/ works on Ubuntu
| [Thursday 28 April 2011] [09:30:05] 	 * pieterh just triple-checked, 2.1.6 configures fine, have libuuid1 and uuid-dev installed
| [Thursday 28 April 2011] [09:30:15] <ezl>	dist upgrade: 0 upgraded, 0 newly installed, 0 to remove and 0 not upgraded.
| [Thursday 28 April 2011] [09:30:21] <ezl>	yeah my problem seems to be libuuid1
| [Thursday 28 April 2011] [09:30:39] <mikko>	ezl: can you put config.log to gist.github.com?
| [Thursday 28 April 2011] [09:30:48] <pieterh>	hmm, try uninstalling that, and then installing uuid-dev
| [Thursday 28 April 2011] [09:30:51] <ezl>	says its installed, but then when i try to install uuid-dev, it complains that i don't have libuuid1
| [Thursday 28 April 2011] [09:30:53] <ezl>	ok
| [Thursday 28 April 2011] [09:30:57] <ezl>	mikko ok also
| [Thursday 28 April 2011] [09:32:09] <ezl>	mikko: pieterh: config.log >> https://gist.github.com/946344
| [Thursday 28 April 2011] [09:32:54] <mikko>	ezl: can you do ldconfig -p | grep uuid
| [Thursday 28 April 2011] [09:34:18] <ezl>	mikko: ok
| [Thursday 28 April 2011] [09:34:59] <ezl>	mikko: libuuid.so.1 (libc6) => /lib/libuuid.so.1
| [Thursday 28 April 2011] [09:35:14] 	 * ezl googles ldconfig as well
| [Thursday 28 April 2011] [09:35:55] <ezl>	piterh: as per your recommendation also tried to uninstall, but didn't go smoothly
| [Thursday 28 April 2011] [09:35:55] <ezl>	https://gist.github.com/946352
| [Thursday 28 April 2011] [09:38:24] <mikko>	ezl: looks like you have it
| [Thursday 28 April 2011] [09:39:47] <mikko>	interesting
| [Thursday 28 April 2011] [09:39:52] <ezl>	mikko: yes, ubuntu thinks i have it, but then when i try to install uuid-dev, it says it can't because it needs libuuid1
| [Thursday 28 April 2011] [09:39:59] <mikko>	you also need /usr/lib/libuuid.so
| [Thursday 28 April 2011] [09:40:12] <ezl>	"Depends: libuuid1 (= 2.17.2-0ubuntu1) but 2.17.2-0ubuntu1.10.10.2 is to be installed"
| [Thursday 28 April 2011] [09:40:17] <ezl>	sounds sort of like a version problem
| [Thursday 28 April 2011] [09:40:27] <ezl>	but i can't decipher what that error means
| [Thursday 28 April 2011] [09:42:55] <ezl>	what are ".so" and ".so.1" files?
| [Thursday 28 April 2011] [09:43:00] <ezl>	(linux newb)
| [Thursday 28 April 2011] [09:52:18] <mikko>	ezl: i think thats the so version
| [Thursday 28 April 2011] [09:52:44] <mikko>	it sounds like ubuntu has messed up the dependencies
| [Thursday 28 April 2011] [09:54:48] <ezl>	how can i force ubuntu to reinstall it?
| [Thursday 28 April 2011] [09:55:02] <macson_g>	hi, I have problem with app crashing on SIGPIPE on exit in 2.1.6. Can anyone help?
| [Thursday 28 April 2011] [09:56:30] <macson_g>	The backtrace is: zmq::mailbox_t::send, zmq::object_t::send_stop, zmq::ctx_t::terminate
| [Thursday 28 April 2011] [09:59:23] <mikko>	ezl: i don't know
| [Thursday 28 April 2011] [09:59:31] <pieterh>	ezl: remove it, reinstall it
| [Thursday 28 April 2011] [09:59:48] <ezl>	https://gist.github.com/946352 -- not letting me remove it
| [Thursday 28 April 2011] [09:59:53] <pieterh>	oh...
| [Thursday 28 April 2011] [10:00:04] 	 * pieterh didn't read the history
| [Thursday 28 April 2011] [10:00:20] <ezl>	I'm getting that E: broken packages thing on anyhting surrounding libuuid1
| [Thursday 28 April 2011] [10:00:31] <ezl>	not sure what that means, but "broken" sounds suboptimal
| [Thursday 28 April 2011] [10:00:33] <ezl>	=P
| [Thursday 28 April 2011] [10:01:03] <pieterh>	ezl: try 'apt-get clean', 'purge', 'update'
| [Thursday 28 April 2011] [10:02:06] <pieterh>	ezl: actually, looks like you have quite a mess
| [Thursday 28 April 2011] [10:02:48] <ezl>	haha awesome.
| [Thursday 28 April 2011] [10:03:00] <ezl>	i really haven't done much on my machine, not sure how i got into this
| [Thursday 28 April 2011] [10:03:31] <ezl>	(i did clean, purge, update: libuuid1 is still installed, tried to uninstall, wouldn't allow again.)
| [Thursday 28 April 2011] [10:06:33] <headzone>	this is why it pays to use debian
| [Thursday 28 April 2011] [10:12:49] <pieterh>	ezl: if you haven't done much on the system, reinstall it...
| [Thursday 28 April 2011] [10:13:36] <pieterh>	headzone: I thought Ubuntu was basically debian, especially its package management layers...
| [Thursday 28 April 2011] [12:32:25] <ParadoxG>	#gitready
| [Thursday 28 April 2011] [12:32:47] <ParadoxG>	sorry, wrong command
| [Thursday 28 April 2011] [12:40:31] <mabes>	does anyone know if zdevice (https://github.com/imatix/zdevices/tree/master/c/generic) is available as binaries/in a deb package?
| [Thursday 28 April 2011] [13:08:36] <pieterh>	mabes: nope, it's not
| [Thursday 28 April 2011] [13:08:53] <pieterh>	it's a single C source file...
| [Thursday 28 April 2011] [13:10:20] <mabes>	pieterh: I know, but my sysadmins like packages :)  I'll have to look into creating our own I suppose. thakns
| [Thursday 28 April 2011] [13:10:42] <pieterh>	mabes: you're using zdevice?
| [Thursday 28 April 2011] [13:13:24] <mabes>	pieterh: well, no, not yet... I'm investigating zeromq and I need to use ROUTER/DEALER (XREQ/XRES).  One process is in ruby and the other Java.  Anyways, I need to use the zmq_queue and it seemed like using zdevice was the easiest way to do that from a deployment standpoint.  I am new to zeromq so I may be wrong though- if so please clue me in...
| [Thursday 28 April 2011] [13:14:30] <pieterh>	mabes: the simplest for you would be to rewrite zdevice in Java or Ruby IMO
| [Thursday 28 April 2011] [13:14:43] <pieterh>	it's a very simple app, mostly concerned with reading configuration data
| [Thursday 28 April 2011] [13:14:48] <pieterh>	that should be trivial in Ruby
| [Thursday 28 April 2011] [13:15:00] <pieterh>	all the hard work is done by the zmq_device() call at the end
| [Thursday 28 April 2011] [13:15:32] <pieterh>	before you do this you need to read the Guide and understand how devices work
| [Thursday 28 April 2011] [13:16:00] <pieterh>	there is a detailed explanation of what zmq_device() actually does, and how to roll your own
| [Thursday 28 April 2011] [13:16:13] <mabes>	pieterh: Yeah, I read the guide and I actually already translated the c msgqueu example that uses zmq_queue into ruby already.
| [Thursday 28 April 2011] [13:16:25] <pieterh>	that's what you want to use then
| [Thursday 28 April 2011] [13:17:19] <mabes>	pieterh: ok, thanks for the advice.  I'll go ahead with that approach then.
| [Thursday 28 April 2011] [13:17:24] <pieterh>	np
| [Thursday 28 April 2011] [14:52:50] <DanielFriesen>	I'm trying to figure out what type of ZMQ sockets I should use; Say I have 1 A and a number of B's. There are multiple requests A can send messages to B for. Individual requests can be sent to any B, but all subsequent messages related to that same request have to be sent to the same B as the first one, so push/pull is out. That sounds like req/rep but A needs to be able to send multiple messages to B and B needs to be able to make multiple replies,
| [Thursday 28 April 2011] [14:52:50] <DanielFriesen>	 they can't wait for a message from the other before sending the next, so req/rep seams to be out.
| [Thursday 28 April 2011] [14:57:33] <guido_g>	sounds like a job for xreq/xrep sockets
| [Thursday 28 April 2011] [14:57:43] <mikko>	XREP/XREQ with multipart messages
| [Thursday 28 April 2011] [14:57:55] <guido_g>	why multipart?
| [Thursday 28 April 2011] [14:58:08] <guido_g>	multipart is just one message send in one go
| [Thursday 28 April 2011] [14:58:24] <mikko>	depends on how far apart the messages are i guess
| [Thursday 28 April 2011] [14:58:33] <guido_g>	see
| [Thursday 28 April 2011] [14:59:20] <guido_g>	DanielFriesen: The Guide has a chapter on lru routing, just replace the lru algo with one that fits your need
| [Thursday 28 April 2011] [14:59:40] <DanielFriesen>	Ok, I thought about XREP/XREQ but didn't know if it was usable as the primary pair
| [Thursday 28 April 2011] [15:00:02] <guido_g>	first of all, check if you really need stateful routing
| [Thursday 28 April 2011] [15:00:14] <guido_g>	most of the time it's not worth the trouble
| [Thursday 28 April 2011] [15:02:14] <DanielFriesen>	I'm writing a NIO http server, sending requests to workers doing the request handling... request initiation/headers, and body are separate messages... naturally the body of a http request needs to go to the same worker as the headers went to...
| [Thursday 28 April 2011] [15:02:51] <guido_g>	a request should be a single message
| [Thursday 28 April 2011] [15:02:56] <mikko>	DanielFriesen: have you checked mongrel2 as well?
| [Thursday 28 April 2011] [15:03:09] <DanielFriesen>	That would destroy streaming capability
| [Thursday 28 April 2011] [15:03:13] <guido_g>	as mikko pointed out, you might use multipart messages
| [Thursday 28 April 2011] [15:03:16] <mikko>	guido_g: not necessarily assuming request has large body
| [Thursday 28 April 2011] [15:03:41] <DanielFriesen>	When I saw how mongrel2 was explained in that video I shuddered...
| [Thursday 28 April 2011] [15:04:21] <guido_g>	some of us have the same feeling when seeing the average java software...
| [Thursday 28 April 2011] [15:04:54] 	 * DanielFriesen is using Java and yet isn't using Java...
| [Thursday 28 April 2011] [15:05:11] <guido_g>	which is the only way to use java :)
| [Thursday 28 April 2011] [15:06:15] 	 * DanielFriesen is using Rhino... Using ES5/JS1.{7,8}...
| [Thursday 28 April 2011] [15:06:38] <guido_g>	whatever that might be
| [Thursday 28 April 2011] [15:06:43] <DanielFriesen>	JavaScript
| [Thursday 28 April 2011] [15:06:58] <DanielFriesen>	;) cept much cleaner
| [Thursday 28 April 2011] [15:07:21] <guido_g>	back to streaming
| [Thursday 28 April 2011] [15:08:07] <guido_g>	if you have content to stream, why partiition it into discrete messages?
| [Thursday 28 April 2011] [15:09:53] <DanielFriesen>	Open up a new socket for each connection?
| [Thursday 28 April 2011] [15:10:22] <guido_g>	no, thinking about where to get the streams content and why
| [Thursday 28 April 2011] [15:11:05] <guido_g>	streaming and request/reply are not different enough to treat them differently
| [Thursday 28 April 2011] [15:11:34] <guido_g>	ups
| [Thursday 28 April 2011] [15:11:43] <guido_g>	i ment: streaming and request/reply are different enough to treat them differently
| [Thursday 28 April 2011] [17:23:56] <chuck>	hello
| [Thursday 28 April 2011] [17:24:02] <chuck>	I'm reading through the guide, and I'm sort of confused
| [Thursday 28 April 2011] [17:24:40] <chuck>	if I want to be able to start multiple "worker" processes for a backend service and I want to contact those processes from my web application server, which socket types should I be looking at?
| [Thursday 28 April 2011] [17:31:02] <mikko>	chuck: what kind of communication are you looking at?
| [Thursday 28 April 2011] [17:31:06] <mikko>	fire and forget ?
| [Thursday 28 April 2011] [17:32:19] <chuck>	mikko, yeah
| [Thursday 28 April 2011] [17:32:49] <mikko>	then you want PUSH on the web application server
| [Thursday 28 April 2011] [17:32:53] <mikko>	and pull on backend
| [Thursday 28 April 2011] [17:33:18] <chuck>	mikko, what would it be for a synchronous response?
| [Thursday 28 April 2011] [17:36:28] <mikko>	XREP/XREQ
| [Thursday 28 April 2011] [17:36:38] <chuck>	hrm
| [Thursday 28 April 2011] [17:37:51] <chuck>	mikko, i'm just trying to think how I would set this up
| [Thursday 28 April 2011] [17:38:40] <chuck>	mikko, so I would create a server that binds, and then multiple worker clients that would connect to that
| [Thursday 28 April 2011] [17:38:49] <chuck>	and then somehow I would contact the server from my web application?
| [Thursday 28 April 2011] [17:39:33] <mikko>	yes
| [Thursday 28 April 2011] [17:42:56] <chuck>	mikko, is that the most straightforward way? it seems like the server middleman should be cut out somehow but I can't see how it would be
| [Thursday 28 April 2011] [17:45:11] <mikko>	chuck: sorry, i don't follow
| [Thursday 28 April 2011] [17:45:16] <mikko>	chuck: what server middleman?
| [Thursday 28 April 2011] [17:46:13] <mikko>	you mean "Architecture of a Single Cluster" in guide?
| [Thursday 28 April 2011] [17:48:53] <chuck>	mikko, well I mean, what I'm describing is this: web application -> backend server -> backend clients
| [Thursday 28 April 2011] [17:49:19] <chuck>	is there any way to talk directly to the clients while retaining the ability to add and remove clients from the "cluster" easily?
| [Thursday 28 April 2011] [17:49:23] <mikko>	the middleman is usually there to do routing
| [Thursday 28 April 2011] [17:49:50] <chuck>	right, and if that's necessary that's fine, i'm just not familiar with the ins and outs of every socket type so i'm not sure if it's necessary or not
| [Thursday 28 April 2011] [17:49:51] <mikko>	if there are multiple web application servers they have no idea of amount of work each backend server has
| [Thursday 28 April 2011] [17:50:18] <mikko>	the backend server in your scenario would probably do the distribution of work
| [Thursday 28 April 2011] [17:50:42] <mikko>	you can connect to backend clients directly from the web application as well
| [Thursday 28 April 2011] [17:50:46] <chuck>	can't zeromq balance the messages it sends to each backend client?
| [Thursday 28 April 2011] [17:51:24] <mikko>	it can, but if you have 10 web application servers they all balance differently
| [Thursday 28 April 2011] [17:51:46] <mikko>	you can end end up into situation where 10 servers all send work to 1 worker
| [Thursday 28 April 2011] [17:52:18] <mikko>	unless you syncronise the state across all web application servers
| [Thursday 28 April 2011] [17:52:22] <chuck>	hmm
| [Thursday 28 April 2011] [17:52:35] <mikko>	or implement a protocol where you ask each backend client how much work they have
| [Thursday 28 April 2011] [17:53:02] <mikko>	the middleman in your case would maintain LRU list of work distribution
| [Thursday 28 April 2011] [17:53:11] <mikko>	or any other algo suitable for the scenario
| [Thursday 28 April 2011] [17:58:23] <mikko>	let's say in the simplest scenario you would connect the web application server directly to backend client
| [Thursday 28 April 2011] [17:58:45] <mikko>	now when you add another backend client and connect to that as well zeromq will do round robin balancing between those backend clients
| [Thursday 28 April 2011] [17:59:06] <mikko>	now when you add another web application server and connect to those backend workers it will do round-robin as well
| [Thursday 28 April 2011] [17:59:23] <mikko>	so work goes to 1 then 2, 1, 2, 1, 2 etc
| [Thursday 28 April 2011] [17:59:31] <chuck>	but the downside is that I can't just start backend clients and call it a day, i have to add their IP addresses to the code my web app server is running?
| [Thursday 28 April 2011] [17:59:47] <mikko>	if you got two web application servers your work might go 1, 1, 2 ,2, 1,1, 2,2,
| [Thursday 28 April 2011] [18:00:04] <mikko>	due to naive round-robin and no state between the two web application servers
| [Thursday 28 April 2011] [18:00:12] <mikko>	so let's say you add third web application server
| [Thursday 28 April 2011] [18:00:31] <mikko>	worst case is: 1,1,1,2,2,2,1,1,1,2,2,2
| [Thursday 28 April 2011] [18:00:48] <chuck>	oh okay, i gotcha
| [Thursday 28 April 2011] [18:01:07] <chuck>	mikko, so this is what i should be doing? https://github.com/imatix/zguide/raw/master/images/fig49.png
| [Thursday 28 April 2011] [18:01:11] <chuck>	the single cluster architecture
| [Thursday 28 April 2011] [18:01:11] <mikko>	the middleman allows you to do a bit more intellegient routing
| [Thursday 28 April 2011] [18:01:45] <chuck>	right
| [Thursday 28 April 2011] [18:01:51] <mikko>	chuck: it all depends on the application as well
| [Thursday 28 April 2011] [18:03:11] <chuck>	mikko, so in that single cluster architecture, on the worker side, the broker would be PUSHing and the workers would be PULLing, right? how would the "clients" (in that diagram) contact the broker?
| [Thursday 28 April 2011] [18:03:58] <mikko>	the broker would be XREP and clients would be XREQ
| [Thursday 28 April 2011] [18:04:09] <mikko>	XREP = ROUTER
| [Thursday 28 April 2011] [18:04:14] <mikko>	in that diagram
| [Thursday 28 April 2011] [18:05:04] <chuck>	oh so that's not a PUSH/PULL thing?
| [Thursday 28 April 2011] [18:07:10] <mikko>	nope
| [Thursday 28 April 2011] [18:07:18] <mikko>	XREP/XREQ allow to do custom routing
| [Thursday 28 April 2011] [18:07:33] <mikko>	take a look at "A Request-Reply Message Broker"
| [Thursday 28 April 2011] [18:15:39] <chuck>	mikko, will do
| [Thursday 28 April 2011] [18:15:55] <chuck>	i've got to go, thanks for the help though, I understand it much better now. not all the way, but I'm getting there ;)
| [Thursday 28 April 2011] [18:17:17] <mikko>	cool
| [Thursday 28 April 2011] [18:52:36] <Bartzy>	Hi
| [Thursday 28 April 2011] [18:52:42] <Bartzy>	I currently have a PHP app that uses system sometimes to call executables that create images on-the-fly... I now need to separate the app to scale: one or more machines for PHP (FastCGI) only, and one ore more machines for running the executables.. 
| [Thursday 28 April 2011] [18:52:51] <Bartzy>	I also want to be able to use multiple "executing" servers.
| [Thursday 28 April 2011] [19:10:32] <DanielFriesen>	'Assertion failed: rc == 0 (zmq_connecter.cpp:48)' caused by accidentally using "tcp://localhost:localhost", should I report that as a bug somewhere?
| [Thursday 28 April 2011] [19:51:09] <mikko>	Bartzy: what is the actual question?
| [Thursday 28 April 2011] [19:51:22] <mikko>	DanielFriesen: yes, if you don't mind opening an issue
| [Thursday 28 April 2011] [19:52:50] <Bartzy>	mikko: I was wondering if zeromq is suitable for that... I'll need to script some custom code for the 'server' part, right?
| [Thursday 28 April 2011] [19:53:26] <mikko>	Bartzy: yes, that is correct
| [Thursday 28 April 2011] [19:53:42] <Bartzy>	Also, if I do a script in PHP or python for example.. and it does a while (true) { ... } and receives data from ZMQ inside the while... What happens if this server-script dies for some reason ?  
| [Thursday 28 April 2011] [19:53:51] <Bartzy>	I'm responsible to re-spawn it, right ?
| [Thursday 28 April 2011] [19:53:56] <mikko>	Bartzy: yes
| [Thursday 28 April 2011] [19:54:08] <Bartzy>	mikko: OK, what's considered a good way to do that ?
| [Thursday 28 April 2011] [19:54:17] <mikko>	for respawning the scripts?
| [Thursday 28 April 2011] [19:54:22] <Bartzy>	yes
| [Thursday 28 April 2011] [19:54:32] <Bartzy>	inittab? monit?
| [Thursday 28 April 2011] [19:54:43] <mikko>	if it's calling an external executable i would create a simple C or C++ daemon
| [Thursday 28 April 2011] [19:55:07] <Bartzy>	and what will spawn that C daemon if it dies ? :)
| [Thursday 28 April 2011] [19:55:27] <mikko>	http://dustin.github.com/2010/02/28/running-processes.html
| [Thursday 28 April 2011] [19:55:33] <mikko>	that is a very good read on running processes
| [Thursday 28 April 2011] [19:55:52] <Bartzy>	Thank you very much.
| [Thursday 28 April 2011] [19:56:12] <Bartzy>	I'm viewing "ZeroMQ is the Answer" talk... I'm quite amazed how easy it is
| [Thursday 28 April 2011] [19:56:27] <mikko>	it's a very good talk
| [Thursday 28 April 2011] [19:56:30] <Bartzy>	But I'm wondering if Gearman would be more suitable because I wouldn't have to code the 'server' 
| [Thursday 28 April 2011] [19:56:33] <mikko>	i saw it in london
| [Thursday 28 April 2011] [19:56:48] <mikko>	with gearman you still need the script running
| [Thursday 28 April 2011] [19:56:51] <Bartzy>	yes it's very straight-forward...
| [Thursday 28 April 2011] [19:57:09] <Bartzy>	So what's different between gearman and zmq ?
| [Thursday 28 April 2011] [19:57:33] <mikko>	zeromq is more oriented towards messaging
| [Thursday 28 April 2011] [19:57:43] <mikko>	where as gearman is more strictly for distributing work
| [Thursday 28 April 2011] [19:59:10] <Bartzy>	messaging, how ? What do you mean by messaging ?
| [Thursday 28 April 2011] [19:59:25] <Bartzy>	Because most of the talk I'm viewing is about distributing work in zmq
| [Thursday 28 April 2011] [19:59:55] <mikko>	with zeromq the core concept is sending a message using different patterns
| [Thursday 28 April 2011] [20:00:15] <mikko>	the message is arbitrary binary blob, a string or a number or anything
| [Thursday 28 April 2011] [20:00:28] <mikko>	but you are always guaranteed to receive the whole message on the other side
| [Thursday 28 April 2011] [20:00:35] <mikko>	the message can be instruction to call a function
| [Thursday 28 April 2011] [20:00:40] <mikko>	or execute a binary 
| [Thursday 28 April 2011] [20:00:47] <mikko>	but this is something you need to implement
| [Thursday 28 April 2011] [20:01:01] <mikko>	think about for example this chatroom
| [Thursday 28 April 2011] [20:01:07] <mikko>	we send messages all the time
| [Thursday 28 April 2011] [20:01:22] <mikko>	you might even say that we publish messages in topic #zeromq
| [Thursday 28 April 2011] [20:01:35] <mikko>	another channel is would be another topic
| [Thursday 28 April 2011] [20:01:40] <mikko>	(using pub-sub terms)
| [Thursday 28 April 2011] [20:02:17] <Bartzy>	instruction to execute a binary = string that I need to check for and do something with it, right ?
| [Thursday 28 April 2011] [20:02:35] <mikko>	yes
| [Thursday 28 April 2011] [20:02:35] <Bartzy>	yes I understand the pub-sub thingie
| [Thursday 28 April 2011] [20:02:46] <Bartzy>	OK.. and how can I send a file using zeromq ?
| [Thursday 28 April 2011] [20:02:51] <Bartzy>	is that recommended ?
| [Thursday 28 April 2011] [20:03:12] <Bartzy>	or there are better ways to store a file and send it (via NFS)? 
| [Thursday 28 April 2011] [20:03:22] <mikko>	send it where?
| [Thursday 28 April 2011] [20:05:45] <Bartzy>	I have a web server, a client sends a request to do an effect on a URL
| [Thursday 28 April 2011] [20:05:50] <Guthur>	Bartzy, working through at least some of the Guide examples can be could to get things to 'click'
| [Thursday 28 April 2011] [20:06:18] <Guthur>	could/good
| [Thursday 28 April 2011] [20:07:25] <Bartzy>	PHP downloads that image from the URL, then it needs to store it some where the image-processing server(s) can access it. It then should send a message or a 'job' for one of the image-processing servers to do a specific effect on that image, and save the new image in a place where the web server can access (for the user to fetch)
| [Thursday 28 April 2011] [20:08:12] <Bartzy>	So storing the original image and the result image - is that best done via NFS , or using ZMQ to get the original image to the image-processing server(s), and then the result image from the image-processing servers to the web server through ZMQ as well...
| [Thursday 28 April 2011] [20:10:28] <DanielFriesen>	*sigh* I wish there was a nice api like ZMQ that also supported udp messages that could just be dropped, or would let you know what connections it still has alive...
| [Thursday 28 April 2011] [21:43:52] <josh_>	hi
| [Thursday 28 April 2011] [21:44:10] <josh_>	does anyone know how to do a rate limit on a pull socket
| [Friday 29 April 2011] [01:21:35] <CIA-75>	libzmq: 03Martin Sustrik 07master * rb2eb84f 10/ (4 files): Substantial simplification of uuid_t ...
| [Friday 29 April 2011] [01:30:07] <CIA-75>	libzmq: 03Martin Sustrik 07master * r96213d5 10/ src/tcp_connecter.cpp : WSAENETUNREACH is a valid networking error ...
| [Friday 29 April 2011] [06:35:01] <travlr>	mikko: ping
| [Friday 29 April 2011] [06:35:11] <mikko>	yes?
| [Friday 29 April 2011] [06:35:54] <travlr>	hey, i'm just now working with the irc log you gave me.. what time zone are you in?
| [Friday 29 April 2011] [06:36:09] <mikko>	BST at the moment
| [Friday 29 April 2011] [06:36:19] <travlr>	the log is in bst then?
| [Friday 29 April 2011] [06:36:31] <mikko>	well, it is during summer
| [Friday 29 April 2011] [06:37:03] <travlr>	the dates are from march 2010 to i think it was november 2010
| [Friday 29 April 2011] [06:38:08] <mikko>	London will stay on BST until Sunday, October 30, 2011 at 2:00 AM
| [Friday 29 April 2011] [06:38:09] <mikko>	when clocks are moved to Sunday, October 30, 2011 at 01:00:00 GMT
| [Friday 29 April 2011] [06:38:39] <travlr>	ok, i think i only need july anyway, so thank you.
| [Friday 29 April 2011] [06:39:10] <mikko>	no problem
| [Friday 29 April 2011] [10:16:44] <ianbarber>	pieterh: here?
| [Friday 29 April 2011] [10:16:56] <pieterh>	ianbarber: aye
| [Friday 29 April 2011] [10:16:58] <ianbarber>	jujst
| [Friday 29 April 2011] [10:17:04] <ianbarber>	argh, typing fail :)
| [Friday 29 April 2011] [10:17:06] <pieterh>	:)
| [Friday 29 April 2011] [10:17:12] <ianbarber>	just looking at the titanic pattern
| [Friday 29 April 2011] [10:17:21] <ianbarber>	titanic.c, titanic_request
| [Friday 29 April 2011] [10:17:31] <ianbarber>	creates a zmsg reply, but doesn't seem to send it: 
| [Friday 29 April 2011] [10:17:37] <ianbarber>	//NowsendUUIDbacktoclient
| [Friday 29 April 2011] [10:17:38] <ianbarber>	reply=zmsg_new();
| [Friday 29 April 2011] [10:17:38] <ianbarber>	zmsg_addstr(reply,"200");
| [Friday 29 April 2011] [10:17:38] <ianbarber>	zmsg_addstr(reply,uuid);
| [Friday 29 April 2011] [10:17:38] <ianbarber>	free(uuid);
| [Friday 29 April 2011] [10:17:45] <pieterh>	let me check...
| [Friday 29 April 2011] [10:18:38] <pieterh>	hmm, indeed... 
| [Friday 29 April 2011] [10:19:03] <pieterh>	I must have chopped that out by mistake at some stage, thanks
| [Friday 29 April 2011] [10:21:01] <ianbarber>	cool - i was about to go trawling through zmsg for some magic i was not previously aware of :)
| [Friday 29 April 2011] [10:21:30] <pieterh>	I ported all the examples to libzapi/czmq and presumably didn't retest everything properly
| [Friday 29 April 2011] [10:21:37] <pieterh>	I'll fix this right now
| [Friday 29 April 2011] [10:21:57] <ianbarber>	yeah, easy to do. 
| [Friday 29 April 2011] [10:22:06] <ianbarber>	when you have a tick as well, i sent a pull req for the MDP examples https://github.com/imatix/zguide/pull/53
| [Friday 29 April 2011] [10:22:11] <ianbarber>	(in php)
| [Friday 29 April 2011] [10:22:26] <pieterh>	nice!
| [Friday 29 April 2011] [10:22:51] <pieterh>	the guide is like a kind of complex game, and as you catch up I have to go build new levels...
| [Friday 29 April 2011] [10:23:21] <ianbarber>	hehe
| [Friday 29 April 2011] [10:23:23] <pieterh>	while sustrik busily keeps shifting the foundations so the levels don't remain stable
| [Friday 29 April 2011] [10:24:02] <ianbarber>	got to keep things interesting! :)
| [Friday 29 April 2011] [10:24:08] <pieterh>	yeah
| [Friday 29 April 2011] [10:24:19] <pieterh>	strangely the old code didn't send a reply back either
| [Friday 29 April 2011] [10:24:36] <pieterh>	so this may in fact be wrong, I need to re-read how titanic works in detail
| [Friday 29 April 2011] [10:25:45] <guido_g>	hehehe
| [Friday 29 April 2011] [10:25:47] <guido_g>	sorry
| [Friday 29 April 2011] [10:26:48] <ianbarber>	you know you've got a good spec when it's a better source than the reference implementation though. 
| [Friday 29 April 2011] [10:27:00] <ianbarber>	too many are done the other way around
| [Friday 29 April 2011] [10:27:01] <pieterh>	yeah, that's true
| [Friday 29 April 2011] [10:27:19] 	 * pieterh intensely dislikes specs written off source code
| [Friday 29 April 2011] [10:33:16] <pieterh>	ianbarber: ah, ok, the code was correct
| [Friday 29 April 2011] [10:33:46] <pieterh>	it's my fault for being too clever with the mdwrk API
| [Friday 29 April 2011] [10:34:18] <ianbarber>	ah, i see it's on the next loop
| [Friday 29 April 2011] [10:34:34] <ianbarber>	yep, that makes sense, just missed it before
| [Friday 29 April 2011] [10:34:52] <pieterh>	I wanted to get a single method for 'send-wait-recv' instead of two
| [Friday 29 April 2011] [10:36:06] <pieterh>	I'll comment the code a little better, and maybe change the API later on
| [Friday 29 April 2011] [10:40:10] <ianbarber>	i think a comment should do it, just to avoid confusion
| [Friday 29 April 2011] [10:48:07] <pieterh>	yup, done
| [Friday 29 April 2011] [10:48:12] <pieterh>	publishing a new version now
| [Friday 29 April 2011] [11:02:08] <sustrik>	pieterh: hi
| [Friday 29 April 2011] [11:02:25] <pieterh>	sustrik: hey! how was Moscow?
| [Friday 29 April 2011] [11:02:30] <sustrik>	great
| [Friday 29 April 2011] [11:02:41] <sustrik>	the meetup was in pub
| [Friday 29 April 2011] [11:02:49] <pieterh>	well, no kidding?
| [Friday 29 April 2011] [11:02:49] <sustrik>	so more a drinking event
| [Friday 29 April 2011] [11:03:05] <mato>	when was a meetup *not* a drinking event? :)
| [Friday 29 April 2011] [11:03:13] <sustrik>	true
| [Friday 29 April 2011] [11:03:28] <sustrik>	anyway, want to have a look at issue 191 now?
| [Friday 29 April 2011] [11:03:39] <sustrik>	the backport thing
| [Friday 29 April 2011] [11:03:46] <pieterh>	sustrik: did you find anything?
| [Friday 29 April 2011] [11:03:57] <sustrik>	haven't looked so far
| [Friday 29 April 2011] [11:04:07] <sustrik>	afaiu the problem you've seen doesn't happen anymore
| [Friday 29 April 2011] [11:04:24] <sustrik>	so what's left are the problems with backported version, right?
| [Friday 29 April 2011] [11:04:32] <pieterh>	well, I found 2-3 different issues
| [Friday 29 April 2011] [11:04:41] 	 * sustrik has to catch up
| [Friday 29 April 2011] [11:04:52] <sustrik>	alllin issue 191
| [Friday 29 April 2011] [11:04:56] <pieterh>	sustrik: I made a gist/repo with all the details
| [Friday 29 April 2011] [11:04:56] <sustrik>	right?
| [Friday 29 April 2011] [11:05:01] <pieterh>	yes, 191
| [Friday 29 April 2011] [11:05:12] <sustrik>	all of them in 2.1
| [Friday 29 April 2011] [11:05:18] <pieterh>	afaics 2-1 and 3-0 die with similar problems though in different places
| [Friday 29 April 2011] [11:05:29] <pieterh>	3-0 definitely is not stable after the patch
| [Friday 29 April 2011] [11:05:37] <sustrik>	do we have a test case?
| [Friday 29 April 2011] [11:05:41] <pieterh>	yes yes and yes
| [Friday 29 April 2011] [11:05:47] <sustrik>	great
| [Friday 29 April 2011] [11:05:48] <pieterh>	could you please grab that gist and ready it?
| [Friday 29 April 2011] [11:05:58] <pieterh>	I spent quite some time documenting this, making test cases
| [Friday 29 April 2011] [11:06:03] <pieterh>	*read it
| [Friday 29 April 2011] [11:06:05] <sustrik>	yup
| [Friday 29 April 2011] [11:06:27] <pieterh>	I'm 80% sure if you fix the problem in 3-0 we'll be able to fix 2-1 similarly
| [Friday 29 April 2011] [11:06:44] <pieterh>	for some reason 3-0 is easier to type than 3.0 today...
| [Friday 29 April 2011] [11:08:07] <sustrik>	:)
| [Friday 29 April 2011] [11:08:12] <sustrik>	ok, let me try to reproduce
| [Friday 29 April 2011] [11:08:25] <sustrik>	mato: btw, have you heard of andrew hume?
| [Friday 29 April 2011] [11:08:37] <sustrik>	he've offered to help with man pages
| [Friday 29 April 2011] [11:08:39] <mato>	sustrik: what about him?
| [Friday 29 April 2011] [11:08:44] <th>	pieterh: i have the feeling zmq_msg_data() does not return the pointer to the mp-part of the last zmq_recv, but the data-pointer of a msg that would be received by later calls to zmq_recv (which are already waiting)
| [Friday 29 April 2011] [11:08:48] <mato>	sustrik: oh, yes, i heard from him
| [Friday 29 April 2011] [11:08:51] <sustrik>	goodo
| [Friday 29 April 2011] [11:09:06] <mato>	sustrik: exchanged a couple of emails but nothing concrete has come of it as yet
| [Friday 29 April 2011] [11:09:16] <pieterh>	th: that's unpossible afaik
| [Friday 29 April 2011] [11:09:40] <th>	pieterh: i converted the test case to pure c now. and it happens even with only a single call to ./stress
| [Friday 29 April 2011] [11:10:00] <pieterh>	ok, push your test case somewhere, I'll give it a go
| [Friday 29 April 2011] [11:13:00] <th>	pieterh: i could not make it much smaller, yet. it's only translated from c++: http://thzn.de/0mq-mp-mix-pure-c/
| [Friday 29 April 2011] [11:14:55] <th>	pieterh: just added the output.txt
| [Friday 29 April 2011] [11:15:50] <pieterh>	sustrik: just tried again with master+patch, both pub and sub die
| [Friday 29 April 2011] [11:16:01] <sustrik>	ok
| [Friday 29 April 2011] [11:16:09] <pieterh>	there is a memory corruption somewhere, because sub dies in weird ways that change when I try to add printfs
| [Friday 29 April 2011] [11:17:05] <sustrik>	compiling it
| [Friday 29 April 2011] [11:18:43] <pieterh>	sustrik: I'm getting a random EINVAL on rc = zmq_getsockopt (s, ZMQ_RCVMORE, &more, &moresz);
| [Friday 29 April 2011] [11:18:47] <pieterh>	in the sub test
| [Friday 29 April 2011] [11:19:05] <pieterh>	but I think it's caused by some memory corruption issues
| [Friday 29 April 2011] [11:21:11] <sustrik>	looks like
| [Friday 29 April 2011] [11:21:21] <pieterh>	sustrik: do you always run ldconfig after installing a new libzmq version?
| [Friday 29 April 2011] [11:21:27] <sustrik>	no idea
| [Friday 29 April 2011] [11:21:28] <sustrik>	mato?
| [Friday 29 April 2011] [11:22:30] <pieterh>	anyhow, that changes nothing... the subscriber dies with EINVAL on a valid getsockopt, the pub segfaults in array.hpp as documented
| [Friday 29 April 2011] [11:22:42] <pieterh>	code is hard :)
| [Friday 29 April 2011] [11:25:35] <sustrik>	ok, reproduced
| [Friday 29 April 2011] [11:25:40] <pieterh>	excellent!
| [Friday 29 April 2011] [11:26:00] <sustrik>	digging in
| [Friday 29 April 2011] [11:26:47] <pieterh>	I *think* there is a problem in the new zmq_recv() method
| [Friday 29 April 2011] [11:27:05] <sustrik>	doesn't happen when you use zmq_recvmsg?
| [Friday 29 April 2011] [11:27:26] <pieterh>	the bogus result on getsockopt only hits with zmq_recv, not zmq_recvmsg
| [Friday 29 April 2011] [11:27:35] <pieterh>	I have two otherwise identical subs, one works, one fails
| [Friday 29 April 2011] [11:27:38] <sustrik>	i se
| [Friday 29 April 2011] [11:27:40] <sustrik>	see
| [Friday 29 April 2011] [11:27:42] 	 * pieterh will do some more digging
| [Friday 29 April 2011] [11:30:44] <pieterh>	sustrik: it was a bug in your C testcase... uninitialized 'size_t moresz'
| [Friday 29 April 2011] [11:31:30] <sustrik>	aha
| [Friday 29 April 2011] [11:31:45] <pieterh>	so, subscriber is stable, publisher does crash 
| [Friday 29 April 2011] [11:31:48] <mato>	sustrik: what's up?
| [Friday 29 April 2011] [11:32:02] <mato>	sustrik: sorry, am distracted, not paying attention here ...
| [Friday 29 April 2011] [11:32:05] <pieterh>	mato: I was asking if one needs to run ldconfig when installing new version of libzmq
| [Friday 29 April 2011] [11:32:26] <mato>	pieterh: you should always run ldconfig as root after doing make install
| [Friday 29 April 2011] [11:32:35] <pieterh>	ah, good to know
| [Friday 29 April 2011] [11:32:39] <sustrik>	hm, i never did that
| [Friday 29 April 2011] [11:32:50] <mato>	pieterh: in some cases it's redundant but it won't hurt
| [Friday 29 April 2011] [11:32:57] <sustrik>	even if the new version just overwrites the old one?
| [Friday 29 April 2011] [11:33:06] <sustrik>	as in recompiling
| [Friday 29 April 2011] [11:33:07] <mato>	sustrik: no, then you don't need to do that
| [Friday 29 April 2011] [11:33:09] <sustrik>	ok
| [Friday 29 April 2011] [11:33:28] <mato>	sustrik: but explaining to users that only run this if the ABI version is different is not worth the trouble
| [Friday 29 April 2011] [11:33:35] <mato>	given that running it won't hurt anything
| [Friday 29 April 2011] [11:33:42] <pieterh>	but between 2.1 and 3.0 for instance it's needed...
| [Friday 29 April 2011] [11:34:04] <mato>	yes, because the soname changes
| [Friday 29 April 2011] [11:34:45] <Guthur>	sustrik, would you have any issues with changing the clrzmq2 bindings license?
| [Friday 29 April 2011] [11:35:31] <sustrik>	Guthur: it's your project
| [Friday 29 April 2011] [11:35:41] <sustrik>	you choose the license
| [Friday 29 April 2011] [11:36:05] <Guthur>	sustrik, well it contains a little code from the original bindng
| [Friday 29 April 2011] [11:36:08] <Guthur>	binding*
| [Friday 29 April 2011] [11:36:11] <sustrik>	ah
| [Friday 29 April 2011] [11:36:15] <sustrik>	sure, go on
| [Friday 29 April 2011] [11:36:23] <sustrik>	what license do you want to use?
| [Friday 29 April 2011] [11:36:30] <Guthur>	i still need to contact Jeffery
| [Friday 29 April 2011] [11:36:40] <Guthur>	may LGPL, or MIT
| [Friday 29 April 2011] [11:37:03] <Guthur>	I don't really care too much, just that GPL turns some people off
| [Friday 29 April 2011] [11:37:11] <sustrik>	it's GPL ???
| [Friday 29 April 2011] [11:37:19] <Guthur>	it would appear so
| [Friday 29 April 2011] [11:37:21] <sustrik>	how the hell that happened?
| [Friday 29 April 2011] [11:37:26] <Guthur>	I only noticed this recently
| [Friday 29 April 2011] [11:37:38] <Guthur>	oh doh
| [Friday 29 April 2011] [11:37:43] <Guthur>	wait I'm blind
| [Friday 29 April 2011] [11:37:50] <Guthur>	sorry false alarm
| [Friday 29 April 2011] [11:38:02] <Guthur>	it's LGPL
| [Friday 29 April 2011] [11:38:04] <sustrik>	:)
| [Friday 29 April 2011] [11:38:08] <pieterh>	lol
| [Friday 29 April 2011] [11:38:12] <pieterh>	LICENSE PANIC!!!
| [Friday 29 April 2011] [11:38:38] <pieterh>	Guthur: good to hear there's no problem after all
| [Friday 29 April 2011] [11:38:47] <Guthur>	hehe
| [Friday 29 April 2011] [11:39:33] <Guthur>	I think it's because the Lesser comes before GNU General Public License
| [Friday 29 April 2011] [11:39:42] <Guthur>	and I started reading at GNU
| [Friday 29 April 2011] [11:40:11] <Guthur>	the real lesson here is that I should read license agreements alot more carefully
| [Friday 29 April 2011] [11:40:25] <sustrik>	actually, the wording is incorrect
| [Friday 29 April 2011] [11:40:46] <sustrik>	it should be "GNU Lesser GPL"
| [Friday 29 April 2011] [11:40:52] <sustrik>	we've fixed that in the  core
| [Friday 29 April 2011] [11:41:04] <sustrik>	but obviously it remained in clrzmq
| [Friday 29 April 2011] [11:41:12] <sustrik>	feel free to fix ti
| [Friday 29 April 2011] [11:41:13] <sustrik>	it
| [Friday 29 April 2011] [11:50:49] <Guthur>	ah ok, cool
| [Friday 29 April 2011] [11:51:02] <Guthur>	I did think it weird to have the GNU after Lesser
| [Friday 29 April 2011] [12:05:57] <sustrik>	pieterh: can you check with this patch instead of the old one:
| [Friday 29 April 2011] [12:05:58] <sustrik>	https://gist.github.com/948531
| [Friday 29 April 2011] [12:09:31] <mikko>	sustrik: build failure
| [Friday 29 April 2011] [12:10:04] <sustrik>	let me see
| [Friday 29 April 2011] [12:10:56] <mikko>	http://build.zero.mq/view/libzmq/
| [Friday 29 April 2011] [12:11:01] <mikko>	uuid related changes
| [Friday 29 April 2011] [12:11:26] <sustrik>	ah, uuid + pgm interaction
| [Friday 29 April 2011] [12:11:31] <sustrik>	i haven't tested that
| [Friday 29 April 2011] [12:11:33] <sustrik>	me bad
| [Friday 29 April 2011] [12:11:58] <mikko>	that's fine
| [Friday 29 April 2011] [12:12:04] <sustrik>	wait a sec
| [Friday 29 April 2011] [12:12:04] <mikko>	at least you get post-commit reviews :)
| [Friday 29 April 2011] [12:12:14] <sustrik>	heh
| [Friday 29 April 2011] [12:12:36] <mikko>	i'm unable to build debian packages though
| [Friday 29 April 2011] [12:12:42] <mikko>	not sure how to use the debian/
| [Friday 29 April 2011] [12:12:45] <mikko>	mato: there?
| [Friday 29 April 2011] [12:12:53] <mato>	mikko: ja
| [Friday 29 April 2011] [12:13:00] <mikko>	how do you build debian packages?
| [Friday 29 April 2011] [12:13:22] <mato>	mikko: the debian/ stuff in git is kinda outdated
| [Friday 29 April 2011] [12:13:31] <mikko>	i can add debian packages to daily builds (x86 and amd64) if it's somewhat easy
| [Friday 29 April 2011] [12:13:49] <mikko>	http://snapshot.zero.mq/ already contains rpms
| [Friday 29 April 2011] [12:14:06] <mato>	mikko: not right now ... the debian/ stuff currently doesn't deal with building snapshot packages
| [Friday 29 April 2011] [12:14:51] <mikko>	can debian/ live under builds/?
| [Friday 29 April 2011] [12:14:57] <mikko>	or does that complicate things?
| [Friday 29 April 2011] [12:15:38] <mato>	mikko: that complicates things
| [Friday 29 April 2011] [12:15:57] <mato>	currently debian/ can either go away altogether or needs to be updated to build snapshot packages
| [Friday 29 April 2011] [12:16:04] <mato>	but i'm not sure of the value of those
| [Friday 29 April 2011] [12:16:23] <mikko>	people can test more easily
| [Friday 29 April 2011] [12:16:42] <mikko>	im planning to do yum repo for rpms later on
| [Friday 29 April 2011] [12:16:53] <mato>	can we discuss this another time? /me is deep into trying to figure out how to get a chrome extension to talk to something else via zmq
| [Friday 29 April 2011] [12:16:59] <mato>	(don't ask why)
| [Friday 29 April 2011] [12:17:21] <mikko>	hehe, sure
| [Friday 29 April 2011] [12:18:52] <sustrik>	oh my, chrome extension? you should have been on that webdev conf in moscow instead of me
| [Friday 29 April 2011] [12:19:31] 	 * mato did not know anything about chrome extensions until about an hour ago :-)
| [Friday 29 April 2011] [12:20:02] <mato>	i need to get a running instance of chrome to talk to a running instance of lynx (yes, the webbrowser from 1995) and vice versa
| [Friday 29 April 2011] [12:20:51] <mikko>	ahmmmm
| [Friday 29 April 2011] [12:20:55] <mikko>	i'm not gonna ask
| [Friday 29 April 2011] [12:20:59] <mato>	:-)
| [Friday 29 April 2011] [12:28:53] <staylor>	just throwing it out there, but have you guys ever considered cmake?  I've used it to build rpms/debs and saves the hassle of maintaining spec/debian configurations.
| [Friday 29 April 2011] [12:33:09] <sustrik>	it've been discussed several times
| [Friday 29 April 2011] [12:34:10] <sustrik>	mikko: i have a patch, but i need steven to approve
| [Friday 29 April 2011] [12:34:11] <sustrik>	it
| [Friday 29 April 2011] [12:34:33] <sustrik>	i guess i just post it to the ML and won't commit it straight away
| [Friday 29 April 2011] [13:03:22] <pieterh>	re
| [Friday 29 April 2011] [13:04:05] <pieterh>	sustrik: do you want me to test that patch then?
| [Friday 29 April 2011] [13:04:30] <sustrik>	yes
| [Friday 29 April 2011] [13:04:36] <pieterh>	ok
| [Friday 29 April 2011] [13:04:38] <sustrik>	i've tried pub.c and sub.c
| [Friday 29 April 2011] [13:04:44] <sustrik>	and it seems to fixed the issue
| [Friday 29 April 2011] [13:04:56] <sustrik>	however, confirming it would be good
| [Friday 29 April 2011] [13:08:04] <pieterh>	sustrik: it complains that the patch is corrupt at the last line
| [Friday 29 April 2011] [13:08:07] <pieterh>	how did you make the patch?
| [Friday 29 April 2011] [13:09:16] <pieterh>	staylor: if you can make cmake work in any way at all, send examples to the list
| [Friday 29 April 2011] [13:09:27] <sustrik>	pieterh: git diff
| [Friday 29 April 2011] [13:09:39] <sustrik>	want me to send the format-patch to the ML?
| [Friday 29 April 2011] [13:10:01] <pieterh>	sustrik: or just send me the two files
| [Friday 29 April 2011] [13:10:13] <pieterh>	i don't really care, just need a branch to test
| [Friday 29 April 2011] [13:10:15] <sustrik>	wait a sec
| [Friday 29 April 2011] [13:10:48] <sustrik>	snet
| [Friday 29 April 2011] [13:10:50] <sustrik>	sent
| [Friday 29 April 2011] [13:10:58] <pieterh>	sustrik: you could work with a fork of libzmq, then push branches to that easily
| [Friday 29 April 2011] [13:11:19] <pieterh>	sustrik: ok, got the files, thanks
| [Friday 29 April 2011] [13:14:57] <pieterh>	sustrik: afaic... it doesn't crash any longer but the subscriber gets the wrong chunk at some stage
| [Friday 29 April 2011] [13:15:25] <pieterh>	gets 1000 bytes instead of 5
| [Friday 29 April 2011] [13:15:29] <pieterh>	after some iterations
| [Friday 29 April 2011] [13:15:40] <pieterh>	the publisher is stable now, however
| [Friday 29 April 2011] [13:15:43] <sustrik>	ok
| [Friday 29 April 2011] [13:16:12] <pieterh>	receiving
| [Friday 29 April 2011] [13:16:12] <pieterh>	5
| [Friday 29 April 2011] [13:16:12] <pieterh>	receiving
| [Friday 29 April 2011] [13:16:12] <pieterh>	1000
| [Friday 29 April 2011] [13:16:12] <pieterh>	sub: sub.c:26: main: Assertion `rc == 5' failed.
| [Friday 29 April 2011] [13:16:28] <pieterh>	this is the kind of output, showing rc of first recv in loop
| [Friday 29 April 2011] [13:17:26] <sustrik>	there are pub.c and sub.c from the gist, right?
| [Friday 29 April 2011] [13:17:55] <sustrik>	these are
| [Friday 29 April 2011] [13:22:06] <pieterh>	sustrik: yes
| [Friday 29 April 2011] [13:22:24] <sustrik>	hm, i'm running it for 2 mins already
| [Friday 29 April 2011] [13:22:32] <sustrik>	no assertions
| [Friday 29 April 2011] [13:22:37] <sustrik>	version 3.0?
| [Friday 29 April 2011] [13:22:41] <pieterh>	sustrik: what kind of box are you on?
| [Friday 29 April 2011] [13:22:43] <pieterh>	I'll update the gist with the precise versions I'm using, they may have changed a little...
| [Friday 29 April 2011] [13:23:00] <sustrik>	i'm using master head
| [Friday 29 April 2011] [13:23:08] <sustrik>	+ the patch
| [Friday 29 April 2011] [13:23:23] <sustrik>	the box is a dual core desktop
| [Friday 29 April 2011] [13:23:27] <pieterh>	sure, I'm using master + the two files you sent
| [Friday 29 April 2011] [13:23:31] <sustrik>	+ ubuntu
| [Friday 29 April 2011] [13:23:38] <pieterh>	is it possible that the problem is related to threading concurrency?
| [Friday 29 April 2011] [13:23:56] <sustrik>	i don't think so
| [Friday 29 April 2011] [13:24:05] <sustrik>	looks like a pipe management problem
| [Friday 29 April 2011] [13:24:14] <sustrik>	but anything is possible
| [Friday 29 April 2011] [13:24:19] <sustrik>	what box you are on?
| [Friday 29 April 2011] [13:24:29] <pieterh>	I'm on a 4-core desktop, Ubuntu
| [Friday 29 April 2011] [13:24:49] <sustrik>	still no assertions here
| [Friday 29 April 2011] [13:24:58] <sustrik>	let's wait couple of minutes more
| [Friday 29 April 2011] [13:25:03] <pieterh>	well, it happens after 0.5 secs or so
| [Friday 29 April 2011] [13:25:16] <sustrik>	hm
| [Friday 29 April 2011] [13:25:29] <pieterh>	I've updated the gist (gists are full git repos, nice)... if you want to be 100% sure you're running the same test
| [Friday 29 April 2011] [13:25:40] <sustrik>	\ok
| [Friday 29 April 2011] [13:25:55] <pieterh>	oh... hang on...
| [Friday 29 April 2011] [13:26:08] <pieterh>	sorry! i copied dist.cpp/hpp into the wrong directory
| [Friday 29 April 2011] [13:26:14] <pieterh>	am running on plain master thus
| [Friday 29 April 2011] [13:26:16] <pieterh>	duh....
| [Friday 29 April 2011] [13:26:29] <sustrik>	interesting it didn't fail
| [Friday 29 April 2011] [13:26:44] <pieterh>	it did fail, confused frames, as expected
| [Friday 29 April 2011] [13:27:00] <sustrik>	ah, right
| [Friday 29 April 2011] [13:27:59] <pieterh>	better now... no errors, no crashes...
| [Friday 29 April 2011] [13:28:42] <pieterh>	fix confirmed on 3.0, thus
| [Friday 29 April 2011] [13:28:46] <pieterh>	now to backport to 2.1...
| [Friday 29 April 2011] [13:28:54] <pieterh>	were the changes to the patch significant?
| [Friday 29 April 2011] [13:29:01] <sustrik>	wait a sec
| [Friday 29 April 2011] [13:29:34] <sustrik>	there's one cosmetic change
| [Friday 29 April 2011] [13:30:14] <sustrik>	removing a leftover function declaration from dist.hpp
| [Friday 29 April 2011] [13:30:35] <pieterh>	ack
| [Friday 29 April 2011] [13:30:51] <sustrik>	clear_new_pipes
| [Friday 29 April 2011] [13:31:06] <sustrik>	and the real patch is in zmq::dist_t::write
| [Friday 29 April 2011] [13:31:18] <sustrik>	these 4 lines:
| [Friday 29 April 2011] [13:31:18] <sustrik>	        pipes.swap (pipes.index (pipe_), active - 1);
| [Friday 29 April 2011] [13:31:19] <sustrik>	        active--;
| [Friday 29 April 2011] [13:31:19] <sustrik>	        pipes.swap (active, eligible - 1);
| [Friday 29 April 2011] [13:31:19] <sustrik>	        eligible--;
| [Friday 29 April 2011] [13:31:25] <sustrik>	instead of original 2 lines
| [Friday 29 April 2011] [13:31:31] <pieterh>	this is a patch on top of the patch, right?
| [Friday 29 April 2011] [13:31:35] <sustrik>	yes
| [Friday 29 April 2011] [13:31:38] <pieterh>	ack
| [Friday 29 April 2011] [13:31:54] <sustrik>	pieterh: sorry, no
| [Friday 29 April 2011] [13:32:02] <sustrik>	the patch i posted to gist
| [Friday 29 April 2011] [13:32:06] <sustrik>	is the whole thing
| [Friday 29 April 2011] [13:32:14] <sustrik>	the original patch + the patch of the patch
| [Friday 29 April 2011] [13:32:46] <pieterh>	ok, since I applied the original patch manually I want to know if there's a shortcut
| [Friday 29 April 2011] [13:32:56] <pieterh>	or if it's safer to redo that work
| [Friday 29 April 2011] [13:33:02] <sustrik>	just use your existing codebase
| [Friday 29 April 2011] [13:33:09] <sustrik>	and fix the 2 issues i've mentioned
| [Friday 29 April 2011] [13:34:09] <pieterh>	ok
| [Friday 29 April 2011] [13:34:30] <pieterh>	so if I do a diff of the two patches it will tell me what to actually change... :)
| [Friday 29 April 2011] [13:35:23] <pieterh>	yeah, that does the trick
| [Friday 29 April 2011] [13:35:30] <pieterh>	ok, will apply this, test, and let you know
| [Friday 29 April 2011] [13:35:41] <pieterh>	am taking the kids for pizza now... bbl
| [Friday 29 April 2011] [13:35:59] <sustrik>	cyl
| [Friday 29 April 2011] [14:06:50] <staylor>	is it possible to both bind and connect with the same socket?
| [Friday 29 April 2011] [14:09:01] <Guthur>	can't think why you would even want to do that
| [Friday 29 April 2011] [14:09:47] <sustrik>	yes, it's possible
| [Friday 29 April 2011] [14:10:02] <sustrik>	you can bind and connect as many times as you want
| [Friday 29 April 2011] [14:14:18] <staylor>	okay, the reason I need to do that is I have many nodes that need to connect to each other to transfer session data.  but depending on which can open a port for nat one node needs to bind or connect to his peer.
| [Friday 29 April 2011] [14:14:50] <staylor>	I'm using a client and host socket right now, but a single socket to both bind and connect would be a lot cleaner if that's valid.
| [Friday 29 April 2011] [14:18:34] <staylor>	should I be concerned about connecting to the same host twice?  I could keep track of which I connected to but these connections are mostly few and far between.
| [Friday 29 April 2011] [14:24:10] <Guthur>	oh, i miss understood, i read that as I bind and connect to the same address
| [Friday 29 April 2011] [14:24:18] <Guthur>	with the same sockeet
| [Friday 29 April 2011] [14:26:41] <taotetek>	anyone have a moment to help me find some clarity in regards to HWM options w/ PUSH / PULL socket types?
| [Friday 29 April 2011] [14:27:12] <sustrik>	staylor: connecting twice means that the two connections will be treated as such
| [Friday 29 April 2011] [14:27:41] <sustrik>	so for example you would get every message twice with a PUB/SUB sockets
| [Friday 29 April 2011] [14:27:53] <sustrik>	taotetek: yes?
| [Friday 29 April 2011] [14:28:34] <taotetek>	sustrik: so... (using pyzmq) .. if I set up a PUSH socket, and there are no PULL's connected, it blocks, which is what I expect
| [Friday 29 April 2011] [14:29:07] <taotetek>	I'm looking at this passage in the documentation: "When a ZMQ_PUSH socket enters an exceptional state due to having reached the high water mark for all downstream nodes, or if there are no downstream nodes at all, then any zmq_send(3) operations on the socket shall block until the exceptional state ends"
| [Friday 29 April 2011] [14:29:21] <sustrik>	yes
| [Friday 29 April 2011] [14:29:31] <taotetek>	but I haven't been able to cause the PUSH socket to become blocked on a send 
| [Friday 29 April 2011] [14:29:37] <taotetek>	(unless no PULL sockets are connected)
| [Friday 29 April 2011] [14:29:51] <taotetek>	so I'm either setting something wrong or not understanding what I'm reading
| [Friday 29 April 2011] [14:29:59] <sustrik>	that's because messages are sent to the PULL socket in parallel
| [Friday 29 April 2011] [14:30:15] <sustrik>	so you never reach the HWM
| [Friday 29 April 2011] [14:30:31] <sustrik>	you can set the HWM on PULL socket
| [Friday 29 April 2011] [14:30:42] <sustrik>	if you won't read from it
| [Friday 29 April 2011] [14:30:50] <sustrik>	the HWM on the PULL socket would be reached
| [Friday 29 April 2011] [14:31:02] <sustrik>	then the recv-side TCP buffer will be filled
| [Friday 29 April 2011] [14:31:12] <sustrik>	then send-side TCP buffer will be filled
| [Friday 29 April 2011] [14:31:23] <sustrik>	then PUSH socket buffer will reach HWM
| [Friday 29 April 2011] [14:31:23] <taotetek>	ok.. so if I.. 1. set up a PULL socket with a HWM of 1, 2. set up a PUSH socket, 3. send from the PUSH socket but don't recv on the PULL
| [Friday 29 April 2011] [14:31:25] <sustrik>	and block
| [Friday 29 April 2011] [14:31:41] <taotetek>	then it will block once the tcp buffer is full
| [Friday 29 April 2011] [14:31:52] <taotetek>	(and the tcp buffer could conceivably be larger than a single message?)
| [Friday 29 April 2011] [14:32:00] <sustrik>	sure
| [Friday 29 April 2011] [14:32:06] <taotetek>	which would be why I'm not seeing an immediate block
| [Friday 29 April 2011] [14:32:08] <sustrik>	the default on linux iirc is 128kB
| [Friday 29 April 2011] [14:32:32] <taotetek>	aha! ok I'll whip up a quick test
| [Friday 29 April 2011] [14:32:39] <taotetek>	thank you sustrik, that's enormously helpful information
| [Friday 29 April 2011] [14:32:47] <sustrik>	you are welcome
| [Friday 29 April 2011] [14:33:30] <staylor>	sustrik, okay so if I have two xrep sockets x1,x2 where x1 binds and x2 connects twice, any message would go to x2 twice?
| [Friday 29 April 2011] [14:34:25] <taotetek>	sustrik: and that makes perfect sense. it's easy when working with zmq to forget that it's still TCP under the hood sometimes I think, because it makes it so ridiculously easy to be "message" oriented.
| [Friday 29 April 2011] [14:34:49] <sustrik>	staylor: nope, req/rep pattern sends message to a single connection
| [Friday 29 April 2011] [14:35:01] <sustrik>	what'll you see would be load-balancing between the connections
| [Friday 29 April 2011] [14:35:21] <sustrik>	and thus possible re-ordering of messages
| [Friday 29 April 2011] [14:35:36] <staylor>	then x2 being the same socket connected twice to the same host would just receive a single message then
| [Friday 29 April 2011] [14:36:00] <sustrik>	yes
| [Friday 29 April 2011] [14:36:06] <sustrik>	with possible reordering
| [Friday 29 April 2011] [14:36:13] <staylor>	alright
| [Friday 29 April 2011] [14:36:40] <staylor>	my worry was that I want to know if I should check before connecting if I'm already connected to that host or just go ahead and connect regardless
| [Friday 29 April 2011] [14:37:27] <staylor>	my network is effectively a mesh of xrep sockets which all bind, and then will also connect to the host they need to message.
| [Friday 29 April 2011] [14:40:13] <Guthur>	ian barbers PHP presentation is very good in regards stable/unstable parts of your arch
| [Friday 29 April 2011] [14:40:46] <Guthur>	worth watching, though it is nearly an hour long
| [Friday 29 April 2011] [14:42:39] <staylor>	"ZeroMQ is the answer" video on the website?
| [Friday 29 April 2011] [14:43:01] <sustrik>	i would recomment watching it as well
| [Friday 29 April 2011] [14:43:29] <sustrik>	connecting every component to every other component using XREP sockets doesn't sound like an ideal architecture
| [Friday 29 April 2011] [14:44:51] <staylor>	my problem is I want to have a single bind per node since they require opening a port over upnp, there's only a few nodes that communicate to each other though.
| [Friday 29 April 2011] [14:45:04] <Guthur>	staylor, yep
| [Friday 29 April 2011] [14:45:37] <staylor>	this might be in the video so let me know if I'm asking something already answered, but what would a 'smarter' architecture be for dealing with this problem?
| [Friday 29 April 2011] [14:46:22] <Guthur>	when you add a bind to a node it becomes a stable node
| [Friday 29 April 2011] [14:46:37] <Guthur>	though I think static is a better term
| [Friday 29 April 2011] [14:47:23] <Guthur>	whereas if a node only connects to other static nodes it is unstable, or dynamic, can come and go
| [Friday 29 April 2011] [14:47:38] <Guthur>	Ian explains it way better than me though
| [Friday 29 April 2011] [14:47:44] <staylor>	that's why I bind to nodes that are able to open upnp ports, other nodes connect, there's a server that acts as a sync to let two peers decide which will bind and which will connect
| [Friday 29 April 2011] [14:47:45] <Guthur>	with pretty pictures and everything
| [Friday 29 April 2011] [14:48:06] <staylor>	I consider a upnp enabled node to be static
| [Friday 29 April 2011] [14:50:59] <th>	pieterh: what i said earlier - was not correct, the pure-c example is not failing earlier. the behaviour is the same as with c++
| [Friday 29 April 2011] [14:51:19] <th>	pieterh: http://thzn.de/0mq-mp-mix-pure-c/  thats the latest testcase
| [Friday 29 April 2011] [15:11:19] <th>	i switched from 2.1 to 3.0 now. i changed zmq_{send,recv} to zmq_{send,recv}msg and it compiles again. but i get a 'errno: 11 (Resource temporarily unavailable)' on sending
| [Friday 29 April 2011] [15:15:30] <th>	which is EAGAIN - but i did not choose NONBLOCKING
| [Friday 29 April 2011] [18:10:17] <Seta00>	I just watched the ZeroMQ is the Answer talk, and it really is worth watching
| [Saturday 30 April 2011] [00:53:57] <CIA-75>	libzmq: 03Martin Sustrik 07master * rfe2e772 10/ src/pgm_socket.cpp : pgm_socket uses binary version of UUID ...
| [Saturday 30 April 2011] [00:53:59] <CIA-75>	libzmq: 03Martin Sustrik 07master * reb9bc1b 10/ (src/dist.cpp src/dist.hpp): Message atomicity problem in PUB socket fixed. ...
| [Saturday 30 April 2011] [01:39:12] <pieterh>	sustrik: issue 191 confirmed fixed on 2.1... :)
| [Saturday 30 April 2011] [01:58:16] <sustrik>	great
| [Saturday 30 April 2011] [02:22:04] <pieterh>	sustrik: IMO we need to become more pedantic about test cases for such things
| [Saturday 30 April 2011] [02:22:15] <pieterh>	without a test case it'd have been impossible to get this working
| [Saturday 30 April 2011] [02:22:25] <sustrik>	what do you propose
| [Saturday 30 April 2011] [02:22:36] <sustrik>	?
| [Saturday 30 April 2011] [02:22:53] <pieterh>	well... we need somewhere to hold test cases
| [Saturday 30 April 2011] [02:23:03] <pieterh>	issue tracker isn't great for this
| [Saturday 30 April 2011] [02:23:10] <pieterh>	I'd prefer a git
| [Saturday 30 April 2011] [02:23:16] <sustrik>	 /tests?
| [Saturday 30 April 2011] [02:23:37] <pieterh>	can't be in libzmq IMO, perhaps a separate git
| [Saturday 30 April 2011] [02:23:51] <sustrik>	why so?
| [Saturday 30 April 2011] [02:23:58] <sustrik>	if it's elsewhere it'll bit-rot
| [Saturday 30 April 2011] [02:24:17] <pieterh>	they'll be historical anyhow, per issue
| [Saturday 30 April 2011] [02:24:24] <pieterh>	now we have issue 199 with tests
| [Saturday 30 April 2011] [02:24:38] <pieterh>	a. random contributors (usually person reporting the issue)
| [Saturday 30 April 2011] [02:24:44] <pieterh>	b. random languages
| [Saturday 30 April 2011] [02:24:52] <pieterh>	c. random versions of 0MQ (2.1, 3.0 at least)
| [Saturday 30 April 2011] [02:25:08] <pieterh>	d. perhaps, testing other layers
| [Saturday 30 April 2011] [02:25:37] <pieterh>	I don't see this as a regression test layer but just an aide for fixing issues as we go along
| [Saturday 30 April 2011] [02:26:18] <pieterh>	see th's test cases for issue 199... random code on some random URL
| [Saturday 30 April 2011] [02:26:38] <sustrik>	why do you need those to be persistent?
| [Saturday 30 April 2011] [02:26:48] <pieterh>	i don't need persistence, I need consistency
| [Saturday 30 April 2011] [02:26:51] <sustrik>	they'll be completely bit-rotten in 6 months
| [Saturday 30 April 2011] [02:26:55] <pieterh>	that's fine
| [Saturday 30 April 2011] [02:27:06] <pieterh>	I don't care about bitrot
| [Saturday 30 April 2011] [02:27:20] <pieterh>	I care about 'where the heck are the test cases for issue 204 for 2.1?'
| [Saturday 30 April 2011] [02:27:41] <pieterh>	searching email and irc and issue trackers is a waste of time
| [Saturday 30 April 2011] [02:28:01] <pieterh>	also, not having a consistent approach means we often don't even have test cases
| [Saturday 30 April 2011] [02:28:22] <pieterh>	clearly, without a test case for 191 we'd have allowed fairly major breakage
| [Saturday 30 April 2011] [02:28:45] <sustrik>	hm, you have to look to issue tracker anyway, otherwise you won't have an idea what issue 204 is meant to be
| [Saturday 30 April 2011] [02:28:49] <pieterh>	also, we need a way to share test code
| [Saturday 30 April 2011] [02:29:06] <pieterh>	e.g. the gist repo I made for 191 but where anyone can write back to it
| [Saturday 30 April 2011] [02:29:14] <pieterh>	so the issue tracker is fine for discussion
| [Saturday 30 April 2011] [02:29:42] <pieterh>	e. multiple authors on repo
| [Saturday 30 April 2011] [02:32:11] <sustrik>	feel free to try, but imo people will consider it too heavyweight and will use gist/bugtracker instead
| [Saturday 30 April 2011] [02:32:39] <pieterh>	well, this would only work if we adopt it and enforce it
| [Saturday 30 April 2011] [02:33:01] <pieterh>	people would like to just email the list saying "hey, 0mq crashes!"
| [Saturday 30 April 2011] [02:34:03] <pieterh>	ok, I'll make an email to zeromq-dev, everyone will ignore it, then I'll start doing this anyhow, and after a month or two people will bitch at me for fragmenting the repos... 
| [Saturday 30 April 2011] [02:34:04] <pieterh>	sigh
| [Saturday 30 April 2011] [02:37:04] <sustrik>	hm
| [Saturday 30 April 2011] [02:37:21] <sustrik>	so once again, what's the rationale?
| [Saturday 30 April 2011] [02:37:26] 	 * sustrik haven't got it
| [Saturday 30 April 2011] [02:37:48] <pieterh>	test-driven change, martin
| [Saturday 30 April 2011] [02:38:06] 	 * pieterh waves arms around in air, frustratedly
| [Saturday 30 April 2011] [02:38:31] <pieterh>	every bug has an issue, and test case, which is in C, and ported to 2.1 and 3.0
| [Saturday 30 April 2011] [02:38:40] <pieterh>	every test case is in a 100% predictable location
| [Saturday 30 April 2011] [02:38:56] <sustrik>	why not in bug tracker
| [Saturday 30 April 2011] [02:38:57] <pieterh>	before a fix is applied to a master branch it can be 100% tested 
| [Saturday 30 April 2011] [02:38:58] <sustrik>	or a gist
| [Saturday 30 April 2011] [02:38:59] <sustrik>	?
| [Saturday 30 April 2011] [02:39:05] <pieterh>	bug tracker has no attachments
| [Saturday 30 April 2011] [02:39:09] <pieterh>	a gist has no name
| [Saturday 30 April 2011] [02:39:21] <sustrik>	gist linked form bug tracker?
| [Saturday 30 April 2011] [02:39:25] <pieterh>	you provided two C test cases
| [Saturday 30 April 2011] [02:39:27] <pieterh>	they had bugs
| [Saturday 30 April 2011] [02:39:30] <pieterh>	did not run on 2.1
| [Saturday 30 April 2011] [02:39:45] <pieterh>	if I fix this, where do I put the improved versions?
| [Saturday 30 April 2011] [02:39:55] <pieterh>	where do I put listings, stack dumps, etc.?
| [Saturday 30 April 2011] [02:40:12] <pieterh>	how does someone download this bundle of stuff?
| [Saturday 30 April 2011] [02:40:18] <pieterh>	click click click on dozens of links?
| [Saturday 30 April 2011] [02:40:20] <pieterh>	srsly?
| [Saturday 30 April 2011] [02:40:44] 	 * pieterh stops ranting and reads up
| [Saturday 30 April 2011] [02:40:53] <pieterh>	gist linked from bug tracker... no predictable location
| [Saturday 30 April 2011] [02:41:21] <pieterh>	dozens of messy gist repos in working directoruy
| [Saturday 30 April 2011] [02:41:30] <pieterh>	no obvious naming of cloned repos
| [Saturday 30 April 2011] [02:44:34] <sustrik>	well, i am not feeling the pain yet
| [Saturday 30 April 2011] [02:44:44] <sustrik>	clicking on link works ok for me
| [Saturday 30 April 2011] [02:45:06] <th>	did i do that wrong?
| [Saturday 30 April 2011] [02:45:19] <pieterh>	th: no, you did exactly what we asked but we're asking for the wrong thing afaics
| [Saturday 30 April 2011] [02:45:21] <th>	i thought it would be easiest to put all information in one place and link it
| [Saturday 30 April 2011] [02:45:39] <th>	ahh i see - infrastructure discussion
| [Saturday 30 April 2011] [02:45:41] <pieterh>	yes
| [Saturday 30 April 2011] [02:45:54] <th>	i just noted github being slow ;)
| [Saturday 30 April 2011] [02:46:06] <th>	did not grok all the gist yet
| [Saturday 30 April 2011] [02:46:07] <pieterh>	sustrik: you don't feel the pain because you avoid a lot of the process
| [Saturday 30 April 2011] [02:46:15] <pieterh>	that however just means the way you work can't scale
| [Saturday 30 April 2011] [02:46:30] <pieterh>	e.g. we can't work like that and maintain stable versions
| [Saturday 30 April 2011] [02:46:55] <sustrik>	ok, give it a try and we'll see how it works
| [Saturday 30 April 2011] [02:47:10] <pieterh>	I'll make a demo and an email explaining it
| [Saturday 30 April 2011] [02:47:29] <th>	pieterh: i replied to what i get via email from you via github, but thats not supposed to show up as comment?
| [Saturday 30 April 2011] [02:47:37] <sustrik>	yes
| [Saturday 30 April 2011] [02:47:47] <pieterh>	th: it should appear as a comment, yes
| [Saturday 30 April 2011] [02:48:18] <th>	at least it did not (yet)
| [Saturday 30 April 2011] [02:49:21] <th>	anyways - added it via the web
| [Saturday 30 April 2011] [02:49:39] <th>	pieterh: the issue only happens under some load... so while ./stress;do;done
| [Saturday 30 April 2011] [02:50:00] <pieterh>	th: we definitely need more infrastructure for issue tests
| [Saturday 30 April 2011] [02:50:08] <th>	and i also tried to port this to 3.0, but i get EAGAIN on send although i dont use NOBLOCK
| [Saturday 30 April 2011] [02:50:19] <pieterh>	hmm
| [Saturday 30 April 2011] [02:50:44] <th>	pieterh: the only change i did to "port" was to use zmq_{send,recv}msg instead
| [Saturday 30 April 2011] [02:51:03] <pieterh>	th: should be sufficient, you don't use a lot of the API
| [Saturday 30 April 2011] [02:51:35] <sustrik>	th: note the change in the return value
| [Saturday 30 April 2011] [02:51:49] <sustrik>	in 2.0 send/recv returned 0/-1
| [Saturday 30 April 2011] [02:51:57] <sustrik>	in 3.0 it returns message size
| [Saturday 30 April 2011] [02:52:01] <th>	dang
| [Saturday 30 April 2011] [02:52:45] <th>	if (zmq_sendmsg()) { ... error ... }
| [Saturday 30 April 2011] [02:52:48] <th>	ok - i'm on it
| [Saturday 30 April 2011] [02:53:48] <th>	there is no manpage installed of zmq_sendmsg with libzmq (there is zmq_send.3 though)
| [Saturday 30 April 2011] [02:54:06] <pieterh>	th: also, don't use asserts like that, if you compile in release mode the whole assert is removed
| [Saturday 30 April 2011] [02:54:08] <sustrik>	th: yes, it's still missing
| [Saturday 30 April 2011] [02:54:31] <th>	pieterh: yea - but this test case will never be compiled in release mode, right?
| [Saturday 30 April 2011] [02:54:37] <pieterh>	th: sure
| [Saturday 30 April 2011] [02:54:38] <sustrik>	should be: if (zmq_sendmsg() < 0) error;
| [Saturday 30 April 2011] [02:54:46] <th>	sustrik: ok
| [Saturday 30 April 2011] [02:55:07] <th>	sustrik: same for recv?
| [Saturday 30 April 2011] [02:56:32] <sustrik>	yes
| [Saturday 30 April 2011] [02:56:51] <th>	pieterh: i'll add some `assert(test=1);if (test!=1) exit(1);`
| [Saturday 30 April 2011] [03:00:01] <pieterh>	th: can you clone https://github.com/zeromq/issues
| [Saturday 30 April 2011] [03:00:09] <pieterh>	and then add your changes, and then make a pull request?
| [Saturday 30 April 2011] [03:00:19] <th>	Unpacking objects: 100% (23/23), done.
| [Saturday 30 April 2011] [03:00:27] <pieterh>	I've already create a space for issue 199 and added your current C test cases
| [Saturday 30 April 2011] [03:00:31] <pieterh>	you can add everything there
| [Saturday 30 April 2011] [03:00:55] <th>	pieterh: excluding any output.{txt,html} and Makefiles?
| [Saturday 30 April 2011] [03:01:16] <pieterh>	anything other people need to run the tests, I'd say
| [Saturday 30 April 2011] [03:01:45] <pieterh>	This is an experiment to see if we can use a git repo for communication instead of pastebins
| [Saturday 30 April 2011] [03:02:10] <th>	pieterh: i'll do that.
| [Saturday 30 April 2011] [03:02:16] <pieterh>	tgh: much appreciated
| [Saturday 30 April 2011] [03:02:19] <th>	but first i'll fix this up for 3.0
| [Saturday 30 April 2011] [03:02:46] <th>	sustrik: any change on return value of [gs]etsockopt?
| [Saturday 30 April 2011] [03:02:46] <pieterh>	no hurry
| [Saturday 30 April 2011] [03:02:57] <pieterh>	th: nope, but most arguments changed
| [Saturday 30 April 2011] [03:03:04] <pieterh>	e.g. from uint64_t to int
| [Saturday 30 April 2011] [03:03:20] <pieterh>	so if you use the old types you'll get an EINVAL error
| [Saturday 30 April 2011] [03:03:44] <th>	well that direction (making it smaller) does not hurt in my case where i use ZMQ_XXXMORE
| [Saturday 30 April 2011] [03:04:05] <th>	pieterh: i dont use type - i pass a pointer and a pointer to a size, right?
| [Saturday 30 April 2011] [03:04:21] <pieterh>	th: in C?
| [Saturday 30 April 2011] [03:04:40] <th>	ZMQ_EXPORT int zmq_getsockopt (void *s, int option, void *optval, size_t *optvallen);
| [Saturday 30 April 2011] [03:04:57] <th>	wait you're talking about `int option`??
| [Saturday 30 April 2011] [03:05:02] <pieterh>	see https://github.com/zeromq/czmq/blob/master/src/zsockopt.c
| [Saturday 30 April 2011] [03:05:04] <th>	and not the value?
| [Saturday 30 April 2011] [03:05:43] <th>	pieterh: i see that... zmq_getsockopt (socket, ZMQ_RCVMORE, &rcvmore, &type_size);
| [Saturday 30 April 2011] [03:06:08] <th>	int64_t
| [Saturday 30 April 2011] [03:06:10] <pieterh>	rcvmore changed from int64_t  to int
| [Saturday 30 April 2011] [03:06:21] <pieterh>	see line 761
| [Saturday 30 April 2011] [03:06:36] <th>	what about line 403?
| [Saturday 30 April 2011] [03:06:46] <pieterh>	the zsockopt class (czmq) has both 2.1 and 3.0 support (two large conditional blocks)
| [Saturday 30 April 2011] [03:07:12] <pieterh>	line 403 is 2.1, line 761 is 3.0...
| [Saturday 30 April 2011] [03:07:14] <th>	ahhhhh
| [Saturday 30 April 2011] [03:07:15] <th>	ok
| [Saturday 30 April 2011] [03:08:06] <th>	pieterh: so i get EINVAL if last argument's value is 8 instead of 4?
| [Saturday 30 April 2011] [03:08:16] <pieterh>	yes
| [Saturday 30 April 2011] [03:08:44] <th>	although - only the pointer to type_size is passed.
| [Saturday 30 April 2011] [03:09:00] <th>	but thats always of size_t?
| [Saturday 30 April 2011] [03:09:06] <pieterh>	yes
| [Saturday 30 April 2011] [03:09:07] <th>	ok
| [Saturday 30 April 2011] [03:09:36] <th>	why a pointer at all? would i get the amount of bytes needed if i pass to small buffer?
| [Saturday 30 April 2011] [03:09:45] <th>	s/to small/too small/
| [Saturday 30 April 2011] [03:09:54] <pieterh>	th: this is the standard POSIX API for get/setsockopt
| [Saturday 30 April 2011] [03:12:27] <th>	`and modified on return to  indicate the  actual  size  of  the value returned.`
| [Saturday 30 April 2011] [03:12:29] <th>	okay
| [Saturday 30 April 2011] [03:13:18] <th>	will a recv in 3.0 ever return 0 to indicate EOF or something like this?
| [Saturday 30 April 2011] [03:14:28] 	 * pieterh doesn't know... :-/
| [Saturday 30 April 2011] [03:14:55] <th>	pieterh: ok - same effect with 3.0
| [Saturday 30 April 2011] [03:14:57] <pieterh>	well, hang on, there's no EOF in 0MQ
| [Saturday 30 April 2011] [03:15:00] <pieterh>	:)
| [Saturday 30 April 2011] [03:15:14] <th>	pieterh: thats why i said "or something like this?" ;)
| [Saturday 30 April 2011] [03:16:50] <th>	i wonder if this issue would still be an issue if i would not be on the VSM side...
| [Saturday 30 April 2011] [03:18:18] <pieterh>	th: I don't get the crash on my box
| [Saturday 30 April 2011] [03:18:22] <pieterh>	what OS are you using?
| [Saturday 30 April 2011] [03:19:25] <pieterh>	I'll let it run for a while...
| [Saturday 30 April 2011] [03:21:55] <th>	pieterh: you also dont get the "STUPID RECV (JUST FOR SHOWING WHATS WAITING)"?
| [Saturday 30 April 2011] [03:22:15] <th>	pieterh: i replaced some assert(0) with an endless loop of juse receiving and printing, to see the order of messages
| [Saturday 30 April 2011] [03:22:38] <th>	pieterh: Ubuntu 10.04.2 LTS on 64bit
| [Saturday 30 April 2011] [03:23:21] <th>	pieterh: i run it |& tee log   and cancel the client-while-loop when i see the "STUPID RECV"