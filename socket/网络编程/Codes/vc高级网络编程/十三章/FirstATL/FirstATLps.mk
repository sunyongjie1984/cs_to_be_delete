
FirstATLps.dll: dlldata.obj FirstATL_p.obj FirstATL_i.obj
	link /dll /out:FirstATLps.dll /def:FirstATLps.def /entry:DllMain dlldata.obj FirstATL_p.obj FirstATL_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del FirstATLps.dll
	@del FirstATLps.lib
	@del FirstATLps.exp
	@del dlldata.obj
	@del FirstATL_p.obj
	@del FirstATL_i.obj
