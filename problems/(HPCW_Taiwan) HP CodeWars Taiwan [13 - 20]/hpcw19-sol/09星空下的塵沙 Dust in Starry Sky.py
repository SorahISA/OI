import fileinput
from functools import reduce
import hashlib
import string
from typing import Dict, Iterator, List, cast


class Recognizer(object):
    def __init__(self):
        self.mapping: Dict[str, str] = {}

        # populate mapping table
        samples = Recognizer._loadSamples()
        for index, value in enumerate(Recognizer.DEFAULT_VALUES):
            self.mapping[Recognizer.hash(samples[index])] = value

    @classmethod
    def _loadSamples(cls, raw_data: str = None) -> List[str]:
        if not raw_data:
            # load default samples
            raw_data = cls.DEFAULT_SAMPLES

        samples = []

        lines = raw_data.splitlines()
        for y in range(0, len(lines), cls.FONT_HEIGHT):
            columns = []
            for x in range(len(lines[y])):
                column = [row[x] for row in lines[y:y+cls.FONT_HEIGHT]]
                isEmptyColumn = not reduce(lambda x, y: x or not y.isspace(), column, False)
                if not isEmptyColumn:
                    columns.append(column)
                    continue

                # transpose
                rows = [[columns[j][i] for j in range(len(columns))] for i in range(len(columns[0]))]
                columns = []

                samples.append(''.join(cell for row in rows for cell in row))

        return samples

    @staticmethod
    def hash(data: str) -> str:
        return hashlib.sha1(data.encode('utf-8')).hexdigest()

    def recognize(self, raw_data: str) -> List[str]:
        if not raw_data:
            return []

        samples = Recognizer._loadSamples(raw_data)
        results = [self.mapping[Recognizer.hash(s)] for s in samples]
        return results


    FONT_HEIGHT = 15
    DEFAULT_VALUES = string.ascii_lowercase + '.?'
    DEFAULT_SAMPLES = """
                  ..                 ..                                       
            . uW8"                 dF                      oec :              
            't888                 '88bu.                  @88888              
      u      8888   .         .   '*88888bu        .u     8"*88%       uL     
   us888u.   9888.z88N   .udR88N    ^"*8888N    ud8888.   8b.      .ue888Nc.. 
.@88 "8888"  9888  888E <888'888k  beWE "888L :888'8888. u888888> d88E'"888E' 
9888  9888   9888  888E 9888 'Y"   888E  888E d888 '88%"  8888R   888E  888E  
9888  9888   9888  888E 9888       888E  888E 8888.+"     8888P   888E  888E  
9888  9888   9888  888E 9888       888E  888F 8888L       *888>   888E  888E  
9888  9888  .8888  888" ?8888u../ .888N..888  '8888c. .+  4888    888& .888E  
"888*""888"  '%888*%"    "8888P'   '"888*""    "88888%    '888    *888" 888&  
 ^Y"   ^Y'      "'         "P'        ""         "YP'      88R     '"   "888E 
                                                           88>    .dWi   '88E 
                                                           48     4888~  J8%  
                                                           '8      ^"===*"'   
               .                  ..            ..                                   
  .uef^"      @88>     ..   < .z@8"'      x .d88"                                    
:d88E         %8P     888>   !@88E         5888R      ..    .     :       u.    u.   
'888E          .      "8P    '888E   u     '888R    .888: x888  x888.   x@88k u@88c. 
 888E .z8k   .@88u     .      888E u@8NL    888R   ~'8888~'888X'?888f' ^"8888""8888" 
 888E~?888L ''888E'  u888u.   888E'"88*"    888R     X888  888X '888>    8888  888R  
 888E  888E   888E  ''888E    888E .dN.     888R     X888  888X '888>    8888  888R  
 888E  888E   888E    888E    888E~8888     888R     X888  888X '888>    8888  888R  
 888E  888E   888E    888E    888E '888&    888R     X888  888X '888>    8888  888R  
 888E  888E   888&    888E    888E  9888.  .888B .  "*88%""*88" '888!'  "*88*" 8888" 
m888N= 888>   R888"   888E  '"888*" 4888"  ^*888%     '~    "    '"'      ""   'Y"   
 'Y"   888     ""     888E     ""    ""      "%                                      
      J88"            888E                                                           
      @%              888P                                                           
    :"              .J88" "                                                          
                                                      .x+=:.        s                   
                                                     z'    ^%      :8                   
       u.    .d''                        .u    .        .   <k    .88       x.    .     
 ...ue888b   @8Ne.   .u       .u@u     .d88B :@8c     .@8Ned8"   :888ooo  .@88k  z88u   
 888R Y888r  %8888:u@88N   .zWF8888bx ="8888f8888r  .@^%8888"  -*8888888 ~"8888 ^8888   
 888R I888>   '888I  888. .888  9888    4888>'88"  x88:  ')8b.   8888      8888  888R   
 888R I888>    888I  888I I888  9888    4888> '    8888N=*8888   8888      8888  888R   
 888R I888>    888I  888I I888  9888    4888>       %8"    R88   8888      8888  888R   
u8888cJ888   uW888L  888' I888  9888   .d888L .+     @8Wou 9%   .8888Lu=   8888 ,888B . 
 "*888*P"   '*88888Nu88P  '888Nx?888   ^"8888*"    .888888P'    ^%888*    "8888Y 8888"  
   'Y"      ~ '88888F'     "88" '888      "Y"      '   ^"F        'Y"      'Y"   'YP    
               888 ^             88E                                                    
               *8E               98>                                                    
               '8>               '8                                                     
                "                 '                                                     
   _                                                                            ...     
  u            x=~                             ..                            u*""888b.  
 88Nu.   u.   88x.   .e.   .e.     uL   ..    @L               ..           J88N. 8888r 
'88888.o888c '8888X.x888:.x888   .@88b  @88R 9888i   .dL     .@88i          '888 .8888> 
 ^8888  8888  '8888  888X '888k '"Y888k/"*P  'Y888k:*888.   ""%888>          '"  8888%  
  8888  8888   X888  888X  888X    Y888L       888E  888I     '88%              88*"    
  8888  8888   X888  888X  888X     8888       888E  888I   ..dILr~'           48  4    
  8888  8888   X888  888X  888X     '888N      888E  888I  '".-%88b            'h.u*    
 .8888b.888P  .X888  888X. 888~  .u./"888&     888E  888I   @  '888k    .        .      
  ^Y8888*""   '%88%''"*888Y"    d888" Y888*"  x888N><888'  8F   8888  .@8c      d8b.    
    'Y"         '~     '"       ' "Y   Y"      "88"  888  '8    8888 '%888"    "888%    
                                                     88F  '8    888F   ^*        %      
                                                    98"    %k  <88F                     
                                                  ./"       "+:*%'                      
                                                 ~'                                     """[1:]


lines = cast(Iterator[str], (line for line in fileinput.input()))
data = ''.join(lines)

r = Recognizer()
results = r.recognize(data)

print(''.join(results))
