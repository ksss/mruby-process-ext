assert 'Process.uid' do
  assert_kind_of Fixnum, Process.uid
end

assert 'Process.gid' do
  assert_kind_of Fixnum, Process.gid
end

assert 'Process.euid' do
  assert_kind_of Fixnum, Process.euid
end

assert 'Process.egid' do
  assert_kind_of Fixnum, Process.egid
end

assert 'Process.uid=' do
  assert_equal Process.uid, Process.uid = Process.uid
end

assert 'Process::Sys.setuid' do
  begin
    assert_nil Process::Sys.setuid(Process.uid)
  rescue NotImplementedError
    skip 'This environment not have system call setuid(2)'
  end
end

assert 'Process::Sys.setruid' do
  begin
    assert_nil Process::Sys.setruid(Process.uid)
  rescue NotImplementedError
    skip 'This environment not have system call setruid(2)'
  end
end
