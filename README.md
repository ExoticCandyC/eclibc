![alt text](media/banner.png)
<h1 align="center">ExoticCandy C Collection</h1>
<h3 align="center">Shared C library for the common needs of any C projects</h3>
<h4 align="center">Free and Open Source library, used in all ECC softwares</h4>
<br />
<p align="center">
<a href="https://github.com/ExoticCandyC/eclibc/blob/master/LICENSE"><img src="https://img.shields.io/badge/License-GNU%20GPL%20v3.0-blueviolet?style=plastic&color=A10AA1&logo=gnu" /></a>
<a href="#"><img src="https://img.shields.io/badge/Language-C-pink?style=plastic&color=blueviolet&logo=c" /></a>
<a href="#"><img src="https://img.shields.io/badge/Library%20name-eclibc-blueviolet?style=plastic&color=B81D7A&logo=data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iaXNvLTg4NTktMSI/Pg0KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDE5LjAuMCwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPg0KPHN2ZyB2ZXJzaW9uPSIxLjEiIGlkPSJDYXBhXzEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHg9IjBweCIgeT0iMHB4Ig0KCSB2aWV3Qm94PSIwIDAgNTQuOTcxIDU0Ljk3MSIgc3R5bGU9ImVuYWJsZS1iYWNrZ3JvdW5kOm5ldyAwIDAgNTQuOTcxIDU0Ljk3MTsiIHhtbDpzcGFjZT0icHJlc2VydmUiPg0KPGc+DQoJPHBhdGggZD0iTTUxLjE3MywzLjgwMWMtNS4wNjgtNS4wNjgtMTMuMzE1LTUuMDY2LTE4LjM4NCwwbC05LjE5Miw5LjE5MmMtMC43ODEsMC43ODEtMC43ODEsMi4wNDcsMCwyLjgyOA0KCQljMC43ODEsMC43ODEsMi4wNDcsMC43ODEsMi44MjgsMGw5LjE5Mi05LjE5MmMxLjY5MS0xLjY5LDMuOTUxLTIuNjIyLDYuMzYzLTIuNjIyYzIuNDEzLDAsNC42NzMsMC45MzIsNi4zNjQsMi42MjMNCgkJczIuNjIzLDMuOTUxLDIuNjIzLDYuMzY0YzAsMi40MTItMC45MzIsNC42NzItMi42MjMsNi4zNjNMMzYuMzI1LDMxLjM3OWMtMy41MSwzLjUwOC05LjIxOSwzLjUwOC0xMi43MjksMA0KCQljLTAuNzgxLTAuNzgxLTIuMDQ3LTAuNzgxLTIuODI4LDBzLTAuNzgxLDIuMDQ4LDAsMi44MjhjMi41MzQsMi41MzQsNS44NjMsMy44MDEsOS4xOTIsMy44MDFzNi42NTgtMS4yNjcsOS4xOTItMy44MDENCgkJbDEyLjAyMS0xMi4wMjFjMi40NDctMi40NDYsMy43OTUtNS43MTEsMy43OTUtOS4xOTJDNTQuOTY4LDkuNTEyLDUzLjYyLDYuMjQ4LDUxLjE3MywzLjgwMXoiLz4NCgk8cGF0aCBkPSJNMjcuMTMyLDQwLjU3bC03Ljc3OCw3Ljc3OGMtMS42OTEsMS42OTEtMy45NTEsMi42MjMtNi4zNjQsMi42MjNjLTIuNDEyLDAtNC42NzMtMC45MzItNi4zNjQtMi42MjMNCgkJYy0zLjUwOS0zLjUwOS0zLjUwOS05LjIxOSwwLTEyLjcyOEwxNy45NCwyNC4zMDZjMS42OTEtMS42OSwzLjk1MS0yLjYyMiw2LjM2NC0yLjYyMmMyLjQxMiwwLDQuNjcyLDAuOTMyLDYuMzYzLDIuNjIyDQoJCWMwLjc4MSwwLjc4MSwyLjA0NywwLjc4MSwyLjgyOCwwczAuNzgxLTIuMDQ3LDAtMi44MjhjLTUuMDY3LTUuMDY3LTEzLjMxNC01LjA2OC0xOC4zODQsMEwzLjc5NywzMi43OTMNCgkJYy0yLjQ0NiwyLjQ0Ni0zLjc5NCw1LjcxMS0zLjc5NCw5LjE5MmMwLDMuNDgsMS4zNDgsNi43NDUsMy43OTUsOS4xOTFjMi40NDYsMi40NDcsNS43MTEsMy43OTUsOS4xOTEsMy43OTUNCgkJYzMuNDgxLDAsNi43NDYtMS4zNDgsOS4xOTItMy43OTVsNy43NzgtNy43NzhjMC43ODEtMC43ODEsMC43ODEtMi4wNDcsMC0yLjgyOFMyNy45MTMsMzkuNzg5LDI3LjEzMiw0MC41N3oiLz4NCjwvZz4NCjxnPg0KPC9nPg0KPGc+DQo8L2c+DQo8Zz4NCjwvZz4NCjxnPg0KPC9nPg0KPGc+DQo8L2c+DQo8Zz4NCjwvZz4NCjxnPg0KPC9nPg0KPGc+DQo8L2c+DQo8Zz4NCjwvZz4NCjxnPg0KPC9nPg0KPGc+DQo8L2c+DQo8Zz4NCjwvZz4NCjxnPg0KPC9nPg0KPGc+DQo8L2c+DQo8Zz4NCjwvZz4NCjwvc3ZnPg0K" /></a>
</p>
<p align="center">
<a href="https://archlinux.org"><img src="https://img.shields.io/badge/Native%20OS-GNU%20Linux-blueviolet?style=plastic&color=1E96CF&logo=linux&logoColor=ffffff" /></a>
<a href="https://github.com/espressif/esp-idf"><img src="https://img.shields.io/badge/Supported%20target-Espressif®%20ESP-blueviolet?style=plastic&color=A31728&logo=data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBzdGFuZGFsb25lPSJubyI/PgogICAgICAgIDwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgCiAgICAgICAgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+IDxzdmcgc3R5bGU9ImNvbG9yOiByZWQiIHJvbGU9ImltZyIgdmlld0JveD0iMCAwIDI0IDI0IiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciPjx0aXRsZT5Fc3ByZXNzaWY8L3RpdGxlPjxwYXRoIGQ9Ik0xMi45MjYgMTkuMzI0YTcuNiA3LjYgMCAwMC0yLjk4My02Ljc1NCA3LjQ0IDcuNDQgMCAwMC0zLjgyOC0xLjU1NC42OTcuNjk3IDAgMDEtLjYwNi0uNzMxLjY3NC42NzQgMCAwMS43NDMtLjYxNyA4Ljk3IDguOTcgMCAwMTggOS44MDUgNy44MjggNy44MjggMCAwMS0uMjk4IDEuNTQybDEuOTg5LjU2YTExLjAzOSAxMS4wMzkgMCAwMDEuNzE0LS42NTEgMTIuMTU5IDEyLjE1OSAwIDAwLjIxNy0yLjM0M0ExMi41NyAxMi41NyAwIDAwNy4yMTIgNi4xNzFhNS41MyA1LjUzIDAgMDAtMiAwIDQuMzU0IDQuMzU0IDAgMDAtMi4xNiAxLjMzNyA0LjI3NCA0LjI3NCAwIDAwMS45MDkgNi44NTYgOS44OTYgOS44OTYgMCAwMDEuMDc0LjE5NSA0LjAxMSA0LjAxMSAwIDAxMy4zMzcgMy45NTQgMy45NjUgMy45NjUgMCAwMS0uNjQgMi4xNmwxLjM3MS44OGExMC4xODIgMTAuMTgyIDAgMDAyLjA1Ny4zNDIgNy41MiA3LjUyIDAgMDAuNzU0LTIuNjI4bS4xNiA0LjczQTEzLjA3MyAxMy4wNzMgMCAwMS4wMDEgMTAuOTgzIDEyLjk4MiAxMi45ODIgMCAwMTMuODMgMS43MzdsLjc0My42OTdhMTIuMDY3IDEyLjA2NyAwIDAwMCAxNy4xNDEgMTIuMDY3IDEyLjA2NyAwIDAwMTcuMTQxIDBsLjY5Ny42OTdhMTIuOTcgMTIuOTcgMCAwMS05LjMzNiAzLjcyNk0yNCAxMC45OTNBMTAuOTkzIDEwLjk5MyAwIDAwMTIuOTQ5IDBjLS4zODkgMC0uNzY2IDAtMS4xNDMuMDU3bC0uMjUyLjczMmExOC45MTIgMTguOTEyIDAgMDExMS41ODggMTEuNTc2bC43MzEtLjI2M2MwLS4zNjYuMDY5LS43MzIuMDY5LTEuMTQzbS0xLjI2OSA1LjE2NUExNy41MyAxNy41MyAwIDAwNy44MTggMS4yN2ExMS4xMTkgMTEuMTE5IDAgMDAtMi40NTcgMS43N3YxLjYzNUExMy45MTkgMTMuOTE5IDAgMDExOS4yNjggMTguNTdoMS42MzRhMTEuNzEzIDExLjcxMyAwIDAwMS43NzEtMi40NDZNNy45MiAxNy44ODRhMS42OTEgMS42OTEgMCAxMS0xLjY5LTEuNjkxIDEuNjkxIDEuNjkxIDAgMDExLjY5IDEuNjkxIiBmaWxsPSJyZWQiPjwvcGF0aD48L3N2Zz4g" /></a>
<a href="https://www.microchip.com/en-us/education/developer-help/learn-tools-software/mcu-mpu/compilers/xc16"><img src="https://img.shields.io/badge/Supported%20target-Microchip®%20PIC24/dsPIC33-inactive?style=plastic&color=652D3F&logo=data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiIHN0YW5kYWxvbmU9Im5vIj8+CjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+CjxzdmcgdmVyc2lvbj0iMS4xIiBpZD0iTGF5ZXJfMSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiB4bWxuczp4bGluaz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94bGluayIgeD0iMHB4IiB5PSIwcHgiIHdpZHRoPSIxMHB4IiBoZWlnaHQ9IjEwcHgiIHZpZXdCb3g9IjAgMCAxMCAxMCIgZW5hYmxlLWJhY2tncm91bmQ9Im5ldyAwIDAgMTAgMTAiIHhtbDpzcGFjZT0icHJlc2VydmUiPiAgPGltYWdlIGlkPSJpbWFnZTAiIHdpZHRoPSIxMCIgaGVpZ2h0PSIxMCIgeD0iMCIgeT0iMCIKICAgIGhyZWY9ImRhdGE6aW1hZ2UvcG5nO2Jhc2U2NCxpVkJPUncwS0dnb0FBQUFOU1VoRVVnQUFBQW9BQUFBS0NBTUFBQUM2N0QrUEFBQUFCR2RCVFVFQUFMR1BDL3hoQlFBQUFDQmpTRkpOCkFBQjZKZ0FBZ0lRQUFQb0FBQUNBNkFBQWRUQUFBT3BnQUFBNm1BQUFGM0NjdWxFOEFBQUJFVkJNVkVYd1AwRDJob2ZuQUFELy8vL3YKT3p6MmpJeis1K2VrQUFELy8vL3RCUWJ1SXlUdUlDSHVJaUx1SVNIdUh5RHdSa2J0RlJidUlDSHVKQ1R1S0NudEZCVHRHQm53UlVidgpPVG50SFI3dUlDRHVLU251SWlQeVdGanZOemYwZFhYNXVManZNelArOVBULy8vLy8vUHo2dmIzLy8vLzZ4TVQvKy92Ly8vLy8vLy93ClNVbnRIQjN1S2lyNHBxYjBjM1B2TVRMdktTcnVKaWZ1SmlidUp5anVLU3J1SmlidUlDSHpYbC81ckt6dUtDbndRa0w1c0xENXRyYi8KLy8vMGRIVDJqNC8zbVpuelpHWDFoWWIvL1B6ODE5ZnpjSEgrN3U3KzdlMzk1dWYxaElYNXVycjJscGIzblozMmlZbnhVbFArOC9QOAoyZG54VUZEODNOM3ZORFh1SHlEM21wcjJoNGp0R3h6MWZuN3VKU2J1SFI3bG92anJBQUFBTlhSU1RsTUFBQUFBQUFBQUFBUUJSclBoCjJJa05XZWY1WVMzWjBpQ0Evb095NUVlMCszYUQvdWM3TU42a0NBRmg3TWtzQTFHLzZ1S2VLZmpLZkZVQUFBQUJZa3RIUkFNUkRFenkKQUFBQUNYQklXWE1BQUFzVEFBQUxFd0VBbXB3WUFBQUFCM1JKVFVVSDVnZ0VFd1VNMlhvcjdnQUFBM042VkZoMFVtRjNJSEJ5YjJacApiR1VnZEhsd1pTQjRiWEFBQUVpSnhWWk4wdHN3Q04xemloNUJCZ1RXY1p6WTNuV215eDYvRDVRZk8zYlNyOSttOFl6c1NBSWVQRUNpCjN6OS8wUS84QnExQ2NwWFZSeTgybU5qRnFpc1hZNnZtMW15Um1YbFpMNWZMeW96NVpob3oxYVhxTEVWbkx5cllPMW9qSFgxeUNGYngKU1plcWhqY1Vpa0NJV1ZaWnVNalZSNWw4TkFqYUhNWnM0QkwvN1dxTFM2eFJXQUFhdFRWd3lOUVhIdHNUeVZNTjVpNGhvUThKTG5YVQp1UmJpQUxkNlRrbmxSWXhuNEJsRUJTckVwV0Z1RUpNaVRWaVVyNWhsL0J2RWVjVTd4a0dFZU03SkNhTmhoRXRjWGg2K3VjZEFnVDJWClZkVmVYR1BLeFhCdmRNVlRaSUk3cStlUEY4Y3VYaEp4dDl6aVNTU01rVEhPM1FBUXVUajRpWWo0Q0xkZ0lkYjNLQUFCVklFSXRwYVIKYW9nUWR0elhiU0FFYkhVRU5sRDF3RzY1aUFBZjhhYXg1VWtSdm9Yd09jT1ZFWGhLZ0Vkb3k1MnJwMHFJeUVrQUNpQ3dYY041NnQ3SApSb3dWZ2pXb0QxZGh0U3Nlam9xUlR5TThBU0k0SEYrRnZnYjhodnNnL3ZTQnp1T2lNMHJnWDB5TXRJOE5GTTRuam9pclZyZE95Ymx5Ck90TytWeDRWNmlBZGU5YkttUVpyQmhubEd1cDdSQ2x5cHRzUEd4cVpVcUVvNHNBMWpLeDJQVlRYTVZhRk5JcnFYajBqQ21LczJVQkMKRE1rdDNONFlxcXI5SFdhRUtaSTlFaDN2TVVldDBJeWFtNkpFc3dhWkx6R2ZsVmgyYW1lTHhHbG1qbjYwMC90UmJjTUlCODdWVXVyTgozbU5kNWZBOTFiVFZuWVV3bVdXMXo2RXU2Vzd4amRaYk15VVhWRUxnZUFrNDlSQUdOeUYrODdxajJmQ1pDVHBwZEFsSjlFdVMzelJOCnhSNG9RZ2ExYk91VFZEQ0NiVUFJV09pWDBTdjU1cFJGOERITWdqeVRrcXNxWTNZbzlDa1NoZ2pTTjRRUENDSnp4QjlsdkVXUUFQUUcKWUJSSGpGSS9yQnE2dGNTaHBNanBPZWVpYjg4V2FUQkVMOGVlTU1zd3JOaUZxWERRc28vUkRrRUV1ZlVURFhHNC9nZEVzbEEvL2phbwpjR29tTTBEbjdlWDhnSmdQK3ptd2pYUEhoUjROWW9wRCs5N1dNMzgyZFJXbmJtemY3SDVKQlRyNDNaNSsvNHZiOUltSkxRSjM1Ry90CldNOEtoNzVRNjF0MVVRUDRndG9oSE5jc25XeHNYMmxhWCtsWnhPczVDKzlKZ0lFaEcreU9BRHBqNEMwQkgycVIvbGFNaDFwOFF3QjkKc3lzZUNLQXpCcjVEQUwwNU5iYkJEdUdJWHBqcHQ1WTRRbThrOFhxN0grMHJLSS9IajNWM0YzeTlNOUdEMkpkdC9ZTDNWUDk2cSswcgp6NnMxUGU3V05keEwwcmxmaStrUGRscWoveTU2aEM4QUFBQjJTVVJCVkFqWFkrRGc1T0xtNGVYaloyQms0QkFRTkRVekV4Sm1ZbVlRCkVUVzNzTFN5RmhObllaQ1F0TEcxczdkMWtHSm1rSFowY25aeGRYT1hrV1dROC9EMHN2WDJzWlZYWUZCVTh2WHpEd2dNVWxaaFVGVUwKRGdrTkM0OVExMkRRMU5JT3NZeU0wdEZsWldEVzB6Y3dOREkyWVdNSEFEMHpFWWprNGxteEFBQUFKWFJGV0hSa1lYUmxPbU55WldGMApaUUF5TURJeUxUQTRMVEEwVkRFNU9qQTFPakV5S3pBd09qQXdXTnJQSFFBQUFDVjBSVmgwWkdGMFpUcHRiMlJwWm5rQU1qQXlNaTB3Ck9DMHdORlF4T1Rvd05Ub3hNaXN3TURvd01DbUhkNkVBQUFBQVNVVk9SSzVDWUlJPSIgLz4KPC9zdmc+Cg==" /></a>
</p>
<p align="center">
<a href="https://github.com/ExoticCandyC/eclibc/releases"><img src="https://img.shields.io/badge/release-1.0-2A9692?style=plastic&logo=github&logoColor=ffffff&label=Release" /></a>
<a href="#"><img src="https://img.shields.io/github/directory-file-count/exoticcandyc/eclibc/include/ec?style=plastic&logo=github&label=Header files%20in%20repository&color=6B248E" /></a>
<a href="#"><img src="https://img.shields.io/github/repo-size/exoticcandyc/eclibc?style=plastic&logo=github&label=Repository%20size&color=1C26D8" /></a>
<a href="https://github.com/ExoticCandyC/eclibc/issues?q=is%3Aopen"><img src="https://img.shields.io/github/issues-raw/exoticcandyc/eclibc?style=plastic&color=8D621C" /></a>
<a href="https://github.com/ExoticCandyC/eclibc/issues"><img src="https://img.shields.io/github/issues-closed-raw/exoticcandyc/eclibc?style=plastic&color=1C8D24" /></a>
<a href="https://github.com/ExoticCandyC/eclibc/graphs/commit-activity"><img src="https://img.shields.io/github/last-commit/exoticcandyc/eclibc?style=plastic&color=B30F7F" /></a>
</p>

## Table of contents
🔸 [Brief description](#brief-description) \
🔸 [Dependencies](#dependencies) \
🔸 [Installation](#installation) \
🔸 [Documentation](#documentation) \
🔸 [Benchmark tools](#benchmark) 




## Brief description

**eclibc** is a C library, containing everyday use functions implemented in ANSI C language. This library can be compiled by most 16bit, 32bit and 64bit compilers, including:

**Computer targets:**<br />
<a href="https://gcc.gnu.org" style="text-decoration:none;">🔹 GCC</a><br />
<a href="https://clang.llvm.org/" style="text-decoration:none;">🔹 Clang</a><br />
<a href="https://bellard.org/tcc/" style="text-decoration:none;">🔹 TCC</a><br />
<a href="https://www.intel.com/content/www/us/en/developer/tools/oneapi/dpc-compiler.html" style="text-decoration:none;">🔹 ICC</a><br />
<a href="https://www.mingw-w64.org/" style="text-decoration:none;">🔹 MinGW32-GCC</a><br />

**Espressif targets:**<br />
<a href="https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/tools/idf-tools.html" style="text-decoration:none;">🔸 xtensa-esp32-elf-gcc</a><br />
<a href="https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/tools/idf-tools.html" style="text-decoration:none;">🔸 xtensa-esp32s2-elf-gcc</a><br />
<a href="https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/tools/idf-tools.html" style="text-decoration:none;">🔸 xtensa-esp32s2-elf-gcc</a><br />

**Micochip© micro-processor units:**<br />
<a href="https://www.microchip.com/en-us/education/developer-help/learn-tools-software/mcu-mpu/compilers/xc16" style="text-decoration:none;">🔸 xc16-gcc</a><br />
<a href="https://www.microchip.com/en-us/education/developer-help/learn-tools-software/mcu-mpu/compilers/xc32" style="text-decoration:none;">🔸 xc32-gcc</a><br />


## Dependencies

💠️ git: used to clone the repository<br />
💠️ cmake: used to generate the make scripts<br />
💠️ A C compiler of choice<br />
<br />

## Installation

This package will soon be added to Arch AUR. But the standard installation process appliees to this library:

```bash
git clone --depth=1 https://github.com/ExoticCandyC/eclibc.git
cd eclibc
./configure
make
sudo make install
```

Please note that in order to use non-standard C compilers, you should manually introduce the compiler of choice to the CMakeLists.txt file.

Basically since the library is targeted for C89 (ANSI) standard, and compiled using heavy warning eliminations and pedantic syntax, this source code should basically be able to be compiled with any compiler that contains C89 standard functions.

As an example, Micochip© XC8 doesn't have an implementation of "free" and "malloc" functions. So it will produce errors during compilation.

The testings and developements are done on:<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1️⃣ Arch Linux and Gentoo Linux, on X86-64 architecture, using GCC, Clang and TCC compilers.<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2️⃣ Arch Linux, using xtensa-esp32-elf-gcc compiler for ESP32 target.<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3️⃣ Arch Linux, using Micochip© XC16 for PIC24FJ256GA106 micro-controller unit and dsPIC33CK256MP406 micro-controller unit.<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4️⃣ Gentoo Linux on Raspberry Pi 4.<br />

Since the standard C protocols are being followed, and CMake is available on most platforms, one should easily be able to compile this library on any other target including FreeBSD, OpenBSD, OSX. 

As of August 2022, there are no plans to enable official support for Microsoft Windows®. But generally speaking, making the library compatible with MinGW32-GCC is a future goal and that would enable the unofficial support for Microsoft Windows® targets.

## Documentation

Wiki pages are planned to be added to the git repository, and an official website is planned to be generated that will host a begginer friendly C tutorial, beginner friendly C++ tutorial and a comprehensive guide on how to use eclibc in both C and C++<br />
Considering my tight schedule and the fact that this project is a solo project, there is no expected date for the aforementioned documentations.


## Benchmark tools

This library is packed with benchmarking tools.

<h4 align="center">Compare module</h4>

You can compare the execution time of two functions using the built-in "ec_performance_compare" function.

Following is an example of how to use the compare function, showing real comparison of C standard functions "strcpy" and "memcpy".

```c
/* Compare function from the benchmark module */
#include <ec/benchmark/compare.h>
#include <string.h>

/* Leaving the static parts out to make sure they dont affect the benchmark */
const char source[] = "source string";
const size_t len = sizeof(source);
char destination[sizeof(source)];
int index;

void function_1()
{
    /* copying a string using memcpy */
    for(index = 0; index < 3000; index++)
        memcpy(destination, source, len);
}

void function_2()
{
    /* copying a string using strcpy */
    for(index = 0; index < 3000; index++)
        strcpy(destination, source);
}

int main()
{
    /* Comparing memcpy vs strcpy*/
    ec_performance_compare(function_1, function_2, 1000000, 3000);
    return 0;
}
```

This is the output of the program:

```
eclibc: ec/benchmark/compare.h:
    Starting the function comparison algorithm:

Function 1 iteration progress: [##################] 100.0%
Function 1 finished iterating.

Function 2 iteration progress: [##################] 100.0%
Function 2 finished iterating.

eclibc: ec/benchmark/compare.h:

Comparison test results:
    Iterations: 3000000000

    Function 1:
        Start:	Fri Aug  5 20:33:20 2022
        Finish:	Fri Aug  5 20:33:28 2022
        Elapsed time: 8222487[us]

    Function 2:
        Start:	Fri Aug  5 20:33:28 2022
        Finish:	Fri Aug  5 20:33:34 2022
        Elapsed time: 6150673[us]

    Function 2 is 133.6843464122% faster than Function 1.


Press any key to continue.
```

As you can see, strcpy is 133.68% faster than memcpy.

<h4 align="center">Performance module</h4>

Inorder to see how long your program takes to run, all you have to do is including the "performance.h" file.

```c
#include <ec/benchmark/performance.h>
```

When the program finishes running, statistics will be printed. Following is an example output:

```
eclibc: ec/benchmark/performance.h:

          Program finished running.     
    Press any key to see the statistics.

Accuracy of the calculated time difference: 97.96%

Execution started at:
        Fri Aug  5 19:53:11 2022

Execution finished at:
        Fri Aug  5 19:53:19 2022

Execution of the program took:
        7455612[us]

Press any key to exit.
```


