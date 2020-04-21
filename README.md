## Build

```shell
mkdir build
cd build
cmake ..
make
```

## Using

Copy the config file to the same folder to the executable file,Open a terminal  and cd to your dataset folder,use command 

```shell
for file in `ls your_dataset_folder/ -1`;do
./image_undistored your_dataset_folder/$file your_undistoredImg_folder/$file;
done;
```
