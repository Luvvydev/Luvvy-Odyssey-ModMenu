Luvvy Odyssey Mod Menu v4.2.2 - Live Transform Teleport Fix
=====================================================

Built only for the exact uploaded Steam ACOdyssey.exe.
SHA256:
ac327dad2cbbdd72a3fda8e99cbeab9d12af328363e4f09bc5674bdd36b8c483

WHAT CHANGED
------------
The v2 logs proved that the in-process menu reached:
  build marker verified
  7 patch signatures verified
  overlay initialized; F10 input initialized

The proxy log also showed ACOdyssey starting more than once during the Ubisoft handoff. That made the active bink2w64 proxy and in-process DLL loading part of the protected startup sequence.

v3 removed both from the active design. v4 kept that working external startup core frozen. v4.2.2 starts from v4.2.1. The proven launcher, process-lock fix, waypoint capture observer, Stealth / Undetected module, and every other cheat module remain unchanged. Only the final teleport application path was replaced.

v4.2 does NOT:
  replace bink2w64.dll
  inject LuvvyOdysseyMod.dll
  call remote LoadLibraryW
  modify game memory during startup

Instead, LuvvyOdysseyExternalMenu.exe runs separately. It launches the Steam app normally, ignores transient ACOdyssey startup processes, and waits for one PID to contain uplay_r1_loader64.dll and own a visible 640x360+ game window continuously for 20 seconds. Only then does it attach.

The external menu verifies the runtime PE timestamp, SizeOfImage, every exact signature, and the expected original bytes before enabling a feature. No cheat effect is applied automatically. After the final game PID is stable and the overlay is created, v4.2 performs no game-memory writes. The waypoint observer is installed only when you explicitly press Enter on the teleport row while in game.

INSTALL / RUN
-------------
1. Extract the ZIP directly into the Assassin's Creed Odyssey folder beside ACOdyssey.exe.
2. Close the Ubisoft crash dialog and make sure ACOdyssey.exe is not running.
3. Double click "Luvvy Odyssey.exe".
4. v4.2 restores the original Bink DLL if v1/v2 is still installed.
5. Steam and Ubisoft Connect perform their normal launch/authentication flow.
6. The external menu waits for the final stable game process.
7. Press F10 after the game is up.

The v3 startup/overlay core was runtime-proven. v4.2 restores its read-only startup rule. The verified Stealth / Undetected module and every other v4 cheat module are left untouched.

MENU KEYS
---------
F10       open / close
Up / Down select
Enter     toggle / run selected action
Esc       hide

FEATURES
--------
God Mode [EXPERIMENTAL]
Infinite Adrenaline
Infinite Oxygen
No Ability Cooldown [v2, replaced failed v3 implementation]
Infinite Ability Points [v2, parent + hidden child patch]
Remove Horse Speed Limit
One Hit Kill [replaces Massive Damage]
Stealth / Undetected
Infinite Materials + Drachmae + Arrows
No Bounty
Inventory Capacity 1000
Ship God Mode + Enemy Ship One Hit Kill
Infinite Ship Stamina [EXPERIMENTAL]
Infinite Felucca HP
Maximum Phobos Speed
Auto Climb [EXPERIMENTAL]
XP Boost +8000 [EXPERIMENTAL]
Teleport to Custom Map Waypoint [captured ACTION]
Disable All

WAYPOINT TELEPORT v4.2.2
----------------------
v4.1 automatically installed the waypoint observer immediately after attaching. That was a regression because it modified Odyssey before you requested a cheat and could interfere with Ubisoft verification/startup.

Waypoint capture remains explicit and user-triggered. Startup and overlay initialization are read-only. After [WAYPOINT CAPTURED], the second Enter no longer writes to the old captured RDX+0xF4 field. v4.2.2 temporarily hooks the exact live character transform instruction used by the supplied working CE teleport scripts at ACOdyssey.exe+0x183D20B. It writes the captured XYZ to [RDX+0x50/+0x54/+0x58] for 30 transform updates, then automatically restores the original 8 bytes. This is intended to stop the engine from immediately overwriting a one-time external position write.

Use it like this:
1. Launch with Luvvy Odyssey.exe and wait until you are fully in game.
2. Press F10.
3. Select Teleport to Custom Map Waypoint. It should show [ARM CAPTURE].
4. Press Enter once. The row changes to [WAITING FOR WAYPOINT].
5. Open the world map and place a new custom waypoint or move the existing one.
6. Return to the game. The row should show [WAYPOINT CAPTURED].
7. Press Enter on the teleport row again to teleport.

Disable All restores the original 7 bytes used by the observer. After Disable All, teleport must be armed again before capturing another waypoint.

MATERIALS / MONEY
-----------------
The working CE table notes that the materials/coins path becomes visible after an inventory-changing action. After enabling it, buy, engrave, or upgrade something once if the values do not update immediately.

ITEM GRANTING
-------------
The uploaded Get Item CE table was analyzed and kept as a verified reference, but bulk item granting is not exposed in v4. Its working implementation invokes the game's internal GetItem routine from a specially initialized TLS worker and creates persistent save changes. That needs its own isolated module rather than being mixed into this runtime-cheat update.

LOGS
----
LuvvyExternalMenu.log   v4.2.2 process selection, build checks, waypoint capture, live-transform teleport, patch/restore results
LuvvyProxy.log          legacy v1/v2 only. v4.2 should add no new proxy entries.
LuvvyModMenu.log        legacy v1/v2 only. v4.2 should add no new in-process mod entries.

STARTUP VIDEO SKIP
------------------
The reversible .bk2 logo/warning skip remains. Files are renamed with .luvvyskip, not deleted.

UBISOFT CONNECT
---------------
Ubisoft Connect authentication and Steam/Ubisoft ownership checks are not bypassed. v4.2 keeps the mod completely out of that startup phase.

RESTORE
-------
Run "Restore Vanilla.bat". It restores an older Luvvy Bink proxy if necessary, removes active Luvvy runtime payloads, and restores the renamed startup videos.

LEGACY SOURCE
-------------
The old v2 Bink proxy and in-process mod DLL are preserved under LuvvyOdyssey\Source\Legacy* for reference only. v4.2 never installs or loads them.
