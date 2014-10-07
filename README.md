vurl
====

create development urls in your terminal


# Installation

1. Make sure the paths in vurl.m match your local setup.<br>
    * default path to hosts file: "/etc/hosts"<br>
    * default path to httpd.conf file: "/Applications/MAMP/conf/apache/extras/httpd-vhosts.conf" (assuming MAMP)<br>

2. Compile vurl.m

    ```
    gcc -framework Foundation vurl.m -o vurl
    ```

2. copy vurl to /usr/local/bin

    ```
    sudo cp vurl /usr/local/bin/vurl
    ```

# Usage

1. run vurl in the desired folder (sudo may be required)

    ```
    sudo vurl -url myCoolProject.dev
    ```

2. Restart Apache


# ToDos

* Better error handling
* show all entries (vurl -all)
* removing entries (vurl -d myCoolProject.dev)
* add help (vurl -help)
