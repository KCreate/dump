class File
  def mmap
    ptr = LibC.mmap(nil, size, LibC::PROT_READ | LibC::PROT_WRITE, LibC::MAP_SHARED, fd, 0)
    if ptr == LibC::MAP_FAILED
      raise Errno.new "Failed to mmap #{fd}"
    end
    Bytes.new Pointer(UInt8).new(ptr.address), size
  end
end

file = File.open "foo.txt", "r+"
map = file.mmap

puts map.hexdump

LibC.munmap(Pointer(Void).new(map.to_unsafe.address), file.size)
