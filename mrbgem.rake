require 'mkmf'

# patch for old mkmf bug
if Gem::Version.create(RUBY_VERSION) <= Gem::Version.create('1.9.3')
  def try_link(src, opt = '', *opts, &b)
    try_link0(src, opt, *opts, &b)
  ensure
    rm_f ['conftest*', 'c0x32*']
  end
end
# patch end
build_extconf = lambda do |fn|
  return if File.exist?(fn)

  # TODO
  # if open this block
  # raise error: redefinition of 'struct timespec'
  # in windows
  if RUBY_PLATFORM !~ /mingw|mswin/
    have_func 'setresuid'
    have_func 'setreuid'
    have_func 'setruid'
    have_func 'setuid'
  end

  create_header fn
end

MRuby::Gem::Specification.new('mruby-process-ext') do |spec|
  spec.license = 'MIT'
  spec.author  = 'ksss <co000ri@gmail.com>'

  FileUtils.mkdir_p build_dir
  build_extconf["#{build_dir}/extconf.h"]
  cc.include_paths << build_dir
end
