#!/usr/bin/env python3

import os
import sys
import getopt

import xml.etree.ElementTree as ET

g_path: str = os.path.dirname(__file__)
g_name: str = 'gload.h'
g_version: str = '1.3'
g_author: str = 'Jakub Oleksiak (yakubofficialmail@gmail.com)'
g_licence: str = 'GNU LESSER GENERAL PUBLIC LICENSE Version 3, 29 June 2007'

# Source: https://en.wikipedia.org/wiki/OpenGL#History
g_gl_version_list: list = [
    '1.0', '1.1', '1.2', '1.2.1', '1.3', '1.4', '1.5',
    '2.0', '2.1',
    '3.0', '3.1', '3.2', '3.3',
    '4.0', '4.1', '4.2', '4.3', '4.4', '4.5', '4.6'
]

# Source: https://en.wikipedia.org/wiki/OpenGL_ES#Versions
g_gles_version_list: list = [
    '1.0', '1.1',
    '2.0',
    '3.0', '3.1', '3.2'
]

# Source: https://en.wikipedia.org/wiki/OpenGL_SC
g_glsc_version_list: list = [
    '1.0',
    '2.0'
]

g_opts: str = 'hvo:p:e:a:'
g_optl: list = [
    'help',         # -h, --help
    'version',      # -v, --version
    'output=',      # -o, --output
    'profile=',     # -p, --profile
    'extensions=',  # -e, --extensions
    'assertion=',   # -a, --assertion
]

# default options for generation script
g_opt: dict = {
    'output': f'{g_path}/gload.h',
    'profile': 'core',
    'version': g_gl_version_list[-1],
    'version-es': g_gles_version_list[-1],
    'version-sc': g_glsc_version_list[-1],
    'extensions': True,
    'assertion': True,
    'template': f'{g_path}/gload-template.h',
}


# ===============
# SECTION: getopt
# ===============

def gl_getopt():
    global g_opt

    try:
        opts, args = getopt.getopt(sys.argv[1:], g_opts, g_optl)
    except getopt.GetoptError as err:
        print(f'{__file__}: {err}')
        sys.exit(1)

    for opt, arg in opts:
        if opt in ('-v', '--version'):
            print(g_version.strip())
            sys.exit(0)

        elif opt in ('-o', '--output'):
            if os.path.isdir(arg):
                # we need to ensure that the path ends with a '/'
                if not arg.endswith('/'):
                    arg += '/'
                g_opt['output'] = arg + g_name

            else:
                if os.path.basename(arg) != g_name:
                    print(f'{__file__}: invalid path: {arg}')
                    sys.exit(1)
                g_opt['output'] = arg

        elif opt in ('-p', '--profile'):
            if arg not in ('core', 'compatibility'):
                print(f'{__file__}: invalid profile: {arg} (expected: core/compatibility)')
                sys.exit(1)
            g_opt['profile'] = arg
        
        elif opt in ('-e', '--extensions'):
            if arg not in ('on', 'off'):
                print(f'{__file__}: invalid extension state: {arg} (expected: on/off)')
                sys.exit(1)

            if arg == 'on':
                g_opt['extensions'] = True
            elif arg == 'off':
                g_opt['extensions'] = False
        
        elif opt in ('-a', '--assertion'):
            if arg not in ('yes', 'no'):
                print(f'{__file__}: invalid extension state: {arg} (expected: yes/no)')
                sys.exit(1)

            if arg == 'yes':
                g_opt['assertion'] = True
            elif arg == 'no':
                g_opt['assertion'] = False

        elif opt in ('-h', '--help'):
            print('help')
            sys.exit(0)


# ==========================
# SECTION: xml parser - type
# ==========================

class glType:
    name: str
    value: str
    requires: str

    def __eq__(self, o):
        return (self.name == o.name)


def gl_parsexml_t(element: ET.Element) -> glType:
    type: glType

    type = glType()
    type.name = element.get('name')
    type.requires = element.get('requires')
    if element.text:
        type.value = element.text
    else:
        type.value = str()
    for child in element:
        if child.tag == 'name':
            type.name = child.text
            type.value += type.name
            type.value += child.tail
        if child.tag == 'apientry':
            type.value += 'APIENTRY'
            type.value += child.tail
    return (type)


# ==========================
# SECTION: xml parser - enum
# ==========================

class glEnum:
    name: str
    value: str
    group: str

    def __eq__(self, o):
        return (self.name == o.name)


def gl_parsexml_e(element: ET.Element) -> glEnum:
    enum: glEnum

    enum = glEnum()
    enum.name = element.get('name')
    enum.value = element.get('value')
    enum.group = element.get('group')
    return (enum)


# =============================
# SECTION: xml parser - command
# =============================

class glCmdParam:
    name: str
    ptype: str
    group: str
    cls: str
    len: str


class glCmdProto:
    name: str
    ptype: str


class glCmd:
    name: str
    alias: str
    proto: glCmdProto
    params: list[glCmdParam]

    def __eq__(self, o):
        return (self.name == o.name)


def gl_parsexml_c(element: ET.Element) -> glCmd:
    cmd: glCmd

    cmd = glCmd()
    cmd.params = list()
    for child in element:
        if child.tag == 'proto':
            cmd.proto = gl_parsexml_cproto(child)
            cmd.name = child.find('name').text
        elif child.tag == 'param':
            cmd.params.append(gl_parsexml_cparam(child))
        elif child.tag == 'alias':
            cmd.alias = child.get('name')
    return (cmd)


def gl_parsexml_cproto(element: ET.Element) -> glCmdProto:
    proto: glCmdProto

    proto = glCmdProto()
    proto.ptype = str()
    proto.name = str()

    if element.text:
        proto.ptype += element.text.strip()

    for child in element:
        if child.tag == 'ptype':
            if proto.ptype:
                proto.ptype += ' '
            proto.ptype += f'{child.text.strip()}'.rstrip()
            if child.tail.strip():
                proto.ptype += f' {child.tail.strip()}'.rstrip()

        elif child.tag == 'name':
            proto.name += child.text

    if len(proto.ptype) == 0:
        proto.ptype = f'{element.text.strip()}'
        if element.tail.strip():
            proto.ptype += f'{element.tail.strip()}'.rstrip()
    return (proto)


def gl_parsexml_cparam(element: ET.Element) -> glCmdParam:
    param: glCmdParam

    param = glCmdParam()
    param.name = str()
    param.ptype = str()
    param.group = element.get('group')
    param.cls = element.get('class')
    param.len = element.get('len')

    if element.text:
        param.ptype += element.text
    for child in element:
        if child.tag == 'ptype':
            param.ptype += f'{child.text.strip()} {child.tail.strip()}'.strip()
        elif child.tag == 'name':
            param.name += child.text
    if len(param.ptype) == 0:
        param.ptype = f'{element.text.strip()} {element.tail.strip()}'.strip()
    return (param)


# =============================
# SECTION: xml parser - require
# =============================

class glReq:
    types: list[str]
    enums: list[str]
    cmds: list[str]


def gl_parsexml_r(element: ET.Element) -> glReq:
    req: glReq

    req = glReq()
    req.types = list()
    req.enums = list()
    req.cmds = list()
    for child in element:
        if child.tag == 'type':
            req.types.append(child.get('name'))
        elif child.tag == 'enum':
            req.enums.append(child.get('name'))
        elif child.tag == 'command':
            req.cmds.append(child.get('name'))
    return (req)


# =============================
# SECTION: xml parser - feature
# =============================

class glFeat:
    api: str
    name: str
    number: str
    req: list[glReq]


def gl_parsexml_f(element: ET.Element) -> glFeat:
    feat: glFeat

    feat = glFeat()
    feat.api = element.get('api')
    feat.name = element.get('name')
    feat.number = element.get('number')
    feat.req = list()

    reqs = element.findall('require')
    if len(reqs) == 0:
        return (None)

    for child in reqs:
        req: glReq

        req = gl_parsexml_r(child)
        feat.req.append(req)
    return (feat)


# ================================
# SECTION: xml parser - extensions
# ================================

class glExt:
    name: str
    supported: str
    req: list[glReq]


def gl_parsexml_ex(element: ET.Element) -> glExt:
    ext: glExt

    ext = glExt()
    ext.name = element.get('name')
    ext.supported= element.get('supported')
    ext.req = list()

    reqs = element.findall('require')
    if len(reqs) == 0:
        return (None)

    for child in reqs:
        req: glReq

        req = gl_parsexml_r(child)
        ext.req.append(req)
    return (ext)


# ===================
# SECTION: xml parser
# ===================

class glParse:
    types: list[glType]
    enums: list[glEnum]
    cmds: list[glCmd]
    feat: list[glFeat]
    ext: list[glExt]


def gl_loadxml(filepath: str) -> ET.ElementTree:
    tree: ET.ElementTree

    try:
        tree = ET.parse(filepath)
    except FileNotFoundError as err:
        print(f'{__file__}: {err}')
        sys.exit(1)
    return (tree)


def gl_parsexml(tree: ET.ElementTree) -> glParse:
    root: ET.ElementTree
    parse: glParse

    root = tree.getroot()
    if root.tag != 'registry':
        print(f'{__file__}: root error')
        sys.exit(1)
    parse = glParse()
    parse.types = list()
    parse.enums = list()
    parse.cmds = list()
    parse.feat = list()
    parse.ext = list()

    for child in root:

        if child.tag == 'types':
            for types in child.findall('type'):
                type: glType

                type = gl_parsexml_t(types)
                if type not in parse.types:
                    parse.types.append(type)

        elif child.tag == 'enums':
            for enums in child.findall('enum'):
                enum: glEnum

                enum = gl_parsexml_e(enums)
                if enum not in parse.enums:
                    parse.enums.append(enum)

        elif child.tag == 'commands':
            for cmds in child.findall('command'):
                cmd: glCmd

                cmd = gl_parsexml_c(cmds)
                if cmd not in parse.cmds:
                    parse.cmds.append(cmd)

        elif child.tag == 'feature':
            feat: glFeat

            feat = gl_parsexml_f(child)
            if feat is not None:
                parse.feat.append(feat)

        elif child.tag == 'extensions':
            for exts in child.findall('extension'):
                ext: glExt

                ext = gl_parsexml_ex(exts)
                if ext is not None:
                    parse.ext.append(ext)

    return (parse)


# ===============
# SECTION: loader
# ===============

def opengl_loader(parse: glParse):
    fstr: str

    with open(g_opt['template'], 'r') as f:
        fstr = f.read()

    # <<gload-version>>
    fstr = fstr.replace('<<gload-version>>', g_version)

    # <<gload-author>>
    fstr = fstr.replace('<<gload-author>>', g_author)

    # <<gload-licence>>
    fstr = fstr.replace('<<gload-licence>>', g_licence)

    # <<gload-profile>>
    fstr = fstr.replace('<<gload-glprofile>>', g_opt['profile'])

    # <<gload-glversion>>
    fstr = fstr.replace('<<gload-glversion>>', g_opt['version'])

    # <<gload-glesversion>>
    fstr = fstr.replace('<<gload-glesversion>>', g_opt['version-es'])

    # <<gload-glscversion>>
    fstr = fstr.replace('<<gload-glscversion>>', g_opt['version-sc'])

    # <<gload-macro-version>>
    fstr = fstr.replace('<<gload-macro-version>>', g_version)

    # <<gload-macro-glprofile>>
    template = gload_macro_glprofile()
    template = template.replace('#', '# ')
    fstr = fstr.replace('/* <<gload-macro-glprofile>> */', template)

    # <<gload-macro-glversion>>
    template = gload_macro_glversion()
    template = template.replace('#', '# ')
    fstr = fstr.replace('/* <<gload-macro-glversion>> */', template)

    # <<gload-macro-ext-state>>
    template = gload_macro_ext_state()
    template = template.replace('#', '# ')
    fstr = fstr.replace('/* <<gload-macro-ext-state>> */', template)

    # <<gload-macro-version-list>>
    template = gload_macro_version_list(parse.feat)
    template = template.replace('#', '# ')
    fstr = fstr.replace('/* <<gload-macro-version-list>> */', template)

    # <<gload-macro-ext-list>>
    template = gload_macro_ext_list(parse.ext)
    template = template.replace('#', '# ')
    fstr = fstr.replace('/* <<gload-macro-ext-list>> */', template)

    # <<gload-type-declr>>
    template = gload_type_declr(parse.types)
    template = template.replace('#', '# ')
    fstr = fstr.replace('/* <<gload-type-declr>> */', template)

    # <<gload-enum-declr>>
    template = gload_enum_declr(parse.feat, parse.enums)
    template += '\n'
    template += gload_enum_declr(parse.ext, parse.enums)
    template = template.replace('#', '# ')
    fstr = fstr.replace('/* <<gload-enum-declr>> */', template)

    # <<gload-func-ptr>>
    template = gload_func_ptr(parse.feat, parse.cmds)
    template += '\n'
    template += gload_func_ptr(parse.ext, parse.cmds)
    template = template.replace('#', '# ')
    fstr = fstr.replace('/* <<gload-func-ptr>> */', template)

    # <<glaod-func-nameaddr>>
    template = gload_func_nameaddr(parse.feat, parse.cmds)
    template += '\n'
    template += gload_func_nameaddr(parse.ext, parse.cmds)
    template = template.replace('#', '# ')
    fstr = fstr.replace('/* <<gload-func-nameaddr>> */', template)

    # <<gload-func-load>>
    template = gload_loadfunc(parse.feat, parse.cmds)
    template += '\n'
    template += gload_loadfunc(parse.ext, parse.cmds)
    template = template.replace('#', '# ')
    fstr = fstr.replace('/* <<gload-func-load>> */', template)

    # <<gload-func-declr-0>>
    template = gload_func_declr(parse.feat, parse.cmds, 0)
    template += '\n'
    template += gload_func_declr(parse.ext, parse.cmds, 0, template)
    template = template.replace('#', '# ')
    fstr = fstr.replace('/* <<gload-func-declr-0>> */', template)

    # <<gload-func-declr-1>>
    template = gload_func_declr(parse.feat, parse.cmds, 1)
    template += '\n'
    template += gload_func_declr(parse.ext, parse.cmds, 1, template)
    template = template.replace('#', '# ')
    fstr = fstr.replace('/* <<gload-func-declr-1>> */', template)

    # <<gload-func-declr-2>>
    template = gload_func_declr(parse.feat, parse.cmds, 2)
    template += '\n'
    template += gload_func_declr(parse.ext, parse.cmds, 2, template)
    template = template.replace('#', '# ')
    fstr = fstr.replace('/* <<gload-func-declr-2>> */', template)

    with open(g_opt['output'], 'w') as f:
        f.write(fstr)


# =================
# SECTION: template
# =================

def gload_macro_glprofile() -> str:
    result: str

    # GLOAD_GL_PROFILE macro...
    result  =  '#if !defined (GLOAD_GL_PROFILE)\n'
    result += f'# define GLOAD_GL_PROFILE \"{g_opt['profile']}\"\n'
    result +=  '#endif /* GLOAD_GL_PROFILE */'

    return (result.strip())

def gload_macro_glversion() -> str:
    result: str

    # GLOAD_GL_VERSION macro...
    result  =  '#if !defined (GLOAD_GL_VERSION)\n'
    result += f'# define GLOAD_GL_VERSION \"{g_opt['version']}\"\n'
    result +=  '#endif /* GLOAD_GL_VERSION */\n'

    # GLOAD_GLES_VERSION macro...
    result +=  '#if !defined (GLOAD_GLES_VERSION)\n'
    result += f'# define GLOAD_GLES_VERSION \"{g_opt['version-es']}\"\n'
    result +=  '#endif /* GLOAD_GLES_VERSION */\n'

    # GLOAD_GLSC_VERSION macro...
    result +=  '#if !defined (GLOAD_GLSC_VERSION)\n'
    result += f'# define GLOAD_GLSC_VERSION \"{g_opt['version-sc']}\"\n'
    result +=  '#endif /* GLOAD_GLSC_VERSION */'

    return (result.strip())

def gload_macro_ext_state() -> str:
    result: str

    # GLOAD_EXTENSIONS / GL_NO_EXTESIONS macros...
    result  = '#if !defined (GLOAD_EXTENSIONS)\n'
    result += '# if !defined (GLOAD_NO_EXTENSIONS)\n'

    # This is where the option 'g_opt['extensions']' is going to be used...
    if g_opt['extensions']:
        result += '#  define GLOAD_EXTENSIONS 1\n'
    else:
        result += '#  define GLOAD_NO_EXTENSIONS 1\n'

    result += '# endif /* GLOAD_NO_EXTENSIONS */\n'
    result += '#endif /* GLOAD_EXTENSIONS */\n'

    # NOTE:
    #  Remember that this is only the default setting that can be manipulated.
    #  You can either edit it in this very script, set it during generation or define it as a compile-time macro.
    #  By default I'm enabling extensions. Note that if you disable them then they won't be processed by gload.h.
    #  That being said using extensions when GLOAD_NO_EXTENSIONS can cause segfaults!
    return (result.strip())

def gload_macro_version_list(feats: list[glFeat]) -> str:
    result: str

    result = str()
    for feat in feats:
        result += f'#define {feat.name}\n'
    return (result.strip())

def gload_macro_ext_list(exts: list[glExt]) -> str:
    result: str

    result = '#if defined (GLOAD_EXTENSIONS)\n'
    for ext in exts:
        result += f'# define {ext.name}\n'
    result += '#endif /* GLOAD_EXTENSIONS */\n'
    return (result.strip())

def gload_type_declr(types: list[glType]) -> str:
    result: str

    result = str()
    for type in types:
        result += f'{type.value}\n'

        # case: #ifdef __APPLE__ ... #endif
        if '__APPLE__' in type.value:
            result = result \
                .replace('#ifdef __APPLE__', '\n#if defined (__APPLE__)') \
                .replace('#else', '#else') \
                .replace('#endif', '#endif /* __APPLE__ */\n')
    return (result.strip())


def gload_func_ptr(lst, cmds: list[glCmd]) -> str:
    result: str

    result = str()
    for child in lst:
        # check if 'cmds' list of current child's requiremens is greater than 0...
        # ...if not, we don't bother adding it to gload.h...
        if len(child.req) == 1:
            if len(child.req[0].cmds) == 0:
                continue

        result += f'#if defined ({child.name})\n\n'

        for req in child.req:
            for c_str in req.cmds:
                cmd: glCmd
                func: str

                cmd = next(cmd for cmd in cmds if cmd.name == c_str)
                func = f'typedef {cmd.proto.ptype}'
                func += f' (APIENTRYP PFN{cmd.name.upper()}PROC) ('
                for param in cmd.params:
                    func += f'{param.ptype}, '
                if func[-2:] == ', ':
                    func = func[:-2]
                else:
                    func += 'void'
                func += ');\n'
                result += func
        result += f'\n#endif /* {child.name} */\n'
    return (result.strip())


def gload_enum_declr(lst, enums: list[glEnum]) -> str:
    result: str

    result = str()
    for child in lst:
        # check if 'enums' list of current child's requiremens is greater than 0...
        # ...if not, we don't bother adding it to gload.h...
        if len(child.req) == 1:
            if len(child.req[0].enums) == 0:
                continue

        result += f'#if defined ({child.name})\n#\n'
        for req in child.req:
            for e_str in req.enums:
                enum: glEnum

                enum = next(enum for enum in enums if enum.name == e_str)
                result += f'# define {enum.name} {enum.value}\n'

        result += f'#\n#endif /* {child.name} */\n'
    return (result.strip())


def gload_func_declr(lst, cmds: list[glCmd], mode: int, prev: str = None) -> str:
    result: str

    result = str()
    for child in lst:
        # check if 'cmds' list of current child's requiremens is greater than 0...
        # ...if not, we don't bother adding it to gload.h...
        if len(child.req) == 1:
            if len(child.req[0].cmds) == 0:
                continue

        result += f'#if defined ({child.name})\n\n'
        # strip the last newline if we print macros...
        if mode == 2:
            result = result[:-1]

        for req in child.req:
            for c_str in req.cmds:
                cmd: glCmd
                func: str

                cmd = next(cmd for cmd in cmds if cmd.name == c_str)

                if mode == 0:
                    func = f'PFN{cmd.name.upper()}PROC '
                    func += f'gload_{cmd.name};\n'

                    search = f'\n{func}'
                    exist = result.rfind(search)
                    if exist != -1:
                        result += 'extern '

                    elif prev is not None:
                        exist = prev.rfind(search)
                        if exist != -1:
                            result += 'extern '


                elif mode == 1:
                    func = 'extern '
                    func += f'PFN{cmd.name.upper()}PROC '
                    func += f'gload_{cmd.name};\n'

                elif mode == 2:
                    func = '# define '
                    func += f'{cmd.name} '
                    if g_opt['assertion']:
                        func += f'(assert(gload_{cmd.name} != 0), gload_{cmd.name})\n'
                    else:
                        func += f'gload_{cmd.name}\n'

                result += func

        # add a newline if we're not printing macros...
        if mode != 2:
            result += '\n'
        result += f'#endif /* {child.name} */\n'
    return (result.strip())


def gload_func_nameaddr(lst, cmds: list[glCmd]) -> str:
    result: str

    result = str()
    for child in lst:
        # check if 'cmds' list of current child's requiremens is greater than 0...
        # ...if not, we don't bother adding it to gload.h...
        if len(child.req) == 1:
            if len(child.req[0].cmds) == 0:
                continue

        result += f'#if defined ({child.name})\n\n'

        for req in child.req:
            for c_str in req.cmds:
                cmd: glCmd
                name: str

                cmd = next(cmd for cmd in cmds if cmd.name == c_str)
                name = f'   {{ \"{cmd.name}\", (void **) &gload_{cmd.name} }},\n'
                result += name
        result += f'\n#endif /* {child.name} */\n'
    return (result.strip())


def gload_loadfunc(lst, cmds: list[glCmd]) -> str:
    result: str

    result = str()
    for child in lst:
        # check if 'cmds' list of current child's requiremens is greater than 0...
        # ...if not, we don't bother adding it to gload.h...
        if len(child.req) == 1:
            if len(child.req[0].cmds) == 0:
                continue

        result += f'#if defined ({child.name})\n\n'

        for req in child.req:
            for c_str in req.cmds:
                cmd: glCmd
                name: str

                cmd = next(cmd for cmd in cmds if cmd.name == c_str)
                name = f'   if defined (!gload_{cmd.name} && '
                name += f'!(gload_{cmd.name} = '
                name += f'(PFN{cmd.name.upper()}PROC) load(\"{cmd.name}\"))) '
                name += '{ return (0); }\n'
                result += name
        result += f'\n#endif /* {child.name} */\n'
    return (result.strip())


# =============
# SECTION: main
# =============

if __name__ == '__main__':
    gl_getopt()

    try:
        tree = gl_loadxml(f'{g_path}/xml/gl.xml')
        parse = gl_parsexml(tree)
        opengl_loader(parse)
    except Exception as err:
        print(f'{__file__}: {err}')
        sys.exit(1)
