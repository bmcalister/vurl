#import <Foundation/Foundation.h>
#import "vurl.h"

// constants
NSString * const hosts =  @"/etc/hosts";
NSString * const httpd = @"/Applications/MAMP/conf/apache/httpd.conf";
NSString * const start_vurl = @"## BEGIN vurl";
NSString * const end_vurl = @"## END vurl";


int main(int argc, const char * argv[])
{

   @autoreleasepool {

      // become root
      setuid(0);

      // create new vurl instance
      vurl *v = [[vurl alloc] init:hosts 
                                  :httpd
                                  :start_vurl
                                  :end_vurl];
      
      // gets url argument
      NSString *url = [[NSUserDefaults standardUserDefaults] valueForKey:@"url"];

      // exit if no url defined
      if(!url){
         fputs("No development URL entered!\nUsage: \"vurl -url <example.com>\"\n", stdout);
         return 0;
      }

      // set URL
      [v setUrl: url];

      // get current path
      NSFileManager *filemgr;
      NSString *currentPath;
      filemgr = [[NSFileManager alloc] init];
      currentPath = [filemgr currentDirectoryPath];

      // set path
      [v setPath: currentPath];

      // init setting of DEV URL
      [v setNewDevURL];
   
   }     

   return 0;

}