import os
import sys
import platform

env = Environment(ENV = { 'PATH' : os.environ['PATH'], 'HOME' : os.environ['HOME'] })
env.ParseConfig('sdl-config --cflags')
env.ParseConfig('sdl-config --static-libs')

env.Append(LIBS = ['SDLmain'])
env.Append(CXXFLAGS = ['-O3', '-Wall', '-Wextra'])
env.Append(CPPPATH = ['.'])
env.Append(CPPPATH = ['src'])

env.Program(target = "ForFun", source = Glob('src/Math/*.cpp') + Glob('src/Renderer/*.cpp') + Glob('src/Viewer/*.cpp'))
