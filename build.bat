@echo off
setlocal
pushd "%~dp0"
rem STREET FIGHTER III NEW GENERATION -- program ROM
rem Hitachi SHC 5.0, asmsh, lnk 6.0, rof2bin
if "%SHC_LIB%"=="" set SHC_LIB=bin
if "%SHC_TMP%"=="" set SHC_TMP=C:\TEMP
set PATH=%SHC_LIB%;%PATH%
rem the compiler revision that built New Generation (see README.md, Compiler)
set XJUMP_2I=2
set MDL_IV_AUTOINC=1
set MDL_MOD_CONST=3
set MDL_IMM_REG=191
set MDL_EQ_CONST=3
set MDL_GCSE=26
set GEN_LAST_IDX=4
set MDL_IV_START0=6
set PEP_SWITCH_END=3
set PEP_RETURN_EXIT=1
if not exist "%SHC_TMP%" mkdir "%SHC_TMP%"
if not exist obj mkdir obj
if exist obj\warnings.log del obj\warnings.log
if not exist build mkdir build
if not exist rom\sfiiina.zip if not exist rom\sfiiin.zip echo rom\sfiiina.zip is missing (see rom\README)& goto fail
if not exist build\rom_pieces.bin python tools\cps3rom1.py extract rom build\rom_pieces.bin
if errorlevel 1 goto fail
echo compiling

shc data\vectors.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\vectors.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
asmsh src\fixed_addr.src -object=obj\fixed_addr.obj
if errorlevel 1 goto fail
shc data\intr_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\intr_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
asmsh data\sections.src -object=obj\sections.obj
if errorlevel 1 goto fail
shc data\tasksw_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\tasksw_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\Entry_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Entry_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\cd_volume.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\cd_volume.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\work.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\work.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
asmsh src\intr.src -object=obj\intr.obj
if errorlevel 1 goto fail
shc src\Entry.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -aggressive=1 -object=obj\Entry.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
asmsh src\tasksw.src -object=obj\tasksw.obj
if errorlevel 1 goto fail
shc src\reset.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\reset.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\Entry_dbg.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Entry_dbg.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\entry_2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -noinline -section=const=CTBL -object=obj\entry_2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\Entry_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Entry_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\Com_Pl_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Com_Pl_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\chr_data_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\chr_data_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLCNT_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLCNT_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLCNT_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLCNT_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLCNT_tbl_c.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLCNT_tbl_c.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLMAIN_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLMAIN_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLS00_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLS00_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLS02_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLS02_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLS03_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLS03_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLPNM_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPNM_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLPDM_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPDM_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLPDM_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPDM_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLPCA_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPCA_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLPCU_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPCU_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLPAT_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLPAT00_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT00_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLPAT01_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT01_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLPAT04_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT04_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLPAT07_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT07_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLPAT08_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT08_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLPAT09_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT09_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PLPAT12_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT12_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\aboutspr_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\aboutspr_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\aboutspr_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\aboutspr_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\aboutspr_tbl_c.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\aboutspr_tbl_c.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\CHARSET_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\CHARSET_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\CHARID_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\CHARID_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\SLOWF_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SLOWF_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\SE_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SE_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\Se_Data.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Se_Data.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\SE_tbl2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SE_tbl2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\CALDIR_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\CALDIR_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\boot_task.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\boot_task.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\mode_init.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\mode_init.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\test_menu_scr.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\test_menu_scr.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\test_mode.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\test_mode.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\plcnt_work.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\plcnt_work.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\plcntset_2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\plcntset_2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLMAIN.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLMAIN.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLS00.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLS00.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLS01.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLS01.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLS02.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLS02.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLS03.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLS03.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPNM.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPNM.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPDM.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPDM.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPCA.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPCA.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPCU.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPCU.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPAT.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPATUNI.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPATUNI.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPAT00.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT00.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPAT01.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT01.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPAT02.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT02.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPAT03.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT03.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPAT04.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT04.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPAT05.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT05.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPAT06.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT06.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPAT07.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT07.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPAT08.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT08.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPAT09.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT09.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\plpat10.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\plpat10.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPAT11.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT11.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PLPAT12.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PLPAT12.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\asstbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=P -code=asmcode -object=obj\asstbl.src >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
python tools\incode.py obj\asstbl.src P
if errorlevel 1 goto fail
asmsh obj\asstbl.src -object=obj\asstbl.obj
if errorlevel 1 goto fail
shc data\gauge.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=P -code=asmcode -object=obj\gauge.src >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
python tools\incode.py obj\gauge.src P
if errorlevel 1 goto fail
asmsh obj\gauge.src -object=obj\gauge.obj
if errorlevel 1 goto fail
shc data\buttobi.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=P -code=asmcode -object=obj\buttobi.src >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
python tools\incode.py obj\buttobi.src P
if errorlevel 1 goto fail
asmsh obj\buttobi.src -object=obj\buttobi.obj
if errorlevel 1 goto fail
shc data\etc.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=P -code=asmcode -object=obj\etc.src >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
python tools\incode.py obj\etc.src P
if errorlevel 1 goto fail
asmsh obj\etc.src -object=obj\etc.obj
if errorlevel 1 goto fail
shc data\exchange.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=P -code=asmcode -object=obj\exchange.src >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
python tools\incode.py obj\exchange.src P
if errorlevel 1 goto fail
asmsh obj\exchange.src -object=obj\exchange.obj
if errorlevel 1 goto fail
shc src\aboutspr.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\aboutspr.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\CHARMOVE.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\CHARMOVE.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\CHARID.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\CHARID.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\HITCHECK.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\HITCHECK.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\HITPLPL.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\HITPLPL.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\HITPLEF.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\HITPLEF.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\HITEFPL.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\HITEFPL.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\HITEFEF.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\HITEFEF.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\SLOWF.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SLOWF.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\SE.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SE.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\workuser.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\workuser.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\se_2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -noinline -object=obj\se_2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\se_3.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\se_3.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\CALDIR.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\CALDIR.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\SYS_sub.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\SYS_sub.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\SYS_sub_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SYS_sub_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\Game_Main.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\Game_Main.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\DEMO_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\DEMO_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\Game_Main_2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Game_Main_2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\demo00.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\demo00.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\demo01.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\demo01.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\demo02_code.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\demo02_code.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\demo02_code_data.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\demo02_code_data.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\RANKING.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\RANKING.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\Manage_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Manage_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\workuser_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\workuser_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\Manage.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\Manage.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\Manage_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Manage_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\Com_Pl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\Com_Pl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\Com_Data.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Com_Data.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\sel_tech.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\sel_tech.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\manage_2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -noinline -section=const=CTBL -object=obj\manage_2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\win_2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -noinline -section=const=CTBL -object=obj\win_2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\Com_Sub_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Com_Sub_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\Getup.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Getup.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\pass0003.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\pass0003.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\Win_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Win_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\POW_DATA.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\POW_DATA.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\Sel_Data.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Sel_Data.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\continue.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\continue.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\Com_Sub.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Com_Sub.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\sel_pl_work.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sel_pl_work.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\pow_work.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\pow_work.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\pow_pow.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\pow_pow.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\sel_pl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -noinline -section=const=CTBL -object=obj\sel_pl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\win_2_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\win_2_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\pass0003_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\pass0003_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ACTIVE00_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ACTIVE00_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\active01_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active01_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\active02_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active02_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\active03_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active03_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\active04_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active04_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\active05_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active05_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\active07_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active07_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\active08_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active08_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\active09_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active09_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\active11_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active11_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\active12_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active12_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\FOLLOW02_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\FOLLOW02_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\Ck_Pass_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Ck_Pass_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\pass00_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\pass00_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PASS01_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS01_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PASS02_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS02_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PASS03_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS03_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PASS04_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS04_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PASS05_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS05_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PASS07_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS07_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PASS08_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS08_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PASS09_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS09_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PASS11_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS11_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\PASS12_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS12_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\pass15_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\pass15_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\SHELL00_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SHELL00_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\SHELL01_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SHELL01_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\SHELL03_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SHELL03_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\SHELL04_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SHELL04_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\SHELL11_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SHELL11_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\SHELL12_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SHELL12_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\game_config_jp_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\game_config_jp_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\next_cpu_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\next_cpu_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\ACTIVE00.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ACTIVE00.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\active01.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active01.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\active02.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active02.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\active03.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active03.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\active04.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active04.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\active05.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active05.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\active07.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active07.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\active08.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active08.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\active09.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active09.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\active11.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active11.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\active12.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\active12.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\FOLLOW01.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\FOLLOW01.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\FOLLOW02.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\FOLLOW02.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\Ck_Pass.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Ck_Pass.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\pass00.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\pass00.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PASS01.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS01.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PASS02.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS02.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PASS03.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS03.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PASS04.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS04.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PASS05.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS05.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PASS07.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS07.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PASS08.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS08.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PASS09.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS09.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PASS11.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS11.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\PASS12.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\PASS12.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\SHELL00.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SHELL00.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\SHELL01.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SHELL01.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\SHELL03.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SHELL03.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\SHELL04.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SHELL04.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\SHELL11.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SHELL11.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\SHELL12.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\SHELL12.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\game_config_main.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\game_config_main.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\game_config_jp.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\game_config_jp.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\CMD_MAIN_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\CMD_MAIN_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\game_config_en.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\game_config_en.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\CMD_MAIN_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\CMD_MAIN_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\sys_config_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sys_config_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\CMD_MAIN_tbl_c.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\CMD_MAIN_tbl_c.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\dbg_work.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\dbg_work.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\CMD_MAIN.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -noinline -section=const=CTBL -object=obj\CMD_MAIN.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\CMD_MAIN_ctbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\CMD_MAIN_ctbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\CMD_MAIN_tbl_d.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\CMD_MAIN_tbl_d.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\cmd_data.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\cmd_data.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ta_sub_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ta_sub_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\cmd_main_2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\cmd_main_2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\cmd_work.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\cmd_work.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\ta_sub.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ta_sub.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\tate00.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\tate00.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\bg_sub_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\bg_sub_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bg000.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\bg000.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\bg_sub_tbl_c.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\bg_sub_tbl_c.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\bg_sub_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\bg_sub_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\bg000_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\bg000_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\bg000_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\bg000_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\bg000_tbl_c.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\bg000_tbl_c.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\bg_data.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\bg_data.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\bg_data2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\bg_data2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bg_work.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\bg_work.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bgst000.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\bgst000.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bgst010.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\bgst010.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bgst030.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\bgst030.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bgst050.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\bgst050.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bgst170.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\bgst170.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bgst070.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\bgst070.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bgst090.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\bgst090.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bgst100.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\bgst100.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bgst110.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\bgst110.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bgst140.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\bgst140.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bgst150.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\bgst150.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bgst160.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\bgst160.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bgst020.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\bgst020.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bgst040.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\bgst040.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\bg000_tbl_d.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\bg000_tbl_d.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\bg000_tbl_e.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\bg000_tbl_e.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\n_input_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\n_input_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\appear_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\appear_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\n_input.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\n_input.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\appear.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\appear.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\appear_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\appear_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\win_pl_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\win_pl_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\win_pl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\win_pl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\win_pl_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\win_pl_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\lose_pl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\lose_pl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\end_main_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\end_main_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\op_end_work.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\op_end_work.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\end_main.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\end_main.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\end_main_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\end_main_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\end_main_tbl_c.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\end_main_tbl_c.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\end_main_tbl2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\end_main_tbl2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\end_1_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\end_1_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\end_main_c.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\end_main_c.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\end_1.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\end_1.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\end_2_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\end_2_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\end_2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\end_2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\end_3_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\end_3_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\end_3.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\end_3.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\end_4_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\end_4_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\end_4.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\end_4.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\end_5_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\end_5_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\end_5_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\end_5_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\end_5.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\end_5.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\end_7_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\end_7_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\end_7.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\end_7.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\end_8_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\end_8_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\end_9_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\end_9_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\end_8.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\end_8.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\end_9.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\end_9.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\end_10_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\end_10_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\end_10.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\end_10.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\end_11.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\end_11.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\end_sub_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\end_sub_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\end_sub.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\end_sub.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\end_sub_2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\end_sub_2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\color3rd.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\color3rd.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\sc_trans_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sc_trans_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\sc_data.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sc_data.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\sc_trans_tbl2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sc_trans_tbl2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\VITAL_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\VITAL_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\spgauge_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\spgauge_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\spgauge_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\spgauge_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\sc_data4.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sc_data4.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\sc_trans.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sc_trans.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\VITAL.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\VITAL.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\count.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\count.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\spgauge.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\spgauge.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\sc_sub.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sc_sub.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\sc_sub_2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sc_sub_2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\sc_sub_3.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sc_sub_3.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\cmb_cont.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\cmb_cont.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\sel_flow.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\sel_flow.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFECT_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFECT_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF02_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF02_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF03_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF03_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF03_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF03_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF09_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF09_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF10_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF10_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\eff12_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff12_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF13_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF13_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\eff14_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff14_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF18_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF18_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFECT.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFECT.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bg_work_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\bg_work_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF00.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF00.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF01_code.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF01_code.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF02.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF02.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF03.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF03.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF04.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF04.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff05.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff05.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff06.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff06.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF07.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF07.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff08.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff08.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF09.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF09.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF10.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF10.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF11.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF11.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff12.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff12.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF13.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF13.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff14.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff14.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\bg_work_c.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\bg_work_c.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effa6_work.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effa6_work.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF15.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF15.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF16.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF16.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF17.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF17.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF18.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF18.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF19.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF19.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff20.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\eff20.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF18_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF18_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF24_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF24_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF26_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF26_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF21.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF21.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF22.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF22.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF23.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF23.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF24.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF24.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF25.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF25.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF26.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF26.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF27.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF27.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff28.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff28.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF29.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF29.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF30.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF30.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF31.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF31.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF32.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF32.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF33.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF33.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\sel_pl_x3.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\sel_pl_x3.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF34.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF34.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF35.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF35.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff36.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\eff36.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF37_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF37_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF41_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF41_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF41_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF41_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF48_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF48_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF37.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF37.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF38.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF38.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\Eff39.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Eff39.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF40.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF40.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF41.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF41.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF42.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF42.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF43.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF43.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF44.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF44.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF45.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF45.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF46.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF46.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF47.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF47.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF48.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF48.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF49.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF49.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\Eff50.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Eff50.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\Eff51.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Eff51.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\Eff52.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Eff52.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF53.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF53.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF54.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF54.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF55.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\EFF55.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff56.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\eff56.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\Eff59_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Eff59_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff57.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff57.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF58.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF58.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\Eff59.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Eff59.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF60.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF60.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF61.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\EFF61.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF62.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\EFF62.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF67_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF67_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF63.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF63.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff64.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff64.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff65.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff65.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff66.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff66.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF67.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF67.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF68.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF68.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF69.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\EFF69.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF70_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF70_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF70.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF70.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF71.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\EFF71.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF71_data.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF71_data.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF72.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\EFF72.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF74_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF74_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff73.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff73.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF74.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\EFF74.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF75_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF75_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF76_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF76_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF81_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF81_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF83_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF83_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\Eff79_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Eff79_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF75.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF75.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF76.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF76.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF77.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF77.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF78.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF78.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF79.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF79.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF80.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF80.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF81.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF81.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF82.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF82.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF83.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF83.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF84.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF84.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF85.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\EFF85.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\eff87_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff87_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\Eff93_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Eff93_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFF92.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF92.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF86.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\EFF86.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff87.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff87.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff88.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff88.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effb8_mes.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effb8_mes.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff89.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff89.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff90.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff90.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff91.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff91.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff92_code.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff92_code.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\Eff93.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\Eff93.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff94.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\eff94.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\Eff95.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\Eff95.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFA6_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFA6_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\Eff93_data.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\Eff93_data.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFB1_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFB1_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFB4_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFB4_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFB6_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFB6_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFC0_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFC0_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFC0_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFC0_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFC4_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFC4_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFC7_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFC7_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFC9_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFC9_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFD0_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFD0_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFD4_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFD4_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF96.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF96.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\eff97.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eff97.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF98.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF98.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFF99.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFF99.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effa0.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effa0.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFA1.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFA1.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFA2_MAIN.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFA2_MAIN.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFA3.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFA3.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFA4.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFA4.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effa5.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effa5.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFA6.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFA6.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFA7.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFA7.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effa8.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effa8.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effa9.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effa9.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFB0.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFB0.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFB1.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFB1.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effb2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effb2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effb3.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effb3.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFB4.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFB4.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFB5.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFB5.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFB5_INIT.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFB5_INIT.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFB6.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFB6.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFB7.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFB7.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFB8.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFB8.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effb9.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effb9.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effa6_work_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effa6_work_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFC0.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFC0.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFC1.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFC1.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFC2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFC2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFC3.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFC3.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFC4.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFC4.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFC5.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFC5.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFC6.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFC6.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFC7.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFC7.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFC8.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFC8.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFC9.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFC9.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\efff9_mes.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\efff9_mes.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effg0_work.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effg0_work.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFD0.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFD0.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFD1.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFD1.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effd2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effd2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effd3.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effd3.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFD4.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFD4.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFD5.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFD5.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFD6.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\EFFD6.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFD7_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFD7_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EffD8_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EffD8_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFD9_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFD9_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFE2_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFE2_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFE2_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFE2_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFE5_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFE5_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFD7.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFD7.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EffD8.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EffD8.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFD9.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFD9.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EffE0.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EffE0.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFE1.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFE1.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFE2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFE2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effe3.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effe3.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFE4.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFE4.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFE5.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFE5.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effe6.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\effe6.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFE7.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFE7.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFE8.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFE8.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effe9.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\effe9.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\efff0_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\efff0_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFF1_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFF1_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFF2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFF2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\efff0.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\efff0.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFF1.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFF1.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFF2_code.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFF2_code.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFF3.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFF3.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFF4.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFF4.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\efff5.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\efff5.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\efff7_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\efff7_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\efff6.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\efff6.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\efff7.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\efff7.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\efff8_code_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\efff8_code_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFF8.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFF8.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFF8_c.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFF8_c.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFG4_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFG4_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFG5_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFG5_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFG6_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFG6_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\efff8_code.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\efff8_code.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFF9.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFF9.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EffG0.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EffG0.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFG1.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFG1.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFG2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFG2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFG3.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFG3.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFG4.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFG4.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFG5.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFG5.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFG6.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFG6.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFG7.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFG7.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effg8.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\effg8.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFG9_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFG9_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFG9_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFG9_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFH2_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFH2_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFH4_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFH4_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFG9.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFG9.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFH0.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFH0.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFH1.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFH1.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFH2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFH2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFH3.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFH3.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effh4.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effh4.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effh5.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=CTBL -object=obj\effh5.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFH6.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFH6.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\EFFH9_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFH9_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\meta_col_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\meta_col_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\sys_test_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sys_test_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\eeprom_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\eeprom_tbl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\sys_config_tbl_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sys_config_tbl_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\sys_config_tbl_c.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sys_config_tbl_c.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\CMD_MAIN_tbl_e.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\CMD_MAIN_tbl_e.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\sys_config_tbl_d.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sys_config_tbl_d.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\effh6_code.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effh6_code.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFH9.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFH9.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\EFFI0.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\EFFI0.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\gill_char.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\gill_char.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\alex_char.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\alex_char.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ryu_char.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ryu_char.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\yun_char.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\yun_char.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\dudley_char.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\dudley_char.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\necro_char.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\necro_char.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\hugo_char.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\hugo_char.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ibuki_char.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ibuki_char.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\elena_char.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\elena_char.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\oro_char.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\oro_char.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\yang_char.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\yang_char.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ken_char.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ken_char.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\sean_char.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sean_char.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\effect_char.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effect_char.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\gill_hitbox.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\gill_hitbox.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\alex_hitbox.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\alex_hitbox.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ryu_hitbox.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ryu_hitbox.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\yun_hitbox.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\yun_hitbox.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\dudley_hitbox.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\dudley_hitbox.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\necro_hitbox.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\necro_hitbox.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\hugo_hitbox.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\hugo_hitbox.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ibuki_hitbox.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ibuki_hitbox.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\elena_hitbox.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\elena_hitbox.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\oro_hitbox.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\oro_hitbox.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\yang_hitbox.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\yang_hitbox.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ken_hitbox.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ken_hitbox.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\sean_hitbox.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sean_hitbox.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ef13_hitbox.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ef13_hitbox.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\gill_attr.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\gill_attr.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\alex_attr.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\alex_attr.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ryu_attr.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ryu_attr.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\yun_attr.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\yun_attr.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\dudley_attr.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\dudley_attr.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\necro_attr.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\necro_attr.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\hugo_attr.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\hugo_attr.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ibuki_attr.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ibuki_attr.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\elena_attr.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\elena_attr.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\oro_attr.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\oro_attr.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\yang_attr.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\yang_attr.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ken_attr.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ken_attr.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\sean_attr.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sean_attr.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ef13_attr.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ef13_attr.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ef13_move.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ef13_move.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\gill_move.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\gill_move.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\alex_move.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\alex_move.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ryu_move.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ryu_move.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\yun_move.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\yun_move.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\dudley_move.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\dudley_move.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\necro_move.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\necro_move.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\hugo_move.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\hugo_move.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ibuki_move.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ibuki_move.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\elena_move.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\elena_move.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\oro_move.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\oro_move.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\yang_move.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\yang_move.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ken_move.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ken_move.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\sean_move.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sean_move.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\gill_yuca.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\gill_yuca.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\alex_yuca.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\alex_yuca.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ryu_yuca.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ryu_yuca.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\yun_yuca.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\yun_yuca.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\dudley_yuca.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\dudley_yuca.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\necro_yuca.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\necro_yuca.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\hugo_yuca.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\hugo_yuca.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ibuki_yuca.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ibuki_yuca.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\elena_yuca.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\elena_yuca.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\oro_yuca.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\oro_yuca.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\yang_yuca.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\yang_yuca.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\ken_yuca.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\ken_yuca.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\sean_yuca.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sean_yuca.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\stage_char.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\stage_char.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\scene_char.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\scene_char.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\scrn_bg050.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\scrn_bg050.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\scrn_bg040.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\scrn_bg040.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\scrn_bg070.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\scrn_bg070.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\scrn_bg100.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\scrn_bg100.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\scrn_eff48.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\scrn_eff48.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\scrn_bg150.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\scrn_bg150.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\scrn_effb0.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\scrn_effb0.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\scrn_op_bg.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\scrn_op_bg.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\scrn_ake.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\scrn_ake.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\scrn_end_100.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\scrn_end_100.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\scrn_end_200.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\scrn_end_200.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\scrn_end_500.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\scrn_end_500.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\scrn_end_900.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\scrn_end_900.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\scrn_end_1100.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\scrn_end_1100.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\scrn_end_shared.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\scrn_end_shared.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\chr_data.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\chr_data.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\effb8_conn.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effb8_conn.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\efff9_mes_jp.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\efff9_mes_jp.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\efff9_mes_en.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\efff9_mes_en.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\efff9_mes_es.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\efff9_mes_es.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\efff9_mes_pt.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\efff9_mes_pt.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\effb8_mes_jp.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effb8_mes_jp.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\effb8_mes_en.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effb8_mes_en.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\effb8_mes_pt.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effb8_mes_pt.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\effb8_mes_es.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\effb8_mes_es.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\snd_seq_b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\snd_seq_b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\snd_bank.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\snd_bank.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc data\snd_seq.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\snd_seq.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
asmsh lib\shclib.src -object=obj\shclib.obj
if errorlevel 1 goto fail
shc src\meta_col_mem.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=program=PSYS -object=obj\meta_col_mem.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\meta_col_strcpy.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=program=PSYS -object=obj\meta_col_strcpy.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\meta_col_lib.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=program=PSYS -object=obj\meta_col_lib.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=0
shc src\meta_col_bcd.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\meta_col_bcd.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
shc src\scrn_work.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\scrn_work.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=0
shc src\fifo.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\fifo.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
shc src\scrn_ctrl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=program=PSYS -object=obj\scrn_ctrl.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=0
shc src\family.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\family.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\sys_test.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\sys_test.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\sys_test_2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\sys_test_2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\iotest_out.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\iotest_out.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\soundtest.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\soundtest.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\colortest.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\colortest.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\sys_test_2a.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\sys_test_2a.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\sys_test_2b.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\sys_test_2b.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\sys_test_2c.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\sys_test_2c.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\sys_test_3.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\sys_test_3.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\sys_test_4.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\sys_test_4.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
shc data\sys_font.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=PSYS -code=asmcode -object=obj\sys_font.src >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
python tools\incode.py obj\sys_font.src PSYS
if errorlevel 1 goto fail
asmsh obj\sys_font.src -object=obj\sys_font.obj
if errorlevel 1 goto fail
set GEN_NARROW_CONST=0
shc src\coin_chute.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\coin_chute.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\sys_test_5.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\sys_test_5.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\coin_sw.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\coin_sw.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\coin_sw_2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\coin_sw_2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\eeprom.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\eeprom.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\sys_config.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\sys_config.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\sys_config_2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\sys_config_2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\sys_config_3.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\sys_config_3.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\spr_pool.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\spr_pool.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\spr_pool_2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\spr_pool_2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
asmsh src\simmram.src -object=obj\simmram.obj
if errorlevel 1 goto fail
set GEN_NARROW_CONST=0
shc src\simmram_slot.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\simmram_slot.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
asmsh src\simmram_10.src -object=obj\simmram_10.obj
if errorlevel 1 goto fail
set GEN_NARROW_CONST=0
shc src\poly_que.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\poly_que.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\spr_list.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\spr_list.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
set GEN_NARROW_CONST=0
shc src\textsound.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\textsound.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
shc src\textsound_2.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=program=PSYS,const=CTBL -object=obj\textsound_2.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
asmsh src\textsound_2_x1.src -object=obj\textsound_2_x1.obj
if errorlevel 1 goto fail
shc src\sound_status.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=program=PSYS -object=obj\sound_status.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
asmsh src\textsound_2_x2.src -object=obj\textsound_2_x2.obj
if errorlevel 1 goto fail
asmsh lib\slow_mvn.src -object=obj\slow_mvn.obj
if errorlevel 1 goto fail
asmsh lib\sta_sftra.src -object=obj\sta_sftra.obj
if errorlevel 1 goto fail
shc src\textsound_3.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=program=PSYS -object=obj\textsound_3.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
asmsh src\sh2_sub.src -object=obj\sh2_sub.obj
if errorlevel 1 goto fail
set GEN_NARROW_CONST=0
shc src\cram_bank.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=0 -nospeed -section=program=PSYS -object=obj\cram_bank.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set GEN_NARROW_CONST=
shc src\sound_work.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -object=obj\sound_work.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
shc src\sound_voice.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=program=PSYS -object=obj\sound_voice.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
asmsh src\sound_voice_x1.src -object=obj\sound_voice_x1.obj
if errorlevel 1 goto fail
asmsh src\sound_voice_2.src -object=obj\sound_voice_2.obj
if errorlevel 1 goto fail
set PEP_AUTOINC=0
set ASM_READY_WAVES=1
shc src\sound_voice_3.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=program=PSYS -object=obj\sound_voice_3.obj >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
set PEP_AUTOINC=
set ASM_READY_WAVES=
shc data\textsound_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=PSYS -code=asmcode -object=obj\textsound_tbl.src >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
python tools\incode.py obj\textsound_tbl.src PSYS
if errorlevel 1 goto fail
asmsh obj\textsound_tbl.src -object=obj\textsound_tbl.obj
if errorlevel 1 goto fail
asmsh lib\quick_strcpy.src -object=obj\quick_strcpy.obj
if errorlevel 1 goto fail
shc data\sound_voice_tbl.c -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include -optimize=1 -speed -section=const=PSYS -code=asmcode -object=obj\sound_voice_tbl.src >obj\shc.log 2>&1
if errorlevel 1 goto fail
findstr /c:") : " obj\shc.log >>obj\warnings.log
python tools\incode.py obj\sound_voice_tbl.src PSYS
if errorlevel 1 goto fail
asmsh obj\sound_voice_tbl.src -object=obj\sound_voice_tbl.obj
if errorlevel 1 goto fail
asmsh data\cg_labels.src -object=obj\cg_labels.obj
if errorlevel 1 goto fail
del obj\shc.log
set /a warnings=0
if exist obj\warnings.log for /f "usebackq delims=" %%l in ("obj\warnings.log") do set /a warnings+=1
echo %warnings% compiler warnings, listed in obj\warnings.log
lnk -subcommand=sfn.sub
if errorlevel 1 goto fail
rof2bin -s=06000000 -e=06800000 -v=FF sfn.abs
if errorlevel 1 goto fail
python tools\cps3rom1.py pack sfn.bin build\rom_pieces.bin rom build
if errorlevel 1 goto fail
echo build\prog.bin and the ROM set in build built: the arcade program
goto end
:fail
if exist obj\shc.log findstr /c:") : " obj\shc.log
echo BUILD FAILED
popd
exit /b 1
:end
popd
