
COM4Dbgps.dll: dlldata.obj COM4Dbg_p.obj COM4Dbg_i.obj
	link /dll /out:COM4Dbgps.dll /def:COM4Dbgps.def /entry:DllMain dlldata.obj COM4Dbg_p.obj COM4Dbg_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del COM4Dbgps.dll
	@del COM4Dbgps.lib
	@del COM4Dbgps.exp
	@del dlldata.obj
	@del COM4Dbg_p.obj
	@del COM4Dbg_i.obj
