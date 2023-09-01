# Launcher
Quick and dirty tool for redirecting executable launches.

## How to use
`Launcher.exe realExecutable.exe anyCmdLineArguments ToBeProxied At TheEnd`

The tool can have any name, so e.g. to redirect the launch of `start_protected_game.exe` to `EldenRing.exe`, one would rename `Launcher.exe` to `start_protected_game.exe` and then provide it with `EldenRing.exe` as a cmd line argument.

## Examples
* The Elden Ring example above which would disable Easy Anti-Cheat and allow modding of the game in offline mode.
* Redirecting `Starfield.exe` to `farcry5.exe` to enable Auto HDR on the Steam version of that game.
