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