#!/usr/bin/env python3

import os
import sys
import getopt

import xml.etree.ElementTree as ET

g_path    = os.path.dirname(__file__)
g_name    = 'glld.h'
g_version = '2.0'
g_author  = 'Jakub Oleksiak (yakubofficialmail@gmail.com)'
g_licence = 'GNU LESSER GENERAL PUBLIC LICENSE Version 3, 29 June 2007'

g_gl_profile = 'core'

# Source: https://en.wikipedia.org/wiki/OpenGL#History
g_gl_version = '4.6'
g_gl_version_list: list = [
    '1.0', '1.1', '1.2', '1.2.1', '1.3', '1.4', '1.5',
    '2.0', '2.1',
    '3.0', '3.1', '3.2', '3.3',
    '4.0', '4.1', '4.2', '4.3', '4.4', '4.5', '4.6'
]

# Source: https://en.wikipedia.org/wiki/OpenGL_ES#Versions
g_gl_es_version = '3.2'
g_gl_es_version_list: list = [
    '1.0', '1.1',
    '2.0',
    '3.0', '3.1', '3.2'
]

# Source: https://en.wikipedia.org/wiki/OpenGL_SC
g_gl_sc_version = '2.0'
g_gl_sc_version_list: list = [
    '1.0',
    '2.0'
]

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
    enum.name  = element.get('name')
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
    length: str


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
    # param.class = element.get('class')
    param.length = element.get('len')

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
    parse.cmds  = list()
    parse.feat  = list()
    parse.ext   = list()

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

    with open(f'{g_path}/glld-template.h') as f:
        fstr = f.read()

    # Simple templates...

    # <<glld-author>>
    fstr = fstr.replace('<<glld-author>>', g_author)

    # <<glld-version>>
    fstr = fstr.replace('<<glld-version>>', g_version)

    # <<glld-licence>>
    fstr = fstr.replace('<<glld-licence>>', g_licence)

    # <<glld-profile>>
    fstr = fstr.replace('<<glld-gl-profile>>', g_gl_profile)

    # <<glld-glversion>>
    fstr = fstr.replace('<<glld-gl-version>>', g_gl_version)

    # <<glld-glesversion>>
    fstr = fstr.replace('<<glld-gl-es-version>>', g_gl_es_version)

    # <<glld-glscversion>>
    fstr = fstr.replace('<<glld-gl-sc-version>>', g_gl_es_version)

    # Advanced templates...
    
    # <<glld-gl-version-macros>>
    fstr = fstr.replace('<<glld-gl-version-macros>>', glld_gl_version_macros(parse))
    
    # <<glld-gl-extension-macros>>
    fstr = fstr.replace('<<glld-gl-extension-macros>>', glld_gl_extension_macros(parse))
    
    # <<glld-gl-types>>
    fstr = fstr.replace('<<glld-gl-types>>', glld_gl_types(parse))
    
    # <<glld-gl-enums>>
    fstr = fstr.replace('<<glld-gl-enums>>', glld_gl_enums(parse))
    
    # <<glld-gl-func-ptr>>
    fstr = fstr.replace('<<glld-gl-func-ptr>>', glld_gl_func_ptr(parse))
    
    # <<glld-gl-func-declr-0>>
    fstr = fstr.replace('<<glld-gl-func-declr-0>>', glld_gl_func_declr(parse, 0))
    
    # <<glld-gl-func-declr-1>>
    fstr = fstr.replace('<<glld-gl-func-declr-1>>', glld_gl_func_declr(parse, 1))
    
    # <<glld-gl-func-macros>>
    fstr = fstr.replace('<<glld-gl-func-macros>>', glld_gl_func_macros(parse))
    
    # <<glld-gl-func-nameaddr>>
    fstr = fstr.replace('<<glld-gl-func-nameaddr>>', glld_gl_func_nameaddr(parse))

    with open('glld.h', 'w') as f:
        f.write(fstr)


# =================
# SECTION: template
# =================

def glld_gl_version_macros(parse: glParse):
    feats = parse.feat
    if feats is None:
        return (None)

    result = ''
    for feat in feats:
        result += f'# define {feat.name}\n'

    return (result.rstrip())


def glld_gl_extension_macros(parse: glParse):
    exts = parse.ext
    if exts is None:
        return (None)

    result  = ''
    result += '# if defined (GLLD_LOAD_EXTENSIONS)\n'
    for ext in exts:
        result += f'#  define {ext.name}\n'
    result += '# endif\n'

    return (result.rstrip())


def glld_gl_types(parse: glParse):
    types = parse.types
    if types is None:
        return (None)

    result = ''
    for type in types:
        result += f'{type.value}\n'

        # case: #ifdef __APPLE__ ... #endif
        if '__APPLE__' in type.value:
            result = result \
                .replace('#ifdef __APPLE__', '\n#if defined (__APPLE__)') \
                .replace('#else', '#else') \
                .replace('#endif', '#endif /* __APPLE__ */\n')

    return (result.replace('#', '# ').rstrip())


def glld_gl_enums(parse: glParse):
    feats = parse.feat
    if feats is None:
        return (None)

    exts = parse.ext
    if exts is None:
        return (None)

    enums = parse.enums
    if enums is None:
        return (None)

    result = ''
    for feat in feats:
        reqs = feat.req
        # skip if this feature doesn't have any enums
        if len(reqs) == 1:
            if len(reqs[0].enums) == 0:
                continue

        result += f'# if defined ({feat.name})\n'
        for req in reqs:
            for e_str in req.enums:
                enum = next(enum for enum in enums if enum.name == e_str)
                result += f'#  define {enum.name} {enum.value}\n'
        result += '# endif\n'

    for ext in exts:
        reqs = ext.req
        # skip if this extension doesn't have any enums
        if len(reqs) == 1:
            if len(reqs[0].enums) == 0:
                continue

        result += f'# if defined ({ext.name})\n'
        for req in reqs:
            for e_str in req.enums:
                enum = next(enum for enum in enums if enum.name == e_str)
                result += f'#  define {enum.name} {enum.value}\n'
        result += '# endif\n'

    return (result.rstrip())


def glld_gl_func_ptr(parse: glParse):
    feats = parse.feat
    if feats is None:
        return (None)

    exts = parse.ext
    if exts is None:
        return (None)

    cmds = parse.cmds
    if cmds is None:
        return (None)

    result = ''
    for feat in feats:
        reqs = feat.req
        # skip if this feature doesn't have any cmds
        if len(reqs) == 1:
            if len(reqs[0].cmds) == 0:
                continue

        result += f'\n/* {feat.name} */\n'
        for req in reqs:
            for c_str in req.cmds:
                cmd = next(cmd for cmd in cmds if cmd.name == c_str)

                func = f'typedef {cmd.proto.ptype}'
                func += f' (APIENTRYP PFN{cmd.name.upper()}PROC) ('
                # append parameters between braces
                for param in cmd.params:
                    func += f'{param.ptype}, '
                # remove trailing comma if exists...
                if func[-2:] == ', ':
                    func = func[:-2]
                # or insert 'void' keyword between braces
                else:
                    func += 'void'
                func += ');\n'

                # append 'func' to 'result'
                result += func

    for ext in exts:
        reqs = ext.req
        # skip if this extension doesn't have any enums
        if len(reqs) == 1:
            if len(reqs[0].cmds) == 0:
                continue

        for req in reqs:
            for c_str in req.cmds:
                cmd = next(cmd for cmd in cmds if cmd.name == c_str)

                func = f'typedef {cmd.proto.ptype}'
                func += f' (APIENTRYP PFN{cmd.name.upper()}PROC) ('
                # append parameters between braces
                for param in cmd.params:
                    func += f'{param.ptype}, '
                # remove trailing comma if exists...
                if func[-2:] == ', ':
                    func = func[:-2]
                # or insert 'void' keyword between braces
                else:
                    func += 'void'
                func += ');\n'
                
                # check if 'func' already exists in 'result'
                if result.rfind(func) != -1:
                    continue

                # append 'func' to 'result'
                result += func

    return (result.rstrip())


def glld_gl_func_declr(parse: glParse, mode):
    feats = parse.feat
    if feats is None:
        return (None)

    exts = parse.ext
    if exts is None:
        return (None)

    cmds = parse.cmds
    if cmds is None:
        return (None)

    result = ''
    for feat in feats:
        reqs = feat.req
        # skip if this feature doesn't have any cmds
        if len(reqs) == 1:
            if len(reqs[0].cmds) == 0:
                continue

        for req in reqs:
            for c_str in req.cmds:
                cmd = next(cmd for cmd in cmds if cmd.name == c_str)

                func = ''
                match (mode):
                    # mode: 0 - regular declarations
                    case (0):
                        func += f'PFN{cmd.name.upper()}PROC '
                        func += f'glld_{cmd.name};\n'
                        # check if 'func' already exists in 'result'
                        if result.rfind(func) != -1:
                            continue

                    # mode: 1 - extern declarations
                    case (1):
                        func += 'extern '
                        func += f'PFN{cmd.name.upper()}PROC '
                        func += f'glld_{cmd.name};\n'

                # append 'func' to 'result'
                result += func

    for ext in exts:
        reqs = ext.req
        # skip if this extension doesn't have any enums
        if len(reqs) == 1:
            if len(reqs[0].cmds) == 0:
                continue

        for req in reqs:
            for c_str in req.cmds:
                cmd = next(cmd for cmd in cmds if cmd.name == c_str)

                func = ''
                match (mode):
                    # mode: 0 - regular declarations
                    case (0):
                        func += f'PFN{cmd.name.upper()}PROC '
                        func += f'glld_{cmd.name};\n'
                        # check if 'func' already exists in 'result'
                        if result.rfind(func) != -1:
                            continue

                    # mode: 1 - extern declarations
                    case (1):
                        func += 'extern '
                        func += f'PFN{cmd.name.upper()}PROC '
                        func += f'glld_{cmd.name};\n'

                # append 'func' to 'result'
                result += func

    return (result.rstrip())


def glld_gl_func_macros(parse: glParse):
    feats = parse.feat
    if feats is None:
        return (None)

    exts = parse.ext
    if exts is None:
        return (None)

    cmds = parse.cmds
    if cmds is None:
        return (None)

    result = ''
    for feat in feats:
        reqs = feat.req
        # skip if this feature doesn't have any cmds
        if len(reqs) == 1:
            if len(reqs[0].cmds) == 0:
                continue

        result += f'# if defined ({feat.name})\n'
        for req in reqs:
            for c_str in req.cmds:
                cmd = next(cmd for cmd in cmds if cmd.name == c_str)

                func  =  '#  define '
                func += f'{cmd.name} '
                func += f'(assert(glld_{cmd.name} != 0), glld_{cmd.name})\n'

                # append 'func' to 'result'
                result += func
        result += '# endif\n'

    for ext in exts:
        reqs = ext.req
        # skip if this extension doesn't have any enums
        if len(reqs) == 1:
            if len(reqs[0].cmds) == 0:
                continue

        result += f'# if defined ({feat.name})\n'
        for req in reqs:
            for c_str in req.cmds:
                cmd = next(cmd for cmd in cmds if cmd.name == c_str)

                func  =  '#  define '
                func += f'{cmd.name} '
                func += f'(assert(glld_{cmd.name} != 0), glld_{cmd.name})\n'

                # append 'func' to 'result'
                result += func
        result += '# endif\n'

    return (result.rstrip())


def glld_gl_func_nameaddr(parse: glParse):
    feats = parse.feat
    if feats is None:
        return (None)

    exts = parse.ext
    if exts is None:
        return (None)

    cmds = parse.cmds
    if cmds is None:
        return (None)

    result = ''
    for feat in feats:
        reqs = feat.req
        # skip if this feature doesn't have any cmds
        if len(reqs) == 1:
            if len(reqs[0].cmds) == 0:
                continue

        result += f'# if defined ({feat.name})\n'
        for req in reqs:
            for c_str in req.cmds:
                cmd = next(cmd for cmd in cmds if cmd.name == c_str)

                name = f'   {{ \"{cmd.name}\", (void **) &glld_{cmd.name} }},\n'
                # check if 'name' already exist in 'result'
                if result.rfind(name) != -1:
                    continue

                # append 'name' to 'result'
                result += name
        result += '# endif\n'

    for ext in exts:
        reqs = ext.req
        # skip if this extension doesn't have any enums
        if len(reqs) == 1:
            if len(reqs[0].cmds) == 0:
                continue

        result += f'# if defined ({feat.name})\n'
        for req in reqs:
            for c_str in req.cmds:
                cmd = next(cmd for cmd in cmds if cmd.name == c_str)

                name = f'   {{ \"{cmd.name}\", (void **) &glld_{cmd.name} }},\n'
                # check if 'name' already exist in 'result'
                if result.rfind(name) != -1:
                    continue

                # append 'name' to 'result'
                result += name
        result += '# endif\n'

    return (result.rstrip())

# =============
# SECTION: main
# =============

if __name__ == '__main__':
    try:
        tree = gl_loadxml(f'{g_path}/xml/gl.xml')
        parse = gl_parsexml(tree)
        opengl_loader(parse)
    except Exception as err:
        print(f'{__file__}: {err}')
        sys.exit(1)
