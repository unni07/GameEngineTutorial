f = open("C:\\Users\\KalaSaand\\Documents\\SourceCodes\\Sync\\AppLinkService\\src\\applink_service_callbacks.cpp")
#lines = f.readlines()
#for l in lines:
    #print(l)
line = f.readline()
while line:
    print(line)
    line = f.readline()

f.close()
