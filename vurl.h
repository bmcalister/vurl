// ---- @interface section ----

@interface vurl: NSObject
{
    NSString* hosts;
    NSString* httpd;
    NSString* start;
    NSString* end;
    NSString* url;
    NSString* path;
}

/* init method */
-(id) init: (NSString*)hostsPath
          : (NSString*)httpdPath
          : (NSString*)startVurl
          : (NSString*)endVurl;

/* setters */
-(void) setUrl: (NSString*)newUrl;
-(void) setPath: (NSString*)newPath;

/* main logic */
-(void) setNewDevURL;

/* Apache httpd.conf helper methods */
-(BOOL) stringCheck: (NSString*)contentString;
-(BOOL) fileExists: (NSString*)filePath;


@end

// ---- @implementation section ----

@implementation vurl

- (id)init: (NSString*)hostsPath 
          : (NSString*)httpdPath
          : (NSString*)startVurl
          : (NSString*)endVurl
{
    self = [super init];
    if (self)
    {
        hosts = hostsPath;
        httpd = httpdPath;
        start = startVurl;
        end = endVurl;
    }

    return self;
}

-(void) setNewDevURL
{

  // check if hosts and httpd files exists
  // return if not
  if(![self fileExists:hosts] || ![self fileExists:httpd]){
    fputs("hosts or httpd file not found.\n", stdout);
    return;
  }

  NSString* hostsContent = [NSString stringWithContentsOfFile:hosts encoding:NSUTF8StringEncoding error:nil];
  NSString* httpdContent = [NSString stringWithContentsOfFile:httpd encoding:NSUTF8StringEncoding error:nil];

  // check if entry in hosts file
  if([self stringCheck:hostsContent]){

    // create new entry for hosts file and append end string
    NSString* newEntryHosts = [NSString stringWithFormat:@"127.0.0.1\t%@\n%@", url, end];

    // replace unique end string with new entry
    hostsContent = [hostsContent stringByReplacingOccurrencesOfString:end
                                     withString:newEntryHosts];


  }else{

    // create string
    NSString* newEntryHosts = [NSString stringWithFormat:@"%@\n\n%@\n127.0.0.1\t%@\n%@", hostsContent, start, url, end];
    hostsContent = newEntryHosts;

  }
    

  // check if entry in httpd file
  if([self stringCheck:httpdContent]){

    NSString* newEntryHttpd = [NSString stringWithFormat:@"<VirtualHost *>\n\tDocumentRoot \"%@\"\n\tServerName %@\n</VirtualHost>\n\n%@", path, url, end];

    // replace unique end string with new entry
    httpdContent = [httpdContent stringByReplacingOccurrencesOfString:end
                                    withString:newEntryHttpd];


  }else{

    NSString* newEntryHttpd = [NSString stringWithFormat:@"%@\n\n%@\n\nNameVirtualHost *\n\n<VirtualHost *>\n\tDocumentRoot \"%@\"\n\tServerName %@\n</VirtualHost>\n\n%@", httpdContent, start, path, url, end];
    httpdContent = newEntryHttpd;

  }

  // write data back to file

  NSError* errorHosts = nil;
  NSError* errorHttpd = nil;

  // hosts
  [hostsContent writeToFile:hosts 
                  atomically:NO 
                    encoding:NSUTF8StringEncoding
                       error: &errorHosts];

  // check errors on hosts file
  if(errorHosts){
    fputs("there was an error writing to the hosts file, please check permissions and run with sudo.\n", stdout);
    return;
  }else{
    fputs("Your hosts file was updated successfully.\n", stdout);
  }

  // hosts
  [httpdContent writeToFile:httpd 
                 atomically:NO 
                   encoding:NSUTF8StringEncoding
                      error: &errorHttpd];

  if(errorHttpd){
    fputs("there was an error writing to the httpd file, please check permissions and run with sudo.\n", stdout);
  }else{
    fputs("Your httpd file was updated successfully.\n", stdout);
    fputs("Restart Apache.\n", stdout);
  }

}

-(void) setUrl:(NSString*)newUrl
{
    url = newUrl;
}

-(void) setPath:(NSString*)newPath
{
    path = newPath;
}

-(BOOL) fileExists:(NSString*)filePath
{
  NSFileManager *fileManager = [NSFileManager defaultManager];
  return [fileManager fileExistsAtPath:filePath];
}

-(BOOL) stringCheck:(NSString*)contentString
{
  return [contentString rangeOfString:end].location != NSNotFound;
}

@end
