Pod::Spec.new do |s|
    s.name          = "GLTools"

    s.authors        = "yuchen peng"
    s.homepage       = "http://home.client.weibo.cn"
    s.license        = 'Private'
    s.summary        = s.name
    s.source         = {:path => '.'}
    s.version        = "1.0"

    s.frameworks = 'OpenGL', 'GLUT'

    s.source_files  = "GLTools/**/*.{h,m}"
    s.public_header_files  = "GLTools/**/*.h"
    s.vendored_libraries = "GLTools/*.a"
end
