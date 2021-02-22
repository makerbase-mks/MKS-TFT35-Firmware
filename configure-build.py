import os
import sys
import re
import xml.etree.ElementTree as ET

Import("env")
platform = env.PioPlatform()
board = env.BoardConfig()

# read IAR project file
def export_iar_project():
  files = []
  def get_files_from_group(group):
      return [x.text.replace('$PROJ_DIR$\\..\\', '.\\').replace('\\', '/') for x in group.findall('file/name')]

  def get_group(group, files):
      for type_tag in group.findall('group'):
          f = get_files_from_group(type_tag)
          files += [x for x in f if (x.endswith('.cpp') or x.endswith('.c'))]
          get_group(type_tag, files)

  root = ET.parse(os.path.join(env['PROJECT_DIR'], 'EWARM/mkstft35.ewp')).getroot()
  get_group(root, files)
  with open(os.path.join(env['PROJECT_DIR'], 'source-files.txt'), 'wt') as fp:
      for f in files:
          fp.write(f + "\n")
  exit(1)

# export_iar_project()

def load_source_files():
  files = ''
  with open('./source-files.txt', 'rt') as fp:
    files = ' '.join(["+<"+x.strip()+">" for x in fp.readlines()])

  src_filter = ' '.join(env.GetProjectOption('src_filter'))
  src_filter += files
  proj = env.GetProjectConfig()
  proj.set("env:" + env['PIOENV'], 'src_filter', src_filter)
  env.Replace(SRC_FILTER=src_filter)

load_source_files()

env.Append(CPPPATH=[
    os.path.join(env['PROJECT_DIR'], 'Inc'),
    os.path.join(env['PROJECT_DIR'], 'Drivers', 'STM32F4xx_HAL_Driver', 'Inc'),
    os.path.join(env['PROJECT_DIR'], 'Drivers', 'CMSIS', 'Device', 'ST', 'STM32F4xx', 'Include'),
    os.path.join(env['PROJECT_DIR'], 'Drivers', 'CMSIS', 'Include'),
    os.path.join(env['PROJECT_DIR'], 'Middlewares', 'Third_Party', 'FatFs', 'src'),
    os.path.join(env['PROJECT_DIR'], 'Middlewares', 'ST', 'STM32_USB_Host_Library', 'Class', 'MSC', 'Inc'),
    os.path.join(env['PROJECT_DIR'], 'Middlewares', 'Third_Party', 'FatFs', 'src', 'drivers'),
    os.path.join(env['PROJECT_DIR'], 'Drivers', 'STM32F4xx_MKS_Driver', 'Inc'),
    os.path.join(env['PROJECT_DIR'], 'Drivers', 'STM32F4xx_MKS_Driver', 'Src'),
    os.path.join(env['PROJECT_DIR'], 'Drivers', 'libstmf4', 'include'),
    os.path.join(env['PROJECT_DIR'], 'User', 'others'),
    os.path.join(env['PROJECT_DIR'], 'User', 'ui'),
    os.path.join(env['PROJECT_DIR'], 'Drivers', 'libstmf4'),
    os.path.join(env['PROJECT_DIR'], 'User', 'uart_model'),
    os.path.join(env['PROJECT_DIR'], 'User', 'others', 'Multi_language'),
    os.path.join(env['PROJECT_DIR'], 'Middlewares', 'GUI'),
    os.path.join(env['PROJECT_DIR'], 'User', 'others', 'QRENCODE'),
    os.path.join(env['PROJECT_DIR'], 'Middlewares', 'Config'),
    os.path.join(env['PROJECT_DIR'], 'Middlewares', 'ST', 'STM32_USB_Host_Library', 'Core', 'Inc'),
    ])

env.Append(
  CFLAGS=['-mcpu=cortex-m4',
    '-mthumb',
    '-ffunction-sections',
    '-fdata-sections',
    '-nostdlib',
    '-std=gnu11',
    "-fmerge-constants",
    # '-funwind-tables',
    # '-fasynchronous-unwind-tables',
    "--param",
    "max-inline-insns-single=500",
    "-mfpu=fpv4-sp-d16", "-mfloat-abi=hard",
    "--specs=nano.specs",
  ],
    
  ASFLAGS=[
    "-x", "assembler-with-cpp",
    '-mcpu=cortex-m4',
    '-mthumb',
    "-mfpu=fpv4-sp-d16", "-mfloat-abi=hard",
    "--specs=nano.specs",
  ],

  CXXFLAGS=[
      "-fpermissive",
      "-Wno-register",
      "-std=gnu++11",
      "-fno-rtti",
      "-fno-exceptions",
      "-fno-threadsafe-statics",
      "-fno-use-cxa-atexit",
  ],

  LINKFLAGS=[
      "-mthumb",
      "-mcpu=cortex-m4",
      "-mfpu=fpv4-sp-d16", "-mfloat-abi=hard",
      "--specs=nano.specs",
      "-Wl,--check-sections",
      "-Wl,--unresolved-symbols=report-all",
      "-Wl,--warn-common",
      "-Wl,--warn-section-align",
      "-Wl,--warn-unresolved-symbols",
  ],

  LIBS=["arm_cortexM4lf_math", "GUI"],

  LIBPATH=[os.path.join(env['PROJECT_DIR'], 'Src', 'pio', 'libs')]
)
env.Append(CXXFLAGS=env['CFLAGS'])

env.Prepend(LINKFLAGS=['-T', "Src/pio/ldscript.ld"])
